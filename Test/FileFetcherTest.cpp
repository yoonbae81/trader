#include "pch.h"
#include "CppUnitTest.h"
#include "../Backtester/FileFetcher.h"

using namespace std;
using namespace std::filesystem;
using namespace concurrency;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

TEST_CLASS(FileFetcherTest) {
private:
	path dir_ = "temp/";
	string filename_ = "BacktesterData.txt";

public:
	TEST_METHOD_INITIALIZE(GenerateFile) {
		create_directories(dir_);

		ofstream outfile(dir_ / filename_);
		outfile << "AAAAAA 1243 10 1234512345" << endl;
		outfile << "AAAAAA 1240 20 1234512345" << endl;
		outfile << "AAAAAA 1240 30 1234512345" << endl;
		outfile << "BBBBBB 5000 30 1234512345" << endl;
		outfile.close();
	}

	TEST_METHOD(OneChannel) {
		auto channel = make_shared<unbounded_buffer<Msg>>();
		FileFetcher sut(dir_);
		sut.add_target(channel);
		sut.start();
		agent::wait(&sut);

		string line;
		ifstream infile(dir_ / filename_);
		while (getline(infile, line)) {
			auto expected = Msg::parse(line);
			auto actual = receive(*channel);
			Assert::AreEqual(expected.symbol, actual.symbol);
		}
	}

	TEST_METHOD(RouteToChannels) {
		auto channel1 = make_shared<unbounded_buffer<Msg>>();
		auto channel2 = make_shared<unbounded_buffer<Msg>>();

		FileFetcher sut(dir_);
		sut.add_target(channel1);
		sut.add_target(channel2);
		sut.start();
		agent::wait(&sut);

		auto msg = receive(*channel1);
		if (msg.symbol == "AAAAAA") {
			Assert::AreEqual(string("AAAAAA"), receive(*channel1).symbol);
			Assert::AreEqual(string("AAAAAA"), receive(*channel1).symbol);
			Assert::AreEqual(string("BBBBBB"), receive(*channel2).symbol);
		} else if (msg.symbol == "BBBBBB") {
			Assert::AreEqual(string("AAAAAA"), receive(*channel2).symbol);
			Assert::AreEqual(string("AAAAAA"), receive(*channel2).symbol);
			Assert::AreEqual(string("AAAAAA"), receive(*channel2).symbol);
		} else {
			Assert::IsTrue(false); // never should be here 
		}
	}

	TEST_METHOD_CLEANUP(DeleteGeneratedFile) {
		filesystem::remove_all(dir_);
	}
};