#include "pch.h"
#include "PriceMsg.h"

using namespace std;

PriceMsg::PriceMsg(const string& symbol, double price, size_t volume, time_t timestamp) 
	: symbol(symbol), price(price), volume(volume), timestamp(timestamp) 
{
}

PriceMsg PriceMsg::Parse(const string& msg) {
	istringstream ss(msg);
	string tokens[4];

	std::getline(ss, tokens[0], ' ');
	std::getline(ss, tokens[1], ' ');
	std::getline(ss, tokens[2], ' ');
	std::getline(ss, tokens[3], ' ');

	return PriceMsg(tokens[0], stod(tokens[1]), stoi(tokens[2]), stoi(tokens[3]));
}
