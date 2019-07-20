#pragma once
#include "pch.h"
#include "Msg.h"

using namespace std;
using namespace concurrency;

class Fetcher : public agent {
public:
	Fetcher(ITarget<Msg>& target);

protected:
	ITarget<Msg>& target;
	shared_ptr<spdlog::logger> logger;
};

