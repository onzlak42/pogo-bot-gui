#include "App.h"

#include "Map.h"
#include "render\camera.h"


App::App()
{
}

App::~App()
{

}

bool App::Initialize()
{
  Window::WindowSystemInitialize();

  try
  {
		m_window = std::move(std::make_unique<Window>(size));
		m_window->SetCurrentContext();
		m_render = std::move(std::make_unique<Render>());
	}
  catch (char *)
  {
    return false;
  }

  return true;
}


int App::Run()
{
  if(!Initialize())
  {
    return 0;
  }

	{
		camera t_camera(glm::vec4(0, size.x, 0, size.y));
		t_camera.Move({ -static_cast<int32_t>(size.x) / 2, -static_cast<int32_t>(size.y) / 2 });
		t_camera.SetScale(3.0f);
		Map map;

		while (!m_window->WindowShouldClose())
		{
			if (m_window->GetKeyboard().IsKeyDown(GLFW_KEY_PERIOD))
			{
				t_camera.Scale(0.001f);
			}
			if (m_window->GetKeyboard().IsKeyDown(GLFW_KEY_COMMA))
			{
				t_camera.Scale(-0.001f);
			}
			if (m_window->GetKeyboard().IsKeyDown(GLFW_KEY_LEFT))
			{
				t_camera.Move(glm::vec2(-0.1f, 0.0f));
			}
			if (m_window->GetKeyboard().IsKeyDown(GLFW_KEY_RIGHT))
			{
				t_camera.Move(glm::vec2(0.1f, 0.0f));
			}
			if (m_window->GetKeyboard().IsKeyDown(GLFW_KEY_DOWN))
			{
				t_camera.Move(glm::vec2(0.0f, -0.1f));
			}
			if (m_window->GetKeyboard().IsKeyDown(GLFW_KEY_UP))
			{
				t_camera.Move(glm::vec2(0.0f, 0.1f));
			}

			m_render->SetProjectMatrix(t_camera.GetProject());
			m_render->BeginScene();
			map.Draw(*m_render);

			m_window->Update();
		}
	}

  Window::WindowSystemFinally();

  return 0;
}
