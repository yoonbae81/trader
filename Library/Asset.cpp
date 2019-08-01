#include "pch.h"
#include "Asset.h"

shared_ptr<spdlog::logger> Asset::logger = spdlog::stdout_color_mt("asset");

Asset::Asset(double cash)
	: cash_(cash) {
	logger->debug("Initializing");
}

void Asset::bought(const string& symbol, double quantity, double bought_price) {
	auto& h = holdings_[symbol];

	critical_section::scoped_lock(*h.mutex);
	{
		auto quantity_old = h.quantity;
		auto price_old = h.bought_price;

		h.quantity = quantity_old + quantity;
		h.bought_price = (quantity_old * price_old + quantity * bought_price) / (quantity_old + quantity);
	}

	auto current_cash = cash_.load();
	while (!cash_.compare_exchange_weak(current_cash, current_cash - quantity * bought_price));
}

void Asset::sold(const string& symbol, double quantity, double bought_price) {
	Holding& h = holdings_[symbol];

	critical_section::scoped_lock(*h.mutex);
	{
		auto quantity_old = h.quantity;
		h.quantity -= quantity;
	}

	auto current_cash = cash_.load();
	while (!cash_.compare_exchange_weak(current_cash, current_cash + quantity * bought_price));
}

double Asset::total_risk() const {
	double result {};

	for_each(begin(holdings_), end(holdings_), [&result](auto& p) {
		result += p.second.quantity * p.second.bought_price;
	});

	return result;
}

double Asset::cash() const {
	return cash_.load();
}

bool Asset::has(const string& symbol) const {
	return holdings_.find(symbol) != holdings_.end();
}

Holding& Asset::operator[](const string& symbol) {
	return holdings_.at(symbol);
}

