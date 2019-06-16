#pragma once
#include "pch.h"
#include "TickMsg.h"

using namespace std;

struct Ticks {
	static const size_t kNumKeep = 100;	// number of ticks to keep from DeleteOld
	const size_t capacity() const;
	const vector<double>& prices() const;
	const vector<double>& volumes() const;
	time_t lastest_timestamp{};

	Ticks();
	bool AddTick(const TickMsg& m);

private:
	mt19937 re_;
	uniform_int_distribution<size_t> dist_;
	const size_t capacity_;
	
	vector<double> prices_;
	vector<double> volumes_;

	void AddValue(vector<double>& v, double value);
	void DeleteOld(vector<double>& v, size_t num_keep);
};