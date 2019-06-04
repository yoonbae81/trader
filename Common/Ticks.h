#pragma once
#include "pch.h"
#include "PriceMsg.h"

using std::string;

struct Ticks { 
	Ticks();
	bool Put(const PriceMsg &m);	// TODO Rename to ADD

	const std::vector<double>& prices() const;
	const std::vector<double>& volumes() const;

	time_t timestamp{};

private:
	static const size_t kNumKeep = 30;	// number of ticks to keep from DeleteOld

	void AddValue(std::vector<double>& v, double value);
	void DeleteOld(std::vector<double>& v);

	//std::mutex mutex;
	std::vector<double> prices_;
	std::vector<double> volumes_;
	//std::deque<PriceMsg> pendings_;
};