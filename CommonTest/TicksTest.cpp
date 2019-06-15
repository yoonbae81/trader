#include "pch.h"
#include "CppUnitTest.h"
#include "../Common/Ticks.h"

using namespace std;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

TEST_CLASS(TicksTest)
{
public:
	TEST_METHOD(PutTest) {

		string line("AAAAAA 3000 10 1234512345");
		auto m = TickMsg::Parse(line);
	
		auto sut = Ticks();
		sut.AddTick(m);

		Assert::AreEqual(m.timestamp, sut.timestamp);
		Assert::AreEqual(m.price, sut.prices().front());
		Assert::AreEqual(m.price, sut.prices().data()[0]);
		Assert::AreEqual(m.volume, (size_t)sut.volumes().front());
		Assert::AreEqual(m.volume, (size_t)sut.volumes().data()[0]);

		// when timestamp is same, subsequent request should update price and add volume
		m.price *= 2;
		Assert::IsFalse(sut.AddTick(m));
		Assert::AreEqual(m.price, sut.prices().back());
		Assert::AreEqual(m.volume * 2, (size_t)sut.volumes().back());
	}

	TEST_METHOD(PutTest_Multiple) {
		auto count = 1000 * 1000;
		auto line = "AAAAAA 3000 10 1234512345";
		auto msg = TickMsg::Parse(line);
		auto sut = Ticks();

		for (auto i = 0; i < count; i++) {
			msg.timestamp += i;
			sut.AddTick(msg);
		}
		
		auto expected = count;
		auto actual = (int) sut.prices().size();
	
		Assert::AreEqual(expected, actual);
	}
};
