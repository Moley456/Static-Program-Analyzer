#include "PKB.h"

void PKB::initializePkb() {
    this->followsStorage = std::make_shared<RelationshipStorage<StmtNum, StmtNum>>();
    this->followsTStorage = std::make_shared<RelationshipStorage<StmtNum, StmtNum>>();
    this->parentStorage = std::make_shared<RelationshipStorage<StmtNum, StmtNum>>();
    this->parentTStorage = std::make_shared<RelationshipStorage<StmtNum, StmtNum>>();
    this->statementStorage = std::make_shared<StmtStorage>();
    this->procedureStorage = std::make_shared<ProcedureStorage>();
    this->procAssignStmtStorage = std::make_shared<ProcedureStorage>();
    this->entityStorage = std::make_shared<EntityStorage<Ent>>();
    this->constantStorage = std::make_shared<EntityStorage<Const>>();
    this->assignPatternStorage = std::make_shared<PatternWithExprStorage>();
    this->ifPatternStorage = std::make_shared<PatternStorage>();
    this->whilePatternStorage = std::make_shared<PatternStorage>();
    this->callStorage = std::make_shared<CallStorage>();
    this->usesStorage = std::make_shared<ModifiesUsesStorage>();
    this->modifiesStorage = std::make_shared<ModifiesUsesStorage>();
    this->cfgStorage = std::make_shared<CFGStorage>();
    this->callsStorage = std::make_shared<RelationshipStorage<Ent, Ent>>();
    this->callsTStorage = std::make_shared<RelationshipStorage<Ent, Ent>>();

    this->relationshipCache = std::make_shared<RelationshipCache>();
    this->patternCache = std::make_shared<PatternCache>();
    this->parameterCache = std::make_shared<ParameterCache>();

    this->followsParentMap[RelationshipType::FOLLOWS] = followsStorage;
    this->followsParentMap[RelationshipType::FOLLOWST] = followsTStorage;
    this->followsParentMap[RelationshipType::PARENT] = parentStorage;
    this->followsParentMap[RelationshipType::PARENTT] = parentTStorage;

    this->modifiesUsesMap[RelationshipType::MODIFIES] = modifiesStorage;
    this->modifiesUsesMap[RelationshipType::USES] = usesStorage;

    this->ifWhilePatternMap[ParameterType::IF] = ifPatternStorage;
    this->ifWhilePatternMap[ParameterType::WHILE] = whilePatternStorage;

    this->callsMap[RelationshipType::CALLS] = callsStorage;
    this->callsMap[RelationshipType::CALLST] = callsTStorage;

    this->affectsHandler = std::make_unique<AffectsHandler>(cfgStorage, statementStorage, procedureStorage,
                                                            modifiesStorage, usesStorage, procAssignStmtStorage);

    this->nextHandler = std::make_unique<NextHandler>(cfgStorage, statementStorage, procedureStorage);

}

void PKB::setFollows(StmtNum followee, StmtNum follower) {
    followsStorage->write(followee, follower);
}

void PKB::setFollowsT(StmtNum followee, std::unordered_set<StmtNum>& followers) {
    followsTStorage->write(followee, followers);
}

void PKB::setParent(StmtNum parent, StmtNum children) {
    parentStorage->write(parent, children);
}

void PKB::setParentT(StmtNum parent, std::unordered_set<StmtNum>& children) {
    parentTStorage->write(parent, children);
}

void PKB::setProcedure(ProcName p, std::unordered_set<StmtNum>& lines) {
    procedureStorage->writeProcedure(p, lines);
}

void PKB::setProcAssignStmt(ProcName p, StmtNum num) {
    procAssignStmtStorage->writeProcedure(p, num);
}

void PKB::setStatement(Stmt s, StmtNum line) {
    statementStorage->writeStatement(s, line);
}

void PKB::setEntity(StmtNum num, std::unordered_set<Ent>& entities) {
    entityStorage->writeEntity(num, entities);
}

