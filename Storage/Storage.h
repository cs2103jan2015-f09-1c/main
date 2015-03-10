#pragma once
#include <string>
#include "TaskList.h"

class Storage {
public:
    static Storage* getInstance();
    static void resetInstance();
    TaskList::TList getAllTasks() const;
    void updateStorage(TaskList taskList);
    void setStorageLoc(std::string loc);
    std::string getStorageLoc() const;

private:
    static const std::string SETTINGS_FILENAME;
    static const std::string TASKLIST_FILENAME;
    Storage(void);
	~Storage(void);

    std::string time_tToString(time_t theTime);
    time_t stringTotime_t(std::string str);

    void overwriteFile(std::string file, std::string contents);
    void writeToSettings();
    void writeToTaskList();
    
    static Storage* _instance;
    TaskList _sessionStore;
	std::string _taskListLoc; //tastList.txt's location
};


