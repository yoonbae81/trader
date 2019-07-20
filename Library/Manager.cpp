#include "pch.h"
#include "Manager.h"

Manager::Manager(ISource<Msg>& source, ITarget<Msg>& target, Holdings& holdings)
	: source(source)
	, target(target)
	, holdings(holdings)
	, logger(spdlog::stdout_color_mt("manager")) {

	logger->debug("Initializing");
	logger->debug("Initialized");

}

void Manager::run() {
	while (true) {
		auto msg = receive(source);
		msg.order_quantity = rand() % 100;
		send(target, msg);
	}

	done();
}


