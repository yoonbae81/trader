#pragma once
#include "pch.h"
#include "Stock.h"

class Stocks
{
public:
	Stocks() = default;
	~Stocks();

	bool Contains(const std::string& symbol) const;
	Stock& Get(const std::string& symbol);
	void Reset();

private:
	std::unordered_map<std::string, std::unique_ptr<Stock>> map;

	Stocks(const Stocks& src) = delete;
	Stocks& operator=(const Stocks& rhs) = delete;
	Stocks& operator=(Stocks&& rhs) = delete;
};

