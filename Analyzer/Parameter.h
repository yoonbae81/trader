#pragma once
struct Parameter
{
	Parameter();
	~Parameter();

	static Parameter Parse(const std::string & filepath);
	int threshold{};
};

