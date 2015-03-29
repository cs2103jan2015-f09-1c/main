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

            StorageUtils::backupExistingFiles();
            StorageUtils::createSettingsFile(initialTaskListLoc);

            Storage *storage = Storage::getInstance();
            storage->updateStorage(TaskStub::getSampleTaskList());

            //File not moved yet and should exist
            Assert::IsTrue(StorageUtils::isFileExist(initialFile.c_str()));
            //File should not be in new location
            Assert::IsFalse(StorageUtils::isFileExist(movedFile.c_str()));
            //Original contents of file
            std::string originalContents = StorageUtils::readFile(initialFile);
            
            //Modify storage location
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

            Storage::resetInstance();
            StorageUtils::removeTaskListFile(newTaskListLoc);
            StorageUtils::removeSettingsFile();
            StorageUtils::restoreExistingFiles();
		}
        
        TEST_METHOD(TestUpdateStorage) {
            std::string taskListLoc = "";
            StorageUtils::backupExistingFiles();
            StorageUtils::createSettingsFile(taskListLoc);

            Storage *storage = Storage::getInstance();
            storage->updateStorage(TaskStub::getSampleTaskList());
            TaskList listAfterUpdate = storage->getTaskList();
            std::ostringstream oss;
            oss << "Buy gift for John" << std::endl;
            oss << "Thu Jan 01" << std::endl;
            oss << "08:00 AM - 08:00 AM" << std::endl;
            oss << "1" << std::endl << std::endl;

            oss << "Performance @ UCC" << std::endl;
            oss << "Sat Mar 07" << std::endl;
            oss << "05:23 AM - 07:23 AM" << std::endl;
            oss << "1" << std::endl << std::endl;

            oss << "Go to NTU" << std::endl;
            oss << "Sun Mar 08" << std::endl;
            oss << "11:23 AM - 01:53 PM" << std::endl;
            oss << "0" << std::endl << std::endl;

            oss << "cs2103 tutorial" << std::endl;
            oss << "Mon Mar 09" << std::endl;
            oss << "07:23 AM - 08:53 AM" << std::endl;
            oss << "0" << std::endl << std::endl;  
            Assert::AreEqual(oss.str(), listAfterUpdate.toString());
            Storage::resetInstance();        

            Storage *storage2 = Storage::getInstance();
            TaskList listAfterInit = storage2->getTaskList();
            Assert::AreEqual(oss.str(), listAfterInit.toString());
            Storage::resetInstance();    

            StorageUtils::removeSettingsFile();
            StorageUtils::removeTaskListFile(taskListLoc);
            StorageUtils::restoreExistingFiles();
        }
	};
}