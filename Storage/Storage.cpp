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
    //_sessionStore.loadTaskList(taskList);
}


Storage::~Storage(void) {
}

std::string time_tToString(time_t theTime) {
    tm timeStruct;
    localtime_s(&timeStruct, &theTime);
    std::ostringstream oss;
    oss << timeStruct.tm_sec << " ";
    oss << timeStruct.tm_min << " ";
    oss << timeStruct.tm_hour << " ";
    oss << timeStruct.tm_mday << " ";
    oss << timeStruct.tm_mon << " ";
    oss << timeStruct.tm_year << " ";
    oss << timeStruct.tm_wday << " ";
    oss << timeStruct.tm_yday << " ";
    oss << timeStruct.tm_isdst;
    return oss.str();
}

time_t stringTotime_t(std::string str) {
    time_t theTime;
    tm timeStruct;
    std::istringstream iss;
    int val;

    iss >> val;
    timeStruct.tm_sec = val;
    iss >> val;
    timeStruct.tm_min = val;
    iss >> val;
    timeStruct.tm_hour = val;
    iss >> val;
    timeStruct.tm_mday = val;
    iss >> val;
    timeStruct.tm_mon = val;
    iss >> val;
    timeStruct.tm_year = val;
    iss >> val;
    timeStruct.tm_wday = val;
    iss >> val;
    timeStruct.tm_yday = val;
    iss >> val;
    timeStruct.tm_isdst = val;

    theTime = mktime(&timeStruct);
    return theTime;
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