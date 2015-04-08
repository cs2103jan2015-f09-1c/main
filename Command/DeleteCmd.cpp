#include "DeleteCmd.h"
#include "Storage.h"
#include "TaskList.h"
#include "MappingNumber.h"
#include <iostream>
#include <sstream>
#include <assert.h>
#include <time.h>
#include "History.h"
#include "State.h"
#include "MCLogger.h"

const std::string DeleteCmd::NO_MATCHING_TASK =  "There is no matching task to be deleted.";
const std::string DeleteCmd::NO_TASK_MESSAGE = "No more tasks for that day!";
const std::string DeleteCmd::REMAINING_TASK_MESSAGE = "Remaining tasks for that day:";
const std::string DeleteCmd::UNDO_MESSAGE = "Task added back to storage:";

DeleteCmd::DeleteCmd(void) {
}

DeleteCmd::~DeleteCmd(void) {
}

void DeleteCmd::prepareTaskId(int _TaskId) {
    TaskId = _TaskId;
}

void DeleteCmd::recordInHistory(Task task) {
    State prevState; 
    prevState.recordTask (task);
    History *hist = History::getInstance();
    hist->saveState(prevState);
    hist->saveCommand(CommandType::DEL);
}

UIObject DeleteCmd::execute() {
  UIObject temp;
  Storage* storage = Storage::getInstance();
  TaskList taskList = storage->getTaskList();

  if (TaskId == 0){
	  temp.setHeaderText(NO_MATCHING_TASK);
  }
  else{
	  Task ActualTask = taskList.findTask(TaskId);
	  recordInHistory (ActualTask);

	  taskList.remove(TaskId);
	  storage->updateStorage(taskList);

	  TaskList::TList tasksThatDay;
      tasksThatDay = taskList.getDay(ActualTask.getTaskBegin());
      temp.setTaskList(tasksThatDay);
	  
	  if (tasksThatDay.empty()){
		  temp.setHeaderText(NO_TASK_MESSAGE);
	  }
	  else{
		  temp.setHeaderText(REMAINING_TASK_MESSAGE);
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

	taskList.add(task);
	storage->updateStorage(taskList);    

	hist->clearHistory();

    UIObject undoMessage;
  
    TaskList::TList tasksThatDay;
    tasksThatDay.push_back(task);

	//return UIObject
	undoMessage.setHeaderText(UNDO_MESSAGE);
	undoMessage.setTaskList(tasksThatDay);

    return undoMessage;
}
