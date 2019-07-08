#pragma once
#include "pch.h"
#include "Msg.h"

using namespace std;

struct Ticks {
	Ticks();

	bool AddTick(const Msg& m);

	static const size_t kNumKeep = 100;	// number of ticks to keep during DeleteOld()
	const size_t capacity;
	time_t timestamp {};

	vector<double> prices;
	vector<double> quantities;

private:
	void AddValue(vector<double>& v, double value);
	void DeleteOld(vector<double>& v, size_t num_keep);
};