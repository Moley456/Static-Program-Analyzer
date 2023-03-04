#include "QPS/entities/AffectsRelationship.h"
#include "QPS/entities/AffectsTRelationship.h"
#include "QPS/entities/CallsRelationship.h"
#include "QPS/entities/CallsTRelationship.h"
#include "QPS/entities/FollowsRelationship.h"
#include "QPS/entities/FollowsTRelationship.h"
#include "QPS/entities/ModifiesRelationship.h"
#include "QPS/entities/NextRelationship.h"
#include "QPS/entities/NextTRelationship.h"
#include "QPS/entities/ParentRelationship.h"
#include "QPS/entities/ParentTRelationship.h"
#include "QPS/entities/Relationship.h"
#include "QPS/entities/UsesRelationship.h"
#include "catch.hpp"

TEST_CASE("makeRelationship / empty relationship type string / throws error") {

  string typeInput = "";
  Parameter p1("a", AppConstants::SYNONYM);
  Parameter p2("b", AppConstants::SYNONYM);
  vector<Parameter> inputParameters{p1, p2};
  REQUIRE_THROWS(Relationship::makeRelationship(typeInput, inputParameters));
}

TEST_CASE(
    "makeRelationship / unknown relationship type string / throws error") {

  string typeInput = "unknown type";
  Parameter p1("a", AppConstants::SYNONYM);
  Parameter p2("b", AppConstants::SYNONYM);
  vector<Parameter> inputParameters{p1, p2};
  REQUIRE_THROWS(Relationship::makeRelationship(typeInput, inputParameters));
}

TEST_CASE("makeRelationship / follows relationship, with correct params / "
          "returns relationship object with correct fields and types") {

  string typeInput = AppConstants::FOLLOWS;
  Parameter p1("a", AppConstants::SYNONYM);
  Parameter p2("1", AppConstants::FIXED_INT);
  Parameter p3("_", AppConstants::WILDCARD);
  vector<Parameter> inputParameters{p1, p2};
  vector<Parameter> inputParameters2{p2, p3};
  vector<Parameter> inputParameters3{p3, p1};

  shared_ptr<Relationship> output =
      Relationship::makeRelationship(typeInput, inputParameters);
  FollowsRelationship expected(inputParameters);
  CHECK(expected == *output);
  shared_ptr<Relationship> output2 =
      Relationship::makeRelationship(typeInput, inputParameters2);
  FollowsRelationship expected2(inputParameters2);
  CHECK(expected2 == *output2);
  shared_ptr<Relationship> output3 =
      Relationship::makeRelationship(typeInput, inputParameters3);
  FollowsRelationship expected3(inputParameters3);
  CHECK(expected3 == *output3);
}

TEST_CASE("makeRelationship / follows relationship, with wrong second param / "
          "throws error") {

  string typeInput = AppConstants::FOLLOWS;
  Parameter p1("a", AppConstants::SYNONYM);
  Parameter p2(AppConstants::FIXED_STRING, AppConstants::FIXED_STRING);
  vector<Parameter> inputParameters{p1, p2};

  REQUIRE_THROWS(Relationship::makeRelationship(typeInput, inputParameters));
}

TEST_CASE("makeRelationship / follows relationship, with wrong first param / "
          "throws error") {

  string typeInput = AppConstants::FOLLOWS;
  Parameter p1(AppConstants::FIXED_STRING, AppConstants::FIXED_STRING);
  Parameter p2("a", AppConstants::SYNONYM);
  vector<Parameter> inputParameters{p1, p2};

  REQUIRE_THROWS(Relationship::makeRelationship(typeInput, inputParameters));
}

TEST_CASE("makeRelationship / follows relationship, more than 2 parameter / "
          "throws error") {

  string typeInput = AppConstants::FOLLOWS;
  Parameter p1("a", AppConstants::SYNONYM);
  Parameter p2("b", AppConstants::SYNONYM);
  Parameter p3("c", AppConstants::SYNONYM);
  vector<Parameter> inputParameters{p1, p2, p3};

  REQUIRE_THROWS(Relationship::makeRelationship(typeInput, inputParameters));
}

TEST_CASE("makeRelationship / follows relationship, less than 2 parameter / "
          "throws error") {

  string typeInput = AppConstants::FOLLOWS;
  Parameter p1("a", AppConstants::SYNONYM);
  vector<Parameter> inputParameters{p1};

  REQUIRE_THROWS(Relationship::makeRelationship(typeInput, inputParameters));
}

TEST_CASE(
    "makeRelationship / FollowsT relationship / return relationship object") {

  string typeInput = AppConstants::FOLLOWST;
  Parameter p1("a", AppConstants::SYNONYM);
  Parameter p2("1", AppConstants::FIXED_INT);
  Parameter p3("_", AppConstants::WILDCARD);
  vector<Parameter> inputParameters{p1, p2};
  vector<Parameter> inputParameters2{p2, p3};
  vector<Parameter> inputParameters3{p3, p1};

  shared_ptr<Relationship> output =
      Relationship::makeRelationship(typeInput, inputParameters);
  FollowsTRelationship expected(inputParameters);
  CHECK(expected == *output);
  shared_ptr<Relationship> output2 =
      Relationship::makeRelationship(typeInput, inputParameters2);
  FollowsTRelationship expected2(inputParameters2);
  CHECK(expected2 == *output2);
  shared_ptr<Relationship> output3 =
      Relationship::makeRelationship(typeInput, inputParameters3);
  FollowsTRelationship expected3(inputParameters3);
  CHECK(expected3 == *output3);
}

TEST_CASE("makeRelationship / FollowsT, wrong 2nd param / throws error") {

  string typeInput = AppConstants::FOLLOWST;
  Parameter p1("a", AppConstants::SYNONYM);
  Parameter p2("entity_ref", AppConstants::FIXED_STRING);
  vector<Parameter> inputParameters{p1, p2};
  REQUIRE_THROWS(Relationship::makeRelationship(typeInput, inputParameters));
}

