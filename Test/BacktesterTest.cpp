#include "pch.h"
#include "CppUnitTest.h"

#include "../Library/Exceptions.h"

using namespace std;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

TEST_CLASS(BacktestFetcherTest) {
	string filename = "temp.txt";

public:
	TEST_METHOD_INITIALIZE(GenerateFile) {
		//ofstream outfile(filename);
		//Assert::IsTrue(outfile.is_open());

		//outfile << "AAAAAA 1243 10 112300201" << endl;
		//outfile << "BBBBBB 1243 20 112300202" << endl;
		//outfile.close();
	}

	TEST_METHOD(ReadMessages) {
		//BacktestFetcher fetcher(filename);

		//Assert::AreEqual(string("AAAAAA"), fetcher.GetMessage().symbol);
		//Assert::AreEqual(string("BBBBBB"), fetcher.GetMessage().symbol);

		// no more message
		//try { auto m = fetcher.GetMessage(); }
		//catch (QuitException) { Assert::IsTrue(true); }
	}

	TEST_METHOD_CLEANUP(DeleteFile) {
		remove(filename.data());
	}
};
