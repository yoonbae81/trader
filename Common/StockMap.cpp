#include "pch.h"
#include "StockMap.h"

using namespace std;

bool StockMap::Contains(const std::string& symbol) const
{
	if (map_.find(symbol) == map_.end())
		return false;
	return true;
}

Stock& StockMap::Get(const std::string& symbol)
{
	try {
		return *map_.at(symbol);
	}
	catch (out_of_range) {
		auto s = make_unique<Stock>(symbol);
		map_.emplace(symbol, move(s));
		return *map_.at(symbol);
	}
}

void StockMap::Clear() {
	map_.clear();
}

