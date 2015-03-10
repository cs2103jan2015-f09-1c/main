#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace MyCalTestSuite {
    
	TEST_CLASS(StorageTest) {
	public:
        time_t sampleTime() {
            time_t rawTime;
            tm sampleTime;
            sampleTime.tm_hour = 7;
            sampleTime.tm_isdst = 0;
            sampleTime.tm_mday = 9;
            sampleTime.tm_min = 23;
            sampleTime.tm_mon = 2;
            sampleTime.tm_sec = 45;
            sampleTime.tm_wday = 1;
            sampleTime.tm_yday = 67;
            sampleTime.tm_year = 115;
           
            rawTime = mktime(&sampleTime);
            return rawTime;
        }

		TEST_METHOD(TestUpdateStorage) {  
            //Storage *storage = Storage::getInstance();
            //storage->setStorageLoc("apple");
            //Assert::AreEqual(std::string("a"), ttt);
            
            //Storage::resetInstance();
		}

	};
}