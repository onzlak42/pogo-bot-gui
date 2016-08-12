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

  /// �������� ������� ����.
  const glm::mat4 &GetView();

  /// �������� ������� ��������.
  const glm::mat4 &GetProject();

private:

  glm::vec2 mSize;    // ������ ������� �������.
  glm::vec2 mCenter;  // ������� ������ ������� �������.

  glm::vec2 mPos;     // ������� ������� ������.

  glm::mat4 mView;
  glm::mat4 mProject;

  // �������.
  float mScale;

private:

  void CalcProject();

};



#endif // Camera2d_h__
