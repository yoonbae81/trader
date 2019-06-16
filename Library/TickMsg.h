#pragma once

#include "pch.h"

struct TickMsg {
	static TickMsg Parse(const std::string& line);

	TickMsg(TickMsg&& src) = default;
	~TickMsg() = default;

	std::string symbol;
	double price{};
	double volume{};
	time_t lastest_timestamp{};


private:
	TickMsg() = default;

	TickMsg(const TickMsg& src) = delete;
	TickMsg& operator=(const TickMsg& rhs) = delete;
	TickMsg& operator=(TickMsg&& rhs) = delete;
};