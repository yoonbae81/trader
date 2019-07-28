#include "pch.h"
#include "Ticks.h"

using namespace std;

Ticks::Ticks() : capacity(rand() % 9999 + 9999) {
	prices.reserve(capacity);
	quantities.reserve(capacity);
}

bool Ticks::add(const Msg& m) {
	bool added = false;

	if (timestamp == m.tick_timestamp) {
		prices.back() = m.tick_price;
		quantities.back() += m.tick_quantity;
	} else {
		add(prices, m.tick_price);
		add(quantities, m.tick_quantity);
		timestamp = m.tick_timestamp;
		added = true;
	}

	return added;
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

