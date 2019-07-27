#include "pch.h"
#include "Fetcher.h"

void Fetcher::add_target(shared_ptr<ITarget<Msg>> target) {
	targets_.push_back(target);
	frequency_[target] = 0;
	logger->debug("Target added");
}

shared_ptr<ITarget<Msg>> Fetcher::get_target(const string& symbol) {
	try {
		return assigned_.at(symbol);
	} catch (out_of_range) {
		auto item = min_element(frequency_.begin(), frequency_.end(),
								[](const auto& l, const auto& r) {return l.second < r.second; });
		auto target = item->first;
		assigned_[symbol] = target;
		frequency_[target]++;

		return target;
	}
}


