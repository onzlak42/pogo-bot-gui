#ifndef GAME_H
#define GAME_H

#include "bot.h"

#include <memory>
#include "render\Render.h"
#include "window\Window.h"

class App
{
public:
  App();
  ~App();

  int Run();

private:
  bool Initialize();

	glm::uvec2 size = { 512, 512};

  std::unique_ptr<Window> m_window;
	std::unique_ptr<Render> m_render;

};

#endif // GAME_H
