#pragma once

#include "pch.h"
#include "Holding.h"

using namespace std;
using namespace concurrency;

class Asset : public agent {
public:
	Asset(double cash);
	// TODO Asset(cash, socketTickFetcher, socketOrderProcessor)
	// TODO Consider the persistence of Cash. e.g. Load from a file or something 

	void Bought(const string& symbol, double quantity, double price);
	void Sold(const string& symbol, double quantity, double price);

	double cash() const;
	double quantity(const string& symbol) const;
	double price(const string& symbol) const;

protected:
	void run() override;

private:
	atomic<double> cash_;
	concurrent_unordered_map<string, Holding> holdings_;
};
