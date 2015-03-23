#include "DoneCmd.h"
#include "Storage.h"
#include "TaskList.h"
#include "RetrieveTaskID.h"
#include <iostream>

DoneCmd::DoneCmd(void) {
}

DoneCmd::~DoneCmd(void) {
}

void DoneCmd::prepareIndex(int index) {
    _index = index;
}

UIObject DoneCmd:: execute(){
	UIObject temp;
	RetrieveTaskID retrieve;
    
    //get current tasks
    Storage* storage = Storage::getInstance();
    TaskList taskList = storage->getTaskList();
	
	
	retrieve.findTaskID(_index, temp.getTaskList());
	// retrieve.getSelectedTaskID();
	
	//std:: cout << "r : " << retrieve.getSelectedTaskID() << std::endl;


    //return UI Object 
	temp.setHeaderText("in progress");
   // temp.setTaskList();
    return temp;
}
