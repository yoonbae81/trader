#include "pch.h"
#include "CppUnitTest.h"
#include "../Common/Stock.h"

using namespace std;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CommonTest
{
	TEST_CLASS(StockTest)
	{
	public:
		TEST_METHOD(Find) {
			std::unordered_map<std::string, Stock> stocks;
			auto& s = stocks["015760"];
			Assert::AreEqual(stocks.size(), (size_t) 1);
		}

		TEST_METHOD(AddTick) {
			auto msg = "015760 3000 10 1234512345";
			auto m = PriceMsg::Parse(msg);

			auto s = Stock();
			Assert::IsTrue(s.AddTick(m));
			Assert::AreEqual(s.prices().size(), (size_t) 1);
		}
	};
}