TEST_CASE("makeRelationship / FollowsT, wrong 1st param / throws error") {

  string typeInput = AppConstants::FOLLOWST;
  Parameter p1("entity_ref", AppConstants::FIXED_STRING);
  Parameter p2("a", AppConstants::SYNONYM);
  vector<Parameter> inputParameters{p1, p2};
  REQUIRE_THROWS(Relationship::makeRelationship(typeInput, inputParameters));
}

TEST_CASE("makeRelationship / FollowsT relationship, more than 2 parameter / "
          "throws error") {

  string typeInput = AppConstants::FOLLOWST;
  Parameter p1("a", AppConstants::SYNONYM);
  Parameter p2("b", AppConstants::SYNONYM);
  Parameter p3("c", AppConstants::SYNONYM);
  vector<Parameter> inputParameters{p1, p2, p3};

  REQUIRE_THROWS(Relationship::makeRelationship(typeInput, inputParameters));
}

TEST_CASE("makeRelationship / FollowsT relationship, less than 2 parameter / "
          "throws error") {

  string typeInput = AppConstants::FOLLOWST;
  Parameter p1("a", AppConstants::SYNONYM);
  vector<Parameter> inputParameters{p1};

  REQUIRE_THROWS(Relationship::makeRelationship(typeInput, inputParameters));
}

TEST_CASE(
    "makeRelationship / Parent relationship / return relationship object") {

  string typeInput = AppConstants::PARENT;
  Parameter p1("a", AppConstants::SYNONYM);
  Parameter p2("1", AppConstants::FIXED_INT);
  Parameter p3("_", AppConstants::WILDCARD);
  vector<Parameter> inputParameters{p1, p2};
  vector<Parameter> inputParameters2{p2, p3};
  vector<Parameter> inputParameters3{p3, p1};

  shared_ptr<Relationship> output =
      Relationship::makeRelationship(typeInput, inputParameters);
  ParentRelationship expected(inputParameters);
  CHECK(expected == *output);
  shared_ptr<Relationship> output2 =
      Relationship::makeRelationship(typeInput, inputParameters2);
  ParentRelationship expected2(inputParameters2);
  CHECK(expected2 == *output2);
  shared_ptr<Relationship> output3 =
      Relationship::makeRelationship(typeInput, inputParameters3);
  ParentRelationship expected3(inputParameters3);
  CHECK(expected3 == *output3);
}

TEST_CASE("makeRelationship / Parent, wrong 2nd param / throws error") {

  string typeInput = AppConstants::PARENT;
  Parameter p1("a", AppConstants::SYNONYM);
  Parameter p2("entity_ref", AppConstants::FIXED_STRING);
  vector<Parameter> inputParameters{p1, p2};
  REQUIRE_THROWS(Relationship::makeRelationship(typeInput, inputParameters));
}

TEST_CASE("makeRelationship / Parent, wrong 1st param / throws error") {

  string typeInput = AppConstants::PARENT;
  Parameter p1("entity_ref", AppConstants::FIXED_STRING);
  Parameter p2("a", AppConstants::SYNONYM);
  vector<Parameter> inputParameters{p1, p2};
  REQUIRE_THROWS(Relationship::makeRelationship(typeInput, inputParameters));
}

TEST_CASE("makeRelationship / Parent relationship, more than 2 parameter / "
          "throws error") {

  string typeInput = AppConstants::PARENT;
  Parameter p1("a", AppConstants::SYNONYM);
  Parameter p2("b", AppConstants::SYNONYM);
  Parameter p3("c", AppConstants::SYNONYM);
  vector<Parameter> inputParameters{p1, p2, p3};

  REQUIRE_THROWS(Relationship::makeRelationship(typeInput, inputParameters));
}

TEST_CASE("makeRelationship / Parent relationship, less than 2 parameter / "
          "throws error") {

  string typeInput = AppConstants::PARENT;
  Parameter p1("a", AppConstants::SYNONYM);
  vector<Parameter> inputParameters{p1};

  REQUIRE_THROWS(Relationship::makeRelationship(typeInput, inputParameters));
}

TEST_CASE(
    "makeRelationship / ParentT relationship / return relationship object") {

  string typeInput = AppConstants::PARENTT;
  Parameter p1("a", AppConstants::SYNONYM);
  Parameter p2("1", AppConstants::FIXED_INT);
  Parameter p3("_", AppConstants::WILDCARD);
  vector<Parameter> inputParameters{p1, p2};
  vector<Parameter> inputParameters2{p2, p3};
  vector<Parameter> inputParameters3{p3, p1};

  shared_ptr<Relationship> output =
      Relationship::makeRelationship(typeInput, inputParameters);
  ParentTRelationship expected(inputParameters);
  CHECK(expected == *output);
  shared_ptr<Relationship> output2 =
      Relationship::makeRelationship(typeInput, inputParameters2);
  ParentTRelationship expected2(inputParameters2);
  CHECK(expected2 == *output2);
  shared_ptr<Relationship> output3 =
      Relationship::makeRelationship(typeInput, inputParameters3);
  ParentTRelationship expected3(inputParameters3);
  CHECK(expected3 == *output3);
}

TEST_CASE("makeRelationship / ParentT, wrong 2nd param / throws error") {

  string typeInput = AppConstants::PARENTT;
  Parameter p1("a", AppConstants::SYNONYM);
  Parameter p2("entity_ref", AppConstants::FIXED_STRING);
  vector<Parameter> inputParameters{p1, p2};
  REQUIRE_THROWS(Relationship::makeRelationship(typeInput, inputParameters));
}

TEST_CASE("makeRelationship / ParentT, wrong 1st param / throws error") {

  string typeInput = AppConstants::PARENTT;
  Parameter p1("entity_ref", AppConstants::FIXED_STRING);
  Parameter p2("a", AppConstants::SYNONYM);
  vector<Parameter> inputParameters{p1, p2};
  REQUIRE_THROWS(Relationship::makeRelationship(typeInput, inputParameters));
}

