#pragma once
#include "pch.h"
#include "Msg.h"

using namespace std;
using namespace concurrency;

class Fetcher : public agent {
public:
	Fetcher();
	virtual ~Fetcher();

	void add_target(shared_ptr<ITarget<Msg>> target);
	shared_ptr<ITarget<Msg>> get_target(const string& msg);

protected:
	void run() override;
	virtual bool fetch(string& line) = 0;

	unordered_map<shared_ptr<ITarget<Msg>>, size_t> targets_;
	unordered_map<string, shared_ptr<ITarget<Msg>>> assigned_;

	static shared_ptr<spdlog::logger> logger;
};

