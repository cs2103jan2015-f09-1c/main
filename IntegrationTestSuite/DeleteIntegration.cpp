#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace IntegrationTestSuite {		
	TEST_CLASS(DeleteIntegration) {
	public:
		TEST_METHOD(DeleteByName) {
			MockStorage::initMockStorage(TaskStub::getLargeTaskList());

			UIObject controllerOutput = Controller::handleInput("delete dummy T5");

			Assert::AreEqual(std::string("Remaining tasks for that day:"), controllerOutput.getHeaderText());

			TaskList::TList list = controllerOutput.getTaskList();
			TaskList taskList;
			taskList.loadTaskList(list);
			std::string expectedList = "4 dummy T4\nTue Mar 10 2015 07:23 AM - 08:23 AM\ndone: 0 float: 0\n";
			Assert::AreEqual(expectedList, taskList.toString());

			MockStorage::cleanMockStorage();
		}

		TEST_METHOD(DeleteTillEmpty) {
			MockStorage::initMockStorage(TaskStub::getLargeTaskList());
			Controller::handleInput("delete dummy T5");
			UIObject controllerOutput = Controller::handleInput("delete dummy T4");
			
			Assert::AreEqual(std::string("No more tasks for that day!"), controllerOutput.getHeaderText());

			TaskList::TList list = controllerOutput.getTaskList();
			Assert::IsTrue(list.empty());

			MockStorage::cleanMockStorage();
		}

		TEST_METHOD(DeleteByNumber) {
			MockStorage::initMockStorage(TaskStub::getLargeTaskList());

			UIObject viewOutput = Controller::handleInput("view all");
			TextUI::showOutput(viewOutput);

			UIObject del2Output = Controller::handleInput("delete 2");

			std::string expectedHeader = "Remaining tasks for that day:";
			Assert::AreEqual(expectedHeader, del2Output.getHeaderText());

			TaskList::TList list = del2Output.getTaskList();
			TaskList taskList;
			taskList.loadTaskList(list);
			std::string expectedList = "1 dummy T1\nMon Mar 09 2015 07:23 AM - 08:23 AM\ndone: 0 float: 0\n"
				+ std::string("3 dummy T3\nMon Mar 09 2015 07:23 PM - 08:23 PM\ndone: 0 float: 0\n");
			Assert::AreEqual(expectedList, taskList.toString());

			MockStorage::cleanMockStorage();
		}

		TEST_METHOD(UndoAfterDel) {
			MockStorage::initMockStorage(TaskStub::getLargeTaskList());

			Controller::handleInput("delete dummy T5");
			Controller::handleInput("delete dummy T4");
			UIObject undoOutput = Controller::handleInput("undo");

			Assert::AreEqual(std::string("Undo successfully."), undoOutput.getHeaderText());

			MockStorage::cleanMockStorage();
		}

		TEST_METHOD(InvalidDelete) {
			MockStorage::initMockStorage(TaskStub::getSmallTaskList());
			
			UIObject garbageOutput = Controller::handleInput("delete %&*#");
			Assert::AreEqual(std::string("There is no matching task to be deleted."), garbageOutput.getHeaderText());
			Assert::IsTrue(garbageOutput.getTaskList().empty());

			UIObject viewOutput = Controller::handleInput("view all");
			TextUI::showOutput(viewOutput);
			UIObject outOfRange = Controller::handleInput("delete 9");
			Assert::AreEqual(std::string("There is no matching task to be deleted."), outOfRange.getHeaderText());
			Assert::IsTrue(outOfRange.getTaskList().empty());

			MockStorage::cleanMockStorage();
		}

		/*TEST_METHOD(DeleteHelp) {
			UIObject noSpecifier = Controller::handleInput("delete");
			Assert::AreEqual(std::string("Delete command help goes here"), noSpecifier.getHeaderText());
			Assert::IsTrue(noSpecifier.getTaskList().empty());
		}*/
	};
}