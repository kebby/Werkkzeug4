/****************************************************************************/
/***                                                                      ***/
/***   Computer generated code - do not modify                            ***/
/***                                                                      ***/
/****************************************************************************/

#ifndef HEADER_WZ4OPS_basic_ops
#define HEADER_WZ4OPS_basic_ops

#include "wz4lib/doc.hpp"

/****************************************************************************/

extern class AnyTypeType_ *AnyTypeType;
extern class GroupTypeType_ *GroupTypeType;
extern class TextObjectType_ *TextObjectType;
extern class BitmapBaseType_ *BitmapBaseType;
extern class Texture2DType_ *Texture2DType;
extern class CubemapBaseType_ *CubemapBaseType;
extern class TextureCubeType_ *TextureCubeType;
extern class MeshBaseType_ *MeshBaseType;
extern class SceneType_ *SceneType;
extern class ScreenshotProxyType_ *ScreenshotProxyType;
extern class UnitTestType_ *UnitTestType;

/****************************************************************************/

#line 18 "basic_ops.ops"

#include "wz4lib/basic.hpp"

#line 32 "basic_ops.hpp"
class AnyTypeType_ : public wType
{
public:
  AnyTypeType_() { Color= 0xffc0c0c0; Flags = 0x0001; GuiSets = 0x0000; Symbol = L"AnyType"; Label = L"any";  Init(); }
  ~AnyTypeType_() { Exit(); }
#line 39 "basic_ops.hpp"
};

class GroupTypeType_ : public AnyTypeType_
{
public:
  GroupTypeType_() { Parent = AnyTypeType; Color= 0xffc0c0c0; Flags = 0x0003; GuiSets = 0x0002; Symbol = L"GroupType"; Label = L"Group";  Init(); }
  ~GroupTypeType_() { Exit(); }
#line 42 "basic_ops.ops"
  void Show(wObject *obj,wPaintInfo &pi);
#line 49 "basic_ops.hpp"
};

class TextObjectType_ : public AnyTypeType_
{
public:
  TextObjectType_() { Parent = AnyTypeType; Color= 0xffc0c0c0; Flags = 0x0001; GuiSets = 0x0000; Symbol = L"TextObject"; Label = L"String";  Init(); }
  ~TextObjectType_() { Exit(); }
#line 63 "basic_ops.ops"
  void Show(wObject *obj,wPaintInfo &pi);
#line 59 "basic_ops.hpp"
};

class BitmapBaseType_ : public AnyTypeType_
{
public:
  BitmapBaseType_() { Parent = AnyTypeType; Flags = 0x0001; GuiSets = 0x0001; Symbol = L"BitmapBase"; Label = L"Bitmap (base)";  Init(); }
  ~BitmapBaseType_() { Exit(); }
#line 67 "basic_ops.hpp"
};

class Texture2DType_ : public AnyTypeType_
{
public:
  Texture2DType_() { Parent = AnyTypeType; Flags = 0x0003; GuiSets = 0x0001; Symbol = L"Texture2D"; Label = L"Texture2D";  Init(); }
  ~Texture2DType_() { Exit(); }
#line 370 "basic_ops.ops"
  void Show(wObject *obj,wPaintInfo &pi);
#line 77 "basic_ops.hpp"
};

class CubemapBaseType_ : public AnyTypeType_
{
public:
  CubemapBaseType_() { Parent = AnyTypeType; Flags = 0x0001; GuiSets = 0x0001; Symbol = L"CubemapBase"; Label = L"Cubemap (base)";  Init(); }
  ~CubemapBaseType_() { Exit(); }
#line 85 "basic_ops.hpp"
};

class TextureCubeType_ : public AnyTypeType_
{
public:
  TextureCubeType_() { Parent = AnyTypeType; Flags = 0x0003; GuiSets = 0x0001; Symbol = L"TextureCube"; Label = L"TextureCube";  Init(); }
  ~TextureCubeType_() { Exit(); }
#line 93 "basic_ops.hpp"
};

