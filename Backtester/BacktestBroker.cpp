#include "pch.h"
#include "BacktestBroker.h"

using namespace std;

BacktestBroker::BacktestBroker()
{
	clog << "Broker initalized" << endl;
}

BacktestBroker::~BacktestBroker()
{
}

void BacktestBroker::Order()
{
	clog << "Order sent" << endl;
}
