#pragma once

#include "pch.h"

struct PriceMsg {
	static PriceMsg Parse(const std::string& line);

	PriceMsg(PriceMsg&& src) = default;
	~PriceMsg() = default;

	std::string symbol;
	double price{};
	size_t volume{};
	time_t timestamp{};


private:
	PriceMsg() = default;

	PriceMsg(const PriceMsg& src) = delete;
	PriceMsg& operator=(const PriceMsg& rhs) = delete;
	PriceMsg& operator=(PriceMsg&& rhs) = delete;
};