#include "stdafx.h"
#include "CppUnitTest.h"
#include <stdio.h>
#include <fstream>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

static const std::string SAMPLE_TASKLIST_LOC = "../../";

namespace MyCalTestSuite {
    
	TEST_CLASS(StorageTest) {
	public:
   		TEST_METHOD(TestSetStorageLoc) {
            std::string initialTaskListLoc = "";
            std::string newTaskListLoc = "../";       
            std::string initialFile = initialTaskListLoc + "tasklist.txt";
            std::string movedFile = newTaskListLoc + "tasklist.txt";

            MockStorage::initMockStorage(TaskStub::getSmallTaskList(), initialTaskListLoc);

            //File not moved yet and should exist
            Assert::IsTrue(StorageUtils::isFileExist(initialFile.c_str()));
            //File should not be in new location
            Assert::IsFalse(StorageUtils::isFileExist(movedFile.c_str()));
            //Original contents of file
            std::string originalContents = StorageUtils::readFile(initialFile);
            
            //Modify storage location
            Storage *storage = Storage::getInstance();
            storage->setStorageLoc(newTaskListLoc);
            std::string storageLocExpected = storage->getStorageLoc();
            Assert::AreEqual(storageLocExpected, newTaskListLoc);

            //File is moved and should not exist
            Assert::IsFalse(StorageUtils::isFileExist(initialFile.c_str()));            
            //File should be in new location
            Assert::IsTrue(StorageUtils::isFileExist(movedFile.c_str()));
            //Contents should be unchanged
            std::string newContents = StorageUtils::readFile(movedFile);
            Assert::AreEqual(originalContents, newContents);

            MockStorage::cleanMockStorage(newTaskListLoc);
		}
        
        TEST_METHOD(TestUpdateStorage) {
            MockStorage::initMockStorage(TaskStub::getLargeTaskList());

            Storage *storage = Storage::getInstance();
            storage->updateStorage(TaskStub::getSmallTaskList());
            TaskList listAfterUpdate = storage->getTaskList();

            std::string expectedList = TaskStub::getSmallTaskList().toString();

            Assert::AreEqual(expectedList, listAfterUpdate.toString());

            Storage::resetInstance();        
            Storage *storage2 = Storage::getInstance();
            TaskList listAfterInit = storage2->getTaskList();
            Assert::AreEqual(expectedList, listAfterInit.toString());

            MockStorage::cleanMockStorage();
        }
	};
}