#include "pch.h"
#include "BacktestFetcher.h"

using namespace std;

BacktestFetcher::BacktestFetcher(const string& filePath)
{
	clog << "Fetcher initalized" << endl;

	datafile.open(filePath);
	if (!datafile.is_open()) {
		clog << "Couldn't find datafile: " << filePath << endl;
	}
}

BacktestFetcher::~BacktestFetcher()
{
	datafile.close();
}

PriceMsg BacktestFetcher::GetMessage()
{
	string line;

	if (getline(datafile, line)) {
		clog << "Got a message: " << line << endl;
	}
	else {
		clog << "End of datafile" << endl;
		line = "QUIT";
	}

	return PriceMsg::Parse(line);

}
