#pragma once
#include "pch.h"
#include "Asset.h"
#include "Msg.h"

using namespace std;
using namespace concurrency;

class Broker : public agent {
public:
	Broker(Asset& asset, ISource<Msg>& source);

protected:
	void run() override;

	Asset& asset_;
	ISource<Msg>& source_;

	shared_ptr<spdlog::logger> logger;
};

