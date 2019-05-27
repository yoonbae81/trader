#pragma once
#include "pch.h"
#include "Stock.h"

class StockMap
{
public:
	StockMap() = default;
	~StockMap() = default;

	Stock& Get(const std::string& symbol);
	bool Contains(const std::string& symbol) const;
	void Clear();

private:
	std::unordered_map<std::string, std::unique_ptr<Stock>> map_;

	StockMap(const StockMap& src) = delete;
	StockMap& operator=(const StockMap& rhs) = delete;
	StockMap& operator=(StockMap&& rhs) = delete;
};
