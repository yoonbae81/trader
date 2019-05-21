#pragma once
#include "pch.h"
#include "../Common/PriceMsg.h"

class BacktestFetcher
{
public:
	BacktestFetcher(const std::string& filePath);
	
	virtual ~BacktestFetcher();
	virtual PriceMsg GetMessage();

private:
	std::ifstream datafile;
};

