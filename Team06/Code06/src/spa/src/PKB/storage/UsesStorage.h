#pragma once

#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <string>

typedef std::string Ent;
typedef std::string StmtType;
typedef std::string ProcedureName;
typedef int StmtNum;

class UsesStorage {
public:
    virtual void writeUses(ProcedureName name, StmtType lhs, StmtNum num, Ent ent);
    virtual bool checkUses(StmtNum, Ent); // Ent is either "x" or _

    // Select s such that Uses(s, v)
    virtual std::vector<std::vector<std::string>> getUsesAll();

    // Select s such that Uses(s, "x")
    virtual std::vector<std::vector<std::string>> getUsesAllGivenVariable(std::string rhs);

    // Select pn such that Uses(pn, v)
    virtual std::vector<std::vector<std::string>> getUsesPrintAll();

    // Select pn such that Uses(pn, "x")
    virtual std::vector<std::vector<std::string>> getUsesPrintGivenVariable(std::string rhs);

    // Select a such that Uses(a, v)
    virtual std::vector<std::vector<std::string>> getUsesAssignAll();

    // Select a such that Uses(a, "x")
    virtual std::vector<std::vector<std::string>> getUsesAssignGivenVariable(std::string rhs);

    // Select cs such that Uses(cs, v)
    virtual std::vector<std::vector<std::string>> getUsesContainerAll();

    // Select cs such that Uses(cs, "x")
    virtual std::vector<std::vector<std::string>> getUsesContainerGivenVariable(std::string rhs);

    // Select c such that Uses(c, v)
    virtual std::vector<std::vector<std::string>> getUsesCallAll();

    // Select c such that Uses(c, "x")
    virtual std::vector<std::vector<std::string>> getUsesCallGivenVariable(std::string rhs);

    // Select p such that Uses(p, v)
    virtual std::vector<std::vector<std::string>> getUsesProcedureAll();

    // Select p such that Uses(p, "x")
    virtual std::vector<std::vector<std::string>> getUsesProcedureGivenVariable(std::string rhs);

private:
    std::unordered_map<StmtNum, Ent> print;
    std::unordered_map<StmtNum, std::unordered_set<Ent>> assignment;
    std::unordered_map<StmtNum, std::unordered_set<Ent>> container;
    std::unordered_map<ProcedureName, std::unordered_set<Ent>> procedureVariables;
    std::unordered_map<StmtNum, std::unordered_set<Ent>> call;

//    std::unordered_map<StmtNum, std::unordered_set<StmtNum>> stmtNum_stmtNum;
    std::unordered_map<StmtNum, std::pair<ProcedureName, StmtType>> stmtNum_procName_stmtType;
    std::unordered_map<ProcedureName, std::unordered_map<StmtType, std::unordered_set<StmtNum>>> procName_stmtType_stmtNum;

    //TODO: inverse table if we got time. Milestone 3?

    /*
     * return type that are vectors needs to be of format: vector of {stmtNum, var}
     * assign a; print pn; stmt s (container statement); procedure p; call c (procedure call);
     *
     * Uses(int, int) => True / False
     * Uses(int, concreteVariable) => True / False
     * Uses(int, variable) => vector of vectors of {lhs, stmtNum}
     *
     * Uses(stmtRef, int) => True / False
     * Uses(stmtRef, concreteVariable) => True / False
     * Uses(stmtRef, variable) => vector of vectors of {lhs, stmtNum}
     *
     * Examples:
     * Select a such that Uses(a, "x")
     * Select a such that Uses(a, v)
     * Select v such that Uses(a, v)
     * Select pn such that Uses(pn, "x")
     * Select pn such that Uses(pn, v)
     * Select s such that Uses(s, "x")
     * Select s such that Uses(s, v)
     * Select p such that Uses(p, "x")
     * Select p such that Uses(p, v)
     * Select c such that Uses(c, "x")
     * Select c such that Uses(c, v)
     *
     * Select a such that Uses("procedure1", v) // and other variants ie pn, stmt, etc
     *
     * Select v such that Uses(1, 2) // where Uses(1, 2) is true
     *
     * Invalids:
     * ... Uses(_, _) => semantic error
     */

};