void PKB::setConstant(StmtNum num, std::unordered_set<Const>& constants) {
    constantStorage->writeEntity(num, constants);
}

void PKB::setCall(StmtNum callLine, ProcName procedure_being_called) {
    callStorage->writeCallS(callLine, procedure_being_called);
}

void PKB::setCalls(ProcName caller, std::unordered_set<ProcName>& callees) {
    callsStorage->write(caller, callees);
}

void PKB::setCallsT(ProcName caller, std::unordered_set<ProcName>& callees) {
    callsTStorage->write(caller, callees);
}

void PKB::setUsesS(StmtNum num, std::unordered_set<Ent>& entities) {
    usesStorage->write(num, entities);
}

void PKB::setUsesP(ProcName name, std::unordered_set<Ent>& entities) {
    usesStorage->write(name, entities);
}

void PKB::setModifiesS(StmtNum num, std::unordered_set<Ent>& entities) {
    modifiesStorage->write(num, entities);
}

void PKB::setModifiesP(ProcName name, std::unordered_set<Ent>& entities) {
    modifiesStorage->write(name, entities);
}

void PKB::writePattern(std::string lhs, StmtNum num, std::unique_ptr<Expression> pointer) {
    assignPatternStorage->writePattern(lhs, num, std::move(pointer));
}

void PKB::writeIfPattern(StmtNum num, std::unordered_set<Ent>& variables) {
    ifPatternStorage->writePattern(num, variables);
}

void PKB::writeWhilePattern(StmtNum num, std::unordered_set<Ent>& variables) {
    whilePatternStorage->writePattern(num, variables);
}

void PKB::writeCFG(ProcName name,
                   std::unordered_map<StmtNum, std::unordered_map<std::string, std::unordered_set<StmtNum>>>& graph) {
    cfgStorage->writeCFG(name, graph);
}

std::vector<std::vector<std::string>> PKB::findRelationship(shared_ptr<Relationship>& rs) {
    RelationshipType type = rs->getType();
    vector<Parameter> params = rs->getParameters();
    Parameter param1 = params[0];
    Parameter param2 = params[1];

    std::vector<std::vector<std::string>> res = relationshipCache->findResult(rs);
    if (!res.empty()) {
        return res;
    }

    if (followsParentMap.find(type) != followsParentMap.end()) {
        FollowsParentHandler handler(followsParentMap.at(type), statementStorage);
        res = handler.handle(param1, param2);
    }
    else if (modifiesUsesMap.find(type) != modifiesUsesMap.end()) {
        ModifiesUsesHandler handler(modifiesUsesMap.at(type), statementStorage);
        res = handler.handle(param1, param2);
    }
    else if (callsMap.find(type) != callsMap.end()) {
        CallsHandler handler(callsMap.at(type));
        res = handler.handle(param1, param2);
    }
    else if (nextMap.find(type) != nextMap.end()) {
        res = nextHandler->handle(param1, param2, type == RelationshipType::NEXTT);
    }
    else if (affectsMap.find(type) != affectsMap.end()) {
        res = affectsHandler->handle(param1, param2, type == RelationshipType::AFFECTST);
    }
    if (!res.empty()) {
        relationshipCache->addResult(rs, res);
    }
    return res;
}

std::vector<std::string> PKB::findDesignEntities(Parameter& p) {
    std::shared_ptr<Parameter> param = std::make_shared<Parameter>(p);

    std::vector<std::string> res = parameterCache->findResult(param);
    if (!res.empty()) {
        return res;
    }

    ParameterType type = p.getType(); // todo: is this dead code?

    if (p.isProcedureOnly()) {
        std::unordered_set<ProcName>& procs = procedureStorage->getProcNames();
        for (auto proc : procs) {
            res.push_back(proc);
        }
    }
    else if (p.isConstant()) {
        std::unordered_set<Const>& constants = constantStorage->getEntNames();
        for (auto constant : constants) {
            res.push_back(constant);
        }
    }
    else if (p.isVariable()) {
        std::unordered_set<Ent>& vars = entityStorage->getEntNames();
        for (auto var : vars) {
            res.push_back(var);
        }
    }
    else if (p.isStatementRef(p)) {
        std::string typeString = param->getTypeString();
        std::unordered_set<StmtNum>& stmtNums = statementStorage->getStatementNumbers(typeString);
        for (auto stmtNum : stmtNums) {
            res.push_back(to_string(stmtNum));
        }
    }

    if (!res.empty()) {
        parameterCache->addResult(param, res);
    }

    return res;
}

