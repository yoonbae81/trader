#pragma once

#include "pch.h"
#include "PriceMsg.h"
#include "Stock.h"

class Loop
{
public:
	template <typename FETCHER, typename ANALYZER, typename CASHER, typename BROKER>
	static void Run(FETCHER& fetcher, ANALYZER& analyzer, CASHER& casher, BROKER& broker)
	{
		std::unordered_map<std::string, Stock> stocks;

		std::clog << "Loop started" << std::endl;

		// while
		// try

		std::clog << "Getting a message..." << std::endl;
		PriceMsg msg = fetcher.GetMessage();	
		// could throw exception in case of QUIT message received

		// TODO override [] to Stock have symbol inside it 
		Stock stock = stocks[msg.symbol];

		// - if current price is lower than stored stoploss price, then sell it
		if (stock.quantity() && msg.price <= stock.stoploss())
		{
			std::clog << "Hits stoploss" << std::endl;
			// TODO Calculate quantity to sell;
			broker.Order();
		}

		// TODO Put PriceMsg into Stock
		
		// - compare timestamp between the recent message and the one stored in Stock object
		// 	- if time difference is more than 1 second, add price and volume, and calculate
		// 		- if the result of calculation is strong enough, make an order to broker in async thread
		// 			- to determine quantity to buy, use AccountManager to query Redis
		// 			- when the order completed, update Stock's quantity which is atom
		// 	- else update price and add volume, and skip to calculate

		// if a stock's timestamp is shorter than 1 second, skip calculating 
		std::clog << "Calculating..." << std::endl;
		int strength = analyzer.CalcStrength(stock);
		std::clog << "Strength: " << strength << std::endl;

		// TODO Calculate quantity to buy
		if (strength) broker.Order();

		std::clog << "Updating stoploss..." << std::endl;
		analyzer.UpdateStoploss(stock);

		// catch 
			// if an error occurred during parsing, continue the loop unless a message says QUIT
	}
private:
	Loop();
};

