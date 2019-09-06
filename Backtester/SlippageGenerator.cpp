#include "pch.h"
#include "SlippageGenerator.h"

SlippageGenerator::SlippageGenerator() {
}

double SlippageGenerator::simulate_market_price(Market market, double fetcher_price) {
	fn_unit_price fn;
	if (market == Market::KOSPI) fn = get_unit_price_kospi;
	else fn = get_unit_price_kosdaq;

	double result = fetcher_price;
	int gap = round(d(gen));
	result += gap * fn(fetcher_price);
	return result;
}

double SlippageGenerator::get_unit_price_kospi(double current_price) {
	// As of Sep. 2019
	if (current_price < 1'000) return 1;
	else if (current_price < 5'000) return 5;
	else if (current_price < 10'000) return 10;
	else if (current_price < 50'000) return 50;
	else if (current_price < 100'000) return 100;
	else if (current_price < 500'000) return 500;
	else return 1'000;
}


double SlippageGenerator::get_unit_price_kosdaq(double current_price) {
	// As of Sep. 2019
	if (current_price < 1'000) return 1;
	else if (current_price < 5'000) return 5;
	else if (current_price < 10'000) return 10;
	else if (current_price < 50'000) return 50;
	else return 100;
}
