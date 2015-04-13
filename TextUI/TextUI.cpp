
//@Ratnawati Kwanditanto A0113736J
#define _CRT_SECURE_NO_WARNINGS
#include <vector>
#include <iostream>
#include <stdio.h>
#include <time.h>
#include <iomanip>
#include <stdlib.h>
#include <windows.h>
#include "TextUI.h"
#include "Color.h"
#include "boost/format.hpp"
#include "MappingNumber.h"

using boost::format;

HANDLE hStdOut;
CONSOLE_SCREEN_BUFFER_INFO csbi;
DWORD count;
DWORD cellCount;
DWORD coord;
COORD homeCoords = { 0, 0 };

const std::string TextUI::WELCOME_MSG = "Welcome to MyCal!"; 
const std::string TextUI::ENTER_CMD = "Enter command: ";
const std::string TextUI::UNSCHEDULED_DATE_BAR = 
	"[Unscheduled Tasks]           Description";
std::string TextUI::QUALIFIER_DATE_BAR = 
	"[%1%, %2% %3% %4% %5%] %|29t| Description";

std::string TextUI::DEFAULT_DATE_BAR = 
	"[%1%, %2% %3% %4%] %|29t| Description";
std:: string TextUI:: TIME_PRINT=
	"%1%. %2% %|30t|";
std:: string TextUI:: DONE_PRINT= " (done)";
std::string TextUI:: lastDate = "-1";
std::string TextUI:: nowDate = "0";
int TextUI:: counter;

struct tm TextUI::convertToLocalTime(const time_t &taskDate) {
    struct tm tmStruct;
    localtime_s(&tmStruct, &taskDate);
    return (tmStruct);
}

bool TextUI::isUnscheduled(const time_t &taskDate) {
	return taskDate == 0;
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

	if(localTime.tm_year == nowTime->tm_year) { //if the year is same
		if (localTime.tm_yday == nowTime->tm_yday){
			return "Today";
		}else 
		if(localTime.tm_yday == nowTime->tm_yday -1){
			return "Yesterday";
		}else 
		if(localTime.tm_yday == nowTime->tm_yday +1){
			return "Tomorrow";
		}
	}//if year is different
	else {
		//to check if yesterday, check whether localTime's is 31 Dec and nowTime is 1 Jan and localTime's year is nowTime's year - 1
		if(localTime.tm_year == nowTime->tm_year - 1 
			&& localTime.tm_mday == 31 && localTime.tm_mon == 11 
			&&  nowTime->tm_mday == 1 && nowTime->tm_mon == 0) {
			return "Yesterday";
		}

		//to check if tomorrow, check whether localTime's is 1 Jan and nowTime is 31 Dec and localTime's year is nowTime's year + 1
		if(localTime.tm_year == nowTime->tm_year + 1 
			&& localTime.tm_mday == 1 && localTime.tm_mon == 0 
			&&  nowTime->tm_mday == 31 && nowTime->tm_mon == 11) {
			return "Tomorrow";
		}
	}
	return "";
}

void TextUI::printDateBar(const time_t &taskDate) {
  
    if (isUnscheduled(taskDate)) {
	    std::cout << UNSCHEDULED_DATE_BAR << std::endl;
	}else {

		std::string qualifier = getQualifierName(taskDate);
	    std::string wkdayName = getWkDayName(taskDate);
	    std::string monthName = getMonthName(taskDate);
        struct tm localTime = convertToLocalTime(taskDate);
	    std::string day = std::to_string(localTime.tm_mday);

		hStdOut = GetStdHandle( STD_OUTPUT_HANDLE );
		Color:: TextColor (11, 0 ,hStdOut);

		std:: string year = std::to_string(localTime.tm_year + 1900);

		if(qualifier == ""){
			std::cout << format(DEFAULT_DATE_BAR) % wkdayName % monthName % day %year;
		}else {
			std::cout << format(QUALIFIER_DATE_BAR) % qualifier % wkdayName % monthName % day %year;
		}

	    std::cout << std::endl;
    }
}

void TextUI::printTasks(TaskList::TList tasks) {
    TaskList::taskIt it;
	counter = 1;

	nowDate = "0";
	lastDate = "-1";

	for (it = tasks.begin(); it != tasks.end(); ++it){
		prepareDatePrint(it);
		prepareDonePrint(it);
		std::cout << std::endl;
		counter++;
	}

	std::cout << std::endl;
}

