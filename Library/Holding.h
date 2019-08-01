#pragma once
#include "pch.h"

using namespace std;
using namespace concurrency;

struct Holding {
	double quantity {};
	double bought_price {};
	double current_price {};
	double stoploss_price {};
	unique_ptr<critical_section> mutex;

	Holding() : mutex(make_unique<critical_section>()) {};
};