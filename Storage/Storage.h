#pragma once
#include <string>
#include "TaskList.h"

class Storage {
public:
    static Storage* getInstance();
    static void resetInstance(); 
    TaskList getTaskList() const;
    void updateStorage(TaskList taskList);
    void setStorageLoc(std::string newLoc);
    std::string getStorageLoc() const;
    unsigned getNextID() const;

private:
    static const std::string SETTINGS_FILENAME;
    static const std::string TASKLIST_FILENAME;

    Storage(void);
	~Storage(void);
	
	unsigned findMaxID(TaskList list) const;
    std::string getExeFileName() const;
    std::string getExePath() const;
    void loadTaskListLoc();
    void initSessionStore();
    void overwriteFile(std::string file, std::string contents, std::string loc);
    void moveTaskList(std::string oldLoc, std::string newLoc);

	//writeSettingsTxt overwrites the exisiting file
	//save to settings.txt in the following format:
	//<contents>
    void writeSettingsTxt(std::string contents);

	//writeTaskListTxt overwrites the exisiting file
	//save to tasklist.txt in the following format:
	// <taskid>
	// <taskname>
	// <taskbegin>
	// <taskend>
	// <isDone>
    void writeTaskListTxt(TaskList::TList listToWrite, std::string writeLoc);
    
    static Storage* _instance;
    TaskList _sessionStore;
	std::string _taskListLoc; //tastList.txt's location
};


