#include "DoneCmd.h"
#include "Storage.h"
#include "TaskList.h"
#include "MappingNumber.h"
#include <iostream>

DoneCmd::DoneCmd(void) {
}

DoneCmd::~DoneCmd(void) {
}

void DoneCmd::prepareIndex(int index) {
    _index = index;
}

UIObject DoneCmd:: execute(){
	UIObject doneObj;
	MappingNumber *mapping = MappingNumber::getInstance();
    
    //get current tasks
    Storage* storage = Storage::getInstance();
    TaskList taskList = storage->getTaskList();

	//before execution, we generate mapping number first
	unsigned taskId =  mapping->getTaskID(_index);
	
	//mark done
	taskList.markDone(taskId);

    //update storage
    storage->updateStorage(taskList);    

    
	//doneObj.setHeaderText();
	doneObj.setTaskList(taskList.getAll()); // currently it will show all after marking the task is done
    return doneObj;
}
