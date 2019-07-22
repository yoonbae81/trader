#include "pch.h"

#include "FileFetcher.h"
#include "../Library/Analyzer.h"
#include "../Library/Broker.h"
#include "../Library/Asset.h"
#include "../Library/Msg.h"
#include "../Library/Exceptions.h"
#include "../Library/Strategy.h"

using namespace std;
using namespace concurrency;

shared_ptr<spdlog::logger> get_logger() {
	auto logger = spdlog::stdout_color_mt("main");
	spdlog::set_level(spdlog::level::trace);
	spdlog::set_pattern("%Y-%m-%d %H:%M:%S.%e %^%-7l%$ %-8n | %v"); // add thread_id with %-5t if necessary

	return logger;
}

int main(int argc, char* argv[]) {
	if (argc == 1) {
		auto exe_name = path(argv[0]).filename().string();
		cout << "usage: " << exe_name << " TICKDATA_DIR" << endl;
		return EXIT_FAILURE;
	}

	auto logger = get_logger();
	logger->info("Started");

	path   tick_dir = argv[1];
	double initial_cash = 100 * 10000.0;	// TODO Load initial cash from argv 
	auto parameter(json::parse(ifstream("parameter.json")));

	try {
		Asset asset(initial_cash);
		Strategy strategy(parameter);

		unbounded_buffer<Msg> tick_channel;
		unbounded_buffer<Msg> order_channel;

		FileFetcher fetcher(tick_dir, tick_channel);

		Analyzer analyzer(asset, strategy, tick_channel, order_channel); // TODO make multiple agents
		Broker broker(asset, order_channel);

		fetcher.start();
		analyzer.start();
		broker.start();

		agent::wait(&fetcher);
		agent::wait(&analyzer);
		agent::wait(&broker);

		logger->info("Done");
		return EXIT_SUCCESS;

	} catch (runtime_error& e) {
		logger->error(e.what());
		return EXIT_FAILURE;
	}
}

