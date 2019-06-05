#include "pch.h"
#include "BacktestFetcher.h"

using namespace std;

BacktestFetcher::BacktestFetcher(const string& filePath)
	: msgFile(filePath)
{
	clog << "Fetcher initalizing..." << endl;

	if (!msgFile.is_open()) {
		clog << "Couldn't open a file: " << filePath << endl;
		exit(1);
	}

	clog << "Fetcher initalized" << endl;
}

BacktestFetcher::~BacktestFetcher()
{
	msgFile.close();
}

TickMsg BacktestFetcher::GetMessage()
{
	string line;

	if (getline(msgFile, line)) {
		clog << "Got a message: " << line << endl;
	}
	else {
		clog << "End of file" << endl;
		line = "QUIT";
	}

	return TickMsg::Parse(line);
}
