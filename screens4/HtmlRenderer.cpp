/*+**************************************************************************/
/***                                                                      ***/
/***   This file is distributed under a BSD license.                      ***/
/***   See LICENSE.txt for details.                                       ***/
/***                                                                      ***/
/**************************************************************************+*/

/****************************************************************************/
/***                                                                      ***/
/***   (C) 2019 Tammo Hinrichs, all rights reserved                       ***/
/***                                                                      ***/
/****************************************************************************/

#include "util/image.hpp"

#include "include/cef_base.h"
#include "include/cef_app.h"
#include "include/cef_client.h"
#include "include/wrapper/cef_helpers.h"

extern HWND sHWND;

#include "HtmlRenderer.hpp"

#pragma comment (lib, "cef/Release/libcef.lib")

class MyCefApp : public CefApp
{
public:

  void OnBeforeCommandLineProcessing(const CefString& process_type, CefRefPtr<CefCommandLine> command_line) override
  {
    //command_line->AppendSwitch("--single-process");
    command_line->AppendSwitch("--disable-lcd-text"); // no ClearType, kthx
    command_line->AppendSwitch("--enable-gpu"); 
  }

  IMPLEMENT_REFCOUNTING(MyCefApp);
};


void InitCef()
{
  auto hInstance = GetModuleHandle(0);
  CefMainArgs main_args(hInstance);
  CefRefPtr<MyCefApp> app = new MyCefApp;

  // child processes: undo COM init, run CEF alone
  if (sFindString(sGetCommandLine(), L"--type") > 0)
  {
    CoUninitialize();
    int exitcode = CefExecuteProcess(main_args, app, 0);
    ExitProcess(exitcode);
  }

  sChar mfn[2048];
  GetModuleFileName(hInstance, mfn, 2048);

  sString<2048> exepath;
  sExtractPath(mfn, exepath);

  sString<1024> dir;
  sGetCurrentDir(dir);

  dir = L"C:\\code\\fr_public\\altona_wz4\\altona\\examples\\_graphics\\cube";

  dir.AddPath(L"cef\\resources");
  auto dir2 = dir;
  dir2.AddPath(L"locales");

  CefSettings settings;
  settings.windowless_rendering_enabled = true;
  settings.multi_threaded_message_loop = true;
  settings.no_sandbox = true;
  CefString(&settings.resources_dir_path) = dir;
  CefString(&settings.locales_dir_path) = dir2;

  CefInitialize(main_args, settings, app, 0);
}

void ExitCef()
{
  CefShutdown();
}

sADDSUBSYSTEM(CEF, 0x08, InitCef, ExitCef);

/****************************************************************************/
/****************************************************************************/

struct OfflineClient : 
  public CefClient,
  public CefLifeSpanHandler,
  public CefLoadHandler,
  public CefRenderHandler
{
  OfflineClient(sImage &img) : Image(img) {}
  virtual ~OfflineClient() {}

  bool Render(const sChar *url, sU32 bkcolor, bool local)
  {
    CefWindowInfo winfo;
    winfo.SetAsWindowless(sHWND);

    CefBrowserSettings settings;
    if (local)
    {
      settings.web_security = cef_state_t::STATE_DISABLED;
      settings.universal_access_from_file_urls = cef_state_t::STATE_ENABLED;
    }
    settings.background_color = bkcolor;
    settings.windowless_frame_rate = 60;

    if (!CefBrowserHost::CreateBrowser(winfo, this, url, settings, 0))
      return false;

    if (!PaintEvent.Wait(5000))
    {
      sDPrintF(L"HtmlRenderer: render timeout for %s", url);
    }
    Browser->GetHost()->CloseBrowser(true);    
    Browser = 0;
    return Error;
  }

  // CefClient methods
  virtual CefRefPtr<CefLifeSpanHandler> GetLifeSpanHandler() override { return this; }
  virtual CefRefPtr<CefLoadHandler> GetLoadHandler() override { return this; }
  virtual CefRefPtr<CefRenderHandler> GetRenderHandler() override { return this; }

  // CefLifeSpanHandler methods
  void OnAfterCreated(CefRefPtr<CefBrowser> browser) override {
    CEF_REQUIRE_UI_THREAD();
    Browser = browser;
  }

  // CefLoadHandler methods
  void OnLoadEnd(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, int httpStatusCode) override
  {
    if (frame->IsMain())
    {
      LoadDone = true;
      Browser->GetHost()->Invalidate(PET_VIEW);
    }
  }

  void OnLoadError(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, ErrorCode errorCode, const CefString& errorText, const CefString& failedUrl) override {
    CEF_REQUIRE_UI_THREAD();
    Error = true;
    PaintEvent.Signal();
  }

  // CefRenderHandler methods
  void GetViewRect(CefRefPtr<CefBrowser> browser, CefRect& rect) override
  {
    rect.Set(0, 0, Image.SizeX, Image.SizeY);
  }

  void OnPaint(CefRefPtr<CefBrowser> browser, PaintElementType type, const RectList& dirtyRects, const void* buffer, int width, int height) override
  {
    sCopyMem(Image.Data, buffer, 4 * width*height);
    if (LoadDone && type==PET_VIEW)
      PaintEvent.Signal();
  }

  bool Error = false;
  bool LoadDone = false;
  sImage &Image;
  sThreadEvent PaintEvent;
  CefRefPtr<CefBrowser> Browser;

  IMPLEMENT_REFCOUNTING(OfflineClient);
};

