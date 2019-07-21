#include "pch.h"

#include "FileFetcher.h"
#include "../Library/Analyzer.h"
#include "../Library/Manager.h"
#include "../Library/Broker.h"
#include "../Library/Asset.h"
#include "../Library/Msg.h"
#include "../Library/Exceptions.h"

using namespace std;
using namespace concurrency;

shared_ptr<spdlog::logger> get_logger() {
	auto logger = spdlog::stdout_color_mt("main");
	spdlog::set_level(spdlog::level::trace);
	spdlog::set_pattern("%Y-%m-%d %H:%M:%S.%e %^%-7l%$ %-8n %-5t | %v");

	return logger;
}

int main(int argc, char* argv[]) {
	if (argc == 1) {
		auto exe_name = path(argv[0]).filename().string();
		cout << "usage: " << exe_name << " TICKDATA_DIR" << endl;
		return EXIT_FAILURE;
	}

	path   tick_dir = argv[1];
	double initial_cash = 100 * 10000.0;	// TODO Load initial cash from argv 

	Asset  asset(initial_cash);
	unbounded_buffer<Msg> tick_channel;
	unbounded_buffer<Msg> signal_channel;
	unbounded_buffer<Msg> order_channel;

	auto logger = get_logger();
	try {
		logger->info("Started");

		FileFetcher fetcher(tick_dir, tick_channel);
		Analyzer analyzer(asset, tick_channel, signal_channel);
		Manager manager(asset, signal_channel, order_channel);
		Broker broker(asset, order_channel);

		fetcher.start();
		analyzer.start();
		manager.start();
		broker.start();

		agent::wait(&fetcher);
		agent::wait(&analyzer);
		agent::wait(&manager);
		agent::wait(&broker);

		logger->info("Done");
		return EXIT_SUCCESS;

	} catch (runtime_error& e) {
		logger->error(e.what());
		return EXIT_FAILURE;
	}
}

