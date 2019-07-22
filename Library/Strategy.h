#pragma once
#include "pch.h"

using namespace std;
using json = nlohmann::json;

class Strategy {
public:
	Strategy(const json& parameter);

	int CalcStrength();

protected:
	json parameter_;
	shared_ptr<spdlog::logger> logger;
};

