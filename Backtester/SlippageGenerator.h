#pragma once
#include "pch.h"

using namespace std;
using fn_unit_price = double(*)(double);

class SlippageGenerator {
public:
	SlippageGenerator();

	enum class Market { KOSPI, KOSDAQ };

	double simulate_market_price(Market market, double fetcher_price);
	static double get_unit_price_kospi(double current_price);
	static double get_unit_price_kosdaq(double current_price);

private:
	random_device rd {};
	mt19937 gen {rd()};
	normal_distribution<> d {0, 0.5};
};

