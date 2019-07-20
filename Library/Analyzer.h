#pragma once
#include "pch.h"
#include "Msg.h"

using namespace std;
using namespace concurrency;

class Analyzer : public agent {
public:
	Analyzer(ISource<Msg>& source, ITarget<Msg>& target);

protected:
	void run() override;

	ISource<Msg>& source;
	ITarget<Msg>& target;

	shared_ptr<spdlog::logger> logger;
};

