#ifndef TEXTURE_H
#define TEXTURE_H

#include <memory>
#include <glm/glm.hpp>
#include "Bitmap.h"

/// Текстура. Находится в видеопамяти.
class Texture
{
public:
  /// Создать текстуру на основе битмапы.
  Texture(const Bitmap &bitmap);

  /// Разрушить текстуру.
  ~Texture();

  /// Вернуть размер текстуры.
  const glm::uvec2 &GetSize() const;

  /// Установить текстуру на заданный текстурный слот.
  void bind();

private:
  // id текстуры. 0 - не существующая текстура.
  unsigned int mTextureId;

  // Размер текстуры в текстелях.
  glm::uvec2 mSize;

};


#endif // TEXTURE_H
