// TextUI Component is only responsible for:
// 1) displaying of messages and printing out tasks. 
// 2) Getting user input
// As much as possible, ordering of tasks and deciding what 
// header text to print is done by the Task Master.
//
// TextUI has no idea whether it is a add, edit or whatever. 
// It Just prints what is given to it.
//
//////////////////////////////////////////////////////////////////////////
///////////////// SAMPLE USER INTERFACE AND ITS COMPONENTS ////////////////
///////////////////////////////////////////////////////////////////////////
//
// Tasks due this week:      <---- THIS IS THE "HEADER TEXT"
//
// [Unscheduled Tasks] =================================    <--- DATE BAR
//
// 1.  ----------------	    comp club meeting			    <--- TASK
//
// [Today Fri Jan 1] ===================================    <--- DATE BAR
//
// 2.  ----------------	    Remember to bring pencil	    <--- TASK
// 3. [8:45am - 11:30am]    Brunch with Jane			    <--- TASK  
// 4. [12pm]			    Submit CS2103 CE2			    <--- TASK
//
// 

#define _CRT_SECURE_NO_WARNINGS
#include <vector>
#include <iostream>
#include <stdio.h>
#include <time.h>
#include "TextUI.h"
#include "boost/format.hpp"

using boost::format;

const std::string TextUI::WELCOME_MSG = "Welcome to MyCal!"; 
const std::string TextUI::HELP_MSG = "Helpppp";
const std::string TextUI::UNSCHEDULED_DATE_BAR = 
	"[Unscheduled Tasks] =================================";
std::string TextUI::QUALIFIER_DATE_BAR = 
	"[%1% %2% %3% %4%] ===================================";

std::string TextUI::DEFAULT_DATE_BAR = 
	"[%1% %2% %3%] =======================================";

struct tm TextUI::convertToLocalTime(const time_t &taskDate) {
    struct tm tmStruct;
    localtime_s(&tmStruct, &taskDate);
    return (tmStruct);
}

bool TextUI::isUnscheduled(const time_t &taskDate) {
    struct tm localTime = convertToLocalTime(taskDate);
	return (localTime).tm_year == 0;
}

std::string TextUI::getWkDayName(const time_t &taskDate) {
    struct tm localTime = convertToLocalTime(taskDate);
	switch(localTime.tm_wday) {
		case 0:
			return "Sun";
		case 1:
			return "Mon";
		case 2:
			return "Tue";
		case 3:
			return "Wed";
		case 4:
			return "Thu";
		case 5:
			return "Fri";
		case 6:
			return "Sat";
        default:
            return "Err";
	}
}

std::string TextUI::getMonthName(const time_t &taskDate) {
    struct tm localTime = convertToLocalTime(taskDate);
	switch(localTime.tm_mon) {
		case 0:
			return "Jan";
		case 1:
			return "Feb";
		case 2:
			return "Mar";
		case 3:
			return "Apr";
		case 4:
			return "May";
		case 5:
			return "Jun";
		case 6:
			return "Jul";
		case 7:
			return "Aug";
		case 8:
			return "Sep";
		case 9:
			return "Oct";
		case 10:
			return "Nov";
		case 11:
			return "Dec";
        default:
            return "Err"; //throw exception?
	}
}


std::string TextUI::getQualifierName(const time_t &taskDate) {
    struct tm localTime = convertToLocalTime(taskDate);
	
	time_t currentTime;
    time(&currentTime);
    struct tm * nowTime;
    nowTime = localtime (&currentTime);

	if(localTime.tm_year == nowTime->tm_year)	//if the year is same
	{
		if (localTime.tm_yday == nowTime->tm_yday)
		{
			return "Today";
		}
		else if(localTime.tm_yday == nowTime->tm_yday -1)
		{
			return "Yesterday";
		}
		else if(localTime.tm_yday == nowTime->tm_yday +1)
		{
			return "Tomorrow";
		}
	}
	else //if year is different
	{
		//to check if yesterday, check whether localTime's is 31 Dec and nowTime is 1 Jan and localTime's year is nowTime's year - 1
		if(localTime.tm_year == nowTime->tm_year - 1 
			&& localTime.tm_mday == 31 && localTime.tm_mon == 11 
			&&  nowTime->tm_mday == 1 && nowTime->tm_mon == 0)
		{
			return "Yesterday";
		}

		
		//to check if tomorrow, check whether localTime's is 1 Jan and nowTime is 31 Dec and localTime's year is nowTime's year + 1
		if(localTime.tm_year == nowTime->tm_year + 1 
			&& localTime.tm_mday == 1 && localTime.tm_mon == 0 
			&&  nowTime->tm_mday == 31 && nowTime->tm_mon == 11)
		{
			return "Tomorrow";
		}
	}
	return "";
}

