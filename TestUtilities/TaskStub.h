#pragma once
#include "TaskList.h"

class TaskStub {
private:
    // given a type time_t, returns local time in the format
    // DD/MM/YY HH:MM AM
    static std::string TaskStub::timetToString(time_t timing);
    // returns an arbitrary hard coded time 09/03/15 07:23 AM
    static time_t getSampleTime();
    static Task getSampleTask1();
    static Task getSampleTask2();
    static Task getSampleTask3();
    static Task getSampleTask4();

public:
    TaskStub(void);
    ~TaskStub(void);

    // returns a tasklist containing four sample tasks.
    // do not use this if you require tasks to adhere to
    // specific ranges of dates, for reasons such as equivalence 
    // partioning and boundary value analysis.
    static TaskList getSampleTaskList();

};

