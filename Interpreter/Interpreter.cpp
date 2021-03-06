﻿#include "Interpreter.h"
#include "Storage.h"
#include <iostream>
#include <sstream>
#include <algorithm>
#include "MappingNumber.h"
#include <assert.h>
#include "StorageAlias.h"
#include "DoneAlias.h"
#include "DeleteAlias.h"
#include "SearchAlias.h"
#include "AddAlias.h"
#include "CommandType.h"
#include "MCLogger.h"
#include "TaskNotFoundException.h"
#include "InvalidInputException.h"

using namespace std; 
const size_t Interpreter::NUM_CHARS_DONE = 4;
const size_t Interpreter::NUM_CHARS_DELETE = 6;
//@author A0086626W
std::string Interpreter::getEditHelp() {
	std::string title = "***************** COMMAND HELP: EDIT  *****************\n\n";

	std::string intro = "The edit command allows you to edit a previously added task \n\n"; 

	std::string pt1 = "1. This command can be invoked by typing edit <task number> {:optional detail}\n";
    pt1 = pt1 + "2. Bring up the task number by using view or search.\n\n";
	pt1 = pt1 + "Optional detail:\n";
    pt1 = pt1 + ":time\tEdit time only.\n";
	pt1 = pt1 + ":name\tEdit name of your task only\n\n";

	pt1 = pt1 + "Example 1: view all\n";
	pt1 = pt1 + "edit 3 :name\n";
    pt1 = pt1 + "Input \"Your new task name\"\n\n";

	pt1 = pt1 + "Example 2: search cs2102 project\n";
	pt1 = pt1 + "edit 2\n";
    pt1 = pt1 + "Input \"ST2334 project :tomorrow :at 3pm\"\n";

	std::string help = title + intro + pt1;

	return help;
}

size_t Interpreter::caseInsensitiveFind(std::string input, std::string pattern, size_t pos) {
    std::transform(input.begin(), input.end(), input.begin(), ::tolower);
    std::transform(pattern.begin(), pattern.end(), pattern.begin(), ::tolower);
    return input.find(pattern, pos);
}

bool Interpreter::searchSubStr(std::string keyword, Task task) {
    std::transform(keyword.begin(), keyword.end(), keyword.begin(), ::tolower);
	std::string line = task.getTaskName();
    std::transform(line.begin(), line.end(), line.begin(), ::tolower);

	if (line.find(keyword) != std::string::npos){
		return true;
	} else {
		return false;
	}
}

//@author A0113856A
Task Interpreter::parseAddCmd(std::string detail) {
	MCLogger::log("Interpreter.cpp: add command");
	Task a;

	if (AddAlias::isHelp(detail)){
		int TaskId = -1;
		a.setTaskID (TaskId);
	} else {
		int flag;

		CalEvent EventOut;
		string event;
		const char *cal = detail.c_str();
		event.assign(cal);
		flag = parse(event, &EventOut);
		if (flag <= -1){
			throw InvalidInputException("Unrecognized time or date. Please check your input.");
		}
	
		time_t starttime, endtime;
		if (EventOut.year!=-1)
			tmConvert(EventOut, &starttime, &endtime);
		else{
			starttime = 0;
			endtime = 0;
		}
		a.setTaskBegin(starttime);
		a.setTaskEnd(endtime);
		a.setTaskName(EventOut.event);
	}
	return a;
}

