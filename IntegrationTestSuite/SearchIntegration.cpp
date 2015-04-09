#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace IntegrationTestSuite {		
	TEST_CLASS(SearchIntegration) {
	public:
		TEST_METHOD(Search_found) {
			MockStorage::initMockStorage(TaskStub::getLargeTaskList());

			UIObject controllerOutput = Controller::handleInput("search dummy T4");

			Assert::AreEqual(std::string("Tasks found:"), controllerOutput.getHeaderText());

			TaskList::TList list = controllerOutput.getTaskList();
			TaskList taskList;
			taskList.loadTaskList(list);
			std::string expectedList = "4 dummy T4\nTue Mar 10 2015 07:23 AM - 08:23 AM\ndone: 0 float: 0\n";
			Assert::AreEqual(expectedList, taskList.toString());

			MockStorage::cleanMockStorage();
		}

		TEST_METHOD(Search_notfound) {
			MockStorage::initMockStorage(TaskStub::getLargeTaskList());
			UIObject controllerOutput = Controller::handleInput("search meeting");
			
			Assert::AreEqual(std::string("There are no matching results"), controllerOutput.getHeaderText());

			TaskList::TList list = controllerOutput.getTaskList();
			Assert::IsTrue(list.empty());

			MockStorage::cleanMockStorage();
		}
	};
}