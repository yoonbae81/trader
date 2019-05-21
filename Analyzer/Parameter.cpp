#include "pch.h"
#include "Parameter.h"


Parameter::Parameter()
{
}


Parameter::~Parameter()
{
}

Parameter Parameter::Parse()
{
	Parameter p;
	p.threshold = 10;
	return p;
}
