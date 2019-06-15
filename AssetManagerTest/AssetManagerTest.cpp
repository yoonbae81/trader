#include "pch.h"
#include "CppUnitTest.h"
#include "../AssetManager/AssetManager.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

TEST_CLASS(AssetManagerTest)
{
public:

	TEST_METHOD(TestCtor)
	{
		auto cash = 1000.0;
		auto expected = cash;

		AssetManager sut(cash);
		auto actual = sut.cash();

		Assert::AreEqual(expected, actual);
	}

	TEST_METHOD(TestCash)
	{
		auto cash = 1000.0;
		auto symbol = "AAAAAA";
		AssetManager sut(cash);

		auto quantity = 2.0;
		auto price = 100.0;
		auto expected = cash - (quantity * price);

		sut.Bought(symbol, quantity, price);
		auto actual = sut.cash();

		Assert::AreEqual(expected, actual);
	}

	TEST_METHOD(TestQuantity)
	{
		auto cash = 1000.0;
		auto symbol = "AAAAAA";
		AssetManager sut(cash);

		auto quantity = 2.0;
		auto price = 100.0;

		sut.Bought(symbol, quantity, price);
		sut.Bought(symbol, quantity, price);

		auto expected = quantity * 2;
		auto actual = sut.quantity(symbol);

		Assert::AreEqual(expected, actual);
	}

	TEST_METHOD(TestPrice)
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

	TEST_METHOD(TestPriceAverage)
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

	//TEST_METHOD(TestSold)
	//{
	//	auto cash = 1000.0;
	//	auto symbol = "AAAAAA";
	//	AssetManager sut(cash);

	//	auto quantity = 2.0;
	//	auto price = 100.0;
	//	auto expected = cash - (quantity * price);
	//
	//	sut.Bought(symbol, quantity, price);
	//	auto actual = sut.cash();

	//	Assert::AreEqual(expected, actual);

	//	h.Bought(2, 1000);
	//	h.Sold(1, 1000);
	//	Assert::AreEqual(size_t(1), h.quantity());
	//	Assert::AreEqual(1000.0, h.average_price());
	//}

};
