#pragma once
#include "pch.h"
#include "Msg.h"
#include "Holding.h"

using namespace std;
using namespace concurrency;

using Holdings = concurrent_unordered_map<string, Holding>;

class Broker : public agent {
public:
	Broker(ISource<Msg>& source, Holdings& holdings);

protected:
	void run() override;

private:
	ISource<Msg>& source_;
	Holdings& holdings_;
};

