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

	m_point = std::move(std::make_unique<sprite>(Bitmap("data/point.png")));
}

void Map::Draw(Render &render)
{
	glm::i32vec2 map_pos(long2tilex(config::pos.lon, m_level), lat2tiley(config::pos.lat, m_level));
	if (m_map_pos != map_pos)
	{
		m_sprites.clear();
		m_map_pos = map_pos;
	}

	for (auto i : m_offsets)
	{
		auto it = m_sprites.find(i);
		if (it == m_sprites.end())
		{
			auto bitmap = m_map_loader.get({ i.x + m_map_pos.x, i.y + m_map_pos.y, m_level });
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

	AddPoint();
}

void Map::AddPoint()
{
	glm::i32vec2 pos_map(long2tilex(config::pos.lon, m_level), lat2tiley(config::pos.lat, m_level));
	glm::i32vec2 pos_tile(long2tilexd(config::pos.lon, m_level), lat2tileyd(config::pos.lat, m_level));
	pos_tile -= 128;

	glm::i32vec2 offset = (m_map_pos - pos_map);

	glm::i32vec2 pos(pos_tile + offset);
	pos.y = -pos.y;
	m_point->set_pos(pos);
	m_point->draw();
}

