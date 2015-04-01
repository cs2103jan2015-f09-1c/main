#include "SearchCmd.h"
#include "Storage.h"
#include "TaskList.h"

SearchCmd::SearchCmd(void) {
}

SearchCmd::~SearchCmd(void) {
}

void SearchCmd::prepareList (TaskList::TList _List){
	List = _List;
}

UIObject SearchCmd::execute() {
    UIObject temp;

	//Search
	if (List.empty()){
		temp.setHeaderText ("There are no matching results");
	}
	else{
		temp.setHeaderText ("Tasks found:");
		temp.setTaskList (List);
	}

    //return UI Object 
    return temp;
}
