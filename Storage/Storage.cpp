#include "Storage.h"
#include <fstream>
#include <sstream>
#include <stdio.h>
#include <windows.h>

const std::string Storage::SETTINGS_FILENAME = "settings.txt";
const std::string Storage::TASKLIST_FILENAME = "tasklist.txt";

Storage* Storage::_instance = 0;

Storage* Storage::getInstance() {
    if (_instance == 0) {
        _instance = new Storage;
    }
    return _instance;
}

void Storage::resetInstance() {
    delete _instance;
    _instance = NULL;
}

TaskList Storage::getTaskList() const {
    return _sessionStore;
}

void Storage::updateStorage(TaskList taskList) {
    _maxID++; //todo: find a better way to increase maxID / set ID
    _sessionStore = taskList;
    writeToTaskList();
}

void Storage::setStorageLoc(std::string newLoc) {
    moveTaskList(_taskListLoc, newLoc);
    _taskListLoc = newLoc;
    writeToSettings();
}

std::string Storage::getStorageLoc() const {
    if (_taskListLoc == "") {
        std::string path = getExePath();
        return path;
    }

    return _taskListLoc;
}

unsigned Storage::getNextID() const {
    return _maxID + 1;
}

Storage::Storage(void) {
    loadTaskListLoc();
    initSessionStore();
}


Storage::~Storage(void) {
}

std::string Storage::getExeFileName() const {
  char buffer[MAX_PATH];
  GetModuleFileName( NULL, buffer, MAX_PATH );
  return std::string(buffer);
}

std::string Storage::getExePath() const {
  std::string f = getExeFileName();
  return f.substr(0, f.find_last_of( "\\/" ));
}

void Storage::loadTaskListLoc() {
    std::ifstream readFile(SETTINGS_FILENAME);
    std::string line;

    std::getline(readFile, line);
    _taskListLoc = line;
}

void Storage::initSessionStore() {
    std::string filepath = _taskListLoc + TASKLIST_FILENAME;
    std::ifstream readFile(filepath);  

    Task *curTask = NULL;
    std::string line;
    int counter = 0;
    _maxID = 0;

    while (std::getline(readFile, line)) {
        counter++;
        unsigned id;
        time_t begin;
        time_t end;

        switch(counter) {
        case 1:
            curTask = new Task;
            id = std::stoul(line);
            if (id > _maxID) {
                _maxID = id;
            }
            curTask->setTaskID(id);
            break;
        case 2:
            curTask->setTaskName(line);
            break;
        case 3:
            begin = std::stoul(line);
            curTask->setTaskBegin(begin);
            break;
        case 4:
            end = std::stoul(line);
            curTask->setTaskEnd(end);
            break;
        case 5:
            if (line == "1") {
                curTask->markDone();
            } 

            counter = 0;
            _sessionStore.add(*curTask);
            delete curTask;
        }
    }
}

void Storage::overwriteFile(std::string file, std::string contents, std::string loc="") {
    std::string filepath = loc + file;
	std::ofstream writeFile(filepath);
	writeFile << contents;
	writeFile.close();
}

void Storage::moveTaskList(std::string oldLoc, std::string newLoc) {
    std::string oldpath = oldLoc + TASKLIST_FILENAME;
    std::string newpath = newLoc + TASKLIST_FILENAME;

    rename(oldpath.c_str(), newpath.c_str());
}

void Storage::writeToSettings() {
    //This overwrites the exisiting file
    //save to settings.txt in the following format:
    //<File Location>
    overwriteFile(SETTINGS_FILENAME, _taskListLoc);
}


void Storage::writeToTaskList() {
    //This overwrites the exisiting file
    //save to tasklist.txt in the following format:
    // <taskid>
    // <taskname>
    // <taskbegin>
    // <taskend>
    // <isDone>
    TaskList::TList list = _sessionStore.getAll();
    TaskList::taskIt it;
    std::ostringstream oss;
    for (it = list.begin(); it != list.end(); ++it) {
        oss << it->getTaskID() << std::endl;
        oss << it->getTaskName() << std::endl;
        oss << it->getTaskBegin() << std::endl;
        oss << it->getTaskEnd() << std::endl;
        oss << it->isDone() << std::endl;
    }

    overwriteFile(TASKLIST_FILENAME, oss.str(), _taskListLoc); 
 }