#include "pch.h"
#include "CppUnitTest.h"
#include "../Library/Asset.h"

using namespace std;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

TEST_CLASS(AssetTest) {
public:

	TEST_METHOD(CtorTest) {
		auto cash = 1000.0;
		auto expected = cash;

		Asset sut(cash);
		auto actual = sut.cash();

		Assert::AreEqual(expected, actual);
	}

	TEST_METHOD(CashTest) {
		auto cash = 1000.0;
		Asset sut(cash);

		Msg m("AAAAAA");
		m.broker_quantity = 2.0;
		m.broker_price = 100.0;

		auto expected = cash;

		parallel_invoke(
			[&] { sut.bought(m); },
			[&] { sut.sold(m); },
			[&] { sut.bought(m); },
			[&] { sut.sold(m); },
			[&] { sut.bought(m); },
			[&] { sut.sold(m); },
			[&] { sut.bought(m); },
			[&] { sut.sold(m); });
		auto actual = sut.cash();

		Assert::AreEqual(expected, actual);
	}

	TEST_METHOD(QuantityTest) {
		auto cash = 1000.0;
		auto symbol = "AAAAAA";
		Asset sut(cash);

		Msg m(symbol);
		m.broker_price = 100.0;
		m.broker_quantity = 2.0;

		auto expected = m.broker_quantity;

		parallel_invoke(
			[&] { sut.bought(m); },
			[&] { sut.bought(m); },
			[&] { sut.sold(m); },
			[&] { sut.bought(m); },
			[&] { sut.sold(m); },
			[&] { sut.bought(m); },
			[&] { sut.sold(m); },
			[&] { sut.bought(m); },
			[&] { sut.sold(m); });
		auto actual = sut[symbol].quantity;

		Assert::AreEqual(expected, actual);
	}

	TEST_METHOD(PriceTest) {
		auto symbol = "AAAAAA";
		auto cash = 1000.0;
		Asset sut(cash);

		Msg m(symbol);
		m.broker_price = 100.0;
		m.broker_quantity = 2.0;

		auto expected = m.broker_price;

		sut.bought(m);
		auto actual = sut[symbol].bought_price;

		Assert::AreEqual(expected, actual);
	}

	TEST_METHOD(PriceAverageTest) {
		auto cash = 1000.0;
		auto symbol = "AAAAAA";

		Msg m1(symbol);
		m1.broker_price = 100.0;
		m1.broker_quantity = 1.0;

		Msg m2(symbol);
		m2.broker_price = 200.0;
		m2.broker_quantity = 1.0;

		Asset sut(cash);
		parallel_invoke(
			[&] { sut.bought(m1); },
			[&] { sut.bought(m2); });

		auto expected = (m1.broker_price * m1.broker_quantity + m2.broker_price * m2.broker_quantity) 
			/ (m1.broker_quantity + m2.broker_quantity);
		auto actual = sut[symbol].bought_price;

		Assert::AreEqual(expected, actual);
	}


	TEST_METHOD(TotalRiskTest) {
		auto cash = 1000.0;

		Msg m1("AAAAAA");
		m1.broker_price = 100.0;
		m1.broker_quantity = 1.0;

		Msg m2("BBBBBB");
		m2.broker_price = 100.0;
		m2.broker_quantity = 2.0;

		Msg m3("CCCCCC");
		m3.broker_price = 100.0;
		m3.broker_quantity = 3.0;

		Asset sut(cash);
		sut.bought(m1);
		sut.bought(m2);
		sut.bought(m3);

		auto expected = m1.broker_price * m1.broker_quantity
			+ m2.broker_price * m2.broker_quantity
			+ m3.broker_price * m3.broker_quantity;
		auto actual = sut.total_risk();

		Assert::AreEqual(expected, actual);
	}
};
