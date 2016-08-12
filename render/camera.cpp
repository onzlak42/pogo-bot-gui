#include "camera.h"

#include <glm/gtc/matrix_transform.hpp>


camera::camera(const glm::vec4 &bound)
  : mSize(bound.y - bound.x, bound.w - bound.z),
    mCenter((bound.x + bound.y) / 2.0f, (bound.z + bound.w) / 2.0f),
    mPos(mCenter), 
    mView(1.0f), mProject(1.0f), mScale(1.0f)
{
  CalcProject();
}


camera::~camera()
{
}

const glm::mat4 &camera::GetView()
{
  return mView;
}

const glm::mat4 &camera::GetProject()
{
  return mProject;
}

void camera::SetScale(float scale)
{
  mScale = scale;
  CalcProject();
}

void camera::Scale(float scale)
{
  mScale += mScale * scale;
  CalcProject();
}

void camera::SetPos(const glm::vec2 &pos)
{
  mPos = pos;
  CalcProject();
}


void camera::CalcProject()
{
  mProject = glm::ortho(mPos.x - (mSize.x / 2.0f) * mScale, 
                        mPos.x + (mSize.x / 2.0f) * mScale, 
                        mPos.y - (mSize.y / 2.0f) * mScale, 
                        mPos.y + (mSize.y / 2.0f) * mScale, 
                        0.0f, 10.0f
                        );
}

void camera::Move(const glm::vec2 &offset)
{
  mPos += offset;
  CalcProject();
}
