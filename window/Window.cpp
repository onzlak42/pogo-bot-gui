#include "Window.h"

#include <assert.h>
#include <glm/glm.hpp>

Window::Window(const glm::uvec2 &size)
  : mSize(size),
    mKeyboard(new Keyboard())
{
  GLFWmonitor *monitor = nullptr;

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_SAMPLES, 0);

  //mWindow = (decltype(mWindow))(glfwCreateWindow(mSize.x, mSize.y, "title", monitor, nullptr));

  if (!mWindow)
  {
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 1);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_ANY_PROFILE);
    glfwWindowHint(GLFW_SAMPLES, 0);

    mWindow = (decltype(mWindow))(glfwCreateWindow(mSize.x, mSize.y, "title", monitor, nullptr));
  }

  if (!mWindow)
  {
    throw "Window not created.";
  }

  /// Привязываем к glfw окну указатель на объект WindowGL.
  glfwSetWindowUserPointer(mWindow.get(), this);

  glfwSetKeyCallback(mWindow.get(), [](GLFWwindow *win, int key, int scancode, int action, int mods)
  {
    Window *window = static_cast<Window *>(glfwGetWindowUserPointer(win));
    assert(window);
    window->mKeyboard->SetKey(key, scancode, action, mods);
  });

}

Window::~Window()
{
}

void Window::WindowSystemInitialize()
{
  glfwSetErrorCallback([](int ,const char* description)
    {
      
    });

  if (glfwInit() != GL_TRUE)
  {
    throw "GLFW not initialized.";
  }
}

void Window::WindowSystemFinally()
{
  glfwTerminate();
}

void Window::SetCurrentContext()
{
  assert(mWindow);
  glfwMakeContextCurrent(mWindow.get());

  glfwSwapInterval(0);
}

bool Window::WindowShouldClose()
{
  assert(mWindow);
  return glfwWindowShouldClose(mWindow.get()) == GL_TRUE;
}

void Window::Update()
{
  assert(mWindow);
  glfwSwapBuffers(mWindow.get());

  glfwPollEvents();
}

const glm::uvec2 & Window::GetSize() const
{
  return mSize;
}

Keyboard &Window::GetKeyboard()
{
  return *mKeyboard;
}

void Window::SetTitle(const std::string &title)
{
  assert(mWindow);
  glfwSetWindowTitle(mWindow.get(), title.c_str());
}

GLFWwindow * Window::Get()
{
  return mWindow.get();
}

