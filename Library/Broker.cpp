#include "pch.h"
#include "Broker.h"

Broker::Broker(ISource<Msg>& source, Holdings& holdings)
	: source_(source), holdings_(holdings) {

	clog << "Initializing Broker..." << endl;

}

void Broker::run() {
	clog << "Broker run" << endl;

	while (true) {
		auto msg = receive(source_);

		clog << "Ordered: " << msg.order_quantity << endl;
		msg.filled_quantity = 2;
	}


	done();
}



