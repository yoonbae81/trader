#include "pch.h"

using namespace std;

int main()
{
	// Trader is integrated executable containing every modules

	clog << "yQuant Trader starting..." << endl;
	// m : an object that retrieve a price message from zmq socket
	//- parse port number and strategy name from command line arguments
	//- create zmq context and open a socket with port number given
	//	- if the port is occupied, exit with error message

	// b : an object that send an order to zmq socket and handle response from zmq socket
	// p : a structure holding property for calculation
	//MessageLoop::Run(f,b,p);
}