std::string TextUI::getTimeName(const time_t &taskDate) {
    struct tm localTime = convertToLocalTime(taskDate);
	std::string timeString = "";
	std::string amPm = "";
	if(localTime.tm_hour >= 12)
	{
		if(localTime.tm_hour == 12)
		{
			timeString =  std::to_string(localTime.tm_hour);
			amPm = "pm";
		}
		else
		{
			timeString =  std::to_string(localTime.tm_hour-12);
			amPm = "pm";
		}
	}
	else
	{
		if(localTime.tm_hour == 0)
		{
			timeString =  "12";
			amPm = "am";
		}
		else
		{
			timeString =  std::to_string(localTime.tm_hour);
			amPm = "am";
		}
	}
	if(localTime.tm_min > 0)
	{
		timeString = timeString + ":" + std::to_string(localTime.tm_min);
	}
	timeString = timeString + amPm;
	return timeString;
	
}

void TextUI::printDateBar(const time_t &taskDate) {
  
    if (isUnscheduled(taskDate)) {
	    std::cout << UNSCHEDULED_DATE_BAR << std::endl << std::endl;

    } else {
		
		std::string qualifier = getQualifierName(taskDate);
	    std::string wkdayName = getWkDayName(taskDate);
	    std::string monthName = getMonthName(taskDate);
        struct tm localTime = convertToLocalTime(taskDate);
	    std::string day = std::to_string(localTime.tm_mday);
		if(qualifier == "")
		{
			std::cout << format(DEFAULT_DATE_BAR) % wkdayName % monthName % day;
		}
		else
		{
			std::cout << format(QUALIFIER_DATE_BAR) % qualifier % wkdayName % monthName % day;
		}
	    std::cout << std::endl << std::endl;
    }
}

void TextUI::printTasks(TaskList::TList tasks) {
    TaskList::taskIt it;
	 int counter = 1;
    
	std::string lastDate = "";
	for (it = tasks.begin(); it != tasks.end(); ++it){
	
		std::string nowDate = "";
		if(it->isFloating())
		{
			nowDate = "empty";
		}
		else
		{
			nowDate = it->getDateStr();
		}

		//if different date then print date bar
		if(lastDate != nowDate)
		{
			printDateBar(it->getTaskBegin());
		}
		lastDate = nowDate;

		std::string timeStart = "";
		
		if(!isUnscheduled(it->getTaskBegin()))
		{
			timeStart =  it->getBeginStr();
		}
		
		std::string timeEnd = "";
		if(!isUnscheduled(it->getTaskEnd() ))
		{
			timeEnd = it->getEndStr();
		}
		std::string timePrint = "";
		if(timeStart == "" && timeEnd == "")
		{
			timePrint = "----------------";
		}
		else if(timeEnd == "")
		{
			timePrint = "["+timeStart+"]";
		}
		else
		{
			timePrint = "["+timeStart+" - "+timeEnd+"]";
		}


		std::cout <<  counter << "." << '\t' << timePrint << '\t' << it->getTaskName() << std::endl;
	    counter++;
	}
	std::cout << std::endl;
}


void TextUI::printWelcomeMsg() {
	std::cout << WELCOME_MSG << std::endl;
	time_t curTime;
    time(&curTime);
//	printDateBar(curTime);
}

void TextUI::printHelp() {
	std::cout << HELP_MSG << std::endl;
}

std::string TextUI::getInput() {
	std::string userInput;
	std::cin >> userInput;
	return userInput;
}


void TextUI::showOutput(UIObject uiObj) {

	std::cout << uiObj.getHeaderText() << std::endl;
	printTasks(uiObj.getTaskList());
}

TextUI::TextUI(void) {
}


TextUI::~TextUI(void) {
}

