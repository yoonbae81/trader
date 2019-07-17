#pragma once
#include "pch.h"
#include "../Library/Fetcher.h"
#include "../Library/Msg.h"

using namespace std;
using namespace concurrency;

class FileFetcher : public Fetcher {
public:
	explicit FileFetcher(const string& dir, ITarget<Msg>& target);
	
protected:
	void run() override;

private:
	const string dir_;
};

