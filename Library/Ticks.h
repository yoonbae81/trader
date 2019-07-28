#pragma once
#include "pch.h"
#include "Msg.h"

using namespace std;

struct Ticks {
	Ticks();

	bool add(const Msg& m);

	static const size_t kNumKeep = 100;	// number of ticks to keep during DeleteOld()
	const size_t capacity;
	time_t timestamp {};

	vector<double> prices;
	vector<double> quantities;

private:
	void add(vector<double>& v, double value);
	void erase_old(vector<double>& v, size_t num_keep);
};