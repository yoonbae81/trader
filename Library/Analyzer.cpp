#include "pch.h"
#include "Analyzer.h"

atomic<int> Analyzer::count = 0; // initialize static member

Analyzer::Analyzer(const yaml& param, const Asset& asset, ISource<shared_ptr<Msg>>& source, ITarget<shared_ptr<Msg>>& target)
	: param_(param)
	, asset_(asset)
	, source_(source)
	, target_(target)
	, logger(spdlog::stdout_color_mt("analyzer" + to_string(++count))) {

	logger->trace("Initializing");
}
Analyzer::~Analyzer() {
	logger->trace("Done");
}

void Analyzer::run() {
	logger->debug("Running");

	while (true) {
		auto m = receive(source_);

		if (*m == Msg::QUIT) {
			asend(target_, m);
			break;
		}
		if (*m == Msg::RESET) {
			ticks_map_.clear();
			continue;
		}

		auto& ticks = ticks_map_[m->symbol];
		if (!ticks.update(*m)) continue;
		logger->trace("Added {} {} tick(s)", m->symbol, ticks.prices.size());

		m->analyzer_strength = calc_strength(*m);
		m->analyzer_quantity = calc_quantity(*m);

		logger->trace("Analyzed {} !{} x{}", m->symbol, m->analyzer_strength, m->analyzer_quantity);

		if (m->analyzer_quantity) {
			asend(target_, m);
			logger->debug("Sent {} !{} x{}", m->symbol, m->analyzer_strength, m->analyzer_quantity);
		}
		if (asset_.has(m->symbol)) update_stoploss(*m);
	}

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
	if (msg.analyzer_strength < param_["threshold"].as<int>()) return 0.0;

	// TODO

	return rand() % 50;
}

void Analyzer::update_stoploss(const Msg& msg) {
	// TODO
}


