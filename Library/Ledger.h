#pragma once
#include "pch.h"
#include "Msg.h"

using namespace std;
using namespace concurrency;

class Ledger {
public:
	Ledger(const string& filename);
	void write(const Msg& msg);
private:
	const string& filename_;
	unique_ptr<critical_section> mutex_;
	
	static shared_ptr<spdlog::logger> logger;
};

