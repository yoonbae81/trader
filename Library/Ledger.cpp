#include "pch.h"
#include "Ledger.h"

shared_ptr<spdlog::logger> Ledger::logger = spdlog::stdout_color_mt("ledger");

Ledger::Ledger(const string& filename)
	: filename_(filename)
	, mutex_(make_unique<critical_section>()) {

	logger->debug("Initializing");
	logger->info("Creating file: {}", filename_);
}




void Ledger::write(const Msg& msg) {
	logger->debug("Wrote: {}", msg.symbol);
}
