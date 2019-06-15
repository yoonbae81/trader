#include "pch.h"
#include "CppUnitTest.h"
#include "../AssetManager/AssetManager.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

TEST_CLASS(AssetManagerTest)
{
public:

	TEST_METHOD(TestCtor)
	{
		auto cash = 1000.0;
		AssetManager sut(cash);

		auto expected = cash;
		auto actual = sut.cash();

		Assert::AreEqual(expected, actual);
	}

	TEST_METHOD(TestHoldings)
	{

	}
};
