#include "pch.h" 
#include "Ledger.h"

shared_ptr<spdlog::logger> Ledger::logger = spdlog::stdout_color_mt("ledger");
const string Ledger::FORMAT_MSG = "{{\"timestamp\": {}, \"symbol\": \"{}\", \"price\": {}, \"quantity\": {}, \"tax\": {}, \"commission\": {}}}";

Ledger::Ledger(const string& filename, double initial_cash)
	: outfile_(filename)
	, mutex_(make_unique<critical_section>()) {

	logger->debug("Initializing");
	logger->info("Creating file: {}", filename);
	logger->debug("Initial Cash: {:.0f}", initial_cash);

	outfile_ << "{" << endl;
	outfile_ << fmt::format("\"initial_cash\": {:.0f},", initial_cash) << endl;
	outfile_ << "\"transactions\": [" << endl;
}

Ledger::~Ledger() {
	outfile_ << "]" << endl;
	outfile_ << "}";
	outfile_.close();
}

void Ledger::write(const Msg& msg) {
	string line = fmt::format(FORMAT_MSG
							  , msg.fetcher_timestamp
							  , msg.symbol
							  , msg.broker_price
							  , msg.broker_quantity
							  , 0 // TODO tax
							  , 0 // TODO commission
	);

	logger->debug("Writing: {}", line);
	critical_section::scoped_lock(*mutex_);
	{
		outfile_ << comma << line << endl;
		comma = ',';
	}
}
