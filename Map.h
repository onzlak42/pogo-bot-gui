#pragma once
#ifndef Map_h__
#define Map_h__

#include <vector>
#include "map_loader.h"
#include "render\Render.h"
#include "sprite.h"
#include <glm/glm.hpp>
#include <map>
#include <memory>

class Map
{
public:
	Map();

	void Draw(Render &render);

	void AddPoint();

private:
	map_loader m_map_loader;

	std::map<glm::i32vec2, sprite> m_sprites;
	std::vector<glm::i32vec2> m_offsets;

	glm::i32vec2 m_map_pos;
	int32_t m_level = 17;

	std::unique_ptr<sprite> m_point;

};



#endif // Map_h__
