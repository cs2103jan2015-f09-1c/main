 #pragma once
#include <string>
#include "Task.h"
#include "TaskList.h"
#include "MappingNumber.h"

#define LENGTH  200
typedef struct Cal {
	int year;
	int month;
	int day;
	int wday;        //value 0-6 represents Sun,Mon,...,Sat
	int time;        //time format is 24hours. e.g. 0 = 12am, 800 = 8am, 1200 = 12pm, 2359 = 1159pm
    int endtime;
    std::string event; 
} CalEvent;

class Interpreter
{
private:
	static const size_t NUM_CHARS_VIEW;
	static const size_t NUM_CHARS_DONE;
	static const size_t NUM_CHARS_DELETE;
    
    // searchs "input" for first occurence of the sequence "pattern"
    // When pos is specified, the search only includes characters at or after position pos, 
    // ignoring any possible occurrences that include characters before pos.
    // This search is case insensitive and returns position of the first character of the first match.
    static size_t caseInsensitiveFind(std::string input, std::string pattern, size_t pos = 0);
    // returns true if the substring is found
	static bool searchSubStr(std::string keyword, Task task);

    static struct tm getToday();
    static bool isFloatingTask(std::string input);
    static bool isWithoutTimeTask(size_t posAt, size_t posFrom, size_t posTo);
    //input: year,yearDay
    //output: the date of a particular day in a year
    static void Monthday(int year, int yearDay, int *pMonth, int *pDay);    
    static std::string parseTaskName(std::string input);
    static CalEvent parseTime(std::string input,  size_t pos, size_t offset);
    static CalEvent parseNext(std::string input, size_t posNext);
    static CalEvent parseOn(std::string input, size_t posOn);
    static CalEvent parseFrom(std::string input, size_t posFrom);
    static CalEvent parseAt(std::string input, size_t posAt);
    static CalEvent parseTo(std::string input, size_t posTo);
    static CalEvent parseTomorrow();

	static int parse(std::string event, CalEvent *calEventOut);
	static int IsLeapYear(int year); //return = 1 means leap year
	static int month_days(int year, int month); //return number of days in a particular month
	static void wDaySearch(int year, int month, int day, int *wday); //output: wday:(0-6: Sun,Mon,....,Sat)
	static int parseNumber(std::string input, int numCmdChars);
	static int gettingTaskID(std::string input);
	static Task prepareTask(std::string input);
	static int ConvertStrtoNum (std::string str);

public:    
    static Task parseAddCmd(std::string detail);
    static Task parseEditCmd(std::string input);
    static std::string parseStoreCmd(std::string input);
    static int parseDelCmd(std::string input);
	static int parseDoneCmd(std::string input);
	static std:: string parseViewCmd(std::string input);
	static TaskList::TList parseSearchCmd(std::string input);
	static void tmConvert(CalEvent Event, time_t *eventTime);
	Interpreter(void);
	~Interpreter(void);
};
