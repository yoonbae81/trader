#include "pch.h"
#include "CppUnitTest.h"
#include "../Backtester/Broker.h"

using namespace std;
using namespace concurrency;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

using fn_unit_price = double(*)(double);

TEST_CLASS(SlippageTest) {
public:

	TEST_METHOD_INITIALIZE(TestInitialize) {}

	TEST_METHOD(UnitPrice) {
		fn_unit_price sut;

		sut = Broker::get_unit_price_kospi;
		Assert::AreEqual(1.0, sut(500));
		Assert::AreEqual(5.0, sut(1'000));
		Assert::AreEqual(10.0, sut(5'000));
		Assert::AreEqual(50.0, sut(10'000));
		Assert::AreEqual(100.0, sut(50'000));
		Assert::AreEqual(500.0, sut(100'000));
		Assert::AreEqual(1'000.0, sut(500'000));

		sut = Broker::get_unit_price_kosdaq;
		Assert::AreEqual(1.0, sut(500.0));
		Assert::AreEqual(5.0, sut(1'000.0));
		Assert::AreEqual(10.0, sut(5'000.0));
		Assert::AreEqual(50.0, sut(10'000.0));
		Assert::AreEqual(100.0, sut(50'000.0));
		Assert::AreEqual(100.0, sut(100'000.0));
		Assert::AreEqual(100.0, sut(500'000.0));
	}

	TEST_METHOD_CLEANUP(TestCleanUp) {}
};