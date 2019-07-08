#include "pch.h"
#include "CppUnitTest.h"

using namespace std;
using namespace concurrency;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

TEST_CLASS(TransformerTest) {
public:
	TEST_METHOD(BasicTest) {
		transformer<int> plus_one([](int n) {
			return n + 1;
		});

		auto value = 1;
		auto expected = value + 1;
		send(plus_one, value);
		auto actual = receive(plus_one);

		Assert::AreEquals(expected, actual);
	}
};