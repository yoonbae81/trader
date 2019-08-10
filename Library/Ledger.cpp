#include "pch.h" 
#include "Ledger.h"

shared_ptr<spdlog::logger> Ledger::logger = spdlog::stdout_color_mt("ledger");
const string Ledger::FORMAT_MSG = "{{\"timestamp\": {}, \"symbol\": \"{}\", \"price\": {}, \"quantity\": {}, \"tax\": {}, \"commission\": {}}}";

Ledger::Ledger(double initial_cash, ostream& out)
	: out_(out)
	, mutex_(make_unique<critical_section>()) {

	logger->debug("Initializing");
	logger->info("Initial cash: {:.0f}", initial_cash);

	out_ << fmt::format("{{\"initial_cash\": {:.0f}}}"
						, initial_cash) << endl;
}

Ledger::~Ledger() {}

void Ledger::write(const Msg& msg) {
	logger->debug("Writing: [{}]x{}", msg.symbol, msg.broker_quantity);

	critical_section::scoped_lock(*mutex_);
	out_ << fmt::format(FORMAT_MSG
						, msg.fetcher_timestamp
						, msg.symbol
						, msg.broker_price
						, msg.broker_quantity
						, 0 // TODO tax
						, 0 // TODO commission
	) << endl;
}
