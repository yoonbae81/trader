#pragma once

#include "../Library/Ticks.h"
#include "Parameter.h"

class BasicAnalyzer
{
	Parameter param;
	
public:
	BasicAnalyzer(Parameter p);
	~BasicAnalyzer();

	int CalcStrength(Ticks ticks);
	void UpdateStoploss(Ticks ticks);
	size_t GetCurrency();
};

