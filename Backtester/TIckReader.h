#pragma once
#include "pch.h"
#include "../Library/Fetcher.h"
#include "../Library/Msg.h"

using namespace std;
using namespace concurrency;

class TickReader : public Fetcher {
public:
	explicit TickReader(const string& dir, ITarget<Msg>& target);
	
protected:
	void run() override;

};

