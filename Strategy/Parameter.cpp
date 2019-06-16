#include "pch.h"
#include "Parameter.h"

using namespace std;

Parameter::Parameter()
{
}


Parameter::~Parameter()
{
}

Parameter Parameter::Parse(const string& filepath)
{
	Parameter p;
	p.threshold = 10;

	return p;
}
