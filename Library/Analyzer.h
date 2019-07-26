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

protected:
	void run() override;

	json parameter_;
	Asset& asset_;
	ISource<Msg>& source_;
	ITarget<Msg>& target_;
	static shared_ptr<spdlog::logger> logger;
};

