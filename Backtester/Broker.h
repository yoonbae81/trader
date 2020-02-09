#pragma once
#include "pch.h"
#include "../Library/Msg.h"
#include "../Library/Asset.h"
#include "../Library/Ledger.h"

using namespace std;
using namespace concurrency;

// TODO Separate broker into backtester and trader

class Broker : public agent {
public:
	Broker(Asset& asset, Ledger& ledger, ISource<shared_ptr<Msg>>& source);
	~Broker();

	// for simulation slippage
	double simulate_market_price(const string& string, double fetcher_price);
	static double get_unit_price_kospi(double current_price);
	static double get_unit_price_kosdaq(double current_price);

protected:
	void run() override;

	double calc_transaction_cost(double filled_quanitty, double filled_price);
	void request(Msg& m);
	void filled(Msg& m);

	Asset& asset_;
	Ledger& ledger_;
	ISource<shared_ptr<Msg>>& source_;

	// TODO load from configuration file
	const double kTaxRate = 0.25 / 100;
	const double kCommissionRate = 0.015 / 100;

	static shared_ptr<spdlog::logger> logger;

private:
	// for simulation slippage
	random_device rd {};
	mt19937 gen {rd()};
	normal_distribution<> d {0, 0.5};
};

