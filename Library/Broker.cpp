#include "pch.h"
#include "Broker.h"

shared_ptr<spdlog::logger> Broker::logger = spdlog::stdout_color_mt("broke");

Broker::Broker(Asset& asset, ISource<Msg>& source)
	: asset_(asset)
	, source_(source) {

	logger->debug("Initializing");
}

void Broker::run() {
	logger->info("Running");
	while (true) {
		auto msg = receive(source_);
		if (msg == Msg::QUIT) break;

		logger->trace("Ordered: {}", msg.analyzer_quantity);
		msg.broker_quantity = 2;
	}

	logger->debug("Done");
	done();
}

 