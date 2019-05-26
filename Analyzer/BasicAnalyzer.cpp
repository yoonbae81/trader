#include "pch.h"
#include "BasicAnalyzer.h"
#include "Parameter.h"
#include "../Common/Stock.h"

using namespace std;

BasicAnalyzer::BasicAnalyzer(Parameter p) : param(p)
{
	clog << "Analyzer initalized" << endl;
	clog << "Parameter: " << p.threshold << endl;
}

BasicAnalyzer::~BasicAnalyzer()
{
}

int BasicAnalyzer::CalcStrength(Stock stock)
{
	return 10;
}

void BasicAnalyzer::UpdateStoploss(Stock stock)
{

	// @todo Calculate new stoploss and put into stock
}

size_t BasicAnalyzer::GetCurrency()
{
	return param.nThread;
}
