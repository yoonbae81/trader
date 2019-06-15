#include "pch.h"
#include "AssetManager.h"

AssetManager::AssetManager(double cash)
{
	send(cash_, cash);
}

void AssetManager::Bought(const string& symbol, double quantity, double price)
{
	critical_section::scoped_lock lock();

	pair<double, double> qp_old = holdings[symbol];
	auto quantity_old = qp_old.first;
	auto quantity_new = quantity_old + quantity;
	auto price_old = qp_old.second;
	auto price_new = (quantity_old * price_old + quantity * price) / (quantity_old + quantity);
	holdings[symbol] = make_pair(quantity_new, price_new);

	double cash_old = receive(cash_);
	double cash_new = cash_old - (quantity * price);
	send(cash_, cash_new);
}

void AssetManager::Sold(const string& symbol, double quantity, double price)
{
}

double AssetManager::cash()
{
	return receive(cash_);
}
double AssetManager::quantity(const string& symbol)
{
	return holdings[symbol].first;
}

double AssetManager::price(const string& symbol)
{
	return holdings[symbol].second;
}

void AssetManager::run()
{
	// TODO Subscribe holdings from TickFetcher
	// TODO Compare the current price to calculated stoploss price
	// TODO When stoploss activated, Send an Order
	done();
}
