#pragma once

#include <base/types.hpp>
#include <base/graphics.hpp>

bool RenderHtml(const sChar *url, sU32 bkcolor, bool local, sImage &dest);

class ILiveBrowser
{
public:
  virtual sMaterial * GetFrame(sFRect &uvrect) = 0;
  virtual sF32 GetAspect() = 0;
  virtual bool HasError() = 0;
  virtual void Release() = 0;
protected:
  virtual ~ILiveBrowser() {}
};

ILiveBrowser *CreateLiveBrowser(const sChar *url, sInt sizeX, sInt sizeY, sU32 bkcolor, bool local);
