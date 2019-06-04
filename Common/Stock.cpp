#include "pch.h"
#include "Stock.h"

using namespace std;

bool Ticks::Contains(const std::string& symbol) 
{
	if (map_.find(symbol) == map_.end())
		return false;
	return true;
}

Ticks& Ticks::Get(const std::string& symbol)
{
	try {
		return *map_.at(symbol);
	}
	catch (out_of_range) {
		auto s = make_unique<Ticks>(symbol);
		map_.emplace(symbol, move(s));
		return *map_.at(symbol);
	}
}

void Ticks::Clear() {
	map_.clear();
}


Ticks::Ticks(const string& symbol) : symbol_(symbol)
{
	int capacity = rand() % 5000 + 1000;
	prices_.reserve(capacity);
	volumes_.reserve(capacity);
}

const string& Ticks::symbol() const
{
	return symbol_;
}

bool Ticks::Update(const PriceMsg& m) {
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

const std::vector<double>& Ticks::prices() const
{
	return prices_;
}

const std::vector<double>& Ticks::volumes() const
{
	return volumes_;
}

void Ticks::Add(vector<double>& v, double value) {
	if (v.capacity() == v.size())
		Recycle(v);
	v.emplace_back(value);
}

void Ticks::Recycle(std::vector<double>& v)
{
	std::copy(v.end() - kNumKeep, v.end(), v.begin());
	v.erase(v.begin() + kNumKeep, v.end());
}

