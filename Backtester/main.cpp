#include "pch.h"

#include "../Library/Analyzer.h"
#include "../Library/Manager.h"
#include "../Library/Broker.h"
#include "../Library/Asset.h"
#include "../Library/Exceptions.h"
#include "../Library/Msg.h"
#include "FileFetcher.h"

using namespace std;
using namespace concurrency;

int main(int argc, char* argv[]) {
	auto logger = spdlog::stdout_color_mt("main");
	spdlog::set_level(spdlog::level::trace);

	if (argc < 2) {
		auto exe_name = path(argv[0]).filename().string();
		cout << "usage: " << exe_name << " TICKDATA_DIR" << endl;
		return EXIT_FAILURE;
	}

	path tick_dir = argv[1];

	unbounded_buffer<Msg> tick_channel;
	unbounded_buffer<Msg> signal_channel;
	unbounded_buffer<Msg> order_channel;
	concurrent_unordered_map<string, Holding> holdings;

	try {
		logger->info("Started");

		FileFetcher fetcher(tick_dir, tick_channel);
		Analyzer analyzer(tick_channel, signal_channel);
		Manager manager(signal_channel, order_channel, holdings);
		Broker broker(order_channel, holdings);

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

