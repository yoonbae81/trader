#pragma once

#include "pch.h"

using namespace std;
using namespace concurrency;

class AssetManager : public agent {
public:
	AssetManager(double cash);
	// TODO AssetManager(cash, socketTickFetcher, socketOrderProcessor)
	// TODO Consider the persistence of Cash. e.g. Load from a file or something 

	void Bought(const string& symbol, double quantity, double price);
	void Sold(const string& symbol, double quantity, double price);

	double cash();
	double quantity(const string& symbol);
	double price(const string& symbol);

protected:
	void run() override;

private:
	overwrite_buffer<double> cash_;
	concurrent_unordered_map<string, pair<double, double>> holdings; // quantity, average_price
	//concurrent_unordered_map<string, pair<double, double>> holdings; // pair.fisrt = quantity, pair.second = price
};
