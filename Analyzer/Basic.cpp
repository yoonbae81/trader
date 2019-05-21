#include "pch.h"
#include "Basic.h"
#include "Parameter.h"
#include "../Common/Stock.h"

using namespace std;

Basic::Basic(Parameter p) : parameter(p)
{
	clog << "Analyzer initalized" << endl;
	clog << "Parameter: " << p.threshold << endl;
}

Basic::~Basic()
{
}

int Basic::CalcStrength(Stock stock)
{
	return 10;
}

void Basic::UpdateStoploss(Stock stock)
{

	// @todo Calculate new stoploss and put into stock
}
