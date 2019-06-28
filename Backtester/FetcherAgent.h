#pragma once
#include "pch.h"

using namespace std;
using namespace concurrency;

class FetcherAgent : public agent {
	void run() override;
};

