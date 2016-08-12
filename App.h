#ifndef GAME_H
#define GAME_H

#ifndef STL_MSVC
#define STL_MSVC
#endif
#ifndef _TIMESPEC_DEFINED
#define _TIMESPEC_DEFINED
#endif
#ifndef CURL_STATICLIB
#define CURL_STATICLIB
#endif
#ifndef _SCL_SECURE_NO_WARNINGS
#define _SCL_SECURE_NO_WARNINGS
#endif

#pragma comment( lib, "Ws2_32.lib" )
#pragma comment( lib, "WLDAP32.lib" )
#pragma comment( lib, "ssleay32.lib" )
#pragma comment( lib, "libeay32.lib" )
#pragma comment( lib, "libcurld.lib" )

#include "window\Window.h"
#include "render\Render.h"
#include <memory>

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
