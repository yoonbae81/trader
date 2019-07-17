#include "pch.h"
#include "CppUnitTest.h"
#include "../Backtester/FileFetcher.h"

using namespace concurrency;
using namespace std;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

TEST_CLASS(TransformerTest) {
private:
	string dir_ = "tmp/";
	string filename_ = "test.txt";

public:
	TEST_METHOD_INITIALIZE(GenerateFile) {

		// TODO make the directory
		// TODO write a file containing ticks

		//ofstream outfile(filename);
		//Assert::IsTrue(outfile.is_open());

		//outfile << "AAAAAA 1243 10 112300201" << endl;
		//outfile << "BBBBBB 1243 20 112300202" << endl;
		//outfile.close();
	}

	TEST_METHOD(BasicTest) {
		// TODO validate whether the number of lines from files were sent to buffer

		unbounded_buffer<Msg> output;
		FileFetcher fetcher(dir_, output);
		fetcher.start();
		agent::wait(&fetcher);

		// TODO expected = lines of the file
		// TODO actual = items in buffer
		// Assert.AreEqual(expected, actual);
	}

	TEST_METHOD_CLEANUP(DeleteGeneratedFile) {
		remove(filename_.data());
	}
};