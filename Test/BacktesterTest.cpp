#include "pch.h"
#include "CppUnitTest.h"
#include "../Backtester/FileFetcher.h"

using namespace std;
using namespace std::filesystem;
using namespace concurrency;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

TEST_CLASS(BacktesterTest) {
private:
	path dir_ = "temp/";
	string filename_ = "BacktesterData.txt";

public:
	TEST_METHOD_INITIALIZE(GenerateFile) {
		create_directories(dir_);
		ofstream outfile(dir_ / filename_);
		Assert::IsTrue(outfile.is_open());

		outfile << "AAAAAA 1243 10 1234512345" << endl;
		outfile << "BBBBBB 5000 20 1234512345" << endl;
		outfile.close();
	}

	TEST_METHOD(FileFetcherTest) {
		// TODO validate whether the number of lines from files were sent to buffer

		unbounded_buffer<Msg> output;
		//FileFetcher fetcher(dir_, output);

		Assert::IsTrue(exists(dir_));
		//fetcher.start();
		//agent::wait(&fetcher);

		// TODO expected = lines of the file
		// TODO actual = items in buffer
		// Assert.AreEqual(expected, actual);
	}

	TEST_METHOD_CLEANUP(DeleteGeneratedFile) {
//		filesystem::remove_all(dir_);
	}
};