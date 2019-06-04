#include "pch.h"
#include "CppUnitTest.h"
#include "../Common/StockMap.h"
#include "../Common/Stock.h"

using namespace std;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

TEST_CLASS(StockMapTest)
{
private:
	const string symbol = "AAA";

public:
	TEST_METHOD(Contains) {
		StockMap map{};
		Assert::IsFalse(map.Contains(symbol));
	}

	TEST_METHOD(Get) {
		StockMap map{};
		Ticks& s = map.Get(symbol);
		Assert::IsTrue(map.Contains(symbol));
		Assert::AreEqual(symbol, s.symbol());
	}

	TEST_METHOD(Reset) {
		StockMap map{};
		Ticks& s = map.Get(symbol);
		map.Reset();
		Assert::IsFalse(map.Contains(symbol));
	}
};
