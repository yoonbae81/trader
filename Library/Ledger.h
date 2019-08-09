#pragma once
#include "pch.h"
#include "Asset.h"
#include "Msg.h"

using namespace std;
using namespace concurrency;

class Ledger {
public:
	Ledger(const string& filename,double initial_cash);
	~Ledger();

	void write(const Msg& msg);

private:
	const static string FORMAT_MSG;
	char comma = ' ';

	ofstream outfile_;
	unique_ptr<critical_section> mutex_;
	static shared_ptr<spdlog::logger> logger;

	Ledger(const Ledger&) = delete;
	Ledger& operator=(const Ledger&) = delete;
};