TEST_CASE("makeRelationship / ParentT relationship, more than 2 parameter / "
          "throws error") {

  string typeInput = AppConstants::PARENTT;
  Parameter p1("a", AppConstants::SYNONYM);
  Parameter p2("b", AppConstants::SYNONYM);
  Parameter p3("c", AppConstants::SYNONYM);
  vector<Parameter> inputParameters{p1, p2, p3};

  REQUIRE_THROWS(Relationship::makeRelationship(typeInput, inputParameters));
}

TEST_CASE("makeRelationship / ParentT relationship, less than 2 parameter / "
          "throws error") {

  string typeInput = AppConstants::PARENTT;
  Parameter p1("a", AppConstants::SYNONYM);
  vector<Parameter> inputParameters{p1};

  REQUIRE_THROWS(Relationship::makeRelationship(typeInput, inputParameters));
}

TEST_CASE("makeRelationship / Uses relationship / return relationship object") {

  string typeInput = AppConstants::USES;
  Parameter p1("a", AppConstants::SYNONYM);
  Parameter p2("_", AppConstants::WILDCARD);
  Parameter p3("ent_ref", AppConstants::FIXED_STRING);
  Parameter p4("1", AppConstants::FIXED_INT);
  vector<Parameter> inputParameters{p1, p2};
  vector<Parameter> inputParameters2{p4, p3};
  vector<Parameter> inputParameters3{p2, p3};
  RelationshipType expectedType = RelationshipType::USES;

  shared_ptr<Relationship> output =
      Relationship::makeRelationship(typeInput, inputParameters);
  UsesRelationship expected(inputParameters);
  CHECK(expected == *output);
  shared_ptr<Relationship> output2 =
      Relationship::makeRelationship(typeInput, inputParameters2);
  UsesRelationship expected2(inputParameters2);
  CHECK(expected2 == *output2);
  shared_ptr<Relationship> output3 =
      Relationship::makeRelationship(typeInput, inputParameters3);
  UsesRelationship expected3(inputParameters3);
  CHECK(expected3 == *output3);
}

TEST_CASE("makeRelationship / Uses, wrong 1st param / throws error") {

  string typeInput = AppConstants::USES;
  Parameter p1("ent_ref", AppConstants::VARIABLE);
  Parameter p2("a", AppConstants::SYNONYM);
  vector<Parameter> inputParameters{p1, p2};
  REQUIRE_THROWS(Relationship::makeRelationship(typeInput, inputParameters));
}

TEST_CASE("makeRelationship / Uses, wrong 2nd param / throws error") {

  string typeInput = AppConstants::USES;
  Parameter p1("a", AppConstants::SYNONYM);
  Parameter p2("stmt_ref", AppConstants::FIXED_INT);
  vector<Parameter> inputParameters{p1, p2};
  REQUIRE_THROWS(Relationship::makeRelationship(typeInput, inputParameters));
}

TEST_CASE("makeRelationship / Uses relationship, more than 2 parameter / "
          "throws error") {

  string typeInput = AppConstants::USES;
  Parameter p1("a", AppConstants::SYNONYM);
  Parameter p2("b", AppConstants::SYNONYM);
  Parameter p3("c", AppConstants::SYNONYM);
  vector<Parameter> inputParameters{p1, p2, p3};

  REQUIRE_THROWS(Relationship::makeRelationship(typeInput, inputParameters));
}

TEST_CASE("makeRelationship / Uses relationship, less than 2 parameter / "
          "throws error") {

  string typeInput = AppConstants::USES;
  Parameter p1("a", AppConstants::SYNONYM);
  vector<Parameter> inputParameters{p1};

  REQUIRE_THROWS(Relationship::makeRelationship(typeInput, inputParameters));
}

TEST_CASE(
    "makeRelationship / Modifies relationship / return relationship object") {

  string typeInput = AppConstants::MODIFIES;
  Parameter p1("a", AppConstants::SYNONYM);
  Parameter p2("_", AppConstants::WILDCARD);
  Parameter p3("ent_ref", AppConstants::FIXED_STRING);
  Parameter p4("1", AppConstants::FIXED_INT);
  vector<Parameter> inputParameters{p1, p2};
  vector<Parameter> inputParameters2{p4, p3};
  vector<Parameter> inputParameters3{p2, p3};
  RelationshipType expectedType = RelationshipType::USES;

  shared_ptr<Relationship> output =
      Relationship::makeRelationship(typeInput, inputParameters);
  ModifiesRelationship expected(inputParameters);
  CHECK(expected == *output);
  shared_ptr<Relationship> output2 =
      Relationship::makeRelationship(typeInput, inputParameters2);
  ModifiesRelationship expected2(inputParameters2);
  CHECK(expected2 == *output2);
  shared_ptr<Relationship> output3 =
      Relationship::makeRelationship(typeInput, inputParameters3);
  ModifiesRelationship expected3(inputParameters3);
  CHECK(expected3 == *output3);
}

TEST_CASE("makeRelationship / Modifies, wrong 1st param / throws error") {

  string typeInput = AppConstants::MODIFIES;
  Parameter p1("ent_ref", AppConstants::VARIABLE);
  Parameter p2("a", AppConstants::SYNONYM);
  vector<Parameter> inputParameters{p1, p2};
  REQUIRE_THROWS(Relationship::makeRelationship(typeInput, inputParameters));
}

TEST_CASE("makeRelationship / Modifies, wrong 2nd param / throws error") {

  string typeInput = AppConstants::MODIFIES;
  Parameter p1("a", AppConstants::SYNONYM);
  Parameter p2("stmt_ref", AppConstants::FIXED_INT);
  vector<Parameter> inputParameters{p1, p2};
  REQUIRE_THROWS(Relationship::makeRelationship(typeInput, inputParameters));
}

TEST_CASE("makeRelationship / Modifies relationship, more than 2 parameter / "
          "throws error") {

  string typeInput = AppConstants::MODIFIES;
  Parameter p1("a", AppConstants::SYNONYM);
  Parameter p2("b", AppConstants::SYNONYM);
  Parameter p3("c", AppConstants::SYNONYM);
  vector<Parameter> inputParameters{p1, p2, p3};

  REQUIRE_THROWS(Relationship::makeRelationship(typeInput, inputParameters));
}

