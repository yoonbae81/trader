#include "pch.h"
#include "BasicAnalyzer.h"
#include "Parameter.h"
#include "../Library/Ticks.h"

using namespace std;

BasicAnalyzer::BasicAnalyzer(Parameter p) : param(p)
{
	clog << "Analyzer initalized" << endl;
	clog << "Parameter: " << p.threshold << endl;
}

BasicAnalyzer::~BasicAnalyzer()
{
}

int BasicAnalyzer::CalcStrength(Ticks ticks)
{
	return 10;
}

void BasicAnalyzer::UpdateStoploss(Ticks ticks)
{

	// @todo Calculate new stoploss and AddTick into ticks
}

size_t BasicAnalyzer::GetCurrency()
{
	return param.nThread;
}
