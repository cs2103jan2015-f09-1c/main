#include "DeleteCmd.h"
#include "Storage.h"
#include "TaskList.h"
#include "MappingNumber.h"
#include <iostream>
#include <sstream>
#include <assert.h>
#include "InvalidFilePathException.h"
#include "Shlwapi.h" // PathFileExists
#include "History.h"
#include "State.h"
#include "Logger.h"

DeleteCmd::DeleteCmd(void) {
}

DeleteCmd::~DeleteCmd(void) {
}

void DeleteCmd::prepareTask(Task task) {
    _task = task;
}

void DeleteCmd::recordInHistory(Task task) {
    State prevState; 
    prevState.recordTask (task);
    History *hist = History::getInstance();
    hist->saveState(prevState);
    hist->saveCommand(CommandType::DEL);
}

bool DeleteCmd::Delete (Task _task){

	MappingNumber *mapping = MappingNumber::getInstance();
	unsigned taskId;
	std::string taskToDel = _task.getTaskName();
	if (_task.getTaskID() == 0){
		int DelNum;
		std::stringstream convert(taskToDel);
		if(! (convert >> DelNum))
		{
			return false;
		}
		else{
		convert >> DelNum;
		int count = mapping->countNode ();
		if (DelNum > count ){
			return false;
		}
		else{
		taskId = mapping->getTaskID(DelNum);
		return true;
		}
		}
	}
		else{
			return true;
		}
}

UIObject DeleteCmd::execute() {
  UIObject temp;

    //get current tasks
    Storage* storage = Storage::getInstance();
    TaskList taskList = storage->getTaskList();
	unsigned taskId;
	if (!(Delete(_task))){
		temp.setHeaderText("There is no matching task to be deleted. \n");
	}
	else{
	taskList.remove(_task.getTaskID());
	storage->updateStorage(taskList);

	recordInHistory (_task);

	TaskList::TList tasksThatDay;
    tasksThatDay = taskList.getDay(_task.getTaskBegin());

    temp.setTaskList(tasksThatDay);
	if (tasksThatDay.empty()){
		temp.setHeaderText("No more tasks for that day! \n");
	}
	else{
		temp.setHeaderText("Remaining tasks for that day: \n");
	}
	}
	 //return UI Object 
	 return temp;
}


UIObject DeleteCmd::undo() {

	History *hist = History::getInstance();

	CommandType::Command prevCmd = hist->getPreviousCommand();
    assert(prevCmd == CommandType::DEL);

	State prevState = hist->getPreviousState();
	Task task = prevState.getTask();

	Storage* storage = Storage::getInstance();
    TaskList taskList = storage->getTaskList();

	task.setTaskID(storage->getNextID());
	taskList.add(_task);

	storage->updateStorage(taskList);    

	hist->clearHistory();

    UIObject undoMessage;
  
    TaskList::TList tasksThatDay;
    tasksThatDay = taskList.getDay(_task.getTaskBegin());

	//return UIObject
	undoMessage.setHeaderText("Undo successfully");
	undoMessage.setTaskList(tasksThatDay);

    return undoMessage;
}

