#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace IntegrationTestSuite {		
	TEST_CLASS(DeleteIntegration) {
	public:
		TEST_METHOD_INITIALIZE(InitDeleteIntegration) {
			MCLogger::log("---------------Begin Delete Integration test------------------");
			MockStorage::initMockStorage(TaskStub::getLargeTaskList());
		}
		TEST_METHOD(TestMethod1)
		{
			// TODO: Your test code here
		}

		TEST_METHOD_CLEANUP(CleanupDeleteIntegration) {
			MockStorage::cleanMockStorage();
			MCLogger::log("---------------End Delete Integration test------------------");
		}

	};
}