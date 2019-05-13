#pragma once
#include "pch.h"
#include "PriceMsg.h"

enum class Storage {
	AA = 30
};

class Stock {
	const size_t kNumKeep = 30;	// must be bigger than long-window

	std::string symbol_{};
	size_t quantity_{};
	time_t timestamp_{};
	double stoploss_{};
	std::vector<double> prices_;
	std::vector<double> volumes_;

public:
	Stock();

	bool AddTick(PriceMsg &m);
	void AddValue(std::vector<double>& v, double value);

	const size_t& quantity() const;
	const std::vector<double>& prices() const;
	const std::vector<double>& volumes() const;

};