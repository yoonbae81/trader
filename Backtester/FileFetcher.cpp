#include "pch.h"
#include "FileFetcher.h"

using namespace std;
using namespace std::filesystem;
using namespace std::string_literals;
using namespace concurrency;

shared_ptr<spdlog::logger> Fetcher::logger = spdlog::stdout_color_mt("fetcher");

FileFetcher::FileFetcher(const path& dir) : dir_(dir) {
	logger->debug("Finding *.txt files in {}/{}"
				  , current_path().string()
				  , dir_.string());
	if (!exists(dir_)) throw runtime_error("Not exists " + dir_.string());

	for (auto& f : directory_iterator(dir_)) {
		if (f.path().extension() != ".txt") continue;
		paths_.push_back(f.path());
		logger->trace("Found {}", f.path().string());
	}

	sort(paths_.begin(), paths_.end());
	logger->info("Found {} file(s) in {}", paths_.size(), dir_.string());

	it_ = paths_.begin();
	load();
}

FileFetcher::~FileFetcher() {}

bool FileFetcher::load() {
	if (it_ == paths_.end()) return false;

	file_ = ifstream(*it_);
	logger->info("Loading {}", it_->string());

	return true;
}

bool FileFetcher::fetch(string& line) {
	getline(file_, line);

	if (!file_) {
		it_++;
		return load();
	}

	return true;
}
