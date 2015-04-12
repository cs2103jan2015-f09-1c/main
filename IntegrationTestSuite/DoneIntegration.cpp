#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace IntegrationTestSuite {		
	TEST_CLASS(DoneIntegration) {
	public:
		TEST_METHOD(DoneByName) {
			MockStorage::initMockStorage(TaskStub::getLargeTaskList());

			UIObject output = Controller::handleInput("done dummy T2");

			Assert::AreEqual(std::string("Done: dummy T2"), output.getHeaderText());
			
			TaskList taskList;
			taskList.loadTaskList(output.getTaskList());
			std::string expectedList =	"1 dummy T1\nMon Mar 09 2015 07:23 AM - 08:23 AM\ndone: 0 float: 0\n"
				+ std::string("2 dummy T2\nMon Mar 09 2015 07:23 AM - 07:23 PM\ndone: 1 float: 0\n")
				+ std::string("3 dummy T3\nMon Mar 09 2015 07:23 PM - 08:23 PM\ndone: 0 float: 0\n");
			Assert::AreEqual(expectedList, taskList.toString());
			

		}


		TEST_METHOD(DoneByNumber) {
			MockStorage::initMockStorage(TaskStub::getLargeTaskList());

			UIObject viewOutput = Controller::handleInput("view all");
			TextUI::showOutput(viewOutput);

			UIObject output = Controller::handleInput("done 3");

			std::string expectedHeader = "Done: dummy T3";
			Assert::AreEqual(expectedHeader, output.getHeaderText());

			TaskList taskList;
			taskList.loadTaskList(output.getTaskList());
			std::string expectedList =	"1 dummy T1\nMon Mar 09 2015 07:23 AM - 08:23 AM\ndone: 0 float: 0\n"
				+ std::string("2 dummy T2\nMon Mar 09 2015 07:23 AM - 07:23 PM\ndone: 1 float: 0\n")
				+ std::string("3 dummy T3\nMon Mar 09 2015 07:23 PM - 08:23 PM\ndone: 1 float: 0\n");
			Assert::AreEqual(expectedList, taskList.toString());

			MockStorage::cleanMockStorage();
		}

		TEST_METHOD(UndoAfterDone) {
			MockStorage::initMockStorage(TaskStub::getLargeTaskList());

			Controller::handleInput("done dummy T4");
			UIObject output = Controller::handleInput("undo");

			Assert::AreEqual(std::string("dummy T4 has been marked undone!"), output.getHeaderText());

			TaskList taskList;
			taskList.loadTaskList(output.getTaskList());
			std::string expectedList =	"4 dummy T4\nTue Mar 10 2015 07:23 AM - 08:23 AM\ndone: 0 float: 0\n"
				+ std::string("5 dummy T5\nTue Mar 10 2015 07:23 PM - 08:23 PM\ndone: 0 float: 0\n");

			Assert::AreEqual(expectedList, taskList.toString());
			MockStorage::cleanMockStorage();
		}

		TEST_METHOD(InvalidDone) {
			MockStorage::initMockStorage(TaskStub::getSmallTaskList());
			
			UIObject garbageOutput = Controller::handleInput("done %&*#");
			Assert::AreEqual(std::string("There is no matching task to be marked done."), garbageOutput.getHeaderText());
			Assert::IsTrue(garbageOutput.getTaskList().empty());

			MockStorage::cleanMockStorage();
		}

		
		TEST_METHOD(DoneHelp) {
			UIObject noSpecifier = Controller::handleInput("done"); // THIS CRASHES !!
			std::string help;

			std::string title = "***************** COMMAND HELP: DONE  *****************\n\n";

			std::string intro = "The done command allows you to mark done your task \n\n"; 

			std::string pt1 = "1. This command can be invoked by typing done [task number / task name] \n";
			pt1 = pt1 + "Example: done 1 \n";
			pt1 = pt1 + "         done meet mum \n";

			help = title + intro + pt1;

			Assert::AreEqual(std::string(help), noSpecifier.getHeaderText());
			Assert::IsTrue(noSpecifier.getTaskList().empty());
		}
		
	};
}