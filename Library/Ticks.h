#pragma once
#include "pch.h"
#include "Msg.h"

using namespace std;
using namespace std::chrono;

struct Ticks {
	Ticks();

	Ticks(Ticks&& src) noexcept
		: capacity(src.capacity)
		, prices(move(src.prices))
		, quantities(move(src.quantities))
		, timestamp(src.timestamp)
		, latest_price_(src.latest_price_) {};

	bool update(const Msg& m);

	const size_t capacity;
	vector<double> prices;
	vector<double> quantities;
	time_t timestamp {};

	static const size_t kNumKeep = 100;	// number of ticks to keep during DeleteOld()

private:
	void add(vector<double>& v, double value);
	void erase_old(vector<double>& v, size_t num_keep);

	double latest_price_ {}; // for checking price changed in update()
};