#include "pch.h"
#include "CppUnitTest.h"
#include "../Library/Parameter.h"
#include "../Library/Strategy.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

TEST_CLASS(StrategyTest) {
public:
	TEST_METHOD(CtorTest) {
		Parameter p = Parameter::Parse("NoFile");
		Strategy sut(p);

		//Assert::AreEqual(expected, actual);
	}
};
