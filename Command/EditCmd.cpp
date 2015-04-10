#include "EditCmd.h"
#include "Storage.h"
#include "TaskList.h"
#include "History.h"
#include <assert.h>

EditCmd::EditCmd(void) {
}


EditCmd::~EditCmd(void) {
}

void EditCmd::prepareTask(Task task) {
    _task = task;
}

void EditCmd::recordInHistory(Task task) {
    State prevState; 
    prevState.recordTask (task);
    History *hist = History::getInstance();
    hist->saveState(prevState);
    hist->saveCommand(CommandType::EDIT);
}


UIObject EditCmd::execute() {
    UIObject temp;

    Storage* storage = Storage::getInstance();
    TaskList taskList = storage->getTaskList();
	recordInHistory(taskList.findTask(_task.getTaskID()));
	//update storage with the edited task
	taskList.update(_task);
    storage->updateStorage(taskList);

	//return UI Object
	temp.setHeaderText("Successfuly Edited");
    return temp;
}

UIObject EditCmd::undo() {
	History *hist = History::getInstance();

	CommandType::Command prevCmd = hist->getPreviousCommand();
    assert(prevCmd == CommandType::EDIT);

	State prevState = hist->getPreviousState();
	Task prevTask = prevState.getTask();

	Storage* storage = Storage::getInstance();
    TaskList taskList = storage->getTaskList();
	taskList.update(prevTask);
	storage->updateStorage(taskList);    

	hist->clearHistory();

    UIObject undoMessage;
  
    TaskList::TList restored;
    restored.push_back(prevTask);

	//return UIObject
	undoMessage.setHeaderText("Original task restored.");
	undoMessage.setTaskList(restored);

    return undoMessage;
}