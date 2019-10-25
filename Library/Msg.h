#pragma once

#include "pch.h"
#include "Exceptions.h"

using namespace std;
using namespace std::chrono;

struct Msg {
	static const Msg QUIT;
	static const Msg RESET;
	static shared_ptr<Msg> parse(const string& line);

	Msg(const string& symbol) : symbol(symbol) {};
	~Msg();
	
	const string symbol;

	// TODO consider nested struct

	double fetcher_price {};
	double fetcher_quantity {};
	time_t fetcher_timestamp {};

	size_t analyzer_strength {};
	double analyzer_quantity {};

	double broker_price {};
	double broker_quantity {};
	double broker_cost {};	// transaction cost including tax and brokerage commission 
	time_t broker_elapsed {};

	bool operator==(const Msg& rhs);
	friend ostream& operator<<(ostream& os, const Msg& msg);
};

