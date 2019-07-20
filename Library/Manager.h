#pragma once
#include "pch.h"
#include "Msg.h"
#include "Holding.h"

using namespace std;
using namespace concurrency;

using Holdings = concurrent_unordered_map<string, Holding>;

class Manager : public agent {
public:
	Manager(ISource<Msg>& source, ITarget<Msg>& target, Holdings& holdings);

protected:
	void run() override;
	ISource<Msg>& source;
	ITarget<Msg>& target;
	Holdings& holdings;

	shared_ptr<spdlog::logger> logger;
};

