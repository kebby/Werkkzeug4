/****************************************************************************/
/***                                                                      ***/
/***   Computer generated code - do not modify                            ***/
/***                                                                      ***/
/****************************************************************************/

#define sPEDANTIC_OBSOLETE 1
#define sPEDANTIC_WARN 1
#include "gui/gui.hpp"
#include "gui/textwindow.hpp"
#include "wz4lib/script.hpp"
#include "poc_ops.hpp"

#pragma warning(disable:4189) // unused variables - happens in generated code


/****************************************************************************/

class PocBitmapType_ *PocBitmapType;
class PocMaterialType_ *PocMaterialType;
class PocMeshType_ *PocMeshType;

/****************************************************************************/

#line 34 "poc_ops.ops"
void PocBitmapType_::Show(wObject *obj,wPaintInfo &pi)
{
#line 35 "poc_ops.ops"

    sImage *img = 0;
    img = ((PocBitmap *) obj)->Image;
    pi.SetSizeTex2D(img->SizeX,img->SizeY);
    pi.PaintTex2D(img);
    pi.PaintHandles();
  ;
#line 36 "poc_ops.cpp"
}
#line 900 "poc_ops.ops"
void PocMaterialType_::Init()
{
#line 901 "poc_ops.ops"
 
    Default=new PocMaterial;
    Default->Material = new sSimpleMaterial;
    Default->Material->Flags |= sMTRL_LIGHTING;
    Default->Material->Prepare(sVertexFormatStandard);
  ;
#line 48 "poc_ops.cpp"
}
#line 908 "poc_ops.ops"
void PocMaterialType_::Exit()
{
#line 909 "poc_ops.ops"
 
    Default->Release(); 
  ;
#line 57 "poc_ops.cpp"
}
#line 913 "poc_ops.ops"
void PocMaterialType_::Show(wObject *obj,wPaintInfo &pi)
{
#line 914 "poc_ops.ops"

    PocMaterial *mtrl;
  
    sSetTarget(sTargetPara(sST_CLEARALL,pi.BackColor,pi.Spec));

    if(obj && obj->Type==PocMaterialType)
    {
      mtrl = (PocMaterial *) obj;

      sCBuffer<sSimpleMaterialEnvPara> cb;
      cb.Data->Set(*pi.View,*pi.Env);
      mtrl->Material->Set(&cb);

      pi.PaintMtrl();
    }
  ;
#line 79 "poc_ops.cpp"
}
#line 986 "poc_ops.ops"
void PocMeshType_::Init()
{
#line 987 "poc_ops.ops"

    WireGeo = new sGeometry;
    WireGeo->Init(sGF_LINELIST|sGF_INDEX32,sVertexFormatSingle);
  ;
#line 89 "poc_ops.cpp"
}
#line 992 "poc_ops.ops"
void PocMeshType_::Exit()
{
#line 993 "poc_ops.ops"

    sDelete(WireGeo);
  ;
#line 98 "poc_ops.cpp"
}
#line 997 "poc_ops.ops"
void PocMeshType_::BeginEngine(wPaintInfo &pi,sBool clear)
{
#line 998 "poc_ops.ops"

    sSetTarget(sTargetPara(clear ? sST_CLEARALL : 0,pi.BackColor,pi.Spec));
    pi.View->SetTargetCurrent();
    pi.View->SetZoom(pi.Zoom3D);
    pi.View->Prepare();
  ;
#line 110 "poc_ops.cpp"
}
#line 1005 "poc_ops.ops"
void PocMeshType_::EndEngine(wPaintInfo &pi)
{
#line 1006 "poc_ops.ops"

  ;
#line 118 "poc_ops.cpp"
}
#line 1009 "poc_ops.ops"
void PocMeshType_::Paint(wObject *obj,wPaintInfo &pi,sMatrix34 *mat,sInt matcount)
{
#line 1010 "poc_ops.ops"

    PocMeshCluster *cl;
    PocMesh *mesh;
    sCBuffer<sSimpleMaterialEnvPara> cb; 
    if(obj && obj->Type==PocMeshType)
    {
      mesh = (PocMesh *) obj;
      mesh->CacheSolid();
      sFORALL(mesh->Clusters,cl)
      {
        for(sInt i=0;i<matcount;i++)
        {
          pi.View->UpdateModelMatrix(mat[i]);
          cb.Data->Set(*pi.View,*pi.Env);
          if(cl->Mtrl && cl->Mtrl->Material)
            cl->Mtrl->Material->Set(&cb);
          else
            pi.ShadedMtrl->Set(&cb);

          sDrawRange ir;
          ir.Start = cl->StartIndex;
          ir.End = cl->EndIndex;
          mesh->SolidGeo->Draw(sGeometryDrawInfo(&ir,1));
        }
      }
    }
  ;
#line 151 "poc_ops.cpp"
}
#line 1038 "poc_ops.ops"
void PocMeshType_::Hit(wObject *obj,const sRay &ray,wHitInfo &info)
{
#line 1039 "poc_ops.ops"

    sClear(info);
    if(obj->IsType(PocMeshType))
      ((PocMesh *)obj)->Hit(ray,info);
  ;
#line 162 "poc_ops.cpp"
}
#line 1045 "poc_ops.ops"
void PocMeshType_::Wireframe(wObject *obj,wPaintInfo &pi,sMatrix34 &mat)
{
#line 1046 "poc_ops.ops"

    if(obj->IsType(PocMeshType))
      ((PocMesh *)obj)->Wireframe(obj,pi,WireGeo,mat);
  ;
#line 172 "poc_ops.cpp"
}

/****************************************************************************/

sBool PocBitmapCmdFlat(wExecutive *exe,wCommand *cmd)
{
  PocBitmapParaFlat sUNUSED *para = (PocBitmapParaFlat *)(cmd->Data); para;
  PocBitmap *out = (PocBitmap *) cmd->Output;
  if(!out) { out=new PocBitmap; cmd->Output=out; }

  {
#line 61 "poc_ops.ops"

    out->Image->Init(1<<para->SizeX,1<<para->SizeY);
    out->Image->Fill(para->Color);
    return 1;
  ;
#line 190 "poc_ops.cpp"
    return 1;
  }
}

void PocBitmapGuiFlat(wGridFrameHelper &gh,wOp *op)
{
  PocBitmapParaFlat sUNUSED *para = (PocBitmapParaFlat *)(op->EditData); para;
  gh.Group(op->Class->Label);

  gh.Label(L"Size");

  gh.Flags(&para->SizeX,L" 1| 2| 4| 8| 16| 32| 64| 128| 256| 512| 1024| 2048",gh.ChangeMsg);

  gh.Flags(&para->SizeY,L" 1| 2| 4| 8| 16| 32| 64| 128| 256| 512| 1024| 2048",gh.ChangeMsg);

  gh.Label(L"Color");
  gh.ColorPick(&para->Color,L"rgba",0);
}

void PocBitmapDefFlat(wOp *op)
{
  PocBitmapParaFlat sUNUSED *para = (PocBitmapParaFlat *)(op->EditData); para;
  op->ArrayGroupMode = 0;
  para->SizeX = 0x00000008;
  para->SizeY = 0x00000008;
  para->Color = 0xff000000;
}

void PocBitmapBindFlat(wCommand *cmd,ScriptContext *ctx)
{
  ScriptValue *val;
  val = ctx->MakeValue(ScriptTypeColor,1);
  val->ColorPtr = ((sU32 *)cmd->Data)+2;
  ctx->BindLocal(ctx->AddSymbol(L"color_"),val);
}
void PocBitmapBind2Flat(wCommand *cmd,ScriptContext *ctx)
{
  static sInt initdone = 0;
  static sPoolString name[4];
  if(!initdone)
  {
    initdone = 1; 
    name[0] = sPoolString(L"size");
    name[1] = sPoolString(L"sizex");
    name[2] = sPoolString(L"sizey");
    name[3] = sPoolString(L"color_");
  }
  ctx->AddImport(name[3],ScriptTypeColor,1,cmd->Data+2);
}
void PocBitmapBind3Flat(wOp *op,sTextBuffer &tb)
{
  tb.PrintF(L"  import color_ : color;\n");
}
const sChar *PocBitmapWikiFlat =
L"= PocBitmap : Flat\n"
L"\n"
L"!t 2 : 2 3\n"
L" !T 2\n"
L"  !i Name\n"
L"  !i Flat\n"
L"\n"
L"  !i Output Type\n"
L"  !i PocBitmap\n"
L" !i\n"
L"\n"
L"== Parameters\n"
L"\n"
L"!T 4 : 1 1 1 2\n"
L" !\n"
L"  ! bc #c0c0c0\n"
L"  !i Screen Name\n"
L"  !i Script Name\n"
L"  !i Type\n"
L"  !i Comment\n"
L"\n"
L"!T 4 : 1 1 1 2\n"
L" !i Size\n"
L" !i SizeX\n"
L" !i 1\n"
L" !i *\n"
L" !i \n"
L" !i \n"
L" !i 2\n"
L" !i *\n"
L" !i \n"
L" !i \n"
L" !i 4\n"
L" !i *\n"
L" !i \n"
L" !i \n"
L" !i 8\n"
L" !i *\n"
L" !i \n"
L" !i \n"
L" !i 16\n"
L" !i *\n"
L" !i \n"
L" !i \n"
L" !i 32\n"
L" !i *\n"
L" !i \n"
L" !i \n"
L" !i 64\n"
L" !i *\n"
L" !i \n"
L" !i \n"
L" !i 128\n"
L" !i *\n"
L" !i \n"
L" !i \n"
L" !i 256\n"
L" !i *\n"
L" !i \n"
L" !i \n"
L" !i 512\n"
L" !i *\n"
L" !i \n"
L" !i \n"
L" !i 1024\n"
L" !i *\n"
L" !i \n"
L" !i \n"
L" !i 2048\n"
L" !i *\n"
L"!T 4 : 1 1 1 2\n"
L" !i <NULL>\n"
L" !i SizeY\n"
L" !i 1\n"
L" !i *\n"
L" !i \n"
L" !i \n"
L" !i 2\n"
L" !i *\n"
L" !i \n"
L" !i \n"
L" !i 4\n"
L" !i *\n"
L" !i \n"
L" !i \n"
L" !i 8\n"
L" !i *\n"
L" !i \n"
L" !i \n"
L" !i 16\n"
L" !i *\n"
L" !i \n"
L" !i \n"
L" !i 32\n"
L" !i *\n"
L" !i \n"
L" !i \n"
L" !i 64\n"
L" !i *\n"
L" !i \n"
L" !i \n"
L" !i 128\n"
L" !i *\n"
L" !i \n"
L" !i \n"
L" !i 256\n"
L" !i *\n"
L" !i \n"
L" !i \n"
L" !i 512\n"
L" !i *\n"
L" !i \n"
L" !i \n"
L" !i 1024\n"
L" !i *\n"
L" !i \n"
L" !i \n"
L" !i 2048\n"
L" !i *\n"
L"!T 4 : 1 1 1 2\n"
L" !i Color\n"
L" !i Color\n"
L" !i color\n"
L" !i *\n"
L"\n"
L"== Comments\n"
L"\n"
L"*\n"
L"\n"
L"== See Also\n"
L"\n"
L"\n"
;

/****************************************************************************/

struct PocBitmapHelperGlow
{
#line 92 "poc_ops.ops"
  sF32 x1;
#line 93 "poc_ops.ops"
  sF32 y1;
#line 94 "poc_ops.ops"
  sF32 cx;
#line 95 "poc_ops.ops"
  sF32 cy;
#line 392 "poc_ops.cpp"
};
sBool PocBitmapCmdGlow(wExecutive *exe,wCommand *cmd)
{
  PocBitmapParaGlow sUNUSED *para = (PocBitmapParaGlow *)(cmd->Data); para;
  PocBitmap sUNUSED *in0 = cmd->GetInput<PocBitmap *>(0); in0;
  PocBitmap *out = (PocBitmap *) cmd->Output;
  if(!out) { out=new PocBitmap; out->CopyFrom(in0); cmd->Output=out; }

  {
#line 86 "poc_ops.ops"

    out->Image->Glow(para->Pos[0],para->Pos[1],para->Radius[0],para->Radius[1],para->Color,para->Alpha,para->Power);
  ;
#line 405 "poc_ops.cpp"
    return 1;
  }
}

void PocBitmapHndGlow(wPaintInfo &pi,wOp *op)
{
  PocBitmapParaGlow sUNUSED *para = (PocBitmapParaGlow *)(op->EditData); para;
  PocBitmapHelperGlow *helper = (PocBitmapHelperGlow *)(op->HelperData);
#line 99 "poc_ops.ops"

    sInt id = pi.FirstSelectedId(op);
    switch(id)
    {
    default:
      helper->x1 = para->Radius[0]+para->Pos[0];
      helper->y1 = para->Radius[1]+para->Pos[1];
      break;
    case 2:
      para->Radius[0] = sAbs(helper->x1-para->Pos[0]);
      para->Radius[1] = sAbs(helper->y1-para->Pos[1]);
      break;
    case 3:
      para->Radius[0] = para->Radius[1] = sAbs(helper->x1-para->Pos[0]);
      helper->y1 = para->Radius[1]+para->Pos[1];
      break;
    case 4:
      para->Radius[0] = para->Radius[1] = sAbs(helper->y1-para->Pos[1]);
      helper->x1 = para->Radius[0]+para->Pos[0];
      break;
    }
    helper->cx = para->Pos[0];
    helper->cy = para->Pos[1];
    pi.HandleTex2D(op,1,para->Pos[0],para->Pos[1]);
    pi.HandleTex2D(op,2,helper->x1,helper->y1);
    pi.HandleTex2D(op,3,helper->x1,helper->cy);
    pi.HandleTex2D(op,4,helper->cx,helper->y1);
    pi.LineTex2D(para->Pos[0],para->Pos[1],helper->x1,helper->y1);
    pi.LineTex2D(para->Pos[0],helper->y1,helper->x1,helper->y1);
    pi.LineTex2D(helper->x1,para->Pos[1],helper->x1,helper->y1);
  ;
#line 446 "poc_ops.cpp"
}

void PocBitmapGuiGlow(wGridFrameHelper &gh,wOp *op)
{
  PocBitmapParaGlow sUNUSED *para = (PocBitmapParaGlow *)(op->EditData); para;
  gh.Group(op->Class->Label);

  gh.Label(L"Center");
  gh.BeginTied();
  sFloatControl *float_Pos_0 = gh.Float(&para->Pos[0],-16.0000f,16.00000f,0.010000f);
  float_Pos_0->Default = 0.500000f; float_Pos_0->RightStep = 0.125000f;
  sFloatControl *float_Pos_1 = gh.Float(&para->Pos[1],-16.0000f,16.00000f,0.010000f);
  float_Pos_1->Default = 0.500000f; float_Pos_1->RightStep = 0.125000f;
  gh.EndTied();

  gh.Label(L"Radius");
  gh.BeginTied();
  sFloatControl *float_Radius_0 = gh.Float(&para->Radius[0],-16.0000f,16.00000f,0.010000f);
  float_Radius_0->Default = 0.500000f; float_Radius_0->RightStep = 0.125000f;
  sFloatControl *float_Radius_1 = gh.Float(&para->Radius[1],-16.0000f,16.00000f,0.010000f);
  float_Radius_1->Default = 0.500000f; float_Radius_1->RightStep = 0.125000f;
  gh.EndTied();

  gh.Label(L"Color");
  gh.ColorPick(&para->Color,L"rgba",0);

  gh.Label(L"Alpha");
  sFloatControl *float_Alpha = gh.Float(&para->Alpha,0.000000f,1.000000f,0.010000f);
  float_Alpha->Default = 1.000000f; float_Alpha->RightStep = 0.125000f;

  gh.Label(L"Power");
  sFloatControl *float_Power = gh.Float(&para->Power,0.000000f,64.00000f,0.020000f);
  float_Power->Default = 2.000000f; float_Power->RightStep = 0.125000f;
}

void PocBitmapDefGlow(wOp *op)
{
  PocBitmapParaGlow sUNUSED *para = (PocBitmapParaGlow *)(op->EditData); para;
  op->ArrayGroupMode = 0;
  para->Pos[0] = 0.500000f;
  para->Pos[1] = 0.500000f;
  para->Radius[0] = 0.500000f;
  para->Radius[1] = 0.500000f;
  para->Color = 0xffffffff;
  para->Alpha = 1.000000f;
  para->Power = 2.000000f;
}

void PocBitmapBindGlow(wCommand *cmd,ScriptContext *ctx)
{
  ScriptValue *val;
  val = ctx->MakeValue(ScriptTypeFloat,2);
  val->FloatPtr = ((sF32 *)cmd->Data)+0;
  ctx->BindLocal(ctx->AddSymbol(L"center"),val);
  val = ctx->MakeValue(ScriptTypeFloat,2);
  val->FloatPtr = ((sF32 *)cmd->Data)+0;
  ctx->BindLocal(ctx->AddSymbol(L"center"),val);
  val = ctx->MakeValue(ScriptTypeFloat,2);
  val->FloatPtr = ((sF32 *)cmd->Data)+2;
  ctx->BindLocal(ctx->AddSymbol(L"radius"),val);
  val = ctx->MakeValue(ScriptTypeFloat,2);
  val->FloatPtr = ((sF32 *)cmd->Data)+2;
  ctx->BindLocal(ctx->AddSymbol(L"radius"),val);
  val = ctx->MakeValue(ScriptTypeColor,1);
  val->ColorPtr = ((sU32 *)cmd->Data)+4;
  ctx->BindLocal(ctx->AddSymbol(L"color_"),val);
  val = ctx->MakeValue(ScriptTypeFloat,1);
  val->FloatPtr = ((sF32 *)cmd->Data)+5;
  ctx->BindLocal(ctx->AddSymbol(L"alpha"),val);
  val = ctx->MakeValue(ScriptTypeFloat,1);
  val->FloatPtr = ((sF32 *)cmd->Data)+6;
  ctx->BindLocal(ctx->AddSymbol(L"power"),val);
}
void PocBitmapBind2Glow(wCommand *cmd,ScriptContext *ctx)
{
  static sInt initdone = 0;
  static sPoolString name[5];
  if(!initdone)
  {
    initdone = 1; 
    name[0] = sPoolString(L"center");
    name[1] = sPoolString(L"radius");
    name[2] = sPoolString(L"color_");
    name[3] = sPoolString(L"alpha");
    name[4] = sPoolString(L"power");
  }
  ctx->AddImport(name[0],ScriptTypeFloat,2,cmd->Data+0);
  ctx->AddImport(name[1],ScriptTypeFloat,2,cmd->Data+2);
  ctx->AddImport(name[2],ScriptTypeColor,1,cmd->Data+4);
  ctx->AddImport(name[3],ScriptTypeFloat,1,cmd->Data+5);
  ctx->AddImport(name[4],ScriptTypeFloat,1,cmd->Data+6);
}
void PocBitmapBind3Glow(wOp *op,sTextBuffer &tb)
{
  tb.PrintF(L"  import center : float[2];\n");
  tb.PrintF(L"  import radius : float[2];\n");
  tb.PrintF(L"  import color_ : color;\n");
  tb.PrintF(L"  import alpha : float;\n");
  tb.PrintF(L"  import power : float;\n");
}
const sChar *PocBitmapWikiGlow =
L"= PocBitmap : Glow\n"
L"\n"
L"!t 2 : 2 3\n"
L" !T 2\n"
L"  !i Name\n"
L"  !i Glow\n"
L"\n"
L"  !i Output Type\n"
L"  !i PocBitmap\n"
L" !i\n"
L"\n"
L"== Inputs\n"
L"\n"
L"!T 3 : 1 1 3\n"
L" !\n"
L"  ! bc #c0c0c0\n"
L"  !i Type\n"
L"  !i Flags\n"
L"  !i Comment\n"
L" !i PocBitmap\n"
L" !i defaults to: Flat\n"
L" !i *\n"
L"\n"
L"== Parameters\n"
L"\n"
L"!T 4 : 1 1 1 2\n"
L" !\n"
L"  ! bc #c0c0c0\n"
L"  !i Screen Name\n"
L"  !i Script Name\n"
L"  !i Type\n"
L"  !i Comment\n"
L"\n"
L" !i Center\n"
L" !i Pos\n"
L" !i float[2]\n"
L" !i *\n"
L"\n"
L" !i Radius\n"
L" !i Radius\n"
L" !i float[2]\n"
L" !i *\n"
L"\n"
L" !i Color\n"
L" !i Color\n"
L" !i color\n"
L" !i *\n"
L"\n"
L" !i Alpha\n"
L" !i Alpha\n"
L" !i float\n"
L" !i *\n"
L"\n"
L" !i Power\n"
L" !i Power\n"
L" !i float\n"
L" !i *\n"
L"\n"
L"== Comments\n"
L"\n"
L"*\n"
L"\n"
L"== See Also\n"
L"\n"
L"\n"
;

/****************************************************************************/

sBool PocBitmapCmdAdd(wExecutive *exe,wCommand *cmd)
{
  PocBitmapParaAdd sUNUSED *para = (PocBitmapParaAdd *)(cmd->Data); para;
  PocBitmap sUNUSED *in0 = cmd->GetInput<PocBitmap *>(0); in0;
  PocBitmap sUNUSED *in1 = cmd->GetInput<PocBitmap *>(1); in1;
  PocBitmap *out = (PocBitmap *) cmd->Output;
  if(!out) { out=new PocBitmap; cmd->Output=out; }

  {
#line 145 "poc_ops.ops"

    if(out!=in0)
      out->CopyFrom(in0);
      
    for(sInt i=1;i<cmd->InputCount;i++)
    {
      PocBitmap *in = cmd->GetInput<PocBitmap *>(i);
      if(in)
      {
        if(in->Image->SizeX!=in0->Image->SizeX || in->Image->SizeY!=in0->Image->SizeY)
        {
          cmd->SetError(L"Input sizes don't match - all input images must have the same resolution.");
          return 0;      
        }

        switch(para->Mode)
        {
        case 0:
          out->Image->Add(in->Image);
          break;
        case 1:
          out->Image->Mul(in->Image);
          break;
        case 2:
          out->Image->AlphaFromLuminance(in->Image);
          break;
        case 3:
          out->Image->Blend(in->Image,sTRUE);
          break;
        case 4:
          out->Image->Blend(in->Image,sFALSE);
          break;
        }
      }
    }
    if(para->ResultMul != 0xffffffff)
      out->Image->Mul(para->ResultMul);
    return 1;
  ;
#line 666 "poc_ops.cpp"
    return 1;
  }
}

void PocBitmapGuiAdd(wGridFrameHelper &gh,wOp *op)
{
  PocBitmapParaAdd sUNUSED *para = (PocBitmapParaAdd *)(op->EditData); para;
  gh.Group(op->Class->Label);

  gh.Label(L"Mode");
  gh.Flags(&para->Mode,L"add|mul|lum2alpha|blend pmalpha|blend alpha",gh.ChangeMsg);

  gh.Label(L"ResultMul");
  gh.ColorPick(&para->ResultMul,L"rgba",0);
}

void PocBitmapDefAdd(wOp *op)
{
  PocBitmapParaAdd sUNUSED *para = (PocBitmapParaAdd *)(op->EditData); para;
  op->ArrayGroupMode = 0;
  para->ResultMul = 0xffffffff;
}

