#include "pch.h"
#include "QuantityCalculator.h"


using namespace std;
using namespace concurrency;

QuantityCalculator::QuantityCalculator(const string& broker_endpoint,
									   ITarget<OrderMsg>& order_channel) :
	signal_sock_(ctx_, zmq::socket_type::pull),
	order_channel_(order_channel) {

	signal_sock_.bind(broker_endpoint);
}

void QuantityCalculator::run() {

	while (true) {
		zmq::message_t buffer;
		signal_sock_.recv(buffer);
		clog << "Received SignalMsg: " << buffer.data() << endl;
		clog << "Calculating quantity..." << endl;
		// TODO Load all signal
		// TODO Calculate quantity to buy/sell
		// TODO Place an order
		OrderMsg msg("AAAAAA", rand() % 100);

		send(order_channel_, msg);


	}

	done();
}
