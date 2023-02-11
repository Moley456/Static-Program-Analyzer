#include "ModifiesStorage.h"

void ModifiesStorage::writeModifiesProcedure(ProcedureName name, std::vector<Ent> entities) {
    procName_ent[name].insert(entities.begin(), entities.end());
}

void ModifiesStorage::writeModifiesStmtnum(StmtNum num, std::vector<Ent> entities) {
    stmtNum_ent[num].insert(entities.begin(), entities.end());
}

std::unordered_set<Ent> ModifiesStorage::getModifiesProcedure(ProcedureName name) {
    // source code does not even contain this procedure
    if (procName_ent.find(name) == procName_ent.end()) {
        std::unordered_set<Ent> emptySet;
        return emptySet;
    }
    return procName_ent[name];
}
std::unordered_set<Ent> ModifiesStorage::getModifiesStmtnum(StmtNum num) {
    // source code does not even contain this statement number
    if (stmtNum_ent.find(num) == stmtNum_ent.end()) {
        std::unordered_set<Ent> emptySet;
        return emptySet;
    }
    return stmtNum_ent[num];
}