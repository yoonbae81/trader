#pragma once
#include "pch.h"
#include "Msg.h"

using namespace std;
using namespace concurrency;

class Analyzer : public agent {
public:
	Analyzer(ISource<Msg>& source, ITarget<Msg>& target);

protected:
	void run() override;

private:
	ISource<Msg>& source_;
	ITarget<Msg>& target_;
};

