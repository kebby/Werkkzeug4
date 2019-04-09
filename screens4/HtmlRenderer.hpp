#pragma once

#include <base/types.hpp>
#include <base/graphics.hpp>

bool RenderHtml(const sChar *url, sU32 bkcolor, bool local, sImage &dest);

class ILiveBrowser
{
public:
  virtual bool CopyToTexture(sTexture2D *&tex) = 0;
  virtual void Destroy() = 0;
protected:
  virtual ~ILiveBrowser() {}
};

ILiveBrowser *CreateLiveBrowser(const sChar *url, sInt sizeX, sInt sizeY, sU32 bkcolor, bool local);
