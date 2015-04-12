//@Seow Yan Yi A0086626W
#include "TaskNotFoundException.h"
#include "MCLogger.h"

TaskNotFoundException::TaskNotFoundException(std::string msg) {
	MCLogger::log("EXCEPTION: " + msg);
    _message = msg;
}

TaskNotFoundException::~TaskNotFoundException(void) {
}

const char* TaskNotFoundException::what() const throw() {
     return _message.c_str();
}