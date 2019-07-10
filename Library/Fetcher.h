#pragma once
#include "pch.h"
#include "Msg.h"

using namespace std;
using namespace concurrency;

class Fetcher : public agent {
public:
	Fetcher(ITarget<Msg>& target) : target_(target) {}
	
protected:
	ITarget<Msg>& target_;


};

