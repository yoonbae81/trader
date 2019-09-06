#pragma once
#include "pch.h"
#include "../Library/Msg.h"
#include "../Library/Asset.h"
#include "../Library/Ledger.h"
#include "SlippageGenerator.h"

using namespace std;
using namespace concurrency;

class Broker : public agent {
public:
	Broker(Asset& asset, Ledger& ledger, ISource<shared_ptr<Msg>>& source);
	~Broker();

protected:
	void run() override;
	double calc_transaction_cost(double filled_quanitty, double filled_price);
	void callback(Msg& m);

	Asset& asset_;
	Ledger& ledger_;
	ISource<shared_ptr<Msg>>& source_;

	const double kTaxRate = 0.25 / 100;
	const double kCommissionRate = 0.015 / 100;

	static shared_ptr<spdlog::logger> logger;

private:
	SlippageGenerator slippage {};
};