TEST_CASE("makeRelationship / Modifies relationship, less than 2 parameter / "
          "throws error") {

  string typeInput = AppConstants::MODIFIES;
  Parameter p1("a", AppConstants::SYNONYM);
  vector<Parameter> inputParameters{p1};

  REQUIRE_THROWS(Relationship::makeRelationship(typeInput, inputParameters));
}

TEST_CASE("makeRelationship / Next relationship / return relationship object") {
  string typeInput = AppConstants::NEXT;
  Parameter p1("a", AppConstants::SYNONYM);
  Parameter p2("_", AppConstants::WILDCARD);
  Parameter p3("1", AppConstants::FIXED_INT);
  vector<Parameter> inputParameters{p1, p2};
  vector<Parameter> inputParameters2{p2, p3};
  vector<Parameter> inputParameters3{p3, p1};
  RelationshipType expectedType = RelationshipType::NEXT;

  shared_ptr<Relationship> output =
      Relationship::makeRelationship(typeInput, inputParameters);
  NextRelationship expected(inputParameters);
  CHECK(expected == *output);
  shared_ptr<Relationship> output2 =
      Relationship::makeRelationship(typeInput, inputParameters2);
  NextRelationship expected2(inputParameters2);
  CHECK(expected2 == *output2);
  shared_ptr<Relationship> output3 =
      Relationship::makeRelationship(typeInput, inputParameters3);
  NextRelationship expected3(inputParameters3);
  CHECK(expected3 == *output3);
}

TEST_CASE("makeRelationship / Next, wrong 1st param / throws error") {

  string typeInput = AppConstants::NEXT;
  Parameter p1("ent_ref", AppConstants::VARIABLE);
  Parameter p2("a", AppConstants::SYNONYM);
  vector<Parameter> inputParameters{p1, p2};
  REQUIRE_THROWS(Relationship::makeRelationship(typeInput, inputParameters));
}

TEST_CASE("makeRelationship / Next, wrong 2nd param / throws error") {

  string typeInput = AppConstants::NEXT;
  Parameter p1("a", AppConstants::SYNONYM);
  Parameter p2("ent_ref", AppConstants::FIXED_STRING);
  vector<Parameter> inputParameters{p1, p2};
  REQUIRE_THROWS(Relationship::makeRelationship(typeInput, inputParameters));
}

TEST_CASE("makeRelationship / Next relationship, more than 2 parameter / "
          "throws error") {

  string typeInput = AppConstants::NEXT;
  Parameter p1("a", AppConstants::SYNONYM);
  Parameter p2("b", AppConstants::SYNONYM);
  Parameter p3("c", AppConstants::SYNONYM);
  vector<Parameter> inputParameters{p1, p2, p3};

  REQUIRE_THROWS(Relationship::makeRelationship(typeInput, inputParameters));
}

TEST_CASE("makeRelationship / Next relationship, less than 2 parameter / "
          "throws error") {

  string typeInput = AppConstants::NEXT;
  Parameter p1("a", AppConstants::SYNONYM);
  vector<Parameter> inputParameters{p1};

  REQUIRE_THROWS(Relationship::makeRelationship(typeInput, inputParameters));
}

TEST_CASE(
    "makeRelationship / NextT relationship / return relationship object") {
  string typeInput = AppConstants::NEXTT;
  Parameter p1("a", AppConstants::SYNONYM);
  Parameter p2("_", AppConstants::WILDCARD);
  Parameter p3("1", AppConstants::FIXED_INT);
  vector<Parameter> inputParameters{p1, p2};
  vector<Parameter> inputParameters2{p2, p3};
  vector<Parameter> inputParameters3{p3, p1};
  RelationshipType expectedType = RelationshipType::NEXTT;

  shared_ptr<Relationship> output =
      Relationship::makeRelationship(typeInput, inputParameters);
  NextTRelationship expected(inputParameters);
  CHECK(expected == *output);
  shared_ptr<Relationship> output2 =
      Relationship::makeRelationship(typeInput, inputParameters2);
  NextTRelationship expected2(inputParameters2);
  CHECK(expected2 == *output2);
  shared_ptr<Relationship> output3 =
      Relationship::makeRelationship(typeInput, inputParameters3);
  NextTRelationship expected3(inputParameters3);
  CHECK(expected3 == *output3);
}

TEST_CASE("makeRelationship / NextT, wrong 1st param / throws error") {

  string typeInput = AppConstants::NEXTT;
  Parameter p1("ent_ref", AppConstants::VARIABLE);
  Parameter p2("a", AppConstants::SYNONYM);
  vector<Parameter> inputParameters{p1, p2};
  REQUIRE_THROWS(Relationship::makeRelationship(typeInput, inputParameters));
}

TEST_CASE("makeRelationship / NextT, wrong 2nd param / throws error") {

  string typeInput = AppConstants::NEXTT;
  Parameter p1("a", AppConstants::SYNONYM);
  Parameter p2("ent_ref", AppConstants::FIXED_STRING);
  vector<Parameter> inputParameters{p1, p2};
  REQUIRE_THROWS(Relationship::makeRelationship(typeInput, inputParameters));
}

TEST_CASE("makeRelationship / NextT relationship, more than 2 parameter / "
          "throws error") {

  string typeInput = AppConstants::NEXTT;
  Parameter p1("a", AppConstants::SYNONYM);
  Parameter p2("b", AppConstants::SYNONYM);
  Parameter p3("c", AppConstants::SYNONYM);
  vector<Parameter> inputParameters{p1, p2, p3};

  REQUIRE_THROWS(Relationship::makeRelationship(typeInput, inputParameters));
}

TEST_CASE("makeRelationship / NextT relationship, less than 2 parameter / "
          "throws error") {

  string typeInput = AppConstants::NEXTT;
  Parameter p1("a", AppConstants::SYNONYM);
  vector<Parameter> inputParameters{p1};

  REQUIRE_THROWS(Relationship::makeRelationship(typeInput, inputParameters));
}

