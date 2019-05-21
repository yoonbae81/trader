#include "pch.h"
#include "Exceptions.h"

ParsingException::ParsingException(const std::string& what_arg) 
	: std::runtime_error(what_arg) 
{
}

QuitException::QuitException() 
	: std::domain_error("QUIT")
{
}
 
