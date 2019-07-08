#include "pch.h"
#include "../Library/Asset.h"
#include "../Library/Exceptions.h"
#include "../Library/Msg.h"
#include "TickReader.h"

using namespace std;
using namespace concurrency;

int main() {
	clog << "Starting Backtest..." << endl;


	unbounded_buffer<Msg> tick_buffer;
	//unbounded_buffer<SignalMsg> signal_buffer;
	//unbounded_buffer<StoplossMsg> stoploss_buffer;
	//auto order_channel = make_unique<unbounded_buffer<OrderMsg>>();

	concurrent_unordered_map<string, Holding> holdings;
	concurrent_unordered_map<string, double> stoploss;

	TickReader fetcher("tick/", tick_buffer);
	fetcher.start();
	
	for (auto i = 0; i < 10; i++) {
		auto msg = receive(tick_buffer);
		clog << "Received: " << msg << endl;
		//clog << "Received: " << receive(tick_buffer).symbol << endl;
	}

	agent::wait(&fetcher);
	clog << "Backtest finished" << endl;

	return EXIT_SUCCESS;
}

