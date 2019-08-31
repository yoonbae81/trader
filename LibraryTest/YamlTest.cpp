#include "pch.h"
#include "CppUnitTest.h"

using namespace std;
using namespace std::filesystem;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

// Examples: https://github.com/jbeder/yaml-cpp/wiki/Tutorial
TEST_CLASS(YamlTest) {
private:
	path dir_ = "temp/";
	string filename_ = "test.yaml";

public:
	TEST_METHOD_INITIALIZE(GenerateFile) {
		create_directories(dir_);
		ofstream outfile(dir_ / filename_);
		outfile << "key: value" << endl;
		outfile << "parent:" << endl;
		outfile << "  number: 1" << endl;
		outfile.close();
	}

	TEST_METHOD(LoadFile) {
		YAML::Node sut = YAML::LoadFile((dir_ / filename_).string());
		Assert::AreEqual(string("value"), sut["key"].as<string>());
		Assert::AreEqual(1, sut["parent"]["number"].as<int>());
	}
};
