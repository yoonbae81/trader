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

		TEST_METHOD(Ctor) {
			string symbol = "AAAAAA";
			Stock s(symbol);
			Assert::AreEqual(symbol, s.symbol());
		}
		TEST_METHOD(NotFound) {
			std::unordered_map<std::string, Stock> map;
			Assert::IsTrue(map.end() == map.find("AAAAAA"));
		}
		TEST_METHOD(AddTick) {
			auto msg = "015760 3000 10 1234512345";
			auto m = PriceMsg::Parse(msg);

			string symbol = "AAAAAA";
			auto s = Stock(symbol);
			Assert::IsTrue(s.AddTick(m));
			Assert::AreEqual(s.prices().size(), (size_t) 1);
		}
	};
}