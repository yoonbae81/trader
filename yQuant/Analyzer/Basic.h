#pragma once

#include "../Common/Stock.h"
#include "Parameter.h"

class Basic
{
	Parameter parameter;
public:
	Basic(Parameter p);
	~Basic();
	int CalcStrength(Stock stock);
	void UpdateStoploss(Stock stock);
};

