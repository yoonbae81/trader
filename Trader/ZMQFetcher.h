#pragma once

#include "../Common/PriceMsg.h"
// #include "zmq.h"

class ZMQFetcher
{
	// zmq context
	// zmq socket
public:
	ZMQFetcher(const char* ip, int port);
	~ZMQFetcher();
	PriceMsg GetMessage();
};