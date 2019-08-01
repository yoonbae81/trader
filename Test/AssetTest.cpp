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
		auto symbol = "AAAAAA";
		Asset sut(cash);

		auto quantity = 2.0;
		auto bought_price = 100.0;
		auto expected = cash;

		parallel_invoke(
			[&] { sut.bought(symbol, quantity, bought_price); },
			[&] { sut.sold(symbol, quantity, bought_price); },
			[&] { sut.bought(symbol, quantity, bought_price); },
			[&] { sut.sold(symbol, quantity, bought_price); },
			[&] { sut.bought(symbol, quantity, bought_price); },
			[&] { sut.sold(symbol, quantity, bought_price); },
			[&] { sut.bought(symbol, quantity, bought_price); },
			[&] { sut.sold(symbol, quantity, bought_price); });
		auto actual = sut.cash();

		Assert::AreEqual(expected, actual);
	}

	TEST_METHOD(QuantityTest) {
		auto cash = 1000.0;
		auto symbol = "AAAAAA";
		Asset sut(cash);

		auto quantity = 2.0;
		auto bought_price = 100.0;
		auto expected = quantity;

		parallel_invoke(
			[&] { sut.bought(symbol, quantity, bought_price); },
			[&] { sut.bought(symbol, quantity, bought_price); },
			[&] { sut.sold(symbol, quantity, bought_price); },
			[&] { sut.bought(symbol, quantity, bought_price); },
			[&] { sut.sold(symbol, quantity, bought_price); },
			[&] { sut.bought(symbol, quantity, bought_price); },
			[&] { sut.sold(symbol, quantity, bought_price); },
			[&] { sut.bought(symbol, quantity, bought_price); },
			[&] { sut.sold(symbol, quantity, bought_price); });
		auto actual = sut[symbol].quantity;

		Assert::AreEqual(expected, actual);
	}

	TEST_METHOD(PriceTest) {
		auto cash = 1000.0;
		auto symbol = "AAAAAA";
		Asset sut(cash);

		auto quantity = 2.0;
		auto bought_price = 100.0;
		auto expected = bought_price;

		sut.bought(symbol, quantity, bought_price);
		auto actual = sut[symbol].bought_price;

		Assert::AreEqual(expected, actual);
	}

	TEST_METHOD(PriceAverageTest) {
		auto cash = 1000.0;
		auto symbol = "AAAAAA";
		auto quantity1 = 1.0;
		auto price1 = 100.0;
		auto quantity2 = 1.0;
		auto price2 = 200.0;

		Asset sut(cash);
		parallel_invoke(
			[&] { sut.bought(symbol, quantity1, price1); },
			[&] { sut.bought(symbol, quantity2, price2); });

		auto expected = (price1 * quantity1 + price2 * quantity2) / (quantity1 + quantity2);
		auto actual = sut[symbol].bought_price;

		Assert::AreEqual(expected, actual);
	}


	TEST_METHOD(TotalRiskTest) {
		auto cash = 1000.0;

		auto symbol1 = "AAAAAA";
		auto quantity1 = 1.0;
		auto price1 = 100.0;

		auto symbol2 = "BBBBBBB";
		auto quantity2 = 2.0;
		auto price2 = 100.0;

		auto symbol3 = "CCCCCC";
		auto quantity3 = 3.0;
		auto price3 = 100.0;

		Asset sut(cash);
		sut.bought(symbol1, quantity1, price1);
		sut.bought(symbol2, quantity2, price2);
		sut.bought(symbol3, quantity3, price3);

		auto expected = quantity1 * price1 + quantity2 * price2 + quantity3 * price3;
		auto actual = sut.total_risk();

		Assert::AreEqual(expected, actual);
	}
};
