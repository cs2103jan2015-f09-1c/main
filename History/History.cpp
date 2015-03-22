#include "History.h"

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
    _previousState = state;
}

void History::clearHistory() {
    _previousCommand = CommandType::INVALID;
}

History::History(void): 
    _previousCommand(CommandType::INVALID) {
}


History::~History(void) {
}
