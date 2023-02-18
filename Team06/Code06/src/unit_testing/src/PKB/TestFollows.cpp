#include "catch.hpp"
#include "../../../spa/src/PKB/WritePKB.h"
#include "../../../spa/src/PKB/ReadPKB.h"


TEST_CASE("Checks that write and read works for FollowsStorage") {

    FollowsStorage fs;

    fs.write(1, 2);
    bool res = fs.exists(1, 2);
    REQUIRE(res);
}

TEST_CASE("Checks that a non-existent follows relationship is detected in FollowsStorage") {

    FollowsStorage fs;

    fs.write(1, 2);
    bool res = fs.exists(1, 3);
    REQUIRE(res == false);
}

TEST_CASE("Checks FollowsStorage such that follower is correct given a followee") {

    FollowsStorage fs;

    fs.write(1, 2);
    std::unordered_set<StmtNum> res = fs.getRightWildcard(1);
    std::unordered_set<StmtNum> check = { 2 };
    REQUIRE(res == check);
}

TEST_CASE("Checks FollowsStorage such that followee is correct given a follower") {

    FollowsStorage fs;

    fs.write(1, 2);
    std::unordered_set<StmtNum> res = fs.getLeftWildcard(2);
    std::unordered_set<StmtNum> check = { 1 };
    REQUIRE(res == check);
}

TEST_CASE("Checks FollowsStorage such that given a followee, if it does not have a certain follower, an empty vector is returned") {

    FollowsStorage fs;

    fs.write(1, 2);
    std::unordered_set<StmtNum> res = fs.getRightWildcard(3);
    std::unordered_set<StmtNum> check;
    REQUIRE(res == check);
}

TEST_CASE("Checks FollowsStorage such that given a follower, if it does not have a certain followee, an empty vector is returned") {

    FollowsStorage fs;

    fs.write(1, 2);
    std::unordered_set<StmtNum> res = fs.getLeftWildcard(3);
    std::unordered_set<StmtNum> check;
    REQUIRE(res == check);
}

TEST_CASE("Checks that writing and reading from ReadPKB works for Follows") {

    WritePKB writePkb;
    ReadPKB readPkb;
    PKB pkb;
    pkb.initializePkb();
    writePkb.setInstancePKB(pkb);
    readPkb.setInstancePKB(pkb);

    writePkb.setFollows(1, 2);
    Parameter param1 = Parameter("1", "fixed_int");
    Parameter param2 = Parameter("2", "fixed_int");
    std::vector<Parameter> params;
    params.push_back(param1);
    params.push_back(param2);
    Relationship rs = Relationship::makeRelationship("Follows", params);

    std::vector<std::vector<std::string>> check = { {"1", "2"} };
    std::vector<std::vector<std::string>> res = readPkb.findRelationship(rs);
    REQUIRE(check==res);
}

TEST_CASE("Checks that a non-existent Follows relationship returns an empty vector from ReadPKB") {

    WritePKB writePkb;
    ReadPKB readPkb;
    PKB pkb;
    pkb.initializePkb();
    writePkb.setInstancePKB(pkb);
    readPkb.setInstancePKB(pkb);

    writePkb.setFollows(1, 2);
    Parameter param1 = Parameter("1", "fixed_int");
    Parameter param2 = Parameter("3", "fixed_int");
    std::vector<Parameter> params;
    params.push_back(param1);
    params.push_back(param2);
    Relationship rs = Relationship::makeRelationship("Follows", params);

    std::vector<std::vector<std::string>> check;
    std::vector<std::vector<std::string>> res = readPkb.findRelationship(rs);
    REQUIRE(check == res);
}

TEST_CASE("Checks that given a followee and a synonym, ReadPKB returns relevant followee-follower pairs") {

    WritePKB writePkb;
    ReadPKB readPkb;
    PKB pkb;
    pkb.initializePkb();
    writePkb.setInstancePKB(pkb);
    readPkb.setInstancePKB(pkb);

    writePkb.setFollows(1, 2);
    writePkb.setStatement("assign", 2);

    Parameter param1 = Parameter("1", "fixed_int");
    Parameter param2 = Parameter("a", "assign");
    std::vector<Parameter> params;
    params.push_back(param1);
    params.push_back(param2);
    Relationship rs = Relationship::makeRelationship("Follows", params);

    std::vector<std::vector<std::string>> check = { {"1", "2"} };
    std::vector<std::vector<std::string>> res = readPkb.findRelationship(rs);
    REQUIRE(check == res);
}

