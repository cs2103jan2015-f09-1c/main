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
		
        TaskList sampleTaskList1() {
            TaskList list;
            list.add(sampleTask3());
			 list.add(sampleTask2());
            list.add(sampleTask4());
            list.add(sampleTask1());
           
            return list;
        }
		
		
		TEST_METHOD(TestHeaderText){
			UIObject uiObj;

			uiObj.setHeaderText("Successfully Edited");
			Assert::AreEqual(std::string("Successfully Edited"), uiObj.getHeaderText());
		}

		TEST_METHOD(printDateBar){
			std::ostringstream oss;
			UIObject uiObj;
			TaskList::TList tasks;		
			uiObj.setTaskList(tasks);

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

			TaskList:: TList listSample = uiObj.getTaskList();

            //Assert::AreEqual(oss.str(), listSample);
		
		}


	};
}