#include "pch.h"
#include "BacktestBroker.h"
#include "BacktestFetcher.h"
#include "BacktestCasher.h"
#include "../Analyzer/Parameter.h"
#include "../Analyzer/BasicAnalyzer.h"
#include "../Common/Loop.h"

using namespace std;

int main()
{
	clog << "Backtester started" << endl;

	string dataFile = "10lines.txt";
	BacktestFetcher fetcher(dataFile);

	BacktestCasher casher;

	BacktestBroker broker;

	string paramFile = "basicParam.txt";
	Parameter p = Parameter::Parse(paramFile);
	BasicAnalyzer analyzer(p);

	Loop::Run(fetcher, analyzer, casher, broker);
}

