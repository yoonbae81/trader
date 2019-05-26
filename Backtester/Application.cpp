#include "pch.h"
#include "BacktestBroker.h"
#include "BacktestFetcher.h"
#include "../Analyzer/Parameter.h"
#include "../Analyzer/BasicAnalyzer.h"
#include "../Common/Loop.h"

using namespace std;

int main()
{
	clog << "Backtest started" << endl;

	string dataFile = "10lines.txt";
	BacktestFetcher fetcher(dataFile);

	BacktestBroker broker;

	string paramFile = "basicParam.txt";
	Parameter p = Parameter::Parse(paramFile);
	BasicAnalyzer analyzer(p);

	auto loop = Loop<BacktestFetcher, BasicAnalyzer, BacktestBroker>();
	loop.fetcher = &fetcher;
	loop.analyzer = &analyzer;
	loop.broker = &broker;
	loop.Run();

	clog << "Backtest finished" << endl;
}