void PocBitmapBindAdd(wCommand *cmd,ScriptContext *ctx)
{
  ScriptValue *val;
  val = ctx->MakeValue(ScriptTypeColor,1);
  val->ColorPtr = ((sU32 *)cmd->Data)+1;
  ctx->BindLocal(ctx->AddSymbol(L"resultmul"),val);
}
void PocBitmapBind2Add(wCommand *cmd,ScriptContext *ctx)
{
  static sInt initdone = 0;
  static sPoolString name[2];
  if(!initdone)
  {
    initdone = 1; 
    name[0] = sPoolString(L"mode");
    name[1] = sPoolString(L"resultmul");
  }
  ctx->AddImport(name[1],ScriptTypeColor,1,cmd->Data+1);
}
void PocBitmapBind3Add(wOp *op,sTextBuffer &tb)
{
  tb.PrintF(L"  import resultmul : color;\n");
}
const sChar *PocBitmapWikiAdd =
L"= PocBitmap : Add\n"
L"\n"
L"!t 2 : 2 3\n"
L" !T 2\n"
L"  !i Name\n"
L"  !i Add\n"
L"\n"
L"  !i Output Type\n"
L"  !i PocBitmap\n"
L" !i\n"
L"\n"
L"== Inputs\n"
L"\n"
L"!T 3 : 1 1 3\n"
L" !\n"
L"  ! bc #c0c0c0\n"
L"  !i Type\n"
L"  !i Flags\n"
L"  !i Comment\n"
L" !i PocBitmap\n"
L" !i\n"
L" !i *\n"
L"\n"
L" !i PocBitmap\n"
L" !i multiple optional\n"
L" !i *\n"
L"\n"
L"== Parameters\n"
L"\n"
L"!T 4 : 1 1 1 2\n"
L" !\n"
L"  ! bc #c0c0c0\n"
L"  !i Screen Name\n"
L"  !i Script Name\n"
L"  !i Type\n"
L"  !i Comment\n"
L"\n"
L"!T 4 : 1 1 1 2\n"
L" !i Mode\n"
L" !i Mode\n"
L" !i add\n"
L" !i *\n"
L" !i \n"
L" !i \n"
L" !i mul\n"
L" !i *\n"
L" !i \n"
L" !i \n"
L" !i lum2alpha\n"
L" !i *\n"
L" !i \n"
L" !i \n"
L" !i blend pmalpha\n"
L" !i *\n"
L" !i \n"
L" !i \n"
L" !i blend alpha\n"
L" !i *\n"
L"!T 4 : 1 1 1 2\n"
L" !i ResultMul\n"
L" !i ResultMul\n"
L" !i color\n"
L" !i *\n"
L"\n"
L"== Comments\n"
L"\n"
L"*\n"
L"\n"
L"== See Also\n"
L"\n"
L"\n"
;

/****************************************************************************/

struct PocBitmapHelperMandelbrot
{
#line 237 "poc_ops.ops"
  sF32 cx;
#line 238 "poc_ops.ops"
  sF32 cy;
#line 239 "poc_ops.ops"
  sF32 sx;
#line 240 "poc_ops.ops"
  sF32 sy;
#line 241 "poc_ops.ops"
  sF32 ex;
#line 242 "poc_ops.ops"
  sF32 ey;
#line 243 "poc_ops.ops"
  sF32 fx;
#line 244 "poc_ops.ops"
  sF32 fy;
#line 245 "poc_ops.ops"
  sF32 CenterX;
#line 246 "poc_ops.ops"
  sF32 CenterY;
#line 247 "poc_ops.ops"
  sF32 SizeX;
#line 248 "poc_ops.ops"
  sF32 SizeY;
#line 816 "poc_ops.cpp"
};
sBool PocBitmapCmdMandelbrot(wExecutive *exe,wCommand *cmd)
{
  PocBitmapParaMandelbrot sUNUSED *para = (PocBitmapParaMandelbrot *)(cmd->Data); para;
  PocBitmap *out = (PocBitmap *) cmd->Output;
  if(!out) { out=new PocBitmap; cmd->Output=out; }

  {
#line 207 "poc_ops.ops"

    out->Image->Init(1<<para->SizeX,1<<para->SizeY);
    sU32 *data = out->Image->Data;
    for(sInt y=0;y<out->Image->SizeY;y++)
    {
      for(sInt x=0;x<out->Image->SizeX;x++)
      {
        sF32 fx = (x*2.0f/out->Image->SizeX-1.0f)*para->Size[0]+para->Center[0];
        sF32 fy = (y*2.0f/out->Image->SizeY-1.0f)*para->Size[1]+para->Center[1];
        
        sInt r = 0;
        sF32 ix,iy,tx,ty;
        ix = iy = 0;
        while(r<para->Depth && ix*ix+iy*iy<4)
        {
          tx = ix*ix-iy*iy+fx;
          ty = 2*ix*iy+fy;
          ix = tx;
          iy = ty;
          r++;
        }
        
        *data++ = sFadeColor(r*0x10000/para->Depth,para->Range0,para->Range1);
      }
    }
    return 1;
  ;
#line 852 "poc_ops.cpp"
    return 1;
  }
}

void PocBitmapHndMandelbrot(wPaintInfo &pi,wOp *op)
{
  PocBitmapParaMandelbrot sUNUSED *para = (PocBitmapParaMandelbrot *)(op->EditData); para;
  PocBitmapHelperMandelbrot *helper = (PocBitmapHelperMandelbrot *)(op->HelperData);
#line 252 "poc_ops.ops"

    sInt id = pi.FirstSelectedId(op);

    if(!pi.Dragging)
    {
      helper->cx = 0.5f;
      helper->cy = 0.5f;
      helper->sx = 0.125f;
      helper->sy = 0.125f;
      helper->ex = helper->cx + helper->sx;
      helper->ey = helper->cy + helper->sy;
      helper->CenterX = para->Center[0];
      helper->CenterY = para->Center[1];
      helper->SizeX = para->Size[0];
      helper->SizeY = para->Size[1];
    }

    switch(id)
    {
    default:
      helper->ex = helper->cx + helper->sx;
      helper->ey = helper->cy + helper->sy;
      break;
    case 1:
      helper->ex = helper->cx + helper->sx;
      helper->ey = helper->cy + helper->sy;
      para->Center[0] = helper->CenterX + (0.5f-helper->cx)*para->Size[0]*2;
      para->Center[1] = helper->CenterY + (0.5f-helper->cy)*para->Size[1]*2;
      break;
    case 2:
      helper->sx = sAbs(helper->ex - helper->cx);
      helper->sy = sAbs(helper->ey - helper->cy);
      break;
    case 3:
      helper->sx = helper->sy = sAbs(helper->ey - helper->cy);
      break;
    case 4:
      helper->sx = helper->sy = sAbs(helper->ex - helper->cx);
      break;
    }
    if(id==2 || id==3 || id==4)
    {
      if(helper->sx>0.01f && helper->sy>0.01f)
      {
        para->Size[0] = helper->SizeX * (0.125f/helper->sx);
        para->Size[1] = helper->SizeY * (0.125f/helper->sy);
      }
    }
    helper->fx = helper->cx;
    helper->fy = helper->cy;

    sF32 x0 = helper->cx - helper->sx;
    sF32 x1 = helper->cx + helper->sx;
    sF32 y0 = helper->cy - helper->sy;
    sF32 y1 = helper->cy + helper->sy;

    pi.HandleTex2D(op,1,helper->cx,helper->cy);
    pi.HandleTex2D(op,2,helper->ex,helper->ey);
    pi.HandleTex2D(op,3,helper->fx,helper->ey);
    pi.HandleTex2D(op,4,helper->ex,helper->fy);
    pi.LineTex2D(x0,y0,x0,y1);
    pi.LineTex2D(x0,y1,x1,y1);
    pi.LineTex2D(x1,y1,x1,y0);
    pi.LineTex2D(x1,y0,x0,y0);
  ;
#line 927 "poc_ops.cpp"
}

void PocBitmapGuiMandelbrot(wGridFrameHelper &gh,wOp *op)
{
  PocBitmapParaMandelbrot sUNUSED *para = (PocBitmapParaMandelbrot *)(op->EditData); para;
  gh.Group(op->Class->Label);

  gh.Label(L"Size");

  gh.Flags(&para->SizeX,L" 1| 2| 4| 8| 16| 32| 64| 128| 256| 512| 1024| 2048",gh.ChangeMsg);

  gh.Flags(&para->SizeY,L" 1| 2| 4| 8| 16| 32| 64| 128| 256| 512| 1024| 2048",gh.ChangeMsg);

  gh.Label(L"Depth");
  sIntControl *int_Depth = gh.Int(&para->Depth,1,512,0.125000f);
  int_Depth->Default = 0x00000010; int_Depth->RightStep = 0.125000f;

  gh.Label(L"Center");
  gh.BeginTied();
  sFloatControl *float_Center_0 = gh.Float(&para->Center[0],-16.0000f,16.00000f,0.000100f);
  float_Center_0->Default = -1.00000f; float_Center_0->RightStep = 0.125000f;
  sFloatControl *float_Center_1 = gh.Float(&para->Center[1],-16.0000f,16.00000f,0.000100f);
  float_Center_1->Default = 0.000000f; float_Center_1->RightStep = 0.125000f;
  gh.EndTied();

  gh.Label(L"Size");
  gh.BeginTied();
  sFloatControl *float_Size_0 = gh.Float(&para->Size[0],0.000000f,16.00000f,0.000100f);
  float_Size_0->Default = 0.500000f; float_Size_0->RightStep = 0.125000f;
  sFloatControl *float_Size_1 = gh.Float(&para->Size[1],0.000000f,16.00000f,0.000100f);
  float_Size_1->Default = 0.500000f; float_Size_1->RightStep = 0.125000f;
  gh.EndTied();

  gh.Label(L"Range0");
  gh.ColorPick(&para->Range0,L"rgba",0);

  gh.Label(L"Range1");
  gh.ColorPick(&para->Range1,L"rgba",0);
}

void PocBitmapDefMandelbrot(wOp *op)
{
  PocBitmapParaMandelbrot sUNUSED *para = (PocBitmapParaMandelbrot *)(op->EditData); para;
  op->ArrayGroupMode = 0;
  para->SizeX = 0x00000008;
  para->SizeY = 0x00000008;
  para->Depth = 0x00000010;
  para->Center[0] = -1.00000f;
  para->Size[0] = 0.500000f;
  para->Size[1] = 0.500000f;
  para->Range0 = 0xffffffff;
  para->Range1 = 0xff000000;
}

void PocBitmapBindMandelbrot(wCommand *cmd,ScriptContext *ctx)
{
  ScriptValue *val;
  val = ctx->MakeValue(ScriptTypeInt,1);
  val->IntPtr = ((sInt *)cmd->Data)+2;
  ctx->BindLocal(ctx->AddSymbol(L"depth"),val);
  val = ctx->MakeValue(ScriptTypeFloat,2);
  val->FloatPtr = ((sF32 *)cmd->Data)+3;
  ctx->BindLocal(ctx->AddSymbol(L"center"),val);
  val = ctx->MakeValue(ScriptTypeFloat,2);
  val->FloatPtr = ((sF32 *)cmd->Data)+3;
  ctx->BindLocal(ctx->AddSymbol(L"center"),val);
  val = ctx->MakeValue(ScriptTypeFloat,2);
  val->FloatPtr = ((sF32 *)cmd->Data)+5;
  ctx->BindLocal(ctx->AddSymbol(L"size"),val);
  val = ctx->MakeValue(ScriptTypeFloat,2);
  val->FloatPtr = ((sF32 *)cmd->Data)+5;
  ctx->BindLocal(ctx->AddSymbol(L"size"),val);
  val = ctx->MakeValue(ScriptTypeColor,1);
  val->ColorPtr = ((sU32 *)cmd->Data)+7;
  ctx->BindLocal(ctx->AddSymbol(L"range0"),val);
  val = ctx->MakeValue(ScriptTypeColor,1);
  val->ColorPtr = ((sU32 *)cmd->Data)+8;
  ctx->BindLocal(ctx->AddSymbol(L"range1"),val);
}
void PocBitmapBind2Mandelbrot(wCommand *cmd,ScriptContext *ctx)
{
  static sInt initdone = 0;
  static sPoolString name[8];
  if(!initdone)
  {
    initdone = 1; 
    name[0] = sPoolString(L"size");
    name[1] = sPoolString(L"sizex");
    name[2] = sPoolString(L"sizey");
    name[3] = sPoolString(L"depth");
    name[4] = sPoolString(L"center");
    name[5] = sPoolString(L"size");
    name[6] = sPoolString(L"range0");
    name[7] = sPoolString(L"range1");
  }
  ctx->AddImport(name[3],ScriptTypeInt,1,cmd->Data+2);
  ctx->AddImport(name[4],ScriptTypeFloat,2,cmd->Data+3);
  ctx->AddImport(name[5],ScriptTypeFloat,2,cmd->Data+5);
  ctx->AddImport(name[6],ScriptTypeColor,1,cmd->Data+7);
  ctx->AddImport(name[7],ScriptTypeColor,1,cmd->Data+8);
}
void PocBitmapBind3Mandelbrot(wOp *op,sTextBuffer &tb)
{
  tb.PrintF(L"  import depth : int;\n");
  tb.PrintF(L"  import center : float[2];\n");
  tb.PrintF(L"  import size : float[2];\n");
  tb.PrintF(L"  import range0 : color;\n");
  tb.PrintF(L"  import range1 : color;\n");
}
const sChar *PocBitmapWikiMandelbrot =
L"= PocBitmap : Mandelbrot\n"
L"\n"
L"!t 2 : 2 3\n"
L" !T 2\n"
L"  !i Name\n"
L"  !i Mandelbrot\n"
L"\n"
L"  !i Output Type\n"
L"  !i PocBitmap\n"
L" !i\n"
L"\n"
L"== Parameters\n"
L"\n"
L"!T 4 : 1 1 1 2\n"
L" !\n"
L"  ! bc #c0c0c0\n"
L"  !i Screen Name\n"
L"  !i Script Name\n"
L"  !i Type\n"
L"  !i Comment\n"
L"\n"
L"!T 4 : 1 1 1 2\n"
L" !i Size\n"
L" !i SizeX\n"
L" !i 1\n"
L" !i *\n"
L" !i \n"
L" !i \n"
L" !i 2\n"
L" !i *\n"
L" !i \n"
L" !i \n"
L" !i 4\n"
L" !i *\n"
L" !i \n"
L" !i \n"
L" !i 8\n"
L" !i *\n"
L" !i \n"
L" !i \n"
L" !i 16\n"
L" !i *\n"
L" !i \n"
L" !i \n"
L" !i 32\n"
L" !i *\n"
L" !i \n"
L" !i \n"
L" !i 64\n"
L" !i *\n"
L" !i \n"
L" !i \n"
L" !i 128\n"
L" !i *\n"
L" !i \n"
L" !i \n"
L" !i 256\n"
L" !i *\n"
L" !i \n"
L" !i \n"
L" !i 512\n"
L" !i *\n"
L" !i \n"
L" !i \n"
L" !i 1024\n"
L" !i *\n"
L" !i \n"
L" !i \n"
L" !i 2048\n"
L" !i *\n"
L"!T 4 : 1 1 1 2\n"
L" !i <NULL>\n"
L" !i SizeY\n"
L" !i 1\n"
L" !i *\n"
L" !i \n"
L" !i \n"
L" !i 2\n"
L" !i *\n"
L" !i \n"
L" !i \n"
L" !i 4\n"
L" !i *\n"
L" !i \n"
L" !i \n"
L" !i 8\n"
L" !i *\n"
L" !i \n"
L" !i \n"
L" !i 16\n"
L" !i *\n"
L" !i \n"
L" !i \n"
L" !i 32\n"
L" !i *\n"
L" !i \n"
L" !i \n"
L" !i 64\n"
L" !i *\n"
L" !i \n"
L" !i \n"
L" !i 128\n"
L" !i *\n"
L" !i \n"
L" !i \n"
L" !i 256\n"
L" !i *\n"
L" !i \n"
L" !i \n"
L" !i 512\n"
L" !i *\n"
L" !i \n"
L" !i \n"
L" !i 1024\n"
L" !i *\n"
L" !i \n"
L" !i \n"
L" !i 2048\n"
L" !i *\n"
L"!T 4 : 1 1 1 2\n"
L" !i Depth\n"
L" !i Depth\n"
L" !i int\n"
L" !i *\n"
L"\n"
L" !i Center\n"
L" !i Center\n"
L" !i float[2]\n"
L" !i *\n"
L"\n"
L" !i Size\n"
L" !i Size\n"
L" !i float[2]\n"
L" !i *\n"
L"\n"
L" !i Range0\n"
L" !i Range0\n"
L" !i color\n"
L" !i *\n"
L"\n"
L" !i Range1\n"
L" !i Range1\n"
L" !i color\n"
L" !i *\n"
L"\n"
L"== Comments\n"
L"\n"
L"*\n"
L"\n"
L"== See Also\n"
L"\n"
L"\n"
;

/****************************************************************************/

sBool PocBitmapCmdPerlin(wExecutive *exe,wCommand *cmd)
{
  PocBitmapParaPerlin sUNUSED *para = (PocBitmapParaPerlin *)(cmd->Data); para;
  PocBitmap *out = (PocBitmap *) cmd->Output;
  if(!out) { out=new PocBitmap; cmd->Output=out; }

  {
#line 341 "poc_ops.ops"

    out->Image->Init(1<<para->SizeX,1<<para->SizeY);
    sU32 *data = out->Image->Data;
    for(sInt y=0;y<out->Image->SizeY;y++)
    {
      for(sInt x=0;x<out->Image->SizeX;x++)
      {
        sF32 fx = x*1.0f/out->Image->SizeX;
        sF32 fy = y*1.0f/out->Image->SizeY;
        sF32 f = 0;
        sF32 e = 1;
        for(sInt i=para->Frequency;i<para->Frequency+para->Octaves;i++)
        {
          sF32 r = sPerlin2D(sInt(fx*(0x10000<<i)),sInt(fy*(0x10000<<i)),(1<<i)-1,para->Seed+i);
          if(para->Mode&2)
            r = sFSin(r*sPI2F);
          if(para->Mode&1)
            r = sFAbs(r)*2-1;
          f+=r*e;
          e*=para->Falloff;
        }
        f = f*0.5f+0.5f;
        
        *data++ = sFadeColor(sClamp(sInt(f*0x10000*para->Amplify),0,0x10000),para->Color0,para->Color1);
      }
    }
    return 1;
  ;
#line 1230 "poc_ops.cpp"
    return 1;
  }
}

void PocBitmapGuiPerlin(wGridFrameHelper &gh,wOp *op)
{
  PocBitmapParaPerlin sUNUSED *para = (PocBitmapParaPerlin *)(op->EditData); para;
  gh.Group(op->Class->Label);

  gh.Label(L"Size");

  gh.Flags(&para->SizeX,L" 1| 2| 4| 8| 16| 32| 64| 128| 256| 512| 1024| 2048",gh.ChangeMsg);

  gh.Flags(&para->SizeY,L" 1| 2| 4| 8| 16| 32| 64| 128| 256| 512| 1024| 2048",gh.ChangeMsg);

  gh.Label(L"Frequency");
  sIntControl *int_Frequency = gh.Int(&para->Frequency,0,15,0.125000f);
  int_Frequency->Default = 0x00000002; int_Frequency->RightStep = 0.125000f;

  gh.Label(L"Octaves");
  sIntControl *int_Octaves = gh.Int(&para->Octaves,1,15,0.125000f);
  int_Octaves->Default = 0x00000002; int_Octaves->RightStep = 0.125000f;

  gh.Label(L"Falloff");
  sFloatControl *float_Falloff = gh.Float(&para->Falloff,-4.00000f,4.000000f,0.010000f);
  float_Falloff->Default = 1.000000f; float_Falloff->RightStep = 0.125000f;

  gh.Label(L"Amplify");
  sFloatControl *float_Amplify = gh.Float(&para->Amplify,0.000000f,4.000000f,0.010000f);
  float_Amplify->Default = 1.000000f; float_Amplify->RightStep = 0.125000f;

  gh.Label(L"Mode");
  gh.Flags(&para->Mode,L"direct|abs|sin",gh.ChangeMsg);

  gh.Label(L"Seed");
  sIntControl *int_Seed = gh.Int(&para->Seed,0,255,0.125000f);
  int_Seed->Default = 0x00000000; int_Seed->RightStep = 0.125000f;

  gh.Label(L"Color0");
  gh.ColorPick(&para->Color0,L"rgba",0);

  gh.Label(L"Color1");
  gh.ColorPick(&para->Color1,L"rgba",0);
}

void PocBitmapDefPerlin(wOp *op)
{
  PocBitmapParaPerlin sUNUSED *para = (PocBitmapParaPerlin *)(op->EditData); para;
  op->ArrayGroupMode = 0;
  para->SizeX = 0x00000008;
  para->SizeY = 0x00000008;
  para->Frequency = 0x00000002;
  para->Octaves = 0x00000002;
  para->Falloff = 1.000000f;
  para->Amplify = 1.000000f;
  para->Color0 = 0xff000000;
  para->Color1 = 0xffffffff;
}

