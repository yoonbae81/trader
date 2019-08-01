#pragma once
#include "pch.h"
#include "Asset.h"
#include "Msg.h"
#include "Ticks.h"

using namespace std;
using namespace concurrency;
using json = nlohmann::json;

class Analyzer : public agent {
public:
	Analyzer(json& param, Asset& asset, ISource<Msg>& source, ITarget<Msg>& target);

	Analyzer(const Analyzer&) = delete;
	Analyzer(Analyzer&& src) noexcept
		: param_(src.param_)
		, asset_(src.asset_)
		, source_(src.source_)
		, target_(src.target_)
		, logger(move(src.logger)) {};

	static atomic<int> count;

protected:
	void run() override;
	int calc_strength(const Msg& msg);
	double calc_quantity(const Msg& msg);
	void update_stoploss(const Msg& msg);

	json& param_;
	Asset& asset_;
	ISource<Msg>& source_;
	ITarget<Msg>& target_;
	unordered_map<string, Ticks> ticks_map_;

	shared_ptr<spdlog::logger> logger;
};

