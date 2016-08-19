#include "map_loader.h"
#include <fstream>
#include <boost/format.hpp>
#include <boost/filesystem.hpp>
#include <chrono>

#include <curl/curl.h>

namespace std
{
	bool operator<(const glm::i32vec3 &a, const glm::i32vec3 &b) noexcept
	{
		//return a.x < b.x && a.y < b.y && a.z < b.z;
		return (a.x < b.x) || (a.x == b.x && a.y < b.y) || (a.x == b.x && a.y == b.y && a.z < b.z);
	}
}

static int curl_writer(char *data, size_t size, size_t nmemb, std::ofstream *file)
{
	int result = 0;
	file->write(data, size * nmemb);
	result = size * nmemb;
	return result;
}

map_loader::map_loader()
{
	m_curl = decltype(m_curl)(curl_easy_init(), [](CURL *curl)
	{
		if (curl) curl_easy_cleanup(curl);
	});

	if (m_curl)
	{
		curl_easy_setopt(m_curl.get(), CURLOPT_WRITEFUNCTION, curl_writer);
	}

	m_thread = std::move(std::thread([this]
	{
		while (m_runned)
		{
			glm::i32vec3 pos; 
			bool empty;
			{
				std::lock_guard<std::mutex> lock(m_mutex);
				empty = m_loaded.empty();
				if (!empty)
				{
					pos = *m_loaded.begin();
				}
			}
			if (!empty)
			{
				auto tail = load(pos);
				std::lock_guard<std::mutex> lock(m_mutex);
				m_loaded.erase(m_loaded.begin());
				m_tiles[pos] = tail;
			}
			else
			{
				std::this_thread::sleep_for(std::chrono::milliseconds(10));
			}
		}
	}));
}


map_loader::~map_loader()
{
	m_runned = false;
	m_thread.join();
}


std::shared_ptr<Bitmap> map_loader::get(const glm::i32vec3 &pos)
{
	std::lock_guard<std::mutex> lock(m_mutex);
	auto it = m_tiles.find(pos);
	if (it == m_tiles.end())
	{
		auto jt = m_loaded.find(pos);
		if (it == m_tiles.end())
		{
			m_loaded.insert(pos);
		}
		return nullptr;
	}

	return it->second;
}

std::shared_ptr<Bitmap> map_loader::load(const glm::i32vec3 &pos)
{
	std::string dir_name = (boost::format("map_data/%1%/") % pos.z).str();
	std::string file_name = (boost::format("%1%%2%_%3%.png") % dir_name % pos.x % pos.y).str();

	if (!boost::filesystem::exists(dir_name))
	{
		boost::filesystem::create_directory(dir_name);
	}

	if (!boost::filesystem::exists(file_name))
	{
		if (m_curl)
		{
			std::string url = (boost::format("http://a.tile.openstreetmap.org/%1%/%2%/%3%.png") % pos.z % pos.x % pos.y).str();
			curl_easy_setopt(m_curl.get(), CURLOPT_URL, url.c_str());
			std::ofstream file;
			file.open(file_name, std::ios::binary);
			curl_easy_setopt(m_curl.get(), CURLOPT_WRITEDATA, &file);
			CURLcode res = curl_easy_perform(m_curl.get());
			file.close();
		}
	}

	if (!boost::filesystem::exists(file_name))
	{
		return nullptr;
	}

	std::shared_ptr<Bitmap> bitmap = std::make_shared<Bitmap>(file_name);
	return bitmap;
}
