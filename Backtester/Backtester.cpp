#include "pch.h"
#include "../Library/Asset.h"
#include "../Library/Exceptions.h"
#include "../Library/Parameter.h"
#include "../Library/Strategy.h"

using namespace std;
using namespace concurrency;

int main() {
	clog << "Backtest started" << endl;

	double cash = 10000;
	Asset asset(cash);
	// TODO Load asset from a file or somewhere persistent
	
	string paramFile = "basicParam.txt";
	Parameter p = Parameter::Parse(paramFile);
	Strategy strategy(p);

	//string filename = "10lines.txt";
	//unique_ptr<istream> source = make_unique<ifstream>(filename);
	//if (!source.is_open()) {
	//	clog << "Couldn't open a file: " << filePath << endl;
	//	exit(1);
	//}
	//TickFetcherAgent tf(*source);

	unbounded_buffer<string> tick_buffer, signal_buffer, stoploss_buffer;


	clog << "Backtest finished" << endl;
	
	return EXIT_SUCCESS;
}

