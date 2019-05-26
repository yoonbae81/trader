#pragma once

#include "pch.h"
#include "Exceptions.h"
#include "PriceMsg.h"
#include "Stock.h"

template <typename FETCHER, typename ANALYZER, typename BROKER>
class Loop
{
private:
	std::unordered_map<std::string, Stock> map;

public:
	FETCHER* fetcher = nullptr;
	ANALYZER* analyzer = nullptr;
	BROKER* broker = nullptr;

	void Run()
	{
		std::clog << "Loop started" << std::endl;

		while (true) {
			try {
				std::clog << "Getting a message..." << std::endl;
				auto msg = fetcher->GetMessage();
				Process(msg);
			}
			catch (ParsingException& ex) {
				std::clog << "Ignored wrong message: " << ex.what() << std::endl;
			}
			catch (ResetException) {
				std::clog << "Data reset" << std::endl;
				map.clear();
				// TODO broker.clear();
			}
			catch (QuitException) {
				std::clog << "Quitting" << std::endl;
				break;
			}

		}
		std::clog << "Loop end" << std::endl;
	}

	void Process(PriceMsg& msg) {
		// TODO override [] to Stock have symbol inside it 
		//Stock stock = stocks[msg.symbol];
		std::string symbol = "AAA";
		auto stock = Stock(symbol);
		

		// - if current price is lower than stored stoploss price, then sell it
		if (stock.quantity() && msg.price <= stock.stoploss())
		{
			std::clog << "Hits stoploss" << std::endl;
			// TODO Calculate quantity to sell;
			broker->Order(msg.symbol, 0);
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
		int strength = analyzer->CalcStrength(stock);
		std::clog << "Strength: " << strength << std::endl;

		// TODO Calculate quantity to buy
		if (strength) broker->Order(msg.symbol, 0);

		std::clog << "Updating stoploss..." << std::endl;
		analyzer->UpdateStoploss(stock);
	}
};

