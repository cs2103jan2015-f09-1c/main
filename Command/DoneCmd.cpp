#include "DoneCmd.h"
#include "Storage.h"
#include "TaskList.h"
#include "MappingNumber.h"
#include <iostream>
#include <time.h>

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

	// finding task from the ID
	std :: string taskName;
	taskName = taskList.findTaskName(taskId);

	//finding the date of the task from the id
	time_t taskTime;
	taskTime = taskList.findTaskDate(taskId);
    //update storage
    storage->updateStorage(taskList);    

	selectedTasks = taskList.getDay(taskTime);
    
	doneObj.setHeaderText("done: " + taskName);
	doneObj.setTaskList(selectedTasks); // currently it will show all after marking the task is done
    return doneObj;
}
