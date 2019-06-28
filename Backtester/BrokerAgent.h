#pragma once
#include "pch.h"

using namespace std;
using namespace concurrency;

class BrokerAgent : public agent {
	BrokerAgent();
	void run() override;
};

