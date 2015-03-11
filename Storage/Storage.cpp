#include "Storage.h"
#include <fstream>
#include <sstream>

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
    //update _taskList
    writeToTaskList();
}

void Storage::setStorageLoc(std::string loc) {
    _taskListLoc = loc;
    //copy file over
    writeToSettings();
}

std::string Storage::getStorageLoc() const {
    return _taskListLoc;
}

Storage::Storage(void) {
    initSessionStore();
}


Storage::~Storage(void) {
}

void Storage::initSessionStore() {
    std::string line;
    std::ifstream readFile(TASKLIST_FILENAME);  
    
    int counter = 0;

    Task curTask;
    while (std::getline(readFile, line)) {
        counter++;
        unsigned id;
        time_t begin;
        time_t end;

        switch(counter) {
        case 1:
            id = std::stoul(line);
            curTask.setTaskID(id);
            break;
        case 2:
            curTask.setTaskName(line);
            break;
        case 3:
            begin = std::stoul(line);
            curTask.setTaskBegin(begin);
            break;
        case 4:
            end = std::stoul(line);
            curTask.setTaskEnd(end);
            break;
        case 5:
            if (line == "done") {
                curTask.markDone();
            } 

            counter = 0;
            _sessionStore.add(curTask);
            break;
        }
    }
    //todo: read from loc
}

void Storage::overwriteFile(std::string file, std::string contents) {
	std::ofstream writeFile(file);
	writeFile << contents;
	writeFile.close();
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
    // <isfloating>
    // <isDone>
    TaskList::TList list = _sessionStore.getAll();
    TaskList::taskIt it;
    std::ostringstream oss;
    for (it = list.begin(); it != list.end(); ++it) {
        std::string begin = time_tToString(it->getTaskBegin());
        std::string end = time_tToString(it->getTaskEnd());
        std::string isfloating = it->isFloating() ? "float" : "nofloat";
        std::string isDone = it->isDone() ? "done" : "notDone";
        oss << it->getTaskID() << std::endl;
        oss << it->getTaskName() << std::endl;
        oss << begin << std::endl;
        oss << end << std::endl;
        oss << isfloating << std::endl;
        oss << it->isDone() << std::endl;
    }

    overwriteFile(TASKLIST_FILENAME, oss.str());
 }