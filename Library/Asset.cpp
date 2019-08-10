#include "pch.h"
#include "Asset.h"

shared_ptr<spdlog::logger> Asset::logger = spdlog::stdout_color_mt("asset");

Asset::Asset(double initial_cash)
	: initial_cash_(initial_cash), cash_(initial_cash) {
	logger->trace("Initializing");
	logger->info("Cash {:.0f}", cash_);
}

void Asset::bought(const Msg& m) {
	auto& h = holdings_[m.symbol];

	critical_section::scoped_lock(*h.mutex);
	{
		auto quantity_old = h.quantity;
		auto price_old = h.bought_price;

		h.quantity = quantity_old + m.broker_quantity;
		h.bought_price = (quantity_old * price_old + m.broker_quantity * m.broker_price) / (quantity_old + m.broker_quantity);
	}

	auto current_cash = cash_.load();
	while (!cash_.compare_exchange_weak(current_cash, current_cash - m.broker_quantity * m.broker_price));

	// TODO Log 
}

void Asset::sold(const Msg& m) {
	Holding& h = holdings_[m.symbol];

	critical_section::scoped_lock(*h.mutex);
	{
		auto quantity_old = h.quantity;
		h.quantity -= m.broker_quantity;
	}

	auto current_cash = cash_.load();
	while (!cash_.compare_exchange_weak(current_cash, current_cash + m.broker_quantity * m.broker_price));

	// TODO Log 
}

double Asset::current_risk() const {
	double result {};

	for_each(begin(holdings_), end(holdings_), [&result](auto& p) {
		result += p.second.quantity * p.second.bought_price;
	});

	return result;
}

double Asset::available_risk() const {
	return cash_ * 0.1;
}

double Asset::profit_rate() const {
	return cash_ / initial_cash_ - 1;
}

double Asset::cash() const {
	return cash_;
}

bool Asset::has(const string& symbol) const {
	return holdings_.find(symbol) != holdings_.end();
}

Holding& Asset::operator[](const string& symbol) {
	return holdings_.at(symbol);
}

