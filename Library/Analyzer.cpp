#include "pch.h"
#include "Analyzer.h"

Analyzer::Analyzer(ISource<Msg>& source, ITarget<Msg>& target)
	: source(source)
	, target(target) 
	, logger(spdlog::stdout_color_mt("analyzer")) {
	
	logger->debug("Initializing");
	logger->debug("Initialized");

}

void Analyzer::run() {
	while (true) {
		auto msg = receive(source);
		msg.signal_strength = 10;

		//if (holdingMap.contains(msg.symbol) 
		//	&& msg.bought_price <= holdingMap[msg.symbol].stoploss())
		//{
		//	std::clog << "Hits stoploss" << std::endl;
		//	// TODO Calculate quantity to sell; How will calculate the quantity?
		//	broker->Order(msg.symbol, -1);
		//}

		send(target, msg);
	}

	done();
}
