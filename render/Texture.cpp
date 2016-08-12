#include "Texture.h"

#include "RenderErrorChecker.h"
#include <GL/glew.h>


// Вспомогательная функция. Узнает, является ли число степенью 2.
static bool IsPow2(unsigned int a)
{
	return !(a & (a - 1));
}

Texture::Texture(const Bitmap &bitmap)
  : mTextureId(0), mSize(bitmap.GetSize())
{
  if(!mSize.x || !mSize.y || !IsPow2(mSize.x) || !IsPow2(mSize.y))
  {
    throw "invalid size";
  }

  bool smoothing = false; 
  bool mipmap = false;

  glGenTextures(1, &mTextureId);
//   if(!mTextureId)
//   {
//     throw new TextureException(TextureException::TEXTURE_NOT_CREATED);
//   }

  glBindTexture(GL_TEXTURE_2D, mTextureId);
  
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, smoothing ? GL_LINEAR : GL_NEAREST);

  if(mipmap)
  {
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, smoothing ? GL_LINEAR_MIPMAP_LINEAR : GL_NEAREST_MIPMAP_NEAREST);
  }
  else
  {
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, smoothing ? GL_LINEAR : GL_NEAREST);
  }

  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, mSize.x, mSize.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, &bitmap.GetRaw()[0]);
  RenderCheckErrors();

  if(mipmap)
  {
    glGenerateMipmap(GL_TEXTURE_2D);
    RenderCheckErrors();
  }
  
}

Texture::~Texture()
{
  glDeleteTextures(1, &mTextureId);
  RenderCheckErrors();
}

const glm::uvec2 & Texture::GetSize() const
{
  return mSize;
}

void Texture::bind()
{
  // GL_TEXTURE_BINDING_2D
  //glActiveTexture(GL_TEXTURE0 + slot);
  glBindTexture(GL_TEXTURE_2D, mTextureId);
}

