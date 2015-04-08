#include "AddCmd.h"
#include "Storage.h"
#include "TaskList.h"
#include <assert.h>
#include "InvalidFilePathException.h"
#include "Shlwapi.h" // PathFileExists
#include "History.h"
#include "State.h"
#include "MCLogger.h"

const std::string AddCmd::ADD_MESSAGE = "Task added" ;
const std::string AddCmd::UNDO_MESSAGE = "Task removed from storage:";
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
	UIObject addObj;
    //get current tasks
    Storage* storage = Storage::getInstance();
    TaskList taskList = storage->getTaskList();

	if (_task.getTaskID() == -1){
		addObj.setHeaderText (getHelp());
	}
	else if (_task.getTaskID() != -1){
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

    addObj.setHeaderText(ADD_MESSAGE);
    addObj.setTaskList(tasksThatDay);
	}

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
    tasksThatDay.push_back (task);

	undoMessage.setHeaderText(UNDO_MESSAGE);
	undoMessage.setTaskList(tasksThatDay);

    return undoMessage;
}

std::string AddCmd::getHelp() const{
		std::string help;

	std::string title = "***************** COMMAND HELP: ADD  *****************\n\n";

	std::string intro = "The add command allows you to add a task \n\n"; 

	std::string pt1 = "1. This command can be invoked by typing add [task name] {:optional detail1} {:optional detail2} \n";
	pt1 = pt1 + "TIME {:at time}\n";
    pt1 = pt1 + "     {:from startTime to endTime}\n";
	pt1 = pt1 + "     {:by time}]\n";
	pt1 = pt1 + "DATE {:dateSpecifier}\n";
	pt1 = pt1 + "Example: add meeting :at 230pm \n";
	pt1 = pt1 + "         add project due :tomorrow\n";

	help = title + intro + pt1;

	return help;
}