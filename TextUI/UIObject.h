#pragma once
#include <string>
#include "TaskList.h"

class UIObject {
public:
    UIObject(void);
    ~UIObject(void);
    std::string getHeaderText() const;
    void setHeaderText(std::string text);
    TaskList::TList getTaskList() const;
    void setTaskList(TaskList::TList list);

private:
    std::string _headerText;
    TaskList::TList _taskList;
};

