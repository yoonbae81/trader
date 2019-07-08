#pragma once
#include "pch.h"
#include "../Library/Msg.h"

using namespace std;
using namespace concurrency;

class TickReader : public agent {
public:
	explicit TickReader(const string& dir, ITarget<Msg>& target);
	
protected:
	void run() override;

private:
	ITarget<Msg>& target_;
};

