#include "pch.h"
#include "CppUnitTest.h"

#include "../Common/Loop.h"

using namespace std;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

struct FetcherStub {
	int count{ 1 };
	TickMsg GetMessage() {
		if (count--) {
			return TickMsg::Parse("015760 1243 10 112300202");
		}
		return TickMsg::Parse("QUIT");
	}
};

struct AnalyzerStub {
	int CalcStrength(Ticks ticks) { return 10; }
	void UpdateStoploss(Ticks ticks) {}
};

struct BrokerStub {
	void Order(string& symbol, int quantity) { }
};

TEST_CLASS(LoopTest)
{
public:
	TEST_METHOD(Method1)
	{
		//auto loop = Loop<FetcherStub, AnalyzerStub, BrokerStub>();
		//loop.fetcher = &FetcherStub();
		//loop.analyzer = &AnalyzerStub();
		//loop.broker = &BrokerStub();
		//loop.Run();
	}
};
