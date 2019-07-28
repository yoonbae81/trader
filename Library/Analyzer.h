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
	Analyzer(const json& param, Asset& asset, ISource<Msg>& source, ITarget<Msg>& target);

	Analyzer(const Analyzer&) = delete;
	Analyzer(Analyzer&& src) noexcept
		: param_(src.param_)
		, asset_(src.asset_)
		, source_(src.source_)
		, target_(src.target_)
		, logger(src.logger) {};

protected:
	void run() override;

	json param_;
	Asset& asset_;
	ISource<Msg>& source_;
	ITarget<Msg>& target_;
	unordered_map<string, Ticks> ticks_map;

	shared_ptr<spdlog::logger> logger;

	static atomic<int> id;

};

