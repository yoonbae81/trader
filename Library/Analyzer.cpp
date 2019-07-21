#include "pch.h"
#include "Analyzer.h"

Analyzer::Analyzer(Asset& asset, ISource<Msg>& source, ITarget<Msg>& target)
	: asset_(asset)
	, source_(source)
	, target_(target) 
	, logger(spdlog::stdout_color_mt("analyzer")) {
	
	logger->debug("Initializing");
}

void Analyzer::run() {
	logger->info("Started");
	while (true) {
		auto msg = receive(source_);
		msg.signal_strength = 10;

		//if (holdingMap.contains(msg.symbol) 
		//	&& msg.bought_price <= holdingMap[msg.symbol].stoploss())
		//{
		//	std::clog << "Hits stoploss" << std::endl;
		//	// TODO Calculate quantity to sell; How will calculate the quantity?
		//	broker->Order(msg.symbol, -1);
		//}

		send(target_, msg);
	}

	done();
}
