#include "Map.h"
#include <stdlib.h>

#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GL/glew.h>
#include "util.h"
#include <iostream>
#include "config.h"

namespace std
{
	bool operator<(const glm::i32vec2 &a, const glm::i32vec2 &b) noexcept
	{
		return (a.x < b.x) || (a.x == b.x && a.y < b.y);
	}
}

Map::Map()
{
	int32_t radius = 2;
	for (int32_t x = -radius; x <= radius; ++x)
		for (int32_t y = -radius; y <= radius; ++y)
		{
			m_offsets.emplace_back(x, y);
		}
}

void Map::Draw(Render &render)
{
	int level = 15;
	auto x = long2tilex(config::pos.lon, level);
	auto y = lat2tiley(config::pos.lat, level);
	for (auto i : m_offsets)
	{
		auto it = m_sprites.find(i);
		if (it == m_sprites.end())
		{
			auto bitmap = m_map_loader.get({ i.x + x, i.y + y, level });
			if (bitmap)
			{
				it = m_sprites.emplace(i, *bitmap).first;
			}
		}

	  if (it != m_sprites.end())
		{
			i.y = -i.y;
			(*it).second.set_pos(i * 256);
			(*it).second.draw();
		}
	}
}


