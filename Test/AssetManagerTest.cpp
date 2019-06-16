#include "pch.h"
#include "CppUnitTest.h"
#include "../Library/AssetManager.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

TEST_CLASS(AssetManagerTest)
{
public:

	TEST_METHOD(CtorTest)
	{
		auto cash = 1000.0;
		auto expected = cash;

		AssetManager sut(cash);
		auto actual = sut.cash();

		Assert::AreEqual(expected, actual);
	}

	TEST_METHOD(CashTest)
	{
		auto cash = 1000.0;
		auto symbol = "AAAAAA";
		AssetManager sut(cash);

		auto quantity = 2.0;
		auto price = 100.0;
		auto expected = cash;

		parallel_invoke(
			[&] { sut.Bought(symbol, quantity, price); },
			[&] { sut.Sold(symbol, quantity, price); },
			[&] { sut.Bought(symbol, quantity, price); },
			[&] { sut.Sold(symbol, quantity, price); },
			[&] { sut.Bought(symbol, quantity, price); },
			[&] { sut.Sold(symbol, quantity, price); },
			[&] { sut.Bought(symbol, quantity, price); },
			[&] { sut.Sold(symbol, quantity, price); });
		auto actual = sut.cash();

		Assert::AreEqual(expected, actual);
	}

	TEST_METHOD(QuantityTest)
	{
		auto cash = 1000.0;
		auto symbol = "AAAAAA";
		AssetManager sut(cash);

		auto quantity = 2.0;
		auto price = 100.0;
		auto expected = quantity;

		parallel_invoke(
			[&] { sut.Bought(symbol, quantity, price); },
			[&] { sut.Bought(symbol, quantity, price); },
			[&] { sut.Sold(symbol, quantity, price); },
			[&] { sut.Bought(symbol, quantity, price); },
			[&] { sut.Sold(symbol, quantity, price); },
			[&] { sut.Bought(symbol, quantity, price); },
			[&] { sut.Sold(symbol, quantity, price); },
			[&] { sut.Bought(symbol, quantity, price); },
			[&] { sut.Sold(symbol, quantity, price); });
		auto actual = sut.quantity(symbol);

		Assert::AreEqual(expected, actual);
	}

	TEST_METHOD(PriceTest)
	{
		auto cash = 1000.0;
		auto symbol = "AAAAAA";
		AssetManager sut(cash);

		auto quantity = 2.0;
		auto price = 100.0;
		auto expected = price;

		sut.Bought(symbol, quantity, price);
		auto actual = sut.price(symbol);

		Assert::AreEqual(expected, actual);
	}

	TEST_METHOD(PriceAverageTest)
	{
		auto cash = 1000.0;
		auto symbol = "AAAAAA";
		auto quantity1 = 1.0;
		auto price1 = 100.0;
		auto quantity2 = 1.0;
		auto price2 = 200.0;

		AssetManager sut(cash);
		parallel_invoke(
			[&] { sut.Bought(symbol, quantity1, price1); },
			[&] { sut.Bought(symbol, quantity2, price2); });

		auto expected = (price1 * quantity1 + price2 * quantity2) / (quantity1 + quantity2);
		auto actual = sut.price(symbol);

		Assert::AreEqual(expected, actual);
	}
};