Task Interpreter::parseEditCmd(std::string input) {
	MCLogger::log("Interpreter.cpp: edit command");
	int taskID; 
    std::string filtered = CommandType::filterOutCmd(input);
	if (DeleteAlias::isInteger(filtered) || !DeleteAlias::isHelp(filtered)){
		taskID = gettingTaskID(filtered);
	}
	else if (DeleteAlias::isHelp(filtered)){
		throw InvalidInputException(getEditHelp());
	}

    if (taskID == 0) {
        throw InvalidInputException("No matching tasks found.");
    }


    Storage *storage = Storage::getInstance();
    TaskList taskList = storage->getTaskList();
    Task toEdit = taskList.findTask(taskID);


	Task a = toEdit;
	CalEvent EventOut;

	cout << endl;
	cout << input << endl;

	const char *cal = input.c_str();

	size_t i = 5;
	size_t k = 0;
	char recch[4];
	while (i < strlen(cal)) {
		if (cal[i] >= '0' && cal[i] <= '9') {
			recch[k] = cal[i];
			k++;
		}
		i++;
	}

	int recID = atoi(recch);
	if (recID <= 0) {
		throw InvalidInputException("Invalid input, please check again");
	}

	char tempEvent[LENGTH];
	string curStr;
	int  posTime, posName;
	posTime = input.find("time", 0);
	posName = input.find("name", 0);

	if (posTime != -1){
        if (!toEdit.isFloating()) {
		    cout << "previous date:" << toEdit.getDateStr() << endl;
		    cout << "        begin:" << toEdit.getBeginStr() << endl;
		    cout << "          end:" << toEdit.getEndStr() << endl << endl;
        }
		cout << "please input new time:" << endl;

		cin.getline(tempEvent, LENGTH, '\n');
		curStr.assign(tempEvent, 0, strlen(tempEvent));

        std::string exitCheck = curStr;
        exitCheck.erase(std::remove(exitCheck.begin(), exitCheck.end(), ' '), exitCheck.end());
        if (caseInsensitiveFind(exitCheck, ":exit") != string::npos) {
            throw InvalidInputException("Edit canceled.");
        }

		parse(curStr, &EventOut);
		time_t startt, endt;
		tmConvert(EventOut, &startt, &endt);
		toEdit.setTaskBegin(startt);
		toEdit.setTaskEnd(endt);
		cout << "    new date:" << toEdit.getDateStr() << endl;
		cout << "       begin:" << toEdit.getBeginStr() << endl;
		cout << "         end:" << toEdit.getEndStr() << endl << endl;
		a = toEdit;
	}
	else if (posName != -1) {
		cout << "previous name:" << toEdit.getTaskName() << endl;
		cout << "please input new name:" << endl;

		cin.getline(tempEvent, LENGTH, '\n');
		curStr.assign(tempEvent, 0, strlen(tempEvent));

        std::string exitCheck = curStr;
        exitCheck.erase(std::remove(exitCheck.begin(), exitCheck.end(), ' '), exitCheck.end());
        if (caseInsensitiveFind(exitCheck, ":exit") != string::npos) {
            throw InvalidInputException("Edit canceled.");
        }
		cout << "    new name: " << curStr << endl;
		toEdit.setTaskName(curStr);
		a = toEdit;
	} else {
		cout << "previous event:" << toEdit.getTaskName() << endl;
        if (!toEdit.isFloating()) {
		    cout << "previous date:" << toEdit.getDateStr() << endl;
		    cout << "        begin:" << toEdit.getBeginStr() << endl;
		    cout << "          end:" << toEdit.getEndStr() << endl << endl;
        }

		cout << "please input new event:" << endl;
		cin.getline(tempEvent, LENGTH, '\n');
		curStr.assign(tempEvent, 0, strlen(tempEvent));

        std::string exitCheck = curStr;
        exitCheck.erase(std::remove(exitCheck.begin(), exitCheck.end(), ' '), exitCheck.end());
        if (caseInsensitiveFind(exitCheck, ":exit") != string::npos) {
            throw InvalidInputException("Edit canceled.");
        }

		parse(curStr, &EventOut);
		time_t startt, endt;
		if (EventOut.year!=-1)
			tmConvert(EventOut, &startt, &endt);
		else{
			startt = 0;
			endt = 0;
		}

        // if no time is entered, do not change the time
        if (startt != 0) {
            toEdit.setTaskBegin(startt);
            toEdit.setTaskEnd(endt);
        }

		toEdit.setTaskName(EventOut.event);
		a = toEdit;
	}

	return a;
}

//@author A0086626W
std::string Interpreter::parseStoreCmd(std::string input) {    
    if (StorageAlias::isGetLocation(input)) { 
        return "getLocation";
    } else if (StorageAlias::isHelp(input)) {
		return "help";
	}

	// take the entire original input as new storage location to be changed
	// if it is neither "getLocation" nor "help".
    return input;
}

//@author A0113955A
int Interpreter::parseDelCmd(std::string input){
	int TaskId; 
	if (DeleteAlias::isInteger(input) || !DeleteAlias::isHelp(input)){
		TaskId = gettingTaskID(input);
	} else if (DeleteAlias::isHelp(input)){
		TaskId = -1;
	}
	return TaskId;
}
//@author A0113736J
int Interpreter::parseDoneCmd(std::string input){
	int TaskId;

	 if (DoneAlias::isInteger(input) || !DoneAlias::isHelp(input) ) { 
		TaskId = gettingTaskID(input);
    } else if (DoneAlias::isHelp(input)) {
		TaskId = -1;
	}
	return TaskId;
}


