#include "pch.h"
#include "FileFetcher.h"

using namespace std;
using namespace concurrency;

FileFetcher::FileFetcher(const string& dir, ITarget<Msg>& target)
	: dir_(dir), Fetcher(target) {

	clog << "Initializing FileFetcher..." << endl;
	clog << "Opening directory: " << dir_ << endl;
	// TODO check directory exists
}

void FileFetcher::run() {
	// TODO consider load balancing
	// TODO Get file lists ends with txt
	// 
	clog << "Getting a message..." << endl;

	for (auto i = 0; i < 10; ++i) {
		concurrency::wait(10);
		// TODO Read from a file
		//unique_ptr<istream> source = make_unique<ifstream>(filepath);
		//if (!source.is_open()) {
		//	clog << "Couldn't open a file: " << filepath << endl;
		//	exit(1);
		//}

		const string line = "AAAAAA 4000 10 1234512345";

		auto msg = Msg::Parse(line);
		clog << "Sending Msg: " << line << endl;

		send(target_, msg);
	}

	done();
}

//while (true) {
//	try {
//		string line;
//		source_.getline(line);
//		if (getline(msgFile, line)) {
//			clog << "Got a message: " << line << endl;
//		} else {
//			clog << "End of file" << endl;
//			line = "QUIT";
//		}
//	} catch (ParsingException& ex) {
//		clog << "Ignored wrong message: " << ex.what() << endl;
//		continue;
//	} catch (QuitException) {
//		clog << "Quitting" << endl;
//		break;
//	}

