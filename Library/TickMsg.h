#pragma once

#include "pch.h"
#include "Exceptions.h"

using namespace std;

struct TickMsg {
	TickMsg(TickMsg&& src) = default;
	~TickMsg() = default;

	string symbol;
	double price {};
	double quantity {};
	time_t timestamp {};

	// TODO Rename or override with << 
	const string& ToString() const {
		throw runtime_error("Not Implemented");
	};

	static TickMsg Parse(const string& line) {
		TickMsg msg;
		string tokens[4];
		istringstream ss(line);

		std::getline(ss, tokens[0], ' ');
		std::getline(ss, tokens[1], ' ');
		std::getline(ss, tokens[2], ' ');
		std::getline(ss, tokens[3], ' ');

		try {
			msg.symbol = tokens[0];
			msg.price = stod(tokens[1]);
			msg.quantity = stoi(tokens[2]);
			msg.timestamp = stoi(tokens[3]);
		} catch (invalid_argument) {
			if (msg.symbol == "QUIT") throw QuitException();
			if (msg.symbol == "RESET") throw ResetException();
			throw ParsingException(line);
		}

		return msg;
	};


private:
	TickMsg() = default;

	TickMsg(const TickMsg&) = delete;
	TickMsg& operator=(const TickMsg&) = delete;
	TickMsg& operator=(TickMsg&&) = delete;
};

