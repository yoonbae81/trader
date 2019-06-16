#pragma once
#include "pch.h"

using namespace std;

struct ParsingException : public runtime_error
{
	explicit ParsingException(const string& what_arg)
		: runtime_error(what_arg) {};
};

struct QuitException : public domain_error
{
	explicit QuitException()
		: domain_error("QUIT") {};
};

struct ResetException : public domain_error
{
	explicit ResetException()
		: domain_error("RESET") {};
};
