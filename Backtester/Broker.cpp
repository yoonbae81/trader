#include "pch.h"
#include "Broker.h"

shared_ptr<spdlog::logger> Broker::logger = spdlog::stdout_color_mt("broker");

Broker::Broker(Asset& asset, Ledger& ledger, ISource<shared_ptr<Msg>>& source)
	: asset_(asset), ledger_(ledger), source_(source) {
	logger->trace("Initializing");
}

Broker::~Broker() {
	logger->trace("Done");
}

void Broker::run() {
	logger->debug("Running");
	while (true) {
		auto m = receive(source_);
		if (*m == Msg::QUIT) break;
		logger->debug("Ordered {} x{}", m->symbol, m->analyzer_quantity);

		callback(*m);
	}

	done();
}


void Broker::callback(Msg& m) {
	m.broker_quantity = m.analyzer_quantity;
	ledger_.write(m);

	logger->info("Updated {} x{}", m.symbol, m.broker_quantity);
}

