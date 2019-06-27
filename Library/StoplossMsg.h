#pragma once

#include "pch.h"
#include "Exceptions.h"

using namespace std;

struct StoplossMsg {
	StoplossMsg(const string& symbol, double bought_price)
		: symbol_(symbol), bought_price_(bought_price) {};

	// TODO Rename or override with << 
	const string& ToString() const {
		throw runtime_error("Not Implemented");
	};

	static StoplossMsg Parse(const string& line) {
		return StoplossMsg("", 0);
	};

private:
	string symbol_;
	double bought_price_;
};
