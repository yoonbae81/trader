#pragma once
#include "pch.h"

using namespace std;
using namespace concurrency;

class AnalyzerAgent : public agent {
public:
	AnalyzerAgent();
	~AnalyzerAgent();

protected:
	void run() override;

private:
};

