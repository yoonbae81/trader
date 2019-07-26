#include "pch.h"
#include "Fetcher.h"


Fetcher::Fetcher(ITarget<Msg>& target)
	: target_(target) {

	logger->debug("Initializing");
}
