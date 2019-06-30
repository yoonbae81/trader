#include "pch.h"
#include "Strategy.h"

using namespace std;
using json = nlohmann::json;


Strategy::Strategy(const json& parameter) : parameter_(parameter) {
	return;
}

int Strategy::CalcStrength() {
	return rand() % 10;
}
