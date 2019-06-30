#pragma once
#include "pch.h"

using namespace std;
using namespace concurrency;

class SignalHandler : public agent {
public:
	SignalHandler(const string& broker_endpoint);

protected:
	void run() override;

private:
	zmq::context_t ctx_;
	zmq::socket_t signal_sock_;
};

