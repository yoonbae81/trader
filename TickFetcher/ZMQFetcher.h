#pragma once

#include "../Library/TickMsg.h"
// #include "zmq.h"

class ZMQFetcher
{
	// zmq context
	// zmq socket
public:
	ZMQFetcher(const char* ip, int port);
	~ZMQFetcher();
	TickMsg GetMessage();
};