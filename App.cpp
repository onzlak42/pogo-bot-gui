#include "App.h"

#include <thread>
#include <chrono>
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

		bot m_bot;
		map.SetPos(m_bot.pos().latitude, m_bot.pos().longitude);
		std::thread thread([&m_bot]
		{
			m_bot.run();
		});

		
		coordinate pos = m_bot.pos();
		map.AddPoint(pos.latitude, pos.longitude);
		
		float speed = 0.8f;
		while (!m_window->WindowShouldClose())
		{
			if (m_window->GetKeyboard().IsKeyDown(GLFW_KEY_PERIOD))
			{
				t_camera.Scale(0.01f);
			}
			if (m_window->GetKeyboard().IsKeyDown(GLFW_KEY_COMMA))
			{
				t_camera.Scale(-0.01f);
			}
			if (m_window->GetKeyboard().IsKeyDown(GLFW_KEY_LEFT))
			{
				t_camera.Move(glm::vec2(-speed, 0.0f));
			}
			if (m_window->GetKeyboard().IsKeyDown(GLFW_KEY_RIGHT))
			{
				t_camera.Move(glm::vec2(speed, 0.0f));
			}
			if (m_window->GetKeyboard().IsKeyDown(GLFW_KEY_DOWN))
			{
				t_camera.Move(glm::vec2(0.0f, -speed));
			}
			if (m_window->GetKeyboard().IsKeyDown(GLFW_KEY_UP))
			{
				t_camera.Move(glm::vec2(0.0f, speed));
			}

			const auto &new_pos = m_bot.pos();
			double dist = distance_earth(pos.latitude, pos.longitude, new_pos.latitude, new_pos.longitude);

			if (dist > 0.005)
			{
				pos = new_pos;
				map.SetPos(pos.latitude, pos.longitude);
				map.AddPoint(pos.latitude, pos.longitude);
			}

			m_render->SetProjectMatrix(t_camera.GetProject());
			m_render->BeginScene();
			map.Draw(*m_render);

			m_window->Update();

			std::this_thread::sleep_for(std::chrono::milliseconds(1));
		}

		m_bot.stop();
		thread.join();
	}

  Window::WindowSystemFinally();

  return 0;
}
