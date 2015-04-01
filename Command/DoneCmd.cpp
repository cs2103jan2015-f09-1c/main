#include "DoneCmd.h"
#include "Storage.h"
#include "TaskList.h"
#include "MappingNumber.h"
#include "InvalidIndex.h"
#include <iostream>
#include <time.h>
#include <assert.h>
#include "History.h"
#include "State.h"
#include "Logger.h"

DoneCmd::DoneCmd(void) {
}

DoneCmd::~DoneCmd(void) {
}

void DoneCmd::prepareIndex(int index) {
    _index = index;
}

void DoneCmd::verifyIndex(){
	MappingNumber *mapping = MappingNumber::getInstance();
	if (_index > mapping->countNode() && mapping->countNode() <= 0 ) {
        throw InvalidIndex("Invalid index. Please try again");
    }
}

std::string DoneCmd::markDone() {
    std::string retText;
	MappingNumber *mapping = MappingNumber::getInstance();
    
    //get current tasks
    Storage* storage = Storage::getInstance();
    TaskList taskList = storage->getTaskList();

    try { 
        verifyIndex();
    } catch(InvalidIndex& e) {
        retText = e.what();
    }

    return retText;
}

UIObject DoneCmd:: execute(){
	UIObject doneObj;
	MappingNumber *mapping = MappingNumber::getInstance();
	std:: string headerText;

	if (_index > mapping->countNode() && mapping->countNode() <= 0 ){	
		headerText = markDone();
	}else{
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

	Task _task;
	_task = taskList.findTask(taskId);
	recordInHistory(_task);
	selectedTasks = taskList.getDay(taskTime);

	headerText = "Done: " + taskName;
	}

	doneObj.setHeaderText(headerText);
	doneObj.setTaskList(selectedTasks);
    return doneObj;
}

void DoneCmd::recordInHistory(Task task) {
    State prevState; 
    prevState.recordTask (task);
    History *hist = History::getInstance();
    hist->saveState(prevState);
    hist->saveCommand(CommandType::DONE);
}

UIObject DoneCmd:: undo(){
	History *hist = History::getInstance();

	CommandType::Command prevCmd = hist->getPreviousCommand();
    assert(prevCmd == CommandType::DONE);

	State prevState = hist->getPreviousState();
	Task task = prevState.getTask();

	Storage* storage = Storage::getInstance();
    TaskList taskList = storage->getTaskList();

	//Removed the newly added task
	taskList.markUndone(task.getTaskID());
	storage->updateStorage(taskList);

	hist->clearHistory();

    UIObject undoMessage;

	undoMessage.setHeaderText("Undo successfully");
	undoMessage.setTaskList(selectedTasks);

    return undoMessage;
}