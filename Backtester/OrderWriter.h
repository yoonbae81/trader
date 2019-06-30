#pragma once
#include "pch.h"
#include "../Library/Asset.h"
#include "../Library/OrderMsg.h"

using namespace std;
using namespace concurrency;

class OrderWriter : public agent {
public:
	OrderWriter(ISource<OrderMsg>& order_channel, const string& broker_endpoint);


protected:
	void run() override;

private:
	zmq::context_t ctx;

};

