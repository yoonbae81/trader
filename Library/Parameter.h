#pragma once
#include "pch.h"

using namespace std;

struct Parameter {
	Parameter();

	int threshold {};

	static Parameter Parse(const string& filepath);
};