void PocBitmapBindPerlin(wCommand *cmd,ScriptContext *ctx)
{
  ScriptValue *val;
  val = ctx->MakeValue(ScriptTypeInt,1);
  val->IntPtr = ((sInt *)cmd->Data)+2;
  ctx->BindLocal(ctx->AddSymbol(L"frequency"),val);
  val = ctx->MakeValue(ScriptTypeInt,1);
  val->IntPtr = ((sInt *)cmd->Data)+3;
  ctx->BindLocal(ctx->AddSymbol(L"octaves"),val);
  val = ctx->MakeValue(ScriptTypeFloat,1);
  val->FloatPtr = ((sF32 *)cmd->Data)+4;
  ctx->BindLocal(ctx->AddSymbol(L"falloff"),val);
  val = ctx->MakeValue(ScriptTypeFloat,1);
  val->FloatPtr = ((sF32 *)cmd->Data)+5;
  ctx->BindLocal(ctx->AddSymbol(L"amplify"),val);
  val = ctx->MakeValue(ScriptTypeInt,1);
  val->IntPtr = ((sInt *)cmd->Data)+7;
  ctx->BindLocal(ctx->AddSymbol(L"seed"),val);
  val = ctx->MakeValue(ScriptTypeColor,1);
  val->ColorPtr = ((sU32 *)cmd->Data)+8;
  ctx->BindLocal(ctx->AddSymbol(L"color0"),val);
  val = ctx->MakeValue(ScriptTypeColor,1);
  val->ColorPtr = ((sU32 *)cmd->Data)+9;
  ctx->BindLocal(ctx->AddSymbol(L"color1"),val);
}
void PocBitmapBind2Perlin(wCommand *cmd,ScriptContext *ctx)
{
  static sInt initdone = 0;
  static sPoolString name[11];
  if(!initdone)
  {
    initdone = 1; 
    name[0] = sPoolString(L"size");
    name[1] = sPoolString(L"sizex");
    name[2] = sPoolString(L"sizey");
    name[3] = sPoolString(L"frequency");
    name[4] = sPoolString(L"octaves");
    name[5] = sPoolString(L"falloff");
    name[6] = sPoolString(L"amplify");
    name[7] = sPoolString(L"mode");
    name[8] = sPoolString(L"seed");
    name[9] = sPoolString(L"color0");
    name[10] = sPoolString(L"color1");
  }
  ctx->AddImport(name[3],ScriptTypeInt,1,cmd->Data+2);
  ctx->AddImport(name[4],ScriptTypeInt,1,cmd->Data+3);
  ctx->AddImport(name[5],ScriptTypeFloat,1,cmd->Data+4);
  ctx->AddImport(name[6],ScriptTypeFloat,1,cmd->Data+5);
  ctx->AddImport(name[8],ScriptTypeInt,1,cmd->Data+7);
  ctx->AddImport(name[9],ScriptTypeColor,1,cmd->Data+8);
  ctx->AddImport(name[10],ScriptTypeColor,1,cmd->Data+9);
}
void PocBitmapBind3Perlin(wOp *op,sTextBuffer &tb)
{
  tb.PrintF(L"  import frequency : int;\n");
  tb.PrintF(L"  import octaves : int;\n");
  tb.PrintF(L"  import falloff : float;\n");
  tb.PrintF(L"  import amplify : float;\n");
  tb.PrintF(L"  import seed : int;\n");
  tb.PrintF(L"  import color0 : color;\n");
  tb.PrintF(L"  import color1 : color;\n");
}
const sChar *PocBitmapWikiPerlin =
L"= PocBitmap : Perlin\n"
L"\n"
L"!t 2 : 2 3\n"
L" !T 2\n"
L"  !i Name\n"
L"  !i Perlin\n"
L"\n"
L"  !i Output Type\n"
L"  !i PocBitmap\n"
L" !i\n"
L"\n"
L"== Parameters\n"
L"\n"
L"!T 4 : 1 1 1 2\n"
L" !\n"
L"  ! bc #c0c0c0\n"
L"  !i Screen Name\n"
L"  !i Script Name\n"
L"  !i Type\n"
L"  !i Comment\n"
L"\n"
L"!T 4 : 1 1 1 2\n"
L" !i Size\n"
L" !i SizeX\n"
L" !i 1\n"
L" !i *\n"
L" !i \n"
L" !i \n"
L" !i 2\n"
L" !i *\n"
L" !i \n"
L" !i \n"
L" !i 4\n"
L" !i *\n"
L" !i \n"
L" !i \n"
L" !i 8\n"
L" !i *\n"
L" !i \n"
L" !i \n"
L" !i 16\n"
L" !i *\n"
L" !i \n"
L" !i \n"
L" !i 32\n"
L" !i *\n"
L" !i \n"
L" !i \n"
L" !i 64\n"
L" !i *\n"
L" !i \n"
L" !i \n"
L" !i 128\n"
L" !i *\n"
L" !i \n"
L" !i \n"
L" !i 256\n"
L" !i *\n"
L" !i \n"
L" !i \n"
L" !i 512\n"
L" !i *\n"
L" !i \n"
L" !i \n"
L" !i 1024\n"
L" !i *\n"
L" !i \n"
L" !i \n"
L" !i 2048\n"
L" !i *\n"
L"!T 4 : 1 1 1 2\n"
L" !i <NULL>\n"
L" !i SizeY\n"
L" !i 1\n"
L" !i *\n"
L" !i \n"
L" !i \n"
L" !i 2\n"
L" !i *\n"
L" !i \n"
L" !i \n"
L" !i 4\n"
L" !i *\n"
L" !i \n"
L" !i \n"
L" !i 8\n"
L" !i *\n"
L" !i \n"
L" !i \n"
L" !i 16\n"
L" !i *\n"
L" !i \n"
L" !i \n"
L" !i 32\n"
L" !i *\n"
L" !i \n"
L" !i \n"
L" !i 64\n"
L" !i *\n"
L" !i \n"
L" !i \n"
L" !i 128\n"
L" !i *\n"
L" !i \n"
L" !i \n"
L" !i 256\n"
L" !i *\n"
L" !i \n"
L" !i \n"
L" !i 512\n"
L" !i *\n"
L" !i \n"
L" !i \n"
L" !i 1024\n"
L" !i *\n"
L" !i \n"
L" !i \n"
L" !i 2048\n"
L" !i *\n"
L"!T 4 : 1 1 1 2\n"
L" !i Frequency\n"
L" !i Frequency\n"
L" !i int\n"
L" !i *\n"
L"\n"
L" !i Octaves\n"
L" !i Octaves\n"
L" !i int\n"
L" !i *\n"
L"\n"
L" !i Falloff\n"
L" !i Falloff\n"
L" !i float\n"
L" !i *\n"
L"\n"
L" !i Amplify\n"
L" !i Amplify\n"
L" !i float\n"
L" !i *\n"
L"\n"
L"!T 4 : 1 1 1 2\n"
L" !i Mode\n"
L" !i Mode\n"
L" !i direct\n"
L" !i *\n"
L" !i \n"
L" !i \n"
L" !i abs\n"
L" !i *\n"
L" !i \n"
L" !i \n"
L" !i sin\n"
L" !i *\n"
L"!T 4 : 1 1 1 2\n"
L" !i Seed\n"
L" !i Seed\n"
L" !i int\n"
L" !i *\n"
L"\n"
L" !i Color0\n"
L" !i Color0\n"
L" !i color\n"
L" !i *\n"
L"\n"
L" !i Color1\n"
L" !i Color1\n"
L" !i color\n"
L" !i *\n"
L"\n"
L"== Comments\n"
L"\n"
L"*\n"
L"\n"
L"== See Also\n"
L"\n"
L"\n"
;

/****************************************************************************/

sBool PocBitmapCmdNormals(wExecutive *exe,wCommand *cmd)
{
  PocBitmapParaNormals sUNUSED *para = (PocBitmapParaNormals *)(cmd->Data); para;
  PocBitmap sUNUSED *in0 = cmd->GetInput<PocBitmap *>(0); in0;
  PocBitmap *out = (PocBitmap *) cmd->Output;
  if(!out) { out=new PocBitmap; cmd->Output=out; }

  {
#line 381 "poc_ops.ops"

    sInt xs = in0->Image->SizeX;
    sInt ys = in0->Image->SizeY;
    out->Image->Init(xs,ys);
    sU32 *d = out->Image->Data;
    sU32 *s = in0->Image->Data;

    sVector30 n;
    sInt dx,dy;
    sF32 strength = para->Strength*255*6;
    for(sInt y=0;y<out->Image->SizeY;y++)
    {
      for(sInt x=0;x<out->Image->SizeX;x++)
      {
        dx = 1*(s[((x+2)&(xs-1))+y*xs]&0xff)
           + 3*(s[((x+1)&(xs-1))+y*xs]&0xff)
           - 3*(s[((x-1)&(xs-1))+y*xs]&0xff)
           - 1*(s[((x-2)&(xs-1))+y*xs]&0xff);
        dy = 1*(s[((y+2)&(ys-1))*xs+x]&0xff)
           + 3*(s[((y+1)&(ys-1))*xs+x]&0xff)
           - 3*(s[((y-1)&(ys-1))*xs+x]&0xff)
           - 1*(s[((y-2)&(ys-1))*xs+x]&0xff);

        n.x = sF32(dx);
        n.y = sF32(dy);
        n.z = strength;
        n.Unit();

        *d++ = 0xff000000 
             | (sClamp(sInt(n.x*0x80+0x80),0,0xff)<<16)
             | (sClamp(sInt(n.y*0x80+0x80),0,0xff)<<8)
             | (sClamp(sInt(n.z*0x80+0x80),0,0xff));
      }
    }
    return 1;
  ;
#line 1578 "poc_ops.cpp"
    return 1;
  }
}

void PocBitmapGuiNormals(wGridFrameHelper &gh,wOp *op)
{
  PocBitmapParaNormals sUNUSED *para = (PocBitmapParaNormals *)(op->EditData); para;
  gh.Group(op->Class->Label);

  gh.Label(L"Strength");
  sFloatControl *float_Strength = gh.Float(&para->Strength,0.000000f,16.00000f,0.001000f);
  float_Strength->Default = 1.000000f; float_Strength->RightStep = 0.125000f;
}

void PocBitmapDefNormals(wOp *op)
{
  PocBitmapParaNormals sUNUSED *para = (PocBitmapParaNormals *)(op->EditData); para;
  op->ArrayGroupMode = 0;
  para->Strength = 1.000000f;
}

void PocBitmapBindNormals(wCommand *cmd,ScriptContext *ctx)
{
  ScriptValue *val;
  val = ctx->MakeValue(ScriptTypeFloat,1);
  val->FloatPtr = ((sF32 *)cmd->Data)+0;
  ctx->BindLocal(ctx->AddSymbol(L"strength"),val);
}
void PocBitmapBind2Normals(wCommand *cmd,ScriptContext *ctx)
{
  static sInt initdone = 0;
  static sPoolString name[1];
  if(!initdone)
  {
    initdone = 1; 
    name[0] = sPoolString(L"strength");
  }
  ctx->AddImport(name[0],ScriptTypeFloat,1,cmd->Data+0);
}
void PocBitmapBind3Normals(wOp *op,sTextBuffer &tb)
{
  tb.PrintF(L"  import strength : float;\n");
}
const sChar *PocBitmapWikiNormals =
L"= PocBitmap : Normals\n"
L"\n"
L"!t 2 : 2 3\n"
L" !T 2\n"
L"  !i Name\n"
L"  !i Normals\n"
L"\n"
L"  !i Output Type\n"
L"  !i PocBitmap\n"
L" !i\n"
L"\n"
L"== Inputs\n"
L"\n"
L"!T 3 : 1 1 3\n"
L" !\n"
L"  ! bc #c0c0c0\n"
L"  !i Type\n"
L"  !i Flags\n"
L"  !i Comment\n"
L" !i PocBitmap\n"
L" !i\n"
L" !i *\n"
L"\n"
L"== Parameters\n"
L"\n"
L"!T 4 : 1 1 1 2\n"
L" !\n"
L"  ! bc #c0c0c0\n"
L"  !i Screen Name\n"
L"  !i Script Name\n"
L"  !i Type\n"
L"  !i Comment\n"
L"\n"
L" !i Strength\n"
L" !i Strength\n"
L" !i float\n"
L" !i *\n"
L"\n"
L"== Comments\n"
L"\n"
L"*\n"
L"\n"
L"== See Also\n"
L"\n"
L"\n"
;

/****************************************************************************/

sBool PocBitmapCmdImport(wExecutive *exe,wCommand *cmd)
{
  PocBitmapParaImport sUNUSED *para = (PocBitmapParaImport *)(cmd->Data); para;
  PocBitmap *out = (PocBitmap *) cmd->Output;
  if(!out) { out=new PocBitmap; cmd->Output=out; }

  {
#line 430 "poc_ops.ops"

    if(out->Image->Load(cmd->Strings[0]))
    {
      if((sIsPower2(out->Image->SizeX) && sIsPower2(out->Image->SizeY)) || (para->Flags&1))
        return 1;
      else
        cmd->SetError(L"Image dimensions not power of two");
    }
    else
      cmd->SetError(L"Couldn't load image!");

    return 0;
  ;
#line 1693 "poc_ops.cpp"
    return 1;
  }
}

void PocBitmapGuiImport(wGridFrameHelper &gh,wOp *op)
{
  PocBitmapParaImport sUNUSED *para = (PocBitmapParaImport *)(op->EditData); para;
  gh.Group(op->Class->Label);

  gh.Label(L"Filename");
  {
    sControl *con = gh.String(op->EditString[0]);
    con->DoneMsg = con->ChangeMsg;
    con->ChangeMsg = sMessage();
    gh.FileLoadDialogMsg.Code = 0;
    gh.Box(L"...",gh.FileLoadDialogMsg);
    gh.Box(L"reload",gh.FileReloadMsg);
  }

  gh.Label(L"Flags");
  gh.Flags(&para->Flags,L"-|Allow NPOT",gh.ChangeMsg);
}

void PocBitmapDefImport(wOp *op)
{
  PocBitmapParaImport sUNUSED *para = (PocBitmapParaImport *)(op->EditData); para;
  op->ArrayGroupMode = 0;
}

void PocBitmapBindImport(wCommand *cmd,ScriptContext *ctx)
{
  ScriptValue *val;
  val = ctx->MakeValue(ScriptTypeString,1);
  val->StringPtr = ((sPoolString *)cmd->Strings)+0;
  ctx->BindLocal(ctx->AddSymbol(L"filename"),val);
}
void PocBitmapBind2Import(wCommand *cmd,ScriptContext *ctx)
{
  static sInt initdone = 0;
  static sPoolString name[2];
  if(!initdone)
  {
    initdone = 1; 
    name[0] = sPoolString(L"filename");
    name[1] = sPoolString(L"flags");
  }
  ctx->AddImport(name[0],ScriptTypeString,1,cmd->Strings+0);
}
void PocBitmapBind3Import(wOp *op,sTextBuffer &tb)
{
  tb.PrintF(L"  import filename : string;\n");
}
const sChar *PocBitmapWikiImport =
L"= PocBitmap : Import\n"
L"\n"
L"!t 2 : 2 3\n"
L" !T 2\n"
L"  !i Name\n"
L"  !i Import\n"
L"\n"
L"  !i Output Type\n"
L"  !i PocBitmap\n"
L" !i\n"
L"\n"
L"== Parameters\n"
L"\n"
L"!T 4 : 1 1 1 2\n"
L" !\n"
L"  ! bc #c0c0c0\n"
L"  !i Screen Name\n"
L"  !i Script Name\n"
L"  !i Type\n"
L"  !i Comment\n"
L"\n"
L" !i Filename\n"
L" !i Filename\n"
L" !i load file\n"
L" !i *\n"
L"\n"
L"!T 4 : 1 1 1 2\n"
L" !i Flags\n"
L" !i Flags\n"
L" !i Allow NPOT\n"
L" !i *\n"
L"== Comments\n"
L"\n"
L"*\n"
L"\n"
L"== See Also\n"
L"\n"
L"\n"
;

/****************************************************************************/

sBool PocBitmapCmdRotZoom(wExecutive *exe,wCommand *cmd)
{
  PocBitmapParaRotZoom sUNUSED *para = (PocBitmapParaRotZoom *)(cmd->Data); para;
  PocBitmap sUNUSED *in0 = cmd->GetInput<PocBitmap *>(0); in0;
  PocBitmap *out = (PocBitmap *) cmd->Output;
  if(!out) { out=new PocBitmap; cmd->Output=out; }

  {
#line 462 "poc_ops.ops"

    sU32 *d;
    sInt xs,ys;

    xs = para->SizeX ? 1<<(para->SizeX-1) : in0->Image->SizeX;
    ys = para->SizeY ? 1<<(para->SizeY-1) : in0->Image->SizeY;
    out->Image->Init(xs,ys);

    // das hier war ryg.
    // ryg sez: hardgecodete matrix-mathematik, und dann auch noch
    // ohne danebenzuschreiben, was genau da eigentlich in welchem
    // koordinatensystem ausgerechnet werden soll? wtf?
    sMatrix34 pretrans,rot,scale,posttrans;
    pretrans.l.Init(-para->Center[0],-para->Center[1],0.0f);
    posttrans.l.Init(para->Center[0]+para->Scroll[0]-0.5f,para->Center[1]+para->Scroll[1]-0.5f,0.0f);
    rot.EulerXYZ(0.0f,0.0f,para->Angle*sPI2F);
    scale.Scale(para->Zoom[0],para->Zoom[1],1.0f);

    sMatrix34 trafo = pretrans*rot*scale*posttrans;

    d = out->Image->Data;
    for(sInt y=0;y<out->Image->SizeY;y++)
    {
      sF32 v = (y + 0.5f) / out->Image->SizeY; // pixel center

      for(sInt x=0;x<out->Image->SizeX;x++)
      {
        sF32 u = (x + 0.5f) / out->Image->SizeX; // pixel center

        sInt su = sInt((u*trafo.i.x + v*trafo.j.x + trafo.l.x) * 256 * xs - 128); // -128: pixel center
        sInt sv = sInt((u*trafo.i.y + v*trafo.j.y + trafo.l.y) * 256 * ys - 128); // -128: pixel center
        *d++ = in0->Image->Filter(su,sv);
      }
    }

    //sInt x0,x1,x2,y0,y1,y2;
    //sF32 s,c;
    //s = sFSin(para->Angle*sPI2F);
    //c = sFCos(para->Angle*sPI2F);

    //sF32 cx = para->Center[0];
    //sF32 cy = para->Center[1];
    //sF32 sx = para->Scroll[0];
    //sF32 sy = para->Scroll[1];

    //x0 = sInt( c*para->Zoom[0]*256*in0->Image->SizeX/xs);
    //x1 = sInt( s*para->Zoom[0]*256*in0->Image->SizeX/ys);
    //y0 = sInt(-s*para->Zoom[1]*256*in0->Image->SizeY/xs);
    //y1 = sInt( c*para->Zoom[1]*256*in0->Image->SizeY/ys);

    //x2 = sInt(-xs*cx*x0 + ys*cy*x1);
    //y2 = sInt(-xs*cx*y0 + ys*cy*y1);
    //x2 += sInt(256*in0->Image->SizeX*sx);
    //y2 += sInt(256*in0->Image->SizeY*sy);

    //d = out->Image->Data;
    //for(sInt y=0;y<out->Image->SizeY;y++)
    //  for(sInt x=0;x<out->Image->SizeX;x++)
    //    *d++ = in0->Image->Filter(x*x0+y*x1+x2,x*y0+y*y1+y2);
  ;
#line 1858 "poc_ops.cpp"
    return 1;
  }
}

void PocBitmapGuiRotZoom(wGridFrameHelper &gh,wOp *op)
{
  PocBitmapParaRotZoom sUNUSED *para = (PocBitmapParaRotZoom *)(op->EditData); para;
  gh.Group(op->Class->Label);

  gh.Label(L"Size");

  gh.Flags(&para->SizeX,L"same| 1| 2| 4| 8| 16| 32| 64| 128| 256| 512| 1024| 2048",gh.ChangeMsg);

  gh.Flags(&para->SizeY,L"same| 1| 2| 4| 8| 16| 32| 64| 128| 256| 512| 1024| 2048",gh.ChangeMsg);

  gh.Label(L"Center");
  gh.BeginTied();
  sFloatControl *float_Center_0 = gh.Float(&para->Center[0],-16.0000f,16.00000f,0.001000f);
  float_Center_0->Default = 0.500000f; float_Center_0->RightStep = 0.125000f;
  sFloatControl *float_Center_1 = gh.Float(&para->Center[1],-16.0000f,16.00000f,0.001000f);
  float_Center_1->Default = 0.500000f; float_Center_1->RightStep = 0.125000f;
  gh.EndTied();

  gh.Label(L"Zoom");
  gh.BeginTied();
  sFloatControl *float_Zoom_0 = gh.Float(&para->Zoom[0],-1024.00f,1024.000f,0.010000f);
  float_Zoom_0->Default = 1.000000f; float_Zoom_0->RightStep = 0.125000f;
  sFloatControl *float_Zoom_1 = gh.Float(&para->Zoom[1],-1024.00f,1024.000f,0.010000f);
  float_Zoom_1->Default = 1.000000f; float_Zoom_1->RightStep = 0.125000f;
  gh.EndTied();

  gh.Label(L"Angle");
  sFloatControl *float_Angle = gh.Float(&para->Angle,-16.0000f,16.00000f,0.010000f);
  float_Angle->Default = 0.000000f; float_Angle->RightStep = 0.125000f;

  gh.Label(L"Scroll");
  gh.BeginTied();
  sFloatControl *float_Scroll_0 = gh.Float(&para->Scroll[0],-16.0000f,16.00000f,0.001000f);
  float_Scroll_0->Default = 0.500000f; float_Scroll_0->RightStep = 0.125000f;
  sFloatControl *float_Scroll_1 = gh.Float(&para->Scroll[1],-16.0000f,16.00000f,0.001000f);
  float_Scroll_1->Default = 0.500000f; float_Scroll_1->RightStep = 0.125000f;
  gh.EndTied();
}

void PocBitmapDefRotZoom(wOp *op)
{
  PocBitmapParaRotZoom sUNUSED *para = (PocBitmapParaRotZoom *)(op->EditData); para;
  op->ArrayGroupMode = 0;
  para->Center[0] = 0.500000f;
  para->Center[1] = 0.500000f;
  para->Zoom[0] = 1.000000f;
  para->Zoom[1] = 1.000000f;
  para->Scroll[0] = 0.500000f;
  para->Scroll[1] = 0.500000f;
}

void PocBitmapBindRotZoom(wCommand *cmd,ScriptContext *ctx)
{
  ScriptValue *val;
  val = ctx->MakeValue(ScriptTypeFloat,2);
  val->FloatPtr = ((sF32 *)cmd->Data)+2;
  ctx->BindLocal(ctx->AddSymbol(L"center"),val);
  val = ctx->MakeValue(ScriptTypeFloat,2);
  val->FloatPtr = ((sF32 *)cmd->Data)+2;
  ctx->BindLocal(ctx->AddSymbol(L"center"),val);
  val = ctx->MakeValue(ScriptTypeFloat,2);
  val->FloatPtr = ((sF32 *)cmd->Data)+4;
  ctx->BindLocal(ctx->AddSymbol(L"zoom"),val);
  val = ctx->MakeValue(ScriptTypeFloat,2);
  val->FloatPtr = ((sF32 *)cmd->Data)+4;
  ctx->BindLocal(ctx->AddSymbol(L"zoom"),val);
  val = ctx->MakeValue(ScriptTypeFloat,1);
  val->FloatPtr = ((sF32 *)cmd->Data)+6;
  ctx->BindLocal(ctx->AddSymbol(L"angle"),val);
  val = ctx->MakeValue(ScriptTypeFloat,2);
  val->FloatPtr = ((sF32 *)cmd->Data)+7;
  ctx->BindLocal(ctx->AddSymbol(L"scroll"),val);
  val = ctx->MakeValue(ScriptTypeFloat,2);
  val->FloatPtr = ((sF32 *)cmd->Data)+7;
  ctx->BindLocal(ctx->AddSymbol(L"scroll"),val);
}
void PocBitmapBind2RotZoom(wCommand *cmd,ScriptContext *ctx)
{
  static sInt initdone = 0;
  static sPoolString name[7];
  if(!initdone)
  {
    initdone = 1; 
    name[0] = sPoolString(L"size");
    name[1] = sPoolString(L"sizex");
    name[2] = sPoolString(L"sizey");
    name[3] = sPoolString(L"center");
    name[4] = sPoolString(L"zoom");
    name[5] = sPoolString(L"angle");
    name[6] = sPoolString(L"scroll");
  }
  ctx->AddImport(name[3],ScriptTypeFloat,2,cmd->Data+2);
  ctx->AddImport(name[4],ScriptTypeFloat,2,cmd->Data+4);
  ctx->AddImport(name[5],ScriptTypeFloat,1,cmd->Data+6);
  ctx->AddImport(name[6],ScriptTypeFloat,2,cmd->Data+7);
}
void PocBitmapBind3RotZoom(wOp *op,sTextBuffer &tb)
{
  tb.PrintF(L"  import center : float[2];\n");
  tb.PrintF(L"  import zoom : float[2];\n");
  tb.PrintF(L"  import angle : float;\n");
  tb.PrintF(L"  import scroll : float[2];\n");
}
const sChar *PocBitmapWikiRotZoom =
L"= PocBitmap : RotZoom\n"
L"\n"
L"!t 2 : 2 3\n"
L" !T 2\n"
L"  !i Name\n"
L"  !i RotZoom\n"
L"\n"
L"  !i Output Type\n"
L"  !i PocBitmap\n"
L" !i\n"
L"\n"
L"== Inputs\n"
L"\n"
L"!T 3 : 1 1 3\n"
L" !\n"
L"  ! bc #c0c0c0\n"
L"  !i Type\n"
L"  !i Flags\n"
L"  !i Comment\n"
L" !i PocBitmap\n"
L" !i\n"
L" !i *\n"
L"\n"
L"== Parameters\n"
L"\n"
L"!T 4 : 1 1 1 2\n"
L" !\n"
L"  ! bc #c0c0c0\n"
L"  !i Screen Name\n"
L"  !i Script Name\n"
L"  !i Type\n"
L"  !i Comment\n"
L"\n"
L"!T 4 : 1 1 1 2\n"
L" !i Size\n"
L" !i SizeX\n"
L" !i same\n"
L" !i *\n"
L" !i \n"
L" !i \n"
L" !i 1\n"
L" !i *\n"
L" !i \n"
L" !i \n"
L" !i 2\n"
L" !i *\n"
L" !i \n"
L" !i \n"
L" !i 4\n"
L" !i *\n"
L" !i \n"
L" !i \n"
L" !i 8\n"
L" !i *\n"
L" !i \n"
L" !i \n"
L" !i 16\n"
L" !i *\n"
L" !i \n"
L" !i \n"
L" !i 32\n"
L" !i *\n"
L" !i \n"
L" !i \n"
L" !i 64\n"
L" !i *\n"
L" !i \n"
L" !i \n"
L" !i 128\n"
L" !i *\n"
L" !i \n"
L" !i \n"
L" !i 256\n"
L" !i *\n"
L" !i \n"
L" !i \n"
L" !i 512\n"
L" !i *\n"
L" !i \n"
L" !i \n"
L" !i 1024\n"
L" !i *\n"
L" !i \n"
L" !i \n"
L" !i 2048\n"
L" !i *\n"
L"!T 4 : 1 1 1 2\n"
L" !i <NULL>\n"
L" !i SizeY\n"
L" !i same\n"
L" !i *\n"
L" !i \n"
L" !i \n"
L" !i 1\n"
L" !i *\n"
L" !i \n"
L" !i \n"
L" !i 2\n"
L" !i *\n"
L" !i \n"
L" !i \n"
L" !i 4\n"
L" !i *\n"
L" !i \n"
L" !i \n"
L" !i 8\n"
L" !i *\n"
L" !i \n"
L" !i \n"
L" !i 16\n"
L" !i *\n"
L" !i \n"
L" !i \n"
L" !i 32\n"
L" !i *\n"
L" !i \n"
L" !i \n"
L" !i 64\n"
L" !i *\n"
L" !i \n"
L" !i \n"
L" !i 128\n"
L" !i *\n"
L" !i \n"
L" !i \n"
L" !i 256\n"
L" !i *\n"
L" !i \n"
L" !i \n"
L" !i 512\n"
L" !i *\n"
L" !i \n"
L" !i \n"
L" !i 1024\n"
L" !i *\n"
L" !i \n"
L" !i \n"
L" !i 2048\n"
L" !i *\n"
L"!T 4 : 1 1 1 2\n"
L" !i Center\n"
L" !i Center\n"
L" !i float[2]\n"
L" !i *\n"
L"\n"
L" !i Zoom\n"
L" !i Zoom\n"
L" !i float[2]\n"
L" !i *\n"
L"\n"
L" !i Angle\n"
L" !i Angle\n"
L" !i float\n"
L" !i *\n"
L"\n"
L" !i Scroll\n"
L" !i Scroll\n"
L" !i float[2]\n"
L" !i *\n"
L"\n"
L"== Comments\n"
L"\n"
L"*\n"
L"\n"
L"== See Also\n"
L"\n"
L"\n"
;