TEST_CASE("Checks that given a followee and a wildcard, ReadPKB returns all followee-follower pairs") {

    WritePKB writePkb;
    ReadPKB readPkb;
    PKB pkb;
    pkb.initializePkb();
    writePkb.setInstancePKB(pkb);
    readPkb.setInstancePKB(pkb);

    writePkb.setFollows(1, 2);
    Parameter param1 = Parameter("1", "fixed_int");
    Parameter param2 = Parameter("_", "wildcard");
    std::vector<Parameter> params;
    params.push_back(param1);
    params.push_back(param2);
    Relationship rs = Relationship::makeRelationship("Follows", params);

    std::vector<std::vector<std::string>> check = { {"1", "2"} };
    std::vector<std::vector<std::string>> res = readPkb.findRelationship(rs);
    REQUIRE(check == res);
}

TEST_CASE("Checks that given a synonym and a follower, ReadPKB returns relevant followee-follower pairs") {

    WritePKB writePkb;
    ReadPKB readPkb;
    PKB pkb;
    pkb.initializePkb();
    writePkb.setInstancePKB(pkb);
    readPkb.setInstancePKB(pkb);

    writePkb.setFollows(1, 2);
    writePkb.setStatement("while", 1);

    Parameter param1 = Parameter("w", "while");
    Parameter param2 = Parameter("2", "fixed_int");
    std::vector<Parameter> params;
    params.push_back(param1);
    params.push_back(param2);
    Relationship rs = Relationship::makeRelationship("Follows", params);

    std::vector<std::vector<std::string>> check = { {"1", "2"} };
    std::vector<std::vector<std::string>> res = readPkb.findRelationship(rs);
    REQUIRE(check == res);
}

TEST_CASE("Checks that given a synonym and a synonym, ReadPKB returns relevant followee-follower pairs") {

    WritePKB writePkb;
    ReadPKB readPkb;
    PKB pkb;
    FollowsStorage fs;
    pkb.initializePkb();
    writePkb.setInstancePKB(pkb);
    readPkb.setInstancePKB(pkb);

    writePkb.setFollows(1, 2);
    writePkb.setStatement("while", 1);
    writePkb.setStatement("if", 2);

    Parameter param1 = Parameter("w", "while");
    Parameter param2 = Parameter("if", "if");
    std::vector<Parameter> params;
    params.push_back(param1);
    params.push_back(param2);
    Relationship rs = Relationship::makeRelationship("Follows", params);

    std::vector<std::vector<std::string>> check = { {"1", "2"} };
    std::vector<std::vector<std::string>> res = readPkb.findRelationship(rs);
    REQUIRE(check == res);
}

TEST_CASE("Checks that given a synonym and a wildcard, ReadPKB returns relevant followee-follower pairs") {

    WritePKB writePkb;
    ReadPKB readPkb;
    PKB pkb;
    FollowsStorage fs;
    pkb.initializePkb();
    writePkb.setInstancePKB(pkb);
    readPkb.setInstancePKB(pkb);

    writePkb.setFollows(1, 2);
    writePkb.setStatement("while", 1);
    writePkb.setStatement("assign", 2);

    Parameter param1 = Parameter("w", "while");
    Parameter param2 = Parameter("_", "wildcard");
    std::vector<Parameter> params;
    params.push_back(param1);
    params.push_back(param2);
    Relationship rs = Relationship::makeRelationship("Follows", params);

    std::vector<std::vector<std::string>> check = { {"1", "2"} };
    std::vector<std::vector<std::string>> res = readPkb.findRelationship(rs);
    REQUIRE(check == res);
}


TEST_CASE("Checks that given a wildcard and a follower, ReadPKB returns relevant followee-follower pairs") {

    WritePKB writePkb;
    ReadPKB readPkb;
    PKB pkb;
    FollowsStorage fs;
    pkb.initializePkb();
    writePkb.setInstancePKB(pkb);
    readPkb.setInstancePKB(pkb);

    writePkb.setFollows(1, 2);

    Parameter param1 = Parameter("_", "wildcard");
    Parameter param2 = Parameter("2", "fixed_int");
    std::vector<Parameter> params;
    params.push_back(param1);
    params.push_back(param2);
    Relationship rs = Relationship::makeRelationship("Follows", params);

    std::vector<std::vector<std::string>> check = { {"1", "2"} };
    std::vector<std::vector<std::string>> res = readPkb.findRelationship(rs);
    REQUIRE(check == res);
}

