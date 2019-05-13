#include "pch.h"
#include "Loop.h"
#include "PriceMsg.h"

using namespace std;

/* 
template <typename FETCHER>
void Loop::Run(FETCHER& fetcher, BrokerService& broker)
{
	clog << "Loop runs" << endl;

	// while
	// try
	clog << "Getting a message..." << endl;
	PriceMsg msg = fetcher.GetMessage();

	// @todo what should be exported? account, vectors?

	// - retrieve a Stock object from unordered_map
	// - if current price is lower than stored stoploss price, then sell it
	// - compare timestamp between the recent message and the one stored in Stock object
	// 	- if time difference is more than 1 second, add price and volume, and calculate
	// 		- if the result of calculation is strong enough, make an order to broker in async thread
	// 			- to determine quantity to buy, use AccountManager to query Redis
	// 			- when the order completed, update Stock's quantity which is atom
	// 	- else update price and add volume, and skip to calculate

	// if a stock's timestamp is shorter than 1 second, skip calculating 
	//clog << "Calculating..." << endl;
	//int strength = strategy.Calculate(msg);

	//broker.Order();

// catch 
	// if an error occurred during parsing, continue the loop unless a message says QUIT
}
*/