class MeshBaseType_ : public AnyTypeType_
{
public:
  MeshBaseType_() { Parent = AnyTypeType; Flags = 0x0003; GuiSets = 0x0002; Symbol = L"MeshBase"; Label = L"Mesh (base)";  Init(); }
  ~MeshBaseType_() { Exit(); }
#line 490 "basic_ops.ops"
  virtual void BeginEngine(wPaintInfo &pi,sBool clear);
#line 491 "basic_ops.ops"
  virtual void EndEngine(wPaintInfo &pi);
#line 492 "basic_ops.ops"
  virtual void Paint(wObject *obj,wPaintInfo &pi,sMatrix34 *mat,sInt matcount);
#line 493 "basic_ops.ops"
  virtual void Hit(wObject *obj,const sRay &,wHitInfo &info);
#line 494 "basic_ops.ops"
  virtual void Wireframe(wObject *obj,wPaintInfo &pi,sMatrix34 &mat);
#line 495 "basic_ops.ops"
  virtual void Show(wObject *obj,wPaintInfo &pi);
#line 113 "basic_ops.hpp"
};

class SceneType_ : public AnyTypeType_
{
public:
  SceneType_() { Parent = AnyTypeType; Color= 0xffffff40; Flags = 0x0002; GuiSets = 0x0002; Symbol = L"Scene"; Label = L"Scene";  Init(); }
  ~SceneType_() { Exit(); }
#line 537 "basic_ops.ops"

  private:
    MeshBaseType_ *LastEngine;
  public:
  
#line 126 "basic_ops.hpp"
#line 543 "basic_ops.ops"
  void Show(wObject *obj,wPaintInfo &pi);
#line 595 "basic_ops.ops"
  void SetEngine(MeshBaseType_ *engine,wPaintInfo &pi);
#line 615 "basic_ops.ops"
  void Hit(wObject *obj,const sRay &ray,wHitInfo &info);
#line 645 "basic_ops.ops"
  void Wireframe(wObject *obj,wPaintInfo &pi,sMatrix34 &mat);
#line 136 "basic_ops.hpp"
};

class ScreenshotProxyType_ : public AnyTypeType_
{
public:
  ScreenshotProxyType_() { Parent = AnyTypeType; Flags = 0x0003; GuiSets = 0x0002; Symbol = L"ScreenshotProxy"; Label = L"ScreenshotProxy";  Init(); }
  ~ScreenshotProxyType_() { Exit(); }
#line 1000 "basic_ops.ops"

    void Show(wObject *obj,wPaintInfo &pi);
  
#line 147 "basic_ops.hpp"
#line 149 "basic_ops.hpp"
};

class UnitTestType_ : public AnyTypeType_
{
public:
  UnitTestType_() { Parent = AnyTypeType; Flags = 0x0001; GuiSets = 0x0001; Symbol = L"UnitTest"; Label = L"UnitTest";  Init(); }
  ~UnitTestType_() { Exit(); }
#line 1116 "basic_ops.ops"

    void Show(wObject *obj,wPaintInfo &pi);
  
#line 160 "basic_ops.hpp"
#line 162 "basic_ops.hpp"
};

struct TextObjectParaText
{
};

struct TextObjectParaTextEx
{
};

struct TextObjectParaTextAdd
{
};

struct TextObjectParaTextExport
{
};

struct AnyTypeParaNop
{
};

struct AnyTypeParaComment
{
  sInt Color;
};

struct AnyTypeParaBlockHandles
{
};

struct AnyTypeParaDummy
{
};

struct AnyTypeParaDummyObj
{
};

struct AnyTypeParaStore
{
};

struct AnyTypeParaLoad
{
};

struct AnyTypeParaGroup
{
};

struct GroupTypeParaGroup3D
{
};

struct AnyTypeParaSlow
{
};

struct AnyTypeParaUnknownOp
{
};

struct AnyTypeParaBlockChange
{
};

struct AnyTypeParaCopy
{
};

struct AnyTypeParaCall
{
  sInt Flags;
};

struct AnyTypeParaCallWithInputLinks
{
  sInt Flags;
};

struct AnyTypeParaInput
{
  sInt Input;
};

struct AnyTypeParaInjectGlobals
{
};

struct AnyTypeParaLoop
{
  sInt Max;
};

struct AnyTypeParaEndLoop
{
};

struct AnyTypeParaShellSwitch
{
  sInt Condition;
};

struct Texture2DParaMakeTexture
{
  sInt Format;
  sInt Flags;
};

