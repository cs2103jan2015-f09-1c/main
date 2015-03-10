#include "TaskList.h"
#include <sstream>

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
        oss << it->getTaskName() << std::endl;
        oss << it->getDateStr() << std::endl ;
        oss << it->getBeginStr() << " - ";
        oss << it->getEndStr() << std::endl << std::endl;
    }

    return oss.str();
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

//Sorts tasks by date, in ascending order (earliest first)
void TaskList::sortByDate() {
    _taskList.sort(isEarlier);
}

bool TaskList::foundTask(unsigned idExpected, unsigned idActual) const {
    return idExpected == idActual;
}

void TaskList::replaceTask(taskIt pos, Task newTask) {
    _taskList.insert(pos, newTask);
    _taskList.erase(pos);
}