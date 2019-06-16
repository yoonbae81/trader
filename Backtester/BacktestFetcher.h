#pragma once
#include "pch.h"
#include "../Library/TickMsg.h"

class BacktestFetcher
{
	std::ifstream msgFile;

public:
	BacktestFetcher(const std::string& filePath);
	~BacktestFetcher();

	TickMsg GetMessage();

	BacktestFetcher(const BacktestFetcher&) = delete;
	BacktestFetcher& operator=(const BacktestFetcher&) = delete;
};

