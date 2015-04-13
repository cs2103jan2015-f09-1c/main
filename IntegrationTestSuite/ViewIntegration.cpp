//@author A0113736J
#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace IntegrationTestSuite {		
	TEST_CLASS(ViewIntegration) {
	public:
		TEST_METHOD(ViewAll) {
			MockStorage::initMockStorage(TaskStub::getAprTaskList());

			UIObject controllerOutput = Controller::handleInput("view all");

			TaskList::TList list = controllerOutput.getTaskList();
			TaskList taskList;
			taskList.loadTaskList(list);
			std::string expectedList = "9 dummy T9\nMon Apr 06 2015 09:00 AM - 10:00 AM\ndone: 0 float: 0\n"
				+ std::string("10 dummy T10\nTue Apr 07 2015 09:00 AM - 09:00 PM\ndone: 0 float: 0\n")
				+ std::string("11 dummy T11\nWed Apr 08 2015 09:00 AM - 09:00 PM\ndone: 0 float: 0\n")
				+ std::string("12 dummy T12\nThu Apr 09 2015 09:00 AM - 10:00 AM\ndone: 0 float: 0\n")
				+ std::string("13 dummy T13\nFri Apr 10 2015 09:00 AM - 09:00 PM\ndone: 0 float: 0\n")
				+ std::string("14 dummy T14\nFri Apr 10 2015 09:00 AM - 10:00 AM\ndone: 0 float: 0\n")
				+ std::string("15 dummy T15\nSun Apr 12 2015 09:00 AM - 09:00 PM\ndone: 0 float: 0\n")
				+ std::string("16 dummy T16\nMon Apr 13 2015 09:00 AM - 10:00 AM\ndone: 0 float: 0\n")
				+ std::string("17 dummy T17\nTue Apr 14 2015 09:00 AM - 09:00 PM\ndone: 0 float: 0\n")
				+ std::string("18 dummy T18\nWed Apr 15 2015 09:00 AM - 09:00 PM\ndone: 0 float: 0\n")
				+ std::string("19 dummy T19\nThu Apr 16 2015 09:00 AM - 10:00 AM\ndone: 0 float: 0\n")
				+ std::string("20 dummy T20\nThu Apr 16 2015 09:00 AM - 09:00 PM\ndone: 0 float: 0\n")
				+ std::string("21 dummy T21\nFri Apr 17 2015 09:00 AM - 10:00 AM\ndone: 0 float: 0\n")
				+ std::string("22 dummy T22\nSun Apr 19 2015 09:00 AM - 09:00 PM\ndone: 0 float: 0\n");
		

			Assert::AreEqual(expectedList, taskList.toString());

			MockStorage::cleanMockStorage();
		}

		TEST_METHOD(ViewToday) {
			MockStorage::initMockStorage(TaskStub::getCurrentTaskList());

			UIObject controllerOutput = Controller::handleInput("view today");

			TaskList::TList list = controllerOutput.getTaskList();
			TaskList taskList;
			taskList.loadTaskList(list);
			std::string expectedList = "23 dummy T23\n09:00 AM - 09:00 PM\ndone: 0 float: 0\n";

			Assert::AreEqual(expectedList, taskList.toStringWithoutDate());

			MockStorage::cleanMockStorage();
		}

		TEST_METHOD(ViewTomorrow) {
			MockStorage::initMockStorage(TaskStub::getCurrentTaskList());

			UIObject controllerOutput = Controller::handleInput("view tomorrow");

			TaskList::TList list = controllerOutput.getTaskList();
			TaskList taskList;
			taskList.loadTaskList(list);
			std::string expectedList = "24 dummy T24\n09:00 AM - 09:00 PM\ndone: 0 float: 0\n";


			Assert::AreEqual(expectedList, taskList.toStringWithoutDate());

			MockStorage::cleanMockStorage();
		}


        TEST_METHOD(ViewHelp) {
            UIObject noSpecifier = Controller::handleInput("view"); 
            std::string help;

            std::string title = "***************** COMMAND HELP: VIEW  *****************\n\n";

            std::string intro = "The view command allows you to view your tasklist on daily and weekly basis \n\n"; 

            std::string pt1 = "1. This command can be invoked by typing view [today/tomorrow/weekly/ \n";
            pt1 = pt1 + "   monday-sunday]\n";
            pt1 = pt1 + "Example: view today \n";

            help = title + intro + pt1;


            Assert::AreEqual(std::string(help), noSpecifier.getHeaderText());
            Assert::IsTrue(noSpecifier.getTaskList().empty());
        }
		
	};
}