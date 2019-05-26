#include "pch.h"
#include "Stocks.h"

using namespace std;

bool Stocks::Contains(const std::string& symbol) const
{
	if (map.find(symbol) == map.end())
		return false;
	return true;
}

Stock& Stocks::Get(const std::string& symbol)
{
	try {
		return *map.at(symbol);
	}
	catch (out_of_range) {
		map.emplace(symbol, make_unique<Stock>(symbol));
		return *map.at(symbol);
	}
}

void Stocks::Reset() {
	map.clear();
}

Stocks::~Stocks()
{

}
