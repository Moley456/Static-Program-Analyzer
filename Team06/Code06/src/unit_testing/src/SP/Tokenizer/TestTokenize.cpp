#include "catch.hpp"
#include "../SP/Tokenizer.h"
#include "../SP/SPExceptions.h"

TEST_CASE("Valid source program") {
	std::stringstream strStream;
	Tokenizer testTokenizer;
	std::deque<Token> generatedTokens;
	std::deque<Token> expectedTokens;
	std::string testDirectory = "../../../../../../Tests06/sp/";

	SECTION("Valid names") {
		std::ifstream testFile(testDirectory + "valid1.txt");
		strStream << testFile.rdbuf();

		Token t1(TokenType::NAME, "hello");
		Token t2(TokenType::NAME, "There");
		Token t3(TokenType::NAME, "test123");
		Token t4(TokenType::ENDOFFILE, "End of File");
		expectedTokens = { t1, t2, t3, t4 };

		generatedTokens = testTokenizer.tokenize(strStream);

		REQUIRE(generatedTokens == expectedTokens);
	}

	SECTION("Valid integers") {
		std::ifstream testFile(testDirectory + "valid2.txt");
		strStream << testFile.rdbuf();

		Token t1(TokenType::INTEGER, "123");
		Token t2(TokenType::INTEGER, "0");
		Token t3(TokenType::INTEGER, "340");
		Token t4(TokenType::ENDOFFILE, "End of File");
		expectedTokens = { t1, t2, t3, t4 };

		generatedTokens = testTokenizer.tokenize(strStream);

		REQUIRE(generatedTokens == expectedTokens);
	}

	SECTION("Valid braces and semicolon") {
		std::ifstream testFile(testDirectory + "valid3.txt");
		strStream << testFile.rdbuf();

		Token t1(TokenType::LEFT_BRACE, "{");
		Token t2(TokenType::RIGHT_BRACE, "}");
		Token t3(TokenType::LEFT_PARENTHESIS, "(");
		Token t4(TokenType::RIGHT_PARENTHESIS, ")");
		Token t5(TokenType::SEMICOLON, ";");
		Token t6(TokenType::ENDOFFILE, "End of File");

		expectedTokens = { t1, t2, t3, t4, t5, t6 };

		generatedTokens = testTokenizer.tokenize(strStream);

		REQUIRE(generatedTokens == expectedTokens);
	}

	SECTION("Valid cond_expr operators") {
		std::ifstream testFile(testDirectory + "valid4.txt");
		strStream << testFile.rdbuf();

		Token t1(TokenType::NOT, "!");
		Token t2(TokenType::AND, "&&");
		Token t3(TokenType::OR, "||");
		Token t4(TokenType::ENDOFFILE, "End of File");

		expectedTokens = { t1, t2, t3, t4 };

		generatedTokens = testTokenizer.tokenize(strStream);

		REQUIRE(generatedTokens == expectedTokens);
	}

	SECTION("Valid comparators") {
		std::ifstream testFile(testDirectory + "valid5.txt");
		strStream << testFile.rdbuf();

		Token t1(TokenType::GREATER, ">");
		Token t2(TokenType::LESS, "<");
		Token t3(TokenType::EQUAL, "==");
		Token t4(TokenType::LESS_EQUAL, "<=");
		Token t5(TokenType::GREATER_EQUAL, ">=");
		Token t6(TokenType::NOT_EQUAL, "!=");
		Token t7(TokenType::ENDOFFILE, "End of File");

		expectedTokens = { t1, t2, t3, t4, t5, t6, t7 };

		generatedTokens = testTokenizer.tokenize(strStream);

		REQUIRE(generatedTokens == expectedTokens);
	}

	SECTION("Valid operators") {
		std::ifstream testFile(testDirectory + "valid6.txt");
		strStream << testFile.rdbuf();

		Token t1(TokenType::MODULO, "%");
		Token t2(TokenType::DIVIDE, "/");
		Token t3(TokenType::MULTIPLY, "*");
		Token t4(TokenType::MINUS, "-");
		Token t5(TokenType::PLUS, "+");
		Token t6(TokenType::ENDOFFILE, "End of File");

		expectedTokens = { t1, t2, t3, t4, t5, t6 };

		generatedTokens = testTokenizer.tokenize(strStream);

		REQUIRE(generatedTokens == expectedTokens);
	}

}

TEST_CASE("Invalid source program") {
	std::stringstream strStream;
	Tokenizer testTokenizer;
	std::string testDirectory = "../../../../../../Tests06/sp/";

	SECTION("Invalid Integer") {
		std::ifstream testFile(testDirectory + "invalid1.txt");
		strStream << testFile.rdbuf();

		REQUIRE_THROWS_AS(testTokenizer.tokenize(strStream), SyntaxErrorException);
	}

	SECTION("Invalid integer due to no whitespace between alphanumeric characters") {
		std::ifstream testFile(testDirectory + "invalid2.txt");
		strStream << testFile.rdbuf();

		REQUIRE_THROWS_AS(testTokenizer.tokenize(strStream), SyntaxErrorException);
	}

	/*Upon detecting a '&', another '&' must follow (even though no whitespace between 
	  non-alphanumeric tokens is allowed), the lone '&' is not a valid token.*/ 
	SECTION("Invalid and operator, lone ampersand") {
		std::ifstream testFile(testDirectory + "invalid3.txt");
		strStream << testFile.rdbuf();

		REQUIRE_THROWS_AS(testTokenizer.tokenize(strStream), SyntaxErrorException);
	}

	SECTION("Invalid or operator, lone |") {
		std::ifstream testFile(testDirectory + "invalid4.txt");
		strStream << testFile.rdbuf();

		REQUIRE_THROWS_AS(testTokenizer.tokenize(strStream), SyntaxErrorException);
	}

	SECTION("Invalid tokens") {
		std::ifstream testFile(testDirectory + "invalid5.txt");
		strStream << testFile.rdbuf();

		REQUIRE_THROWS_AS(testTokenizer.tokenize(strStream), SyntaxErrorException);
	}
}