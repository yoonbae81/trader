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

	clog << "Backtest finished" << endl;

	return EXIT_SUCCESS;
}

