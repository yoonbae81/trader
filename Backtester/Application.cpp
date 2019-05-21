#include "pch.h"
#include "BacktestBroker.h"
#include "BacktestFetcher.h"
#include "BacktestCasher.h"
#include "../Common/Loop.h"
#include "../Analyzer/Parameter.h"
#include "../Analyzer/Basic.h"


using namespace std;

int main()
{
	clog << "Backtester started" << endl;

	BacktestFetcher fetcher("10lines.txt");
	BacktestCasher casher;
	BacktestBroker broker;

	string parameterFile = "fake.txt";
	Parameter p = Parameter::Parse(parameterFile);
	Basic analyzer(p);

	Loop::Run(fetcher, analyzer, casher, broker);
}

