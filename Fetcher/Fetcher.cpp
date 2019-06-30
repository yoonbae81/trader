#include "pch.h"

using namespace std;
using namespace concurrency;

int main() {
	cout << "Starting Fetcher..." << endl;

	int major, minor, patch = 0;
	zmq::version(&major, &minor, &patch);
	clog << "ZeroMQ version: " << major << '.' << minor << '.' << patch << '\n';

	zmq::context_t ctx;

	zmq::socket_t sock_tick(ctx, zmq::socket_type::pub);
	sock_tick.connect("tcp://127.0.0.1:3001");

	zmq::socket_t sock_stoploss(ctx, zmq::socket_type::sub);
	sock_stoploss.connect("tcp://127.0.0.1:5555");

	zmq::socket_t sock_signal(ctx, zmq::socket_type::pub);
	sock_signal.connect("tcp://127.0.0.1:9999");


	//const string_view m = "Hello, world";
	//sock.send(zmq::buffer(m), zmq::send_flags::dontwait);

	return EXIT_SUCCESS;
}


//while (true) {
//	try {
//		clog << "Getting a message..." << endl;
//		string line;
//		source_.getline(line);
//		auto msg = TickMsg::Parse(line);

//		if (getline(msgFile, line)) {
//			clog << "Got a message: " << line << endl;
//		} else {
//			clog << "End of file" << endl;
//			line = "QUIT";
//		}
		//if (holdingMap.contains(msg.symbol) 
	//	&& msg.bought_price <= holdingMap[msg.symbol].stoploss())
	//{
	//	std::clog << "Hits stoploss" << std::endl;
	//	// TODO Calculate quantity to sell; How will calculate the quantity?
	//	broker->Order(msg.symbol, -1);
	//}



//		// TODO send a message somewhere
//	} catch (ParsingException& ex) {
//		clog << "Ignored wrong message: " << ex.what() << endl;
//		continue;
//	} catch (QuitException) {
//		clog << "Quitting" << endl;
//		break;
//	}
