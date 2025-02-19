#include "ModifiesUsesHandler.h"

ModifiesUsesHandler::ModifiesUsesHandler(std::shared_ptr<ModifiesUsesStorage> rlStorage,
                                         std::shared_ptr<StmtStorage> stmtStorage) {
    this->rlStorage = rlStorage;
    this->stmtStorage = stmtStorage;
}

std::vector<std::vector<std::string>> ModifiesUsesHandler::handleIntVar(Parameter param1, Parameter param2) {
    std::string paramString1 = param1.getValue();
    std::string paramString2 = param2.getValue();
    std::vector<std::vector<std::string>> res;

    if (rlStorage->exists(stoi(paramString1), paramString2)) {
        res.push_back({paramString1, paramString2});
    }
    return res;
}

std::vector<std::vector<std::string>> ModifiesUsesHandler::handleIntWildcard(Parameter fixedIntParam) {
    std::string fixedIntString = fixedIntParam.getValue();
    std::vector<std::vector<std::string>> res;
    for (Ent entity : rlStorage->getRightItems(stoi(fixedIntString))) {
        res.push_back({fixedIntString, entity});
    }
    return res;
}

std::vector<std::vector<std::string>> ModifiesUsesHandler::handleProcVar(Parameter param1, Parameter param2) {
    std::string paramString1 = param1.getValue();
    std::string paramString2 = param2.getValue();
    std::vector<std::vector<std::string>> res;

    if (rlStorage->exists(paramString1, paramString2)) {
        res.push_back({paramString1, paramString2});
    }
    return res;
}

std::vector<std::vector<std::string>> ModifiesUsesHandler::handleProcWildcard(Parameter fixedProcParam) {
    std::string fixedProc = fixedProcParam.getValue();
    std::vector<std::vector<std::string>> res;
    for (Ent entity : rlStorage->getRightItems(fixedProc)) {
        res.push_back({fixedProc, entity});
    }
    return res;
}

std::vector<std::vector<std::string>> ModifiesUsesHandler::handleStmtSynVar(Parameter param1, Parameter param2) {
    std::string paramString2 = param2.getValue();
    std::vector<std::vector<std::string>> res;

    std::unordered_set<StmtNum>& typedStmtNums = stmtStorage->getStatementNumbers(param1.getTypeString());

    for (StmtNum stmtNum : rlStorage->getLeftItems(paramString2)) {
        if (typedStmtNums.find(stmtNum) != typedStmtNums.end()) {
            std::string stmtNumString = to_string(stmtNum);
            res.push_back({stmtNumString, paramString2});
        }
    }
    return res;
}

std::vector<std::vector<std::string>> ModifiesUsesHandler::handleStmtSynWildcard(Parameter param1) {
    std::vector<std::vector<std::string>> res;

    for (auto typedStmtNum : stmtStorage->getStatementNumbers(param1.getTypeString())) {
        for (Ent entity : rlStorage->getRightItems(typedStmtNum)) {
            std::string stmtNumString = to_string(typedStmtNum);
            res.push_back({stmtNumString, entity});
        }
    }
    return res;
}

std::vector<std::vector<std::string>> ModifiesUsesHandler::handleProcSynVar(Parameter fixedVarParam) {
    std::string fixedVar = fixedVarParam.getValue();
    std::vector<std::vector<std::string>> res;

    for (ProcName proc : rlStorage->getProcs(fixedVar)) {
        res.push_back({proc, fixedVar});
    }
    return res;
}

std::vector<std::vector<std::string>> ModifiesUsesHandler::handleProcSynWildcard() {
    std::vector<std::vector<std::string>> res;
    for (ProcName proc : rlStorage->getAllProcs()) {
        for (Ent entity : rlStorage->getRightItems(proc)) {
            res.push_back({proc, entity});
        }
    }
    return res;
}

std::vector<std::vector<std::string>> ModifiesUsesHandler::handle(Parameter param1, Parameter param2) {
    bool isIntParam1 = param1.isFixedInt();
    bool isStringParam1 = param1.isFixedStringType();
    bool isStringParam2 = param2.isFixedStringType();
    bool isProcParam1 = param1.isProcedureOnly();

    if (isIntParam1) {
        if (isStringParam2) {
            return handleIntVar(param1, param2);
        }
        else {
            return handleIntWildcard(param1);
        }
    }
    else if (isStringParam1) {
        if (isStringParam2) {
            return handleProcVar(param1, param2);
        }
        else {
            return handleProcWildcard(param1);
        }
    }
    else if (isProcParam1) {
        if (isStringParam2) {
            return handleProcSynVar(param2);
        }
        else {
            return handleProcSynWildcard();
        }
    }
    else {
        if (isStringParam2) {
            return handleStmtSynVar(param1, param2);
        }
        else {
            return handleStmtSynWildcard(param1);
        }
    }
    return std::vector<std::vector<std::string>>();
}