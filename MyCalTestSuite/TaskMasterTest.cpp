//@Seow Yan Yi A0086626W
#include "stdafx.h"
#include "CppUnitTest.h"
#include <string>
#include <ctime>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;


namespace MyCalTestSuite {
	TEST_CLASS(TaskMasterTest) {
	public:
		TEST_METHOD(TestTaskConstructor) {     
            Task task;

            Assert::IsFalse(task.isDone());
            Assert::IsTrue(task.isFloating());
            Assert::AreEqual((unsigned)0, task.getTaskID());
            Assert::AreEqual(std::string("Thu Jan 01 1970"), task.getDateStr());
            Assert::AreEqual(std::string("08:00 AM"), task.getBeginStr());
            Assert::AreEqual(std::string("08:00 AM"), task.getEndStr());
		}

        TEST_METHOD(TestTaskAPI) {
            Task task;
            
            task.setTaskName("do CS2103 tutorial");
            Assert::AreEqual(std::string("do CS2103 tutorial"), task.getTaskName());
           
            task.markDone();
            Assert::IsTrue(task.isDone());
            
            task.setTaskID((unsigned)123);
            Assert::AreEqual((unsigned)123, task.getTaskID());

            task.setTaskBegin(TaskStub::getSampleTime());
            Assert::AreEqual(std::string("Mon Mar 09 2015"), task.getDateStr());
            Assert::AreEqual(std::string("07:23 AM"), task.getBeginStr());
        }

        TEST_METHOD(TestTaskList) {
            TaskList list;
            list.add(TaskStub::getSampleTask8());
            list.add(TaskStub::getSampleTask2());
            list.add(TaskStub::getSampleTask5());
            
            std::string expected = 
                TaskStub::getSampleTask2().toString() + "\n" +
                TaskStub::getSampleTask5().toString() + "\n" + 
                TaskStub::getSampleTask8().toString() + "\n";

            Assert::AreEqual(expected, list.toString());
        }

	};


}