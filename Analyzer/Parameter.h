#pragma once
#include "pch.h"

struct Parameter
{
	Parameter();
	~Parameter();

	static Parameter Parse(const std::string & filepath);
	int threshold{};
	size_t nThread = std::thread::hardware_concurrency();
};

