/****************************************************************************/
/***                                                                      ***/
/***   Computer generated code - do not modify                            ***/
/***                                                                      ***/
/****************************************************************************/

#ifndef HEADER_WZ4OPS_poc_ops
#define HEADER_WZ4OPS_poc_ops

#include "wz4lib/doc.hpp"

/****************************************************************************/

extern class PocBitmapType_ *PocBitmapType;
extern class PocMaterialType_ *PocMaterialType;
extern class PocMeshType_ *PocMeshType;

/****************************************************************************/

#line 13 "poc_ops.ops"

  #include "wz4lib/basic_ops.hpp"
  #include "wz4lib/poc.hpp"
  #include "util/image.hpp"
  #include "base/graphics.hpp"
  #include "util/shaders.hpp"

#line 28 "poc_ops.hpp"
class PocBitmapType_ : public BitmapBaseType_
{
public:
  PocBitmapType_() { Parent = BitmapBaseType; Color= 0xffff40ff; Flags = 0x0004; GuiSets = 0x0001; Symbol = L"PocBitmap"; Label = L"PoC Bitmap";  Init(); }
  ~PocBitmapType_() { Exit(); }
#line 34 "poc_ops.ops"
  void Show(wObject *obj,wPaintInfo &pi);
#line 37 "poc_ops.hpp"
};

class PocMaterialType_ : public AnyTypeType_
{
public:
  PocMaterialType_() { Parent = AnyTypeType; Color= 0xff40ff40; Flags = 0x0003; GuiSets = 0x0000; Symbol = L"PocMaterial"; Label = L"PoC Material";  Init(); }
  ~PocMaterialType_() { Exit(); }
#line 893 "poc_ops.ops"

  private:
    PocMaterial *Default;
  public:
    PocMaterial *GetDefault() { return Default; }
  
#line 51 "poc_ops.hpp"
#line 900 "poc_ops.ops"
  void Init();
#line 908 "poc_ops.ops"
  void Exit();
#line 913 "poc_ops.ops"
  void Show(wObject *obj,wPaintInfo &pi);
#line 59 "poc_ops.hpp"
};

class PocMeshType_ : public MeshBaseType_
{
public:
  PocMeshType_() { Parent = MeshBaseType; Color= 0xff40ffff; Flags = 0x0002; GuiSets = 0x0002; Symbol = L"PocMesh"; Label = L"PoC Mesh";  Init(); }
  ~PocMeshType_() { Exit(); }
#line 982 "poc_ops.ops"

    sGeometry *WireGeo;
  
#line 70 "poc_ops.hpp"
#line 986 "poc_ops.ops"
  void Init();
#line 992 "poc_ops.ops"
  void Exit();
#line 997 "poc_ops.ops"
  void BeginEngine(wPaintInfo &pi,sBool clear);
#line 1005 "poc_ops.ops"
  void EndEngine(wPaintInfo &pi);
#line 1009 "poc_ops.ops"
  void Paint(wObject *obj,wPaintInfo &pi,sMatrix34 *mat,sInt matcount);
#line 1038 "poc_ops.ops"
  void Hit(wObject *obj,const sRay &ray,wHitInfo &info);
#line 1045 "poc_ops.ops"
  void Wireframe(wObject *obj,wPaintInfo &pi,sMatrix34 &mat);
#line 86 "poc_ops.hpp"
};

struct PocBitmapParaFlat
{
  sInt SizeX;
  sInt SizeY;
  sU32 Color;
};

struct PocBitmapParaGlow
{
  sF32 Pos[2];
  sF32 Radius[2];
  sU32 Color;
  sF32 Alpha;
  sF32 Power;
};

struct PocBitmapParaAdd
{
  sInt Mode;
  sU32 ResultMul;
};

struct PocBitmapParaMandelbrot
{
  sInt SizeX;
  sInt SizeY;
  sInt Depth;
  sF32 Center[2];
  sF32 Size[2];
  sU32 Range0;
  sU32 Range1;
};

struct PocBitmapParaPerlin
{
  sInt SizeX;
  sInt SizeY;
  sInt Frequency;
  sInt Octaves;
  sF32 Falloff;
  sF32 Amplify;
  sInt Mode;
  sInt Seed;
  sU32 Color0;
  sU32 Color1;
};

struct PocBitmapParaNormals
{
  sF32 Strength;
};

struct PocBitmapParaImport
{
  sInt Flags;
};

struct PocBitmapParaRotZoom
{
  sInt SizeX;
  sInt SizeY;
  sF32 Center[2];
  sF32 Zoom[2];
  sF32 Angle;
  sF32 Scroll[2];
};

struct PocBitmapParaAtlas
{
  sU32 EmptyColor;
  sInt Mode;
};

struct PocBitmapParaPreMulAlpha
{
  sInt Flags;
};

struct PocBitmapParaBlueToAlpha
{
};

struct PocBitmapParaColor
{
  sInt Mode;
  sU32 Color0;
  sU32 Color1;
};

struct PocBitmapParaSCB
{
  sF32 Saturation;
  sF32 Contrast;
  sF32 Brightness;
};

struct PocBitmapParaColorBalance
{
  sVector30 Shadows;
  sVector30 Midtones;
  sVector30 Highlights;
};

struct PocBitmapParaBlur
{
  sF32 Radius[2];
  sInt Filter;
};

