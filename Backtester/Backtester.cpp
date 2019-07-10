#include "pch.h"

#include "../Library/Analyzer.h"
#include "../Library/Manager.h"
#include "../Library/Broker.h"
#include "../Library/Asset.h"
#include "../Library/Exceptions.h"
#include "../Library/Msg.h"
#include "TickReader.h"

using namespace std;
using namespace concurrency;

int main() {
	clog << "Starting Backtest..." << endl;

	unbounded_buffer<Msg> tick_channel;
	unbounded_buffer<Msg> signal_channel;
	unbounded_buffer<Msg> order_channel;
	concurrent_unordered_map<string, Holding> holdings;

	TickReader fetcher("tick/", tick_channel);
	Analyzer analyzer(tick_channel, signal_channel);
	Manager manager(signal_channel, order_channel, holdings);
	Broker broker(order_channel, holdings);


	fetcher.start();
	analyzer.start();
	manager.start();
	broker.start();

	// init Manager

	agent::wait(&fetcher);
	agent::wait(&analyzer);
	agent::wait(&manager);
	agent::wait(&broker);
	clog << "Backtest finished" << endl;

	return EXIT_SUCCESS;
}