/****************************************************************************/

sBool PocBitmapCmdAtlas(wExecutive *exe,wCommand *cmd)
{
  PocBitmapParaAtlas sUNUSED *para = (PocBitmapParaAtlas *)(cmd->Data); para;
  PocBitmap sUNUSED *in0 = cmd->GetInput<PocBitmap *>(0); in0;
  PocBitmap *out = (PocBitmap *) cmd->Output;
  if(!out) { out=new PocBitmap; cmd->Output=out; }

  {
#line 506 "poc_ops.ops"

    sStaticArray<PocBitmapAtlas> a;
    a.HintSize(cmd->InputCount);
    a.AddMany(cmd->InputCount);

    for(sInt i=0;i<cmd->InputCount;i++)
      a[i].Image = cmd->GetInput<PocBitmap *>(i)->Image;

    PocBitmapMakeAtlas(a,out->Image,para->EmptyColor, para->Mode);
    
    out->Atlas.Entries.Clear();
    out->Atlas.Entries.HintSize(a.GetCount());
    PocBitmapAtlas *pba;
    sFORALL(a, pba)
    {
      BitmapAtlasEntry e;

      e.Pixels.Init(pba->PosX,pba->PosY,pba->PosX+pba->SizeX,pba->PosY+pba->SizeY);
      e.UVs.x0 = sF32(e.Pixels.x0)/out->Image->SizeX;
      e.UVs.y0 = sF32(e.Pixels.y0)/out->Image->SizeY;
      e.UVs.x1 = sF32(e.Pixels.x1)/out->Image->SizeX;
      e.UVs.y1 = sF32(e.Pixels.y1)/out->Image->SizeY;
      out->Atlas.Entries.AddTail(e);
    }
  ;
#line 2173 "poc_ops.cpp"
    return 1;
  }
}

void PocBitmapGuiAtlas(wGridFrameHelper &gh,wOp *op)
{
  PocBitmapParaAtlas sUNUSED *para = (PocBitmapParaAtlas *)(op->EditData); para;
  gh.Group(op->Class->Label);

  gh.Label(L"EmptyColor");
  gh.ColorPick(&para->EmptyColor,L"rgba",0);

  gh.Label(L"Mode");
  gh.Flags(&para->Mode,L"Auto|Horizontal|Vertical",gh.ChangeMsg);
}

void PocBitmapDefAtlas(wOp *op)
{
  PocBitmapParaAtlas sUNUSED *para = (PocBitmapParaAtlas *)(op->EditData); para;
  op->ArrayGroupMode = 0;
}

void PocBitmapBindAtlas(wCommand *cmd,ScriptContext *ctx)
{
  ScriptValue *val;
  val = ctx->MakeValue(ScriptTypeColor,1);
  val->ColorPtr = ((sU32 *)cmd->Data)+0;
  ctx->BindLocal(ctx->AddSymbol(L"emptycolor"),val);
}
void PocBitmapBind2Atlas(wCommand *cmd,ScriptContext *ctx)
{
  static sInt initdone = 0;
  static sPoolString name[2];
  if(!initdone)
  {
    initdone = 1; 
    name[0] = sPoolString(L"emptycolor");
    name[1] = sPoolString(L"mode");
  }
  ctx->AddImport(name[0],ScriptTypeColor,1,cmd->Data+0);
}
void PocBitmapBind3Atlas(wOp *op,sTextBuffer &tb)
{
  tb.PrintF(L"  import emptycolor : color;\n");
}
const sChar *PocBitmapWikiAtlas =
L"= PocBitmap : Atlas\n"
L"\n"
L"!t 2 : 2 3\n"
L" !T 2\n"
L"  !i Name\n"
L"  !i Atlas\n"
L"\n"
L"  !i Output Type\n"
L"  !i PocBitmap\n"
L" !i\n"
L"\n"
L"== Inputs\n"
L"\n"
L"!T 3 : 1 1 3\n"
L" !\n"
L"  ! bc #c0c0c0\n"
L"  !i Type\n"
L"  !i Flags\n"
L"  !i Comment\n"
L" !i PocBitmap\n"
L" !i multiple\n"
L" !i *\n"
L"\n"
L"== Parameters\n"
L"\n"
L"!T 4 : 1 1 1 2\n"
L" !\n"
L"  ! bc #c0c0c0\n"
L"  !i Screen Name\n"
L"  !i Script Name\n"
L"  !i Type\n"
L"  !i Comment\n"
L"\n"
L" !i EmptyColor\n"
L" !i EmptyColor\n"
L" !i color\n"
L" !i *\n"
L"\n"
L"!T 4 : 1 1 1 2\n"
L" !i Mode\n"
L" !i Mode\n"
L" !i Auto\n"
L" !i *\n"
L" !i \n"
L" !i \n"
L" !i Horizontal\n"
L" !i *\n"
L" !i \n"
L" !i \n"
L" !i Vertical\n"
L" !i *\n"
L"== Comments\n"
L"\n"
L"*\n"
L"\n"
L"== See Also\n"
L"\n"
L"\n"
;

/****************************************************************************/

sBool PocBitmapCmdPreMulAlpha(wExecutive *exe,wCommand *cmd)
{
  PocBitmapParaPreMulAlpha sUNUSED *para = (PocBitmapParaPreMulAlpha *)(cmd->Data); para;
  PocBitmap sUNUSED *in0 = cmd->GetInput<PocBitmap *>(0); in0;
  PocBitmap *out = (PocBitmap *) cmd->Output;
  if(!out) { out=new PocBitmap; out->CopyFrom(in0); cmd->Output=out; }

  {
#line 543 "poc_ops.ops"

    sU8 *data = (sU8 *)out->Image->Data;

    if((para->Flags & 1) == 0) // normal mode
    {
      for(sInt i=0;i<out->Image->SizeX*out->Image->SizeY;i++)
      {
        data[0] = data[0] * data[3] / 255;
        data[1] = data[1] * data[3] / 255;
        data[2] = data[2] * data[3] / 255;
        data += 4;
      }
    }
    else // white input background mode: assume image was composited onto white.
    {
      for(sInt i=0;i<out->Image->SizeX*out->Image->SizeY;i++)
      {
        sInt alpha = data[3];
        sInt invAlpha = 255 - alpha;

        data[0] = sU8(sMax(data[0] - invAlpha,0));
        data[1] = sU8(sMax(data[1] - invAlpha,0));
        data[2] = sU8(sMax(data[2] - invAlpha,0));
        data += 4;
      }
    }
  ;
#line 2318 "poc_ops.cpp"
    return 1;
  }
}

void PocBitmapGuiPreMulAlpha(wGridFrameHelper &gh,wOp *op)
{
  PocBitmapParaPreMulAlpha sUNUSED *para = (PocBitmapParaPreMulAlpha *)(op->EditData); para;
  gh.Group(op->Class->Label);

  gh.Label(L"Flags");
  gh.Flags(&para->Flags,L"-|White input BG",gh.ChangeMsg);
}

void PocBitmapDefPreMulAlpha(wOp *op)
{
  PocBitmapParaPreMulAlpha sUNUSED *para = (PocBitmapParaPreMulAlpha *)(op->EditData); para;
  op->ArrayGroupMode = 0;
}

void PocBitmapBindPreMulAlpha(wCommand *cmd,ScriptContext *ctx)
{
}
void PocBitmapBind2PreMulAlpha(wCommand *cmd,ScriptContext *ctx)
{
  static sInt initdone = 0;
  static sPoolString name[1];
  if(!initdone)
  {
    initdone = 1; 
    name[0] = sPoolString(L"flags");
  }
}
void PocBitmapBind3PreMulAlpha(wOp *op,sTextBuffer &tb)
{
}
const sChar *PocBitmapWikiPreMulAlpha =
L"= PocBitmap : PreMulAlpha\n"
L"\n"
L"!t 2 : 2 3\n"
L" !T 2\n"
L"  !i Name\n"
L"  !i PreMulAlpha\n"
L"\n"
L"  !i Output Type\n"
L"  !i PocBitmap\n"
L" !i\n"
L"\n"
L"== Inputs\n"
L"\n"
L"!T 3 : 1 1 3\n"
L" !\n"
L"  ! bc #c0c0c0\n"
L"  !i Type\n"
L"  !i Flags\n"
L"  !i Comment\n"
L" !i PocBitmap\n"
L" !i\n"
L" !i *\n"
L"\n"
L"== Parameters\n"
L"\n"
L"!T 4 : 1 1 1 2\n"
L" !\n"
L"  ! bc #c0c0c0\n"
L"  !i Screen Name\n"
L"  !i Script Name\n"
L"  !i Type\n"
L"  !i Comment\n"
L"\n"
L"!T 4 : 1 1 1 2\n"
L" !i Flags\n"
L" !i Flags\n"
L" !i White input BG\n"
L" !i *\n"
L"== Comments\n"
L"\n"
L"*\n"
L"\n"
L"== See Also\n"
L"\n"
L"\n"
;

/****************************************************************************/

sBool PocBitmapCmdBlueToAlpha(wExecutive *exe,wCommand *cmd)
{
  PocBitmapParaBlueToAlpha sUNUSED *para = (PocBitmapParaBlueToAlpha *)(cmd->Data); para;
  PocBitmap sUNUSED *in0 = cmd->GetInput<PocBitmap *>(0); in0;
  PocBitmap *out = (PocBitmap *) cmd->Output;
  if(!out) { out=new PocBitmap; out->CopyFrom(in0); cmd->Output=out; }

  {
#line 575 "poc_ops.ops"

    sU8 *data = (sU8 *)out->Image->Data;
    for(sInt i=0;i<out->Image->SizeX*out->Image->SizeY;i++)
    {
      sInt alpha = data[0];
      data[0] = 255;
      data[1] = 255;
      data[2] = 255;
      data[3] = sU8(alpha);
      data += 4;
    }
  ;
#line 2425 "poc_ops.cpp"
    return 1;
  }
}

void PocBitmapGuiBlueToAlpha(wGridFrameHelper &gh,wOp *op)
{
  PocBitmapParaBlueToAlpha sUNUSED *para = (PocBitmapParaBlueToAlpha *)(op->EditData); para;
}

void PocBitmapDefBlueToAlpha(wOp *op)
{
  PocBitmapParaBlueToAlpha sUNUSED *para = (PocBitmapParaBlueToAlpha *)(op->EditData); para;
  op->ArrayGroupMode = 0;
}

void PocBitmapBindBlueToAlpha(wCommand *cmd,ScriptContext *ctx)
{
}
void PocBitmapBind2BlueToAlpha(wCommand *cmd,ScriptContext *ctx)
{
}
void PocBitmapBind3BlueToAlpha(wOp *op,sTextBuffer &tb)
{
}
const sChar *PocBitmapWikiBlueToAlpha =
L"= PocBitmap : BlueToAlpha\n"
L"\n"
L"!t 2 : 2 3\n"
L" !T 2\n"
L"  !i Name\n"
L"  !i BlueToAlpha\n"
L"\n"
L"  !i Output Type\n"
L"  !i PocBitmap\n"
L" !i\n"
L"\n"
L"== Inputs\n"
L"\n"
L"!T 3 : 1 1 3\n"
L" !\n"
L"  ! bc #c0c0c0\n"
L"  !i Type\n"
L"  !i Flags\n"
L"  !i Comment\n"
L" !i PocBitmap\n"
L" !i\n"
L" !i *\n"
L"\n"
L"== Comments\n"
L"\n"
L"*\n"
L"\n"
L"== See Also\n"
L"\n"
L"\n"
;

/****************************************************************************/

sBool PocBitmapCmdColor(wExecutive *exe,wCommand *cmd)
{
  PocBitmapParaColor sUNUSED *para = (PocBitmapParaColor *)(cmd->Data); para;
  PocBitmap sUNUSED *in0 = cmd->GetInput<PocBitmap *>(0); in0;
  PocBitmap *out = (PocBitmap *) cmd->Output;
  if(!out) { out=new PocBitmap; out->CopyFrom(in0); cmd->Output=out; }

  {
#line 601 "poc_ops.ops"

    sU8 *data = (sU8 *)out->Image->Data;
    
    sInt c0[4];
    sInt c1[4];

    c0[0] = (para->Color0>> 0)&0xff;
    c0[1] = (para->Color0>> 8)&0xff;
    c0[2] = (para->Color0>>16)&0xff;
    c0[3] = (para->Color0>>24)&0xff;
    c1[0] = (para->Color1>> 0)&0xff;
    c1[1] = (para->Color1>> 8)&0xff;
    c1[2] = (para->Color1>>16)&0xff;
    c1[3] = (para->Color1>>24)&0xff;

    if(para->Mode==0)
    {
      for(sInt i=0;i<out->Image->SizeX*out->Image->SizeY;i++)
      {
        sInt v = (data[0]+data[1]*2+data[2])/4;
        data[0] = sU8(v * (c1[0]-c0[0])/255 + c0[0]);
        data[1] = sU8(v * (c1[1]-c0[1])/255 + c0[1]);
        data[2] = sU8(v * (c1[2]-c0[2])/255 + c0[2]);
        data[3] = sU8(v * (c1[3]-c0[3])/255 + c0[3]);
        data += 4;
      }
    }
    else
    {
      for(sInt i=0;i<out->Image->SizeX*out->Image->SizeY;i++)
      {
        data[0] = sU8(data[0] * (c1[0]-c0[0])/255 + c0[0]);
        data[1] = sU8(data[1] * (c1[1]-c0[1])/255 + c0[1]);
        data[2] = sU8(data[2] * (c1[2]-c0[2])/255 + c0[2]);
        data[3] = sU8(data[3] * (c1[3]-c0[3])/255 + c0[3]);
        data += 4;
      }
    }
  ;
#line 2533 "poc_ops.cpp"
    return 1;
  }
}

void PocBitmapGuiColor(wGridFrameHelper &gh,wOp *op)
{
  PocBitmapParaColor sUNUSED *para = (PocBitmapParaColor *)(op->EditData); para;
  gh.Group(op->Class->Label);

  gh.Label(L"Mode");
  gh.Flags(&para->Mode,L"ramp|range",gh.ChangeMsg);

  gh.Label(L"Color0");
  gh.ColorPick(&para->Color0,L"rgba",0);

  gh.Label(L"Color1");
  gh.ColorPick(&para->Color1,L"rgba",0);
}

void PocBitmapDefColor(wOp *op)
{
  PocBitmapParaColor sUNUSED *para = (PocBitmapParaColor *)(op->EditData); para;
  op->ArrayGroupMode = 0;
  para->Color0 = 0xff000000;
  para->Color1 = 0xffffffff;
}

void PocBitmapBindColor(wCommand *cmd,ScriptContext *ctx)
{
  ScriptValue *val;
  val = ctx->MakeValue(ScriptTypeColor,1);
  val->ColorPtr = ((sU32 *)cmd->Data)+1;
  ctx->BindLocal(ctx->AddSymbol(L"color0"),val);
  val = ctx->MakeValue(ScriptTypeColor,1);
  val->ColorPtr = ((sU32 *)cmd->Data)+2;
  ctx->BindLocal(ctx->AddSymbol(L"color1"),val);
}
void PocBitmapBind2Color(wCommand *cmd,ScriptContext *ctx)
{
  static sInt initdone = 0;
  static sPoolString name[3];
  if(!initdone)
  {
    initdone = 1; 
    name[0] = sPoolString(L"mode");
    name[1] = sPoolString(L"color0");
    name[2] = sPoolString(L"color1");
  }
  ctx->AddImport(name[1],ScriptTypeColor,1,cmd->Data+1);
  ctx->AddImport(name[2],ScriptTypeColor,1,cmd->Data+2);
}
void PocBitmapBind3Color(wOp *op,sTextBuffer &tb)
{
  tb.PrintF(L"  import color0 : color;\n");
  tb.PrintF(L"  import color1 : color;\n");
}
const sChar *PocBitmapWikiColor =
L"= PocBitmap : Color\n"
L"\n"
L"!t 2 : 2 3\n"
L" !T 2\n"
L"  !i Name\n"
L"  !i Color\n"
L"\n"
L"  !i Output Type\n"
L"  !i PocBitmap\n"
L" !i\n"
L"\n"
L"== Inputs\n"
L"\n"
L"!T 3 : 1 1 3\n"
L" !\n"
L"  ! bc #c0c0c0\n"
L"  !i Type\n"
L"  !i Flags\n"
L"  !i Comment\n"
L" !i PocBitmap\n"
L" !i\n"
L" !i *\n"
L"\n"
L"== Parameters\n"
L"\n"
L"!T 4 : 1 1 1 2\n"
L" !\n"
L"  ! bc #c0c0c0\n"
L"  !i Screen Name\n"
L"  !i Script Name\n"
L"  !i Type\n"
L"  !i Comment\n"
L"\n"
L"!T 4 : 1 1 1 2\n"
L" !i Mode\n"
L" !i Mode\n"
L" !i ramp\n"
L" !i *\n"
L" !i \n"
L" !i \n"
L" !i range\n"
L" !i *\n"
L"!T 4 : 1 1 1 2\n"
L" !i Color0\n"
L" !i Color0\n"
L" !i color\n"
L" !i *\n"
L"\n"
L" !i Color1\n"
L" !i Color1\n"
L" !i color\n"
L" !i *\n"
L"\n"
L"== Comments\n"
L"\n"
L"*\n"
L"\n"
L"== See Also\n"
L"\n"
L"\n"
;

/****************************************************************************/

sBool PocBitmapCmdSCB(wExecutive *exe,wCommand *cmd)
{
  PocBitmapParaSCB sUNUSED *para = (PocBitmapParaSCB *)(cmd->Data); para;
  PocBitmap sUNUSED *in0 = cmd->GetInput<PocBitmap *>(0); in0;
  PocBitmap *out = (PocBitmap *) cmd->Output;
  if(!out) { out=new PocBitmap; out->CopyFrom(in0); cmd->Output=out; }

  {
#line 654 "poc_ops.ops"

    sU8 *data = (sU8 *)out->Image->Data;
   
    sVector30 ooo;
    sVector31 col;
    sMatrix34 mat,mat1;
    ooo.Init(1,1,1);

    mat.Init();
    mat.i = (1.0f-para->Saturation)*ooo*0.3086f;
    mat.j = (1.0f-para->Saturation)*ooo*0.6094f;
    mat.k = (1.0f-para->Saturation)*ooo*0.0820f;
    mat.i.x += para->Saturation;
    mat.j.y += para->Saturation;
    mat.k.z += para->Saturation;
    mat.Scale(para->Contrast);
    mat.l = sVector31((0.5f*(1.0f-para->Contrast)+para->Brightness)*ooo);

    for(sInt i=0;i<out->Image->SizeX*out->Image->SizeY;i++)
    {
      col.x = sF32(data[0])/255.0f;
      col.y = sF32(data[1])/255.0f;
      col.z = sF32(data[2])/255.0f;

      col = col*mat;

      data[0] = sU8(sClamp(sInt(col.x*255),0,255));
      data[1] = sU8(sClamp(sInt(col.y*255),0,255));
      data[2] = sU8(sClamp(sInt(col.z*255),0,255));
      data[3] = data[3];
      data += 4;
    }
  ;
#line 2697 "poc_ops.cpp"
    return 1;
  }
}

void PocBitmapGuiSCB(wGridFrameHelper &gh,wOp *op)
{
  PocBitmapParaSCB sUNUSED *para = (PocBitmapParaSCB *)(op->EditData); para;
  gh.Group(op->Class->Label);

  gh.Label(L"Saturation");
  sFloatControl *float_Saturation = gh.Float(&para->Saturation,-16.0000f,16.00000f,0.010000f);
  float_Saturation->Default = 1.000000f; float_Saturation->RightStep = 0.125000f;

  gh.Label(L"Contrast");
  sFloatControl *float_Contrast = gh.Float(&para->Contrast,-16.0000f,16.00000f,0.010000f);
  float_Contrast->Default = 1.000000f; float_Contrast->RightStep = 0.125000f;

  gh.Label(L"Brightness");
  sFloatControl *float_Brightness = gh.Float(&para->Brightness,-16.0000f,16.00000f,0.010000f);
  float_Brightness->Default = 0.000000f; float_Brightness->RightStep = 0.125000f;
}

void PocBitmapDefSCB(wOp *op)
{
  PocBitmapParaSCB sUNUSED *para = (PocBitmapParaSCB *)(op->EditData); para;
  op->ArrayGroupMode = 0;
  para->Saturation = 1.000000f;
  para->Contrast = 1.000000f;
}

