#include "catch.hpp"
#include "../../../spa/src/PKB/WritePKB.h"
#include "../../../spa/src/PKB/ReadPKB.h"

TEST_CASE("Support for pattern query of type pattern(\"a\", \"v\")") {
    WritePKB writePkb;
    ReadPKB readPkb;
    PKB pkb;
    PatternStorage pa;
    pkb.patternStorage = &pa;
    writePkb.setInstancePKB(pkb);
    readPkb.setInstancePKB(pkb);

    //line 1: z = a + b / c
    //line 2: z = z * 5

    std::string lhs = "z";
    std::unique_ptr<Expression> line1rhs = writePkb.buildSubtree("a + b / c");
    std::unique_ptr<Expression> line2rhs = writePkb.buildSubtree("z * 5");

    writePkb.writePattern(lhs, 1, std::move(line1rhs));
    writePkb.writePattern(lhs, 2, std::move(line2rhs));

    Parameter param1;
    Parameter param2 = Parameter("z", "fixed_string");
    Pattern pattern1 = Pattern(param1, param2, "a + b / c");
    Pattern pattern2 = Pattern(param1, param2, "z * 5");

    std::vector<std::vector<std::string>> res1 = readPkb.findPattern(pattern1);
    std::vector<std::vector<std::string>> res2 = readPkb.findPattern(pattern2);

    std::vector<std::vector<std::string>> check1 = { {"z", "1"} };
    std::vector<std::vector<std::string>> check2 = { {"z", "2"} };

    std::cout << "COMPLETE";
    REQUIRE(res1 == check1); 
    REQUIRE(res2 == check2);
}


TEST_CASE("Support for pattern query of type pattern(\"a\", _\"v\"_)") {
    WritePKB writePkb;
    ReadPKB readPkb;
    PKB pkb;
    PatternStorage pa;
    pkb.patternStorage = &pa;
    writePkb.setInstancePKB(pkb);
    readPkb.setInstancePKB(pkb);

    //line 1: z = a + b / c
    //line 2: z = z * 5

    std::string lhs = "z";
    std::unique_ptr<Expression> line1rhs = writePkb.buildSubtree("a + b / c");
    std::unique_ptr<Expression> line2rhs = writePkb.buildSubtree("z * 5");

    writePkb.writePattern(lhs, 1, std::move(line1rhs));
    writePkb.writePattern(lhs, 2, std::move(line2rhs));

    Parameter param1;
    Parameter param2 = Parameter("z", "fixed_string");
    Pattern pattern1 = Pattern(param1, param2, "_b / c_");
    Pattern pattern2 = Pattern(param1, param2, "_5_");

    std::vector<std::vector<std::string>> res1 = readPkb.findPattern(pattern1);
    std::vector<std::vector<std::string>> res2 = readPkb.findPattern(pattern2);

    std::vector<std::vector<std::string>> check1 = { {"z", "1"} };
    std::vector<std::vector<std::string>> check2 = { {"z", "2"} };

    std::cout << "COMPLETE";
    REQUIRE(res1 == check1);
    REQUIRE(res2 == check2);
    REQUIRE(readPkb.findPattern(pattern2).size() == 1);
}

