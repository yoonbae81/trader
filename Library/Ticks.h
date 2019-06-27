#pragma once
#include "pch.h"
#include "TickMsg.h"

using namespace std;

struct Ticks {
	Ticks();

	bool AddTick(const TickMsg& m);

	static const size_t kNumKeep = 100;	// number of ticks to keep from DeleteOld
	const size_t capacity;
	vector<double> prices;
	vector<double> quantities;
	time_t timestamp {};

private:
	mt19937 re_;
	uniform_int_distribution<size_t> dist_;
	void AddValue(vector<double>& v, double value);
	void DeleteOld(vector<double>& v, size_t num_keep);
};