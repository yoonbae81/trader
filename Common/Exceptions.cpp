#include "pch.h"
#include "Exceptions.h"

using namespace std;

ParsingException::ParsingException(const string& what_arg)
	: runtime_error(what_arg) {}

QuitException::QuitException()
	: domain_error("QUIT") {}

ResetException::ResetException()
	: domain_error("RESET") {}
