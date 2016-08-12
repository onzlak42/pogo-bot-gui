#include "Bitmap.h"
#include "lodepng\lodepng.h"

Bitmap::Bitmap()
{
}

Bitmap::Bitmap(const std::string &fileName)
{
  unsigned error = lodepng::decode(mData, mSize.x, mSize.y, fileName);
  if(error)
  {
    throw "error png load";
  }
}

const glm::uvec2 &Bitmap::GetSize() const
{
  return mSize;
}

const std::vector<unsigned char> &Bitmap::GetRaw() const
{
  return mData;
}
