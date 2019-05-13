#include "pch.h"
#include "Stock.h"

using namespace std;

Stock::Stock() {
	int capacity = rand() % 3000 + 1000;
	prices_.reserve(capacity);
	volumes_.reserve(capacity);
}

bool Stock::AddTick(PriceMsg& m) {
	bool added = false;

	if (timestamp_ == m.timestamp) {
		prices_.back() = m.price;
		volumes_.back() += m.volume;
	}
	else {
		AddValue(prices_, m.price);
		AddValue(volumes_, m.volume);
		timestamp_ = m.timestamp;
		added = true;
	}

	return added;
}

void Stock::AddValue(vector<double>& v, double value) {
	if (v.capacity() == v.size()) {
		std::copy(v.end() - kNumKeep, v.end(), v.begin());
		v.erase(v.begin() + kNumKeep, v.end());
	}

	v.emplace_back(value);
}

const double Stock::stoploss() const
{
	return stoploss_;
}

const size_t& Stock::quantity() const {
	return quantity_;
}

const vector<double>& Stock::prices() const {
	return prices_;
}

const vector<double>& Stock::volumes() const {
	return volumes_;
}

