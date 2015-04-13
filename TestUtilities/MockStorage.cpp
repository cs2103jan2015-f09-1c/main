//@Seow Yan Yi A0086626W
#include "MockStorage.h"
#include "MCLogger.h"

MockStorage::MockStorage(void) {
}


MockStorage::~MockStorage(void) {
}

void MockStorage::initMockStorage(TaskList taskList, std::string taskListLoc) {
	MCLogger::log("MockStorage.cpp: initializing mock storage");
    StorageUtils::backupExistingFiles();
    StorageUtils::createSettingsFile(taskListLoc);
    Storage *storage = Storage::getInstance();
    storage->updateStorage(taskList);
}

void MockStorage::cleanMockStorage(std::string taskListLoc) {
	MCLogger::log("MockStorage.cpp: Clean mock storage");
    StorageUtils::removeTaskListFile(taskListLoc);
    StorageUtils::removeSettingsFile();
    StorageUtils::restoreExistingFiles();
    Storage::resetInstance();
}
