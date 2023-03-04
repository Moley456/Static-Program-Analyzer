#ifndef SPA_QPS_NEXTRELATIONSHIP_H
#define SPA_QPS_NEXTRELATIONSHIP_H
#include "Relationship.h"
#include "exceptions/SyntaxException.h"

using namespace std;

class NextRelationship : public Relationship {
public:
  NextRelationship(vector<Parameter> &);
  bool validateParams();
};
#endif // !SPA_QPS_NEXTRELATIONSHIP_H