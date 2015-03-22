#include "State.h"

State::State(void) {
}

State::~State(void) {
}

void State::recordTask(Task task) {
    _task = task;
}

Task State::getTask() const {
    return _task;
}

void State::recordStorageLoc(std::string loc) {
    _storageLoc = loc;
}

std::string State::getStorageLoc() const {
    return _storageLoc;
}
