#include "pch.h"
#include "../Library/Asset.h"
#include "../Library/Exceptions.h"
#include "../Library/TickMsg.h"
#include "../Library/SignalMsg.h"
#include "../Library/StoplossMsg.h"
#include "TickReader.h"
#include "QuantityCalculator.h"
#include "StoplossMonitor.h"
#include "OrderWriter.h"

using namespace std;
using namespace concurrency;
using json = nlohmann::json;

int main() {
	clog << "Starting Backtest..." << endl;

	auto endpoints_filename = "endpoints.json"s; // TODO get from argv
	clog << "Loading " << endpoints_filename << "..." << endl;
	json endpoints = json::parse(ifstream(endpoints_filename));
	clog << "Endpoints: " << endpoints.dump() << endl;

	int major, minor, patch = 0;
	zmq_version(&major, &minor, &patch);
	clog << "ZeroMQ version: " << major << '.' << minor << '.' << patch << '\n';

	unbounded_buffer<TickMsg> tick_buffer;
	unbounded_buffer<SignalMsg> signal_buffer;
	unbounded_buffer<StoplossMsg> stoploss_buffer;
	auto order_channel = make_unique<unbounded_buffer<OrderMsg>>();

	concurrent_unordered_map<string, Holding> holdings;
	concurrent_unordered_map<string, double> stoploss;

	TickReader tr("temp", endpoints.at("analyzers").get<vector<string>>());
	tr.start();

	QuantityCalculator qc(endpoints["broker"], *order_channel);
	qc.start();
	
	OrderWriter ow(*order_channel, "order.log");
	ow.start();

	agent::wait(&tr);
	agent::wait(&qc);
	agent::wait(&ow);

	clog << "Backtest finished" << endl;

	return EXIT_SUCCESS;
}

