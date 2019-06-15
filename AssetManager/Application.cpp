#include "pch.h"
#include "AssetManager.h"

using namespace std;
using namespace concurrency;

int main()
{
    std::cout << "Starting AssetManager\n";
	AssetManager am(1000);
	am.start();

	return EXIT_SUCCESS;
}
