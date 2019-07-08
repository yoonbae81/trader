#pragma once

#include "pch.h"
#include "Exceptions.h"

using namespace std;

struct Msg {
	//Msg() = default;
	//Msg(Msg&& src) = default;
	//~Msg() = default;

	string symbol;
	double price {};
	double quantity {};
	time_t timestamp {};

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

	friend ostream& operator<<(ostream& os, const Msg& msg) {
		os << "[Msg] " << msg.symbol << " : " << msg.price << " x " << msg.quantity;
		return os;
	}

private:
	//Msg(const Msg&) = delete;
	//Msg& operator=(const Msg&) = delete;
	//Msg& operator=(Msg&&) = delete;
};
