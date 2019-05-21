#pragma once

#include "pch.h"

struct OrderMsg {
	OrderMsg(const std::string symbol, const double price, const size_t quantity, const time_t timestamp);

	std::string symbol;
	double price {};
	size_t quantity{};
	time_t timestamp {};

	OrderMsg(const OrderMsg &src) = delete;
	OrderMsg& operator=(const OrderMsg &rhs) = delete;
};