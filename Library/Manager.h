#pragma once
#include "pch.h"
#include "Asset.h"
#include "Msg.h"
#include "Holding.h"

using namespace std;
using namespace concurrency;

class Manager : public agent {
public:
	Manager(Asset& asset, ISource<Msg>& source, ITarget<Msg>& target);

protected:
	void run() override;

	Asset& asset_;
	ISource<Msg>& source_;
	ITarget<Msg>& target_;

	shared_ptr<spdlog::logger> logger;
};

