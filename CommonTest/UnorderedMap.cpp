#include "pch.h"
#include "CppUnitTest.h"

#include "../Common/Stock.h"

using namespace std;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CommonTest
{
	TEST_CLASS(UnorderedTest)
	{
	private:
		unordered_map<string, Stock> map;
		
	public:
		TEST_METHOD_INITIALIZE(Retrieve)
		{

		}
		
		TEST_METHOD(Retrieve)
		{
		}

	};
}
