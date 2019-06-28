#include "pch.h"
#include "../Library/Asset.h"
#include "../Library/Exceptions.h"

using namespace std;
using namespace concurrency;

int main() {
	clog << "Starting Backtest..." << endl;

	int major, minor, patch = 0;
	zmq_version(&major, &minor, &patch);
	clog << "ZeroMQ version: " << major << '.' << minor << '.' << patch << '\n';

	concurrent_unordered_map<string, Holding> holdings;
	concurrent_unordered_map<string, double> stoploss;

	// init output socket for Fetcher
	// init input socket for 

	//string filename = "10lines.txt";
	//unique_ptr<istream> source = make_unique<ifstream>(filename);
	//if (!source.is_open()) {
	//	clog << "Couldn't open a file: " << filePath << endl;
	//	exit(1);
	//}
	//TickFetcherAgent tf(*source);



	clog << "Backtest finished" << endl;

	return EXIT_SUCCESS;
}

