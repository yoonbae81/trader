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
		outfile << "AAAAAA 1243 10 1234512345" << endl;
		outfile << "BBBBBB 5000 20 1234512345" << endl;
		outfile << "CCCCCC 1000 20 1234512345" << endl;
		outfile.close();
	}

	TEST_METHOD(FileFetcherTest) {
		unbounded_buffer<Msg> output;
		FileFetcher sut(dir_, output);
		sut.start();
		agent::wait(&sut);

		string line;
		ifstream infile(dir_ / filename_);
		while (getline(infile, line)) {
			auto expected = Msg::Parse(line);
			auto actual = receive(output);
			Assert::AreEqual(expected.symbol, actual.symbol);
		}
	}

	TEST_METHOD_CLEANUP(DeleteGeneratedFile) {
		filesystem::remove_all(dir_);
	}
};