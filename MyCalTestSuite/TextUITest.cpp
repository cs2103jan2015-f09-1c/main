#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace MyCalTestSuite
{
	TEST_CLASS(TextUITest)
	{
	public: time_t sampleTime() {
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
            task.setTaskID((unsigned) 1);
            task.setTaskName("cs2103 tutorial");
            task.setTaskBegin(sampleTime());
            task.setTaskEnd(sampleTime() + 5400);
            return task;
        }

        Task sampleTask2() {
            Task task;
            task.setTaskID((unsigned) 3);
            task.setTaskName("Performance @ UCC");
            task.setTaskBegin(sampleTime() - 180000);
            task.setTaskEnd(sampleTime() - 172800);
            task.markDone();
            return task;
        }

        Task sampleTask3() {
            Task task;
            task.setTaskID((unsigned) 4);
            task.setTaskName("Buy gift for John");
            task.markDone();
            return task;
        }

        Task sampleTask4() {
            Task task;
            task.setTaskID((unsigned) 5);
            task.setTaskName("Go to NTU");
            task.setTaskBegin(sampleTime() - 72000);
            task.setTaskEnd(sampleTime() - 63000);
            return task;
        }

        TaskList sampleTaskList() {
            TaskList list;
            list.add(sampleTask3());
            list.add(sampleTask1());
            list.add(sampleTask2());
            list.add(sampleTask4());
            return list;
        }
		
		TEST_METHOD(TestHeaderText)
		{
			UIObject uiObj;

			uiObj.setHeaderText("Successfully edited");
			Assert::AreEqual(std::string("Successfully edited"), uiObj.getHeaderText());
		}

		//TEST_ME

	};
}