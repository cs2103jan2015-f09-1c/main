#include "SearchCmd.h"
#include "Storage.h"
#include "TaskList.h"

SearchCmd::SearchCmd(void) {
}

SearchCmd::~SearchCmd(void) {
}

void SearchCmd::prepareTask (Task task){
	_task = task;
}
void SearchCmd::prepareSearch(std::string keyword) {
    _keyword = keyword;
}

UIObject SearchCmd::execute() {
    UIObject temp;
    //The storage functions are not completed yet
    //so just hardcode a tasklist to test AddCmd
   
    //get current tasks
    Storage* storage = Storage::getInstance();
    TaskList taskList = storage->getTaskList();

	TaskList::TList _templist;
    //search
	if (Search(_keyword, _task)){
	temp.setTaskList(_templist);
	}
	else{
		temp.setHeaderText("There are no matching results.");
	}
    //return UI Object 
    return temp;
}
