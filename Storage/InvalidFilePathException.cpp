//@Seow Yan Yi A0086626W
#include "InvalidFilePathException.h"
#include "MCLogger.h"

InvalidFilePathException::InvalidFilePathException(std::string msg) {
	MCLogger::log("EXCEPTION: invalid file path");
    _message = msg;
}

InvalidFilePathException::~InvalidFilePathException(void) {
}

const char* InvalidFilePathException::what() const throw() {
     return _message.c_str();
}