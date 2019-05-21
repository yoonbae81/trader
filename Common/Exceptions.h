#pragma once
struct ParsingException : public std::runtime_error
{
	explicit ParsingException(const std::string& what_arg);
};

struct QuitException : public std::domain_error
{
	explicit QuitException();
};
