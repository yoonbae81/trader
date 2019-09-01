#include "pch.h"
#include "CppUnitTest.h"

using namespace std;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using json = nlohmann::json;

// Examples: https://github.com/nlohmann/json
TEST_CLASS(JsonTest) {
public:

	TEST_METHOD(DumpTest) {
		json sut;
		sut["Key"] = "Value";

		auto expected = "{\"Key\":\"Value\"}"s;
		auto actual = sut.dump();

		Assert::AreEqual(expected, actual);
	}

	TEST_METHOD(WriteReadTest) {
		string filename = "JsonTest.json";
		string key = "Analyzer";
		string value = "tcp://127.0.0.1:3001";

		json sut1;
		sut1[key] = value;

		ofstream output(filename);
		output << setw(4) << sut1 << endl;
		output.close();

		auto sut2 = json::parse(ifstream(filename));
		string expected = value;
		string actual = sut2[key];

		Assert::AreEqual(expected, actual);

		remove(filename.data());
	}
};
