#include "stdafx.h"
#include "CppUnitTest.h"
#include <stdio.h>
#include <fstream>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace MyCalTestSuite {
	TEST_CLASS(TextUITest) {
	public: 
		TEST_METHOD(TestHeaderText) { 
			UIObject uiObj;

			uiObj.setHeaderText("Successfully Edited");
			Assert::AreEqual(std::string("Successfully Edited"), uiObj.getHeaderText());
		}


	};
}