#pragma once

#include "pch.h"
#include "PriceMsg.h"

class Loop
{
public:
	template <typename FETCHER, typename ANALYZER, typename CASHER, typename BROKER>
	static void Run(FETCHER& fetcher, ANALYZER& analyzer, CASHER& casher, BROKER& broker)
	{
		std::clog << "Loop runs" << std::endl;

		// while
		// try

		std::clog << "Getting a message..." << std::endl;
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
		std::clog << "Calculating..." << std::endl;
		int strength = analyzer.CalcStrength(NULL);
		std::clog << "Strength: " << strength << std::endl;

		// if (strength >= config.threshold) 
		broker.Order();
		analyzer.UpdateStoploss(NULL);

	// catch 
		// if an error occurred during parsing, continue the loop unless a message says QUIT
	}
private:
	Loop();
};

