#pragma once
#include "pch.h"

using namespace std;
using namespace concurrency;

class FetcherAgent : public agent {
public:
	FetcherAgent(ISource<string>& stoploss_source, ITarget<string>& tick_target, ITarget<string>& signal_target);

protected:
	void run() override;

private:
	ISource<string>& stoploss_source_;
	ITarget<string>& tick_target_;
	ITarget<string>& signal_target_;
	concurrent_unordered_map<string, double> stoploss_;
};

