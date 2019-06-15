#pragma once
#include "pch.h"
#include "TickMsg.h"

using std::string;

struct Ticks {
	Ticks();
	bool AddTick(const TickMsg& m);

	const std::vector<double>& prices() const;
	const std::vector<double>& volumes() const;

	time_t timestamp{};

private:
	static const size_t kNumKeep = 100;	// number of ticks to keep from DeleteOld

	void AddValue(std::vector<double>& v, double value);
	void DeleteOld(std::vector<double>& v, size_t num_keep);

	//std::mutex mutex;
	std::vector<double> prices_;
	std::vector<double> volumes_;
	//std::deque<TickMsg> pendings_;
};