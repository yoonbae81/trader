#include "pch.h"
#include "CppUnitTest.h"
#include "../Common/Ticks.h"

using namespace std;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

TEST_CLASS(TicksTest)
{
public:
	TEST_METHOD(Contains) {
		Ticks::Clear();
		Assert::IsFalse(Ticks::Contains("Nothing"));
	}

	TEST_METHOD(Get) {
		string symbol = "AAAAAA";

		Ticks::Clear();
		Ticks& s = Ticks::Get(symbol);
		Assert::IsTrue(Ticks::Contains(symbol));
		Assert::AreEqual(symbol, s.symbol());
	}

	TEST_METHOD(Clear) {
		string symbol = "AAAAAA";

		Ticks& s = Ticks::Get(symbol);
		Assert::IsTrue(Ticks::Contains(symbol));
		Ticks::Clear();
		Assert::IsFalse(Ticks::Contains(symbol));
	}

	TEST_METHOD(Update) {
		string symbol = "AAAAAA";
		string line = "AAAAAA 3000 10 1234512345";

		auto s = Ticks(symbol);
		auto m = PriceMsg::Parse(line);

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
		auto symbol = "AAAAAA";
		auto line = "AAAAAA 3000 10 1234512345";

		auto s = Ticks(symbol);
		auto m = PriceMsg::Parse(line);

		auto count = 1000 * 1000;
		for (auto i = 0; i < count; i++) {
			m.timestamp += i;
			s.Update(m);
		}
		Assert::AreEqual(m.volume, (size_t)s.volumes().back());
	}
};
