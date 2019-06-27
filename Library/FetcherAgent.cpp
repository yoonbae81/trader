#include "pch.h"
#include "FetcherAgent.h"
#include "Exceptions.h"
#include "TickMsg.h"

using namespace std;
using namespace concurrency;

// TODO Add ISource<string> for tick_source
FetcherAgent::FetcherAgent(ISource<string>& stoploss_source, ITarget<string>& tick_target, ITarget<string>& signal_target)
	: stoploss_source_(stoploss_source), tick_target_(tick_target), signal_target_(signal_target) {
	clog << "Fetcher initilized" << endl;

}

void FetcherAgent::run() {
	clog << "Fetching..." << endl;
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

	done();
}
