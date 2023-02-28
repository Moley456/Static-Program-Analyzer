#include "PKB.h"

void PKB::initializePkb() {
    this->followsStorage = std::make_shared<FollowsStorage>();
    this->followsTStorage = std::make_shared<FollowsTStorage>();
    this->parentStorage = std::make_shared<ParentStorage>();
    this->parentTStorage = std::make_shared<ParentTStorage>();
    this->statementStorage = std::make_shared<StmtStorage>();
    this->entityStorage = std::make_shared<EntityStorage>();
    this->procedureStorage = std::make_shared<ProcedureStorage>();
    this->constantStorage = std::make_shared<ConstantStorage>();
    this->patternStorage = std::make_shared<PatternStorage>();
    this->callStorage = std::make_shared<CallStorage>();
    this->usesStorage = std::make_shared<ModifiesUsesStorage>();
    this->modifiesStorage = std::make_shared<ModifiesUsesStorage>();
    this->cfgStorage = std::make_shared<CFGStorage>();
}