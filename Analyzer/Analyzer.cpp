#include "pch.h"
#include "../Library/Ticks.h"

#include "../Strategy/Parameter.h"
#include "../Strategy/Strategy.h"

using namespace std;
using namespace concurrency;

int main() {
	clog << "Starting Analyzer..." << endl;
	concurrent_unordered_map<string, Ticks> ticks;

	int major, minor, patch = 0;
	zmq::version(&major, &minor, &patch);
	clog << "ZeroMQ version: " << major << '.' << minor << '.' << patch << '\n';

	zmq::context_t ctx;

	zmq::socket_t sock_tick(ctx, zmq::socket_type::sub);
	sock_tick.bind("tcp://127.0.0.1:3001");

	zmq::socket_t sock_signal(ctx, zmq::socket_type::pub);
	sock_signal.connect("tcp://127.0.0.1:9999");

	string paramFile = "basicParam.txt";
	Parameter p = Parameter::Parse(paramFile);
	Strategy strategy(p);

	clog << "Strategy initalized" << endl;
	clog << "Parameter: " << p.threshold << endl;



	// Bind a SUB socket for TickMsg
	// Bind a PUB socket for SignalMsg


	clog << "Calculating..." << endl;

	return EXIT_SUCCESS;
}

//auto ticks = ticksMap[msg.symbol];
//ticks.AddTick(msg);
// TODO AddTick TickMsg into Ticks

// - compare timestamp between the recent message and the one stored in Ticks object
// 	- if time difference is more than 1 second, add bought_price and quantity, and calculate
// 		- if the result of calculation is strong enough, make an order to broker in async thread
// 			- to determine quantity to buy, use AccountManager to query Redis
// 			- when the order completed, update Ticks's quantity which is atom
// 	- else update bought_price and add quantity, and skip to calculate

// if a ticks's timestamp is shorter than 1 second, skip calculating 
//int strength = analyzer->CalcStrength(ticks);
//clog << "Strength: " << strength << endl;

// TODO Calculate quantity to buy
//if (strength) broker->Order(msg.symbol, 0);
// TODO holdingMap[msg.symbol].Bought(quantity, bought_price);

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

//		// TODO send a message somewhere
//	} catch (ParsingException& ex) {
//		clog << "Ignored wrong message: " << ex.what() << endl;
//		continue;
//	} catch (ResetException) {
//		clog << "Data reset" << endl;
//		// TODO broker.clear();
//		continue;
//	} catch (QuitException) {
//		clog << "Quitting" << endl;
//		break;
//	}

