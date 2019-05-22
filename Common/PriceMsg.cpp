#include "pch.h"
#include "PriceMsg.h"
#include "Exceptions.h"

using namespace std;

PriceMsg PriceMsg::Parse(const string& line) {
	istringstream ss(line);
	string tokens[4];
	std::getline(ss, tokens[0], ' ');
	std::getline(ss, tokens[1], ' ');
	std::getline(ss, tokens[2], ' ');
	std::getline(ss, tokens[3], ' ');

	PriceMsg msg;
	try {
		msg.symbol = tokens[0];
		msg.price = stod(tokens[1]);
		msg.volume = stoi(tokens[2]);
		msg.timestamp = stoi(tokens[3]);
	}
	catch (invalid_argument) {
		if (msg.symbol == "QUIT")
			throw QuitException();

		throw ParsingException(line);
	}

	return msg;
}
