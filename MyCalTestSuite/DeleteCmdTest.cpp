#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;


namespace MyCalTestSuite {
	TEST_CLASS(DeleteCmdTest) {
	public:
		TEST_METHOD_INITIALIZE(InitDeleteCmdTest) {
			MCLogger::log("---------------Begin Delete Cmd test------------------");
		}
        /*TEST_METHOD(TestDeleteByNum) {
            unsigned idToDel = 3;
            MockStorage::initMockStorage(TaskStub::getSampleTaskList());
            Task taskToDel = TaskStub::getTaskWithID(idToDel);



            MockStorage::cleanMockStorage();
        }*/
        
        TEST_METHOD(TestDeleteByName) {
            MockStorage::initMockStorage(TaskStub::getSmallTaskList());
            
            // TEST FOR ONE TASK REMAINING
            DeleteCmd delCmdObj;
            delCmdObj.prepareTaskId((unsigned) 3);
            UIObject oneRemaining = delCmdObj.execute();

            // check header text
            std::string actualHeader = oneRemaining.getHeaderText();
            std::string expectedHeader = "Remaining tasks for that day:";
            Assert::AreEqual(expectedHeader, actualHeader);

            // check task list
            TaskList actualTaskList;
            actualTaskList.loadTaskList(oneRemaining.getTaskList());
            std::string expectedTaskStr = TaskStub::getSampleTask1().toString() + "\n";
            Assert::AreEqual(expectedTaskStr, actualTaskList.toString());

            // TEST FOR NO TASKS REMAINING
            delCmdObj.prepareTaskId((unsigned) 1);
            UIObject noneRemaining = delCmdObj.execute();
            
            // check header text
            std::string actualHeader2 = noneRemaining.getHeaderText();
            std::string expectedHeader2 = "No more tasks for that day!";
            Assert::AreEqual(expectedHeader2, actualHeader2);

            // check task list
            TaskList actualTaskList2;
            actualTaskList2.loadTaskList(noneRemaining.getTaskList());
            Assert::AreEqual(0, actualTaskList2.totalTasks());

            // check remaining tasks in storage
            std::string expectedStorage = "5\ndummy T5\n1425986625\n1425990225\n0\n";;
            Assert::AreEqual(expectedStorage, StorageUtils::readFile("tasklist.txt"));

            MockStorage::cleanMockStorage();
        }

        /*
        TEST_METHOD(TestDeleteEmpty) {
            MockStorage::initMockStorage(TaskStub::getSampleTaskList());


            MockStorage::cleanMockStorage();
        }

        TEST_METHOD(TestDeleteNotFound) {
            MockStorage::initMockStorage(TaskStub::getSampleTaskList());


            MockStorage::cleanMockStorage();
        }

        TEST_METHOD(TestDeleteUndo) {
            MockStorage::initMockStorage(TaskStub::getSampleTaskList());


            MockStorage::cleanMockStorage();
        }*/

		TEST_METHOD_CLEANUP(CleanupDeleteCmdTest) {
			MCLogger::log("---------------End Delete Cmd test------------------");
		}

	};


}