#include "pch.h"
#include "../Library/Holding.h"

using namespace std;
using namespace concurrency;

int main() {
	clog << "Starting Broker..." << endl;

	concurrent_unordered_map<string, Holding> holdings;

	int major, minor, patch = 0;
	zmq_version(&major, &minor, &patch);
	clog << "ZeroMQ version: " << major << '.' << minor << '.' << patch << '\n';

	zmq::context_t ctx;
	
	zmq::socket_t sock_signal(ctx, zmq::socket_type::sub);
	sock_signal.bind("tcp://127.0.0.1:9999");

	zmq::socket_t sock_stoploss(ctx, zmq::socket_type::pub);
	sock_stoploss.bind("tcp://127.0.0.1:5555");

	return EXIT_SUCCESS;
}

