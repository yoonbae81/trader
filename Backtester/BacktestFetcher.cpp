#include "pch.h"
#include "BacktestFetcher.h"

using namespace std;

BacktestFetcher::BacktestFetcher()
{
	clog << "Fetcher initalized" << endl;
}

BacktestFetcher::~BacktestFetcher()
{
}

PriceMsg BacktestFetcher::GetMessage()
{
	string msg = "112300201 015760 1243 20";
	clog << "Got a message: " << msg << endl;
	return PriceMsg::Parse(msg);
}
