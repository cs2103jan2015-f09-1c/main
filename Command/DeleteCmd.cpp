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

int DeleteCmd::ConvertStrtoNum (std::string str){
	int integer;
	std::stringstream convert (str);
	convert >> integer;

	if (convert.fail()){
		integer = 0;
	}
	else{
		convert >> integer;
	}
	return integer;
}

bool DeleteCmd::CheckTask (Task _task){
	MappingNumber *mapping = MappingNumber::getInstance();
	std::string taskToDel = _task.getTaskName();
	int DelNum;
	if (_task.getTaskID() == 0){
		int integer = ConvertStrtoNum (taskToDel);
		if (integer == 0){
			return false;
		}
		else{
			int count = mapping->countNode ();
			if(integer > count){
				return false;
			}
			else{
				return true;
			}
		}
	}
	else{
		return true;
	}

}

unsigned DeleteCmd::GetTaskId (){
  MappingNumber *mapping = MappingNumber::getInstance();
  std::string taskToDel = _task.getTaskName();
  unsigned TaskId;
  int DelNum = ConvertStrtoNum (taskToDel);
	  TaskId = mapping->getTaskID(DelNum);
	  return TaskId;
}

UIObject DeleteCmd::execute() {
  UIObject temp;
  unsigned TaskId;
  Storage* storage = Storage::getInstance();
  TaskList taskList = storage->getTaskList();

  if (!CheckTask(_task)){
	  temp.setHeaderText("There is no matching task to be deleted. \n");
  }
  else{
	  TaskId = GetTaskId();
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
    tasksThatDay = taskList.getDay(_task.getTaskBegin());

	//return UIObject
	undoMessage.setHeaderText("Undo successfully");
	undoMessage.setTaskList(tasksThatDay);

    return undoMessage;
}
