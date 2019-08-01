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
	virtual ~FileFetcher();

protected:
	virtual bool fetch(string& line);

private:
	bool load();

	const path& dir_;
	vector<path> paths_;
	vector<path>::iterator it_;
	ifstream file_;
};

