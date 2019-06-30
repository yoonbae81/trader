#include "pch.h"
#include "../Library/Ticks.h"

#include "../Strategy/Parameter.h"
#include "../Strategy/Strategy.h"

using namespace std;
using namespace concurrency;
using json = nlohmann::json;

int main() {
	clog << "Analyzer Starting..." << endl;
	concurrent_unordered_map<string, Ticks> ticks;

	auto endpoints_filename = "endpoints.json"s; // TODO get from argv
	clog << "Loading " << endpoints_filename << "..." << endl;
	json endpoints = json::parse(ifstream(endpoints_filename));
	clog << "Endpoints: " << endpoints.dump() << endl;

	auto parameter_filename = "parameter.json"s;
	clog << "Loading " << parameter_filename << "..." << endl;
	json parameter = json::parse(ifstream(parameter_filename));
	Strategy strategy(parameter);
	clog << "Parameter: " << parameter.dump() << endl;

	clog << "ZeroMQ initalizing..." << endl;
	zmq::context_t ctx;
	int major, minor, patch = 0;
	zmq::version(&major, &minor, &patch);
	clog << "ZeroMQ version: " << major << '.' << minor << '.' << patch << '\n';

	zmq::socket_t sock_tick(ctx, zmq::socket_type::pull);
	sock_tick.bind(endpoints["analyzers"][0]);
	clog << "Listening TickMsg at " << endpoints["analyzers"][0] << endl;

	zmq::socket_t sock_signal(ctx, zmq::socket_type::push);
	sock_signal.connect(endpoints["broker"]);
	clog << "Connecting Broker at " << endpoints["broker"] << endl;

	while (true) {
		zmq::message_t buffer;
		sock_tick.recv(buffer);
		clog << "Received: " << buffer.data() << endl;

		clog << "Calculating..." << endl;
		this_thread::sleep_for(20ms);

		ostringstream out;
		out << "AAAAAA " << strategy.CalcStrength();
		sock_signal.send(zmq::buffer(out.str()), zmq::send_flags::dontwait);
		clog << "Sent: " << out.str() << endl;
	}

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

