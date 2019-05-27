#include "pch.h"
#include "Stock.h"

using namespace std;

Stock::Stock(const string& symbol) : symbol_(symbol)
{
	int capacity = rand() % 5000 + 1000;
	prices_.reserve(capacity);
	volumes_.reserve(capacity);
}

const string& Stock::symbol() const
{
	return symbol_;
}

bool Stock::Update(const PriceMsg& m) {
	bool added = false;

	if (timestamp == m.timestamp) {
		prices_.back() = m.price;
		volumes_.back() += m.volume;
	}
	else {
		Add(prices_, m.price);
		Add(volumes_, m.volume);
		timestamp = m.timestamp;
		added = true;
	}

	return added;
}

const std::vector<double>& Stock::prices() const
{
	return prices_;
}

const std::vector<double>& Stock::volumes() const
{
	return volumes_;
}

void Stock::Add(vector<double>& v, double value) {
	if (v.capacity() == v.size())
		Recycle(v);
	v.emplace_back(value);
}

void Stock::Recycle(std::vector<double>& v)
{
	std::copy(v.end() - kNumKeep, v.end(), v.begin());
	v.erase(v.begin() + kNumKeep, v.end());
}

