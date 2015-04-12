#include "stdafx.h"
#include "CppUnitTest.h"
#include "CommandType.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace MyCalTestSuite {
	TEST_CLASS(InterpreterAddNegativeTest) {
	public:
        TEST_METHOD(TestInvalidTime) {
            bool correctException = false;

            try {
                Interpreter::parseAddCmd("project meeting :at 1260pm");
                std::wstring msg( L"No exception has been thrown" );
                const wchar_t* failMsg = msg.c_str();
                Assert::Fail(failMsg);
            } 
            catch(InvalidInputException &e) {
                correctException = true;
            } 

            Assert::IsTrue(correctException);
        }

        TEST_METHOD(TestDayOutOfRange) {
            bool correctException = false;

            try {
                Interpreter::parseAddCmd("project meeting :on 32/01/2015");
                std::wstring msg( L"No exception has been thrown" );
                const wchar_t* failMsg = msg.c_str();
                Assert::Fail(failMsg);
            } 
            catch(InvalidInputException &e) {
                correctException = true;
            } 

            Assert::IsTrue(correctException);
        }

        TEST_METHOD(TestMonthOutOfRange) {
            bool correctException = false;

            try {
                Interpreter::parseAddCmd("project meeting :on 01/13/2015");
                std::wstring msg( L"No exception has been thrown" );
                const wchar_t* failMsg = msg.c_str();
                Assert::Fail(failMsg);
            } 
            catch(InvalidInputException &e) {
                correctException = true;
            } 

            Assert::IsTrue(correctException);
        }

        TEST_METHOD(TestYearUpperLimit) {
            bool correctException = false;

            try {
                Interpreter::parseAddCmd("project meeting :on 01/13/2201");
                std::wstring msg( L"No exception has been thrown" );
                const wchar_t* failMsg = msg.c_str();
                Assert::Fail(failMsg);
            } 
            catch(InvalidInputException &e) {
                correctException = true;
            } 

            Assert::IsTrue(correctException);
        }

        TEST_METHOD(TestYearLowerLimit) {
            bool correctException = false;

            try {
                Interpreter::parseAddCmd("project meeting :on 01/13/1970");
                std::wstring msg( L"No exception has been thrown" );
                const wchar_t* failMsg = msg.c_str();
                Assert::Fail(failMsg);
            } 
            catch(InvalidInputException &e) {
                correctException = true;
            } 

            Assert::IsTrue(correctException);
        }


		
	};
}