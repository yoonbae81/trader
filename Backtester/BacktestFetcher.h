#pragma once
#include "pch.h"
#include "../Common/PriceMsg.h"

class BacktestFetcher
{
	std::ifstream msgFile;

public:
	BacktestFetcher(const std::string& filePath);
	~BacktestFetcher();

	PriceMsg GetMessage();

	BacktestFetcher(const BacktestFetcher&) = delete;
	BacktestFetcher& operator=(const BacktestFetcher&) = delete;

};

