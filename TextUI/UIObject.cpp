#include "UIObject.h"


UIObject::UIObject(void) {
}


UIObject::~UIObject(void) {
}

std::string UIObject::getHeaderText() const {
    return _headerText;
}

void UIObject::setHeaderText(std::string text) {
    _headerText = text;
}

TaskList::TList UIObject::getTaskList() const {
    return _taskList;
}

void UIObject::setTaskList(TaskList::TList list) {
    _taskList = list;
}