//@Seow Yan Yi A0086626W
#include "History.h"
#include "MCLogger.h"
History* History::_instance = 0;

History* History::getInstance() {
    if (_instance == 0) {
        _instance = new History;
    }
    return _instance;
}

void History::resetInstance() {
    delete _instance;
    _instance = NULL;
}

CommandType::Command History::getPreviousCommand() const {
    return _previousCommand;
}

void History::saveCommand(CommandType::Command cmd) {
    _previousCommand = cmd;
}

State History::getPreviousState() const {
    return _previousState;
}

void History::saveState(State state) {
	MCLogger::log("History.cpp: save state " + state.toString());
    _previousState = state;
}

void History::clearHistory() {
	MCLogger::log("History.cpp: clear history");
    _previousCommand = CommandType::INVALID;
}

History::History(void): 
    _previousCommand(CommandType::INVALID) {
}


History::~History(void) {
}