bool RenderHtml(const sChar *url, sU32 bkcolor, bool local, sImage &dest)
{
  CefRefPtr<OfflineClient> client = new OfflineClient(dest);
  return client->Render(url, bkcolor, local);
}

/****************************************************************************/
/****************************************************************************/

struct LiveClient :
  public ILiveBrowser,
  public CefClient,
  public CefLifeSpanHandler,
  public CefLoadHandler,
  public CefRenderHandler
{
  LiveClient(const sChar *url, sInt sizeX, sInt sizeY, sU32 bkcolor, bool local) : SizeX(sizeX), SizeY(sizeY)
  {
    stagingTex = new sTexture2D(sizeX, sizeY, sTEX_ARGB8888 | sTEX_STAGING | sTEX_NOMIPMAPS, 1);

    CefWindowInfo winfo;
    winfo.SetAsWindowless(sHWND);
    //winfo.shared_texture_enabled = true;

    CefBrowserSettings settings;
    if (local)
    {
      settings.web_security = cef_state_t::STATE_DISABLED;
      settings.universal_access_from_file_urls = cef_state_t::STATE_ENABLED;
    }
    settings.background_color = bkcolor;
    settings.windowless_frame_rate = 60;

    CefBrowserHost::CreateBrowser(winfo, this, url, settings, 0);       
  }

  virtual ~LiveClient() {}

  // CefClient methods
  virtual CefRefPtr<CefLifeSpanHandler> GetLifeSpanHandler() override { return this; }
  virtual CefRefPtr<CefLoadHandler> GetLoadHandler() override { return this; }
  virtual CefRefPtr<CefRenderHandler> GetRenderHandler() override { return this; }

  // CefLifeSpanHandler methods
  void OnAfterCreated(CefRefPtr<CefBrowser> browser) override {
    CEF_REQUIRE_UI_THREAD();
    Browser = browser;
  }

  // CefLoadHandler methods
  void OnLoadEnd(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, int httpStatusCode) override
  {
    
    if (frame->IsMain())
    {
      LoadDone = true;
    }
  }

  void OnLoadError(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, ErrorCode errorCode, const CefString& errorText, const CefString& failedUrl) override {
    CEF_REQUIRE_UI_THREAD();
    Error = true;
  }

  // CefRenderHandler methods
  void GetViewRect(CefRefPtr<CefBrowser> browser, CefRect& rect) override
  {
    rect.Set(0, 0, SizeX, SizeY);
  }

  void OnPaint(CefRefPtr<CefBrowser> browser, PaintElementType type, const RectList& dirtyRects, const void* buffer, int width, int height) override
  {
    for (auto r : dirtyRects)
    {
      sRect tr(r.x, r.y, r.x + r.width, r.y + r.height);
      sU8 *data;
      sInt pitch;
      stagingTex->BeginLoadPartial(tr, data, pitch);
      const sU32 *src = ((const sU32*)buffer) + r.y*SizeX + r.x;
      for (int y = 0; y < r.height; y++)
      {
        sCopyMem(data, src, 4 * r.width);
        src += SizeX;
        data += pitch;
      }
      stagingTex->EndLoad();
    }
    
    Dirty = 1;
  }

  void OnAcceleratedPaint(CefRefPtr<CefBrowser> browser, PaintElementType type, const RectList& dirtyRects, void* shared_handle)  override 
  {
  }

  int SizeX, SizeY;
  bool Error = false;
  bool LoadDone = false;
  bool Dirty = false;
  CefRefPtr<CefBrowser> Browser;
//  void *sharehandle = 0;
//  void *lasthandle = 0;
  sTexture2D *stagingTex = 0;

  IMPLEMENT_REFCOUNTING(LiveClient);

  // Inherited via ILiveBrowser
  bool CopyToTexture(sTexture2D *& tex) override
  {
    if (!tex)
      tex = new sTexture2D(SizeX, SizeY, sTEX_ARGB8888 | sTEX_DYNAMIC | sTEX_NOMIPMAPS);
    else
      tex->ReInit(SizeX, SizeY, sTEX_ARGB8888 | sTEX_DYNAMIC | sTEX_NOMIPMAPS);

    if (Dirty)
    {
      tex->UpdateFrom(stagingTex);
      Dirty = 0;
    }

    return LoadDone;
  }

  void Destroy() override
  {
    Browser->GetHost()->CloseBrowser(true);
    Browser = 0;
  }
};

ILiveBrowser *CreateLiveBrowser(const sChar *url, sInt sizeX, sInt sizeY, sU32 bkcolor, bool local)
{
  return new LiveClient(url, sizeX, sizeY, bkcolor, local);
}