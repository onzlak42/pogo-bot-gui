#pragma once

#include <glm/glm.hpp>
#include "render/Texture.h"


class sprite
{
public:
	sprite(const Bitmap &bitmap);

	const glm::uvec2 &size() const;

	void set_pos(const glm::ivec2 &pos);

	void draw();

private:
	Texture m_texture;
	glm::ivec2 m_pos;

};

