#pragma once

#include "pch.h"

using namespace std;

struct OrderMsg {
	OrderMsg(const string& symbol, double price, double quantity, time_t timestamp);

	string symbol;
	double price{};
	double quantity{};
	time_t timestamp{};

	//OrderMsg(const OrderMsg& src) = delete;
	//OrderMsg& operator=(const OrderMsg& rhs) = delete;
};