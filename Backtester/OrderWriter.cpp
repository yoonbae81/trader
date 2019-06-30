#include "pch.h"
#include "OrderWriter.h"

using namespace std;
using namespace concurrency;

OrderWriter::OrderWriter(ISource<OrderMsg>& order_channel,
						 const string& filepath) :
	order_channel_(order_channel), filepath_(filepath) {

	double cash = 10000;
	Asset asset(cash);

	// TODO Load asset from a file or somewhere persistent
	// connect sockets signals and 
	// publish stoploss 

}

void OrderWriter::run() {

	// TODO implement followings
	// 1. Load all signal
	// 2. Calculate quantity to buy/sell
	// 3. Place an order
	// 4. Send stoploss
	while (true) {
		OrderMsg msg = receive(order_channel_);
		clog << "Received OrderMsg: " << msg.ToString() << endl;
	}

	done();
}
