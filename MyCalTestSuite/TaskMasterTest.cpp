#include "stdafx.h"
#include "CppUnitTest.h"
#include <string>
#include <ctime>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;


namespace MyCalTestSuite {
	TEST_CLASS(TaskMasterTest) {
	public:
        time_t sampleTime() {
            time_t rawTime;
            tm sampleTime;
            sampleTime.tm_hour = 7;
            sampleTime.tm_isdst = 0;
            sampleTime.tm_mday = 9;
            sampleTime.tm_min = 23;
            sampleTime.tm_mon = 2;
            sampleTime.tm_sec = 45;
            sampleTime.tm_wday = 1;
            sampleTime.tm_yday = 67;
            sampleTime.tm_year = 115;
           
            rawTime = mktime(&sampleTime);
            return rawTime;
        }

        Task sampleTask1() {
            Task task;
            task.setTaskName("apple");
            task.setTaskBegin(sampleTime());
            task.setTaskEnd(sampleTime() + 5400);
            return task;
        }

        Task sampleTask2() {
            Task task;
            task.setTaskName("orange");
            task.setTaskBegin(sampleTime() - 180000);
            task.setTaskEnd(sampleTime() - 172800);
            return task;
        }

        Task sampleTask3() {
            Task task;
            task.setTaskName("durian");
            task.setTaskBegin(sampleTime() + 1000);
            task.setTaskEnd(sampleTime() + 5400);
            return task;
        }

        Task sampleTask4() {
            Task task;
            task.setTaskName("nus");
            task.setTaskBegin(sampleTime() - 72000);
            task.setTaskEnd(sampleTime() - 63000);
            return task;
        }

		TEST_METHOD(TestTaskConstructor) {     
            Task task;

            Assert::IsFalse(task.isDone());
            Assert::IsTrue(task.isFloating());
            Assert::AreEqual((unsigned)0, task.getTaskID());
            Assert::AreEqual(std::string("Thu Jan 01"), task.getDateStr());
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

            task.setTaskBegin(sampleTime());

            Assert::AreEqual(std::string("Mon Mar 09"), task.getDateStr());
            Assert::AreEqual(std::string("07:23 AM"), task.getBeginStr());
        }

        TEST_METHOD(TestTaskList) {
            TaskList list;
            list.add(sampleTask3());
            list.add(sampleTask1());
            list.add(sampleTask2());
            std::ostringstream oss;
            oss << "orange" << std::endl;
            oss << "Sat Mar 07" << std::endl;
            oss << "05:23 AM - 07:23 AM" << std::endl << std::endl;
            oss << "apple" << std::endl;
            oss << "Mon Mar 09" << std::endl;
            oss << "07:23 AM - 08:53 AM" << std::endl << std::endl;
            oss << "durian" << std::endl;
            oss << "Mon Mar 09" << std::endl;
            oss << "07:40 AM - 08:53 AM" << std::endl << std::endl;
            Assert::AreEqual(oss.str(), list.toString());

            list.add(sampleTask4());
            std::ostringstream oss2;
            oss2 << "orange" << std::endl;
            oss2 << "Sat Mar 07" << std::endl;
            oss2 << "05:23 AM - 07:23 AM" << std::endl << std::endl;
            oss2 << "nus" << std::endl;
            oss2 << "Sun Mar 08" << std::endl;
            oss2 << "11:23 AM - 01:53 PM" << std::endl << std::endl;
            oss2 << "apple" << std::endl;
            oss2 << "Mon Mar 09" << std::endl;
            oss2 << "07:23 AM - 08:53 AM" << std::endl << std::endl;
            oss2 << "durian" << std::endl;
            oss2 << "Mon Mar 09" << std::endl;
            oss2 << "07:40 AM - 08:53 AM" << std::endl << std::endl;
            Assert::AreEqual(oss2.str(), list.toString());
        }

	};


}