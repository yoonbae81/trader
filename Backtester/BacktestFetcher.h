#pragma once
#include "../Common/PriceMsg.h"

class BacktestFetcher
{
public:
	BacktestFetcher();
	
	// TODO loading backtest files from given dir
	// BacktestFetcher(const std::string& dir);
	
	virtual ~BacktestFetcher();
	virtual PriceMsg GetMessage();
};

