#include "EditCmd.h"
#include "Storage.h"
#include "TaskList.h"


EditCmd::EditCmd(void) {
}


EditCmd::~EditCmd(void) {
}

void EditCmd::prepareTask(Task task) {
    _task = task;
}

UIObject EditCmd::execute() {
    UIObject temp;

    //The storage functions are not completed yet
    //so just hardcode a tasklist to test AddCmd
    
    //get current tasks
    Storage* storage = Storage::getInstance();
    TaskList taskList = storage->getTaskList();

	//edit the task
	taskList.update(_task);

	//return UI Object
	TaskList::taskIt it;
	TaskList::TList _taskList = taskList.getAll();	
	temp.setHeaderText("-----Editing task " + std::to_string(it->getTaskID()) + "-----");

	

	/*
    //edit the task
	TaskList::taskIt it;
	TaskList::TList _taskList = taskList.getAll();
    for (it = _taskList.begin(); it != _taskList.end(); ++it) {
        unsigned targetId = _task.getTaskID();
        unsigned curId = it->getTaskID();

        if (targetId == curId) { //found
			temp.setTask(*it);
			std::string input;
			temp.setHeaderText("-----Editing task "+std::to_string(it->getTaskID())+"-----");
		//	std::getline(std::cin, input);
			
        }
		else{ //not found
			temp.setHeaderText("-----Task not found-----");			
		}
    }
	*/

    //storage->updateStorage(taskList);    


    return temp;
}