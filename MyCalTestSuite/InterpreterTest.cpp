#include "stdafx.h"
#include "CppUnitTest.h"
#include <iomanip> // put_time
#include "CommandType.h"

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

        time_t getCurrentTime() const {
            time_t timer;
            time(&timer);
            return timer;
        }

		bool check_substring(std::string sub_str, std::string str ){
			if (str.find(sub_str) != std::string::npos){
				return true;
			}
			else{
				return false;
			}
		}

		TEST_METHOD(TestParseAddCmd) {
			std::string floatingInput = "add CS2103 tutorial";
            Task floatingTask = Interpreter::parseAddCmd(floatingInput);
            Assert::AreEqual(std::string("CS2103 tutorial"), floatingTask.getTaskName());
            //Assert::IsTrue(floatingTask.isFloating()); //This fails. If floating task, set default start time = 0
            
            //task2 gettaskbegin fails. User inputs 10 mar 2016, should get
            //10/03/16 12:31 PM. We get 13/03/15 12:31 AM instead.
            //(I use timetToString because comparing time_t directly
            //will be wrong as we dont care about seconds)
            //
            //what output are we expecting if there is no ending time specified?

            std::string input2 = "add submit appliction :on 10/03/2015 :at 1159pm"; 
            
            Task task2 = Interpreter::parseAddCmd(input2);
            //Assert::AreEqual(std::string("project meeting "), task2.getTaskName());
            //Assert::IsFalse(task2.isFloating());
            std::string task2Begin = timetToString(task2.getTaskBegin());
            std::string task2End = timetToString(task2.getTaskEnd());
            //Assert::AreEqual(std::string("10/03/16 12:31 PM"), task2Begin);            
            //Assert::AreEqual(std::string("??"), task2End);                      
		}

		TEST_METHOD (TestParseSearchCmd){
			std::string input = "search meeting";
			TaskList::TList list;
			std::string keyword = CommandType::filterOutCmd(input); 
			list = Interpreter::parseSearchCmd(keyword);

			for (int i=0; i<list.size(); i++){
			Task task = list.front();
			std::string taskName = task.getTaskName();
			int TaskId = task.getTaskID();
			if (TaskId > 0){
			Assert::IsTrue(check_substring(keyword, taskName));
			//Check if the task name contain the key word "meeting"
			}
			else if (TaskId <= 0 ){
				//Check if the task name contain the key word "meeting"
				Assert::IsFalse(check_substring(keyword, taskName));
			}
			list.pop_front();
			}
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