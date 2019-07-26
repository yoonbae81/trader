#pragma once
#include "pch.h"
#include "Msg.h"

using namespace std;
using namespace concurrency;

class Fetcher : public agent {
public:
	void add_target(shared_ptr<ITarget<Msg>> target);
	ITarget<Msg>& get_target(const Msg& msg);

protected:
	vector<shared_ptr<ITarget<Msg>>> targets_;
	unordered_map<string, shared_ptr<ITarget<Msg>>> assigned_;
	unordered_map<shared_ptr<ITarget<Msg>>, size_t> counts_;

	static shared_ptr<spdlog::logger> logger;
};

