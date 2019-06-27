#include "pch.h"
#include "BrokerAgent.h"

BrokerAgent::BrokerAgent(ISource<string>& signal_source, ITarget<string>& stoploss_target, Asset& asset)
	: signal_source_(signal_source), stoploss_target_(stoploss_target), asset_(asset) {
	clog << "Broker initalized" << endl;
}

void BrokerAgent::run() {
	clog << "Updating stoploss..." << endl;
	//analyzer->UpdateStoploss(ticks);

	// after buy
	// asset.bought
	// send stoploss msg to fetcher

	done();
}
