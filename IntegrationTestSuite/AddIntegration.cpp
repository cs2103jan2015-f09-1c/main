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
	};
}