void PocBitmapBindSCB(wCommand *cmd,ScriptContext *ctx)
{
  ScriptValue *val;
  val = ctx->MakeValue(ScriptTypeFloat,1);
  val->FloatPtr = ((sF32 *)cmd->Data)+0;
  ctx->BindLocal(ctx->AddSymbol(L"saturation"),val);
  val = ctx->MakeValue(ScriptTypeFloat,1);
  val->FloatPtr = ((sF32 *)cmd->Data)+1;
  ctx->BindLocal(ctx->AddSymbol(L"contrast"),val);
  val = ctx->MakeValue(ScriptTypeFloat,1);
  val->FloatPtr = ((sF32 *)cmd->Data)+2;
  ctx->BindLocal(ctx->AddSymbol(L"brightness"),val);
}
void PocBitmapBind2SCB(wCommand *cmd,ScriptContext *ctx)
{
  static sInt initdone = 0;
  static sPoolString name[3];
  if(!initdone)
  {
    initdone = 1; 
    name[0] = sPoolString(L"saturation");
    name[1] = sPoolString(L"contrast");
    name[2] = sPoolString(L"brightness");
  }
  ctx->AddImport(name[0],ScriptTypeFloat,1,cmd->Data+0);
  ctx->AddImport(name[1],ScriptTypeFloat,1,cmd->Data+1);
  ctx->AddImport(name[2],ScriptTypeFloat,1,cmd->Data+2);
}
void PocBitmapBind3SCB(wOp *op,sTextBuffer &tb)
{
  tb.PrintF(L"  import saturation : float;\n");
  tb.PrintF(L"  import contrast : float;\n");
  tb.PrintF(L"  import brightness : float;\n");
}
const sChar *PocBitmapWikiSCB =
L"= PocBitmap : SCB\n"
L"\n"
L"!t 2 : 2 3\n"
L" !T 2\n"
L"  !i Name\n"
L"  !i SCB\n"
L"\n"
L"  !i Output Type\n"
L"  !i PocBitmap\n"
L" !i\n"
L"\n"
L"== Inputs\n"
L"\n"
L"!T 3 : 1 1 3\n"
L" !\n"
L"  ! bc #c0c0c0\n"
L"  !i Type\n"
L"  !i Flags\n"
L"  !i Comment\n"
L" !i PocBitmap\n"
L" !i\n"
L" !i *\n"
L"\n"
L"== Parameters\n"
L"\n"
L"!T 4 : 1 1 1 2\n"
L" !\n"
L"  ! bc #c0c0c0\n"
L"  !i Screen Name\n"
L"  !i Script Name\n"
L"  !i Type\n"
L"  !i Comment\n"
L"\n"
L" !i Saturation\n"
L" !i Saturation\n"
L" !i float\n"
L" !i *\n"
L"\n"
L" !i Contrast\n"
L" !i Contrast\n"
L" !i float\n"
L" !i *\n"
L"\n"
L" !i Brightness\n"
L" !i Brightness\n"
L" !i float\n"
L" !i *\n"
L"\n"
L"== Comments\n"
L"\n"
L"*\n"
L"\n"
L"== See Also\n"
L"\n"
L"\n"
;

/****************************************************************************/

sBool PocBitmapCmdColorBalance(wExecutive *exe,wCommand *cmd)
{
  PocBitmapParaColorBalance sUNUSED *para = (PocBitmapParaColorBalance *)(cmd->Data); para;
  PocBitmap sUNUSED *in0 = cmd->GetInput<PocBitmap *>(0); in0;
  PocBitmap *out = (PocBitmap *) cmd->Output;
  if(!out) { out=new PocBitmap; out->CopyFrom(in0); cmd->Output=out; }

  {
#line 700 "poc_ops.ops"

    sVector30 col,min,max,msc,pow;
    sVector30 c0,c1,c2;

    sU8 *data = (sU8 *)out->Image->Data;

    c0 = para->Shadows;
    c1 = para->Midtones;
    c2 = para->Highlights;

    pow = c0*0.5f + c1 + c2*0.5f;
    pow.x = sFPow(0.5f,pow.x);
    pow.y = sFPow(0.5f,pow.y);
    pow.z = sFPow(0.5f,pow.z);
    min.x = -sMin(c0.x,0.0f);
    min.y = -sMin(c0.y,0.0f);
    min.z = -sMin(c0.z,0.0f);
    max.x = 1-sMax(c2.x,0.0f);
    max.y = 1-sMax(c2.y,0.0f);
    max.z = 1-sMax(c2.z,0.0f);
    msc.x = 1.0f / (max.x-min.x);
    msc.y = 1.0f / (max.y-min.y);
    msc.z = 1.0f / (max.z-min.z);

    for(sInt i=0;i<out->Image->SizeX*out->Image->SizeY;i++)
    {
      col.x = sF32(data[0])/255.0f;
      col.y = sF32(data[1])/255.0f;
      col.z = sF32(data[2])/255.0f;

      col.x = sFPow((sClamp(col.x,min.x,max.x)-min.x)*msc.x,pow.x);
      col.y = sFPow((sClamp(col.y,min.y,max.y)-min.y)*msc.y,pow.y);
      col.z = sFPow((sClamp(col.z,min.z,max.z)-min.z)*msc.z,pow.z);

      data[0] = sU8(sClamp(sInt(col.x*255),0,255));
      data[1] = sU8(sClamp(sInt(col.y*255),0,255));
      data[2] = sU8(sClamp(sInt(col.z*255),0,255));
      data[3] = data[3];
      data += 4;
    }
  ;
#line 2872 "poc_ops.cpp"
    return 1;
  }
}

void PocBitmapGuiColorBalance(wGridFrameHelper &gh,wOp *op)
{
  PocBitmapParaColorBalance sUNUSED *para = (PocBitmapParaColorBalance *)(op->EditData); para;
  gh.Group(op->Class->Label);

  gh.Label(L"Shadows");
  gh.BeginTied();
  sFloatControl *float_Shadows_0 = gh.Float(&para->Shadows.x,-1.00000f,1.000000f,0.001000f);
  float_Shadows_0->Default = 0.000000f; float_Shadows_0->RightStep = 0.125000f;
  sFloatControl *float_Shadows_1 = gh.Float(&para->Shadows.y,-1.00000f,1.000000f,0.001000f);
  float_Shadows_1->Default = 0.000000f; float_Shadows_1->RightStep = 0.125000f;
  sFloatControl *float_Shadows_2 = gh.Float(&para->Shadows.z,-1.00000f,1.000000f,0.001000f);
  float_Shadows_2->Default = 0.000000f; float_Shadows_2->RightStep = 0.125000f;
  gh.EndTied();

  gh.Label(L"Midtones");
  gh.BeginTied();
  sFloatControl *float_Midtones_0 = gh.Float(&para->Midtones.x,-1.00000f,1.000000f,0.001000f);
  float_Midtones_0->Default = 0.000000f; float_Midtones_0->RightStep = 0.125000f;
  sFloatControl *float_Midtones_1 = gh.Float(&para->Midtones.y,-1.00000f,1.000000f,0.001000f);
  float_Midtones_1->Default = 0.000000f; float_Midtones_1->RightStep = 0.125000f;
  sFloatControl *float_Midtones_2 = gh.Float(&para->Midtones.z,-1.00000f,1.000000f,0.001000f);
  float_Midtones_2->Default = 0.000000f; float_Midtones_2->RightStep = 0.125000f;
  gh.EndTied();

  gh.Label(L"Highlights");
  gh.BeginTied();
  sFloatControl *float_Highlights_0 = gh.Float(&para->Highlights.x,-1.00000f,0.999000f,0.001000f);
  float_Highlights_0->Default = 0.000000f; float_Highlights_0->RightStep = 0.125000f;
  sFloatControl *float_Highlights_1 = gh.Float(&para->Highlights.y,-1.00000f,0.999000f,0.001000f);
  float_Highlights_1->Default = 0.000000f; float_Highlights_1->RightStep = 0.125000f;
  sFloatControl *float_Highlights_2 = gh.Float(&para->Highlights.z,-1.00000f,0.999000f,0.001000f);
  float_Highlights_2->Default = 0.000000f; float_Highlights_2->RightStep = 0.125000f;
  gh.EndTied();
}

void PocBitmapDefColorBalance(wOp *op)
{
  PocBitmapParaColorBalance sUNUSED *para = (PocBitmapParaColorBalance *)(op->EditData); para;
  op->ArrayGroupMode = 0;
}

void PocBitmapBindColorBalance(wCommand *cmd,ScriptContext *ctx)
{
  ScriptValue *val;
  val = ctx->MakeValue(ScriptTypeFloat,3);
  val->FloatPtr = ((sF32 *)cmd->Data)+0;
  ctx->BindLocal(ctx->AddSymbol(L"shadows"),val);
  val = ctx->MakeValue(ScriptTypeFloat,3);
  val->FloatPtr = ((sF32 *)cmd->Data)+0;
  ctx->BindLocal(ctx->AddSymbol(L"shadows"),val);
  val = ctx->MakeValue(ScriptTypeFloat,3);
  val->FloatPtr = ((sF32 *)cmd->Data)+0;
  ctx->BindLocal(ctx->AddSymbol(L"shadows"),val);
  val = ctx->MakeValue(ScriptTypeFloat,3);
  val->FloatPtr = ((sF32 *)cmd->Data)+3;
  ctx->BindLocal(ctx->AddSymbol(L"midtones"),val);
  val = ctx->MakeValue(ScriptTypeFloat,3);
  val->FloatPtr = ((sF32 *)cmd->Data)+3;
  ctx->BindLocal(ctx->AddSymbol(L"midtones"),val);
  val = ctx->MakeValue(ScriptTypeFloat,3);
  val->FloatPtr = ((sF32 *)cmd->Data)+3;
  ctx->BindLocal(ctx->AddSymbol(L"midtones"),val);
  val = ctx->MakeValue(ScriptTypeFloat,3);
  val->FloatPtr = ((sF32 *)cmd->Data)+6;
  ctx->BindLocal(ctx->AddSymbol(L"highlights"),val);
  val = ctx->MakeValue(ScriptTypeFloat,3);
  val->FloatPtr = ((sF32 *)cmd->Data)+6;
  ctx->BindLocal(ctx->AddSymbol(L"highlights"),val);
  val = ctx->MakeValue(ScriptTypeFloat,3);
  val->FloatPtr = ((sF32 *)cmd->Data)+6;
  ctx->BindLocal(ctx->AddSymbol(L"highlights"),val);
}
void PocBitmapBind2ColorBalance(wCommand *cmd,ScriptContext *ctx)
{
  static sInt initdone = 0;
  static sPoolString name[3];
  if(!initdone)
  {
    initdone = 1; 
    name[0] = sPoolString(L"shadows");
    name[1] = sPoolString(L"midtones");
    name[2] = sPoolString(L"highlights");
  }
  ctx->AddImport(name[0],ScriptTypeFloat,3,cmd->Data+0);
  ctx->AddImport(name[1],ScriptTypeFloat,3,cmd->Data+3);
  ctx->AddImport(name[2],ScriptTypeFloat,3,cmd->Data+6);
}
void PocBitmapBind3ColorBalance(wOp *op,sTextBuffer &tb)
{
  tb.PrintF(L"  import shadows : float[3];\n");
  tb.PrintF(L"  import midtones : float[3];\n");
  tb.PrintF(L"  import highlights : float[3];\n");
}
const sChar *PocBitmapWikiColorBalance =
L"= PocBitmap : ColorBalance\n"
L"\n"
L"!t 2 : 2 3\n"
L" !T 2\n"
L"  !i Name\n"
L"  !i ColorBalance\n"
L"\n"
L"  !i Output Type\n"
L"  !i PocBitmap\n"
L" !i\n"
L"\n"
L"== Inputs\n"
L"\n"
L"!T 3 : 1 1 3\n"
L" !\n"
L"  ! bc #c0c0c0\n"
L"  !i Type\n"
L"  !i Flags\n"
L"  !i Comment\n"
L" !i PocBitmap\n"
L" !i\n"
L" !i *\n"
L"\n"
L"== Parameters\n"
L"\n"
L"!T 4 : 1 1 1 2\n"
L" !\n"
L"  ! bc #c0c0c0\n"
L"  !i Screen Name\n"
L"  !i Script Name\n"
L"  !i Type\n"
L"  !i Comment\n"
L"\n"
L" !i Shadows\n"
L" !i Shadows\n"
L" !i float[3]\n"
L" !i *\n"
L"\n"
L" !i Midtones\n"
L" !i Midtones\n"
L" !i float[3]\n"
L" !i *\n"
L"\n"
L" !i Highlights\n"
L" !i Highlights\n"
L" !i float[3]\n"
L" !i *\n"
L"\n"
L"== Comments\n"
L"\n"
L"*\n"
L"\n"
L"== See Also\n"
L"\n"
L"\n"
;

/****************************************************************************/

sBool PocBitmapCmdBlur(wExecutive *exe,wCommand *cmd)
{
  PocBitmapParaBlur sUNUSED *para = (PocBitmapParaBlur *)(cmd->Data); para;
  PocBitmap sUNUSED *in0 = cmd->GetInput<PocBitmap *>(0); in0;
  PocBitmap *out = (PocBitmap *) cmd->Output;
  if(!out) { out=new PocBitmap; cmd->Output=out; }

  {
#line 754 "poc_ops.ops"

    sInt passes = para->Filter + 1;

    sInt radX = sInt(para->Radius[0] * in0->Image->SizeX);
    sInt radY = sInt(para->Radius[1] * in0->Image->SizeY);
    out->Image->Copy(in0->Image);

    for(sInt i=0;i<passes;i++)
    {
      if(radX) out->Image->BlurX(radX);
      if(radY) out->Image->BlurY(radY);
    }
  ;
#line 3053 "poc_ops.cpp"
    return 1;
  }
}

void PocBitmapGuiBlur(wGridFrameHelper &gh,wOp *op)
{
  PocBitmapParaBlur sUNUSED *para = (PocBitmapParaBlur *)(op->EditData); para;
  gh.Group(op->Class->Label);

  gh.Label(L"Radius");
  gh.BeginTied();
  sFloatControl *float_Radius_0 = gh.Float(&para->Radius[0],0.000000f,1.000000f,0.001000f);
  float_Radius_0->Default = 0.002000f; float_Radius_0->RightStep = 0.125000f;
  sFloatControl *float_Radius_1 = gh.Float(&para->Radius[1],0.000000f,1.000000f,0.001000f);
  float_Radius_1->Default = 0.002000f; float_Radius_1->RightStep = 0.125000f;
  gh.EndTied();

  gh.Label(L"Filter");
  gh.Flags(&para->Filter,L"Box|Triangle|Gauss",gh.ChangeMsg);
}

void PocBitmapDefBlur(wOp *op)
{
  PocBitmapParaBlur sUNUSED *para = (PocBitmapParaBlur *)(op->EditData); para;
  op->ArrayGroupMode = 0;
  para->Radius[0] = 0.002000f;
  para->Radius[1] = 0.002000f;
}

void PocBitmapBindBlur(wCommand *cmd,ScriptContext *ctx)
{
  ScriptValue *val;
  val = ctx->MakeValue(ScriptTypeFloat,2);
  val->FloatPtr = ((sF32 *)cmd->Data)+0;
  ctx->BindLocal(ctx->AddSymbol(L"radius"),val);
  val = ctx->MakeValue(ScriptTypeFloat,2);
  val->FloatPtr = ((sF32 *)cmd->Data)+0;
  ctx->BindLocal(ctx->AddSymbol(L"radius"),val);
}
void PocBitmapBind2Blur(wCommand *cmd,ScriptContext *ctx)
{
  static sInt initdone = 0;
  static sPoolString name[2];
  if(!initdone)
  {
    initdone = 1; 
    name[0] = sPoolString(L"radius");
    name[1] = sPoolString(L"filter");
  }
  ctx->AddImport(name[0],ScriptTypeFloat,2,cmd->Data+0);
}
void PocBitmapBind3Blur(wOp *op,sTextBuffer &tb)
{
  tb.PrintF(L"  import radius : float[2];\n");
}
const sChar *PocBitmapWikiBlur =
L"= PocBitmap : Blur\n"
L"\n"
L"!t 2 : 2 3\n"
L" !T 2\n"
L"  !i Name\n"
L"  !i Blur\n"
L"\n"
L"  !i Output Type\n"
L"  !i PocBitmap\n"
L" !i\n"
L"\n"
L"== Inputs\n"
L"\n"
L"!T 3 : 1 1 3\n"
L" !\n"
L"  ! bc #c0c0c0\n"
L"  !i Type\n"
L"  !i Flags\n"
L"  !i Comment\n"
L" !i PocBitmap\n"
L" !i\n"
L" !i *\n"
L"\n"
L"== Parameters\n"
L"\n"
L"!T 4 : 1 1 1 2\n"
L" !\n"
L"  ! bc #c0c0c0\n"
L"  !i Screen Name\n"
L"  !i Script Name\n"
L"  !i Type\n"
L"  !i Comment\n"
L"\n"
L" !i Radius\n"
L" !i Radius\n"
L" !i float[2]\n"
L" !i *\n"
L"\n"
L"!T 4 : 1 1 1 2\n"
L" !i Filter\n"
L" !i Filter\n"
L" !i Box\n"
L" !i *\n"
L" !i \n"
L" !i \n"
L" !i Triangle\n"
L" !i *\n"
L" !i \n"
L" !i \n"
L" !i Gauss\n"
L" !i *\n"
L"== Comments\n"
L"\n"
L"*\n"
L"\n"
L"== See Also\n"
L"\n"
L"\n"
;

/****************************************************************************/

sBool PocBitmapCmdDistanceField(wExecutive *exe,wCommand *cmd)
{
  PocBitmapParaDistanceField sUNUSED *para = (PocBitmapParaDistanceField *)(cmd->Data); para;
  PocBitmap sUNUSED *in0 = cmd->GetInput<PocBitmap *>(0); in0;
  PocBitmap *out = (PocBitmap *) cmd->Output;
  if(!out) { out=new PocBitmap; cmd->Output=out; }

  {
#line 782 "poc_ops.ops"

    sInt thres=para->Threshold*100;
    sInt scale=para->Scale;
    sInt width=para->Width;

    sInt sx,sy,dx,dy;
    sx = dx = in0->Image->SizeX;
    sy = dy = in0->Image->SizeY;
    dx>>=scale;
    dy>>=scale;
    out->Image->Init(dx,dy);

    // yes, this is slow. sorry.
    for (sInt y=0; y<dy; y++)
    {
      sU32 *d = out->Image->Data+y*dx;
      
      sInt ysmid=(y<<scale);
      sInt ysmin=sMax(0,ysmid-width);
      sInt ysmax=sMin(sy,ysmid+width+1);

      for (sInt x=0; x<dx; x++)
      {
        sInt xsmid=x<<scale;
        sInt xsmin=sMax(0,xsmid-width);
        sInt xsmax=sMin(sx,xsmid+width+1);

        sF32 mind1=sSquare(sF32(width+1));
        sF32 mind0=sSquare(sF32(width+1));
        for (sInt yy=ysmin; yy<ysmax; yy++)
        {
          sU32 *s = in0->Image->Data+yy*sx;
          for (sInt xx=xsmin; xx<xsmax; xx++)
          {
            sU32 p=s[xx];
            sInt lum=((p>>16)&0xff)*30+((p>>8)&0xff)*59+(p&0xff)*11;
            sF32 d=sF32(sSquare(xx-xsmid)+sSquare(yy-ysmid));
            if (lum>=thres)
              mind1=sMin(mind1,d);
            else
              mind0=sMin(mind0,d);
          }
        }

        sF32 out;
        if (mind0>0)
          out=0.5f*(sFSqrt(mind0)-1)/width+0.5f;
        else
          out=-0.5f*sFSqrt(mind1)/width+0.5f;

        d[x]=0x01010101*sClamp<sInt>(sInt(256.0f*out),0,255);
      }
    }
    return 1;
  ;
#line 3236 "poc_ops.cpp"
    return 1;
  }
}

void PocBitmapGuiDistanceField(wGridFrameHelper &gh,wOp *op)
{
  PocBitmapParaDistanceField sUNUSED *para = (PocBitmapParaDistanceField *)(op->EditData); para;
  gh.Group(op->Class->Label);

  gh.Label(L"Threshold");
  sIntControl *int_Threshold = gh.Int(&para->Threshold,0,255,0.125000f);
  int_Threshold->Default = 0x00000080; int_Threshold->RightStep = 0.125000f;

  gh.Label(L"Width");
  sIntControl *int_Width = gh.Int(&para->Width,1,255,0.125000f);
  int_Width->Default = 0x00000010; int_Width->RightStep = 0.125000f;

  gh.Label(L"Scale");
  gh.Flags(&para->Scale,L"none|/2|/4|/8|/16|/32|/64",gh.ChangeMsg);
}

void PocBitmapDefDistanceField(wOp *op)
{
  PocBitmapParaDistanceField sUNUSED *para = (PocBitmapParaDistanceField *)(op->EditData); para;
  op->ArrayGroupMode = 0;
  para->Threshold = 0x00000080;
  para->Width = 0x00000010;
  para->Scale = 0x00000002;
}

void PocBitmapBindDistanceField(wCommand *cmd,ScriptContext *ctx)
{
  ScriptValue *val;
  val = ctx->MakeValue(ScriptTypeInt,1);
  val->IntPtr = ((sInt *)cmd->Data)+0;
  ctx->BindLocal(ctx->AddSymbol(L"threshold"),val);
  val = ctx->MakeValue(ScriptTypeInt,1);
  val->IntPtr = ((sInt *)cmd->Data)+1;
  ctx->BindLocal(ctx->AddSymbol(L"width"),val);
}
void PocBitmapBind2DistanceField(wCommand *cmd,ScriptContext *ctx)
{
  static sInt initdone = 0;
  static sPoolString name[3];
  if(!initdone)
  {
    initdone = 1; 
    name[0] = sPoolString(L"threshold");
    name[1] = sPoolString(L"width");
    name[2] = sPoolString(L"scale");
  }
  ctx->AddImport(name[0],ScriptTypeInt,1,cmd->Data+0);
  ctx->AddImport(name[1],ScriptTypeInt,1,cmd->Data+1);
}
void PocBitmapBind3DistanceField(wOp *op,sTextBuffer &tb)
{
  tb.PrintF(L"  import threshold : int;\n");
  tb.PrintF(L"  import width : int;\n");
}
const sChar *PocBitmapWikiDistanceField =
L"= PocBitmap : DistanceField\n"
L"\n"
L"!t 2 : 2 3\n"
L" !T 2\n"
L"  !i Name\n"
L"  !i DistanceField\n"
L"\n"
L"  !i Output Type\n"
L"  !i PocBitmap\n"
L" !i\n"
L"\n"
L"== Inputs\n"
L"\n"
L"!T 3 : 1 1 3\n"
L" !\n"
L"  ! bc #c0c0c0\n"
L"  !i Type\n"
L"  !i Flags\n"
L"  !i Comment\n"
L" !i PocBitmap\n"
L" !i\n"
L" !i *\n"
L"\n"
L"== Parameters\n"
L"\n"
L"!T 4 : 1 1 1 2\n"
L" !\n"
L"  ! bc #c0c0c0\n"
L"  !i Screen Name\n"
L"  !i Script Name\n"
L"  !i Type\n"
L"  !i Comment\n"
L"\n"
L" !i Threshold\n"
L" !i Threshold\n"
L" !i int\n"
L" !i *\n"
L"\n"
L" !i Width\n"
L" !i Width\n"
L" !i int\n"
L" !i *\n"
L"\n"
L"!T 4 : 1 1 1 2\n"
L" !i Scale\n"
L" !i Scale\n"
L" !i none\n"
L" !i *\n"
L" !i \n"
L" !i \n"
L" !i /2\n"
L" !i *\n"
L" !i \n"
L" !i \n"
L" !i /4\n"
L" !i *\n"
L" !i \n"
L" !i \n"
L" !i /8\n"
L" !i *\n"
L" !i \n"
L" !i \n"
L" !i /16\n"
L" !i *\n"
L" !i \n"
L" !i \n"
L" !i /32\n"
L" !i *\n"
L" !i \n"
L" !i \n"
L" !i /64\n"
L" !i *\n"
L"== Comments\n"
L"\n"
L"*\n"
L"\n"
L"== See Also\n"
L"\n"
L"\n"
;

/****************************************************************************/

