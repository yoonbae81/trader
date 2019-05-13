#pragma once
struct Parameter
{
	Parameter();
	~Parameter();

	static Parameter Parse();
	int threshold{};
};