std::string Interpreter::parseViewCmd(std::string input){
	std:: string detail;
	detail = input;
	return detail;
}

//@author A0113955A
TaskList::TList Interpreter::parseSearchCmd (std::string input){
	MCLogger::log("Interpreter.cpp: parse search command");
	Storage *storage = Storage::getInstance();
	TaskList tasklist = storage->getTaskList();
	TaskList::TList list = tasklist.getAll();
	TaskList::TList foundTaskList;
	TaskList::taskIt it;

	if (SearchAlias::isHelp(input)){
		Task task;
		task.setTaskID(-1);
			foundTaskList.push_back(task);
	} else{
		for (it = list.begin(); it != list.end(); ++it) {
			Task _task = *it;
			if (searchSubStr(input, _task)) {
				foundTaskList.push_back(_task);
			}
		}
	}
	if (foundTaskList.empty()){
		Task task;
		task.setTaskID (0);
		foundTaskList.push_back(task);
	}
	return foundTaskList;
}

Interpreter::Interpreter(void) {
}

Interpreter::~Interpreter(void) {
}


//@author A0113856A
int Interpreter::parse(string event, CalEvent *calEventOut) {
	char week[7][10] = { "sun", "mon", "tues", "wed", "thur", "fri", "sat" };
	int posOn, posAt, posTmr1, posTmr2, posNext, posFrom, posEvent;
	size_t i, j, k;
	CalEvent curEvent;

	curEvent.year = -1;
	curEvent.month = -1;
	curEvent.day = -1;
	curEvent.wday = -1;
	curEvent.time = 800;
	curEvent.endtime = 1000;
	curEvent.event = "\0";

	//get time of "today"
	time_t rawtime;
	struct tm  timeinfo;
	time(&rawtime);
	localtime_s(&timeinfo, &rawtime);
	const char *cal = event.c_str();

	string cureve;
	posEvent = event.find(":", 0);
	if (posEvent != -1)
		cureve.assign(cal, 0, posEvent);
	else
		cureve.assign(cal, 0, strlen(cal));
	const char *cheve = cureve.c_str();
	curEvent.event = cureve;    

    if (posEvent != -1) {
        event.erase(std::remove(event.begin() + posEvent, event.end(), ' '), event.end());
    }
    
    cal = event.c_str();

	//deal with "next" in a command
	posNext = caseInsensitiveFind(event, ":next");
	if (posNext != -1){
		i = posNext + 5;
		k = 0;
		char weekx[10]; 
		strcpy_s(weekx, "\0");

        while (i<strlen(cal)){
			if (cal[i] >= 'A' && cal[i] <= 'Z' || cal[i] >= 'a' && cal[i] <= 'z') { 
				weekx[k] = cal[i];
				k++;
			}
			else if (cal[i] == ' ') { 
				if (k != 0) break;
			}
			else {
				break;
			}
			i++;
		}
		string strweek;
		strweek.assign(weekx, 0, strlen(weekx)); 
        std::transform(strweek.begin(), strweek.end(), strweek.begin(), ::tolower);
        bool foundDay = false;
		for (i = 0; i<7; i++){
			if (strweek.find(week[i], 0) != -1) {
                foundDay = true;
                break;
            }
		}
		if (foundDay == false) {
            throw InvalidInputException("Unrecognized day. Please check your input.");
        }

		int yday, year, wday, nextwday;
		year = timeinfo.tm_year + 1900;
		yday = timeinfo.tm_yday + 1;
		wday = timeinfo.tm_wday;
		assert(wday >= 0);
		nextwday = 6 - wday + i + 1;
		if (yday <= 365 - nextwday){
			int pMonth, pDay;
			Monthday(year, yday + nextwday, &pMonth, &pDay);
			curEvent.year = year;
			curEvent.month = pMonth;
			curEvent.day = pDay;
		}
		else{
			int pMonth, pDay;
			Monthday(year + 1, yday + nextwday - 365, &pMonth, &pDay);     
            curEvent.year = year + 1;			
            curEvent.month = pMonth;
            curEvent.day = pDay;            						
		}
	}

	//deal with "from" in a command
	posFrom = caseInsensitiveFind(event, ":from");
	if (posFrom != -1){
		i = posFrom + 5;
		k = 0;
		j = 0;
		char tmch[2][10], apm[2][5];
		int  tim[2];
		int num = 0;
		strcpy_s(apm[0], "am");
		strcpy_s(apm[1], "am");
		assert(apm[1] != " ");

        bool toFound = false;
		while (i<strlen(cal)) {
			if (cal[i] >= '0' && cal[i] <= '9') {
				tmch[num][k] = cal[i];
				k++;
			}
			else if (cal[i] == 'a' || cal[i] == 'A' || cal[i] == 'p' || cal[i] == 'P'||
                cal[i] == 'm' || cal[i] == 'M') {
				apm[num][j] = cal[i];
				j++;
			}
			else if (cal[i] == 't' || cal[i] == 'T' || cal[i] == '-') { // check :to
                toFound = true;
				k = 0;
				j = 0;
				tim[num] = atoi(tmch[num]);
				num++;
			}
			i++;
		}
		tim[num] = atoi(tmch[num]);
		for (int ii = 0; ii<2; ii++) {
			if (strcmp(apm[ii], "pm") == 0){  
				if (tim[ii]>100) {
					tim[ii] = tim[ii] + 1200;
                } else {
                    tim[ii] = tim[ii] + 12;
                }
			}
			if (tim[ii]<100) {
                tim[ii] = tim[ii] * 100;
            }
		}
		curEvent.year = timeinfo.tm_year + 1900;
		curEvent.month = timeinfo.tm_mon + 1;
		curEvent.day = timeinfo.tm_mday;
		curEvent.time = tim[0];
        if (!toFound) {
            curEvent.endtime = curEvent.time + 200;
        } 
        else {
		    curEvent.endtime = tim[1];
        }
	}

	//deal with "to" in a command
    // if there's only "to" without "from"
	int posTo = caseInsensitiveFind(event, ":to");
	if (posTo != -1 && posFrom == -1 && cal[posTo+3] <= '9' && cal[posTo+3] >= '1'){
		i = posTo + 3;
		k = 0;
		j = 0;
		char tmch[2][10], apm[2][5];
		int  tim[2];
		int num = 0;
		strcpy_s(apm[0], "am");
		strcpy_s(apm[1], "am");

        bool toFound = false;
		while (i<strlen(cal)) {
			if (cal[i] >= '0' && cal[i] <= '9') {
				tmch[num][k] = cal[i];
				k++;
			}
			else if (cal[i] == 'a' || cal[i] == 'A' || cal[i] == 'p' || cal[i] == 'P'||
                cal[i] == 'm' || cal[i] == 'M') {
				apm[num][j] = cal[i];
				j++;
			}

			i++;
		}
		tim[num] = atoi(tmch[num]);
		for (int ii = 0; ii<2; ii++) {
			if (strcmp(apm[ii], "pm") == 0){  
				if (tim[ii]>100) {
					tim[ii] = tim[ii] + 1200;
                } else {
                    tim[ii] = tim[ii] + 12;
                }
			}
			if (tim[ii]<100) {
                tim[ii] = tim[ii] * 100;
            }
		}
		curEvent.year = timeinfo.tm_year + 1900;
		curEvent.month = timeinfo.tm_mon + 1;
		curEvent.day = timeinfo.tm_mday;
		curEvent.endtime = tim[0];
        curEvent.time = curEvent.endtime - 200;
	}

	//deal with "on" in a command
	posOn = caseInsensitiveFind(event, ":on"); 
	if (posOn != -1)	{
		i = posOn + 3;
		k = 0;
		char dat[3][5];
		int dmy[3];
		int num = 0;

		while (i<strlen(cal)) {    
            if (num == 2 && k == 0 && ((strlen(cal) - i) < 2 ||(strlen(cal) - i) == 3)) {
                // year has 0, 1 or 3 digits
                throw InvalidInputException("Unrecognized year. Please check your input.");
            }        

			if (cal[i] >= '0' && cal[i] <= '9') {
				dat[num][k] = cal[i];
				k++;
			}
			else if (cal[i] == '/' || cal[i] == '\\' || cal[i] == '.') {
				k = 0;
				num++;
			}
			else {
				if (num != 2) {
					i++;
					continue;
				}
				else {
					break;
                }
			}
			i++;
		}

		for (i = 0; i<3; i++) {
			dmy[i] = atoi(dat[i]);
        }

		curEvent.year = dmy[2];
		curEvent.month = dmy[1];
		curEvent.day = dmy[0];

		if (curEvent.month>12 || curEvent.month <= 0 || curEvent.day>31 || curEvent.day <= 0)
			return -1;
	}

	//deal with "at" in a command
	posAt = caseInsensitiveFind(event, ":at"); 
	if (posAt != -1 && posFrom == -1){
		i = posAt + 3;
		k = 0;
		j = 0;
		char tm[10], apm[3];
		int tmm;
		strcpy_s(apm, "am");
		while (i<strlen(cal)) {
			if (cal[i] >= '0' && cal[i] <= '9') {
				tm[k] = cal[i];
				k++;
			}
			else if (cal[i] == 'a' || cal[i] == 'p' || cal[i] == 'm') {
				apm[j] = cal[i];
				j++;
			}
			else if (j >= 2) 
				break;
			i++;
		}

		tmm = atoi(tm);
		if (strcmp(apm, "pm") == 0){
			if (tmm>100)
				tmm = tmm + 1200;
			else
				tmm = tmm + 12;
		}
		if (tmm<100) tmm = tmm * 100;
		curEvent.time = tmm;
		curEvent.endtime = curEvent.time + 200;
		if (posOn == -1){
			curEvent.year = timeinfo.tm_year + 1900;
			curEvent.month = timeinfo.tm_mon + 1;
			curEvent.day = timeinfo.tm_mday;
		}
		if (tmm>2400)  
			return -1;

	}

	//deal with "tomorrow" in a command
	posTmr1 = caseInsensitiveFind(event, ":tmr"); 
    if (posTmr1 == string::npos && posOn == -1) {
        posTmr1 = caseInsensitiveFind(event, ":tom"); 
    }
	posTmr2 = caseInsensitiveFind(event, ":tomorrow"); 
	if (posTmr1 != -1 || posTmr2 != -1 && posOn == -1){
		int yday, year;
		year = timeinfo.tm_year + 1900;
		yday = timeinfo.tm_yday + 1;
		if (yday == 365){
			curEvent.year = year + 1;
			curEvent.month = 1;
			curEvent.day = 1;
		} else {
			int pMonth, pDay;
			Monthday(year, yday + 1, &pMonth, &pDay);
			curEvent.year = year;
			curEvent.month = pMonth;
			curEvent.day = pDay;
		}
	}

	wDaySearch(curEvent.year, curEvent.month, curEvent.day, &curEvent.wday);
	*calEventOut = curEvent;
	return 1;
}

