//
// Created by Faruq on 31/1/23.
//

#include "Query.h"

vector<string> Query::evaluate(ReadPKB &readPKB) {
    // I am going to assume here that since the object has been created it means
    // that the variables are correctly instantiated.
    QueryDB queryDb = QueryDB();
    Table emptyTable({},{});
    for (shared_ptr<Relationship> relation : relations) {
        // Run an PKB API call for each relationship.
        // Taking the example of select s1 follows(s1, s2)
        vector<vector<string>> response = readPKB.findRelationship(relation);
        vector<Parameter> params = relation->getParameters();
        Table table(params, response);
        if (response.empty()) {
            queryDb.insertTable(emptyTable);
            break;
        }
        // clauses that are just fixed ints or wild cards will just be
        // taken as true and not be inserted into the tableVec
        table = table.extractDesignEntities();
        if (!table.isEmptyTable()) {
            queryDb.insertTable(table);
        }
    }

    for (Pattern pattern : patterns) {
    // Run an PKB API call for each relationship.
    // Taking the example of select s1 follows(s1, s2)
        vector<vector<string>> response = readPKB.findPattern(pattern);
        Parameter *patternSyn = pattern.getPatternSyn();
        Parameter *entRef = pattern.getEntRef();
        vector<Parameter> headers{*patternSyn, *entRef};
        Table table(headers, response);
        if (response.empty()) {
            queryDb.insertTable(emptyTable);
            break;
        }
        // This will remove wild cards and FIXED INT from the table.
        table = table.extractDesignEntities();
        if (!table.isEmptyTable()) {
            queryDb.insertTable(table);
        }
    }
    vector<string> res = queryDb.fetch(selectParameters, readPKB);
    return res;
}

Query::Query() {}

Query::Query(const Query& q) {
    for (int i = 0; i < q.relations.size(); i++) {
    }
    relations = q.relations;
    selectParameters = q.selectParameters;
    patterns = q.patterns;
}

Query::Query(vector<Parameter>& ss, vector<shared_ptr<Relationship>>& rs, vector<Pattern>& ps) {
    selectParameters = ss;
    relations = rs;
    patterns = ps;
}

vector<Parameter*> Query::getAllUncheckedSynonyms() {
    vector<Parameter*> synonyms;
    for (int i = 0; i < selectParameters.size(); i++) {
        if (selectParameters.at(i).isUncheckedSynonym()) {
            synonyms.push_back(&selectParameters.at(i));
        }
    }
    for (int i = 0; i < relations.size(); i++) {
        vector<Parameter*> relSyns = (*relations.at(i)).getAllUncheckedSynonyms();
        for (int j = 0; j < relSyns.size(); j++) {
            synonyms.push_back(relSyns.at(j));
        }
    }
    for (int i = 0; i < patterns.size(); i++) {
        Parameter* entRef = patterns.at(i).getEntRef();
        Parameter* patternSyn = patterns.at(i).getPatternSyn();
        if (entRef->getType() == ParameterType::SYNONYM) {
            synonyms.push_back(entRef);
        }
        if (patternSyn->getType() == ParameterType::SYNONYM) {
            synonyms.push_back(patternSyn);
        }
    }
    return synonyms;
}

bool Query::validateAllParameters() {
    for (Pattern p : patterns) {
        if (!p.validateParams()) {
            return false;
        }
    }

    for (shared_ptr<Relationship> r : relations) {
        if (!(*r).validateParams()) {
            return false;
        }
    }

    for (Parameter p : selectParameters) {
        if (selectParameters.size() > 1 && p.getType() == ParameterType::BOOLEAN) {
            throw SyntaxException();
        }
    }
    return true;
}
