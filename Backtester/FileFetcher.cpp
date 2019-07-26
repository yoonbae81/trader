#include "pch.h"
#include "FileFetcher.h"

using namespace std;
using namespace std::filesystem;
using namespace std::string_literals;
using namespace concurrency;

shared_ptr<spdlog::logger> Fetcher::logger = spdlog::stdout_color_mt("fetcher");

FileFetcher::FileFetcher(const path& dir, ITarget<Msg>& target)
	: dir_(dir), Fetcher(target) {

	logger->debug("Current directory: {}", current_path().string());
	logger->debug("Finding files in {}", dir_.string());
	if (!exists(dir_)) throw runtime_error("Not exists " + dir_.string());

	for (auto& f : directory_iterator(dir_)) {
		files_.push_back(f.path().string());
		logger->trace("Found: {}", f.path().string());
	}

	logger->debug("Found: {} files", files_.size());
}

void FileFetcher::run() {
	logger->info("Started");

	sort(files_.begin(), files_.end());
	for (auto filepath : files_) {
		logger->info("Loading: {}", filepath);
		ifstream file(filepath);

		string line;
		size_t count = 0;
		while (getline(file, line)) {
			try {
				auto msg = Msg::Parse(line);
				send(target_, msg);
				count++;

				logger->trace("Sent: {}", line);

			} catch (ParsingException& e) {
				logger->warn("ParsingException: {}", e.what());
				continue;
			}
		}
		logger->info("{} ticks sent", count);
	}

	// TODO Let other agents know it's done

	done();
}

