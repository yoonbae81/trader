#include "pch.h"
#include "BacktestBroker.h"
#include "BacktestFetcher.h"
#include "../Strategy/Parameter.h"
#include "../Strategy/BasicAnalyzer.h"
#include "../Library/Loop.h"

using namespace std;
using namespace concurrency;

int main()
{
	clog << "Backtest started" << endl;

	concurrent_vector<TickMsg> ticks;

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