TEST_CASE(
    "makeRelationship / Calls relationship / return relationship object") {
  string typeInput = AppConstants::CALLS;
  Parameter p1("a", AppConstants::SYNONYM);
  Parameter p2("_", AppConstants::WILDCARD);
  Parameter p3("ent_ref", AppConstants::FIXED_STRING);
  vector<Parameter> inputParameters{p1, p2};
  vector<Parameter> inputParameters2{p2, p3};
  vector<Parameter> inputParameters3{p3, p1};
  RelationshipType expectedType = RelationshipType::CALLS;

  shared_ptr<Relationship> output =
      Relationship::makeRelationship(typeInput, inputParameters);
  CallsRelationship expected(inputParameters);
  CHECK(expected == *output);
  shared_ptr<Relationship> output2 =
      Relationship::makeRelationship(typeInput, inputParameters2);
  CallsRelationship expected2(inputParameters2);
  CHECK(expected2 == *output2);
  shared_ptr<Relationship> output3 =
      Relationship::makeRelationship(typeInput, inputParameters3);
  CallsRelationship expected3(inputParameters3);
  CHECK(expected3 == *output3);
}

TEST_CASE("makeRelationship / Calls, wrong 1st param / throws error") {

  string typeInput = AppConstants::CALLS;
  Parameter p1("stmt_ref", AppConstants::FIXED_INT);
  Parameter p2("a", AppConstants::SYNONYM);
  vector<Parameter> inputParameters{p1, p2};
  REQUIRE_THROWS(Relationship::makeRelationship(typeInput, inputParameters));
}

TEST_CASE("makeRelationship / Calls, wrong 2nd param / throws error") {

  string typeInput = AppConstants::CALLS;
  Parameter p1("a", AppConstants::SYNONYM);
  Parameter p2("stmt_ref", AppConstants::FIXED_INT);
  vector<Parameter> inputParameters{p1, p2};
  REQUIRE_THROWS(Relationship::makeRelationship(typeInput, inputParameters));
}

TEST_CASE("makeRelationship / Calls relationship, more than 2 parameter / "
          "throws error") {

  string typeInput = AppConstants::CALLS;
  Parameter p1("a", AppConstants::SYNONYM);
  Parameter p2("b", AppConstants::SYNONYM);
  Parameter p3("c", AppConstants::SYNONYM);
  vector<Parameter> inputParameters{p1, p2, p3};

  REQUIRE_THROWS(Relationship::makeRelationship(typeInput, inputParameters));
}

TEST_CASE("makeRelationship / Calls relationship, less than 2 parameter / "
          "throws error") {

  string typeInput = AppConstants::CALLS;
  Parameter p1("a", AppConstants::SYNONYM);
  vector<Parameter> inputParameters{p1};

  REQUIRE_THROWS(Relationship::makeRelationship(typeInput, inputParameters));
}

TEST_CASE(
    "makeRelationship / CallsT relationship / return relationship object") {
  string typeInput = AppConstants::CALLST;
  Parameter p1("a", AppConstants::SYNONYM);
  Parameter p2("_", AppConstants::WILDCARD);
  Parameter p3("ent_ref", AppConstants::FIXED_STRING);
  vector<Parameter> inputParameters{p1, p2};
  vector<Parameter> inputParameters2{p2, p3};
  vector<Parameter> inputParameters3{p3, p1};
  RelationshipType expectedType = RelationshipType::CALLST;

  shared_ptr<Relationship> output =
      Relationship::makeRelationship(typeInput, inputParameters);
  CallsTRelationship expected(inputParameters);
  CHECK(expected == *output);
  shared_ptr<Relationship> output2 =
      Relationship::makeRelationship(typeInput, inputParameters2);
  CallsTRelationship expected2(inputParameters2);
  CHECK(expected2 == *output2);
  shared_ptr<Relationship> output3 =
      Relationship::makeRelationship(typeInput, inputParameters3);
  CallsTRelationship expected3(inputParameters3);
  CHECK(expected3 == *output3);
}

TEST_CASE("makeRelationship / CallsT, wrong 1st param / throws error") {

  string typeInput = AppConstants::CALLST;
  Parameter p1("stmt_ref", AppConstants::FIXED_INT);
  Parameter p2("a", AppConstants::SYNONYM);
  vector<Parameter> inputParameters{p1, p2};
  REQUIRE_THROWS(Relationship::makeRelationship(typeInput, inputParameters));
}

TEST_CASE("makeRelationship / CallsT, wrong 2nd param / throws error") {

  string typeInput = AppConstants::CALLST;
  Parameter p1("a", AppConstants::SYNONYM);
  Parameter p2("stmt_ref", AppConstants::FIXED_INT);
  vector<Parameter> inputParameters{p1, p2};
  REQUIRE_THROWS(Relationship::makeRelationship(typeInput, inputParameters));
}

TEST_CASE("makeRelationship / CallsT relationship, more than 2 parameter / "
          "throws error") {

  string typeInput = AppConstants::CALLST;
  Parameter p1("a", AppConstants::SYNONYM);
  Parameter p2("b", AppConstants::SYNONYM);
  Parameter p3("c", AppConstants::SYNONYM);
  vector<Parameter> inputParameters{p1, p2, p3};

  REQUIRE_THROWS(Relationship::makeRelationship(typeInput, inputParameters));
}

TEST_CASE("makeRelationship / CallsT relationship, less than 2 parameter / "
          "throws error") {

  string typeInput = AppConstants::CALLST;
  Parameter p1("a", AppConstants::SYNONYM);
  vector<Parameter> inputParameters{p1};

  REQUIRE_THROWS(Relationship::makeRelationship(typeInput, inputParameters));
}

