#define _CRT_SECURE_NO_WARNINGS
#include "ViewCmd.h"
#include "Storage.h"
#include "TaskList.h"
#include <iostream>
#include <sstream>
#include "ViewType.h"
#include <time.h>

ViewCmd::ViewCmd(void) {
}

ViewCmd::~ViewCmd(void) {
}

void ViewCmd:: prepareDetail(std::string detail){
    _detail = detail;
}

time_t ViewCmd:: getDayPosition(int index){
	time_t curTime;
	time_t day;
	struct tm * timeinfo;
	int diff = 0;

	time (&curTime);
	timeinfo = localtime(&curTime);

	if(timeinfo->tm_wday < index){
		diff = index - timeinfo->tm_wday;
		day = curTime + diff*86400;
	}else 
	if(timeinfo->tm_wday > index){
		diff = index - timeinfo->tm_wday;
		day = curTime + diff*86400;
	}else{
		day = curTime;
	}

	return day;
}

void ViewCmd:: getSelectedTasks(){
	
	//get current tasks
    Storage* storage = Storage::getInstance();
    TaskList taskList = storage->getTaskList();

	//returns the day's tasks
	if(_detail == "all"){
		selectedTasks = taskList.getAll();
	} else
	if(_detail == "today"){
		selectedTasks = taskList.getToday();
	}else
	if(_detail == "tomorrow"){
		selectedTasks = taskList.getTomorrow();
	}else
	if(_detail == "weekly"){
		selectedTasks = taskList.getWeekly();
	}
	/*
	ViewType::View ViewType = ViewType::determineViewType(_detail);  
	 switch (ViewType) {
        case ViewType::SUNDAY: {
			time_t day = getDayPosition(0);
			selectedTasks = taskList.getDay(day);
		}
		case ViewType::MONDAY: {
			time_t day = getDayPosition(1);
			selectedTasks = taskList.getDay(day);
        }
		case ViewType::TUESDAY: {
			time_t day = getDayPosition(2);
			selectedTasks = taskList.getDay(day);
        }
		case ViewType::WEDNESDAY: {
			time_t day = getDayPosition(3);
			selectedTasks = taskList.getDay(day);
        }
		case ViewType::THURSDAY: {
			time_t day = getDayPosition(4);
			selectedTasks = taskList.getDay(day);
        }
		case ViewType::FRIDAY: {
			time_t day = getDayPosition(5);
			selectedTasks = taskList.getDay(day);
        }
		case ViewType::SATURDAY: {
			time_t day = getDayPosition(6);
			selectedTasks = taskList.getDay(day);
        }
		case ViewType::ALL: {
			selectedTasks = taskList.getAll();
        }
		case ViewType::TODAY: {
			selectedTasks = taskList.getToday();
        }
		case ViewType::TOMORROW: {
			selectedTasks = taskList.getTomorrow();
        }
		case ViewType::WEEKLY: {
			selectedTasks = taskList.getWeekly();
        }
		case ViewType::INVALID: {
		//	selectedTasks = NULL;
        }
		default :{
		//	selectedTasks = NULL;
		 }
	 }
	 */
}


UIObject ViewCmd::execute() {
	std:: string header;
	
	getSelectedTasks();
   
    UIObject viewObj;
	if(!selectedTasks.empty()){
		viewObj.setTaskList(selectedTasks);
	} else{
		viewObj.setHeaderText("There is no task!");
	}
	return viewObj;
}

