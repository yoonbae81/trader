#include "pch.h"
#include "FileFetcher.h"

using namespace std;
using namespace std::filesystem;
using namespace std::string_literals;
using namespace concurrency;

FileFetcher::FileFetcher(const path& dir, ITarget<Msg>& target)
	: dir_(dir), Fetcher(target) {

	logger->debug("Current directory: {}", current_path().string());
	logger->debug("Finding files in {}", dir_.string());
	if (!exists(dir_)) throw runtime_error("Not exists " + dir_.string());

	for (auto& p : directory_iterator(dir_)) {
		files_.push_back(p.path().string());
		logger->trace("Found: {}",
					  p.path().string());
	}

	logger->debug("{} files found", files_.size());
	logger->debug("Initialized");
}

void FileFetcher::run() {
	// TODO consider load balancing

	logger->debug("Getting messages...");

	sort(files_.begin(), files_.end());
	for (auto filepath : files_) {
		logger->info("Loading: {}", filepath);
		ifstream file(filepath);

		size_t count = 0;
		string line;
		while (getline(file, line)) {
			auto msg = Msg::Parse(line);
			send(target, msg);
			logger->trace("Sent: {}", line);
			concurrency::wait(10);		// TODO delete later
			count++;
		}
		logger->debug("{} ticks sent", count);
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

