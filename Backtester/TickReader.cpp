#include "pch.h"
#include "TickReader.h"

using namespace std;
using namespace concurrency;

TickReader::TickReader(const string& filepath,
					   vector<string> analyzer_endpoints) {
	for (auto endpoint : analyzer_endpoints) {
	}

	// TODO uncommentn below
	//unique_ptr<istream> source = make_unique<ifstream>(filepath);
	//if (!source.is_open()) {
	//	clog << "Couldn't open a file: " << filepath << endl;
	//	exit(1);
	//}
}


void TickReader::run() {
	// TODO consider load balancing

	for (auto i = 0; i < 10; ++i) {
		this_thread::sleep_for(100ms);
		// TODO Read from a file
		const std::string_view msg = "AAAAAA 4000 10 1234512345";
		clog << "Sent Msg: " << msg << endl;
	}

	done();
}

//while (true) {
//	try {
//		clog << "Getting a message..." << endl;
//		string line;
//		source_.getline(line);
//		auto msg = Msg::Parse(line);

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
