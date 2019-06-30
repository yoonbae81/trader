#include "pch.h"
#include "../Library/Asset.h"
#include "../Library/Exceptions.h"
#include "../Library/TickMsg.h"
#include "../Library/SignalMsg.h"
#include "../Library/StoplossMsg.h"
#include "TickReader.h"
#include "SignalHandler.h"
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

	concurrent_unordered_map<string, Holding> holdings;
	concurrent_unordered_map<string, double> stoploss;

	TickReader tick_reader("temp", endpoints.at("analyzers").get<vector<string>>());
	tick_reader.start();

	SignalHandler signal_handler(endpoints["broker"]);
	signal_handler.start();

	agent::wait(&tick_reader);
	agent::wait(&signal_handler);

	clog << "Backtest finished" << endl;

	return EXIT_SUCCESS;
}

