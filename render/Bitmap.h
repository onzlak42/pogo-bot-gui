#ifndef BITMAP_H
#define BITMAP_H

#include <glm/glm.hpp>
#include <vector>
#include <string>


/// Битовое изображение в оперативной памяти.
class Bitmap
{
public:
  /// Создает пустую битмапу.
  Bitmap();

  /// Загружает битмапу из png файла.
  Bitmap(const std::string &fileName);

  /// Вернуть размер битмапы.
  const glm::uvec2 &GetSize() const;

  /// Вернуть данные битмапы.
  const std::vector<unsigned char> &GetRaw() const;

private:
  std::vector<unsigned char> mData;

  // Размер битмапы.
  glm::uvec2 mSize;
};

#endif // BITMAP_H
