#include "EditCmd.h"
#include "Storage.h"
#include "TaskList.h"
#include "History.h"
#include <assert.h>
#include "MCLogger.h"
const std::string EditCmd::UNDO_MESSAGE = "Edit undo successful. Tasks for that day:";

EditCmd::EditCmd(void) {
}


EditCmd::~EditCmd(void) {
}

void EditCmd::prepareTask(Task task) {
    _task = task;
}

UIObject EditCmd::execute() {
    Storage* storage = Storage::getInstance();
    TaskList taskList = storage->getTaskList();
    Task originalTask = taskList.findTask(_task.getTaskID());
    recordInHistory (originalTask);

	//update the edited task
	taskList.update(_task);
    storage->updateStorage(taskList);    

    std::string headerText = "Successfuly Edited. ";
    headerText = headerText + "Updated event: \nName:" + _task.getTaskName() + "\n";

    if (!_task.isFloating()) {
        headerText = headerText + "Date: " + _task.getDateStr() + "\nBegin:" + _task.getBeginStr();
        headerText = headerText + " End: " + _task.getEndStr();
    }

    UIObject edited;
	edited.setHeaderText(headerText);
    History *hist = History::getInstance();
    CommandType::Command prevCmd = hist->getPreviousCommand();

    return edited;
}

UIObject EditCmd::undo() {
    UIObject undoMessage;
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

    TaskList::TList tasksThatDay;
    tasksThatDay = taskList.getDay(prevTask.getTaskBegin());

	//return UIObject
	undoMessage.setHeaderText(UNDO_MESSAGE);
	undoMessage.setTaskList(tasksThatDay);

    return undoMessage;
}

void EditCmd::recordInHistory(Task task) {
    State prevState; 
    prevState.recordTask (task);
    History *hist = History::getInstance();
    hist->saveState(prevState);
    hist->saveCommand(CommandType::EDIT);
}