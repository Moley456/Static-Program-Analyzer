#include "catch.hpp"
#include <iostream>
#include "qps/entities/Relationship.h"

TEST_CASE("makeRelationship / empty relationship type string / throws error") {
	string typeInput = "";
	Parameter p1("a", "synonym");
	Parameter p2("b", "synonym");
	vector<Parameter> inputParameters{ p1, p2 };
	REQUIRE_THROWS(Relationship::makeRelationship(typeInput, inputParameters));
}

TEST_CASE("makeRelationship / unknown relationship type string / throws error") {
	string typeInput = "unknown type";
	Parameter p1("a", "synonym");
	Parameter p2("b", "synonym");
	vector<Parameter> inputParameters{ p1, p2 };
	REQUIRE_THROWS(Relationship::makeRelationship(typeInput, inputParameters));
}

TEST_CASE("makeRelationship / follows relationship, with correct params / returns relationship object with correct fields and types") {
	string typeInput = "Follows";
	Parameter p1("a", "synonym");
	Parameter p2("b", "synonym");
	vector<Parameter> inputParameters{p1, p2};
	RelationshipType expectedType = RelationshipType::FOLLOWS;
	vector<Parameter> expectedParameters = inputParameters;

	Relationship output = Relationship::makeRelationship(typeInput, inputParameters);
	CHECK(expectedType == output.type);
	//REQUIRE(expectedParameters == inputParameters);
}

TEST_CASE("makeRelationship / follows relationship, with wrong second param / throws error") {
	string typeInput = "Follows";
	Parameter p1("a", "synonym");
	Parameter p2("\"fixed_string\"", "fixed_string");
	vector<Parameter> inputParameters{ p1, p2 };
	RelationshipType expectedType = RelationshipType::FOLLOWS;

	REQUIRE_THROWS(Relationship::makeRelationship(typeInput, inputParameters));
	//REQUIRE(expectedParameters == inputParameters);
}

TEST_CASE("makeRelationship / follows relationship, with wrong first param / throws error") {
	string typeInput = "Follows";
	Parameter p1("\"fixed_string\"", "fixed_string");
	Parameter p2("a", "synonym");
	vector<Parameter> inputParameters{ p1, p2 };
	RelationshipType expectedType = RelationshipType::FOLLOWS;

	REQUIRE_THROWS(Relationship::makeRelationship(typeInput, inputParameters));
	//REQUIRE(expectedParameters == inputParameters);
}

TEST_CASE("makeRelationship / followsT relationship / return relationship object") {
	string typeInput = "Follows*";
	Parameter p1("a", "synonym");
	Parameter p2("b", "synonym");
	vector<Parameter> inputParameters{ p1, p2 };
	RelationshipType expectedType = RelationshipType::FOLLOWST;

	Relationship output = Relationship::makeRelationship(typeInput, inputParameters);
	CHECK(expectedType == output.type);
}

TEST_CASE("makeRelationship / FollowsT, wrong 2nd param / throws error") {
	string typeInput = "Follows*";
	Parameter p1("a", "synonym");
	Parameter p2("\"entity_ref\"", "fixed_string");
	vector<Parameter> inputParameters{ p1, p2 };
	REQUIRE_THROWS(Relationship::makeRelationship(typeInput, inputParameters));
}

TEST_CASE("makeRelationship / Parent relationship / return relationship object") {
	string typeInput = "Parent";
	Parameter p1("a", "synonym");
	Parameter p2("b", "synonym");
	vector<Parameter> inputParameters{ p1, p2 };
	RelationshipType expectedType = RelationshipType::PARENT;

	Relationship output = Relationship::makeRelationship(typeInput, inputParameters);
	CHECK(expectedType == output.type);
}

TEST_CASE("makeRelationship / ParentT relationship / return relationship object") {
	string typeInput = "Parent*";
	Parameter p1("a", "synonym");
	Parameter p2("b", "synonym");
	vector<Parameter> inputParameters{ p1, p2 };
	RelationshipType expectedType = RelationshipType::PARENTT;

	Relationship output = Relationship::makeRelationship(typeInput, inputParameters);
	CHECK(expectedType == output.type);
}

TEST_CASE("makeRelationship / Uses relationship / return relationship object") {
	string typeInput = "Uses";
	Parameter p1("a", "synonym");
	Parameter p2("b", "synonym");
	vector<Parameter> inputParameters{ p1, p2 };
	RelationshipType expectedType = RelationshipType::USES;

	Relationship output = Relationship::makeRelationship(typeInput, inputParameters);
	CHECK(expectedType == output.type);
}

TEST_CASE("makeRelationship / Modifies relationship / return relationship object") {
	string typeInput = "Modifies";
	Parameter p1("a", "synonym");
	Parameter p2("b", "synonym");
	vector<Parameter> inputParameters{ p1, p2 };
	RelationshipType expectedType = RelationshipType::MODIFIES;

	Relationship output = Relationship::makeRelationship(typeInput, inputParameters);
	CHECK(expectedType == output.type);
}