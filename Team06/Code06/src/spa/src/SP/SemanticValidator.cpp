#include "SemanticValidator.h"

SemanticValidator::SemanticValidator(Program* root, WritePKB* writePKB, ReadPKB* readPKB)
    : ASTroot(root), writeApi(writePKB), readApi(readPKB){};

std::vector<ProcName> SemanticValidator::validate() {
    buildCallerCalleeTable();

    try {
        validateNoDuplicateProcedureName();
        validateCalledProceduresExist();
        auto topoOrder = validateNoCycles();
        return topoOrder;
    } catch (SemanticErrorException e) {
        throw e;
    }
}

void SemanticValidator::buildCallerCalleeTable() {
    for (const auto& procedure : ASTroot->procedureList) {
        procedureNames.push_back(procedure->procedureName);
        for (const auto& statement : procedure->getStatements()) {
            if (const auto i = CAST_TO(CallStatement, statement.get())) {
                procCallMap[procedure->procedureName].insert(i->procName);
            }
            if (isContainerStatement(statement.get())) {
                recurseCallStatementHelper(statement.get(), procedure->procedureName);
            }
        }
    }
}

void SemanticValidator::recurseCallStatementHelper(Statement* recurseStmt, ProcName parentProcedure) {
    if (const auto ifStmt = CAST_TO(IfStatement, recurseStmt)) {
        checkCallStatementHelper(ifStmt->getThenStatements(), parentProcedure);
        checkCallStatementHelper(ifStmt->getElseStatements(), parentProcedure);
    }
    else if (const auto whileStmt = CAST_TO(WhileStatement, recurseStmt)) {
        checkCallStatementHelper(whileStmt->getStatements(), parentProcedure);
    }
}

void SemanticValidator::checkCallStatementHelper(std::vector<std::unique_ptr<Statement>>& statements,
                                                 ProcName parentProcedure) {
    for (const auto& statement : statements) {
        if (const auto callStmt = CAST_TO(CallStatement, statement.get())) {
            procCallMap[parentProcedure].insert(callStmt->procName);
        }
        if (isContainerStatement(statement.get())) {
            recurseCallStatementHelper(statement.get(), parentProcedure);
        }
    }
}

void SemanticValidator::validateNoDuplicateProcedureName() {
    if (procedureNames.size() > std::unordered_set<ProcName>(procedureNames.begin(), procedureNames.end()).size()) {
        throw SemanticErrorException("A program cannot have two procedures with the same name.");
    }
}

void SemanticValidator::validateCalledProceduresExist() {
    std::unordered_set<ProcName> calledProcedures;
    for (const auto& pair : procCallMap) {
        for (const auto& calledProc : pair.second) {
            calledProcedures.insert(calledProc);
        }
    }

    for (const auto& calledProc : calledProcedures) {
        if (std::find(procedureNames.begin(), procedureNames.end(), calledProc) == procedureNames.end()) {
            throw SemanticErrorException("A procedure cannot call a non-existing procedure -> " + calledProc);
        }
    }
}

std::vector<ProcName> SemanticValidator::validateNoCycles() {
    std::deque<ProcName> queue;
    std::unordered_map<ProcName, std::pair<int, std::unordered_set<ProcName>>> nodes;
    std::vector<ProcName> topoOrder;

    for (int i = 0; i < procedureNames.size(); i++) {
        nodes[procedureNames[i]] = std::make_pair(0, std::unordered_set<ProcName>());
    }

    for (const auto& pair : procCallMap) {
        ProcName callerProc = pair.first;
        for (const auto& calledProc : pair.second) {
            nodes[callerProc].first += 1;
            nodes[calledProc].second.insert(callerProc);
        }
    }

    for (const auto& pair : nodes) {
        if (pair.second.first == 0) {
            queue.push_back(pair.first);
        }
    }

    while (queue.size() > 0) {
        ProcName proc = queue.front();
        queue.pop_front();
        for (Ent callerProc : nodes[proc].second) {
            nodes[callerProc].first -= 1;
            if (nodes[callerProc].first == 0) {
                queue.push_back(callerProc);
            }
        }
        topoOrder.push_back(proc);
    }

    if (topoOrder.size() != procedureNames.size()) {
        throw SemanticErrorException("Recursive and cyclic calls are not allowed.");
    }
    else {
        populateCallsTable(topoOrder);
        return topoOrder;
    }
}

void SemanticValidator::populateCallsTable(std::vector<ProcName>& topoOrder) {
    std::unordered_set<ProcName> calleeTSet;
    for (ProcName p : topoOrder) {
        writeApi->setCalls(p, procCallMap[p]);
        for (ProcName j : procCallMap[p]) {
            calleeTSet.insert(j);
            calleeTSet.insert(readApi->getCallsT(j).begin(), readApi->getCallsT(j).end());
        }
        writeApi->setCallsT(p, calleeTSet);
        calleeTSet.clear();
    }
}