#pragma once
#include "pch.h"
#include "../Library/OrderMsg.h"

using namespace std;
using namespace concurrency;

class QuantityCalculator : public agent {
public:
	QuantityCalculator(const string& broker_endpoint,
					   ITarget<OrderMsg>& order_channel);

protected:
	void run() override;

private:
	zmq::context_t ctx_;
	zmq::socket_t signal_sock_;
	ITarget<OrderMsg>& order_channel_;
};

