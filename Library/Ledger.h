#pragma once
#include "pch.h"
#include "Asset.h"
#include "Msg.h"

using namespace std;
using namespace concurrency;

class Ledger {
public:
	Ledger(double initial_cash, ostream& out);
	~Ledger();

	void write(const Msg& msg);

private:
	const static string FORMAT_MSG;
	static shared_ptr<spdlog::logger> logger;

	ostream& out_;
	unique_ptr<critical_section> mutex_;

	Ledger(const Ledger&) = delete;
	Ledger& operator=(const Ledger&) = delete;
};

