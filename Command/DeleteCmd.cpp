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
	  temp.setHeaderText("There is no matching task to be deleted. \n");
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

	taskList.add(task);
	storage->updateStorage(taskList);    

	hist->clearHistory();

    UIObject undoMessage;
  
    TaskList::TList tasksThatDay;
    tasksThatDay = taskList.getDay(task.getTaskBegin());

	//return UIObject
	undoMessage.setHeaderText("Undo successfully");
	undoMessage.setTaskList(tasksThatDay);

    return undoMessage;
}
