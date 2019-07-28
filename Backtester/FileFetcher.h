#pragma once
#include "pch.h"
#include "../Library/Fetcher.h"
#include "../Library/Msg.h"

using namespace std;
using namespace std::filesystem;
using namespace concurrency;

class FileFetcher : public Fetcher {
public:
	explicit FileFetcher(const path& dir);

private:
	void run() override;

	const path& dir_;
	vector<string> files_;

};

