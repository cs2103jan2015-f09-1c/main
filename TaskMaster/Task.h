#pragma once
#include <ctime> // time_t
#include <string>

class Task {
public:
    Task(void);
    ~Task(void);

    void setTaskName(std::string name);
    std::string getTaskName() const;

	// Tasks which do not have their begin times set are floating by default.
	// Tasks which have their begin times = 0 are also set to floating.
	// Nevertheless, the use of setFloating() method provides a clearer way to set a Task as floating.
	void setFloating();
	void setNotFloating();
    void setTaskWithoutTime();
    bool isFloating() const; 
	bool taskWithoutTime() const;

    std::string getDateStr() const;
    std::string getBeginStr() const;
    std::string getEndStr() const;

    time_t getTaskBegin() const;
    time_t getTaskEnd() const;

    void setTaskBegin(time_t begin);
    void setTaskEnd(time_t end);
    
    void markDone();
    void markUndone();
    bool isDone() const;

    unsigned getTaskID() const;
    void setTaskID(unsigned id);

    std::string toString() const;
	std::string toStringWithoutDate() const; // for testing purpose

private:
    unsigned _taskID;
    std::string _taskName;
    time_t _taskBegin;
    time_t _taskEnd;
    bool _isFloating;
    bool _isDone;
	bool _isWithoutTime;
};

