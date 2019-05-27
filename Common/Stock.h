#pragma once
#include "pch.h"
#include "PriceMsg.h"

struct Stock {
	size_t quantity{};
	time_t timestamp{};
	double stoploss{};

	Stock(const std::string& symbol);
	const std::string& symbol() const;
	
	bool Update(const PriceMsg &m);
	const std::vector<double>& prices() const;
	const std::vector<double>& volumes() const;

private:
	const static size_t kNumKeep = 30;	// number of elements to keep when vector is recycled

	std::string symbol_{};
	std::vector<double> prices_;
	std::vector<double> volumes_;
	
	void Add(std::vector<double>& v, double value);
	void Recycle(std::vector<double>& v);
	Stock() = delete;
};