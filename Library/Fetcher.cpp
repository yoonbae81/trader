#include "pch.h"
#include "Fetcher.h"

void Fetcher::add_target(shared_ptr<ITarget<Msg>> target) {
	targets_.push_back(target);
	counts_[target] = 0;
	logger->debug("Target added");
}

ITarget<Msg>& Fetcher::get_target(const Msg& msg) {
	try {
		return *assigned_.at(msg.symbol);
	} catch (out_of_range) {
		auto item = min_element(counts_.begin(), counts_.end(),
								[](const auto& l, const auto& r) {return l.second < r.second; });
		auto target = item->first;
		assigned_[msg.symbol] = target;
		counts_[target]++;

		return *target;
	}
}