void TextUI::prepareDatePrint(std::list<Task>::const_iterator it){
	
		if(it->isFloating()){
			nowDate = "0";
		}else {
			nowDate = it->getDateStr();
		}

		//if different date then print date bar
		if(lastDate != nowDate){
			std::cout << std::endl;
			printDateBar(it->getTaskBegin());
		}

		lastDate = nowDate;
}

std::string TextUI::prepareTimePrint(std::list<Task>::const_iterator it){
		std::string timeStart= "";
		std::string timeEnd= "";
		std::string timePrint= "";
	
		if(!isUnscheduled(it->getTaskBegin())){
			  timeStart = it->getBeginStr();
		}
		
		if(!isUnscheduled(it->getTaskEnd())){
			 timeEnd = it->getEndStr();
		}

		if(it->taskWithoutTime()){
			timePrint = "------------------";
		}
		else 
			if (it->isFloating()) {
			timePrint = "------------------";
		}else {
			timePrint = timeStart+" - "+timeEnd;
		}

		return timePrint;
}

void TextUI::prepareDonePrint(std::list<Task>::const_iterator it){
	std::string taskname;
	std::string  timePrint = prepareTimePrint(it); 

	if(it->isDone()){
			hStdOut = GetStdHandle( STD_OUTPUT_HANDLE );
			Color:: TextColor (8, 0 ,hStdOut);
			std::cout << format(TIME_PRINT) %counter %timePrint;
			taskname = it->getTaskName();
			std::cout << taskname;
			std::cout << DONE_PRINT;
		}else {
			hStdOut = GetStdHandle( STD_OUTPUT_HANDLE );
			Color:: TextColor (15, 0 ,hStdOut);
			std::cout << format(TIME_PRINT) %counter %timePrint;
			taskname = it->getTaskName();
			std::cout << taskname;
		}
}

void TextUI:: mappingNumber(TaskList::TList tasks){
	TaskList::taskIt it;
	MappingNumber* mapping = MappingNumber::getInstance();
	MappingNumber:: NODE node;
	
	int counter = 1;
    
	for (it = tasks.begin(); it != tasks.end(); ++it){
		node.displayNum = counter;
		node.taskID = it->getTaskID();
		mapping->addNode(node);
		counter++;
	}
}

void TextUI::printWelcomeMsg() {
	hStdOut = GetStdHandle( STD_OUTPUT_HANDLE );
	Color:: TextColor (11, 0 ,hStdOut);
	FillConsoleOutputAttribute(hStdOut, _rotl(0,11) , 80 * 50,homeCoords , &count);
	std::cout << WELCOME_MSG << std::endl << std:: endl;
}

void TextUI::printEnterCommand() {
	hStdOut = GetStdHandle( STD_OUTPUT_HANDLE );
	Color:: TextColor (14, 0 ,hStdOut);
	std::cout << ENTER_CMD;
}

std::string TextUI::getInput() {
	std::string userInput;
	Color:: TextColor (14, 0 ,hStdOut);
	std::getline(std::cin, userInput);
	return userInput;
}


void TextUI::showOutput(UIObject uiObj) {
	
    MappingNumber* mapping = MappingNumber::getInstance();

	hStdOut = GetStdHandle( STD_OUTPUT_HANDLE );
	Color:: TextColor (11, 0 ,hStdOut);
	std::cout << uiObj.getHeaderText() << std::endl;
	
	mapping->clearMappingNumber();
	printTasks(uiObj.getTaskList());
	mappingNumber(uiObj.getTaskList());
}

void TextUI:: clearScreen(){

  hStdOut = GetStdHandle( STD_OUTPUT_HANDLE );
  if (hStdOut == INVALID_HANDLE_VALUE){
	  return;
  }

  // Get the number of cells in the current buffer 
  if (!GetConsoleScreenBufferInfo( hStdOut, &csbi )){
	  return;
  }
  
  cellCount = csbi.dwSize.X *csbi.dwSize.Y;

  // Fill the entire buffer with spaces
  if (!FillConsoleOutputCharacter(
    hStdOut,
    (TCHAR) ' ',
    cellCount,
    homeCoords,
    &count
    )){
		return;
  }
  // Fill the entire buffer with the current colors and attributes
  if (!FillConsoleOutputAttribute(
    hStdOut,
    csbi.wAttributes,
    cellCount,
    homeCoords,
    &count
    )){
		return;
  }

  // Move the cursor home
  SetConsoleCursorPosition( hStdOut, homeCoords );
  
}


TextUI::TextUI(void) {
}


TextUI::~TextUI(void) {
}

