#include "AddCmd.h"
#include "Storage.h"
#include "TaskList.h"

AddCmd::AddCmd(void) {
}


AddCmd::~AddCmd(void) {
}

void AddCmd::prepareTask(Task task) {
    _task = task;
}

UIObject AddCmd::execute() {
    UIObject temp;

    //The storage functions are not completed yet
    //so just hardcode a tasklist to test AddCmd
    
    //get current tasks
    Storage* storage = Storage::getInstance();
    TaskList taskList = storage->getTaskList();

    //add the task
    taskList.add(_task);

    //update storage
    storage->updateStorage(taskList);    

    //return UI Object

    return temp;
}