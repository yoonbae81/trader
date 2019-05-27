#include "pch.h"
#include "CppUnitTest.h"
#include "../Common/Stock.h"

using namespace std;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

TEST_CLASS(StockTest)
{
private:
	const string line_ = "AAAAAA 3000 10 1234512345";
	const string symbol_ = "AAAAAA";

public:
	TEST_METHOD(Update) {
		auto s = Stock(symbol_);
		auto m = PriceMsg::Parse(line_);

		Assert::IsTrue(s.Update(m));
		Assert::AreEqual(m.symbol, s.symbol());
		Assert::AreEqual(m.timestamp, s.timestamp);
		Assert::AreEqual(m.price, s.prices().back());
		Assert::AreEqual(m.volume, (size_t)s.volumes().back());

		// when timestamp is same, subsequent request updates price and adds volume
		m.price += 10;
		Assert::IsFalse(s.Update(m));
		Assert::AreEqual(m.price, s.prices().back());
		Assert::AreEqual(m.volume * 2, (size_t)s.volumes().back());
	}

	TEST_METHOD(UpdateMultiple) {
		auto s = Stock(symbol_);
		auto m = PriceMsg::Parse(line_);

		auto count = 1000*1000;
		for (auto i = 0; i < count; i++) {
			m.timestamp += i;
			s.Update(m);
		}
		Assert::AreEqual(m.volume, (size_t)s.volumes().back());
	}
};
