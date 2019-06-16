#pragma once
#include "pch.h"
#include "TickMsg.h"

using namespace std;

struct Ticks {
	static const size_t kNumKeep = 100;	// number of ticks to keep from DeleteOld

	Ticks();
	bool AddTick(const TickMsg& m);

	size_t capacity() const;
	const std::vector<double>& prices() const;
	const std::vector<double>& volumes() const;

	time_t timestamp{};

private:
	mt19937 re_;
	uniform_int_distribution<size_t> dist_;
	const size_t capacity_;
	std::vector<double> prices_;
	std::vector<double> volumes_;

	void AddValue(std::vector<double>& v, double value);
	void DeleteOld(std::vector<double>& v, size_t num_keep);
};