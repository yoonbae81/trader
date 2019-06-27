#include "pch.h"
#include "../Library/Asset.h"
#include "../Library/Exceptions.h"
#include "../Library/FetcherAgent.h"
#include "../Library/AnalyzerAgent.h"
#include "../Library/BrokerAgent.h"
#include "../Library/Parameter.h"
#include "../Library/Strategy.h"

using namespace std;
using namespace concurrency;

int main() {
	clog << "Backtest started" << endl;

	double cash = 10000;
	Asset asset(cash);
	// TODO Load asset from a file or somewhere persistent
	
	string paramFile = "basicParam.txt";
	Parameter p = Parameter::Parse(paramFile);
	Strategy strategy(p);

	//string filename = "10lines.txt";
	//unique_ptr<istream> source = make_unique<ifstream>(filename);
	//if (!source.is_open()) {
	//	clog << "Couldn't open a file: " << filePath << endl;
	//	exit(1);
	//}
	//TickFetcherAgent tf(*source);

	unbounded_buffer<string> tick_buffer, signal_buffer, stoploss_buffer;
	FetcherAgent fetcher(stoploss_buffer, tick_buffer, signal_buffer);
	AnalyzerAgent analyzer(tick_buffer, signal_buffer);
	BrokerAgent broker(signal_buffer, stoploss_buffer, asset);

	fetcher.start();
	analyzer.start();
	broker.start();

	agent::wait(&fetcher);
	agent::wait(&analyzer);
	agent::wait(&broker);

	clog << "Backtest finished" << endl;
	
	return EXIT_SUCCESS;
}

