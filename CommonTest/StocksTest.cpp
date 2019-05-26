#include "pch.h"
#include "CppUnitTest.h"
#include "../Common/Stocks.h"
#include "../Common/Stock.h"

using namespace std;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CommonTest
{
	TEST_CLASS(StocksTest)
	{
	private:
		string symbol = "AAA";

	public:
		TEST_METHOD(Contains) {
			Stocks stocks{};
			Assert::IsFalse(stocks.Contains(symbol));
		}

		TEST_METHOD(Get) {
			Stocks stocks{};
			Stock& s = stocks.Get(symbol);
			Assert::AreEqual(symbol, s.symbol());
		}

		TEST_METHOD(Reset) {
			Stocks stocks{};
			Stock& s = stocks.Get(symbol);
			stocks.Reset();
			Assert::IsFalse(stocks.Contains(symbol));

		}
	};
}