struct Texture2DParaExport
{
};

struct Texture2DParaImport
{
};

struct TextureCubeParaMakeCubeTex
{
  sInt Format;
};

struct SceneParaAdd
{
};

struct SceneParaConvertSceneNode
{
};

struct SceneParaNode
{
  sInt LFlags;
  sInt NameId;
  sInt Lods;
  sInt HighLod;
  sInt MediumLod;
  sInt LowLod;
};

struct SceneParaNameId
{
  sInt NameId;
};

struct SceneParaSelectNameId
{
  sInt NameId;
  sInt Mode;
};

struct SceneParaTransform
{
  sVector31 Scale;
  sVector30 Rotate;
  sVector31 Translate;
};

struct SceneParaMultiply
{
  sVector31 Scale;
  sVector30 Rotate;
  sVector31 Translate;
  sInt Count;
  sVector31 Scale0;
  sVector30 Rotate0;
  sVector31 Translate0;
};

struct ScreenshotProxyParaScreenshot
{
  sInt Mode;
  sVector30 Rotate;
  sVector31 Position;
  sVector31 Target;
  sF32 Zoom;
  sInt SizeX;
  sInt SizeY;
  sInt Multisample;
  sF32 StartTime;
  sInt TimeBase;
  sF32 EndTime;
  sF32 FPS;
};

struct UnitTestParaUnitTestAdd
{
};

struct UnitTestParaUnitTestScene
{
  sInt Flags;
  sVector30 Rotate;
  sF32 Distance;
  sF32 Zoom;
  sInt SizeX;
  sInt SizeY;
  sU32 ClearColor;
};


/****************************************************************************/

struct TextObjectAnimText
{
  void Init(class ScriptContext *sc);
  void Bind(class ScriptContext *sc,TextObjectParaText *para);

};

struct TextObjectAnimTextEx
{
  void Init(class ScriptContext *sc);
  void Bind(class ScriptContext *sc,TextObjectParaTextEx *para);

};

struct TextObjectAnimTextAdd
{
  void Init(class ScriptContext *sc);
  void Bind(class ScriptContext *sc,TextObjectParaTextAdd *para);

};

struct TextObjectAnimTextExport
{
  void Init(class ScriptContext *sc);
  void Bind(class ScriptContext *sc,TextObjectParaTextExport *para);

};

struct AnyTypeAnimNop
{
  void Init(class ScriptContext *sc);
  void Bind(class ScriptContext *sc,AnyTypeParaNop *para);

};

struct AnyTypeAnimComment
{
  void Init(class ScriptContext *sc);
  void Bind(class ScriptContext *sc,AnyTypeParaComment *para);

};

struct AnyTypeAnimBlockHandles
{
  void Init(class ScriptContext *sc);
  void Bind(class ScriptContext *sc,AnyTypeParaBlockHandles *para);

};

struct AnyTypeAnimDummy
{
  void Init(class ScriptContext *sc);
  void Bind(class ScriptContext *sc,AnyTypeParaDummy *para);

};

struct AnyTypeAnimDummyObj
{
  void Init(class ScriptContext *sc);
  void Bind(class ScriptContext *sc,AnyTypeParaDummyObj *para);

};

struct AnyTypeAnimStore
{
  void Init(class ScriptContext *sc);
  void Bind(class ScriptContext *sc,AnyTypeParaStore *para);

};

struct AnyTypeAnimLoad
{
  void Init(class ScriptContext *sc);
  void Bind(class ScriptContext *sc,AnyTypeParaLoad *para);

};

struct AnyTypeAnimGroup
{
  void Init(class ScriptContext *sc);
  void Bind(class ScriptContext *sc,AnyTypeParaGroup *para);

};

struct GroupTypeAnimGroup3D
{
  void Init(class ScriptContext *sc);
  void Bind(class ScriptContext *sc,GroupTypeParaGroup3D *para);

};

struct AnyTypeAnimSlow
{
  void Init(class ScriptContext *sc);
  void Bind(class ScriptContext *sc,AnyTypeParaSlow *para);

};

struct AnyTypeAnimUnknownOp
{
  void Init(class ScriptContext *sc);
  void Bind(class ScriptContext *sc,AnyTypeParaUnknownOp *para);

};

