#pragma once
#include "pch.h"
#include "Msg.h"
#include "Asset.h"
#include "Ledger.h"

using namespace std;
using namespace concurrency;

class Broker : public agent {
public:
	Broker(Asset& asset, Ledger& ledger, ISource<shared_ptr<Msg>>& source);
	~Broker();

protected:
	void run() override;
	void callback(Msg& m);

	Asset& asset_;
	Ledger& ledger_;
	ISource<shared_ptr<Msg>>& source_;

	static shared_ptr<spdlog::logger> logger;
};

