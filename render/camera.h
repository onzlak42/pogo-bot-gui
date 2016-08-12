#pragma once
#ifndef Camera2d_h__
#define Camera2d_h__

#include <glm/glm.hpp>

class camera
{
public:
  camera(const glm::vec4 &bound);
  ~camera();

  void SetScale(float scale);

  void Scale(float scale);

  void SetPos(const glm::vec2 &pos);

  void Move(const glm::vec2 &offset);

  /// Получить матрицу вида.
  const glm::mat4 &GetView();

  /// Получить матрицу проекции.
  const glm::mat4 &GetProject();

private:

  glm::vec2 mSize;    // Размер рабочей области.
  glm::vec2 mCenter;  // Позиция центра рабочей области.

  glm::vec2 mPos;     // Текущая позиция камеры.

  glm::mat4 mView;
  glm::mat4 mProject;

  // Масштаб.
  float mScale;

private:

  void CalcProject();

};



#endif // Camera2d_h__
