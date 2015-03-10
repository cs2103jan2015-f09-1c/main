#include "Task.h"
#include <sstream> 
#include <iomanip> // put_time

Task::Task(void): _taskID(0), _isDone(false), _isFloating(true),
    _taskBegin(0), _taskEnd(0) {

}


Task::~Task(void) {
}

void Task::setTaskName(std::string name) {
    _taskName = name;
}

std::string Task::getTaskName() const {
    return _taskName;
}

bool Task::isFloating() const {
    return _isFloating;
}

std::string Task::getDateStr() const {
    //refer to std::put_time fmt
    tm beginStruct;
    localtime_s(&beginStruct, &_taskBegin);
    std::ostringstream beginOss;
    beginOss << std::put_time(&beginStruct, "%a %b %d");
    return beginOss.str();
}

std::string Task::getBeginStr() const {
    //refer to std::put_time fmt
    tm beginStruct;
    localtime_s(&beginStruct, &_taskBegin);
    std::ostringstream beginOss;
    beginOss << std::put_time(&beginStruct, "%I:%M %p");
    return beginOss.str();
}

std::string Task::getEndStr() const {
    tm endStruct;
    localtime_s(&endStruct, &_taskEnd);
    std::ostringstream endOss;
    endOss << std::put_time(&endStruct, "%I:%M %p");
    return endOss.str();
}

time_t Task::getTaskBegin() const {
    return _taskBegin;
}

time_t Task::getTaskEnd() const {
    return _taskEnd;
}

void Task::setTaskBegin(time_t begin) {
    _taskBegin = begin;
    _isFloating = false;
}

void Task::setTaskEnd(time_t end) {
    _taskEnd = end;
}
    
void Task::markDone() {
    _isDone = true;
}

bool Task::isDone() const {
    return _isDone;
}

unsigned Task::getTaskID() const {
    return _taskID;
}

void Task::setTaskID(unsigned id) {
    _taskID = id;
}