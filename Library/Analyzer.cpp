#include "pch.h"
#include "Analyzer.h"

atomic<int> Analyzer::count = 0; // initialize static member

Analyzer::Analyzer(const json& param, const Asset& asset, ISource<Msg>& source, ITarget<Msg>& target)
	: param_(param)
	, asset_(asset)
	, source_(source)
	, target_(target)
	, logger(spdlog::stdout_color_mt("analyzer" + to_string(++count))) {

	logger->debug("Initializing");
	logger->debug("Parameter: {}", param_.dump());
}

void Analyzer::run() {
	logger->info("Running");

	while (true) {
		Msg m = receive(source_);

		if (m == Msg::QUIT) break;
		if (m == Msg::RESET) {
			ticks_map_.clear();
			continue;
		}

		logger->trace("Adding Tick...");
		auto& ticks = ticks_map_[m.symbol];
		if (!ticks.update(m)) continue;

		//if (!ticks_map_[m.symbol].update(m)) continue;

		m.analyzer_strength = calc_strength(m);
		m.analyzer_quantity = calc_quantity(m);

		logger->trace("[{}] Strength: {}", m.symbol, m.analyzer_strength);
		logger->trace("[{}] Quantity: {}", m.symbol, m.analyzer_quantity);

		if (m.analyzer_quantity) asend(target_, m);
		if (asset_.has(m.symbol)) update_stoploss(m);
	}

	asend(target_, Msg::QUIT);
	logger->debug("Done");
	done();
}

int Analyzer::calc_strength(const Msg& msg) {
	// TODO
	//if (asset_.has(m.symbol)
	//	&& m.fetcher_price < asset_[m.symbol].stoploss_price) {
	//	logger->info("[{}] below stoploss (Tick: {} < Limit: {})", m.symbol, m.fetcher_price, asset_[m.symbol].stoploss_price);
	//	m.analyzer_quantity = quantity_sell(m);
	//	return asset_[msg.symbol].quantity * -1;
	//}

	return rand() % 10;
}

double Analyzer::calc_quantity(const Msg& msg) {
	if (msg.analyzer_strength < param_["threshold"]) return 0.0;

	// TODO

	return rand() % 100;
}

void Analyzer::update_stoploss(const Msg& msg) {
	// TODO
}


