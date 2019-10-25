#include "pch.h"
#include "Analyzer.h"

atomic<int> Analyzer::id = 0; // initialize static member

Analyzer::Analyzer(const yaml& param, const Asset& asset, ISource<shared_ptr<Msg>>& source, ITarget<shared_ptr<Msg>>& target)
	: param_(param)
	, asset_(asset)
	, source_(source)
	, target_(target)
	, logger(spdlog::stdout_color_mt("analyzer" + to_string(++id))) {

	logger->trace("Initializing");
}
Analyzer::~Analyzer() {
	if (total_processed_msg_) {
		double average_ms = total_elapsed_ms_.count() / total_processed_msg_;
		logger->debug("Done ({} ms/msg)", average_ms);
	}
}

void Analyzer::run() {
	logger->debug("Running");

	while (true) {
		auto m = receive(source_);
		auto begin = chrono::steady_clock::now();

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
		logger->debug("Analyzed {} !{} x{}", m->symbol, m->analyzer_strength, m->analyzer_quantity);

		if (m->analyzer_quantity) {
			asend(target_, m);
		}
		if (asset_.has(m->symbol)) update_stoploss(*m);

		auto end = chrono::steady_clock::now();
		total_elapsed_ms_ += chrono::duration_cast<milliseconds> (end - begin);
		total_processed_msg_++;	// for performance measures
	}

	done();
}

int Analyzer::calc_strength(const Msg& msg) {
	// TODO
	this_thread::sleep_for(chrono::milliseconds(rand() % 30));

	return rand() % 10;
}

double Analyzer::calc_quantity(const Msg& msg) {
	if (msg.analyzer_strength < param_["threshold"].as<size_t>()) return 0;
	this_thread::sleep_for(chrono::milliseconds(rand() % 10));

	// TODO
	//if (asset_.has(m.symbol)
	//	&& m.fetcher_price < asset_[m.symbol].stoploss_price) {
	//	logger->info("[{}] below stoploss (Tick: {} < Limit: {})", m.symbol, m.fetcher_price, asset_[m.symbol].stoploss_price);
	//	m.analyzer_quantity = quantity_sell(m);
	//	return asset_[msg.symbol].quantity * -1;
	//}

	return rand() % 50;
}

void Analyzer::update_stoploss(const Msg& msg) {
	// TODO
	this_thread::sleep_for(chrono::milliseconds(rand() % 10));
}