TEST_CASE(
    "makeRelationship / Affects relationship / return relationship object") {
  string typeInput = AppConstants::AFFECTS;
  Parameter p1("a", AppConstants::SYNONYM);
  Parameter p2("_", AppConstants::WILDCARD);
  Parameter p3("stmt_ref", AppConstants::FIXED_INT);
  vector<Parameter> inputParameters{p1, p2};
  vector<Parameter> inputParameters2{p2, p3};
  vector<Parameter> inputParameters3{p3, p1};
  RelationshipType expectedType = RelationshipType::AFFECTS;

  shared_ptr<Relationship> output =
      Relationship::makeRelationship(typeInput, inputParameters);
  AffectsRelationship expected(inputParameters);
  CHECK(expected == *output);
  shared_ptr<Relationship> output2 =
      Relationship::makeRelationship(typeInput, inputParameters2);
  AffectsRelationship expected2(inputParameters2);
  CHECK(expected2 == *output2);
  shared_ptr<Relationship> output3 =
      Relationship::makeRelationship(typeInput, inputParameters3);
  AffectsRelationship expected3(inputParameters3);
  CHECK(expected3 == *output3);
}

TEST_CASE("makeRelationship / Affects, wrong 1st param / throws error") {

  string typeInput = AppConstants::AFFECTS;
  Parameter p1("ent_ref", AppConstants::FIXED_STRING);
  Parameter p2("a", AppConstants::SYNONYM);
  vector<Parameter> inputParameters{p1, p2};
  REQUIRE_THROWS(Relationship::makeRelationship(typeInput, inputParameters));
}

TEST_CASE("makeRelationship / Affects, wrong 2nd param / throws error") {

  string typeInput = AppConstants::AFFECTS;
  Parameter p1("a", AppConstants::SYNONYM);
  Parameter p2("ent_ref", AppConstants::FIXED_STRING);
  vector<Parameter> inputParameters{p1, p2};
  REQUIRE_THROWS(Relationship::makeRelationship(typeInput, inputParameters));
}

TEST_CASE("makeRelationship / Affects relationship, more than 2 parameter / "
          "throws error") {

  string typeInput = AppConstants::AFFECTS;
  Parameter p1("a", AppConstants::SYNONYM);
  Parameter p2("b", AppConstants::SYNONYM);
  Parameter p3("c", AppConstants::SYNONYM);
  vector<Parameter> inputParameters{p1, p2, p3};

  REQUIRE_THROWS(Relationship::makeRelationship(typeInput, inputParameters));
}

TEST_CASE("makeRelationship / Affects relationship, less than 2 parameter / "
          "throws error") {

  string typeInput = AppConstants::AFFECTS;
  Parameter p1("a", AppConstants::SYNONYM);
  vector<Parameter> inputParameters{p1};

  REQUIRE_THROWS(Relationship::makeRelationship(typeInput, inputParameters));
}

TEST_CASE(
    "makeRelationship / AffectsT relationship / return relationship object") {
  string typeInput = AppConstants::AFFECTST;
  Parameter p1("a", AppConstants::SYNONYM);
  Parameter p2("_", AppConstants::WILDCARD);
  Parameter p3("stmt_ref", AppConstants::FIXED_INT);
  vector<Parameter> inputParameters{p1, p2};
  vector<Parameter> inputParameters2{p2, p3};
  vector<Parameter> inputParameters3{p3, p1};
  RelationshipType expectedType = RelationshipType::AFFECTST;

  shared_ptr<Relationship> output =
      Relationship::makeRelationship(typeInput, inputParameters);
  AffectsTRelationship expected(inputParameters);
  CHECK(expected == *output);
  shared_ptr<Relationship> output2 =
      Relationship::makeRelationship(typeInput, inputParameters2);
  AffectsTRelationship expected2(inputParameters2);
  CHECK(expected2 == *output2);
  shared_ptr<Relationship> output3 =
      Relationship::makeRelationship(typeInput, inputParameters3);
  AffectsTRelationship expected3(inputParameters3);
  CHECK(expected3 == *output3);
}

TEST_CASE("makeRelationship / AffectsT, wrong 1st param / throws error") {

  string typeInput = AppConstants::AFFECTST;
  Parameter p1("ent_ref", AppConstants::FIXED_STRING);
  Parameter p2("a", AppConstants::SYNONYM);
  vector<Parameter> inputParameters{p1, p2};
  REQUIRE_THROWS(Relationship::makeRelationship(typeInput, inputParameters));
}

TEST_CASE("makeRelationship / AffectsT, wrong 2nd param / throws error") {

  string typeInput = AppConstants::AFFECTST;
  Parameter p1("a", AppConstants::SYNONYM);
  Parameter p2("ent_ref", AppConstants::FIXED_STRING);
  vector<Parameter> inputParameters{p1, p2};
  REQUIRE_THROWS(Relationship::makeRelationship(typeInput, inputParameters));
}

TEST_CASE("makeRelationship / AffectsT relationship, more than 2 parameter / "
          "throws error") {

  string typeInput = AppConstants::AFFECTST;
  Parameter p1("a", AppConstants::SYNONYM);
  Parameter p2("b", AppConstants::SYNONYM);
  Parameter p3("c", AppConstants::SYNONYM);
  vector<Parameter> inputParameters{p1, p2, p3};

  REQUIRE_THROWS(Relationship::makeRelationship(typeInput, inputParameters));
}

TEST_CASE("makeRelationship / AffectsT relationship, less than 2 parameter / "
          "throws error") {

  string typeInput = AppConstants::AFFECTST;
  Parameter p1("a", AppConstants::SYNONYM);
  vector<Parameter> inputParameters{p1};

  REQUIRE_THROWS(Relationship::makeRelationship(typeInput, inputParameters));
}

TEST_CASE(
    "FollowsRelationship.validateParams / invalid 1st param / return false") {

  string typeInput = AppConstants::FOLLOWS;
  Parameter p1("a", AppConstants::SYNONYM);
  Parameter p2("1", AppConstants::FIXED_INT);
  vector<Parameter> inputParameters{p1, p2};

  shared_ptr<Relationship> output =
      Relationship::makeRelationship(typeInput, inputParameters);
  output->params.at(0).updateSynonymType(ParameterType::VARIABLE);
  CHECK(!output->validateParams());
}

