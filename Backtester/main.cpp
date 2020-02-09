#include "pch.h"

#include "FileFetcher.h"
#include "../Library/Analyzer.h"
#include "../Library/Asset.h"
#include "Broker.h"
#include "../Library/Ledger.h"
#include "../Library/Msg.h"
#include "../Library/Exceptions.h"

using namespace std;
using namespace std::filesystem;
using namespace concurrency;

shared_ptr<spdlog::logger> get_logger() {
	auto logger = spdlog::stdout_color_mt("main");

	// choose one below
	//spdlog::set_level(spdlog::level::critical);
	//spdlog::set_level(spdlog::level::info);
	spdlog::set_level(spdlog::level::debug);
	//spdlog::set_level(spdlog::level::trace);

	spdlog::set_pattern("%Y-%m-%d %H:%M:%S.%e %^%-8l%$ %-9n %5t | %v"); // add thread_id with %5t if necessary

	return logger;
}


int main(int argc, char* argv[]) {
	if (argc != 2) {
		cout << "usage: "
			<< path(argv[0]).filename().string()
			<< " CONFIG" << endl;

		return EXIT_FAILURE;
	}

	if (!exists(argv[1])) {
		cout << "Not found CONFIG file: " << argv[1] << endl;
		return EXIT_FAILURE;
	}

	auto logger = get_logger();
	logger->info("Starting");

	try {
		auto config = YAML::LoadFile(argv[1]);

		path input_dir(config["backtester"]["input_dir"].as<string>());
		path output_dir(config["backtester"]["output_dir"].as<string>());
		double initial_cash = config["cash"]["initial"].as<double>();

		FileFetcher fetcher(input_dir);
		Asset asset(initial_cash);

		filesystem::create_directories(output_dir);
		ofstream out(output_dir.string() + "output.jsonl");
		Ledger ledger(initial_cash, out);

		unbounded_buffer<shared_ptr<Msg>> order_channel;
		Broker broker(asset, ledger, order_channel);

		vector<Analyzer> analyzers;
		size_t num_analyzer = thread::hardware_concurrency() - 1;
		vector<unbounded_buffer<shared_ptr<Msg>>> tick_channels(num_analyzer);
		for (auto& tick_channel : tick_channels) {
			fetcher.add_target(tick_channel);
			analyzers.emplace_back(config["analyzer"], asset, tick_channel, order_channel);
		}

		fetcher.start();
		for (auto& analyzer : analyzers) analyzer.start();
		broker.start();

		// Wait Agents
		agent::wait(&fetcher);
		for (auto& analyzer : analyzers) agent::wait(&analyzer);
		agent::wait(&broker);

		this_thread::sleep_for(chrono::seconds(3));
		logger->info("Done");
		return EXIT_SUCCESS;

	} catch (exception & e) {
		logger->error(e.what());
		return EXIT_FAILURE;
	}
}

