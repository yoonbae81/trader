#pragma once

#include "pch.h"

using namespace std;
using namespace concurrency;

class AssetManager : public agent {
public:
	AssetManager(double cash);

	double cash();

protected:
	void run() override;

private:
	overwrite_buffer<double> cash_;

};




