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


UIObject ViewCmd::execute() {
    //get current tasks
    Storage* storage = Storage::getInstance();
    TaskList taskList = storage->getTaskList();
	std:: string header;
	

    //returns the day's tasks
    TaskList::TList wantedTasks;
    if(_detail == "all"){
		wantedTasks = taskList.getAll();
	}

    UIObject viewObj;
	if(!wantedTasks.empty()){
	viewObj.setTaskList(wantedTasks);
	} 
	else{
		viewObj.setHeaderText("There is no task!");
	}


	return viewObj;
}

