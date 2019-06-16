#pragma once

#include "pch.h"

using namespace std;

struct OrderMsg {
	OrderMsg(const string& symbol, double price, double quantity, time_t lastest_timestamp);

	string symbol;
	double price{};
	double quantity{};
	time_t lastest_timestamp{};

	//OrderMsg(const OrderMsg& src) = delete;
	//OrderMsg& operator=(const OrderMsg& rhs) = delete;
};