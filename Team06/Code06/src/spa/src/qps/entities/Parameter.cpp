#include "Parameter.h"

string Parameter::getValue()
{
	return value;
}

ParameterType Parameter::getType() const
{
	return type;
}

Parameter::Parameter(string v, string t)
{
	value = v;
	type = stringToType(t);
}

Parameter::Parameter(string v, ParameterType t)
{
	value = v;
	type = t;
}

Parameter::Parameter(const Parameter& p)
{
	value = p.value;
	type = p.type;
}

Parameter::Parameter()
{
	type = ParameterType::UNKNOWN;
	value = "";
}

bool Parameter::isSyntacticStatementRef(Parameter& p)
{
	return p.type == ParameterType::SYNONYM || isStatementRef(p);
}

bool Parameter::isStatementRef(Parameter& p)
{
	switch (p.type) {
	case ParameterType::STMT:
		return true;
	case ParameterType::READ:
		return true;
	case ParameterType::PRINT:
		return true;
	case ParameterType::WHILE:
		return true;
	case ParameterType::IF:
		return true;
	case ParameterType::ASSIGN:
		return true;
	case ParameterType::FIXED_INT:
		return true;
	case ParameterType::WILDCARD:
		return true;
	case ParameterType::CALL:
		return true;

	}
	return false;
}

bool Parameter::isProcedure(Parameter& p)
{
	return p.type == ParameterType::PROCEDURE || p.type == ParameterType::FIXED_STRING;
}

bool Parameter::isDsgEntity(Parameter& p) {
    return isDesignEntity(p.getTypeString());
}

bool Parameter::isUncheckedSynonym()
{
	return type == ParameterType::SYNONYM;
}

void Parameter::updateSynonymType(ParameterType pt)
{
	if (type != ParameterType::SYNONYM) {
		throw InternalException("Error: Parameter.updateSynonymType parameter is not a synonym.");
	}
	type = pt;
}

bool Parameter::isSyntacticEntityRef(Parameter& p)
{
	return p.type == ParameterType::SYNONYM || isEntityRef(p);
}

bool Parameter::isEntityRef(Parameter& p)
{
	return p.type == ParameterType::VARIABLE || p.type == ParameterType::WILDCARD || p.type == ParameterType::FIXED_STRING;
}

//TODO: IF NOT FOUND, MAY WANT TO THROW ERROR
ParameterType Parameter::stringToType(string s)
{
	auto iter = Parameter::stringToTypeMap.find(s);
	if (iter == stringToTypeMap.end()) {
		return ParameterType::UNKNOWN;
	}
	return iter->second;
}

string Parameter::getTypeString() const {
    for(pair<string, ParameterType> item: stringToTypeMap) {
        if(item.second == this->getType()) {
            return item.first;
        }
    }
    return "None";
}

ParameterType Parameter::guessParameterType(string s)
{
	if (isSynonym(s)) {
		return ParameterType::SYNONYM;
	}
	if (isFixedString(s)) {
		return ParameterType::FIXED_STRING;
	}
	if (isInteger(s)) {
		return ParameterType::FIXED_INT;
	}
	if (isWildCard(s)) {
		return ParameterType::WILDCARD;
	}
	return ParameterType::UNKNOWN;
}

bool Parameter::isEqualTo(Parameter p) {
    return p.getValue() == this->getValue();
}

bool Parameter::operator==(const Parameter& p) const
{
	return type == p.type && value == p.value;
}

bool Parameter::isPatternSyn(Parameter& p)
{
	return p.type == ParameterType::ASSIGN;
}

const unordered_map<string, ParameterType> Parameter::stringToTypeMap = {
	{AppConstants::STMT, ParameterType::STMT},
	{AppConstants::READ, ParameterType::READ},
	{AppConstants::PRINT, ParameterType::PRINT},
	{AppConstants::CALL, ParameterType::CALL},
	{AppConstants::WHILE, ParameterType::WHILE},
	{AppConstants::IF, ParameterType::IF},
	{AppConstants::ASSIGN, ParameterType::ASSIGN},
	{AppConstants::VARIABLE, ParameterType::VARIABLE},
	{AppConstants::CONSTANT, ParameterType::CONSTANT},
	{AppConstants::PROCEDURE, ParameterType::PROCEDURE},
	{AppConstants::SYNONYM, ParameterType::SYNONYM},
	{AppConstants::WILDCARD, ParameterType::WILDCARD},
	{AppConstants::FIXED_INT, ParameterType::FIXED_INT},
	{AppConstants::FIXED_STRING, ParameterType::FIXED_STRING},
	{AppConstants::FIXED_STRING_WTIH_WILDCARD, ParameterType::FIXED_STRING_WITH_WILDCARD},
};