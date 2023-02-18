#include <utility>
#include "Exception.h"
using namespace std;

Exception::Exception() = default;

Exception::Exception(string message) {
    this->errorMessage = std::move(message);
}

string Exception::getMessage() {
    return this->errorMessage;
}