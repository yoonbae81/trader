#include "pch.h"
#include "BacktestBroker.h"
#include "BacktestFetcher.h"
#include "BacktestCasher.h"
#include "../Common/Loop.h"
#include "../Analyzer/Dummy.h"

using namespace std;

int main()
{
	clog << "Backtester started" << endl;

	BacktestFetcher fetcher;
	BacktestCasher casher;
	BacktestBroker broker;
	Dummy analyzer;

	Loop::Run(fetcher, analyzer, casher, broker);
}

