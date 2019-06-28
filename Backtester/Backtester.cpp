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

	zmq::context_t ctx;

	zmq::socket_t sock_tick(ctx, zmq::socket_type::pub);
	sock_tick.connect("tcp://127.0.0.1:3001");

	zmq::socket_t sock_signal(ctx, zmq::socket_type::sub);
	sock_signal.bind("tcp://127.0.0.1:9999");
	
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

