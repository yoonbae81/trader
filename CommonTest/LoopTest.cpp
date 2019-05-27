#include "pch.h"
#include "CppUnitTest.h"

#include "../Common/Loop.h"

using namespace std;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

struct DummyFetcher {
	int count{ 1 };
	PriceMsg GetMessage() {
		if (count--) {
			return PriceMsg::Parse("015760 1243 10 112300202");
		}
		return PriceMsg::Parse("QUIT");
	}
};

struct DummyAnalyzer {
	int CalcStrength(Stock stock) { return 10; }
	void UpdateStoploss(Stock stock) {}
};

struct DummyBroker {
	void Order(string& symbol, int quantity) { }
};

TEST_CLASS(LoopTest)
{
public:
	TEST_METHOD(Method1)
	{
		auto loop = Loop<DummyFetcher, DummyAnalyzer, DummyBroker>();
		loop.fetcher = &DummyFetcher();
		loop.analyzer = &DummyAnalyzer();
		loop.broker = &DummyBroker();
		loop.Run();
	}
};
