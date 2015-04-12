#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include "TaskList.h"

class TaskStub {
private:
    static int _secsInADay;
    static int _secsInHalfDay;
    static int _secsInAnHour;
	static int _secsInThreeDays;
    static time_t _9Mar723AM;
    static time_t _9Mar723PM;
    static time_t _10Mar723AM;
    static time_t _10Mar723PM;
    static time_t _11Mar723AM;
    static time_t _11Mar723PM;
	static time_t _6Apr9AM;
	static time_t _7Apr9AM;
	static time_t _8Apr9AM;
	static time_t _9Apr9AM;
	static time_t _10Apr9AM;
	static time_t _12Apr9AM;
	static time_t _13Apr9AM;
	static time_t _14Apr9AM;
	static time_t _15Apr9AM;
	static time_t _16Apr9AM;
	static time_t _17Apr9AM;
	static time_t _19Apr9AM;
	static time_t _Today9AM;
	static time_t _Tomorrow9AM;

public:
    TaskStub(void);
    ~TaskStub(void);
    // given a type time_t, returns local time in the format
    // DD/MM/YY HH:MM AM
    static std::string timetToString(time_t timing);
    // returns an arbitrary hard coded time 09/03/15 07:23 AM
    static time_t getSampleTime();
	// returns an arbitrary hard coded time 13/04/15 09:00 AM
	static time_t getSampleTimeApr();
	static time_t getToday9AM();
    static std::string getCurrentDate();
    static std::string getTomorrowDate();

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
	 // 6 Apr 15, undone, 09:00 AM
	static Task getSampleTask9();
	 // 7 Apr 15, undone, 09:00 AM
	static Task getSampleTask10();
	 // 8 Apr 15, undone, 09:00 AM
	static Task getSampleTask11();
	 // 9 Apr 15, undone, 09:00 AM
	static Task getSampleTask12();
	 // 10 Apr 15, undone, 09:00 AM
	static Task getSampleTask13();
	 // 10 Apr 15, undone, 09:00 AM
	static Task getSampleTask14();
	 // 12 Apr 15, undone, 09:00 AM
	static Task getSampleTask15();
	 // 13 Apr 15, undone, 09:00 AM
	static Task getSampleTask16();
	 // 14 Apr 15, undone, 09:00 AM
	static Task getSampleTask17();
	 // 15 Apr 15, undone, 09:00 AM
	static Task getSampleTask18();
	 // 16 Apr 15, undone, 09:00 AM
	static Task getSampleTask19();
	 // 16 Apr 15, undone, 09:00 AM
	static Task getSampleTask20();
	 // 17 Apr 15, undone, 09:00 AM
	static Task getSampleTask21();
	 // 19 Apr 15, undone, 09:00 AM
	static Task getSampleTask22();
	static Task getSampleTask23();
	static Task getSampleTask24();

    // returns a tasklist containing eight sample tasks with ids 1 to 8.
	// order after internal TaskList sorting: 1, 3, 2, 4, 5, 6, 7, 8
    // do not use this if you require tasks to adhere to
    // specific ranges of dates, for reasons such as equivalence 
    // partioning and boundary value analysis.
    static TaskList getLargeTaskList();

    // returns a tasklist containing only three sample tasks with ids 1, 3, 5
    static TaskList getSmallTaskList();
	 // returns a tasklist containing only three sample tasks with ids from 9 to 22
	// Tasklist begins on 6 April 
	static TaskList getAprTaskList();
	static TaskList getCurrentTaskList();
};
