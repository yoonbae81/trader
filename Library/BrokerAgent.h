#pragma once
#include "pch.h"
#include "Asset.h"

using namespace std;
using namespace concurrency;

class BrokerAgent : public agent {
public:
	BrokerAgent(ISource<string>& signal_source, ITarget<string>& stoploss_target, Asset& asset);

protected:
	void run() override;

private:
	ISource<string>& signal_source_;
	ITarget<string>& stoploss_target_;
	Asset& asset_;
};
