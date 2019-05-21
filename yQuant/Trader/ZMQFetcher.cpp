#include "pch.h"
#include "../Common/PriceMsg.h"
#include "ZMQFetcher.h"

using namespace std;

ZMQFetcher::ZMQFetcher(const char* ip, int port)
{
	// initalize zmq socket
}

ZMQFetcher::~ZMQFetcher()
{
	// release zmq socket
}

PriceMsg ZMQFetcher::GetMessage()
{
	// ctx.receive_string();
	string msg = "1234567890 015760 20 1 [MOCK]";
	clog << "Got a message: " << msg << endl;
	return PriceMsg::Parse(msg);
}