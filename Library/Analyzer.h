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
	Analyzer(const json& param, const Asset& asset, ISource<Msg>& source, ITarget<Msg>& target);

	Analyzer(Analyzer&& src) noexcept
		: param_(src.param_)
		, asset_(src.asset_)
		, source_(src.source_)
		, target_(src.target_)
		//, ticks_map_(move(src.ticks_map_))
		, logger(src.logger) {};

	static atomic<int> count;

protected:
	void run() override;
	int calc_strength(const Msg& msg);
	double calc_quantity(const Msg& msg);
	void update_stoploss(const Msg& msg);

	const json& param_;
	const Asset& asset_;
	ISource<Msg>& source_;
	ITarget<Msg>& target_;
	unordered_map<string, Ticks> ticks_map_;
	shared_ptr<spdlog::logger> logger;
};

