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
	m.broker_price = slippage.simulate_market_price(SlippageGenerator::Market::KOSPI, m.fetcher_price);
	m.broker_cost = calc_transaction_cost(m.broker_quantity, m.broker_price);
	ledger_.write(m);

	logger->info("Order Filled {} x{}", m.symbol, m.broker_quantity);
}


double Broker::calc_transaction_cost(double filled_quantity, double filled_price) {
	double total = abs(filled_quantity) * filled_price;
	double commission = total * kCommissionRate;
	double tax = 0;

	if (filled_quantity < 0)	// only when sell
		tax = total * kTaxRate;
	
	return commission + tax;
}

