#pragma once
#include "pch.h"
#include "Asset.h"
#include "Msg.h"

using namespace std;
using namespace concurrency;
using json = nlohmann::json;

class Analyzer : public agent {
public:
	Analyzer(const json& parameter, Asset& asset, ISource<Msg>& source, ITarget<Msg>& target);

	Analyzer(const Analyzer&) = delete;
	Analyzer(Analyzer&& src) noexcept
		: parameter_(move(src.parameter_))
		, asset_(src.asset_)
		, source_(src.source_)
		, target_(src.target_) {};

protected:
	void run() override;

	json parameter_;
	Asset& asset_;
	ISource<Msg>& source_;
	ITarget<Msg>& target_;

	static shared_ptr<spdlog::logger> logger;
};

