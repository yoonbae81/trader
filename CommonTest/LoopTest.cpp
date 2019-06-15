#include "pch.h"
#include "CppUnitTest.h"

#include "../Common/Loop.h"

using namespace std;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

struct FetcherStub {
	int count{ 1 };
	TickMsg GetMessage() {
		if (count--) {
			return TickMsg::Parse("AAAAAA 10000 2 1234512345");
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