sBool PocBitmapCmdHalf(wExecutive *exe,wCommand *cmd)
{
  PocBitmapParaHalf sUNUSED *para = (PocBitmapParaHalf *)(cmd->Data); para;
  PocBitmap sUNUSED *in0 = cmd->GetInput<PocBitmap *>(0); in0;
  PocBitmap *out = (PocBitmap *) cmd->Output;
  if(!out) { out=new PocBitmap; cmd->Output=out; }

  {
#line 841 "poc_ops.ops"

    delete out->Image;
    out->Image = in0->Image->Half();
  ;
#line 3393 "poc_ops.cpp"
    return 1;
  }
}

void PocBitmapGuiHalf(wGridFrameHelper &gh,wOp *op)
{
  PocBitmapParaHalf sUNUSED *para = (PocBitmapParaHalf *)(op->EditData); para;
}

void PocBitmapDefHalf(wOp *op)
{
  PocBitmapParaHalf sUNUSED *para = (PocBitmapParaHalf *)(op->EditData); para;
  op->ArrayGroupMode = 0;
}

void PocBitmapBindHalf(wCommand *cmd,ScriptContext *ctx)
{
}
void PocBitmapBind2Half(wCommand *cmd,ScriptContext *ctx)
{
}
void PocBitmapBind3Half(wOp *op,sTextBuffer &tb)
{
}
const sChar *PocBitmapWikiHalf =
L"= PocBitmap : Half\n"
L"\n"
L"!t 2 : 2 3\n"
L" !T 2\n"
L"  !i Name\n"
L"  !i Half\n"
L"\n"
L"  !i Output Type\n"
L"  !i PocBitmap\n"
L" !i\n"
L"\n"
L"== Inputs\n"
L"\n"
L"!T 3 : 1 1 3\n"
L" !\n"
L"  ! bc #c0c0c0\n"
L"  !i Type\n"
L"  !i Flags\n"
L"  !i Comment\n"
L" !i PocBitmap\n"
L" !i\n"
L" !i *\n"
L"\n"
L"== Comments\n"
L"\n"
L"*\n"
L"\n"
L"== See Also\n"
L"\n"
L"\n"
;

/****************************************************************************/

sBool PocBitmapCmdExport(wExecutive *exe,wCommand *cmd)
{
  PocBitmapParaExport sUNUSED *para = (PocBitmapParaExport *)(cmd->Data); para;
  PocBitmap sUNUSED *in0 = cmd->GetInput<PocBitmap *>(0); in0;
  PocBitmap *out = (PocBitmap *) cmd->Output;
  if(!out) { out=new PocBitmap; out->CopyFrom(in0); cmd->Output=out; }

  {
#line 858 "poc_ops.ops"

    out->Image->Save(cmd->Strings[0]);
  ;
#line 3465 "poc_ops.cpp"
    return 1;
  }
}

void PocBitmapGuiExport(wGridFrameHelper &gh,wOp *op)
{
  PocBitmapParaExport sUNUSED *para = (PocBitmapParaExport *)(op->EditData); para;
  gh.Group(op->Class->Label);

  gh.Label(L"Output Filename (pic/bmp/tga)");
  {
    sControl *con = gh.String(op->EditString[0]);
    con->DoneMsg = con->ChangeMsg;
    con->ChangeMsg = sMessage();
    gh.FileSaveDialogMsg.Code = 0;
    gh.Box(L"...",gh.FileSaveDialogMsg);
  }
}

void PocBitmapDefExport(wOp *op)
{
  PocBitmapParaExport sUNUSED *para = (PocBitmapParaExport *)(op->EditData); para;
  op->ArrayGroupMode = 0;
}

void PocBitmapBindExport(wCommand *cmd,ScriptContext *ctx)
{
  ScriptValue *val;
  val = ctx->MakeValue(ScriptTypeString,1);
  val->StringPtr = ((sPoolString *)cmd->Strings)+0;
  ctx->BindLocal(ctx->AddSymbol(L"filename"),val);
}
void PocBitmapBind2Export(wCommand *cmd,ScriptContext *ctx)
{
  static sInt initdone = 0;
  static sPoolString name[1];
  if(!initdone)
  {
    initdone = 1; 
    name[0] = sPoolString(L"filename");
  }
  ctx->AddImport(name[0],ScriptTypeString,1,cmd->Strings+0);
}
void PocBitmapBind3Export(wOp *op,sTextBuffer &tb)
{
  tb.PrintF(L"  import filename : string;\n");
}
const sChar *PocBitmapWikiExport =
L"= PocBitmap : Export\n"
L"\n"
L"!t 2 : 2 3\n"
L" !T 2\n"
L"  !i Name\n"
L"  !i Export\n"
L"\n"
L"  !i Output Type\n"
L"  !i PocBitmap\n"
L" !i\n"
L"\n"
L"== Inputs\n"
L"\n"
L"!T 3 : 1 1 3\n"
L" !\n"
L"  ! bc #c0c0c0\n"
L"  !i Type\n"
L"  !i Flags\n"
L"  !i Comment\n"
L" !i PocBitmap\n"
L" !i\n"
L" !i *\n"
L"\n"
L"== Parameters\n"
L"\n"
L"!T 4 : 1 1 1 2\n"
L" !\n"
L"  ! bc #c0c0c0\n"
L"  !i Screen Name\n"
L"  !i Script Name\n"
L"  !i Type\n"
L"  !i Comment\n"
L"\n"
L" !i Output Filename (pic/bmp/tga)\n"
L" !i Filename\n"
L" !i save file\n"
L" !i *\n"
L"\n"
L"== Comments\n"
L"\n"
L"*\n"
L"\n"
L"== See Also\n"
L"\n"
L"\n"
;

/****************************************************************************/

sBool UnitTestCmdUnitTestPocBitmap(wExecutive *exe,wCommand *cmd)
{
  UnitTestParaUnitTestPocBitmap sUNUSED *para = (UnitTestParaUnitTestPocBitmap *)(cmd->Data); para;
  PocBitmap sUNUSED *in0 = cmd->GetInput<PocBitmap *>(0); in0;
  UnitTest *out = (UnitTest *) cmd->Output;
  if(!out) { out=new UnitTest; cmd->Output=out; }

  {
#line 872 "poc_ops.ops"

    sImage img;
    in0->CopyTo(&img);
    return out->Test(img,cmd->Strings[0],para->Flags);
  ;
#line 3577 "poc_ops.cpp"
    return 1;
  }
}

void UnitTestGuiUnitTestPocBitmap(wGridFrameHelper &gh,wOp *op)
{
  UnitTestParaUnitTestPocBitmap sUNUSED *para = (UnitTestParaUnitTestPocBitmap *)(op->EditData); para;
  gh.Group(op->Class->Label);

  gh.Label(L"TestName");
  {
    sControl *con = gh.String(op->EditString[0]);
    con->DoneMsg = con->ChangeMsg;
    con->ChangeMsg = sMessage();
    gh.FileSaveDialogMsg.Code = 0;
    gh.Box(L"...",gh.FileSaveDialogMsg);
  }

  gh.Label(L"Always Pass");
  gh.Flags(&para->Flags,L"-|compare:*1-|cross compare",gh.ChangeMsg);
}

void UnitTestDefUnitTestPocBitmap(wOp *op)
{
  UnitTestParaUnitTestPocBitmap sUNUSED *para = (UnitTestParaUnitTestPocBitmap *)(op->EditData); para;
  op->ArrayGroupMode = 0;
}

void UnitTestBindUnitTestPocBitmap(wCommand *cmd,ScriptContext *ctx)
{
  ScriptValue *val;
  val = ctx->MakeValue(ScriptTypeString,1);
  val->StringPtr = ((sPoolString *)cmd->Strings)+0;
  ctx->BindLocal(ctx->AddSymbol(L"testname"),val);
}
void UnitTestBind2UnitTestPocBitmap(wCommand *cmd,ScriptContext *ctx)
{
  static sInt initdone = 0;
  static sPoolString name[2];
  if(!initdone)
  {
    initdone = 1; 
    name[0] = sPoolString(L"testname");
    name[1] = sPoolString(L"flags");
  }
  ctx->AddImport(name[0],ScriptTypeString,1,cmd->Strings+0);
}
void UnitTestBind3UnitTestPocBitmap(wOp *op,sTextBuffer &tb)
{
  tb.PrintF(L"  import testname : string;\n");
}
const sChar *UnitTestWikiUnitTestPocBitmap =
L"= UnitTest : UnitTestPocBitmap\n"
L"\n"
L"!t 2 : 2 3\n"
L" !T 2\n"
L"  !i Name\n"
L"  !i UnitTestPocBitmap\n"
L"\n"
L"  !i Output Type\n"
L"  !i UnitTest\n"
L" !i\n"
L"\n"
L"== Inputs\n"
L"\n"
L"!T 3 : 1 1 3\n"
L" !\n"
L"  ! bc #c0c0c0\n"
L"  !i Type\n"
L"  !i Flags\n"
L"  !i Comment\n"
L" !i PocBitmap\n"
L" !i\n"
L" !i *\n"
L"\n"
L"== Parameters\n"
L"\n"
L"!T 4 : 1 1 1 2\n"
L" !\n"
L"  ! bc #c0c0c0\n"
L"  !i Screen Name\n"
L"  !i Script Name\n"
L"  !i Type\n"
L"  !i Comment\n"
L"\n"
L" !i TestName\n"
L" !i TestName\n"
L" !i save file\n"
L" !i *\n"
L"\n"
L"!T 4 : 1 1 1 2\n"
L" !i Always Pass\n"
L" !i Flags\n"
L" !i compare\n"
L" !i *\n"
L" !i\n"
L" !i\n"
L" !i\n"
L" !i\n"
L"\n"
L" !i \n"
L" !i \n"
L" !i cross compare\n"
L" !i *\n"
L"== Comments\n"
L"\n"
L"*\n"
L"\n"
L"== See Also\n"
L"\n"
L"\n"
;

/****************************************************************************/

sBool PocMaterialCmdMaterial(wExecutive *exe,wCommand *cmd)
{
  PocMaterialParaMaterial sUNUSED *para = (PocMaterialParaMaterial *)(cmd->Data); para;
  Texture2D sUNUSED *in0 = cmd->GetInput<Texture2D *>(0); in0;
  PocMaterial *out = (PocMaterial *) cmd->Output;
  if(!out) { out=new PocMaterial; cmd->Output=out; }

  {
#line 948 "poc_ops.ops"

    static sU32 blend[8] =
    {
      sMB_OFF,sMB_ADD,sMB_MUL,sMB_MUL2,sMB_ADDSMOOTH
    };
    out->Material = new sSimpleMaterial;
    out->Material->Flags = para->Flags;
    out->Material->BlendColor = blend[para->Blend&7];
    if(in0)
    {
      out->Tex[0] = in0; in0->AddRef();
      out->Material->Texture[0] = in0->Texture;
      out->Material->TFlags[0] = sConvertOldUvFlags(para->TFlags0);
    }
    out->Material->Prepare(sVertexFormatStandard);

    return 1;
  ;
#line 3720 "poc_ops.cpp"
    return 1;
  }
}

void PocMaterialGuiMaterial(wGridFrameHelper &gh,wOp *op)
{
  PocMaterialParaMaterial sUNUSED *para = (PocMaterialParaMaterial *)(op->EditData); para;
  gh.Group(op->Class->Label);

  gh.Label(L"Flags");
  gh.Flags(&para->Flags,L"zoff|zread|zwrite|zon:*4culloff|cullon|cullinv:*7-|light",gh.ChangeMsg);

  gh.Label(L"Blend");
  gh.Flags(&para->Blend,L"opaque|add|mul|mul2|smooth",gh.ChangeMsg);

  gh.Label(L"Texture");
  gh.Flags(&op->Links[0].Select,L"input|link",gh.ConnectLayoutMsg);
  if(op->Links[0].Select==1)
  {
    sControl *con=gh.String(op->Links[0].LinkName,gh.LabelWidth+gh.WideWidth-gh.Left);
    con->ChangeMsg = gh.ConnectMsg;
    con->DoneMsg = gh.ConnectLayoutMsg;
    sMessage msg = gh.LinkBrowserMsg; msg.Code = 0;
    gh.Box(L"...",msg);
    msg = gh.LinkPopupMsg; msg.Code = 0;
    gh.Box(L"..",msg);
    if(!op->Links[0].LinkName.IsEmpty())
    {
      msg = gh.LinkGotoMsg; msg.Code = 0;
      gh.Box(L"->",msg);
    }
  }

  gh.Label(L"TFlags0");
  gh.Flags(&para->TFlags0,L"point|linear|mipmaps|aniso:*4tile|clamp|mirror",gh.ChangeMsg);
}

void PocMaterialDefMaterial(wOp *op)
{
  PocMaterialParaMaterial sUNUSED *para = (PocMaterialParaMaterial *)(op->EditData); para;
  op->ArrayGroupMode = 0;
  para->Flags = 0x00000093;
  para->TFlags0 = 0x00000002;
}

void PocMaterialBindMaterial(wCommand *cmd,ScriptContext *ctx)
{
}
void PocMaterialBind2Material(wCommand *cmd,ScriptContext *ctx)
{
  static sInt initdone = 0;
  static sPoolString name[4];
  if(!initdone)
  {
    initdone = 1; 
    name[0] = sPoolString(L"flags");
    name[1] = sPoolString(L"blend");
    name[2] = sPoolString(L"texture");
    name[3] = sPoolString(L"tflags0");
  }
}
void PocMaterialBind3Material(wOp *op,sTextBuffer &tb)
{
}
const sChar *PocMaterialWikiMaterial =
L"= PocMaterial : Material\n"
L"\n"
L"!t 2 : 2 3\n"
L" !T 2\n"
L"  !i Name\n"
L"  !i Material\n"
L"\n"
L"  !i Output Type\n"
L"  !i PocMaterial\n"
L" !i\n"
L"\n"
L"== Inputs\n"
L"\n"
L"!T 3 : 1 1 3\n"
L" !\n"
L"  ! bc #c0c0c0\n"
L"  !i Type\n"
L"  !i Flags\n"
L"  !i Comment\n"
L" !i Texture2D\n"
L" !i optional link Texture\n"
L" !i *\n"
L"\n"
L"== Parameters\n"
L"\n"
L"!T 4 : 1 1 1 2\n"
L" !\n"
L"  ! bc #c0c0c0\n"
L"  !i Screen Name\n"
L"  !i Script Name\n"
L"  !i Type\n"
L"  !i Comment\n"
L"\n"
L"!T 4 : 1 1 1 2\n"
L" !i Flags\n"
L" !i Flags\n"
L" !i zoff\n"
L" !i *\n"
L" !i \n"
L" !i \n"
L" !i zread\n"
L" !i *\n"
L" !i \n"
L" !i \n"
L" !i zwrite\n"
L" !i *\n"
L" !i \n"
L" !i \n"
L" !i zon\n"
L" !i *\n"
L" !i\n"
L" !i\n"
L" !i\n"
L" !i\n"
L"\n"
L" !i \n"
L" !i \n"
L" !i culloff\n"
L" !i *\n"
L" !i \n"
L" !i \n"
L" !i cullon\n"
L" !i *\n"
L" !i \n"
L" !i \n"
L" !i cullinv\n"
L" !i *\n"
L" !i\n"
L" !i\n"
L" !i\n"
L" !i\n"
L"\n"
L" !i \n"
L" !i \n"
L" !i light\n"
L" !i *\n"
L"!T 4 : 1 1 1 2\n"
L" !i Blend\n"
L" !i Blend\n"
L" !i opaque\n"
L" !i *\n"
L" !i \n"
L" !i \n"
L" !i add\n"
L" !i *\n"
L" !i \n"
L" !i \n"
L" !i mul\n"
L" !i *\n"
L" !i \n"
L" !i \n"
L" !i mul2\n"
L" !i *\n"
L" !i \n"
L" !i \n"
L" !i smooth\n"
L" !i *\n"
L"!T 4 : 1 1 1 2\n"
L" !i Texture\n"
L" !i Texture\n"
L" !i link\n"
L" !i *\n"
L"\n"
L"!T 4 : 1 1 1 2\n"
L" !i TFlags0\n"
L" !i TFlags0\n"
L" !i point\n"
L" !i *\n"
L" !i \n"
L" !i \n"
L" !i linear\n"
L" !i *\n"
L" !i \n"
L" !i \n"
L" !i mipmaps\n"
L" !i *\n"
L" !i \n"
L" !i \n"
L" !i aniso\n"
L" !i *\n"
L" !i\n"
L" !i\n"
L" !i\n"
L" !i\n"
L"\n"
L" !i \n"
L" !i \n"
L" !i tile\n"
L" !i *\n"
L" !i \n"
L" !i \n"
L" !i clamp\n"
L" !i *\n"
L" !i \n"
L" !i \n"
L" !i mirror\n"
L" !i *\n"
L"== Comments\n"
L"\n"
L"*\n"
L"\n"
L"== See Also\n"
L"\n"
L"\n"
;

/****************************************************************************/

sBool PocMeshCmdtorus(wExecutive *exe,wCommand *cmd)
{
  PocMeshParatorus sUNUSED *para = (PocMeshParatorus *)(cmd->Data); para;
  PocMesh *out = (PocMesh *) cmd->Output;
  if(!out) { out=new PocMesh; cmd->Output=out; }

  {
#line 1070 "poc_ops.ops"

    sInt ty = para->Segments;
    sInt tx = para->Roundness;
    sF32 ro = para->Outer;
    sF32 ri = para->Inner;
    sF32 u,v,fx,fy;
    
    out->Init(tx*ty,tx*ty*6);
    PocMeshVertex *vp = &out->Vertices[0];

    for(sInt y=0;y<ty;y++)
    {
      for(sInt x=0;x<tx;x++)
      {
        u = sF32(x)/tx; fx = (u-para->Phase)*sPI2F;
        v = sF32(y)/ty; fy =  v       *sPI2F;
        vp->Pos.x = -sFCos(fy)*(ro+sFSin(fx)*ri);
        vp->Pos.y = -sFCos(fx)*ri;
        vp->Pos.z = sFSin(fy)*(ro+sFSin(fx)*ri);
        vp->Normal.x = -sFCos(fy)*sFSin(fx);
        vp->Normal.y = -sFCos(fx);
        vp->Normal.z = sFSin(fy)*sFSin(fx);
        vp->u = u;
        vp->v = v;
        vp++;
      }
    }
    
    sU32 *ip = &out->Indices[0];
    for(sInt y=0;y<ty;y++)
    {
      for(sInt x=0;x<tx;x++)
      {
        sQuad(ip,0,
          (y+0)%ty*tx+(x+0)%tx,
          (y+1)%ty*tx+(x+0)%tx,
          (y+1)%ty*tx+(x+1)%tx,
          (y+0)%ty*tx+(x+1)%tx);
      }
    }
    return 1;
  ;
#line 3984 "poc_ops.cpp"
    return 1;
  }
}

void PocMeshGuitorus(wGridFrameHelper &gh,wOp *op)
{
  PocMeshParatorus sUNUSED *para = (PocMeshParatorus *)(op->EditData); para;
  gh.Group(op->Class->Label);

  gh.Label(L"Inner");
  sFloatControl *float_Inner = gh.Float(&para->Inner,0.000000f,1024.000f,0.010000f);
  float_Inner->Default = 0.250000f; float_Inner->RightStep = 0.125000f;

  gh.Label(L"Outer");
  sFloatControl *float_Outer = gh.Float(&para->Outer,0.000000f,1024.000f,0.010000f);
  float_Outer->Default = 1.000000f; float_Outer->RightStep = 0.125000f;

  gh.Label(L"Phase");
  sFloatControl *float_Phase = gh.Float(&para->Phase,0.000000f,1.000000f,0.010000f);
  float_Phase->Default = 0.000000f; float_Phase->RightStep = 0.125000f;

  gh.Label(L"Segments");
  sIntControl *int_Segments = gh.Int(&para->Segments,3,64,0.125000f);
  int_Segments->Default = 0x00000004; int_Segments->RightStep = 0.125000f;

  gh.Label(L"Roundness");
  sIntControl *int_Roundness = gh.Int(&para->Roundness,3,64,0.125000f);
  int_Roundness->Default = 0x00000004; int_Roundness->RightStep = 0.125000f;
}

void PocMeshDeftorus(wOp *op)
{
  PocMeshParatorus sUNUSED *para = (PocMeshParatorus *)(op->EditData); para;
  op->ArrayGroupMode = 0;
  para->Inner = 0.250000f;
  para->Outer = 1.000000f;
  para->Segments = 0x00000004;
  para->Roundness = 0x00000004;
}

void PocMeshBindtorus(wCommand *cmd,ScriptContext *ctx)
{
  ScriptValue *val;
  val = ctx->MakeValue(ScriptTypeFloat,1);
  val->FloatPtr = ((sF32 *)cmd->Data)+0;
  ctx->BindLocal(ctx->AddSymbol(L"inner"),val);
  val = ctx->MakeValue(ScriptTypeFloat,1);
  val->FloatPtr = ((sF32 *)cmd->Data)+1;
  ctx->BindLocal(ctx->AddSymbol(L"outer"),val);
  val = ctx->MakeValue(ScriptTypeFloat,1);
  val->FloatPtr = ((sF32 *)cmd->Data)+2;
  ctx->BindLocal(ctx->AddSymbol(L"phase"),val);
  val = ctx->MakeValue(ScriptTypeInt,1);
  val->IntPtr = ((sInt *)cmd->Data)+3;
  ctx->BindLocal(ctx->AddSymbol(L"segments"),val);
  val = ctx->MakeValue(ScriptTypeInt,1);
  val->IntPtr = ((sInt *)cmd->Data)+4;
  ctx->BindLocal(ctx->AddSymbol(L"roundness"),val);
}
void PocMeshBind2torus(wCommand *cmd,ScriptContext *ctx)
{
  static sInt initdone = 0;
  static sPoolString name[5];
  if(!initdone)
  {
    initdone = 1; 
    name[0] = sPoolString(L"inner");
    name[1] = sPoolString(L"outer");
    name[2] = sPoolString(L"phase");
    name[3] = sPoolString(L"segments");
    name[4] = sPoolString(L"roundness");
  }
  ctx->AddImport(name[0],ScriptTypeFloat,1,cmd->Data+0);
  ctx->AddImport(name[1],ScriptTypeFloat,1,cmd->Data+1);
  ctx->AddImport(name[2],ScriptTypeFloat,1,cmd->Data+2);
  ctx->AddImport(name[3],ScriptTypeInt,1,cmd->Data+3);
  ctx->AddImport(name[4],ScriptTypeInt,1,cmd->Data+4);
}
void PocMeshBind3torus(wOp *op,sTextBuffer &tb)
{
  tb.PrintF(L"  import inner : float;\n");
  tb.PrintF(L"  import outer : float;\n");
  tb.PrintF(L"  import phase : float;\n");
  tb.PrintF(L"  import segments : int;\n");
  tb.PrintF(L"  import roundness : int;\n");
}
const sChar *PocMeshWikitorus =
L"= PocMesh : torus\n"
L"\n"
L"!t 2 : 2 3\n"
L" !T 2\n"
L"  !i Name\n"
L"  !i torus\n"
L"\n"
L"  !i Output Type\n"
L"  !i PocMesh\n"
L" !i\n"
L"\n"
L"== Parameters\n"
L"\n"
L"!T 4 : 1 1 1 2\n"
L" !\n"
L"  ! bc #c0c0c0\n"
L"  !i Screen Name\n"
L"  !i Script Name\n"
L"  !i Type\n"
L"  !i Comment\n"
L"\n"
L" !i Inner\n"
L" !i Inner\n"
L" !i float\n"
L" !i *\n"
L"\n"
L" !i Outer\n"
L" !i Outer\n"
L" !i float\n"
L" !i *\n"
L"\n"
L" !i Phase\n"
L" !i Phase\n"
L" !i float\n"
L" !i *\n"
L"\n"
L" !i Segments\n"
L" !i Segments\n"
L" !i int\n"
L" !i *\n"
L"\n"
L" !i Roundness\n"
L" !i Roundness\n"
L" !i int\n"
L" !i *\n"
L"\n"
L"== Comments\n"
L"\n"
L"*\n"
L"\n"
L"== See Also\n"
L"\n"
L"\n"
;

