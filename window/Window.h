// ============================================================================
// ==                   Copyright (c) 2015, Smirnov Denis                    ==
// ==                  See license.txt for more information                  ==
// ============================================================================
#ifndef WINDOW_GL_H
#define WINDOW_GL_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <memory>
#include "Keyboard.h"
#include <glm/glm.hpp>

class Window
{
public:
  Window(const glm::uvec2 &size);
  ~Window();

  /// Инициализация оконной системы.
  static void WindowSystemInitialize();

  /// Завершить работу с оконной системой.
  static void WindowSystemFinally();

  /// Установить текущий контекст для данного окна.
  void SetCurrentContext();

  /// Должно ли окно закрыться?
  bool WindowShouldClose();

  void Update();

  const glm::uvec2 &GetSize() const;

  /// Установить имя окна.
  void SetTitle(const std::string &title);

  /// Получить клавиатуру.
  Keyboard &GetKeyboard();

  GLFWwindow *Get();

private:

  struct WindowDeleter
  {
    void operator()(GLFWwindow *window) const
    {
      printf("window delete\n");
      glfwDestroyWindow(window);
    }
  };

  std::unique_ptr<GLFWwindow, WindowDeleter> mWindow;

  std::unique_ptr<Keyboard> mKeyboard;

  glm::uvec2 mSize;
};

#endif // WINDOW_GL_H
