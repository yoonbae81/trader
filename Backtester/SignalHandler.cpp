#include "pch.h"
#include "SignalHandler.h"

using namespace std;
using namespace concurrency;

SignalHandler::SignalHandler(const string& broker_endpoint)
	: signal_sock_(ctx_, zmq::socket_type::pull) {
	signal_sock_.bind(broker_endpoint);
}

void SignalHandler::run() {

	while (true) {
		zmq::message_t buffer;
		signal_sock_.recv(buffer);
		clog << "Received: " << buffer.data() << endl;
		// TODO Load all signal
		// TODO Calculate quantity to buy/sell
		// TODO Place an order
	}

	done();
}
