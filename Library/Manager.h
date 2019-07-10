#pragma once
#include "pch.h"
#include "Msg.h"
#include "Holding.h"

using namespace std;
using namespace concurrency;

using Holdings = concurrent_unordered_map<string, Holding>;

class Manager : public agent {
public:
	Manager(ISource<Msg>& source, ITarget<Msg>& target, Holdings& holdings);

protected:
	void run() override;

private:
	ISource<Msg>& source_;
	ITarget<Msg>& target_;
	Holdings& holdings_;

};

