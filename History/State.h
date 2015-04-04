#pragma once
#include <string>
#include "Task.h"

class State {
public:
    State(void);
    ~State(void);
    void recordTask(Task task);
    Task getTask() const;
    void recordStorageLoc(std::string loc);
    std::string getStorageLoc() const;
	std::string toString() const;

private:
    Task _task;
    std::string _storageLoc;
};

