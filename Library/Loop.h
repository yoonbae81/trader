#pragma once

#include "pch.h"
#include "Exceptions.h"
#include "TickMsg.h"
#include "Ticks.h"

using std::string;

template <typename FETCHER, typename ANALYZER, typename BROKER>
class Loop
{
private:
	std::unordered_map<string, Ticks> ticksMap;
	//std::unordered_map<string, Holding> holdingMap;

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
				continue;
			}
			catch (ResetException) {
				std::clog << "Data reset" << std::endl;
				ticksMap.clear();
				// TODO broker.clear();
				continue;
			}
			catch (QuitException) {
				std::clog << "Quitting" << std::endl;
				break;
			}

		}
		std::clog << "Loop end" << std::endl;
	}

	void Process(TickMsg& msg) {
		//if (holdingMap.contains(msg.symbol) 
		//	&& msg.price <= holdingMap[msg.symbol].stoploss())
		//{
		//	std::clog << "Hits stoploss" << std::endl;
		//	// TODO Calculate quantity to sell; How will calculate the quantity?
		//	broker->Order(msg.symbol, -1);
		//}

		auto ticks = ticksMap[msg.symbol];
		ticks.AddTick(msg);
		// TODO AddTick TickMsg into Ticks

		// - compare lastest_timestamp between the recent message and the one stored in Ticks object
		// 	- if time difference is more than 1 second, add price and volume, and calculate
		// 		- if the result of calculation is strong enough, make an order to broker in async thread
		// 			- to determine quantity to buy, use AccountManager to query Redis
		// 			- when the order completed, update Ticks's quantity which is atom
		// 	- else update price and add volume, and skip to calculate

		// if a ticks's lastest_timestamp is shorter than 1 second, skip calculating 
		std::clog << "Calculating..." << std::endl;
		int strength = analyzer->CalcStrength(ticks);
		std::clog << "Strength: " << strength << std::endl;

		// TODO Calculate quantity to buy
		if (strength) broker->Order(msg.symbol, 0);
		// TODO holdingMap[msg.symbol].Bought(quantity, price);

		std::clog << "Updating stoploss..." << std::endl;
		analyzer->UpdateStoploss(ticks);
	}
};