TEST_CASE(
    "FollowsRelationship.validateParams / invalid 2nd params / return false") {

  string typeInput = AppConstants::FOLLOWS;
  Parameter p1("1", AppConstants::FIXED_INT);
  Parameter p2("a", AppConstants::SYNONYM);
  vector<Parameter> inputParameters{p1, p2};

  shared_ptr<Relationship> output =
      Relationship::makeRelationship(typeInput, inputParameters);
  output->params.at(1).updateSynonymType(ParameterType::VARIABLE);
  CHECK(!output->validateParams());
}

TEST_CASE("FollowsRelationship.validateParams / valid params / return true") {

  string typeInput = AppConstants::FOLLOWS;
  Parameter p1("a", AppConstants::SYNONYM);
  Parameter p2("1", AppConstants::FIXED_INT);
  vector<Parameter> inputParameters{p1, p2};

  shared_ptr<Relationship> output =
      Relationship::makeRelationship(typeInput, inputParameters);
  output->params.at(0).updateSynonymType(ParameterType::ASSIGN);
  CHECK(output->validateParams());
}

TEST_CASE(
    "FollowsTRelationship.validateParams / invalid 1st params / return false") {

  string typeInput = AppConstants::FOLLOWST;
  Parameter p1("a", AppConstants::SYNONYM);
  Parameter p2("1", AppConstants::FIXED_INT);
  vector<Parameter> inputParameters{p1, p2};

  shared_ptr<Relationship> output =
      Relationship::makeRelationship(typeInput, inputParameters);
  output->params.at(0).updateSynonymType(ParameterType::VARIABLE);
  CHECK(!output->validateParams());
}

TEST_CASE(
    "FollowsTRelationship.validateParams / invalid 2nd params / return false") {

  string typeInput = AppConstants::FOLLOWST;
  Parameter p1("1", AppConstants::FIXED_INT);
  Parameter p2("a", AppConstants::SYNONYM);
  vector<Parameter> inputParameters{p1, p2};

  shared_ptr<Relationship> output =
      Relationship::makeRelationship(typeInput, inputParameters);
  output->params.at(1).updateSynonymType(ParameterType::VARIABLE);
  CHECK(!output->validateParams());
}

TEST_CASE("FollowsTRelationship.validateParams / valid params / return true") {

  string typeInput = AppConstants::FOLLOWST;
  Parameter p1("a", AppConstants::SYNONYM);
  Parameter p2("1", AppConstants::FIXED_INT);
  vector<Parameter> inputParameters{p1, p2};

  shared_ptr<Relationship> output =
      Relationship::makeRelationship(typeInput, inputParameters);
  output->params.at(0).updateSynonymType(ParameterType::STMT);
  CHECK(output->validateParams());
}

TEST_CASE(
    "ParentRelationship.validateParams / invalid 1st params / return false") {

  string typeInput = AppConstants::PARENT;
  Parameter p1("a", AppConstants::SYNONYM);
  Parameter p2("1", AppConstants::FIXED_INT);
  vector<Parameter> inputParameters{p1, p2};

  shared_ptr<Relationship> output =
      Relationship::makeRelationship(typeInput, inputParameters);
  output->params.at(0).updateSynonymType(ParameterType::VARIABLE);
  CHECK(!output->validateParams());
}

TEST_CASE(
    "ParentRelationship.validateParams / invalid 2nd params / return false") {

  string typeInput = AppConstants::PARENT;
  Parameter p1("1", AppConstants::FIXED_INT);
  Parameter p2("a", AppConstants::SYNONYM);
  vector<Parameter> inputParameters{p1, p2};

  shared_ptr<Relationship> output =
      Relationship::makeRelationship(typeInput, inputParameters);
  output->params.at(1).updateSynonymType(ParameterType::VARIABLE);
  CHECK(!output->validateParams());
}

TEST_CASE("ParentRelationship.validateParams / valid params / return true") {

  string typeInput = AppConstants::PARENT;
  Parameter p1("1", AppConstants::FIXED_INT);
  Parameter p2("a", AppConstants::SYNONYM);
  vector<Parameter> inputParameters{p1, p2};

  shared_ptr<Relationship> output =
      Relationship::makeRelationship(typeInput, inputParameters);
  output->params.at(1).updateSynonymType(ParameterType::READ);
  CHECK(output->validateParams());
}

TEST_CASE(
    "ParentTRelationship.validateParams / invalid 1st params / return false") {

  string typeInput = AppConstants::PARENTT;
  Parameter p1("a", AppConstants::SYNONYM);
  Parameter p2("1", AppConstants::FIXED_INT);
  vector<Parameter> inputParameters{p1, p2};

  shared_ptr<Relationship> output =
      Relationship::makeRelationship(typeInput, inputParameters);
  output->params.at(0).updateSynonymType(ParameterType::VARIABLE);
  CHECK(!output->validateParams());
}

TEST_CASE(
    "ParentTRelationship.validateParams / invalid 2nd params / return false") {

  string typeInput = AppConstants::PARENTT;
  Parameter p1("1", AppConstants::FIXED_INT);
  Parameter p2("a", AppConstants::SYNONYM);
  vector<Parameter> inputParameters{p1, p2};

  shared_ptr<Relationship> output =
      Relationship::makeRelationship(typeInput, inputParameters);
  output->params.at(1).updateSynonymType(ParameterType::VARIABLE);
  CHECK(!output->validateParams());
}

TEST_CASE("ParentTRelationship.validateParams / valid params / return true") {

  string typeInput = AppConstants::PARENTT;
  Parameter p1("1", AppConstants::FIXED_INT);
  Parameter p2("a", AppConstants::SYNONYM);
  vector<Parameter> inputParameters{p1, p2};

  shared_ptr<Relationship> output =
      Relationship::makeRelationship(typeInput, inputParameters);
  output->params.at(1).updateSynonymType(ParameterType::WHILE);
  CHECK(output->validateParams());
}

TEST_CASE(
    "ModifiesRelationship.validateParams / invalid 1st params / return false") {

  string typeInput = AppConstants::MODIFIES;
  Parameter p1("a", AppConstants::SYNONYM);
  Parameter p2("a", AppConstants::FIXED_STRING);
  vector<Parameter> inputParameters{p1, p2};

  shared_ptr<Relationship> output =
      Relationship::makeRelationship(typeInput, inputParameters);
  output->params.at(0).updateSynonymType(ParameterType::VARIABLE);
  CHECK(!output->validateParams());
}

