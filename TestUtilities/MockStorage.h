//@author A0086626W
#pragma once
#include "Storage.h"
#include "StorageUtils.h"
#include "TaskStub.h"

class MockStorage {
public:
    MockStorage(void);
    ~MockStorage(void);

    // sets up storage with same location as the executable 
    // and loaded with the task list passed in
    // original storage files are backed up; they will be restored when
    // cleanMockStorage() is called.
    static void initMockStorage(TaskList taskList, std::string taskListLoc = "");

    // to be used at the end of the test method
    // removes files created during initMockStorage and restores 
    // original storage files
    static void cleanMockStorage(std::string taskListLoc = "");
};

