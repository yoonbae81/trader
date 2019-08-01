#include "pch.h"
#include "Broker.h"

shared_ptr<spdlog::logger> Broker::logger = spdlog::stdout_color_mt("broke");

Broker::Broker(Asset& asset, ISource<Msg>& source, ITarget<Msg>& target)
	: asset_(asset)
	, source_(source)
	, target_(target) {

	logger->debug("Initializing");

}

Broker::~Broker() {}

void Broker::run() {
	logger->info("Running");
	while (true) {
		auto msg = receive(source_);
		if (msg == Msg::QUIT) break;

		logger->trace("Ordered: {}", msg.analyzer_quantity);
		msg.broker_quantity = 2;

		// TODO on callback 
		asend(target_, msg);
	}

	asend(target_, Msg::QUIT);
	logger->debug("Done");
	done();
}

