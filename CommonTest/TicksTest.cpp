#include "pch.h"
#include "CppUnitTest.h"
#include "../Common/Ticks.h"

using namespace std;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

TEST_CLASS(TicksTest)
{
public:
	TEST_METHOD(PutTest) {
		string line = "AAAAAA 3000 10 1234512345";

		auto s = Ticks();
		auto m = PriceMsg::Parse(line);
	
		Assert::IsTrue(s.Put(m));

		Assert::AreEqual(m.timestamp, s.timestamp);
		Assert::AreEqual(m.price, s.prices().front());
		Assert::AreEqual(m.price, s.prices().data()[0]);
		Assert::AreEqual(m.volume, (size_t)s.volumes().front());
		Assert::AreEqual(m.volume, (size_t)s.volumes().data()[0]);

		// when timestamp is same, subsequent request updates price and adds volume
		m.price += 10;
		Assert::IsFalse(s.Put(m));
		Assert::AreEqual(m.price, s.prices().back());
		Assert::AreEqual(m.volume * 2, (size_t)s.volumes().back());
	}

	TEST_METHOD(PutTest_Multiple) {
		auto line = "AAAAAA 3000 10 1234512345";

		auto s = Ticks();
		auto m = PriceMsg::Parse(line);

		auto count = 1000 * 1000;
		for (auto i = 0; i < count; i++) {
			m.timestamp += i;
			s.Put(m);
		}
	
		Assert::AreEqual(m.volume, (size_t)s.volumes().back());
	}
};
