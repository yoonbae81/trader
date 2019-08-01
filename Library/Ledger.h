#pragma once
#include "pch.h"
#include "Asset.h"
#include "Msg.h"

using namespace std;
using namespace std::filesystem;
using namespace concurrency;

class Ledger : public agent {
public:
	Ledger(ISource<Msg>& source, const string& filename);
	~Ledger();

protected:
	void run() override;
	ISource<Msg>& source_;

	static shared_ptr<spdlog::logger> logger;

private:
	const string& filename_;
};

