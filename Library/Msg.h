#pragma once

#include "pch.h"
#include "Exceptions.h"

using namespace std;

struct Msg {
	//Msg() = default;
	//Msg(Msg&& src) = default;
	//~Msg() = default;

	string symbol;

	// TODO consider nested struct
	double tick_price {};
	double tick_quantity {};
	time_t tick_timestamp {};

	int    signal_strength {};
	time_t signal_timestamp {};

	double order_price {};
	double order_quantity {};
	time_t order_timestamp {};

	double filled_price {};
	double filled_quantity {};
	time_t filled_timestamp {};

	static Msg Parse(const string& line) {
		Msg msg;
		string tokens[4];
		istringstream ss(line);

		getline(ss, tokens[0], ' ');
		getline(ss, tokens[1], ' ');
		getline(ss, tokens[2], ' ');
		getline(ss, tokens[3], ' ');

		try {
			msg.symbol = tokens[0];
			msg.tick_price = stod(tokens[1]);
			msg.tick_quantity = stoi(tokens[2]);
			msg.tick_timestamp = stoi(tokens[3]);
		} catch (invalid_argument) {
			if (msg.symbol == "QUIT") throw QuitException();
			if (msg.symbol == "RESET") throw ResetException();
			throw ParsingException(line);
		}

		return msg;
	};

	friend ostream& operator<<(ostream& os, const Msg& msg) {
		os << "[Msg] " << msg.symbol;
		return os;
	}

private:
	//Msg(const Msg&) = delete;
	//Msg& operator=(const Msg&) = delete;
	//Msg& operator=(Msg&&) = delete;
};
