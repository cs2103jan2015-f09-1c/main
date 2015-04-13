// TextUI Component is only responsible for:
// 1) displaying of messages and printing out tasks. 
// 2) Getting user input
// As much as possible, ordering of tasks and deciding what 
// header text to print is done by the Task Master.
//
// TextUI has no idea whether it is a add, edit or whatever. 
// It Just prints what is given to it.
//

///////////////////////////////////////////////////////////////////////////
///////////////// SAMPLE USER INTERFACE AND ITS COMPONENTS ////////////////
///////////////////////////////////////////////////////////////////////////
//
// Tasks due this week:      <---- THIS IS THE "HEADER TEXT"
//
// [Unscheduled Tasks]		Description						<--- DATE BAR
//
// 1.  ----------------	    comp club meeting			    <--- TASK
//
// [Today Fri Jan 1]		Description						<--- DATE BAR
//
// 2.  ----------------	    Remember to bring pencil	    <--- TASK [done]
// 3. [8:45am - 11:30am]    Brunch with Jane			    <--- TASK  
// 4. [12pm]			    Submit CS2103 CE2			    <--- TASK
//

#pragma once
#include <string>
#include "UIObject.h"

class TextUI
{
private:
	static std::string lastDate;
	static std::string nowDate;
	static int counter;

	static const std::string WELCOME_MSG;
	static const std::string ENTER_CMD;
	static const std::string UNSCHEDULED_DATE_BAR;
	static std::string QUALIFIER_DATE_BAR;
	static std::string DEFAULT_DATE_BAR;
	static std:: string NO_SCHEDULE;
	static std:: string TIME_PRINT;
	static std:: string DONE_PRINT;

    static struct tm convertToLocalTime(const time_t &taskDate); 
	static bool isUnscheduled(const time_t &taskDate);
	static std::string getWkDayName(const time_t &taskDate);
	static std::string getMonthName(const time_t &taskDate);
    static std::string getTimeName(const time_t &taskDate);
	static std::string getQualifierName(const time_t &taskDate);
	static void printDateBar(const time_t &taskDate);
	static void printTasks(TaskList::TList tasks);
	static void mappingNumber(TaskList::TList tasks);

public:
	static void printWelcomeMsg();
	static void printEnterCommand();
	static std::string getInput();
	static void showOutput(UIObject uiObj);
	static void clearScreen();
	static void prepareDatePrint(std::list<Task>::const_iterator taskIt);
	static void prepareDonePrint(std::list<Task>::const_iterator taskIt);
	static std::string prepareTimePrint(std::list<Task>::const_iterator taskIt);
	TextUI(void);
	~TextUI(void);
};

