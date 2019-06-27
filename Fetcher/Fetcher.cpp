#include "pch.h"
#include "../Library/FetcherAgent.h"

using namespace std;
using namespace concurrency;

int main()
{
	cout << "Starting Fetcher..." << endl;

	//class ZmqSubSource : public source_block<multi_link_registry<ISource<string>>>;

	FetcherAgent fetcher();
}
