#include "pch.h"
#include "TickMsg.h"
#include "Exceptions.h"

using namespace std;

TickMsg TickMsg::Parse(const string& line) {
	istringstream ss(line);
	string tokens[4];
	std::getline(ss, tokens[0], ' ');
	std::getline(ss, tokens[1], ' ');
	std::getline(ss, tokens[2], ' ');
	std::getline(ss, tokens[3], ' ');

	TickMsg msg;
	try {
		msg.symbol = tokens[0];
		msg.price = stod(tokens[1]);
		msg.volume = stoi(tokens[2]);
		msg.lastest_timestamp = stoi(tokens[3]);
	}
	catch (invalid_argument) {
		if (msg.symbol == "QUIT")
			throw QuitException();

		if (msg.symbol == "RESET")
			throw ResetException();

		throw ParsingException(line);
	}

	return msg;
}
