#include "Render.h"

#include "RenderErrorChecker.h"
#include <GL/glew.h>
#define GLM_FORCE_RADIANS
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Render::Render(void)
{
	glewExperimental = true; // Needed in core profile

	GLenum error = glewInit();
	if (error != GLEW_OK)
	{
		throw "glew init error";
	}
	glGetError();

//  glEnable(GL_DEPTH_TEST);
//  glDepthFunc(GL_LESS);

//  glEnable(GL_CULL_FACE);
//  glCullFace(GL_BACK);

  RenderCheckErrors();

	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	glEnable(GL_TEXTURE_2D);
	glShadeModel(GL_SMOOTH);

	RenderCheckErrors();
}


void Render::SetViewport(const glm::uvec2 &pos, const glm::uvec2 &size)
{
  // Рисовать будем в эту область, заданную в экранных координатах.
  glViewport(pos.x, pos.y, size.x, size.y);
}

void Render::BeginScene()
{
	//glLoadMatrixf(glm::value_ptr(mCamera->GetProject()));

  glMatrixMode(GL_MODELVIEW);   
	glLoadIdentity();
  
  glClear(GL_COLOR_BUFFER_BIT); //GL_DEPTH_BUFFER_BIT
  glClearColor(0, 0, 0, 0);
}

void Render::UseTexture(const Texture &texture)
{

}

void Render::SetModelMatrix(const glm::mat4 &mat)
{
	GLint matrixState = 0;
	glGetIntegerv(GL_MATRIX_MODE, &matrixState);

	glMatrixMode(GL_MODELVIEW);    // Выбор матрицы проекций
	glLoadMatrixf(glm::value_ptr(mat));

	glMatrixMode(matrixState);
}

void Render::SetProjectMatrix(const glm::mat4 &mat)
{
	GLint matrixState = 0;
	glGetIntegerv(GL_MATRIX_MODE, &matrixState);

	glMatrixMode(GL_PROJECTION);    // Выбор матрицы проекций
	glLoadMatrixf(glm::value_ptr(mat));

	glMatrixMode(matrixState);
}

void Render::DrawQuade(const glm::vec3 &a, const glm::vec3 &b, const glm::vec3 &c, const glm::vec3 &d)
{
  glBegin(GL_QUADS);
    glVertex3fv(glm::value_ptr(a));
    glVertex3fv(glm::value_ptr(b));
    glVertex3fv(glm::value_ptr(c));
    glVertex3fv(glm::value_ptr(d));
  glEnd();
}




