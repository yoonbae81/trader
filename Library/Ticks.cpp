#include "pch.h"
#include "Ticks.h"

using namespace std;

Ticks::Ticks() : capacity(rand() % 9999 + 9999) {
	prices.reserve(capacity);
	quantities.reserve(capacity);
}

bool Ticks::update(const Msg& m) {
	if (timestamp == m.fetcher_timestamp) {
		prices.back() = m.fetcher_price;
		quantities.back() += m.fetcher_quantity;
	} else {
		add(prices, m.fetcher_price);
		add(quantities, m.fetcher_quantity);
		timestamp = m.fetcher_timestamp;
	}

	// return whether price changed
	if (latest_price_ == m.fetcher_price) return false;
	else {
		latest_price_ = m.fetcher_price;
		return true;
	}
}

void Ticks::add(vector<double>& v, double value) {
	if (v.capacity() == v.size())
		erase_old(v, kNumKeep);
	v.push_back(value);
}

void Ticks::erase_old(vector<double>& v, size_t num_keep) {
	copy(v.end() - num_keep, v.end(), v.begin());
	v.erase(v.begin() + num_keep, v.end());
}

