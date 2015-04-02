#pragma once
#include "TaskList.h"

class TaskStub {
private:
    static int _secsInADay;
    static int _secsInHalfDay;
    static int _secsInAnHour;
    static time_t _9Mar723AM;
    static time_t _9Mar723PM;
    static time_t _10Mar723AM;
    static time_t _10Mar723PM;
    static time_t _11Mar723AM;
    static time_t _11Mar723PM;

    // given a type time_t, returns local time in the format
    // DD/MM/YY HH:MM AM
    static std::string timetToString(time_t timing);

public:
    TaskStub(void);
    ~TaskStub(void);
    // returns an arbitrary hard coded time 09/03/15 07:23 AM
    static time_t getSampleTime();

    // 9 March 15, undone, 07:23 AM
    static Task getSampleTask1();
	// 9 March 15, done
    static Task getSampleTask2();
    // 9 March 15, undone, 07:23 PM
    static Task getSampleTask3();
    // 10 March 15, undone, 07:23 AM
    static Task getSampleTask4();
    // 10 March 15, undone, 07:23 PM
    static Task getSampleTask5();
    // 11 March 15, done
    static Task getSampleTask6();
    // 11 March 15, done
    static Task getSampleTask7();
    // 11 March 15, undone, 07:23 AM
    static Task getSampleTask8();

    // returns a tasklist containing eight sample tasks with ids 1 to 8.
	// order after internal TaskList sorting: 1, 3, 2, 4, 5, 6, 7, 8
    // do not use this if you require tasks to adhere to
    // specific ranges of dates, for reasons such as equivalence 
    // partioning and boundary value analysis.
    static TaskList getLargeTaskList();

    // returns a tasklist containing only three sample tasks with ids 1, 3, 5
    static TaskList getSmallTaskList();
};

