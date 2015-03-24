#include "ViewCmd.h"
#include "Storage.h"
#include "TaskList.h"
#include <iostream>

ViewCmd::ViewCmd(void) {
}

ViewCmd::~ViewCmd(void) {
}

void ViewCmd:: prepareDetail(std::string detail){
    _detail = detail;
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
	}
	// havent made function for other types
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

