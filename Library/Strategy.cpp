#include "pch.h"
#include "Strategy.h"
#include "Parameter.h"
#include "../Library/Ticks.h"

using namespace std;

Strategy::Strategy(Parameter p) : param(p)
{
	clog << "Strategy initalized" << endl;
	clog << "Parameter: " << p.threshold << endl;
}

int Strategy::CalcStrength(Ticks& ticks)
{
	return 10;
}

