#include "DeleteCmd.h"
#include "Storage.h"
#include "TaskList.h"

DeleteCmd::DeleteCmd(void) {
}

DeleteCmd::~DeleteCmd(void) {
}

void DeleteCmd::prepareTask(Task task) {
    _task = task;
}

UIObject DeleteCmd::execute() {
    UIObject temp;
    
    //get current tasks
    Storage* storage = Storage::getInstance();
    TaskList taskList = storage->getTaskList();

    //remove
    taskList.remove(_task.getTaskID());

    //update storage
    storage->updateStorage(taskList);    

    //return UI Object 
	temp.setHeaderText("Deleted "+(_task.getTaskName())+" on "+(_task.getDateStr())+" at "+(_task.getBeginStr())+" \n " "Remaining tasks for that day: ");
    temp.setTaskList(taskList.getToday());
    return temp;
}

UIObject DeleteCmd::undo() {
    UIObject undoMessage;
    //undo stuff
    return undoMessage;
}