std::vector<std::vector<std::string>> PKB::findPattern(Pattern& p) {
    std::shared_ptr<Pattern> pattern = std::make_shared<Pattern>(p);
    std::vector<std::vector<std::string>> res = patternCache->findResult(pattern);
    if (!res.empty()) {
        return res;
    }

    Parameter patternSyn = *p.getPatternSyn();
    ParameterType patternType = p.getPatternType();

    if (patternSyn.isAssign()) {
        AssignPatternHandler handler(assignPatternStorage);
        res = handler.handle(p);
    }
    else if (ifWhilePatternMap.find(patternType) != ifWhilePatternMap.end()) {
        IfWhilePatternHandler handler(ifWhilePatternMap.at(patternType));
        res = handler.handle(p);
    }

    if (!res.empty()) {
        patternCache->addResult(pattern, res);
    }

    return res;
}

std::vector<std::vector<std::string>> PKB::findAttribute(Parameter& p) {
    AttributeType attrType = p.getAttribute();
    ParameterType paramType = p.getType();

    std::vector<std::vector<std::string>> res;

    if (Parameter::isStatementRef(p)) {
        std::unordered_set<StmtNum>& stmtNums = statementStorage->getStatementNumbers(p.getTypeString());
        if (attrType == AttributeType::PROCNAME) {
            for (auto stmtNum : stmtNums) {
                std::pair<StmtNum, ProcName> numProcPair = callStorage->getCallStmt(stmtNum);
                if (numProcPair.second == AppConstants::PROCEDURE_DOES_NOT_EXIST) {
                    continue;
                }
                res.push_back({std::to_string(stmtNum), numProcPair.second});
            }
        }
        // assumes that QPS is correct in only allowing varName for reads and prints,
        // since reads and prints will only have 1 variable tied to them
        else if (attrType == AttributeType::VARNAME) {
            for (auto stmtNum : stmtNums) {
                Ent var = *entityStorage->getEntities(stmtNum).begin();
                res.push_back({std::to_string(stmtNum), var});
            }
        }
        // currently just returns a pair of duplicated values. Maybe QPS can remove these trivial With clauses.
        else if (attrType == AttributeType::STMTNO) {
            for (auto stmtNum : stmtNums) {
                res.push_back({std::to_string(stmtNum), std::to_string(stmtNum)});
            }
        }
    }
    // currently just returns a pair of duplicated values
    else if (p.isConstant()) {
        std::unordered_set<Const>& consts = constantStorage->getEntNames();
        for (auto constant : consts) {
            res.push_back({constant, constant});
        }
    }
    // currently just returns a pair of duplicated values
    else if (p.isVariable()) {
        std::unordered_set<Ent>& vars = entityStorage->getEntNames();
        for (auto var : vars) {
            res.push_back({var, var});
        }
    }
    // currently just returns a pair of duplicated values
    else {
        std::unordered_set<ProcName>& procs = procedureStorage->getProcNames();
        for (ProcName proc : procs) {
            res.push_back({proc, proc});
        }
    }

    return res;
}

