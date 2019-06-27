#include "pch.h"
#include "../Library/Holding.h"

using namespace std;
using namespace concurrency;

int main() {
	clog << "Starting Broker..." << endl;

	concurrent_unordered_map<string, Holding> holdings;

	int major = 0;
	int minor = 0;
	int patch = 0;
	zmq_version(&major, &minor, &patch);
	clog << "ZeroMQ version: " << major << '.' << minor << '.' << patch << '\n';

	return EXIT_SUCCESS;
}