TEST_CASE(
    "ModifiesRelationship.validateParams / invalid 2nd params / return false") {

  string typeInput = AppConstants::MODIFIES;
  Parameter p1("1", AppConstants::FIXED_INT);
  Parameter p2("a", AppConstants::SYNONYM);
  vector<Parameter> inputParameters{p1, p2};

  shared_ptr<Relationship> output =
      Relationship::makeRelationship(typeInput, inputParameters);
  output->params.at(1).updateSynonymType(ParameterType::PROCEDURE);
  CHECK(!output->validateParams());
}

TEST_CASE("ModifiesRelationship.validateParams / 1st param is procedure / "
          "return true") {

  string typeInput = AppConstants::MODIFIES;
  Parameter p1("a", AppConstants::SYNONYM);
  Parameter p2("a", AppConstants::FIXED_STRING);
  vector<Parameter> inputParameters{p1, p2};

  shared_ptr<Relationship> output =
      Relationship::makeRelationship(typeInput, inputParameters);
  output->params.at(0).updateSynonymType(ParameterType::PROCEDURE);
  CHECK(output->validateParams());
}

TEST_CASE("ModifiesRelationship.validateParams / 1st param is stmt ref / "
          "return true") {

  string typeInput = AppConstants::MODIFIES;
  Parameter p1("a", AppConstants::SYNONYM);
  Parameter p2("a", AppConstants::FIXED_STRING);
  vector<Parameter> inputParameters{p1, p2};

  shared_ptr<Relationship> output =
      Relationship::makeRelationship(typeInput, inputParameters);
  output->params.at(0).updateSynonymType(ParameterType::CALL);
  CHECK(output->validateParams());
}

TEST_CASE(
    "UsesRelationship.validateParams / invalid 1st params / return false") {

  string typeInput = AppConstants::USES;
  Parameter p1("a", AppConstants::SYNONYM);
  Parameter p2("a", AppConstants::FIXED_STRING);
  vector<Parameter> inputParameters{p1, p2};

  shared_ptr<Relationship> output =
      Relationship::makeRelationship(typeInput, inputParameters);
  output->params.at(0).updateSynonymType(ParameterType::VARIABLE);
  CHECK(!output->validateParams());
}

TEST_CASE(
    "UsesRelationship.validateParams / invalid 2nd params / return false") {

  string typeInput = AppConstants::USES;
  Parameter p1("1", AppConstants::FIXED_INT);
  Parameter p2("a", AppConstants::SYNONYM);
  vector<Parameter> inputParameters{p1, p2};

  shared_ptr<Relationship> output =
      Relationship::makeRelationship(typeInput, inputParameters);
  output->params.at(1).updateSynonymType(ParameterType::PROCEDURE);
  CHECK(!output->validateParams());
}

TEST_CASE(
    "UsesRelationship.validateParams / 1st param is procedure / return true") {

  string typeInput = AppConstants::USES;
  Parameter p1("a", AppConstants::SYNONYM);
  Parameter p2("a", AppConstants::FIXED_STRING);
  vector<Parameter> inputParameters{p1, p2};

  shared_ptr<Relationship> output =
      Relationship::makeRelationship(typeInput, inputParameters);
  output->params.at(0).updateSynonymType(ParameterType::PROCEDURE);
  CHECK(output->validateParams());
}

TEST_CASE(
    "UsesRelationship.validateParams / 1st param is stmt ref / return true") {

  string typeInput = AppConstants::USES;
  Parameter p1("a", AppConstants::SYNONYM);
  Parameter p2("a", AppConstants::FIXED_STRING);
  vector<Parameter> inputParameters{p1, p2};

  shared_ptr<Relationship> output =
      Relationship::makeRelationship(typeInput, inputParameters);
  output->params.at(0).updateSynonymType(ParameterType::CALL);
  CHECK(output->validateParams());
}

TEST_CASE(
    "getAllUncheckedSynonyms / contains no synonyms / return empty list ") {

  string typeInput = AppConstants::FOLLOWS;
  Parameter p1("1", AppConstants::FIXED_INT);
  Parameter p2("2", AppConstants::FIXED_INT);
  vector<Parameter> inputParameters{p1, p2};

  shared_ptr<Relationship> output =
      Relationship::makeRelationship(typeInput, inputParameters);
  vector<Parameter *> synonyms = output->getAllUncheckedSynonyms();
  CHECK(synonyms.empty());
}

TEST_CASE("getAllUncheckedSynonyms / contains one synonyms / return list with "
          "pointer to synonym") {

  string typeInput = AppConstants::FOLLOWS;
  Parameter p1("a", AppConstants::SYNONYM);
  Parameter p2("2", AppConstants::FIXED_INT);
  Parameter p1After("a", AppConstants::STMT);
  vector<Parameter> inputParameters{p1, p2};
  vector<Parameter> afterParameters{p1After, p2};

  shared_ptr<Relationship> output =
      Relationship::makeRelationship(typeInput, inputParameters);
  shared_ptr<Relationship> expected =
      Relationship::makeRelationship(typeInput, afterParameters);
  vector<Parameter *> synonyms = output->getAllUncheckedSynonyms();
  REQUIRE(synonyms.size() == 1);
  Parameter *pp = synonyms.at(0);
  pp->updateSynonymType(ParameterType::STMT);
  REQUIRE((*output) == (*expected));
}

TEST_CASE("getAllUncheckedSynonyms / contains more than one synonym / return "
          "list with pointer to the synonyms") {

  string typeInput = AppConstants::FOLLOWS;
  Parameter p1("a", AppConstants::SYNONYM);
  Parameter p2("b", AppConstants::SYNONYM);
  vector<Parameter> inputParameters{p1, p2};

  shared_ptr<Relationship> output =
      Relationship::makeRelationship(typeInput, inputParameters);
  vector<Parameter *> synonyms = output->getAllUncheckedSynonyms();
  REQUIRE(synonyms.size() == 2);
}
