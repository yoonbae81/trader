#include "pch.h"
#include "CppUnitTest.h"
#include "../Strategy/Strategy.h"

using namespace std;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

TEST_CLASS(StrategyTest) {
public:
	TEST_METHOD(DummyTest) {
		Parameter p = Parameter::Parse("NoFile");
		Strategy sut(p);

		auto expected = 3;
		auto actual = p.threshold;
		Assert::AreEqual(expected, actual);
	}
};
