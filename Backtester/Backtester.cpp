#include "pch.h"
#include "../Library/Asset.h"
#include "../Library/Exceptions.h"
#include "../Library/Parameter.h"
#include "../Library/Strategy.h"

using namespace std;
using namespace concurrency;

int main() {
	clog << "Starting Backtest..." << endl;

	concurrent_unordered_map<string, Holding> holdings;
	concurrent_unordered_map<string, double> stoploss;

	int major = 0;
	int minor = 0;
	int patch = 0;
	zmq_version(&major, &minor, &patch);
	clog << "ZeroMQ version: " << major << '.' << minor << '.' << patch << '\n';


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


	clog << "Backtest finished" << endl;

	return EXIT_SUCCESS;
}

