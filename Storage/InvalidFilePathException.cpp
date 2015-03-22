#include "InvalidFilePathException.h"


InvalidFilePathException::InvalidFilePathException(std::string msg) {
    _message = msg;
}

InvalidFilePathException::~InvalidFilePathException(void) {
}

const char* InvalidFilePathException::what() const throw() {
     return _message.c_str();
}