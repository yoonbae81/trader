#include "pch.h"
#include "Asset.h"

Asset::Asset(double cash) : cash_(cash)
{
}

void Asset::Bought(const string& symbol, double quantity, double price)
{
	auto& h = holdings_[symbol];

	critical_section::scoped_lock(*h.mutex);
	{
		auto quantity_old = h.quantity;
		auto price_old = h.price;

		h.quantity = quantity_old + quantity;
		h.price = (quantity_old * price_old + quantity * price) / (quantity_old + quantity);
	}

	auto current_cash = cash_.load();
	while (!cash_.compare_exchange_weak(current_cash, current_cash - quantity * price));
}

void Asset::Sold(const string& symbol, double quantity, double price)
{
	Holding& h = holdings_[symbol];

	critical_section::scoped_lock(*h.mutex);
	{
		auto quantity_old = h.quantity;
		h.quantity -= quantity;
	}

	auto current_cash = cash_.load();
	while (!cash_.compare_exchange_weak(current_cash, current_cash + quantity * price));
}

double Asset::cash() const
{
	return cash_.load();
}
double Asset::quantity(const string& symbol) const
{
	return holdings_.at(symbol).quantity;
}

double Asset::price(const string& symbol) const
{
	return holdings_.at(symbol).price;
}

void Asset::run()
{
	// TODO Subscribe holdings_ from TickFetcher
	// TODO Compare the current price to calculated stoploss price
	// TODO When stoploss activated, Send an Order
	done();
}
