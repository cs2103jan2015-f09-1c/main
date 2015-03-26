#include "DeleteCmd.h"
#include "Storage.h"
#include "TaskList.h"
#include "MappingNumber.h"
#include <iostream>
#include <sstream>

DeleteCmd::DeleteCmd(void) {
}

DeleteCmd::~DeleteCmd(void) {
}

void DeleteCmd::prepareTask(Task task) {
    _task = task;
}

UIObject DeleteCmd::execute() {
    UIObject temp;
    MappingNumber *mapping = MappingNumber::getInstance();

    //get current tasks
    Storage* storage = Storage::getInstance();
    TaskList taskList = storage->getTaskList();

	//remove
	std::string taskToDel = _task.getTaskName();
		if (_task.getTaskID() == 0){
		int DelNum;
		std::stringstream convert(taskToDel);
		convert >> DelNum;
		unsigned taskId =  mapping->getTaskID(DelNum);
		taskList.remove(taskId);

		}
		else{
			taskList.remove(_task.getTaskID());
		}
    //update storage
    storage->updateStorage(taskList);    

    //return UI Object 
	temp.setHeaderText("Remaining tasks for that day: \n");
    temp.setTaskList(taskList.getToday());
    return temp;
}

UIObject DeleteCmd::undo() {
    UIObject undoMessage;
    //undo stuff
	//get current tasks
    Storage* storage = Storage::getInstance();
    TaskList taskList = storage->getTaskList();

    //set the taskid
    _task.setTaskID(storage->getNextID());

    //add the task
    taskList.add(_task);

    //update storage
    storage->updateStorage(taskList);    

    //returns the day's tasks
    TaskList::TList tasksThatDay;
    tasksThatDay = taskList.getDay(_task.getTaskBegin());

	//return UIObject
	undoMessage.setHeaderText("Undo successfully");
	undoMessage.setTaskList(tasksThatDay);

    return undoMessage;
}