struct PocBitmapParaDistanceField
{
  sInt Threshold;
  sInt Width;
  sInt Scale;
};

struct PocBitmapParaHalf
{
};

struct PocBitmapParaExport
{
};

struct UnitTestParaUnitTestPocBitmap
{
  sInt Flags;
};

struct PocMaterialParaMaterial
{
  sInt Flags;
  sInt Blend;
  sInt TFlags0;
};

struct PocMeshParatorus
{
  sF32 Inner;
  sF32 Outer;
  sF32 Phase;
  sInt Segments;
  sInt Roundness;
};

struct PocMeshParaCube
{
};

struct PocMeshParaAdd
{
};

struct PocMeshParaTranslate
{
  sVector31 Scale;
  sVector30 Rotate;
  sVector31 Trans;
};

struct PocMeshParaSetMtrl
{
};


/****************************************************************************/

struct PocBitmapAnimFlat
{
  void Init(class ScriptContext *sc);
  void Bind(class ScriptContext *sc,PocBitmapParaFlat *para);

};

struct PocBitmapAnimGlow
{
  void Init(class ScriptContext *sc);
  void Bind(class ScriptContext *sc,PocBitmapParaGlow *para);

};

struct PocBitmapAnimAdd
{
  void Init(class ScriptContext *sc);
  void Bind(class ScriptContext *sc,PocBitmapParaAdd *para);

};

struct PocBitmapAnimMandelbrot
{
  void Init(class ScriptContext *sc);
  void Bind(class ScriptContext *sc,PocBitmapParaMandelbrot *para);

};

struct PocBitmapAnimPerlin
{
  void Init(class ScriptContext *sc);
  void Bind(class ScriptContext *sc,PocBitmapParaPerlin *para);

};

struct PocBitmapAnimNormals
{
  void Init(class ScriptContext *sc);
  void Bind(class ScriptContext *sc,PocBitmapParaNormals *para);

};

struct PocBitmapAnimImport
{
  void Init(class ScriptContext *sc);
  void Bind(class ScriptContext *sc,PocBitmapParaImport *para);

};

struct PocBitmapAnimRotZoom
{
  void Init(class ScriptContext *sc);
  void Bind(class ScriptContext *sc,PocBitmapParaRotZoom *para);

};

struct PocBitmapAnimAtlas
{
  void Init(class ScriptContext *sc);
  void Bind(class ScriptContext *sc,PocBitmapParaAtlas *para);

};

struct PocBitmapAnimPreMulAlpha
{
  void Init(class ScriptContext *sc);
  void Bind(class ScriptContext *sc,PocBitmapParaPreMulAlpha *para);

};

struct PocBitmapAnimBlueToAlpha
{
  void Init(class ScriptContext *sc);
  void Bind(class ScriptContext *sc,PocBitmapParaBlueToAlpha *para);

};

struct PocBitmapAnimColor
{
  void Init(class ScriptContext *sc);
  void Bind(class ScriptContext *sc,PocBitmapParaColor *para);

};

struct PocBitmapAnimSCB
{
  void Init(class ScriptContext *sc);
  void Bind(class ScriptContext *sc,PocBitmapParaSCB *para);

};

struct PocBitmapAnimColorBalance
{
  void Init(class ScriptContext *sc);
  void Bind(class ScriptContext *sc,PocBitmapParaColorBalance *para);

};

struct PocBitmapAnimBlur
{
  void Init(class ScriptContext *sc);
  void Bind(class ScriptContext *sc,PocBitmapParaBlur *para);

};

struct PocBitmapAnimDistanceField
{
  void Init(class ScriptContext *sc);
  void Bind(class ScriptContext *sc,PocBitmapParaDistanceField *para);

};

struct PocBitmapAnimHalf
{
  void Init(class ScriptContext *sc);
  void Bind(class ScriptContext *sc,PocBitmapParaHalf *para);

};

struct PocBitmapAnimExport
{
  void Init(class ScriptContext *sc);
  void Bind(class ScriptContext *sc,PocBitmapParaExport *para);

};

struct UnitTestAnimUnitTestPocBitmap
{
  void Init(class ScriptContext *sc);
  void Bind(class ScriptContext *sc,UnitTestParaUnitTestPocBitmap *para);

};

struct PocMaterialAnimMaterial
{
  void Init(class ScriptContext *sc);
  void Bind(class ScriptContext *sc,PocMaterialParaMaterial *para);

};

struct PocMeshAnimtorus
{
  void Init(class ScriptContext *sc);
  void Bind(class ScriptContext *sc,PocMeshParatorus *para);

};

struct PocMeshAnimCube
{
  void Init(class ScriptContext *sc);
  void Bind(class ScriptContext *sc,PocMeshParaCube *para);

};

struct PocMeshAnimAdd
{
  void Init(class ScriptContext *sc);
  void Bind(class ScriptContext *sc,PocMeshParaAdd *para);

};

struct PocMeshAnimTranslate
{
  void Init(class ScriptContext *sc);
  void Bind(class ScriptContext *sc,PocMeshParaTranslate *para);

};

struct PocMeshAnimSetMtrl
{
  void Init(class ScriptContext *sc);
  void Bind(class ScriptContext *sc,PocMeshParaSetMtrl *para);

};


/****************************************************************************/

void AddTypes_poc_ops(sBool secondary=0);
void AddOps_poc_ops(sBool secondary=0);

/****************************************************************************/

#endif