// TODO: Consider refactoring?
std::vector<std::vector<std::string>> PKB::findWith(Comparison& c) {
    Parameter leftParam = c.getLeftParam();
    Parameter rightParam = c.getRightParam();
    bool isLeftParamFixed = leftParam.isFixedInt() || leftParam.isFixedStringType();
    bool isRightParamFixed = rightParam.isFixedInt() || rightParam.isFixedStringType();
    Ent leftParamValue = leftParam.getValue();
    Ent rightParamValue = rightParam.getValue();

    std::vector<std::vector<std::string>> res;

    if (isLeftParamFixed) {
        if (isRightParamFixed) {
            if (leftParamValue == rightParamValue) {
                res.push_back({leftParamValue, rightParamValue});
            }
        }
        else {
            res = findAttribute(rightParam);
            res.erase(std::remove_if(res.begin(), res.end(),
                                     [&](const std::vector<std::string>& item) {
                                         return item[1] != leftParamValue;
                                     }),
                      res.end());
            for (auto& item : res) {
                std::swap(item[0], item[1]);
            }
        }
    }
    else {
        if (isRightParamFixed) {
            res = findAttribute(leftParam);
            res.erase(std::remove_if(res.begin(), res.end(),
                                     [&](const std::vector<std::string>& item) {
                                         return item[1] != rightParamValue;
                                     }),
                      res.end());
        }
        else {
            std::vector<std::vector<std::string>> leftParamRes = findAttribute(leftParam);

            std::vector<std::vector<std::string>> rightParamRes = findAttribute(rightParam);
            std::unordered_map<std::string, std::unordered_set<std::string>> tempMap;
            for (auto pair : leftParamRes) {
                tempMap[pair[1]].insert(pair[0]);
            }
            for (auto pair : rightParamRes) {
                for (auto item : tempMap[pair[1]]) {
                    res.push_back({item, pair[0]});
                }
            }
        }
    }
    return res;
}

bool PKB::checkStatement(Stmt stmt, StmtNum num) {
    return statementStorage->checkStatement(stmt, num);
}

std::unordered_set<StmtNum>& PKB::getProcedureStatementNumbers(ProcName p) {
    return procedureStorage->getProcedureStatementNumbers(p);
}

std::unordered_set<StmtNum>& PKB::getProcAssignStmtNums(ProcName p) {
    return procAssignStmtStorage->getProcedureStatementNumbers(p);
}

std::unordered_set<ProcName>& PKB::getAllProcedureNames() {
    return procedureStorage->getProcNames();
}

std::unordered_set<Ent>& PKB::getUsesS(StmtNum num) {
    return usesStorage->getRightItems(num);
}

std::unordered_set<Ent>& PKB::getUsesP(ProcName name) {
    return usesStorage->getRightItems(name);
}

std::unordered_set<Ent>& PKB::getModifiesS(StmtNum num) {
    return modifiesStorage->getRightItems(num);
}

std::unordered_set<Ent>& PKB::getModifiesP(ProcName name) {
    return modifiesStorage->getRightItems(name);
}

std::unordered_set<StmtNum>& PKB::getIfStatementNumbers() {
    return statementStorage->getStatementNumbers(IF);
}

std::unordered_set<StmtNum>& PKB::getWhileStatementNumbers() {
    return statementStorage->getStatementNumbers(WHILE);
}

std::unordered_set<StmtNum>& PKB::getContainedStatements(StmtNum containerNum) {
    return parentTStorage->getRightItems(containerNum);
}

std::pair<StmtNum, ProcName> PKB::getCallStmt(StmtNum s) {
    return callStorage->getCallStmt(s);
}

std::unordered_set<ProcName>& PKB::getCallsT(ProcName p) {
    return callsTStorage->getRightItems(p);
}

std::unordered_map<StmtNum, std::unordered_map<std::string, std::unordered_set<StmtNum>>>& PKB::getCFG(ProcName name) {
    return cfgStorage->getGraph(name);
}

void PKB::clearCache() {
    relationshipCache->clearCache();
    parameterCache->clearCache();
    patternCache->clearCache();
    affectsHandler->clearCache();
    nextHandler->clearCache();
}