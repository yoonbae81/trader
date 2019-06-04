#include "pch.h"
#include "Ticks.h"

using namespace std;

Ticks::Ticks()
{
	int capacity = rand() % 5000 + 1000;
	prices_.reserve(capacity);
	volumes_.reserve(capacity);
}

bool Ticks::Put(const PriceMsg& m) {
	bool added = false;

	if (timestamp == m.timestamp) {
		prices_.back() = m.price;
		volumes_.back() += m.volume;
	}
	else {
		AddValue(prices_, m.price);
		AddValue(volumes_, m.volume);
		timestamp = m.timestamp;
		added = true;
	}

	return added;
}

void Ticks::AddValue(vector<double>& v, double value) {
	if (v.capacity() == v.size())
		DeleteOld(v);
	v.emplace_back(value);
}

void Ticks::DeleteOld(std::vector<double>& v)
{
	std::copy(v.end() - kNumKeep, v.end(), v.begin());
	v.erase(v.begin() + kNumKeep, v.end());
}

const std::vector<double>& Ticks::prices() const
{
	return prices_;
}

const std::vector<double>& Ticks::volumes() const
{
	return volumes_;
}


