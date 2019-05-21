#pragma once

class BacktestBroker 
{
public:
	BacktestBroker();
	~BacktestBroker();
	void Order(const std::string& symbol, int quantity);
};

