#include "MockStorage.h"

// empty string means location of executable will be used.

MockStorage::MockStorage(void) {
}


MockStorage::~MockStorage(void) {
}

void MockStorage::initMockStorage(TaskList taskList, std::string taskListLoc) {
    StorageUtils::backupExistingFiles();
    StorageUtils::createSettingsFile(taskListLoc);
    Storage *storage = Storage::getInstance();
    storage->updateStorage(taskList);
}

void MockStorage::cleanMockStorage(std::string taskListLoc) {
    StorageUtils::removeTaskListFile(taskListLoc);
    StorageUtils::removeSettingsFile();
    StorageUtils::restoreExistingFiles();
    Storage::resetInstance();
}