void Interpreter::tmConvert(CalEvent Event, time_t *starttime, time_t *endtime) {
	int year, mon, day, tim1, tim2;

	year = Event.year;
	mon = Event.month - 1;
	day = Event.day;
	tim1 = Event.time;
	tim2 = Event.endtime;

    if (year > 2200 || year < 1971) {
        throw InvalidInputException("Sorry, the date you entered is out of range");
    }

    struct tm startTm;
    startTm.tm_hour = tim1 / 100;
    startTm.tm_min = tim1 % 100;
    startTm.tm_sec = 0;
    startTm.tm_mday = day;
    startTm.tm_mon = mon;
    startTm.tm_year = (year - 1900);
    time_t start = mktime (&startTm);

    struct tm endTm;
    endTm.tm_hour = tim2 / 100;
    endTm.tm_min = tim2 % 100;
    endTm.tm_sec = 0;
    endTm.tm_mday = day;
    endTm.tm_mon = mon;
    endTm.tm_year = (year - 1900);
    time_t end = mktime (&endTm);


    // if start time earlier than end time, shift end time forward by a day
    if (start < end) {
       end += 60 * 60 * 24;
    }

    *starttime = start;
    *endtime = end;
 }

int Interpreter::IsLeapYear(int year)
{
	if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))
		return 1;
	else
		return 0;
}
//return the number of days in a particular month of year
int Interpreter::month_days(int y, int m)
{
	int mon_day[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

	if (IsLeapYear(y) && m == 2)
		return 29;
	else
		return(mon_day[m - 1]);
}

void Interpreter::wDaySearch(int year, int month, int day, int *wday)
{
	int c = 0;
	float s;
	int m;
	for (m = 1; m<month; m++)
		c = c + month_days(year, m);
	c = c + day;
	s = year - 1 + (float)(year - 1) / 4 + (float)(year - 1) / 100 + (float)(year - 1) / 400 - 40 + c;
	*wday = (int)s % 7;
}


void Interpreter::Monthday(int year, int yearDay, int *pMonth, int *pDay)
//input: year,yearDay: year & nth day in a year
//output: pMonth,pDay: month day
{
	int dec;
	if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))  dec = 0;
	else dec = 1;
	if (yearDay >= 1 && yearDay <= 31) 	{
		*pMonth = 1;
		*pDay = yearDay;
	}
	else if (yearDay >= 32 && yearDay <= 60 - dec) {
		*pMonth = 2;
		*pDay = yearDay - 31;
	}
	else if (yearDay >= 61 - dec && yearDay <= 91 - dec){
		*pMonth = 3;
		*pDay = yearDay - (60 - dec);
	}
	else if (yearDay >= 92 - dec && yearDay <= 121 - dec){
		*pMonth = 4;
		*pDay = yearDay - (91 - dec);
	}
	else if (yearDay >= 122 - dec && yearDay <= 152 - dec){
		*pMonth = 5;
		*pDay = yearDay - (121 - dec);
	}
	else if (yearDay >= 153 - dec && yearDay <= 182 - dec){
		*pMonth = 6;
		*pDay = yearDay - (152 - dec);
	}
	else if (yearDay >= 183 - dec && yearDay <= 212 - dec){
		*pMonth = 7;
		*pDay = yearDay - (182 - dec);
	}
	else if (yearDay >= 214 - dec && yearDay <= 244 - dec){
		*pMonth = 8;
		*pDay = yearDay - (213 - dec);
	}
	else if (yearDay >= 245 - dec && yearDay <= 274 - dec){
		*pMonth = 9;
		*pDay = yearDay - (244 - dec);
	}
	else if (yearDay >= 275 - dec && yearDay <= 305 - dec){
		*pMonth = 10;
		*pDay = yearDay - (274 - dec);
	}
	else if (yearDay >= 306 - dec && yearDay <= 335 - dec){
		*pMonth = 11;
		*pDay = yearDay - (305 - dec);
	}
	else if (yearDay >= 336 - dec && yearDay <= 366 - dec) {
		*pMonth = 12;
		*pDay = yearDay - (335 - dec);
	}

}

