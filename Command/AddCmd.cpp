#include "AddCmd.h"
#include "Storage.h"
#include "TaskList.h"
#include <assert.h>
#include "InvalidFilePathException.h"
#include "Shlwapi.h" // PathFileExists
#include "History.h"
#include "State.h"
#include "MCLogger.h"

AddCmd::AddCmd(void) {
}


AddCmd::~AddCmd(void) {
}

void AddCmd::prepareTask(Task task) {
    _task = task;
}

void AddCmd::recordInHistory(Task task) {
    State prevState; 
    prevState.recordTask (task);
    History *hist = History::getInstance();
    hist->saveState(prevState);
    hist->saveCommand(CommandType::ADD);
}


UIObject AddCmd::execute() {
    //get current tasks
    Storage* storage = Storage::getInstance();
    TaskList taskList = storage->getTaskList();

    //set the taskid
    _task.setTaskID(storage->getNextID());

    //add the task
    taskList.add(_task);

    //update storage
    storage->updateStorage(taskList);    

	recordInHistory (_task);

    //returns the day's tasks
    TaskList::TList tasksThatDay;
    tasksThatDay = taskList.getDay(_task.getTaskBegin());

    UIObject addObj;
    addObj.setHeaderText("Task added.");
    addObj.setTaskList(tasksThatDay);

    return addObj;
}

UIObject AddCmd::undo() {
	History *hist = History::getInstance();

	CommandType::Command prevCmd = hist->getPreviousCommand();
    assert(prevCmd == CommandType::ADD);

	State prevState = hist->getPreviousState();
	Task task = prevState.getTask();

	Storage* storage = Storage::getInstance();
    TaskList taskList = storage->getTaskList();

	//Removed the newly added task
	taskList.remove(task.getTaskID());
	storage->updateStorage(taskList);

	hist->clearHistory();

    UIObject undoMessage;

	TaskList::TList tasksThatDay;
    tasksThatDay = taskList.getDay(_task.getTaskBegin());
	undoMessage.setHeaderText("Undo successfully");
	undoMessage.setTaskList(tasksThatDay);

    return undoMessage;
}