/*
TEST_CASE("Support for pattern query of type pattern(\"a\", _") {
    WritePKB writePkb;
    ReadPKB readPkb;
    PKB pkb;
    PatternStorage pa;
    pkb.patternStorage = &pa;
    writePkb.setInstancePKB(pkb);
    readPkb.setInstancePKB(pkb);

    //line 1: z = a + b / c
    //line 2: z = z * 5
    std::string lhs = "z";
    std::unique_ptr<Expression> line1rhs = writePkb.buildSubtree("a + b / c");
    std::unique_ptr<Expression> line2rhs = writePkb.buildSubtree("z * 5");

    writePkb.writePattern(lhs, 1, std::move(line1rhs));
    writePkb.writePattern(lhs, 2, std::move(line2rhs));

    QueryStub qs1;
    qs1.lhs = "z";
    qs1.pattern = "_";

    std::vector<StmtNum> lines_qs1 = readPkb.interpretQuery(qs1);

    bool res = true;
    res = res && lines_qs1.size() == 2;

    std::cout << "COMPLETE";
    REQUIRE(res);
}

TEST_CASE("Support for pattern query of type pattern(_, \"v\")") {
    WritePKB writePkb;
    ReadPKB readPkb;
    PKB pkb;
    PatternStorage pa;
    pkb.patternStorage = &pa;
    writePkb.setInstancePKB(pkb);
    readPkb.setInstancePKB(pkb);

    //line 1: z = a + b / c
    //line 2: z = z * 5

    std::string lhs = "z";
    std::unique_ptr<Expression> line1rhs = writePkb.buildSubtree("a + b / c");
    std::unique_ptr<Expression> line2rhs = writePkb.buildSubtree("z * 5");

    writePkb.writePattern(lhs, 1, std::move(line1rhs));
    writePkb.writePattern(lhs, 2, std::move(line2rhs));

    QueryStub qs1;
    qs1.lhs = "_";
    qs1.pattern = "a + b / c";

    QueryStub qs2;
    qs2.lhs = "_";
    qs2.pattern = "z * 5";


    QueryStub qs3;
    qs3.lhs = "_";
    qs3.pattern = "z";

    std::vector<StmtNum> lines_qs1 = readPkb.interpretQuery(qs1);
    std::vector<StmtNum> lines_qs2 = readPkb.interpretQuery(qs2);

    bool res = true;
    res = res && lines_qs1.size() == 1;
    res = res && lines_qs2.size() == 1;
    res = res && readPkb.interpretQuery(qs3).size() == 0;

    std::cout << "COMPLETE";
    REQUIRE(res);
}

TEST_CASE("Support for Select v pattern a (v, _)\'") {
    WritePKB writePkb;
    ReadPKB readPkb;
    PKB pkb;
    PatternStorage pa;
    pkb.patternStorage = &pa;
    writePkb.setInstancePKB(pkb);
    readPkb.setInstancePKB(pkb);

    //line 1: z = a + b / c
    //line 2: z = z * 5

    std::string lhs = "z";
    std::unique_ptr<Expression> line1rhs = writePkb.buildSubtree("a + b / c");
    std::unique_ptr<Expression> line2rhs = writePkb.buildSubtree("z * 5");

    writePkb.writePattern(lhs, 1, std::move(line1rhs));
    writePkb.writePattern(lhs, 2, std::move(line2rhs));

    std::vector<std::vector<std::string>> result = readPkb.getLHSAndStmtNum();

    for (std::vector v : result) {
        std::cout << v[0] << " " << v[1] << "\n";
    }

    bool res = true;
    std::cout << "COMPLETE";
    REQUIRE(res);
}

//TEST_CASE("Support for pattern's inorder traversal") {
//    WritePKB writePkb;
//    ReadPKB readPkb;
//    PKB pkb;
//    PatternStorage pa;
//    pkb.patternStorage = &pa;
//    writePkb.setInstancePKB(pkb);
//    readPkb.setInstancePKB(pkb);
//
//    //line 1: z = a + b / c
//    //line 2: z = z * 5
//
//    std::string lhs = "z";
//    std::unique_ptr<Expression> line1rhs = writePkb.buildSubtree("a + b / c");
//    std::unique_ptr<Expression> line2rhs = writePkb.buildSubtree("z * 5");
//    std::unique_ptr<Expression> line3rhs = writePkb.buildSubtree("x * 5");
//
//    writePkb.writePattern(lhs, 1, std::move(line1rhs));
//    writePkb.writePattern(lhs, 2, std::move(line2rhs));
//    writePkb.writePattern(lhs, 3, std::move(line3rhs));
//
//    std::vector<StmtNum> lines_qs1 = readPkb.interpretQuery(qs1);
//    std::vector<StmtNum> lines_qs2 = readPkb.interpretQuery(qs2);
//
//    bool res = true;
//    res = res && lines_qs1.size() == 1;
//    res = res && lines_qs2.size() == 0;
//
//    std::cout << "COMPLETE";
//    REQUIRE(res);
//}
*/


