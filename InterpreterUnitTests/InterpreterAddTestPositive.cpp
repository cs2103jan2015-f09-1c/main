#include "stdafx.h"
#include "CppUnitTest.h"
#include <iomanip> // put_time
#include "CommandType.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

// The interpreter's command options like :at, :from, :to are case insensitive and space-insensitive.
// Thus you will see test cases with a mix of cases as well as spacings

namespace MyCalTestSuite {
	TEST_CLASS(InterpreterAddPositiveTest) {
	public:
		TEST_METHOD(TestFloating) {
			std::string floatingInput = "CS2103 tutorial";
            Task floatingTask = Interpreter::parseAddCmd(floatingInput);
            Assert::AreEqual(std::string("CS2103 tutorial"), floatingTask.getTaskName());
            Assert::IsTrue(floatingTask.isFloating()); 
        }

		TEST_METHOD(TestAtOption12Hrs) {
			std::string atInput = "project meeting :aT       531 pm";
            Task task = Interpreter::parseAddCmd(atInput);

            Assert::AreEqual(std::string("project meeting "), task.getTaskName());
            Assert::IsFalse(task.isFloating()); 
            Assert::AreEqual(std::string("05:31 PM"), task.getBeginStr());
            Assert::AreEqual(std::string("07:31 PM"), task.getEndStr());
            Assert::AreEqual(TaskStub::getCurrentDate(), task.getDateStr());
        }

		TEST_METHOD(TestAtOption24Hrs) {
			std::string atInput = "project meeting  :At          1731  ";
            Task task = Interpreter::parseAddCmd(atInput);

            Assert::AreEqual(std::string("project meeting  "), task.getTaskName());
            Assert::IsFalse(task.isFloating()); 
            Assert::AreEqual(std::string("05:31 PM"), task.getBeginStr());
            Assert::AreEqual(std::string("07:31 PM"), task.getEndStr());
            Assert::AreEqual(TaskStub::getCurrentDate(), task.getDateStr());
        }


		TEST_METHOD(TestSpaceAfterColon) {
			std::string atInput = "project meeting :   at       531 pm";
            Task task = Interpreter::parseAddCmd(atInput);

            Assert::AreEqual(std::string("project meeting "), task.getTaskName());
            Assert::IsTrue(task.isFloating()); 
        }

		TEST_METHOD(TestFromOption) {
			std::string fromInput = "project meeting :from      309    am";
            Task task = Interpreter::parseAddCmd(fromInput);

            Assert::AreEqual(std::string("project meeting "), task.getTaskName());
            Assert::IsFalse(task.isFloating()); 
            Assert::AreEqual(std::string("03:09 AM"), task.getBeginStr());
            //Assert::AreEqual(std::string("10:40 PM"), atTask.getEndStr());
            Assert::AreEqual(TaskStub::getCurrentDate(), task.getDateStr());
        }

		TEST_METHOD(TestFromToOption) {
			std::string fromInput = "project meeting :from 1021am :to 1pm";
            Task task = Interpreter::parseAddCmd(fromInput);

            Assert::AreEqual(std::string("project meeting "), task.getTaskName());
            Assert::IsFalse(task.isFloating()); 
            Assert::AreEqual(std::string("10:21 AM"), task.getBeginStr());
            Assert::AreEqual(std::string("01:00 PM"), task.getEndStr());
            Assert::AreEqual(TaskStub::getCurrentDate(), task.getDateStr());
        }

		TEST_METHOD(TestWithoutTime) {
			std::string input = "project meeting :oN 30/07/2014";
            Task task = Interpreter::parseAddCmd(input);

            Assert::AreEqual(std::string("project meeting "), task.getTaskName());
            Assert::IsFalse(task.isFloating()); 
            Assert::AreEqual(std::string("Wed Jul 30 2014"), task.getDateStr());
            Assert::AreEqual(std::string("08:00 AM"), task.getBeginStr());
            Assert::AreEqual(std::string("10:00 AM"), task.getEndStr());
        }

		TEST_METHOD(TestTomorrowOption) {
			std::string input = "project meeting :tomorrow";
            Task task = Interpreter::parseAddCmd(input);

            Assert::AreEqual(std::string("project meeting "), task.getTaskName());
            Assert::IsFalse(task.isFloating()); 
            Assert::AreEqual(TaskStub::getTomorrowDate(), task.getDateStr());
            Assert::AreEqual(std::string("08:00 AM"), task.getBeginStr());
            Assert::AreEqual(std::string("10:00 AM"), task.getEndStr());
        }

		TEST_METHOD(TestTomorrowFromToOption) {
			std::string input = "blah :toMoRrow :FroM 7am :TO 932pm";
            Task task = Interpreter::parseAddCmd(input);

            Assert::AreEqual(std::string("blah "), task.getTaskName());
            Assert::IsFalse(task.isFloating()); 
            Assert::AreEqual(TaskStub::getTomorrowDate(), task.getDateStr());
            Assert::AreEqual(std::string("07:00 AM"), task.getBeginStr());
            Assert::AreEqual(std::string("09:32 PM"), task.getEndStr());
        }       

        // Test boundary of dates, e.g. last day, first day of months 
        TEST_METHOD(TestJanBoundary) {
			std::string firstDay = "blah :on 01/01/2015";
            Task taskFirstDay = Interpreter::parseAddCmd(firstDay);
            Assert::AreEqual(std::string("blah "), taskFirstDay.getTaskName());
            Assert::IsFalse(taskFirstDay.isFloating()); 
            Assert::AreEqual(std::string("Thu Jan 01 2015"), taskFirstDay.getDateStr());
            Assert::AreEqual(std::string("08:00 AM"), taskFirstDay.getBeginStr());
            Assert::AreEqual(std::string("10:00 AM"), taskFirstDay.getEndStr());

			std::string lastDay = "blah :on 31/01/2015";
            Task tasklastDay = Interpreter::parseAddCmd(lastDay);
            Assert::AreEqual(std::string("blah "), tasklastDay.getTaskName());
            Assert::IsFalse(tasklastDay.isFloating()); 
            Assert::AreEqual(std::string("Sat Jan 31 2015"), tasklastDay.getDateStr());
            Assert::AreEqual(std::string("08:00 AM"), tasklastDay.getBeginStr());
            Assert::AreEqual(std::string("10:00 AM"), tasklastDay.getEndStr());
        }

        TEST_METHOD(TestFebBoundary) {
			std::string firstDay = "blah :on 01/02/2015";
            Task taskFirstDay = Interpreter::parseAddCmd(firstDay);
            Assert::AreEqual(std::string("blah "), taskFirstDay.getTaskName());
            Assert::IsFalse(taskFirstDay.isFloating()); 
            Assert::AreEqual(std::string("Sun Feb 01 2015"), taskFirstDay.getDateStr());
            Assert::AreEqual(std::string("08:00 AM"), taskFirstDay.getBeginStr());
            Assert::AreEqual(std::string("10:00 AM"), taskFirstDay.getEndStr());

			std::string lastDay = "blah :on 28/02/2015";
            Task tasklastDay = Interpreter::parseAddCmd(lastDay);
            Assert::AreEqual(std::string("blah "), tasklastDay.getTaskName());
            Assert::IsFalse(tasklastDay.isFloating()); 
            Assert::AreEqual(std::string("Sat Feb 28 2015"), tasklastDay.getDateStr());
            Assert::AreEqual(std::string("08:00 AM"), tasklastDay.getBeginStr());
            Assert::AreEqual(std::string("10:00 AM"), tasklastDay.getEndStr());
        }

        TEST_METHOD(TestJuneBoundary) {
			std::string firstDay = "blah :on 01/06/2015";
            Task taskFirstDay = Interpreter::parseAddCmd(firstDay);
            Assert::AreEqual(std::string("blah "), taskFirstDay.getTaskName());
            Assert::IsFalse(taskFirstDay.isFloating()); 
            Assert::AreEqual(std::string("Mon Jun 01 2015"), taskFirstDay.getDateStr());
            Assert::AreEqual(std::string("08:00 AM"), taskFirstDay.getBeginStr());
            Assert::AreEqual(std::string("10:00 AM"), taskFirstDay.getEndStr());

			std::string lastDay = "blah :on 30/06/2015";
            Task tasklastDay = Interpreter::parseAddCmd(lastDay);
            Assert::AreEqual(std::string("blah "), tasklastDay.getTaskName());
            Assert::IsFalse(tasklastDay.isFloating()); 
            Assert::AreEqual(std::string("Tue Jun 30 2015"), tasklastDay.getDateStr());
            Assert::AreEqual(std::string("08:00 AM"), tasklastDay.getBeginStr());
            Assert::AreEqual(std::string("10:00 AM"), tasklastDay.getEndStr());
        }

        TEST_METHOD(TestDecBoundary) {
			std::string firstDay = "blah :on 01/12/2015";
            Task taskFirstDay = Interpreter::parseAddCmd(firstDay);
            Assert::AreEqual(std::string("blah "), taskFirstDay.getTaskName());
            Assert::IsFalse(taskFirstDay.isFloating()); 
            Assert::AreEqual(std::string("Tue Dec 01 2015"), taskFirstDay.getDateStr());
            Assert::AreEqual(std::string("08:00 AM"), taskFirstDay.getBeginStr());
            Assert::AreEqual(std::string("10:00 AM"), taskFirstDay.getEndStr());

			std::string lastDay = "blah :on 31/12/2015";
            Task tasklastDay = Interpreter::parseAddCmd(lastDay);
            Assert::AreEqual(std::string("blah "), tasklastDay.getTaskName());
            Assert::IsFalse(tasklastDay.isFloating()); 
            Assert::AreEqual(std::string("Thu Dec 31 2015"), tasklastDay.getDateStr());
            Assert::AreEqual(std::string("08:00 AM"), tasklastDay.getBeginStr());
            Assert::AreEqual(std::string("10:00 AM"), tasklastDay.getEndStr());
        }

        TEST_METHOD(TestLeapDay) {
			std::string lastDay = "blah :on    29/02/2016";
            Task tasklastDay = Interpreter::parseAddCmd(lastDay);
            Assert::AreEqual(std::string("blah "), tasklastDay.getTaskName());
            Assert::IsFalse(tasklastDay.isFloating()); 
            Assert::AreEqual(std::string("Mon Feb 29 2016"), tasklastDay.getDateStr());
            Assert::AreEqual(std::string("08:00 AM"), tasklastDay.getBeginStr());
            Assert::AreEqual(std::string("10:00 AM"), tasklastDay.getEndStr());
        }

        TEST_METHOD(TestPastDate) {
			std::string firstDay = "blah :on 01/01/2010";
            Task taskFirstDay = Interpreter::parseAddCmd(firstDay);
            Assert::AreEqual(std::string("blah "), taskFirstDay.getTaskName());
            Assert::IsFalse(taskFirstDay.isFloating()); 
            Assert::AreEqual(std::string("Fri Jan 01 2015"), taskFirstDay.getDateStr());
            Assert::AreEqual(std::string("08:00 AM"), taskFirstDay.getBeginStr());
            Assert::AreEqual(std::string("10:00 AM"), taskFirstDay.getEndStr());

			std::string lastDay = "blah :on 31/12/2010";
            Task tasklastDay = Interpreter::parseAddCmd(lastDay);
            Assert::AreEqual(std::string("blah "), tasklastDay.getTaskName());
            Assert::IsFalse(tasklastDay.isFloating()); 
            Assert::AreEqual(std::string("Fri Dec 31 2010"), tasklastDay.getDateStr());
            Assert::AreEqual(std::string("08:00 AM"), tasklastDay.getBeginStr());
            Assert::AreEqual(std::string("10:00 AM"), tasklastDay.getEndStr());
        }

        TEST_METHOD(TestColonInTaskName) {
			std::string input = "project me:eting :oN 30/07/2014 :from 1145pm to 2359";
            Task task = Interpreter::parseAddCmd(input);

            Assert::AreEqual(std::string("project me"), task.getTaskName());
            Assert::IsFalse(task.isFloating()); 
            Assert::AreEqual(std::string("Wed Jul 30 2014"), task.getDateStr());
            Assert::AreEqual(std::string("11:45 PM"), task.getBeginStr());
            Assert::AreEqual(std::string("11:59 PM"), task.getEndStr());
        }
        
        TEST_METHOD(TestInvalidTime) {
			std::string input = "project meeeting :oN 30/07/2014 :from 1145pm to 2359";
            Task task = Interpreter::parseAddCmd(input);

            Assert::AreEqual(std::string("project me"), task.getTaskName());
            Assert::IsFalse(task.isFloating()); 
            Assert::AreEqual(std::string("Wed Jul 30 2014"), task.getDateStr());
            Assert::AreEqual(std::string("11:45 PM"), task.getBeginStr());
            Assert::AreEqual(std::string("11:59 PM"), task.getEndStr());

        }


         /*  

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
        
        */
	};
}