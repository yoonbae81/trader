#pragma once
#include "pch.h"
#include "Msg.h"
#include "Holding.h"

using namespace std;
using namespace concurrency;

class Asset {
public:
	Asset(double initial_cash);

	// TODO Load initial_cash and holdings from a file or something 

	void bought(const Msg& msg);
	void sold(const Msg& msg);

	double cash() const;
	double current_risk() const;
	double available_risk() const;
	double profit_rate() const;

	bool has(const string& symbol) const;
	Holding& operator[](const string& symbol);

private:
	const double initial_cash_;
	atomic<double> cash_;
	concurrent_unordered_map<string, Holding> holdings_;

	static shared_ptr<spdlog::logger> logger;
};

