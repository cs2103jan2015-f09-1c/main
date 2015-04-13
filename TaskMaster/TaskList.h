//@Seow Yan Yi A0086626W
#pragma once
#include <list>
//@Seow Yan Yi A0086626W
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
	void markDone(unsigned id);
	void markUndone(unsigned id);

	Task findTask(unsigned idActual) const;
	TList getTomorrow() const;
	//given any time_t value, returns tasks which falls within that day
    TList getDay(time_t day) const; 
    TList getToday() const;
    TList getAll() const;
	TList getWeekly() const;
    void loadTaskList(TList list);
    int totalTasks() const;
    std::string toString() const;
	std::string toStringWithoutDate() const;

private:
    TList _taskList;
    bool isSameDay(time_t time1, time_t time2) const;
    static bool isEarlier(Task task1, Task task2);

	//Sorts tasks by date, in ascending order (earliest first)
    void sortByDate();
    bool foundTask(unsigned idExpected, unsigned idActual) const;
    void replaceTask(taskIt pos, Task newTask);
};
