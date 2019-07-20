#include "pch.h"
#include "Fetcher.h"

Fetcher::Fetcher(ITarget<Msg>& target)
	: target(target)
	, logger(spdlog::stdout_color_mt("fetcher")) {
	
	logger->debug("Initializing");
}
