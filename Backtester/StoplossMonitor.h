#pragma once
#include "pch.h"

using namespace std;
using namespace concurrency;

class StoplossMonitor : public agent {
public:
	StoplossMonitor() {

	}


protected:
	void run() override;

private:
	zmq::context_t ctx {};


};

