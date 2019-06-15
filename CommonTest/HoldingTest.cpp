#include "pch.h"
#include "CppUnitTest.h"
#include "../Common/Holding.h"

using namespace std;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

TEST_CLASS(HoldingTest)
{
public:
	TEST_METHOD(Bought)
	{
		Holding h;

		h.Bought(2, 1000);
		Assert::AreEqual(size_t(2), h.quantity());
		Assert::AreEqual(1000.0, h.average_price());

		h.Bought(2, 2000);
		Assert::AreEqual(size_t(4), h.quantity());
		Assert::AreEqual(1500.0, h.average_price());
	}

	TEST_METHOD(Sold)
	{
		Holding h;

		h.Bought(2, 1000);
		h.Sold(1, 1000);
		Assert::AreEqual(size_t(1), h.quantity());
		Assert::AreEqual(1000.0, h.average_price());
	}
};

