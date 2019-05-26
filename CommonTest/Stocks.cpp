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
	public:
		TEST_METHOD(Contains) {
			Stocks stocks{};

			string symbol = "AAA";
			Assert::IsFalse(stocks.Contains(symbol));
		}
		
		TEST_METHOD(Get) {
			Stocks stocks{};

			string symbol = "AAA";
			Stock s = stocks.Get(symbol);
			Assert::AreEqual(symbol, s.symbol());
		}

		TEST_METHOD(Reset) {
			
		}
	};
}