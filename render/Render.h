#pragma once

#ifndef Render_h__
#define Render_h__

#include "Texture.h"

class Render
{
public:
  Render();

	void BeginScene();

  void SetModelMatrix(const glm::mat4 &mat);
	void SetProjectMatrix(const glm::mat4 &mat);

  void DrawQuade(const glm::vec3 &a, const glm::vec3 &b, const glm::vec3 &c, const glm::vec3 &d);

  void SetViewport(const glm::uvec2 &pos, const glm::uvec2 &size);


	void UseTexture(const Texture &texture);

};



#endif // Render_h__
