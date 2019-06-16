#include "pch.h"
#include "../Common/AssetManager.h"

using namespace std;
using namespace concurrency;

int main()
{
	// TODO Generate ZMQ context and socket
	// TODO Subscribe holdings' tick from TickFetcher

    std::cout << "Starting AssetManager\n";
	AssetManager am(1000);
	am.start();

	return EXIT_SUCCESS;
}
