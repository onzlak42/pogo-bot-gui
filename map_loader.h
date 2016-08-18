#pragma once
#ifndef CURL_STATICLIB
#define CURL_STATICLIB
#endif

#include <stdint.h>
#include <map>
#include <glm/glm.hpp>
#include <memory>
#include <set>
#include <mutex>
#include <atomic>
#include <curl/curl.h>
#include <vector>
#include "render/Bitmap.h"

class map_loader
{
public:
	map_loader();
	~map_loader();

	std::shared_ptr<Bitmap> get(const glm::i32vec3 &pos);

private:
	std::unique_ptr<CURL, std::function<void(CURL *)>> m_curl;

	std::map<glm::i32vec3, std::shared_ptr<Bitmap>> m_tiles;
	std::set<glm::i32vec3> m_loaded;

	std::mutex m_mutex;
	std::thread m_thread;

	std::atomic<bool> m_runned = true;
private:
	std::shared_ptr<Bitmap> load(const glm::i32vec3 &pos);

};

