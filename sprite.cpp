#include "sprite.h"


#include <GL/glew.h>
#include <glm/gtc/type_ptr.hpp>

sprite::sprite(const Bitmap &bitmap)
	: m_texture(bitmap)
{

}

const glm::uvec2 & sprite::size() const
{
	return m_texture.GetSize();
}

void sprite::set_pos(const glm::ivec2 &pos)
{
	m_pos = pos;
}

void sprite::draw()
{
	glm::ivec2 size = m_texture.GetSize();

	glm::vec3 a(m_pos.x - size.x / 2, m_pos.y - size.y / 2, 0);
	glm::vec3 b(m_pos.x - size.x / 2, m_pos.y + size.y / 2, 0);
	glm::vec3 c(m_pos.x + size.x / 2, m_pos.y + size.y / 2, 0);
	glm::vec3 d(m_pos.x + size.x / 2, m_pos.y - size.y / 2, 0);

	m_texture.bind();
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 1.0f); glVertex3fv(glm::value_ptr(a));
	glTexCoord2f(0.0f, 0.0f); glVertex3fv(glm::value_ptr(b));
	glTexCoord2f(1.0f, 0.0f); glVertex3fv(glm::value_ptr(c));
	glTexCoord2f(1.0f, 1.0f); glVertex3fv(glm::value_ptr(d));
	glEnd();
}

