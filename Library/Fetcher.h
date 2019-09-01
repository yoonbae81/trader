#pragma once
#include "pch.h"
#include "Msg.h"

using namespace std;
using namespace concurrency;

class Fetcher : public agent {
public:
	Fetcher();
	virtual ~Fetcher();

	void add_target(ITarget<shared_ptr<Msg>>& target);
	ITarget<shared_ptr<Msg>>& get_target(const string& msg);

protected:
	void run() override;
	virtual bool fetch(string& line) = 0;

	unordered_map<ITarget<shared_ptr<Msg>>*, size_t> targets_;
	unordered_map<string, ITarget<shared_ptr<Msg>>*> assigned_;

	static shared_ptr<spdlog::logger> logger;
};

