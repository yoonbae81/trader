// pch.h: This is a precompiled header file.
// Files listed below are compiled only once, improving build performance for future builds.
// This also affects IntelliSense performance, including code completion and many code browsing features.
// However, files listed here are ALL re-compiled if any one of them is updated between builds.
// Do not add files here that you will be updating frequently as this negates the performance advantage.

#ifndef PCH_H_LIBRARY
#define PCH_H_LIBRARY

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers

//#include <cassert>
#include <algorithm>
#include <chrono>
#include <iostream>
#include <iterator>
#include <filesystem>
#include <fstream>
#include <functional>
#include <memory>
#include <sstream>
#include <string>
//#include <thread>
#include <random>
#include <vector>
#include <unordered_map>

#include <ppl.h>
#include <agents.h>
#include <concurrent_vector.h>
#include <concurrent_unordered_map.h>

#include <fmt/core.h>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <yaml-cpp/yaml.h>
//#include "ta-lib/ta_libc.h"

#endif //PCH_H_LIBRARY

