#include "../../qps/entities/Parameter.h"
#include "../storage/CallsStorage.h"
#include <algorithm>
#include <memory>


class CallsHandler {
public:
    CallsHandler(std::shared_ptr<CallsStorage> callsStorage);
    std::vector<std::vector<std::string>> handle(Parameter param1, Parameter param2);

private:
    std::shared_ptr<CallsStorage> callsStorage;

    // e.g. Calls("proc1", "proc2")
    std::vector<std::vector<std::string>> handleProcnameProcname(Parameter param1, Parameter param2);

    // e.g. CallsT("proc1", p2) or Calls("proc1", _)
    std::vector<std::vector<std::string>> handleProcnameWildcard(Parameter param1);

    // e.g. Calls(_, "proc2") or Calls(p1, "proc2")
    std::vector<std::vector<std::string>> handleWildcardProcname(Parameter param2);

    // e.g. CallsT(_, _)
    std::vector<std::vector<std::string>> handleWildcardWildcard();

};

