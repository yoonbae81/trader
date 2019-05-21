#include "pch.h"
#include "CppUnitTest.h"

#include "../Backtester/BacktestFetcher.h"

using namespace std;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace BacktesterTest
{
	TEST_CLASS(BacktestFetcherTest)
	{
	public:
		TEST_METHOD(GettingMessagesAnyHow)
		{
			size_t lines = 10;
			string filePath = "10lines.txt";
			BacktestFetcher fetcher(filePath);

			for (int i = 0; i < lines; i++) {
				PriceMsg msg = fetcher.GetMessage();
				Assert::AreEqual(string("015760"), msg.symbol);
			}
		}
	};
}
