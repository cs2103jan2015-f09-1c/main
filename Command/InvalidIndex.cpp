#include "InvalidIndex.h"


InvalidIndex::InvalidIndex(std::string msg) {
    _message = msg;
}

InvalidIndex::~InvalidIndex(void) {
}

const char* InvalidIndex::what() const throw() {
     return _message.c_str();
}