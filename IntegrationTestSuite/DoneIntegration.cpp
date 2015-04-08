#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace IntegrationTestSuite {		
	TEST_CLASS(DoneIntegration) {
	public:
		TEST_METHOD(DoneByName) {
			MockStorage::initMockStorage(TaskStub::getLargeTaskList());

			UIObject controllerOutput = Controller::handleInput("done dummy T5");

			Assert::AreEqual(std::string("Done: dummy T5"), controllerOutput.getHeaderText());

			TaskList::TList list = controllerOutput.getTaskList();
			TaskList taskList;
			taskList.loadTaskList(list);
			std::string expectedList =	"4 dummy T4\nTue Mar 10 2015 07:23 AM - 08:23 AM\ndone: 0 float: 0\n "
				+ std::string("5 dummy T5\nTue Mar 10 2015 07:23 PM - 08:23 PM\ndone: 0 float: 0\n ");
			Assert::AreEqual(expectedList, taskList.toString());

			MockStorage::cleanMockStorage();
		}


		TEST_METHOD(DoneByNumber) {
			MockStorage::initMockStorage(TaskStub::getLargeTaskList());

			UIObject viewOutput = Controller::handleInput("view all");
			TextUI::showOutput(viewOutput);

			UIObject del2Output = Controller::handleInput("done 2");

			std::string expectedHeader = "Done: dummy T2";
			Assert::AreEqual(expectedHeader, del2Output.getHeaderText());

			TaskList::TList list = del2Output.getTaskList();
			TaskList taskList;
			taskList.loadTaskList(list);
			std::string expectedList = "1 dummy T1\nMon Mar 09 2015 07:23 AM - 08:23 AM\ndone: 0 float: 0\n"
				+ std::string("2 dummy T3\nMon Mar 09 2015 07:23 PM - 08:23 PM\ndone: 0 float: 0\n")
				+ std::string("3 dummy T3\nMon Mar 09 2015 07:23 PM - 08:23 PM\ndone: 0 float: 0\n");
			Assert::AreEqual(expectedList, taskList.toString());

			MockStorage::cleanMockStorage();
		}

		TEST_METHOD(UndoAfterDone) {
			MockStorage::initMockStorage(TaskStub::getLargeTaskList());

			Controller::handleInput("done dummy T5");
			Controller::handleInput("done dummy T4");
			UIObject undoOutput = Controller::handleInput("undo");

			Assert::AreEqual(std::string("dummy T4 has been marked undone!"), undoOutput.getHeaderText());

			MockStorage::cleanMockStorage();
		}

		TEST_METHOD(InvalidDone) {
			MockStorage::initMockStorage(TaskStub::getSmallTaskList());
			
			UIObject garbageOutput = Controller::handleInput("delete %&*#");
			Assert::AreEqual(std::string("There is no matching task to be marked done."), garbageOutput.getHeaderText());
			Assert::IsTrue(garbageOutput.getTaskList().empty());

			UIObject viewOutput = Controller::handleInput("view all");
			TextUI::showOutput(viewOutput);
			UIObject outOfRange = Controller::handleInput("done 9");
			Assert::AreEqual(std::string("There is no matching task to be marked done."), outOfRange.getHeaderText());
			Assert::IsTrue(outOfRange.getTaskList().empty());

			MockStorage::cleanMockStorage();
		}
		/*
		TEST_METHOD(DoneHelp) {
			UIObject noSpecifier = Controller::handleInput("done"); // THIS CRASHES !!
			Assert::AreEqual(std::string("Done command help goes here"), noSpecifier.getHeaderText());
			Assert::IsTrue(noSpecifier.getTaskList().empty());
		}
		*/
	};
}