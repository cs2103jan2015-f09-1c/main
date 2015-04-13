//@Ratnawati Kwanditanto A0113736J
#include "DoneCmd.h"
#include "Storage.h"
#include "TaskList.h"
#include "MappingNumber.h"
#include <iostream>
#include <time.h>
#include <assert.h>
#include "History.h"
#include "State.h"
#include "MCLogger.h"

const std::string DoneCmd:: NO_MATCHING_TASK = "There is no matching task to be marked done.";
const std::string DoneCmd:: DONE_MESSAGE = "Done: "; 
const std::string DoneCmd:: UNDO_DONE_MESSAGE = " has been marked undone!";

DoneCmd::DoneCmd(void) {
}

DoneCmd::~DoneCmd(void) {
}

void DoneCmd::prepareTaskId(int _taskId) {
    taskId = _taskId;
}


UIObject DoneCmd:: execute(){
	UIObject doneObj;
	
	if (taskId == 0){
		doneObj.setHeaderText(NO_MATCHING_TASK);
	 }else 
	 if (taskId == -1){
		 std::string help = getHelp();
		 doneObj.setHeaderText(help);
	}else {
	//get current tasks
    Storage* storage = Storage::getInstance();
    TaskList taskList = storage->getTaskList();

	Task ActualTask = taskList.findTask(taskId);
	recordInHistory (ActualTask);

	taskList.markDone(taskId);
	storage->updateStorage(taskList);

	TaskList::TList tasksThatDay;
    tasksThatDay = taskList.getDay(ActualTask.getTaskBegin());
	
	doneObj.setHeaderText(DONE_MESSAGE + ActualTask.getTaskName());
	doneObj.setTaskList(tasksThatDay);
	}
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
	TaskList::TList tasksThatDay;
	tasksThatDay = taskList.getDay(task.getTaskBegin());

	undoMessage.setHeaderText(task.getTaskName() + UNDO_DONE_MESSAGE );
	undoMessage.setTaskList(tasksThatDay);

    return undoMessage;
}



std::string DoneCmd::getHelp() const {
	std::string help;

	std::string title = "***************** COMMAND HELP: DONE  *****************\n\n";

	std::string intro = "The done command allows you to mark done your task \n\n"; 

	std::string pt1 = "1. This command can be invoked by typing done [task number / task name] \n";
	pt1 = pt1 + "Example: done 1 \n";
	pt1 = pt1 + "         done meet mum \n";

	help = title + intro + pt1;

	return help;
}
