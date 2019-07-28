#include "pch.h"
#include "Fetcher.h"

void Fetcher::add_target(shared_ptr<ITarget<Msg>> target) {
	targets_.insert({target, 0});
	logger->trace("Target added");
}

shared_ptr<ITarget<Msg>> Fetcher::get_target(const string& symbol) {
	shared_ptr<ITarget<Msg>> target;
	try {
		target = assigned_.at(symbol);
	} catch (out_of_range) {
		auto item = min_element(targets_.begin(), targets_.end(),
								[](const auto& l, const auto& r) {return l.second < r.second; });
		target = item->first;
		assigned_[symbol] = target;
	}

	targets_[target]++;
	return target;
}

