#pragma once

#include "../Library/Ticks.h"
#include "Parameter.h"

class Strategy {
	Parameter param;

public:
	Strategy(Parameter p);
	int CalcStrength(Ticks& ticks);
};