struct AnyTypeAnimBlockChange
{
  void Init(class ScriptContext *sc);
  void Bind(class ScriptContext *sc,AnyTypeParaBlockChange *para);

};

struct AnyTypeAnimCopy
{
  void Init(class ScriptContext *sc);
  void Bind(class ScriptContext *sc,AnyTypeParaCopy *para);

};

struct AnyTypeAnimCall
{
  void Init(class ScriptContext *sc);
  void Bind(class ScriptContext *sc,AnyTypeParaCall *para);

};

struct AnyTypeAnimCallWithInputLinks
{
  void Init(class ScriptContext *sc);
  void Bind(class ScriptContext *sc,AnyTypeParaCallWithInputLinks *para);

};

struct AnyTypeAnimInput
{
  void Init(class ScriptContext *sc);
  void Bind(class ScriptContext *sc,AnyTypeParaInput *para);

};

struct AnyTypeAnimInjectGlobals
{
  void Init(class ScriptContext *sc);
  void Bind(class ScriptContext *sc,AnyTypeParaInjectGlobals *para);

};

struct AnyTypeAnimLoop
{
  void Init(class ScriptContext *sc);
  void Bind(class ScriptContext *sc,AnyTypeParaLoop *para);

};

struct AnyTypeAnimEndLoop
{
  void Init(class ScriptContext *sc);
  void Bind(class ScriptContext *sc,AnyTypeParaEndLoop *para);

};

struct AnyTypeAnimShellSwitch
{
  void Init(class ScriptContext *sc);
  void Bind(class ScriptContext *sc,AnyTypeParaShellSwitch *para);

};

struct Texture2DAnimMakeTexture
{
  void Init(class ScriptContext *sc);
  void Bind(class ScriptContext *sc,Texture2DParaMakeTexture *para);

};

struct Texture2DAnimExport
{
  void Init(class ScriptContext *sc);
  void Bind(class ScriptContext *sc,Texture2DParaExport *para);

};

struct Texture2DAnimImport
{
  void Init(class ScriptContext *sc);
  void Bind(class ScriptContext *sc,Texture2DParaImport *para);

};

struct TextureCubeAnimMakeCubeTex
{
  void Init(class ScriptContext *sc);
  void Bind(class ScriptContext *sc,TextureCubeParaMakeCubeTex *para);

};

struct SceneAnimAdd
{
  void Init(class ScriptContext *sc);
  void Bind(class ScriptContext *sc,SceneParaAdd *para);

};

struct SceneAnimConvertSceneNode
{
  void Init(class ScriptContext *sc);
  void Bind(class ScriptContext *sc,SceneParaConvertSceneNode *para);

};

struct SceneAnimNode
{
  void Init(class ScriptContext *sc);
  void Bind(class ScriptContext *sc,SceneParaNode *para);

};

struct SceneAnimNameId
{
  void Init(class ScriptContext *sc);
  void Bind(class ScriptContext *sc,SceneParaNameId *para);

};

struct SceneAnimSelectNameId
{
  void Init(class ScriptContext *sc);
  void Bind(class ScriptContext *sc,SceneParaSelectNameId *para);

};

struct SceneAnimTransform
{
  void Init(class ScriptContext *sc);
  void Bind(class ScriptContext *sc,SceneParaTransform *para);

};

struct SceneAnimMultiply
{
  void Init(class ScriptContext *sc);
  void Bind(class ScriptContext *sc,SceneParaMultiply *para);

};

struct ScreenshotProxyAnimScreenshot
{
  void Init(class ScriptContext *sc);
  void Bind(class ScriptContext *sc,ScreenshotProxyParaScreenshot *para);

};

struct UnitTestAnimUnitTestAdd
{
  void Init(class ScriptContext *sc);
  void Bind(class ScriptContext *sc,UnitTestParaUnitTestAdd *para);

};

struct UnitTestAnimUnitTestScene
{
  void Init(class ScriptContext *sc);
  void Bind(class ScriptContext *sc,UnitTestParaUnitTestScene *para);

};


/****************************************************************************/

void AddTypes_basic_ops(sBool secondary=0);
void AddOps_basic_ops(sBool secondary=0);

/****************************************************************************/

#endif
