#pragma once
#include "pch.h"
#include "Msg.h"
#include "Holding.h"

using namespace std;
using namespace concurrency;

class Asset {
public:
	Asset(double cash);

	// TODO Load cash and holdings from a file or something 

	// TODO change following to Msg
	void bought(const Msg& m);
	void sold(const Msg& m);
	
	double total_risk() const;
	double cash() const;

	bool has(const string& symbol) const;
	Holding& operator[](const string& symbol);

private:
	atomic<double> cash_;
	concurrent_unordered_map<string, Holding> holdings_;

	static shared_ptr<spdlog::logger> logger;
};

