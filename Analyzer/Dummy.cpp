#include "pch.h"
#include "Dummy.h"
#include "../Common/Stock.h"

using namespace std;

Dummy::Dummy()
{
	clog << "Analyzer initalized" << endl;
}

Dummy::~Dummy()
{
}

int Dummy::CalcStrength(Stock stock)
{
	return 10;
}

void Dummy::UpdateStoploss(Stock stock)
{
	clog << "Updating stoploss..." << endl;
}


