#include "pch.h"
#include "Analyzer.h"

Analyzer::Analyzer(const json& parameter, Asset& asset, ISource<Msg>& source, ITarget<Msg>& target)
	: parameter_(parameter)
	, asset_(asset)
	, source_(source)
	, target_(target)
	, logger(spdlog::stdout_color_mt("analyzer")) {

	logger->debug("Parameter: {}", parameter_.dump());
	logger->debug("Initializing");
}

void Analyzer::run() {
	logger->info("Started");

	while (true) {
		auto msg = receive(source_);
		msg.signal_strength = 10;

		// TODO Compare the current bought_price to calculated stoploss bought_price
		// TODO When stoploss activated, Send an Order

		//asset_.bought_price(msg.symbol);

		//if (holdingMap.contains(msg.symbol) 
		//	&& msg.bought_price <= holdingMap[msg.symbol].stoploss())
		//{
		//	std::clog << "Hits stoploss" << std::endl;
		//	// TODO Calculate quantity to sell; How will calculate the quantity?
		//	broker->Order(msg.symbol, -1);
		//}

		// TODO add ticks

//auto ticks = ticksMap[msg.symbol];
//ticks.AddTick(msg);
// TODO AddTick Msg into Ticks

// - compare timestamp between the recent message and the one stored in Ticks object
// 	- if time difference is more than 1 second, add bought_price and quantity, and calculate
// 		- if the result of calculation is strong enough, make an order to broker in async thread
// 			- to determine quantity to buy, use AccountManager to query Redis
// 			- when the order completed, update Ticks's quantity which is atom
// 	- else update bought_price and add quantity, and skip to calculate

// if a ticks's timestamp is shorter than 1 second, skip calculating 
//int strength = analyzer->CalcStrength(ticks);
//clog << "Strength: " << strength << endl;

// TODO Calculate quantity to buy
//if (strength) broker->Order(msg.symbol, 0);
// TODO holdingMap[msg.symbol].Bought(quantity, bought_price);

		// TODO calculate quantity to buy or sell based on asset
		msg.order_quantity = rand() % 100;
		logger->trace("Quantity: {}", msg.order_quantity);

		send(target_, msg);
	}

	done();
}
