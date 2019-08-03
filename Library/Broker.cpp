#include "pch.h"
#include "Broker.h"

shared_ptr<spdlog::logger> Broker::logger = spdlog::stdout_color_mt("broke");

Broker::Broker(Asset& asset, Ledger& ledger, ISource<Msg>& source)
	: asset_(asset)
	, ledger_(ledger)
	, source_(source) {

	logger->debug("Initializing");

}

Broker::~Broker() {}

void Broker::run() {
	logger->info("Running");
	while (true) {
		auto m = receive(source_);
		if (m == Msg::QUIT) break;
		
		callback(m);
	}

	logger->debug("Done");
	done();
}


void Broker::callback(Msg& m) {
	m.broker_quantity = 2;
	ledger_.write(m);
	logger->trace("Ordered: {}", m.analyzer_quantity);
}

