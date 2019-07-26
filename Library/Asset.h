#pragma once
#include "pch.h"
#include "Holding.h"

using namespace std;
using namespace concurrency;

class Asset {
public:
	Asset(double cash);

	// TODO Subscribe holdings_ from TickFetcher
	// TODO Consider the persistence of Cash. e.g. Load from a file or something 

	void Bought(const string& symbol, double quantity, double bought_price);
	void Sold(const string& symbol, double quantity, double bought_price);
	double GetTotalRisk();

	double cash() const;
	double quantity(const string& symbol) const;
	double bought_price(const string& symbol) const;

private:
	atomic<double> cash_;
	concurrent_unordered_map<string, Holding> holdings_;

	static shared_ptr<spdlog::logger> logger;
};

