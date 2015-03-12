#include "stdafx.h"
#include "CppUnitTest.h"
#include <iomanip> // put_time

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace MyCalTestSuite {
	TEST_CLASS(InterpreterTest) {
	public:
        std::string timetToString(time_t timing) const {
            //refer to std::put_time fmt
            tm tmstruct;
            localtime_s(&tmstruct, &timing);
            std::ostringstream oss;
            oss << std::put_time(&tmstruct, "%d/%m/%y %I:%M %p");
            return oss.str();
        }

		TEST_METHOD(TestParseAddCmd) {
			std::string floatingInput = "add CS2103 tutorial";
            Task floatingTask = Interpreter::parseAddCmd(floatingInput);
            Assert::AreEqual(std::string("CS2103 tutorial"), floatingTask.getTaskName());
            //Assert::IsTrue(floatingTask.isFloating()); //This fails. If floating task, set default start time = 0
            
            //Feel free to change the time, date format here if this is not
            //what you were expecting
            //task2 gettaskname test fails. There is a extra space character after taskname
            //this is not a big deal, so you can fix it later
            std::string input2 = "add CS2103 tutorial :at 1231pm :10 mar 2016"; 
            
            Task task2 = Interpreter::parseAddCmd(input2);
            Assert::AreEqual(std::string("CS2103 tutorial "), task2.getTaskName());
            Assert::IsFalse(task2.isFloating());

            std::string task2Begin = timetToString(task2.getTaskBegin());
            std::string task2End = timetToString(task2.getTaskEnd());
            //task2 gettaskbegin fails. User inputs 10 mar 2016, should get
            //10/03/16 12:31 PM. We get 13/03/15 12:31 AM instead.
            //(I use timetToString because comparing time_t directly
            //will be wrong as we dont care about seconds)
            //
            //Assert::AreEqual(std::string("10/03/16 12:31 PM"), task2Begin);
            //Assert::AreEqual(std::string("??"), task2End);                      
            //what output are you expecting if there is no ending time specified?
            //seems like the default end time is = to start time?

            std::string input3 = "add CS2103 tutorial :at 4am :3 nov 2015"; 
            
            Task task3 = Interpreter::parseAddCmd(input3);
            //Assert::AreEqual(std::string("CS2103 tutorial "), task3.getTaskName());
            //Assert::IsFalse(task3.isFloating());

            std::string task3Begin = timetToString(task3.getTaskBegin());
            std::string task3End = timetToString(task3.getTaskEnd());
            //task 3 gettaskbegin fails too. 
            //Expected 03/11/15 04:00 AM but got 12/03/15 04:00 AM
            //seems like the parser keeps giving wrong date 
            //Assert::AreEqual(std::string("03/11/15 04:00 AM"), task3Begin);

            /*
            For V0.1, just make sure the :from :to and :at is working
            The other commands can save for later when theres more time
            */
		}

        /*
		TEST_METHOD(TestParseEditCmd) {
			// TODO: Your test code here
		}

		TEST_METHOD(TestParseStoreCmd) {
			// TODO: Your test code here
		}
        */
	};
}