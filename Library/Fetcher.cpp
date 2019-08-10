#include "pch.h"
#include "Fetcher.h"

Fetcher::Fetcher() {
	logger->trace("Initializing");
}

Fetcher::~Fetcher() {
	logger->trace("Done");
}

void Fetcher::add_target(ITarget<Msg>& target) {
	targets_.insert({&target, 0});
	//logger->trace("Target added");
}

ITarget<Msg>& Fetcher::get_target(const string& symbol) {
	ITarget<Msg>* target;
	try {
		target = assigned_.at(symbol);
	} catch (out_of_range) {
		auto item = min_element(targets_.begin(), targets_.end(),
								[](const auto& l, const auto& r) {return l.second < r.second; });
		target = item->first;
		assigned_[symbol] = target;
	}

	targets_[target]++;
	return *target;
}

void Fetcher::run() {
	logger->debug("Running");

	string line;
	size_t count = 0;
	while (fetch(line)) {
		try {
			auto m = Msg::parse(line);
			auto& target = get_target(m.symbol);
			asend(target, m);
			count++;

			// TODO set msg.fetcher_timestamp 
			logger->trace("Sent [{}]", line);

		} catch (invalid_argument& e) {
			logger->warn("Error {}", e.what());
			continue;
		}
	}
	logger->info("Sent {} ticks", count);

	for (auto& item : targets_) {
		asend(*item.first, Msg::QUIT);
	}

	done();
}

