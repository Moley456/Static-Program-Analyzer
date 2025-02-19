#include "Token.h"

Token::Token(TokenType type, std::string value) : type(type), value(value) {}

Token::Token(TokenType type) : type(type), value() {}

bool Token::isType(TokenType tt) {
    return type == tt;
}

bool Token::hasValue(std::string val) {
    return value == val;
}

bool operator==(const Token& lhs, const Token& rhs) {
    return lhs.type == rhs.type && lhs.value == rhs.value;
}