/****************************************************************************/

sBool PocMeshCmdCube(wExecutive *exe,wCommand *cmd)
{
  PocMeshParaCube sUNUSED *para = (PocMeshParaCube *)(cmd->Data); para;
  PocMesh *out = (PocMesh *) cmd->Output;
  if(!out) { out=new PocMesh; cmd->Output=out; }

  {
#line 1120 "poc_ops.ops"

    sVector31 pos[8];
    const static sInt ci[6][4] =
    {
      { 3,2,1,0 },
      { 4,5,6,7 },
      { 0,1,5,4 },
      { 1,2,6,5 },
      { 2,3,7,6 },
      { 3,0,4,7 },
    };
    
    pos[0].Init(-1,-1,-1);
    pos[1].Init( 1,-1,-1);
    pos[2].Init( 1, 1,-1);
    pos[3].Init(-1, 1,-1);
    pos[4].Init(-1,-1, 1);
    pos[5].Init( 1,-1, 1);
    pos[6].Init( 1, 1, 1);
    pos[7].Init(-1, 1, 1);

    out->Init(24,36);
    sVector30 n;
    PocMeshVertex *vp = &out->Vertices[0];
    sU32 *ip = &out->Indices[0];
    
    for(sInt i=0;i<6;i++)
    {      
      vp[0].Pos = pos[ci[i][0]];
      vp[1].Pos = pos[ci[i][1]];
      vp[2].Pos = pos[ci[i][2]];
      vp[3].Pos = pos[ci[i][3]];
      vp[0].u = 0; vp[0].v = 0;
      vp[1].u = 1; vp[1].v = 0;
      vp[2].u = 1; vp[2].v = 1;
      vp[3].u = 0; vp[3].v = 1;
      n.Cross(vp[0].Pos-vp[1].Pos,vp[1].Pos-vp[2].Pos);
      n.Unit();
      vp[0].Normal = n;
      vp[1].Normal = n;
      vp[2].Normal = n;
      vp[3].Normal = n;
      
      vp+=4;
      sQuad(ip,i*4,0,1,2,3);
    }    
    return 1;
  ;
#line 4185 "poc_ops.cpp"
    return 1;
  }
}

void PocMeshGuiCube(wGridFrameHelper &gh,wOp *op)
{
  PocMeshParaCube sUNUSED *para = (PocMeshParaCube *)(op->EditData); para;
}

void PocMeshDefCube(wOp *op)
{
  PocMeshParaCube sUNUSED *para = (PocMeshParaCube *)(op->EditData); para;
  op->ArrayGroupMode = 0;
}

void PocMeshBindCube(wCommand *cmd,ScriptContext *ctx)
{
}
void PocMeshBind2Cube(wCommand *cmd,ScriptContext *ctx)
{
}
void PocMeshBind3Cube(wOp *op,sTextBuffer &tb)
{
}
const sChar *PocMeshWikiCube =
L"= PocMesh : Cube\n"
L"\n"
L"!t 2 : 2 3\n"
L" !T 2\n"
L"  !i Name\n"
L"  !i Cube\n"
L"\n"
L"  !i Output Type\n"
L"  !i PocMesh\n"
L" !i\n"
L"\n"
L"== Comments\n"
L"\n"
L"*\n"
L"\n"
L"== See Also\n"
L"\n"
L"\n"
;

/****************************************************************************/

sBool PocMeshCmdAdd(wExecutive *exe,wCommand *cmd)
{
  PocMeshParaAdd sUNUSED *para = (PocMeshParaAdd *)(cmd->Data); para;
  PocMesh sUNUSED *in0 = cmd->GetInput<PocMesh *>(0); in0;
  PocMesh *out = (PocMesh *) cmd->Output;
  if(!out) { out=new PocMesh; cmd->Output=out; }

  {
#line 1176 "poc_ops.ops"

    sInt incount = cmd->InputCount;
    sInt vc,ic,cc;
    
    vc = ic = cc = 0;
    for(sInt i=0;i<incount;i++)
    {
      PocMesh *in = cmd->GetInput<PocMesh *>(i);
      vc += in->Vertices.GetCount();
      ic += in->Indices.GetCount();
      cc += in->Clusters.GetCount();
    }
    out->Init(vc,ic,cc);

    vc = ic = cc = 0;
    for(sInt i=0;i<incount;i++)
    {
      PocMesh *in = cmd->GetInput<PocMesh *>(i);
      sCopyMem(&out->Vertices[vc],&in->Vertices[0],in->Vertices.GetCount()*sizeof(PocMeshVertex));
      for(sInt j=0;j<in->Indices.GetCount();j++)
        out->Indices[ic+j] = in->Indices[j]+vc;
      for(sInt j=0;j<in->Clusters.GetCount();j++)
      {
        out->Clusters[cc+j].Mtrl = 0;
        out->Clusters[cc+j].StartIndex = in->Clusters[j].StartIndex + ic;
        out->Clusters[cc+j].EndIndex = in->Clusters[j].EndIndex + ic;
      }
      vc += in->Vertices.GetCount();
      ic += in->Indices.GetCount();
      cc += in->Clusters.GetCount();
    }
    
    return 1;
  ;
#line 4276 "poc_ops.cpp"
    return 1;
  }
}

void PocMeshGuiAdd(wGridFrameHelper &gh,wOp *op)
{
  PocMeshParaAdd sUNUSED *para = (PocMeshParaAdd *)(op->EditData); para;
}

void PocMeshDefAdd(wOp *op)
{
  PocMeshParaAdd sUNUSED *para = (PocMeshParaAdd *)(op->EditData); para;
  op->ArrayGroupMode = 0;
}

void PocMeshBindAdd(wCommand *cmd,ScriptContext *ctx)
{
}
void PocMeshBind2Add(wCommand *cmd,ScriptContext *ctx)
{
}
void PocMeshBind3Add(wOp *op,sTextBuffer &tb)
{
}
const sChar *PocMeshWikiAdd =
L"= PocMesh : Add\n"
L"\n"
L"!t 2 : 2 3\n"
L" !T 2\n"
L"  !i Name\n"
L"  !i Add\n"
L"\n"
L"  !i Output Type\n"
L"  !i PocMesh\n"
L" !i\n"
L"\n"
L"== Inputs\n"
L"\n"
L"!T 3 : 1 1 3\n"
L" !\n"
L"  ! bc #c0c0c0\n"
L"  !i Type\n"
L"  !i Flags\n"
L"  !i Comment\n"
L" !i PocMesh\n"
L" !i multiple\n"
L" !i *\n"
L"\n"
L"== Comments\n"
L"\n"
L"*\n"
L"\n"
L"== See Also\n"
L"\n"
L"\n"
;

/****************************************************************************/

sBool PocMeshCmdTranslate(wExecutive *exe,wCommand *cmd)
{
  PocMeshParaTranslate sUNUSED *para = (PocMeshParaTranslate *)(cmd->Data); para;
  PocMesh sUNUSED *in0 = cmd->GetInput<PocMesh *>(0); in0;
  PocMesh *out = (PocMesh *) cmd->Output;
  if(!out) { out=new PocMesh; cmd->Output=out; }

  {
#line 1224 "poc_ops.ops"

    PocMeshVertex *vp;
    sSRT srt;
    sMatrix34 matp;
    sMatrix34 matn;
    
    srt.Rotate = para->Rotate;
    srt.MakeMatrix(matn);
    srt.Translate = para->Trans;
    srt.Scale = para->Scale;
    srt.MakeMatrix(matp);
    
    out->Copy(in0);
    sFORALL(out->Vertices,vp)
    {
      vp->Pos = vp->Pos * matp;
      vp->Normal = vp->Normal * matn;
    }
    
    return 1;
  ;
#line 4366 "poc_ops.cpp"
    return 1;
  }
}

void PocMeshGuiTranslate(wGridFrameHelper &gh,wOp *op)
{
  PocMeshParaTranslate sUNUSED *para = (PocMeshParaTranslate *)(op->EditData); para;
  gh.Group(op->Class->Label);

  gh.Label(L"Scale");
  gh.BeginTied();
  sFloatControl *float_Scale_0 = gh.Float(&para->Scale.x,-1024.00f,1024.000f,0.010000f);
  float_Scale_0->Default = 1.000000f; float_Scale_0->RightStep = 0.125000f;
  sFloatControl *float_Scale_1 = gh.Float(&para->Scale.y,-1024.00f,1024.000f,0.010000f);
  float_Scale_1->Default = 1.000000f; float_Scale_1->RightStep = 0.125000f;
  sFloatControl *float_Scale_2 = gh.Float(&para->Scale.z,-1024.00f,1024.000f,0.010000f);
  float_Scale_2->Default = 1.000000f; float_Scale_2->RightStep = 0.125000f;
  gh.EndTied();

  gh.Label(L"Rotate");
  gh.BeginTied();
  sFloatControl *float_Rotate_0 = gh.Float(&para->Rotate.x,-64.0000f,64.00000f,0.001000f);
  float_Rotate_0->Default = 0.000000f; float_Rotate_0->RightStep = 0.125000f;
  sFloatControl *float_Rotate_1 = gh.Float(&para->Rotate.y,-64.0000f,64.00000f,0.001000f);
  float_Rotate_1->Default = 0.000000f; float_Rotate_1->RightStep = 0.125000f;
  sFloatControl *float_Rotate_2 = gh.Float(&para->Rotate.z,-64.0000f,64.00000f,0.001000f);
  float_Rotate_2->Default = 0.000000f; float_Rotate_2->RightStep = 0.125000f;
  gh.EndTied();

  gh.Label(L"Trans");
  gh.BeginTied();
  sFloatControl *float_Trans_0 = gh.Float(&para->Trans.x,-1024.00f,1024.000f,0.010000f);
  float_Trans_0->Default = 0.000000f; float_Trans_0->RightStep = 0.125000f;
  sFloatControl *float_Trans_1 = gh.Float(&para->Trans.y,-1024.00f,1024.000f,0.010000f);
  float_Trans_1->Default = 0.000000f; float_Trans_1->RightStep = 0.125000f;
  sFloatControl *float_Trans_2 = gh.Float(&para->Trans.z,-1024.00f,1024.000f,0.010000f);
  float_Trans_2->Default = 0.000000f; float_Trans_2->RightStep = 0.125000f;
  gh.EndTied();
}

void PocMeshDefTranslate(wOp *op)
{
  PocMeshParaTranslate sUNUSED *para = (PocMeshParaTranslate *)(op->EditData); para;
  op->ArrayGroupMode = 0;
  para->Scale.x = 1.000000f;
  para->Scale.y = 1.000000f;
  para->Scale.z = 1.000000f;
}

void PocMeshBindTranslate(wCommand *cmd,ScriptContext *ctx)
{
  ScriptValue *val;
  val = ctx->MakeValue(ScriptTypeFloat,3);
  val->FloatPtr = ((sF32 *)cmd->Data)+0;
  ctx->BindLocal(ctx->AddSymbol(L"scale"),val);
  val = ctx->MakeValue(ScriptTypeFloat,3);
  val->FloatPtr = ((sF32 *)cmd->Data)+0;
  ctx->BindLocal(ctx->AddSymbol(L"scale"),val);
  val = ctx->MakeValue(ScriptTypeFloat,3);
  val->FloatPtr = ((sF32 *)cmd->Data)+0;
  ctx->BindLocal(ctx->AddSymbol(L"scale"),val);
  val = ctx->MakeValue(ScriptTypeFloat,3);
  val->FloatPtr = ((sF32 *)cmd->Data)+3;
  ctx->BindLocal(ctx->AddSymbol(L"rotate"),val);
  val = ctx->MakeValue(ScriptTypeFloat,3);
  val->FloatPtr = ((sF32 *)cmd->Data)+3;
  ctx->BindLocal(ctx->AddSymbol(L"rotate"),val);
  val = ctx->MakeValue(ScriptTypeFloat,3);
  val->FloatPtr = ((sF32 *)cmd->Data)+3;
  ctx->BindLocal(ctx->AddSymbol(L"rotate"),val);
  val = ctx->MakeValue(ScriptTypeFloat,3);
  val->FloatPtr = ((sF32 *)cmd->Data)+6;
  ctx->BindLocal(ctx->AddSymbol(L"trans"),val);
  val = ctx->MakeValue(ScriptTypeFloat,3);
  val->FloatPtr = ((sF32 *)cmd->Data)+6;
  ctx->BindLocal(ctx->AddSymbol(L"trans"),val);
  val = ctx->MakeValue(ScriptTypeFloat,3);
  val->FloatPtr = ((sF32 *)cmd->Data)+6;
  ctx->BindLocal(ctx->AddSymbol(L"trans"),val);
}
void PocMeshBind2Translate(wCommand *cmd,ScriptContext *ctx)
{
  static sInt initdone = 0;
  static sPoolString name[3];
  if(!initdone)
  {
    initdone = 1; 
    name[0] = sPoolString(L"scale");
    name[1] = sPoolString(L"rotate");
    name[2] = sPoolString(L"trans");
  }
  ctx->AddImport(name[0],ScriptTypeFloat,3,cmd->Data+0);
  ctx->AddImport(name[1],ScriptTypeFloat,3,cmd->Data+3);
  ctx->AddImport(name[2],ScriptTypeFloat,3,cmd->Data+6);
}
void PocMeshBind3Translate(wOp *op,sTextBuffer &tb)
{
  tb.PrintF(L"  import scale : float[3];\n");
  tb.PrintF(L"  import rotate : float[3];\n");
  tb.PrintF(L"  import trans : float[3];\n");
}
const sChar *PocMeshWikiTranslate =
L"= PocMesh : Translate\n"
L"\n"
L"!t 2 : 2 3\n"
L" !T 2\n"
L"  !i Name\n"
L"  !i Translate\n"
L"\n"
L"  !i Output Type\n"
L"  !i PocMesh\n"
L" !i\n"
L"\n"
L"== Inputs\n"
L"\n"
L"!T 3 : 1 1 3\n"
L" !\n"
L"  ! bc #c0c0c0\n"
L"  !i Type\n"
L"  !i Flags\n"
L"  !i Comment\n"
L" !i PocMesh\n"
L" !i\n"
L" !i *\n"
L"\n"
L"== Parameters\n"
L"\n"
L"!T 4 : 1 1 1 2\n"
L" !\n"
L"  ! bc #c0c0c0\n"
L"  !i Screen Name\n"
L"  !i Script Name\n"
L"  !i Type\n"
L"  !i Comment\n"
L"\n"
L" !i Scale\n"
L" !i Scale\n"
L" !i float[3]\n"
L" !i *\n"
L"\n"
L" !i Rotate\n"
L" !i Rotate\n"
L" !i float[3]\n"
L" !i *\n"
L"\n"
L" !i Trans\n"
L" !i Trans\n"
L" !i float[3]\n"
L" !i *\n"
L"\n"
L"== Comments\n"
L"\n"
L"*\n"
L"\n"
L"== See Also\n"
L"\n"
L"\n"
;

/****************************************************************************/

sBool PocMeshCmdSetMtrl(wExecutive *exe,wCommand *cmd)
{
  PocMeshParaSetMtrl sUNUSED *para = (PocMeshParaSetMtrl *)(cmd->Data); para;
  PocMesh sUNUSED *in0 = cmd->GetInput<PocMesh *>(0); in0;
  PocMaterial sUNUSED *in1 = cmd->GetInput<PocMaterial *>(1); in1;
  PocMesh *out = (PocMesh *) cmd->Output;
  if(!out) { out=new PocMesh; cmd->Output=out; }

  {
#line 1259 "poc_ops.ops"

    PocMeshCluster *cl;
    out->Copy(in0);
    sFORALL(out->Clusters,cl)
    {
      cl->Mtrl = in1;
      in1->AddRef();
    }
    return 1;
  ;
#line 4548 "poc_ops.cpp"
    return 1;
  }
}

void PocMeshGuiSetMtrl(wGridFrameHelper &gh,wOp *op)
{
  PocMeshParaSetMtrl sUNUSED *para = (PocMeshParaSetMtrl *)(op->EditData); para;
  gh.Group(op->Class->Label);

  gh.Label(L"Material");
  gh.Flags(&op->Links[0].Select,L"input|link",gh.ConnectLayoutMsg);
  if(op->Links[0].Select==1)
  {
    sControl *con=gh.String(op->Links[0].LinkName,gh.LabelWidth+gh.WideWidth-gh.Left);
    con->ChangeMsg = gh.ConnectMsg;
    con->DoneMsg = gh.ConnectLayoutMsg;
    sMessage msg = gh.LinkBrowserMsg; msg.Code = 0;
    gh.Box(L"...",msg);
    msg = gh.LinkPopupMsg; msg.Code = 0;
    gh.Box(L"..",msg);
    if(!op->Links[0].LinkName.IsEmpty())
    {
      msg = gh.LinkGotoMsg; msg.Code = 0;
      gh.Box(L"->",msg);
    }
  }
}

void PocMeshDefSetMtrl(wOp *op)
{
  PocMeshParaSetMtrl sUNUSED *para = (PocMeshParaSetMtrl *)(op->EditData); para;
  op->ArrayGroupMode = 0;
}

void PocMeshBindSetMtrl(wCommand *cmd,ScriptContext *ctx)
{
}
void PocMeshBind2SetMtrl(wCommand *cmd,ScriptContext *ctx)
{
  static sInt initdone = 0;
  static sPoolString name[1];
  if(!initdone)
  {
    initdone = 1; 
    name[0] = sPoolString(L"material");
  }
}
void PocMeshBind3SetMtrl(wOp *op,sTextBuffer &tb)
{
}
const sChar *PocMeshWikiSetMtrl =
L"= PocMesh : SetMtrl\n"
L"\n"
L"!t 2 : 2 3\n"
L" !T 2\n"
L"  !i Name\n"
L"  !i SetMtrl\n"
L"\n"
L"  !i Output Type\n"
L"  !i PocMesh\n"
L" !i\n"
L"\n"
L"== Inputs\n"
L"\n"
L"!T 3 : 1 1 3\n"
L" !\n"
L"  ! bc #c0c0c0\n"
L"  !i Type\n"
L"  !i Flags\n"
L"  !i Comment\n"
L" !i PocMesh\n"
L" !i link Material\n"
L" !i *\n"
L"\n"
L" !i PocMaterial\n"
L" !i\n"
L" !i *\n"
L"\n"
L"== Parameters\n"
L"\n"
L"!T 4 : 1 1 1 2\n"
L" !\n"
L"  ! bc #c0c0c0\n"
L"  !i Screen Name\n"
L"  !i Script Name\n"
L"  !i Type\n"
L"  !i Comment\n"
L"\n"
L" !i Material\n"
L" !i Material\n"
L" !i link\n"
L" !i *\n"
L"\n"
L"== Comments\n"
L"\n"
L"*\n"
L"\n"
L"== See Also\n"
L"\n"
L"\n"
;

/****************************************************************************/

void PocBitmapAnimFlat::Init(class ScriptContext *sc)
{
};

void PocBitmapAnimFlat::Bind(class ScriptContext *sc,PocBitmapParaFlat *para)
{
};

void PocBitmapAnimGlow::Init(class ScriptContext *sc)
{
};

void PocBitmapAnimGlow::Bind(class ScriptContext *sc,PocBitmapParaGlow *para)
{
};

void PocBitmapAnimAdd::Init(class ScriptContext *sc)
{
};

void PocBitmapAnimAdd::Bind(class ScriptContext *sc,PocBitmapParaAdd *para)
{
};

void PocBitmapAnimMandelbrot::Init(class ScriptContext *sc)
{
};

void PocBitmapAnimMandelbrot::Bind(class ScriptContext *sc,PocBitmapParaMandelbrot *para)
{
};

void PocBitmapAnimPerlin::Init(class ScriptContext *sc)
{
};

void PocBitmapAnimPerlin::Bind(class ScriptContext *sc,PocBitmapParaPerlin *para)
{
};

void PocBitmapAnimNormals::Init(class ScriptContext *sc)
{
};

void PocBitmapAnimNormals::Bind(class ScriptContext *sc,PocBitmapParaNormals *para)
{
};

void PocBitmapAnimImport::Init(class ScriptContext *sc)
{
};

void PocBitmapAnimImport::Bind(class ScriptContext *sc,PocBitmapParaImport *para)
{
};

void PocBitmapAnimRotZoom::Init(class ScriptContext *sc)
{
};

void PocBitmapAnimRotZoom::Bind(class ScriptContext *sc,PocBitmapParaRotZoom *para)
{
};

void PocBitmapAnimAtlas::Init(class ScriptContext *sc)
{
};

void PocBitmapAnimAtlas::Bind(class ScriptContext *sc,PocBitmapParaAtlas *para)
{
};

void PocBitmapAnimPreMulAlpha::Init(class ScriptContext *sc)
{
};

void PocBitmapAnimPreMulAlpha::Bind(class ScriptContext *sc,PocBitmapParaPreMulAlpha *para)
{
};

void PocBitmapAnimBlueToAlpha::Init(class ScriptContext *sc)
{
};

void PocBitmapAnimBlueToAlpha::Bind(class ScriptContext *sc,PocBitmapParaBlueToAlpha *para)
{
};

void PocBitmapAnimColor::Init(class ScriptContext *sc)
{
};

void PocBitmapAnimColor::Bind(class ScriptContext *sc,PocBitmapParaColor *para)
{
};

void PocBitmapAnimSCB::Init(class ScriptContext *sc)
{
};

void PocBitmapAnimSCB::Bind(class ScriptContext *sc,PocBitmapParaSCB *para)
{
};

void PocBitmapAnimColorBalance::Init(class ScriptContext *sc)
{
};

void PocBitmapAnimColorBalance::Bind(class ScriptContext *sc,PocBitmapParaColorBalance *para)
{
};

void PocBitmapAnimBlur::Init(class ScriptContext *sc)
{
};

void PocBitmapAnimBlur::Bind(class ScriptContext *sc,PocBitmapParaBlur *para)
{
};

void PocBitmapAnimDistanceField::Init(class ScriptContext *sc)
{
};

void PocBitmapAnimDistanceField::Bind(class ScriptContext *sc,PocBitmapParaDistanceField *para)
{
};

void PocBitmapAnimHalf::Init(class ScriptContext *sc)
{
};

void PocBitmapAnimHalf::Bind(class ScriptContext *sc,PocBitmapParaHalf *para)
{
};

void PocBitmapAnimExport::Init(class ScriptContext *sc)
{
};

void PocBitmapAnimExport::Bind(class ScriptContext *sc,PocBitmapParaExport *para)
{
};

void UnitTestAnimUnitTestPocBitmap::Init(class ScriptContext *sc)
{
};

void UnitTestAnimUnitTestPocBitmap::Bind(class ScriptContext *sc,UnitTestParaUnitTestPocBitmap *para)
{
};

void PocMaterialAnimMaterial::Init(class ScriptContext *sc)
{
};

void PocMaterialAnimMaterial::Bind(class ScriptContext *sc,PocMaterialParaMaterial *para)
{
};

void PocMeshAnimtorus::Init(class ScriptContext *sc)
{
};

void PocMeshAnimtorus::Bind(class ScriptContext *sc,PocMeshParatorus *para)
{
};

void PocMeshAnimCube::Init(class ScriptContext *sc)
{
};

void PocMeshAnimCube::Bind(class ScriptContext *sc,PocMeshParaCube *para)
{
};

void PocMeshAnimAdd::Init(class ScriptContext *sc)
{
};

