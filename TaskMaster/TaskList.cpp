#define _CRT_SECURE_NO_WARNINGS
#include "TaskList.h"
#include <sstream>
#include <iomanip> //put_time
#include <time.h>
#include <iostream>


TaskList::TaskList(void) {
}


TaskList::~TaskList(void) {
}

void TaskList::add(Task task) {
    _taskList.push_back(task);
    sortByDate();
}

void TaskList::update(Task task) {
    taskIt it;
    for (it = _taskList.begin(); it != _taskList.end(); ++it) {
        unsigned targetId = task.getTaskID();
        unsigned curId = it->getTaskID();

        if (foundTask(targetId, curId)) {
            replaceTask(it, task);
            sortByDate();
            break;
        }
    }
}

void TaskList::remove(unsigned id) {
    taskIt it;
    for (it = _taskList.begin(); it != _taskList.end(); ++it) {
        unsigned curId = it->getTaskID();

        if (foundTask(id, curId)) {
            _taskList.erase(it);
            break;
        }
    }
}

TaskList::TList TaskList::getDay(time_t day) const {
    TaskList retList;
    constTaskIt it;
    for (it = _taskList.begin(); it != _taskList.end(); ++it) {
        time_t begin = it->getTaskBegin();
        if (isSameDay(day, begin)) {
            retList.add((*it));
        }
    }
    
    return retList.getAll();
}

TaskList::TList TaskList::getToday() const {
    time_t curTime;
    time(&curTime); //get today

    return getDay(curTime);    
}

TaskList::TList TaskList::getTomorrow() const {
    time_t curTime = time(NULL);	//get today
	curTime += 86400; // add number of seconds in a day
    return getDay(curTime);    
}

TaskList::TList TaskList::getWeekly() const {	
	TaskList retList;
    constTaskIt it;

	time_t curTime;
	time_t day;
	struct tm * timeinfo;
	int diff = 0;

	time (&curTime);
	timeinfo = localtime(&curTime);

	if(timeinfo->tm_wday != 1){
		diff = timeinfo->tm_wday - 1;
		day = curTime - (diff+1)*86400;
	}else{
		day = time(&curTime);
	}
	
	for (int i = 0; i<=6; i++){
		day = day + 86400;
    for (it = _taskList.begin(); it != _taskList.end(); ++it) {
        time_t begin = it->getTaskBegin();
        if (isSameDay(day, begin)) {
            retList.add((*it));
        }
	}
    }
    return retList.getAll();
}

TaskList::TList TaskList::getAll() const {
    return _taskList;
}

void TaskList::loadTaskList(TList list) {
    _taskList = list;
}

int TaskList::totalTasks() const {
    return _taskList.size();
}

std::string TaskList::toString() const {
    std::ostringstream oss;
    constTaskIt it;
    for (it = _taskList.begin(); it != _taskList.end(); ++it) {
        oss << it->toString() << std::endl;
    }

    return oss.str();
}

bool TaskList::isSameDay(time_t time1, time_t time2) const {
    tm tmstruct1;
    localtime_s(&tmstruct1, &time1);
    std::ostringstream oss;
    oss << std::put_time(&tmstruct1, "%d/%m/%y");

    tm tmstruct2;
    localtime_s(&tmstruct2, &time2);
    std::ostringstream oss2;
    oss2 << std::put_time(&tmstruct2, "%d/%m/%y");

    return oss.str() == oss2.str();
}

bool TaskList::isEarlier(Task task1, Task task2) {
    time_t task1Time = task1.getTaskBegin();
    time_t task2Time = task2.getTaskBegin();
    double diff = difftime(task1Time, task2Time);
    if (diff < 0) {
        return true;
    }

    return false;
}

void TaskList::markDone(unsigned id){
    taskIt it;
    for (it = _taskList.begin(); it != _taskList.end(); ++it) {
        unsigned curId = it->getTaskID();

        if (foundTask(id, curId)) {
            it->markDone();
            break;
        }
    }
}

void TaskList::markUndone(unsigned id){
    taskIt it;
    for (it = _taskList.begin(); it != _taskList.end(); ++it) {
        unsigned curId = it->getTaskID();

        if (foundTask(id, curId)) {
            it->markUndone();
            break;
        }
    }
}


//Sorts tasks by date, in ascending order (earliest first)
void TaskList::sortByDate() {
    _taskList.sort(isEarlier);
}

//finding taskName from taskID
std::string TaskList::findTaskName(unsigned idActual) const{
	constTaskIt it;
	std::string taskName;
    for (it = _taskList.begin(); it != _taskList.end(); ++it) {
        unsigned curId = it->getTaskID();
        if (foundTask(idActual, curId)) {
			taskName = it->getTaskName();
            break;
        }
    }
	return taskName;
}

//finding taskDate from taskID
time_t TaskList:: findTaskDate(unsigned idActual) const{
	constTaskIt it;
	time_t taskTime;
	time (&taskTime);
    for (it = _taskList.begin(); it != _taskList.end(); ++it) {
        unsigned curId = it->getTaskID();
        if (foundTask(idActual, curId)) {
			taskTime = it->getTaskBegin();
            break;
        }
    }
	return taskTime;
}

Task TaskList::findTask(unsigned idActual) const{
	constTaskIt it;
    for (it = _taskList.begin(); it != _taskList.end(); ++it) {
        unsigned curId = it->getTaskID();
        if (foundTask(idActual, curId)) {
			return(*it);
        }
    }
}

bool TaskList::foundTask(unsigned idExpected, unsigned idActual) const {
    return idExpected == idActual;
}

void TaskList::replaceTask(taskIt pos, Task newTask) {
    _taskList.insert(pos, newTask);
    _taskList.erase(pos);
}