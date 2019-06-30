#pragma once

#include "pch.h"
#include "Exceptions.h"

using namespace std;

struct OrderMsg {
	OrderMsg(const string& symbol, int quantity)
		: symbol_(symbol), quantity_ {quantity} {};

	// TODO Rename or override with << 
	const string& ToString() const {
		throw runtime_error("Not Implemented");
	};

	// TODO implement
	static OrderMsg Parse(const string& line) {
		throw runtime_error("Not Implemented");
		return OrderMsg("", 0);
	};

private:
	string symbol_;
	int quantity_;
};

