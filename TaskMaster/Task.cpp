#define _CRT_SECURE_NO_WARNINGS
#include "Task.h"
#include <sstream> 
#include <iomanip> // put_time

Task::Task(void):   _taskID(0), 
                    _isDone(false), 
                    _isFloating(true),
                    _isWithoutTime(false),
                    _taskBegin(0),
                    _taskEnd(0) {
}

Task::~Task(void) {
}

void Task::setTaskName(std::string name) {
    _taskName = name;
}

std::string Task::getTaskName() const {
    return _taskName;
}

void Task::setFloating() {
	_isFloating = true;
	_taskBegin = 0;
}

void Task::setNotFloating() {
	_isFloating = false;
}


bool Task::isFloating() const {
    return _isFloating;
}

bool Task::isTaskWithoutTime() const{
	return _isWithoutTime;
}

void Task::setTaskWithoutTime() {
    _isWithoutTime = true;
}

void Task::setTaskWithTime() {
    _isWithoutTime = false;
}

std::string Task::getDateStr() const {
    //refer to std::put_time fmt
    tm beginStruct;
    localtime_s(&beginStruct, &_taskBegin);
    std::ostringstream beginOss;
    beginOss << std::put_time(&beginStruct, "%a %b %d %Y");
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

    if (_taskBegin == 0) {
        _isFloating = true;
    } else {
        _isFloating = false;
    }
}

void Task::setTaskEnd(time_t end) {
    _taskEnd = end;
}
    
void Task::markDone() {
    _isDone = true;
}

void Task::markUndone() {
    _isDone = false;
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

std::string Task::toString() const {
    std::ostringstream oss;
    oss << getTaskID() << " ";
    oss << getTaskName() << std::endl;
    oss << getDateStr() << " ";
    oss << getBeginStr() << " - ";
    oss << getEndStr() << std::endl;
    oss << "done: " << isDone() << " ";
	oss << "float: " << isFloating();

    return oss.str();
}

std::string Task::toStringWithoutDate() const {
    std::ostringstream oss;
    oss << getTaskID() << " ";
    oss << getTaskName() << std::endl;
    oss << getBeginStr() << " - ";
    oss << getEndStr() << std::endl;
    oss << "done: " << isDone() << " ";
	oss << "float: " << isFloating();
    return oss.str();
}