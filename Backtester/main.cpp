#include "pch.h"

#include "FileFetcher.h"
#include "Analyzer.h"
#include "Broker.h"
#include "Asset.h"
#include "Ledger.h"
#include "Msg.h"
#include "Exceptions.h"

using namespace std;
using namespace std::filesystem;
using namespace concurrency;

shared_ptr<spdlog::logger> get_logger() {
	auto logger = spdlog::stdout_color_mt("main");
	//spdlog::set_level(spdlog::level::trace);
	//spdlog::set_level(spdlog::level::debug);
	spdlog::set_level(spdlog::level::critical);
	spdlog::set_pattern("%Y-%m-%d %H:%M:%S.%e %^%-8l%$ %-9n | %v"); // add thread_id with %5t if necessary

	return logger;
}

int main(int argc, char* argv[]) {
	if (argc != 4) {
		cout << "usage: "
			<< path(argv[0]).filename().string()
			<< " PARAM_JSON TICKS_DIR OUTPUT_FILE" << endl;

		return EXIT_FAILURE;
	}

	if (!exists(argv[1])) {
		cout << "Not found parameter file: " << argv[1] << endl;
		return EXIT_FAILURE;
	}

	if (!exists(argv[2])) {
		cout << "Not found directory: " << argv[2] << endl;
		return EXIT_FAILURE;
	}

	auto logger = get_logger();
	logger->info("Starting");

	try {
		auto param = json::parse(ifstream(argv[1]));
		logger->debug("Parameter {}", param.dump());

		path input_dir(argv[2]);
		path output_file(argv[3]);
		double initial_cash = param["initial_cash"];

		FileFetcher fetcher(input_dir);
		Asset asset(initial_cash);

		ofstream out(output_file);
		Ledger ledger(initial_cash, out);

		unbounded_buffer<shared_ptr<Msg>> order_channel;
		Broker broker(asset, ledger, order_channel);

		vector<Analyzer> analyzers;
		size_t num_analyzer = thread::hardware_concurrency() - 2;
		vector<unbounded_buffer<shared_ptr<Msg>>> tick_channels(num_analyzer);
		for (auto& tick_channel : tick_channels) {
			fetcher.add_target(tick_channel);
			analyzers.emplace_back(param, asset, tick_channel, order_channel);
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

