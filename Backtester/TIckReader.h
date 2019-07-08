#pragma once
#include "pch.h"

using namespace std;
using namespace concurrency;

class TickReader : public agent {
public:
	TickReader(const string& filepath, vector<string> analyzer_endpoints);
	
protected:
	void run() override;

private:
};

