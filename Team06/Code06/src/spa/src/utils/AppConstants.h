#pragma once

#include <stdio.h>

#include <iostream>
#include <string>
#include <vector>

typedef std::string ProcName;
typedef std::string Stmt;
typedef std::string Ent;
typedef std::string Operator;
typedef int StmtNum;
typedef int Const;

class AppConstants {
public:
    inline static const std::string READ = "read";
    inline static const std::string ASSIGN = "assign";
    inline static const std::string PRINT = "print";
    inline static const std::string CALL = "call";
    inline static const std::string IF = "if";
    inline static const std::string WHILE = "while";

    inline static const std::string STMT = "stmt";
    inline static const std::string VARIABLE = "variable";
    inline static const std::string CONSTANT = "constant";
    inline static const std::string PROCEDURE = "procedure";
    inline static const std::string SYNONYM = "synonym";
    inline static const std::string WILDCARD = "wildcard";
    inline static const std::string FIXED_INT = "fixed_int";
    inline static const std::string FIXED_STRING = "fixed_string";

    // relationships
    inline static const std::string FOLLOWS = "Follows";
    inline static const std::string FOLLOWST = "Follows*";
    inline static const std::string PARENT = "Parent";
    inline static const std::string PARENTT = "Parent*";
    inline static const std::string USES = "Uses";
    inline static const std::string MODIFIES = "Modifies";
    inline static const std::string NEXT = "Next";
    inline static const std::string NEXTT = "Next*";
    inline static const std::string CALLS = "Calls";
    inline static const std::string CALLST = "Calls*";
    inline static const std::string AFFECTS = "Affects";
    inline static const std::string AFFECTST = "Affects*";

    // terminals
    inline static const std::string THEN = "then";
    inline static const std::string ELSE = "else";
    inline static const std::string AND = "&&";
    inline static const std::string OR = "||";
    inline static const std::string EQUALS = "==";
    inline static const std::string NOT_EQUALS = "!=";
    inline static const char NOT = '!';
    inline static const char GREATER = '>';
    inline static const char LESS = '<';
    inline static const char PLUS = '+';
    inline static const char MINUS = '-';
    inline static const char MULTIPLY = '*';
    inline static const char DIVIDE = '/';
    inline static const char MODULO = '%';
    inline static const char LEFT_BRACE = '{';
    inline static const char RIGHT_BRACE = '}';
    inline static const char LEFT_PARENTHESIS = '(';
    inline static const char RIGHT_PARENTHESIS = ')';
    inline static const char SEMICOLON = ';';
    inline static const char EQUAL_SIGN = '=';
    inline static const char AMPERSAND = '&';
    inline static const char VERTICAL_BAR = '|';

    // CFG-related
    inline static const std::string PARENTS = "parents";
    inline static const std::string CHILDREN = "children";

    inline static const int NOT_USED_FIELD = -1;
    inline static const std::string PROCEDURE_DOES_NOT_EXIST = "procedure does not exist";
    inline static const int IS_FIND_CHILDREN = true;
};