#pragma once

#include "pch.h"
#include "Exceptions.h"

using namespace std;

struct Msg {
	static const Msg QUIT;
	static const Msg RESET;
	static Msg Parse(const string& line);

	Msg(const string& symbol) : symbol(symbol) {};

	const string symbol;

	// TODO consider nested struct
	double tick_price {};
	double tick_quantity {};
	time_t tick_timestamp {};

	int    signal_strength {};
	time_t signal_timestamp {};

	double order_price {};
	double order_quantity {};
	time_t order_timestamp {};

	double filled_price {};
	double filled_quantity {};
	time_t filled_timestamp {};

	bool operator==(const Msg& rhs);
	friend ostream& operator<<(ostream& os, const Msg& msg);
};

