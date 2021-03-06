#pragma once

// project includes
#include "json.hpp"

// memory cache size in number of files to cache (file size not inspected)
#define MEMCACHE_MAX_FILECOUNT 10

namespace Punchinello::MemoryCache {

	void Erase(std::string &);
	void Find(std::string &, nlohmann::json &);
	void Push(std::string &, nlohmann::json &);

}
