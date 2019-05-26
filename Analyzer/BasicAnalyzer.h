#pragma once

#include "../Common/Stock.h"
#include "Parameter.h"

class BasicAnalyzer
{
	Parameter param;
public:
	BasicAnalyzer(Parameter p);
	~BasicAnalyzer();
	int CalcStrength(Stock stock);
	void UpdateStoploss(Stock stock);
	size_t GetCurrency();
};

