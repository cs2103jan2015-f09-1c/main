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

CommandType History::getPreviousCommand() const {
    return _previousCommand;
}

void History::saveCommand(CommandType cmdType) {
    _previousCommand = cmdType;
}

State History::getPreviousState() const {
    return _previousState;
}

void History::saveState(State state) {
    _previousState = state;
}

History::History(void) {
}


History::~History(void) {
}
