#include "pch.h" 
#include "Ledger.h"

shared_ptr<spdlog::logger> Ledger::logger = spdlog::stdout_color_mt("ledger");
const string Ledger::FORMAT_MSG = "{{\"timestamp\": {}, \"symbol\": \"{}\", \"price\": {}, \"quantity\": {}, \"cost\": {}, \"slippage\": {:.2}}}";

Ledger::Ledger(double initial_cash, ostream& out)
	: out_(out)
	, mutex_(make_unique<critical_section>()) {

	logger->trace("Initializing");
	logger->debug("Cash {:.0f}", initial_cash);

	out_ << fmt::format("{{\"initial_cash\": {:.0f}}}"
						, initial_cash) << endl;
}

Ledger::~Ledger() {}

void Ledger::write(const Msg& msg) {
	logger->trace("Wrote {} x{}", msg.symbol, msg.broker_quantity);

	critical_section::scoped_lock(*mutex_);
	out_ << fmt::format(FORMAT_MSG
						, msg.fetcher_timestamp
						, msg.symbol
						, msg.broker_price
						, msg.broker_quantity
						, msg.broker_cost
						, msg.broker_price - msg.fetcher_price
	) << endl;
}