//@author A0113955A
Task Interpreter::prepareTask(std::string input) {
    //std::string taskToDel = input.substr(lengthCommand);
    Storage *storage = Storage::getInstance();
    TaskList tasklist = storage->getTaskList();
    TaskList::TList list = tasklist.getAll();
    TaskList::taskIt it;

	int _size = input.size();
	for (int i=0; i<_size; i++){
		if (isdigit(input[i])){
				Task _task;
				_task.setTaskName(input);
				_task.setTaskID(0);
				return _task;
		}
		else{
    for (it = list.begin(); it != list.end(); ++it) {
        Task task = *it;
        if (searchSubStr(input, task)) {
            return task;
		}
	}
		}
	}
    //else, throw excpetion
    Task a;
    return a;

}

//@author A0113955A
int Interpreter::ConvertStrtoNum(std::string str){
	int integer;
	std::stringstream convert (str);
	convert >> integer;

	if (convert.fail()){
		integer = 0;
	}
	else{
		convert >> integer;
	}
	return integer;
}

//@author A0113955A
int Interpreter::gettingTaskID(std::string input){
	MappingNumber *mapping = MappingNumber::getInstance();
	Task _task = prepareTask(input);
	std::string taskToDel = _task.getTaskName();
	int TaskId;
	int integer;
	int ID = _task.getTaskID();
	if (ID == 0){
		integer = ConvertStrtoNum (taskToDel);
		if (integer == 0){
			TaskId = 0;
		}
		else{
			int count = mapping->countNode ();
			if(integer > count){
				TaskId = 0;
			}
			else{
				TaskId = mapping->getTaskID(integer);
			}
		}
	}
	else if (ID !=0){
		TaskId = ID;
	}
	return TaskId;
}