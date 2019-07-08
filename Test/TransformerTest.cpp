#include "pch.h"
#include "CppUnitTest.h"

using namespace concurrency;
using namespace std;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

TEST_CLASS(TransformerTest) {
public:
	TEST_METHOD(BasicTest) {
		transformer<int, int> plus_one([](int n) {
			return n + 1;
		});

		int value = 1;
		int expected = value + 1;
		send(plus_one, value);
		int actual = receive(plus_one);

		Assert::AreEqual(expected, actual);
	}
};