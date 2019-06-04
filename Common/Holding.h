#pragma once
#include "pch.h"

using std::string;

struct Holding
{
	void Bought(size_t quantity, double price);
	void Sold(size_t quantity, double price);

	size_t quantity() const;
	double average_price() const;

	double stoploss() const;
	void stoploss(double value);

private:
	size_t quantity_{};
	double average_price_{};
	double stoploss_{};
};

