#include "pch.h"
#include "Manager.h"

Manager::Manager(Asset& asset, ISource<Msg>& source, ITarget<Msg>& target)
	: asset_(asset)
	, source_(source)
	, target_(target)
	, logger(spdlog::stdout_color_mt("manager")) {

	logger->debug("Initializing");
}

void Manager::run() {
	logger->info("Started");
	while (true) {
		auto msg = receive(source_);
		msg.order_quantity = rand() % 100;
		logger->trace("Quantity: {}", msg.order_quantity);
		send(target_, msg);
	}

	done();
}


