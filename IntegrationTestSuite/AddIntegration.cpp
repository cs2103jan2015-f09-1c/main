#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace IntegrationTestSuite {		
	TEST_CLASS(AddIntegration) {
	public:
		TEST_METHOD(AddFloating) {
			MockStorage::initMockStorage(TaskStub::getSmallTaskList());

			UIObject output = Controller::handleInput("add I am a floating task");
			Assert::AreEqual(std::string("Task added"), output.getHeaderText());

			TaskList taskList;
			taskList.loadTaskList(output.getTaskList());
			std::string expectedList = "6 I am a floating task\nThu Jan 01 1970 08:00 AM - 08:00 AM\ndone: 0 float: 1\n";
			Assert::AreEqual(expectedList, taskList.toString());

			MockStorage::cleanMockStorage();
		}
		
		/*TEST_METHOD(AddOnDate) {
			MockStorage::initMockStorage(TaskStub::getSmallTaskList());

			UIObject output = Controller::handleInput("add submit application :on 01/01/2017");
			Assert::AreEqual(std::string("Task added."), output.getHeaderText());

			TaskList taskList;
			taskList.loadTaskList(output.getTaskList());
			std::string expectedList = "6 submit application\nThu Jan 01 1970 08:00 AM - 08:00 AM\ndone: 0 float: 0\n";
			Assert::AreEqual(expectedList, taskList.toString());

			MockStorage::cleanMockStorage();
		}


		TEST_METHOD(AddFromTo) {
			MockStorage::initMockStorage(TaskStub::getSmallTaskList());

			UIObject output = Controller::handleInput("add drama performance @UCC :from 8pm to 10pm");
			
			MockStorage::cleanMockStorage();
		}

		TEST_METHOD(AddAt) {
			MockStorage::initMockStorage(TaskStub::getSmallTaskList());
			MockStorage::cleanMockStorage();
		}

		TEST_METHOD(AddTomorrow) {
			MockStorage::initMockStorage(TaskStub::getSmallTaskList());
			MockStorage::cleanMockStorage();
		}

		TEST_METHOD(AddNextWeek) {
			MockStorage::initMockStorage(TaskStub::getSmallTaskList());
			MockStorage::cleanMockStorage();
		}

		TEST_METHOD(InvalidAdd) {
			MockStorage::initMockStorage(TaskStub::getSmallTaskList());
			// something not a time
			//typo errors
			// invalid date
			// start time later than end time
			// adding a date which has already passed
			MockStorage::cleanMockStorage();
		}

		TEST_METHOD(AddHelp) {
			UIObject noSpecifier = Controller::handleInput("add");
			Assert::AreEqual(std::string("Add command help goes here"), noSpecifier.getHeaderText());
			Assert::IsTrue(noSpecifier.getTaskList().empty());
		}


		TEST_METHOD(UndoAfterAdd) {
			MockStorage::initMockStorage(TaskStub::getSmallTaskList());

			MockStorage::cleanMockStorage();
		}*/
	};
}