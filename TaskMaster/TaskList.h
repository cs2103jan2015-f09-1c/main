#pragma once
#include <list>
#include "Task.h"

class TaskList {
public:
    TaskList(void);
    ~TaskList(void);
    
    typedef std::list<Task> TList;
    typedef std::list<Task>::iterator taskIt;
    typedef std::list<Task>::const_iterator constTaskIt;

    void add(Task task);
    void update(Task task);
    void remove(unsigned id);
    TList getDay(time_t day) const; //get tasks of a certain day
    TList getToday() const;
    TList getAll() const;
    void loadTaskList(TList list);
    int totalTasks() const;

    std::string toString() const;

private:
    TList _taskList;
    bool isSameDay(time_t time1, time_t time2) const;
    static bool isEarlier(Task task1, Task task2);
    void sortByDate();
    bool foundTask(unsigned idExpected, unsigned idActual) const;
    void replaceTask(taskIt pos, Task newTask);
};

