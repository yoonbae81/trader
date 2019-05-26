#pragma once

#include "pch.h"

struct PriceMsg {
	std::string symbol;
	double price {};
	size_t volume {};
	time_t timestamp {};

	~PriceMsg() = default;
	PriceMsg(PriceMsg&& src) = default;
	static PriceMsg Parse(const std::string& msg);
	
private:
	PriceMsg() = default;

	PriceMsg(const PriceMsg& src) = delete;
	PriceMsg& operator=(const PriceMsg& rhs) = delete;
	PriceMsg& operator=(PriceMsg&& rhs) = delete;
};