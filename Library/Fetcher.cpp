#include "pch.h"
#include "Fetcher.h"

Fetcher::Fetcher() {
	logger->trace("Initializing");
}

Fetcher::~Fetcher() {
	logger->trace("Done");
}

void Fetcher::add_target(ITarget<shared_ptr<Msg>>& target) {
	targets_.insert({&target, 0});
	//logger->trace("Target added");
}

ITarget<shared_ptr<Msg>>& Fetcher::get_target(const string& symbol) {
	ITarget<shared_ptr<Msg>>* target;
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
			auto& target = get_target(m->symbol);
			asend(target, m);
			count++;

			// TODO set msg.fetcher_timestamp 
			logger->trace("Sent [{}]", line);

		} catch (ParsingException& e) {
			logger->warn("Error {}", e.what());
			continue;
		}
	}
	logger->info("Sent {} ticks", count);

	auto m = make_shared<Msg>(Msg::QUIT);
	for (auto& item : targets_) {
		asend(*item.first, m);
	}

	done();
}

