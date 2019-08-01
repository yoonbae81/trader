#include "pch.h"
#include "Ledger.h"

shared_ptr<spdlog::logger> Ledger::logger = spdlog::stdout_color_mt("ledger");

Ledger::Ledger(ISource<Msg>& source, const string& filename)
	: source_(source)
	, filename_(filename) {

	logger->debug("Initializing");
	logger->info("Filename: {}", filename);
}

Ledger::~Ledger() {}

void Ledger::run() {
	logger->info("Running");
	while (true) {
		auto msg = receive(source_);
		if (msg == Msg::QUIT) break;

		// TODO
		// Write to file 

		logger->trace("Written");
	}

	logger->debug("Done");
	done();
}
