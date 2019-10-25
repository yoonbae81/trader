#include "pch.h"
#include "Msg.h"

const Msg Msg::QUIT = Msg("QUIT");
const Msg Msg::RESET = Msg("RESET");

shared_ptr<Msg> Msg::parse(const string& line) {
	string tokens[4];
	istringstream ss(line);
	getline(ss, tokens[0], ' ');
	getline(ss, tokens[1], ' ');
	getline(ss, tokens[2], ' ');
	getline(ss, tokens[3], ' ');

	//Msg msg(tokens[0]);
	auto msg = make_shared<Msg>(tokens[0]);
	try {
		msg->fetcher_price = stod(tokens[1]);
		msg->fetcher_quantity = stoi(tokens[2]);
		msg->fetcher_timestamp = stoi(tokens[3]);
	} catch (invalid_argument) {
		if (msg->symbol == "QUIT") throw QuitException();
		if (msg->symbol == "RESET") throw ResetException();
		throw ParsingException(line);
	}

	return msg;
}

Msg::~Msg() {
	//cout << "MSG DESTRUCTOR " << symbol << endl;
}


bool Msg::operator==(const Msg& rhs) {
	return this->symbol == rhs.symbol;
}

ostream& operator<<(ostream& os, const Msg& msg) {
	os << "[Msg] " << msg.symbol;
	return os;
}

