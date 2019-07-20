#include "pch.h"
#include "Broker.h"

Broker::Broker(ISource<Msg>& source, Holdings& holdings)
	: source(source)
	, holdings(holdings) 
	, logger(spdlog::stdout_color_mt("broker")) {

	logger->debug("Initializing");
	logger->debug("Initialized");
}

void Broker::run() {
	while (true) {
		auto msg = receive(source);

		logger->trace("Ordered: {}", msg.order_quantity);
		msg.filled_quantity = 2;
	}


	done();
}

 