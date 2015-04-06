#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace IntegrationTestSuite {		
	TEST_CLASS(ViewIntegration) {
	public:
		TEST_METHOD(ViewAll) {
			MockStorage::initMockStorage(TaskStub::getLargeTaskList());

			UIObject controllerOutput = Controller::handleInput("view all");

			TaskList::TList list = controllerOutput.getTaskList();
			TaskList taskList;
			taskList.loadTaskList(list);
			std::string expectedList = "1 dummy T1\nMon Mar 09 2015 07:23 AM - 08:23 AM\ndone: 0 float: 0\n"
				+ std::string("2 dummy T2\nMon Mar 09 2015 07:23 AM - 07:23 PM\ndone: 0 float: 0\n")
				+ std::string("3 dummy T3\nMon Mar 09 2015 07:23 PM - 08:23 PM\ndone: 0 float: 0\n")
				+ std::string("4 dummy T4\nTue Mar 10 2015 07:23 AM - 08:23 AM\ndone: 0 float: 0\n ")
				+ std::string("5 dummy T5\nTue Mar 10 2015 07:23 PM - 08:23 PM\ndone: 0 float: 0\n ")
				+ std::string("6 dummy T6\nWed Mar 11 2015 07:23 AM - 07:23 AM\ndone: 0 float: 0\n ")
				+ std::string("7 dummy T7\nWed Mar 11 2015 07:23 AM - 07:23 PM\ndone: 0 float: 0\n ")
				+ std::string("8 dummy T8\nWed Mar 11 2015 07:23 AM - 08:23 AM\ndone: 0 float: 0\n "); 

			Assert::AreEqual(expectedList, taskList.toString());

			MockStorage::cleanMockStorage();
		}

		/*
		TEST_METHOD(ViewWednesday) {
			MockStorage::initMockStorage(TaskStub::getLargeTaskList());
			Controller::handleInput("view wednesday");
			UIObject controllerOutput = Controller::handleInput("view dummy T4");
			
			Assert::AreEqual(std::string("No more tasks for that day!"), controllerOutput.getHeaderText());

			TaskList::TList list = controllerOutput.getTaskList();
			Assert::IsTrue(list.empty());

			MockStorage::cleanMockStorage();
		}*/

		/*
		TEST_METHOD(ViewHelp) {
			UIObject noSpecifier = Controller::handleInput("view"); // THIS CRASHES !!
			Assert::AreEqual(std::string("view command help goes here"), noSpecifier.getHeaderText());
			Assert::IsTrue(noSpecifier.getTaskList().empty());
		}
		*/
	};
}