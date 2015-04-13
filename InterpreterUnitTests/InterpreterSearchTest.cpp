#include "stdafx.h"
#include "CppUnitTest.h"
#include "CommandType.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace MyCalTestSuite {
	TEST_CLASS(InterpreterAddPositiveTest) {
	public:
		bool check_substring(std::string sub_str, std::string str ){
			if (str.find(sub_str) != std::string::npos){
				return true;
			}
			else{
				return false;
			}
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
	};
}