void PocMeshAnimAdd::Bind(class ScriptContext *sc,PocMeshParaAdd *para)
{
};

void PocMeshAnimTranslate::Init(class ScriptContext *sc)
{
};

void PocMeshAnimTranslate::Bind(class ScriptContext *sc,PocMeshParaTranslate *para)
{
};

void PocMeshAnimSetMtrl::Init(class ScriptContext *sc)
{
};

void PocMeshAnimSetMtrl::Bind(class ScriptContext *sc,PocMeshParaSetMtrl *para)
{
};


/****************************************************************************/

void AddTypes_poc_ops(sBool secondary)
{
  sVERIFY(Doc);

  Doc->Types.AddTail(PocBitmapType = new PocBitmapType_);
  PocBitmapType->Secondary = secondary;

  Doc->Types.AddTail(PocMaterialType = new PocMaterialType_);
  PocMaterialType->Secondary = secondary;

  Doc->Types.AddTail(PocMeshType = new PocMeshType_);
  PocMeshType->Secondary = secondary;

}

/****************************************************************************/

void AddOps_poc_ops(sBool secondary)
{
  sVERIFY(Doc);

  wClass sUNUSED *cl=0; cl;
  wClassInputInfo sUNUSED *in=0; in;



  cl= new wClass;
  cl->Name = L"Flat";
  cl->Label = L"Flat";
  cl->OutputType = PocBitmapType;
  cl->TabType = PocBitmapType;
  cl->Command = PocBitmapCmdFlat;
  cl->MakeGui = PocBitmapGuiFlat;
  cl->SetDefaults = PocBitmapDefFlat;
  cl->BindPara = PocBitmapBindFlat;
  cl->Bind2Para = PocBitmapBind2Flat;
  cl->Bind3Para = PocBitmapBind3Flat;
  cl->WikiText = PocBitmapWikiFlat;
  cl->ParaWords = 3;
  cl->Shortcut = 'f';
  cl->Flags = 0x1000;
  Doc->Classes.AddTail(cl);

  cl= new wClass;
  cl->Name = L"Glow";
  cl->Label = L"Glow";
  cl->OutputType = PocBitmapType;
  cl->TabType = PocBitmapType;
  cl->Command = PocBitmapCmdGlow;
  cl->MakeGui = PocBitmapGuiGlow;
  cl->SetDefaults = PocBitmapDefGlow;
  cl->BindPara = PocBitmapBindGlow;
  cl->Bind2Para = PocBitmapBind2Glow;
  cl->Bind3Para = PocBitmapBind3Glow;
  cl->WikiText = PocBitmapWikiGlow;
  cl->Handles = PocBitmapHndGlow;
  cl->ParaWords = 7;
  cl->HelperWords = (sizeof(PocBitmapHelperGlow)+3)/4;
  cl->Shortcut = 'g';
  cl->Column = 1;
  cl->Flags = 0x1800;
  in = cl->Inputs.AddMany(1);
  in[0].Type = PocBitmapType;
  in[0].DefaultClass = Doc->FindClass(L"Flat",L"PocBitmap");
  in[0].Flags = 0;
  Doc->Classes.AddTail(cl);

  cl= new wClass;
  cl->Name = L"Add";
  cl->Label = L"Add";
  cl->OutputType = PocBitmapType;
  cl->TabType = PocBitmapType;
  cl->Command = PocBitmapCmdAdd;
  cl->MakeGui = PocBitmapGuiAdd;
  cl->SetDefaults = PocBitmapDefAdd;
  cl->BindPara = PocBitmapBindAdd;
  cl->Bind2Para = PocBitmapBind2Add;
  cl->Bind3Para = PocBitmapBind3Add;
  cl->WikiText = PocBitmapWikiAdd;
  cl->ParaWords = 2;
  cl->Shortcut = 'a';
  cl->Column = 2;
  cl->Flags = 0x1001;
  in = cl->Inputs.AddMany(2);
  in[0].Type = PocBitmapType;
  in[0].DefaultClass = 0;
  in[0].Flags = 0;
  in[1].Type = PocBitmapType;
  in[1].DefaultClass = 0;
  in[1].Flags = 0|wCIF_OPTIONAL;
  Doc->Classes.AddTail(cl);

  cl= new wClass;
  cl->Name = L"Mandelbrot";
  cl->Label = L"Mandelbrot";
  cl->OutputType = PocBitmapType;
  cl->TabType = PocBitmapType;
  cl->Command = PocBitmapCmdMandelbrot;
  cl->MakeGui = PocBitmapGuiMandelbrot;
  cl->SetDefaults = PocBitmapDefMandelbrot;
  cl->BindPara = PocBitmapBindMandelbrot;
  cl->Bind2Para = PocBitmapBind2Mandelbrot;
  cl->Bind3Para = PocBitmapBind3Mandelbrot;
  cl->WikiText = PocBitmapWikiMandelbrot;
  cl->Handles = PocBitmapHndMandelbrot;
  cl->ParaWords = 9;
  cl->HelperWords = (sizeof(PocBitmapHelperMandelbrot)+3)/4;
  cl->Flags = 0x1000;
  Doc->Classes.AddTail(cl);

  cl= new wClass;
  cl->Name = L"Perlin";
  cl->Label = L"Perlin";
  cl->OutputType = PocBitmapType;
  cl->TabType = PocBitmapType;
  cl->Command = PocBitmapCmdPerlin;
  cl->MakeGui = PocBitmapGuiPerlin;
  cl->SetDefaults = PocBitmapDefPerlin;
  cl->BindPara = PocBitmapBindPerlin;
  cl->Bind2Para = PocBitmapBind2Perlin;
  cl->Bind3Para = PocBitmapBind3Perlin;
  cl->WikiText = PocBitmapWikiPerlin;
  cl->ParaWords = 10;
  cl->Shortcut = 'p';
  cl->Flags = 0x1000;
  Doc->Classes.AddTail(cl);

  cl= new wClass;
  cl->Name = L"Normals";
  cl->Label = L"Normals";
  cl->OutputType = PocBitmapType;
  cl->TabType = PocBitmapType;
  cl->Command = PocBitmapCmdNormals;
  cl->MakeGui = PocBitmapGuiNormals;
  cl->SetDefaults = PocBitmapDefNormals;
  cl->BindPara = PocBitmapBindNormals;
  cl->Bind2Para = PocBitmapBind2Normals;
  cl->Bind3Para = PocBitmapBind3Normals;
  cl->WikiText = PocBitmapWikiNormals;
  cl->ParaWords = 1;
  cl->Column = 1;
  cl->Flags = 0x1000;
  in = cl->Inputs.AddMany(1);
  in[0].Type = PocBitmapType;
  in[0].DefaultClass = 0;
  in[0].Flags = 0;
  Doc->Classes.AddTail(cl);

  cl= new wClass;
  cl->Name = L"Import";
  cl->Label = L"Import";
  cl->OutputType = PocBitmapType;
  cl->TabType = PocBitmapType;
  cl->Command = PocBitmapCmdImport;
  cl->MakeGui = PocBitmapGuiImport;
  cl->SetDefaults = PocBitmapDefImport;
  cl->BindPara = PocBitmapBindImport;
  cl->Bind2Para = PocBitmapBind2Import;
  cl->Bind3Para = PocBitmapBind3Import;
  cl->WikiText = PocBitmapWikiImport;
  cl->ParaStrings = 1;
  cl->ParaWords = 1;
  cl->FileInMask = 1;
  cl->Flags = 0x1000;
  Doc->Classes.AddTail(cl);

  cl= new wClass;
  cl->Name = L"RotZoom";
  cl->Label = L"RotZoom";
  cl->OutputType = PocBitmapType;
  cl->TabType = PocBitmapType;
  cl->Command = PocBitmapCmdRotZoom;
  cl->MakeGui = PocBitmapGuiRotZoom;
  cl->SetDefaults = PocBitmapDefRotZoom;
  cl->BindPara = PocBitmapBindRotZoom;
  cl->Bind2Para = PocBitmapBind2RotZoom;
  cl->Bind3Para = PocBitmapBind3RotZoom;
  cl->WikiText = PocBitmapWikiRotZoom;
  cl->ParaWords = 9;
  cl->Column = 1;
  cl->Flags = 0x1000;
  in = cl->Inputs.AddMany(1);
  in[0].Type = PocBitmapType;
  in[0].DefaultClass = 0;
  in[0].Flags = 0;
  Doc->Classes.AddTail(cl);

  cl= new wClass;
  cl->Name = L"Atlas";
  cl->Label = L"Atlas";
  cl->OutputType = PocBitmapType;
  cl->TabType = PocBitmapType;
  cl->Command = PocBitmapCmdAtlas;
  cl->MakeGui = PocBitmapGuiAtlas;
  cl->SetDefaults = PocBitmapDefAtlas;
  cl->BindPara = PocBitmapBindAtlas;
  cl->Bind2Para = PocBitmapBind2Atlas;
  cl->Bind3Para = PocBitmapBind3Atlas;
  cl->WikiText = PocBitmapWikiAtlas;
  cl->ParaWords = 2;
  cl->Column = 2;
  cl->Flags = 0x1001;
  in = cl->Inputs.AddMany(1);
  in[0].Type = PocBitmapType;
  in[0].DefaultClass = 0;
  in[0].Flags = 0;
  Doc->Classes.AddTail(cl);

  cl= new wClass;
  cl->Name = L"PreMulAlpha";
  cl->Label = L"PreMulAlpha";
  cl->OutputType = PocBitmapType;
  cl->TabType = PocBitmapType;
  cl->Command = PocBitmapCmdPreMulAlpha;
  cl->MakeGui = PocBitmapGuiPreMulAlpha;
  cl->SetDefaults = PocBitmapDefPreMulAlpha;
  cl->BindPara = PocBitmapBindPreMulAlpha;
  cl->Bind2Para = PocBitmapBind2PreMulAlpha;
  cl->Bind3Para = PocBitmapBind3PreMulAlpha;
  cl->WikiText = PocBitmapWikiPreMulAlpha;
  cl->ParaWords = 1;
  cl->Column = 1;
  cl->Flags = 0x1800;
  in = cl->Inputs.AddMany(1);
  in[0].Type = PocBitmapType;
  in[0].DefaultClass = 0;
  in[0].Flags = 0;
  Doc->Classes.AddTail(cl);

  cl= new wClass;
  cl->Name = L"BlueToAlpha";
  cl->Label = L"BlueToAlpha";
  cl->OutputType = PocBitmapType;
  cl->TabType = PocBitmapType;
  cl->Command = PocBitmapCmdBlueToAlpha;
  cl->MakeGui = PocBitmapGuiBlueToAlpha;
  cl->SetDefaults = PocBitmapDefBlueToAlpha;
  cl->BindPara = PocBitmapBindBlueToAlpha;
  cl->Bind2Para = PocBitmapBind2BlueToAlpha;
  cl->Bind3Para = PocBitmapBind3BlueToAlpha;
  cl->WikiText = PocBitmapWikiBlueToAlpha;
  cl->Column = 1;
  cl->Flags = 0x1800;
  in = cl->Inputs.AddMany(1);
  in[0].Type = PocBitmapType;
  in[0].DefaultClass = 0;
  in[0].Flags = 0;
  Doc->Classes.AddTail(cl);

  cl= new wClass;
  cl->Name = L"Color";
  cl->Label = L"Color";
  cl->OutputType = PocBitmapType;
  cl->TabType = PocBitmapType;
  cl->Command = PocBitmapCmdColor;
  cl->MakeGui = PocBitmapGuiColor;
  cl->SetDefaults = PocBitmapDefColor;
  cl->BindPara = PocBitmapBindColor;
  cl->Bind2Para = PocBitmapBind2Color;
  cl->Bind3Para = PocBitmapBind3Color;
  cl->WikiText = PocBitmapWikiColor;
  cl->ParaWords = 3;
  cl->Column = 1;
  cl->Flags = 0x1800;
  in = cl->Inputs.AddMany(1);
  in[0].Type = PocBitmapType;
  in[0].DefaultClass = 0;
  in[0].Flags = 0;
  Doc->Classes.AddTail(cl);

  cl= new wClass;
  cl->Name = L"SCB";
  cl->Label = L"SCB";
  cl->OutputType = PocBitmapType;
  cl->TabType = PocBitmapType;
  cl->Command = PocBitmapCmdSCB;
  cl->MakeGui = PocBitmapGuiSCB;
  cl->SetDefaults = PocBitmapDefSCB;
  cl->BindPara = PocBitmapBindSCB;
  cl->Bind2Para = PocBitmapBind2SCB;
  cl->Bind3Para = PocBitmapBind3SCB;
  cl->WikiText = PocBitmapWikiSCB;
  cl->ParaWords = 3;
  cl->Column = 1;
  cl->Flags = 0x1800;
  in = cl->Inputs.AddMany(1);
  in[0].Type = PocBitmapType;
  in[0].DefaultClass = 0;
  in[0].Flags = 0;
  Doc->Classes.AddTail(cl);

  cl= new wClass;
  cl->Name = L"ColorBalance";
  cl->Label = L"ColorBalance";
  cl->OutputType = PocBitmapType;
  cl->TabType = PocBitmapType;
  cl->Command = PocBitmapCmdColorBalance;
  cl->MakeGui = PocBitmapGuiColorBalance;
  cl->SetDefaults = PocBitmapDefColorBalance;
  cl->BindPara = PocBitmapBindColorBalance;
  cl->Bind2Para = PocBitmapBind2ColorBalance;
  cl->Bind3Para = PocBitmapBind3ColorBalance;
  cl->WikiText = PocBitmapWikiColorBalance;
  cl->ParaWords = 9;
  cl->Column = 1;
  cl->Flags = 0x1800;
  in = cl->Inputs.AddMany(1);
  in[0].Type = PocBitmapType;
  in[0].DefaultClass = 0;
  in[0].Flags = 0;
  Doc->Classes.AddTail(cl);

  cl= new wClass;
  cl->Name = L"Blur";
  cl->Label = L"Blur";
  cl->OutputType = PocBitmapType;
  cl->TabType = PocBitmapType;
  cl->Command = PocBitmapCmdBlur;
  cl->MakeGui = PocBitmapGuiBlur;
  cl->SetDefaults = PocBitmapDefBlur;
  cl->BindPara = PocBitmapBindBlur;
  cl->Bind2Para = PocBitmapBind2Blur;
  cl->Bind3Para = PocBitmapBind3Blur;
  cl->WikiText = PocBitmapWikiBlur;
  cl->ParaWords = 3;
  cl->Shortcut = 'b';
  cl->Column = 1;
  cl->Flags = 0x1000;
  in = cl->Inputs.AddMany(1);
  in[0].Type = PocBitmapType;
  in[0].DefaultClass = 0;
  in[0].Flags = 0;
  Doc->Classes.AddTail(cl);

  cl= new wClass;
  cl->Name = L"DistanceField";
  cl->Label = L"DistanceField";
  cl->OutputType = PocBitmapType;
  cl->TabType = PocBitmapType;
  cl->Command = PocBitmapCmdDistanceField;
  cl->MakeGui = PocBitmapGuiDistanceField;
  cl->SetDefaults = PocBitmapDefDistanceField;
  cl->BindPara = PocBitmapBindDistanceField;
  cl->Bind2Para = PocBitmapBind2DistanceField;
  cl->Bind3Para = PocBitmapBind3DistanceField;
  cl->WikiText = PocBitmapWikiDistanceField;
  cl->ParaWords = 3;
  cl->Column = 1;
  cl->Flags = 0x1000;
  in = cl->Inputs.AddMany(1);
  in[0].Type = PocBitmapType;
  in[0].DefaultClass = 0;
  in[0].Flags = 0;
  Doc->Classes.AddTail(cl);

  cl= new wClass;
  cl->Name = L"Half";
  cl->Label = L"Half";
  cl->OutputType = PocBitmapType;
  cl->TabType = PocBitmapType;
  cl->Command = PocBitmapCmdHalf;
  cl->MakeGui = PocBitmapGuiHalf;
  cl->SetDefaults = PocBitmapDefHalf;
  cl->BindPara = PocBitmapBindHalf;
  cl->Bind2Para = PocBitmapBind2Half;
  cl->Bind3Para = PocBitmapBind3Half;
  cl->WikiText = PocBitmapWikiHalf;
  cl->Column = 1;
  cl->Flags = 0x0000;
  in = cl->Inputs.AddMany(1);
  in[0].Type = PocBitmapType;
  in[0].DefaultClass = 0;
  in[0].Flags = 0;
  Doc->Classes.AddTail(cl);

  cl= new wClass;
  cl->Name = L"Export";
  cl->Label = L"Export";
  cl->OutputType = PocBitmapType;
  cl->TabType = PocBitmapType;
  cl->Command = PocBitmapCmdExport;
  cl->MakeGui = PocBitmapGuiExport;
  cl->SetDefaults = PocBitmapDefExport;
  cl->BindPara = PocBitmapBindExport;
  cl->Bind2Para = PocBitmapBind2Export;
  cl->Bind3Para = PocBitmapBind3Export;
  cl->WikiText = PocBitmapWikiExport;
  cl->ParaStrings = 1;
  cl->FileOutMask = 1;
  cl->Column = 1;
  cl->Flags = 0x1800;
  in = cl->Inputs.AddMany(1);
  in[0].Type = PocBitmapType;
  in[0].DefaultClass = 0;
  in[0].Flags = 0;
  Doc->Classes.AddTail(cl);

  cl= new wClass;
  cl->Name = L"UnitTestPocBitmap";
  cl->Label = L"UnitTestPocBitmap";
  cl->OutputType = UnitTestType;
  cl->TabType = PocBitmapType;
  cl->Command = UnitTestCmdUnitTestPocBitmap;
  cl->MakeGui = UnitTestGuiUnitTestPocBitmap;
  cl->SetDefaults = UnitTestDefUnitTestPocBitmap;
  cl->BindPara = UnitTestBindUnitTestPocBitmap;
  cl->Bind2Para = UnitTestBind2UnitTestPocBitmap;
  cl->Bind3Para = UnitTestBind3UnitTestPocBitmap;
  cl->WikiText = UnitTestWikiUnitTestPocBitmap;
  cl->ParaStrings = 1;
  cl->ParaWords = 1;
  cl->FileOutMask = 1;
  cl->Column = 3;
  cl->Flags = 0x0000;
  in = cl->Inputs.AddMany(1);
  in[0].Type = PocBitmapType;
  in[0].DefaultClass = 0;
  in[0].Flags = 0;
  Doc->Classes.AddTail(cl);

  cl= new wClass;
  cl->Name = L"Material";
  cl->Label = L"Material";
  cl->OutputType = PocMaterialType;
  cl->TabType = PocMaterialType;
  cl->Command = PocMaterialCmdMaterial;
  cl->MakeGui = PocMaterialGuiMaterial;
  cl->SetDefaults = PocMaterialDefMaterial;
  cl->BindPara = PocMaterialBindMaterial;
  cl->Bind2Para = PocMaterialBind2Material;
  cl->Bind3Para = PocMaterialBind3Material;
  cl->WikiText = PocMaterialWikiMaterial;
  cl->ParaWords = 3;
  cl->Shortcut = 'm';
  cl->Column = 3;
  cl->Flags = 0x0000;
  in = cl->Inputs.AddMany(1);
  in[0].Type = Texture2DType;
  in[0].DefaultClass = 0;
  in[0].Name = L"Texture";
  in[0].Flags = 0|wCIF_OPTIONAL|wCIF_METHODBOTH;
  Doc->Classes.AddTail(cl);

  cl= new wClass;
  cl->Name = L"torus";
  cl->Label = L"torus";
  cl->OutputType = PocMeshType;
  cl->TabType = PocMeshType;
  cl->Command = PocMeshCmdtorus;
  cl->MakeGui = PocMeshGuitorus;
  cl->SetDefaults = PocMeshDeftorus;
  cl->BindPara = PocMeshBindtorus;
  cl->Bind2Para = PocMeshBind2torus;
  cl->Bind3Para = PocMeshBind3torus;
  cl->WikiText = PocMeshWikitorus;
  cl->ParaWords = 5;
  cl->Shortcut = 'o';
  cl->Flags = 0x0000;
  Doc->Classes.AddTail(cl);

  cl= new wClass;
  cl->Name = L"Cube";
  cl->Label = L"Cube";
  cl->OutputType = PocMeshType;
  cl->TabType = PocMeshType;
  cl->Command = PocMeshCmdCube;
  cl->MakeGui = PocMeshGuiCube;
  cl->SetDefaults = PocMeshDefCube;
  cl->BindPara = PocMeshBindCube;
  cl->Bind2Para = PocMeshBind2Cube;
  cl->Bind3Para = PocMeshBind3Cube;
  cl->WikiText = PocMeshWikiCube;
  cl->Shortcut = 'q';
  cl->Flags = 0x0000;
  Doc->Classes.AddTail(cl);

  cl= new wClass;
  cl->Name = L"Add";
  cl->Label = L"Add";
  cl->OutputType = PocMeshType;
  cl->TabType = PocMeshType;
  cl->Command = PocMeshCmdAdd;
  cl->MakeGui = PocMeshGuiAdd;
  cl->SetDefaults = PocMeshDefAdd;
  cl->BindPara = PocMeshBindAdd;
  cl->Bind2Para = PocMeshBind2Add;
  cl->Bind3Para = PocMeshBind3Add;
  cl->WikiText = PocMeshWikiAdd;
  cl->Shortcut = 'a';
  cl->Column = 2;
  cl->Flags = 0x0001;
  in = cl->Inputs.AddMany(1);
  in[0].Type = PocMeshType;
  in[0].DefaultClass = 0;
  in[0].Flags = 0;
  Doc->Classes.AddTail(cl);

  cl= new wClass;
  cl->Name = L"Translate";
  cl->Label = L"Translate";
  cl->OutputType = PocMeshType;
  cl->TabType = PocMeshType;
  cl->Command = PocMeshCmdTranslate;
  cl->MakeGui = PocMeshGuiTranslate;
  cl->SetDefaults = PocMeshDefTranslate;
  cl->BindPara = PocMeshBindTranslate;
  cl->Bind2Para = PocMeshBind2Translate;
  cl->Bind3Para = PocMeshBind3Translate;
  cl->WikiText = PocMeshWikiTranslate;
  cl->ParaWords = 9;
  cl->Shortcut = 't';
  cl->Column = 1;
  cl->Flags = 0x0000;
  in = cl->Inputs.AddMany(1);
  in[0].Type = PocMeshType;
  in[0].DefaultClass = 0;
  in[0].Flags = 0;
  Doc->Classes.AddTail(cl);

  cl= new wClass;
  cl->Name = L"SetMtrl";
  cl->Label = L"SetMtrl";
  cl->OutputType = PocMeshType;
  cl->TabType = PocMeshType;
  cl->Command = PocMeshCmdSetMtrl;
  cl->MakeGui = PocMeshGuiSetMtrl;
  cl->SetDefaults = PocMeshDefSetMtrl;
  cl->BindPara = PocMeshBindSetMtrl;
  cl->Bind2Para = PocMeshBind2SetMtrl;
  cl->Bind3Para = PocMeshBind3SetMtrl;
  cl->WikiText = PocMeshWikiSetMtrl;
  cl->Shortcut = 'm';
  cl->Column = 3;
  cl->Flags = 0x0000;
  in = cl->Inputs.AddMany(2);
  in[0].Type = PocMeshType;
  in[0].DefaultClass = 0;
  in[0].Name = L"Material";
  in[0].Flags = 0|wCIF_METHODBOTH;
  in[1].Type = PocMaterialType;
  in[1].DefaultClass = 0;
  in[1].Flags = 0;
  Doc->Classes.AddTail(cl);

}

// sADDSUBSYSTEM(poc_ops,0x102,AddOps_poc_ops,0);


/****************************************************************************/

