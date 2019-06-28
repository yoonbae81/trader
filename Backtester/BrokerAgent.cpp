#include "pch.h"
#include "BrokerAgent.h"
#include "../Library/Asset.h"

using namespace std;
using namespace concurrency;

BrokerAgent::BrokerAgent() {
	double cash = 10000;
	Asset asset(cash);
	// TODO Load asset from a file or somewhere persistent
}

void BrokerAgent::run() {
	done();
}
