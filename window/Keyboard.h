﻿#pragma once
#ifndef Keyboard_GLFW_h__
#define Keyboard_GLFW_h__

#include <GLFW\glfw3.h>
#include <array>

class Keyboard
{
public:
  Keyboard();
  ~Keyboard();

  void SetKey(int key, int scancode, int action, int mods);

  bool IsKeyPress(int key);
  bool IsKeyUp(int key);
  bool IsKeyDown(int key);

private:
  std::array<int, GLFW_KEY_LAST + 1> mKeyState;
};


#endif // Keyboard_GLFW_h__
