#pragma once

#include "pch.h"

struct PriceMsg {
	const std::string symbol;
	const double price {};
	const size_t volume {};
	const time_t timestamp {};

	PriceMsg(const std::string& symbol, double price, size_t volume, time_t timestamp);
	PriceMsg(PriceMsg&& src) = default;
	
	static PriceMsg Parse(const std::string& msg);
	
	PriceMsg& operator=(const PriceMsg& rhs) = delete;
	PriceMsg(const PriceMsg& src) = delete;
	PriceMsg& operator=(PriceMsg&& rhs) = delete;
};