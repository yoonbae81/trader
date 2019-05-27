#include "pch.h"
#include "CppUnitTest.h"

#include "../Analyzer/Parameter.h"

using namespace std;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

TEST_CLASS(ParameterTest)
{
public:
	TEST_METHOD(Parse)
	{
		string filepath = "fake.txt";
		Parameter p = Parameter::Parse(filepath);

		Assert::AreEqual(p.threshold, 10);
	}
};
