#include "pch.h"

#include "FileFetcher.h"
#include "../Library/Analyzer.h"
#include "../Library/Broker.h"
#include "../Library/Asset.h"
#include "../Library/Ledger.h"
#include "../Library/Msg.h"
#include "../Library/Exceptions.h"

using namespace std;
using namespace std::filesystem;
using namespace concurrency;

shared_ptr<spdlog::logger> get_logger() {
	auto logger = spdlog::stdout_color_mt("main");
	spdlog::set_level(spdlog::level::trace);
	spdlog::set_pattern("%Y-%m-%d %H:%M:%S.%e %^%-7l%$ %-9n | %v"); // add thread_id with %5t if necessary

	return logger;
}

int main(int argc, char* argv[]) {
	if (argc != 4) {
		cout << "usage: "
			<< path(argv[0]).filename().string()
			<< " TICKDATA_DIR PARAMETER_JSON INITIAL_CASH" << endl;
		return EXIT_FAILURE;
	}

	if (!exists(argv[1])) {
		cout << "Not found: " << argv[1] << endl;
		return EXIT_FAILURE;
	}

	if (!exists(argv[2])) {
		cout << "Not found: " << argv[2] << endl;
		return EXIT_FAILURE;
	}

	auto logger = get_logger();
	logger->info("Started");

	try {
		// Fetcher
		path tick_dir(argv[2]);
		FileFetcher fetcher(tick_dir);

		// Parameter
		auto param = json::parse(ifstream(argv[1]));
		logger->debug("Parameter: {}", param.dump());

		// Analyzers
		vector<Analyzer> analyzers;
		size_t num_analyzer = thread::hardware_concurrency() - 2;

		// Asset, Ledger
		Asset asset(stod(argv[3]));
		Ledger ledger("log.json");

		// Broker
		unbounded_buffer<Msg> order_channel;
		Broker broker(asset, ledger, order_channel);

		// Start Agents
		for (auto i = 0; i < num_analyzer; ++i) {
			auto tick_channel = make_shared<unbounded_buffer<Msg>>();
			fetcher.add_target(tick_channel);
			analyzers.emplace_back(param, asset, *tick_channel, order_channel);
		}

		broker.start();
		for (auto& analyzer : analyzers) analyzer.start();
		fetcher.start();

		// Wait Agents
		agent::wait(&fetcher);
		for (auto& analyzer : analyzers) agent::wait(&analyzer);
		agent::wait(&broker);

		logger->info("Done");
		return EXIT_SUCCESS;

	} catch (exception& e) {
		logger->error(e.what());
		return EXIT_FAILURE;
	}
}

