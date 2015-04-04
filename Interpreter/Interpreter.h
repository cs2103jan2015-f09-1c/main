 #pragma once
#include <string>
#include "Task.h"
#include "TaskList.h"
#include "MappingNumber.h"

#define LENGTH  200
typedef struct Cal
{
	int year;
	int month;
	int day;
	int wday;        //value 0-6 represents Sun,Mon,...,Sat
	int time;        //start time
	int endtime;     //end time
	std::string event;       //event
}CalEvent;

class Interpreter
{
private:
	static const size_t NUM_CHARS_VIEW;

	static bool search(std::string keyword, Task task);
	static int parse(std::string event, CalEvent *calEventOut);
	static int IsLeapYear(int year); //return = 1 means leap year
	static int month_days(int year, int month); //return number of days in a particular month
	static void wDaySearch(int year, int month, int day, int *wday); //output: wday:(0-6: Sun,Mon,....,Sat)
	static void Monthday(int year, int yearDay, int *pMonth, int *pDay); //input: year,yearDay
	//output: the date of a particular day in a year
	static Task prepareDelOrDoneCmd(std::string input, int);
	static int parseNumber(std::string input, int numCmdChars);

	static int ConvertStrtoNum (std::string str);

public:    
    static Task parseAddCmd(std::string input);
    static Task parseEditCmd(std::string input);
    static std::string parseStoreCmd(std::string input);

    static int parseDelOrDoneCmd(std::string input, int);

	static std:: string parseViewCmd(std::string input);
	static TaskList::TList parseSearchCmd(std::string input);
	static void tmConvert(CalEvent Event, time_t *starttime, time_t *endtime);
	Interpreter(void);
	~Interpreter(void);
};
