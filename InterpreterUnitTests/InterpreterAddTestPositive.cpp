#include "stdafx.h"
#include "CppUnitTest.h"
#include "CommandType.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace MyCalTestSuite {
	TEST_CLASS(InterpreterAddPositiveTest) {
	public:
		TEST_METHOD(TestFloating) {
            Task floatingTask = Interpreter::parseAddCmd("CS2103 tutorial");
            Assert::AreEqual(std::string("CS2103 tutorial"), floatingTask.getTaskName());
            Assert::IsTrue(floatingTask.isFloating()); 
        }

		TEST_METHOD(Test12HrsFormat) {
            Task task = Interpreter::parseAddCmd("project meeting :at 531 pm");

            Assert::AreEqual(std::string("project meeting "), task.getTaskName());
            Assert::IsFalse(task.isFloating()); 
            Assert::AreEqual(std::string("05:31 PM"), task.getBeginStr());
            Assert::AreEqual(std::string("07:31 PM"), task.getEndStr());
            Assert::AreEqual(TaskStub::getCurrentDate(), task.getDateStr());
        }

		TEST_METHOD(Test24HrsFormat) {
            Task task = Interpreter::parseAddCmd("project meeting :at 1731");

            Assert::AreEqual(std::string("project meeting "), task.getTaskName());
            Assert::IsFalse(task.isFloating()); 
            Assert::AreEqual(std::string("05:31 PM"), task.getBeginStr());
            Assert::AreEqual(std::string("07:31 PM"), task.getEndStr());
            Assert::AreEqual(TaskStub::getCurrentDate(), task.getDateStr());
        }

		TEST_METHOD(TestDateSeparatorFormats) {
            Task task = Interpreter::parseAddCmd("project :on 11.12.2014");

            Assert::AreEqual(std::string("project "), task.getTaskName());
            Assert::IsFalse(task.isFloating()); 
            Assert::AreEqual(std::string("08:00 AM"), task.getBeginStr());
            Assert::AreEqual(std::string("10:00 AM"), task.getEndStr());
            Assert::AreEqual(std::string("Thu Dec 11 2014"), task.getDateStr());

            Task task2 = Interpreter::parseAddCmd("project :on 11/12/2014");
            Assert::AreEqual(std::string("Thu Dec 11 2014"), task2.getDateStr());

            Task task3 = Interpreter::parseAddCmd("project :on 11\\12.2014");
            Assert::AreEqual(std::string("Thu Dec 11 2014"), task3.getDateStr());
        }

		TEST_METHOD(TestFromOptionOnly) {
            Task task = Interpreter::parseAddCmd("project meeting :from 309am");

            Assert::AreEqual(std::string("project meeting "), task.getTaskName());
            Assert::IsFalse(task.isFloating()); 
            Assert::AreEqual(std::string("03:09 AM"), task.getBeginStr());
            Assert::AreEqual(std::string("05:09 AM"), task.getEndStr());
            Assert::AreEqual(TaskStub::getCurrentDate(), task.getDateStr());
        }


		TEST_METHOD(TestToOptionOnly) {
            Task task = Interpreter::parseAddCmd("project meeting :to 309am");

            Assert::AreEqual(std::string("project meeting "), task.getTaskName());
            Assert::IsFalse(task.isFloating()); 
            Assert::AreEqual(std::string("01:09 AM"), task.getBeginStr());
            Assert::AreEqual(std::string("03:09 AM"), task.getEndStr());
            Assert::AreEqual(TaskStub::getCurrentDate(), task.getDateStr());
        }

		TEST_METHOD(TestFromToOption) {
            Task task = Interpreter::parseAddCmd("project meeting :from 1021am :to 1pm");

            Assert::AreEqual(std::string("project meeting "), task.getTaskName());
            Assert::IsFalse(task.isFloating()); 
            Assert::AreEqual(std::string("10:21 AM"), task.getBeginStr());
            Assert::AreEqual(std::string("01:00 PM"), task.getEndStr());
            Assert::AreEqual(TaskStub::getCurrentDate(), task.getDateStr());
        }


		TEST_METHOD(TestFromToAlternateFormat) {
            Task task = Interpreter::parseAddCmd("project meeting :from 1021am-1pm");

            Assert::AreEqual(std::string("project meeting "), task.getTaskName());
            Assert::IsFalse(task.isFloating()); 
            Assert::AreEqual(std::string("10:21 AM"), task.getBeginStr());
            Assert::AreEqual(std::string("01:00 PM"), task.getEndStr());
            Assert::AreEqual(TaskStub::getCurrentDate(), task.getDateStr());
        }

		TEST_METHOD(TestCaseInsensitivity) {
            Task task = Interpreter::parseAddCmd("project meeting :oN 13/08/2015 :FRoM 1021am :To 1pm");

            Assert::AreEqual(std::string("project meeting "), task.getTaskName());
            Assert::IsFalse(task.isFloating()); 
            Assert::AreEqual(std::string("10:21 AM"), task.getBeginStr());
            Assert::AreEqual(std::string("01:00 PM"), task.getEndStr());
            Assert::AreEqual(std::string("Thu Aug 13 2015"), task.getDateStr());
        }

		TEST_METHOD(TestSpaceInsensitivity) {
            Task task = Interpreter::parseAddCmd("project : o n  1 3 / 0  8 /  2  0 15    : f r om  1 02 1 a m   :to   1p  m");

            Assert::AreEqual(std::string("project "), task.getTaskName());
            Assert::IsFalse(task.isFloating()); 
            Assert::AreEqual(std::string("10:21 AM"), task.getBeginStr());
            Assert::AreEqual(std::string("01:00 PM"), task.getEndStr());
            Assert::AreEqual(std::string("Thu Aug 13 2015"), task.getDateStr());
        }

		TEST_METHOD(TestWithoutTime) {
            Task task = Interpreter::parseAddCmd("project meeting :on 30/07/2014");

            Assert::AreEqual(std::string("project meeting "), task.getTaskName());
            Assert::IsFalse(task.isFloating()); 
            Assert::AreEqual(std::string("Wed Jul 30 2014"), task.getDateStr());
            Assert::AreEqual(std::string("08:00 AM"), task.getBeginStr());
            Assert::AreEqual(std::string("10:00 AM"), task.getEndStr());
        }

		TEST_METHOD(TestTomorrowOption) {
            Task task = Interpreter::parseAddCmd("project meeting :tomorrow");

            Assert::AreEqual(std::string("project meeting "), task.getTaskName());
            Assert::IsFalse(task.isFloating()); 
            Assert::AreEqual(TaskStub::getTomorrowDate(), task.getDateStr());
            Assert::AreEqual(std::string("08:00 AM"), task.getBeginStr());
            Assert::AreEqual(std::string("10:00 AM"), task.getEndStr());
        }

		TEST_METHOD(TestTomorrowFromToOption) {
            Task task = Interpreter::parseAddCmd("blah :tomorrow :from 7am :to 932pm");

            Assert::AreEqual(std::string("blah "), task.getTaskName());
            Assert::IsFalse(task.isFloating()); 
            Assert::AreEqual(TaskStub::getTomorrowDate(), task.getDateStr());
            Assert::AreEqual(std::string("07:00 AM"), task.getBeginStr());
            Assert::AreEqual(std::string("09:32 PM"), task.getEndStr());
        }       

        // Test boundary of dates, e.g. last day, first day of months 
        TEST_METHOD(TestJanBoundary) {
            Task taskFirstDay = Interpreter::parseAddCmd("blah :on 01/01/2015");
            Assert::AreEqual(std::string("blah "), taskFirstDay.getTaskName());
            Assert::IsFalse(taskFirstDay.isFloating()); 
            Assert::AreEqual(std::string("Thu Jan 01 2015"), taskFirstDay.getDateStr());
            Assert::AreEqual(std::string("08:00 AM"), taskFirstDay.getBeginStr());
            Assert::AreEqual(std::string("10:00 AM"), taskFirstDay.getEndStr());

            Task tasklastDay = Interpreter::parseAddCmd("blah :on 31/01/2015");
            Assert::AreEqual(std::string("blah "), tasklastDay.getTaskName());
            Assert::IsFalse(tasklastDay.isFloating()); 
            Assert::AreEqual(std::string("Sat Jan 31 2015"), tasklastDay.getDateStr());
            Assert::AreEqual(std::string("08:00 AM"), tasklastDay.getBeginStr());
            Assert::AreEqual(std::string("10:00 AM"), tasklastDay.getEndStr());
        }

        TEST_METHOD(TestFebBoundary) {
            Task taskFirstDay = Interpreter::parseAddCmd("blah :on 01/02/2015");
            Assert::AreEqual(std::string("blah "), taskFirstDay.getTaskName());
            Assert::IsFalse(taskFirstDay.isFloating()); 
            Assert::AreEqual(std::string("Sun Feb 01 2015"), taskFirstDay.getDateStr());
            Assert::AreEqual(std::string("08:00 AM"), taskFirstDay.getBeginStr());
            Assert::AreEqual(std::string("10:00 AM"), taskFirstDay.getEndStr());

            Task tasklastDay = Interpreter::parseAddCmd("blah :on 28/02/2015");
            Assert::AreEqual(std::string("blah "), tasklastDay.getTaskName());
            Assert::IsFalse(tasklastDay.isFloating()); 
            Assert::AreEqual(std::string("Sat Feb 28 2015"), tasklastDay.getDateStr());
            Assert::AreEqual(std::string("08:00 AM"), tasklastDay.getBeginStr());
            Assert::AreEqual(std::string("10:00 AM"), tasklastDay.getEndStr());
        }

        TEST_METHOD(TestJuneBoundary) {
            Task taskFirstDay = Interpreter::parseAddCmd("blah :on 01/06/2015");
            Assert::AreEqual(std::string("blah "), taskFirstDay.getTaskName());
            Assert::IsFalse(taskFirstDay.isFloating()); 
            Assert::AreEqual(std::string("Mon Jun 01 2015"), taskFirstDay.getDateStr());
            Assert::AreEqual(std::string("08:00 AM"), taskFirstDay.getBeginStr());
            Assert::AreEqual(std::string("10:00 AM"), taskFirstDay.getEndStr());

            Task tasklastDay = Interpreter::parseAddCmd("blah :on 30/06/2015");
            Assert::AreEqual(std::string("blah "), tasklastDay.getTaskName());
            Assert::IsFalse(tasklastDay.isFloating()); 
            Assert::AreEqual(std::string("Tue Jun 30 2015"), tasklastDay.getDateStr());
            Assert::AreEqual(std::string("08:00 AM"), tasklastDay.getBeginStr());
            Assert::AreEqual(std::string("10:00 AM"), tasklastDay.getEndStr());
        }

        TEST_METHOD(TestDecBoundary) {
            Task taskFirstDay = Interpreter::parseAddCmd("blah :on 01/12/2015");
            Assert::AreEqual(std::string("blah "), taskFirstDay.getTaskName());
            Assert::IsFalse(taskFirstDay.isFloating()); 
            Assert::AreEqual(std::string("Tue Dec 01 2015"), taskFirstDay.getDateStr());
            Assert::AreEqual(std::string("08:00 AM"), taskFirstDay.getBeginStr());
            Assert::AreEqual(std::string("10:00 AM"), taskFirstDay.getEndStr());

            Task tasklastDay = Interpreter::parseAddCmd("blah :on 31/12/2015");
            Assert::AreEqual(std::string("blah "), tasklastDay.getTaskName());
            Assert::IsFalse(tasklastDay.isFloating()); 
            Assert::AreEqual(std::string("Thu Dec 31 2015"), tasklastDay.getDateStr());
            Assert::AreEqual(std::string("08:00 AM"), tasklastDay.getBeginStr());
            Assert::AreEqual(std::string("10:00 AM"), tasklastDay.getEndStr());
        }

        TEST_METHOD(TestLeapDay) {
            Task tasklastDay = Interpreter::parseAddCmd("blah :on 29/02/2016");
            Assert::AreEqual(std::string("blah "), tasklastDay.getTaskName());
            Assert::IsFalse(tasklastDay.isFloating()); 
            Assert::AreEqual(std::string("Mon Feb 29 2016"), tasklastDay.getDateStr());
            Assert::AreEqual(std::string("08:00 AM"), tasklastDay.getBeginStr());
            Assert::AreEqual(std::string("10:00 AM"), tasklastDay.getEndStr());
        }

        TEST_METHOD(TestPastDate) {
            Task taskFirstDay = Interpreter::parseAddCmd("blah :on 01/01/1971");
            Assert::AreEqual(std::string("blah "), taskFirstDay.getTaskName());
            Assert::IsFalse(taskFirstDay.isFloating()); 
            Assert::AreEqual(std::string("Fri Jan 01 1971"), taskFirstDay.getDateStr());
            Assert::AreEqual(std::string("08:00 AM"), taskFirstDay.getBeginStr());
            Assert::AreEqual(std::string("10:00 AM"), taskFirstDay.getEndStr());

            Task tasklastDay = Interpreter::parseAddCmd("blah :on 31/12/1971");
            Assert::AreEqual(std::string("blah "), tasklastDay.getTaskName());
            Assert::IsFalse(tasklastDay.isFloating()); 
            Assert::AreEqual(std::string("Fri Dec 31 1971"), tasklastDay.getDateStr());
            Assert::AreEqual(std::string("08:00 AM"), tasklastDay.getBeginStr());
            Assert::AreEqual(std::string("10:00 AM"), tasklastDay.getEndStr());
        }

        TEST_METHOD(TestFutureDate) {
            Task taskFirstDay = Interpreter::parseAddCmd("blah :on 01/01/2200");
            Assert::AreEqual(std::string("blah "), taskFirstDay.getTaskName());
            Assert::IsFalse(taskFirstDay.isFloating()); 
            Assert::AreEqual(std::string("Wed Jan 01 2200"), taskFirstDay.getDateStr());
            Assert::AreEqual(std::string("08:00 AM"), taskFirstDay.getBeginStr());
            Assert::AreEqual(std::string("10:00 AM"), taskFirstDay.getEndStr());

            Task tasklastDay = Interpreter::parseAddCmd("blah :on 31/12/2200");
            Assert::AreEqual(std::string("blah "), tasklastDay.getTaskName());
            Assert::IsFalse(tasklastDay.isFloating()); 
            Assert::AreEqual(std::string("Wed Dec 31 2200"), tasklastDay.getDateStr());
            Assert::AreEqual(std::string("08:00 AM"), tasklastDay.getBeginStr());
            Assert::AreEqual(std::string("10:00 AM"), tasklastDay.getEndStr());
        }

        TEST_METHOD(TestColonInTaskName) {
            Task task = Interpreter::parseAddCmd("project me:eting :on 30/07/2014 :from 1145pm to 2359");

            Assert::AreEqual(std::string("project me"), task.getTaskName());
            Assert::IsFalse(task.isFloating()); 
            Assert::AreEqual(std::string("Wed Jul 30 2014"), task.getDateStr());
            Assert::AreEqual(std::string("11:45 PM"), task.getBeginStr());
            Assert::AreEqual(std::string("11:59 PM"), task.getEndStr());
        }
        
        // If an unrecognized option is entered, task will default to floating
        TEST_METHOD(TestUnrecognizedOption) {        
            Task task = Interpreter::parseAddCmd("project meeting :zzz 05/01/2015");

            Assert::AreEqual(std::string("project meeting "), task.getTaskName());
            Assert::IsTrue(task.isFloating());     
        }
	};
}