TEST_CASE("Checks that given a wildcard and a synonym, ReadPKB returns relevant followee-follower pairs") {

    WritePKB writePkb;
    ReadPKB readPkb;
    PKB pkb;
    FollowsStorage fs;
    pkb.initializePkb();
    writePkb.setInstancePKB(pkb);
    readPkb.setInstancePKB(pkb);

    writePkb.setFollows(1, 2);
    writePkb.setStatement("print", 2);

    Parameter param1 = Parameter("_", "wildcard");
    Parameter param2 = Parameter("p", "print");
    std::vector<Parameter> params;
    params.push_back(param1);
    params.push_back(param2);
    Relationship rs = Relationship::makeRelationship("Follows", params);

    std::vector<std::vector<std::string>> check = { {"1", "2"} };
    std::vector<std::vector<std::string>> res = readPkb.findRelationship(rs);
    REQUIRE(check == res);
}

TEST_CASE("Checks that given a wildcard and a wildcard, ReadPKB returns relevant followee-follower pairs") {

    WritePKB writePkb;
    ReadPKB readPkb;
    PKB pkb;
    FollowsStorage fs;
    pkb.initializePkb();
    writePkb.setInstancePKB(pkb);
    readPkb.setInstancePKB(pkb);

    writePkb.setFollows(1, 2);

    Parameter param1 = Parameter("_", "wildcard");
    Parameter param2 = Parameter("_", "wildcard");
    std::vector<Parameter> params;
    params.push_back(param1);
    params.push_back(param2);
    Relationship rs = Relationship::makeRelationship("Follows", params);

    std::vector<std::vector<std::string>> check = { {"1", "2"} };
    std::vector<std::vector<std::string>> res = readPkb.findRelationship(rs);
    REQUIRE(check == res);
}

TEST_CASE("Checks that given a followee, if it does not have a certain follower, readPKB returns an empty vector") {

    WritePKB writePkb;
    ReadPKB readPkb;
    PKB pkb;
    FollowsStorage fs;
    pkb.initializePkb();
    writePkb.setInstancePKB(pkb);
    readPkb.setInstancePKB(pkb);

    writePkb.setFollows(1, 2);
    Parameter param1 = Parameter("2", "fixed_int");
    Parameter param2 = Parameter("_", "wildcard");
    std::vector<Parameter> params;
    params.push_back(param1);
    params.push_back(param2);
    Relationship rs = Relationship::makeRelationship("Follows", params);

    std::vector<std::vector<std::string>> check;
    std::vector<std::vector<std::string>> res = readPkb.findRelationship(rs);
    REQUIRE(check == res);
}

TEST_CASE("Checks that given a follower, if it does not have a certain followee, readPKB returns an empty vector") {

    WritePKB writePkb;
    ReadPKB readPkb;
    PKB pkb;
    FollowsStorage fs;
    pkb.initializePkb();
    writePkb.setInstancePKB(pkb);
    readPkb.setInstancePKB(pkb);

    writePkb.setFollows(1, 2);
    Parameter param1 = Parameter("_", "wildcard");
    Parameter param2 = Parameter("3", "fixed_int");
    std::vector<Parameter> params;
    params.push_back(param1);
    params.push_back(param2);
    Relationship rs = Relationship::makeRelationship("Follows", params);

    std::vector<std::vector<std::string>> check;
    std::vector<std::vector<std::string>> res = readPkb.findRelationship(rs);
    REQUIRE(check == res);
}

TEST_CASE("Checks that PKB pointer in WritePKB and ReadPKB is set to first pkb instance and not overwritten") {

    WritePKB writePkb;
    ReadPKB readPkb;
    PKB pkb1;
    FollowsStorage fs;
    pkb1.initializePkb();
    writePkb.setInstancePKB(pkb1);
    readPkb.setInstancePKB(pkb1);

    writePkb.setFollows(1, 2);

    PKB pkb2;
    FollowsStorage fs2;
    pkb2.initializePkb();
    writePkb.setInstancePKB(pkb2);

    Parameter param1 = Parameter("1", "fixed_int");
    Parameter param2 = Parameter("2", "fixed_int");
    std::vector<Parameter> params;
    params.push_back(param1);
    params.push_back(param2);
    Relationship rs = Relationship::makeRelationship("Follows", params);

    std::vector<std::vector<std::string>> check = { {"1", "2"} };
    std::vector<std::vector<std::string>> res = readPkb.findRelationship(rs);
    REQUIRE(check == res);

    readPkb.setInstancePKB(pkb2);

    res = readPkb.findRelationship(rs);
    REQUIRE(check == res);
}


TEST_CASE("FollowsStorage: write(StmtNum followee, StmtNum follower)") {
    FollowsStorage fs;
    fs.write(1, 2);
    fs.write(2, 3);

    SECTION("exists(StmtNum followee, StmtNum follower)") {
        REQUIRE(fs.exists(1, 2));
        REQUIRE(!fs.exists(1, 3));
        REQUIRE(!fs.exists(3, 4));
    }
}
