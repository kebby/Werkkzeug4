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
#include "basic_ops.hpp"

#pragma warning(disable:4189) // unused variables - happens in generated code


/****************************************************************************/

class AnyTypeType_ *AnyTypeType;
class GroupTypeType_ *GroupTypeType;
class TextObjectType_ *TextObjectType;
class BitmapBaseType_ *BitmapBaseType;
class Texture2DType_ *Texture2DType;
class CubemapBaseType_ *CubemapBaseType;
class TextureCubeType_ *TextureCubeType;
class MeshBaseType_ *MeshBaseType;
class SceneType_ *SceneType;
class ScreenshotProxyType_ *ScreenshotProxyType;
class UnitTestType_ *UnitTestType;

/****************************************************************************/

#line 13 "basic_ops.ops"

#include "base/graphics.hpp"
#include "wz4lib/wz4gui.hpp"

#line 38 "basic_ops.cpp"

/****************************************************************************/

#line 771 "basic_ops.ops"

  class SceneSelectNameId : public Scene
  {
  public:
    sInt Mode;
    sInt CompareId;
    SceneSelectNameId()
    {
      Mode = 0;
      CompareId = 0;
    }
    void OpFilter(SceneMatrices *sm,sInt begin,sInt end)
    {
      SceneInstances *ss;
      SceneInstance *si;
      sFORALL(sm->Instances,ss)
        ss->Temp = 0;
      for(sInt i=begin;i<end;i++)
      {
        ss = sm->Instances[i];
        sFORALL(ss->Matrices,si)
          si->Temp = (si->NameId==CompareId);
        if(Mode)
          sRemTrue(ss->Matrices,&SceneInstance::Temp);
        else
          sRemFalse(ss->Matrices,&SceneInstance::Temp);
        ss->Temp = (ss->Matrices.GetCount()==0);
      }
      sDeleteTrue(sm->Instances,&SceneInstances::Temp);
    }
  };

#line 75 "basic_ops.cpp"

/****************************************************************************/

#line 905 "basic_ops.ops"

  class SceneMultiply : public Scene
  {
  public:
    sInt Multiply;
    sMatrix34 GroupTrans;
    SceneMultiply()
    {
      Multiply = 2;
    }
    void OpTransform(SceneMatrices *sm)
    {
      sMatrix34 mat;
      mat.Init();
      for(sInt i=0;i<Multiply;i++)
      {
        TransformAdd(sm,mat * GroupTrans);
        mat = mat * Transform;
      }
    }
  };

#line 102 "basic_ops.cpp"

/****************************************************************************/

#line 989 "basic_ops.ops"

  extern void ProgressPaint(sInt count,sInt max);

#line 110 "basic_ops.cpp"

/****************************************************************************/

#line 42 "basic_ops.ops"
void GroupTypeType_::Show(wObject *obj,wPaintInfo &pi)
{
#line 43 "basic_ops.ops"

    pi.DontPaintHandles++;

    GroupType *me = (GroupType *) obj;
    wObject *member;

    sFORALL(me->Members,member)
      Doc->Show(member,pi);

    if(--pi.DontPaintHandles == 0)
      pi.PaintHandles();
  ;
#line 130 "basic_ops.cpp"
}
#line 63 "basic_ops.ops"
void TextObjectType_::Show(wObject *obj,wPaintInfo &pi)
{
#line 64 "basic_ops.ops"

    TextObject *str = (TextObject *)obj;
    if(!pi.Enable3D)
    {
      sGui->FixedFont->SetColor(sGC_TEXT,sGC_DOC);
      sGui->FixedFont->Print(sF2P_MULTILINE|sF2P_LEFT|sF2P_OPAQUE,pi.Client,str->Text.Get());
    }
  ;
#line 144 "basic_ops.cpp"
}
#line 370 "basic_ops.ops"
void Texture2DType_::Show(wObject *obj,wPaintInfo &pi)
{
#line 371 "basic_ops.ops"

    sTextureBase *tex = ((Texture2D *) obj)->Texture;
    if(tex)
    {
      pi.SetSizeTex2D(tex->SizeX,tex->SizeY);
      pi.PaintTex2D(tex->CastTex2D());
    }
  ;
#line 158 "basic_ops.cpp"
}
#line 490 "basic_ops.ops"
void MeshBaseType_::BeginEngine(wPaintInfo &pi,sBool clear)
{
#line 490 "basic_ops.ops"
;
#line 165 "basic_ops.cpp"
}
#line 491 "basic_ops.ops"
void MeshBaseType_::EndEngine(wPaintInfo &pi)
{
#line 491 "basic_ops.ops"
;
#line 172 "basic_ops.cpp"
}
#line 492 "basic_ops.ops"
void MeshBaseType_::Paint(wObject *obj,wPaintInfo &pi,sMatrix34 *mat,sInt matcount)
{
#line 492 "basic_ops.ops"
;
#line 179 "basic_ops.cpp"
}
#line 493 "basic_ops.ops"
void MeshBaseType_::Hit(wObject *obj,const sRay &,wHitInfo &info)
{
#line 493 "basic_ops.ops"
 sClear(info); ;
#line 186 "basic_ops.cpp"
}
#line 494 "basic_ops.ops"
void MeshBaseType_::Wireframe(wObject *obj,wPaintInfo &pi,sMatrix34 &mat)
{
#line 494 "basic_ops.ops"
;
#line 193 "basic_ops.cpp"
}
#line 495 "basic_ops.ops"
void MeshBaseType_::Show(wObject *obj,wPaintInfo &pi)
{
#line 496 "basic_ops.ops"

    if(pi.Enable3D)
    {
      if(pi.Wireframe)
      {
        sSetTarget(sTargetPara(sST_CLEARALL,pi.BackColor,pi.Spec));
        pi.View->SetTargetCurrent();
        pi.View->SetZoom(pi.Zoom3D);
        pi.View->Prepare();
        sMatrix34 mat;
        mat.Init();
        Wireframe(obj,pi,mat);
        pi.PaintHandles();
      }
      else
      {
        sMatrix34 mat;
        mat.Init();
        BeginEngine(pi,pi.ClearFirst);
        pi.ClearFirst = sFALSE;
        Paint(obj,pi,&mat,1);
        EndEngine(pi);
        pi.PaintHandles();
      }
    }
  ;
#line 225 "basic_ops.cpp"
}
#line 543 "basic_ops.ops"
void SceneType_::Show(wObject *obj,wPaintInfo &pi)
{
#line 544 "basic_ops.ops"

    if(pi.Wireframe)
    {
      sSetTarget(sTargetPara(pi.ClearFirst ? sST_CLEARALL : 0,pi.BackColor,pi.Spec));
      pi.ClearFirst = sFALSE;

      pi.View->SetTargetCurrent();
      pi.View->SetZoom(pi.Zoom3D);
      pi.View->Prepare();
      sMatrix34 mat;
      mat.Init();
      Wireframe(obj,pi,mat);
    }
    else
    {
      SceneInstances *inst;
      SceneInstance *mp;
      LastEngine = 0;
      SceneMatrices sm; sm.Seed();

      ((Scene*)obj)->Recurse(&sm);

      sInt maxcount = 1;
      sFORALL(sm.Instances,inst)
        maxcount = sMax(maxcount,inst->Matrices.GetCount());
      sMatrix34 *mat = sALLOCSTACK(sMatrix34,maxcount);

      sBool something = 0;
      sFORALL(sm.Instances,inst)
      {
        if(inst->Object)
        {
          MeshBaseType_* mt = (MeshBaseType_ *)(inst->Object->Type);
          SceneType->SetEngine(mt,pi);
          sFORALL(inst->Matrices,mp)
            mat[_i] = mp->Matrix;
          mt->Paint(inst->Object,pi,mat,inst->Matrices.GetCount());
          something = 1;
        }
      }
      SetEngine(0,pi);
      if(pi.ClearFirst && !something)
      {
        sSetTarget(sTargetPara(sST_CLEARALL,pi.BackColor,pi.Spec));
        pi.ClearFirst = sFALSE;
      }

      sSetTarget(sTargetPara(0,0,pi.Spec));
      pi.PaintHandles();
    }
  ;
#line 282 "basic_ops.cpp"
}
#line 595 "basic_ops.ops"
void SceneType_::SetEngine(MeshBaseType_ *engine,wPaintInfo &pi)
{
#line 596 "basic_ops.ops"

    if(LastEngine!=engine)
    {
      if(LastEngine)
      {
        LastEngine->EndEngine(pi);
        sMatrix34 mat;
        mat.Init();
        pi.View->UpdateModelMatrix(mat);
      }
      LastEngine = engine;
      if(LastEngine)
      {
        LastEngine->BeginEngine(pi,pi.ClearFirst);
        pi.ClearFirst = sFALSE;
      }
    }
  ;
#line 306 "basic_ops.cpp"
}
#line 615 "basic_ops.ops"
void SceneType_::Hit(wObject *obj,const sRay &ray,wHitInfo &info)
{
#line 616 "basic_ops.ops"

    if(obj->IsType(SceneType))
    {
      SceneInstances *inst;
      SceneMatrices sm; sm.Seed();
      wPaintInfo pi;
      sClear(pi);

      ((Scene*)obj)->Recurse(&sm);

      sClear(info);
      wHitInfo newinfo;
      sFORALL(sm.Instances,inst)
      {
        if(inst->Object)
        {
          MeshBaseType_* mt = (MeshBaseType_ *)(inst->Object->Type);
          SceneInstance *mp;
          sFORALL(inst->Matrices,mp)
          {
            // should rotate ray by mp->Matrix here!
            mt->Hit(inst->Object,ray,newinfo);
            if(newinfo.Hit && (!info.Hit || newinfo.Dist<info.Dist))
              info = newinfo;
          }
        }
      }
    }
  ;
#line 341 "basic_ops.cpp"
}
#line 645 "basic_ops.ops"
void SceneType_::Wireframe(wObject *obj,wPaintInfo &pi,sMatrix34 &mat)
{
#line 646 "basic_ops.ops"

    if(obj->IsType(SceneType))
    {
      SceneInstances *inst;
      SceneMatrices sm; sm.Seed();

      ((Scene*)obj)->Recurse(&sm);

      sFORALL(sm.Instances,inst)
      {
        if(inst->Object)
        {
          MeshBaseType_* mt = (MeshBaseType_ *)(inst->Object->Type);
          SceneInstance *mp;
          sFORALL(inst->Matrices,mp)
            mt->Wireframe(inst->Object,pi,mp->Matrix);
        }
      }
    }
  ;
#line 367 "basic_ops.cpp"
}

/****************************************************************************/

sBool TextObjectCmdText(wExecutive *exe,wCommand *cmd)
{
  TextObjectParaText sUNUSED *para = (TextObjectParaText *)(cmd->Data); para;
  TextObject *out = (TextObject *) cmd->Output;
  if(!out) { out=new TextObject; cmd->Output=out; }

  {
#line 81 "basic_ops.ops"

    out->Text = cmd->Strings[0];
  ;
#line 383 "basic_ops.cpp"
    return 1;
  }
}

void TextObjectGuiText(wGridFrameHelper &gh,wOp *op)
{
  TextObjectParaText sUNUSED *para = (TextObjectParaText *)(op->EditData); para;
  gh.Group(op->Class->Label);

  gh.Label(L"Text");
  {
    sTextWindow *tw = gh.Text(op->EditString[0],5,gh.Right-gh.Left);
    tw->SetFont(sGui->FixedFont);
  }
}

void TextObjectDefText(wOp *op)
{
  TextObjectParaText sUNUSED *para = (TextObjectParaText *)(op->EditData); para;
  op->ArrayGroupMode = 0;
}

void TextObjectBindText(wCommand *cmd,ScriptContext *ctx)
{
  ScriptValue *val;
  val = ctx->MakeValue(ScriptTypeString,1);
  val->StringPtr = ((sPoolString *)cmd->Strings)+0;
  ctx->BindLocal(ctx->AddSymbol(L"text"),val);
}
void TextObjectBind2Text(wCommand *cmd,ScriptContext *ctx)
{
  static sInt initdone = 0;
  static sPoolString name[1];
  if(!initdone)
  {
    initdone = 1; 
    name[0] = sPoolString(L"text");
  }
  ctx->AddImport(name[0],ScriptTypeString,1,cmd->Strings+0);
}
void TextObjectBind3Text(wOp *op,sTextBuffer &tb)
{
  tb.PrintF(L"  import text : string;\n");
}
const sChar *TextObjectWikiText =
L"= TextObject : Text\n"
L"\n"
L"!t 2 : 2 3\n"
L" !T 2\n"
L"  !i Name\n"
L"  !i Text\n"
L"\n"
L"  !i Output Type\n"
L"  !i TextObject\n"
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
L" !i Text\n"
L" !i Text\n"
L" !i string\n"
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

sBool TextObjectCmdTextEx(wExecutive *exe,wCommand *cmd)
{
  TextObjectParaTextEx sUNUSED *para = (TextObjectParaTextEx *)(cmd->Data); para;
  TextObject *out = (TextObject *) cmd->Output;
  if(!out) { out=new TextObject; cmd->Output=out; }

  {
#line 93 "basic_ops.ops"

    out->Text = cmd->Strings[0];
  ;
#line 477 "basic_ops.cpp"
    return 1;
  }
}

void TextObjectGuiTextEx(wGridFrameHelper &gh,wOp *op)
{
  TextObjectParaTextEx sUNUSED *para = (TextObjectParaTextEx *)(op->EditData); para;
  gh.Group(op->Class->Label);

  gh.Left = 0;
  {
    sTextWindow *tw = gh.Text(op->EditString[0],20,gh.Grid->Columns-gh.Left);
    tw->SetFont(sGui->FixedFont);
    tw->EditFlags |= sTEF_LINENUMBER;
  }
}

void TextObjectDefTextEx(wOp *op)
{
  TextObjectParaTextEx sUNUSED *para = (TextObjectParaTextEx *)(op->EditData); para;
  op->ArrayGroupMode = 0;
}

void TextObjectBindTextEx(wCommand *cmd,ScriptContext *ctx)
{
  ScriptValue *val;
  val = ctx->MakeValue(ScriptTypeString,1);
  val->StringPtr = ((sPoolString *)cmd->Strings)+0;
  ctx->BindLocal(ctx->AddSymbol(L"text"),val);
}
void TextObjectBind2TextEx(wCommand *cmd,ScriptContext *ctx)
{
  static sInt initdone = 0;
  static sPoolString name[1];
  if(!initdone)
  {
    initdone = 1; 
    name[0] = sPoolString(L"text");
  }
  ctx->AddImport(name[0],ScriptTypeString,1,cmd->Strings+0);
}
void TextObjectBind3TextEx(wOp *op,sTextBuffer &tb)
{
  tb.PrintF(L"  import text : string;\n");
}
const sChar *TextObjectWikiTextEx =
L"= TextObject : TextEx\n"
L"\n"
L"!t 2 : 2 3\n"
L" !T 2\n"
L"  !i Name\n"
L"  !i TextEx\n"
L"\n"
L"  !i Output Type\n"
L"  !i TextObject\n"
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
L" !i Text\n"
L" !i Text\n"
L" !i string\n"
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

sBool TextObjectCmdTextAdd(wExecutive *exe,wCommand *cmd)
{
  TextObjectParaTextAdd sUNUSED *para = (TextObjectParaTextAdd *)(cmd->Data); para;
  TextObject sUNUSED *in0 = cmd->GetInput<TextObject *>(0); in0;
  TextObject *out = (TextObject *) cmd->Output;
  if(!out) { out=new TextObject; cmd->Output=out; }

  {
#line 130 "basic_ops.ops"

    for(sInt i=0;i<cmd->InputCount;i++)
      out->Text.Print(cmd->GetInput<TextObject *>(i)->Text.Get());
  ;
#line 574 "basic_ops.cpp"
    return 1;
  }
}

void TextObjectGuiTextAdd(wGridFrameHelper &gh,wOp *op)
{
  TextObjectParaTextAdd sUNUSED *para = (TextObjectParaTextAdd *)(op->EditData); para;
}

void TextObjectDefTextAdd(wOp *op)
{
  TextObjectParaTextAdd sUNUSED *para = (TextObjectParaTextAdd *)(op->EditData); para;
  op->ArrayGroupMode = 0;
}

void TextObjectBindTextAdd(wCommand *cmd,ScriptContext *ctx)
{
}
void TextObjectBind2TextAdd(wCommand *cmd,ScriptContext *ctx)
{
}
void TextObjectBind3TextAdd(wOp *op,sTextBuffer &tb)
{
}
const sChar *TextObjectWikiTextAdd =
L"= TextObject : TextAdd\n"
L"\n"
L"!t 2 : 2 3\n"
L" !T 2\n"
L"  !i Name\n"
L"  !i TextAdd\n"
L"\n"
L"  !i Output Type\n"
L"  !i TextObject\n"
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
L" !i TextObject\n"
L" !i multiple optional\n"
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

sBool TextObjectCmdTextExport(wExecutive *exe,wCommand *cmd)
{
  TextObjectParaTextExport sUNUSED *para = (TextObjectParaTextExport *)(cmd->Data); para;
  TextObject sUNUSED *in0 = cmd->GetInput<TextObject *>(0); in0;
  TextObject *out = (TextObject *) cmd->Output;
  if(!out) { out=new TextObject; cmd->Output=out; }

  {
#line 143 "basic_ops.ops"

    out->Text = in0->Text;
    sSaveTextAnsi(cmd->Strings[0],in0->Text.Get());
  ;
#line 647 "basic_ops.cpp"
    return 1;
  }
}

void TextObjectGuiTextExport(wGridFrameHelper &gh,wOp *op)
{
  TextObjectParaTextExport sUNUSED *para = (TextObjectParaTextExport *)(op->EditData); para;
  gh.Group(op->Class->Label);

  gh.Label(L"Filename");
  {
    sControl *con = gh.String(op->EditString[0]);
    con->DoneMsg = con->ChangeMsg;
    con->ChangeMsg = sMessage();
    gh.FileSaveDialogMsg.Code = 0;
    gh.Box(L"...",gh.FileSaveDialogMsg);
  }
}

void TextObjectDefTextExport(wOp *op)
{
  TextObjectParaTextExport sUNUSED *para = (TextObjectParaTextExport *)(op->EditData); para;
  op->ArrayGroupMode = 0;
}

void TextObjectBindTextExport(wCommand *cmd,ScriptContext *ctx)
{
  ScriptValue *val;
  val = ctx->MakeValue(ScriptTypeString,1);
  val->StringPtr = ((sPoolString *)cmd->Strings)+0;
  ctx->BindLocal(ctx->AddSymbol(L"filename"),val);
}
void TextObjectBind2TextExport(wCommand *cmd,ScriptContext *ctx)
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
void TextObjectBind3TextExport(wOp *op,sTextBuffer &tb)
{
  tb.PrintF(L"  import filename : string;\n");
}
const sChar *TextObjectWikiTextExport =
L"= TextObject : TextExport\n"
L"\n"
L"!t 2 : 2 3\n"
L" !T 2\n"
L"  !i Name\n"
L"  !i TextExport\n"
L"\n"
L"  !i Output Type\n"
L"  !i TextObject\n"
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
L" !i TextObject\n"
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
L" !i Filename\n"
L" !i \n"
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

void AnyTypeGuiNop(wGridFrameHelper &gh,wOp *op)
{
  AnyTypeParaNop sUNUSED *para = (AnyTypeParaNop *)(op->EditData); para;
}

void AnyTypeDefNop(wOp *op)
{
  AnyTypeParaNop sUNUSED *para = (AnyTypeParaNop *)(op->EditData); para;
  op->ArrayGroupMode = 0;
}

void AnyTypeBindNop(wCommand *cmd,ScriptContext *ctx)
{
}
void AnyTypeBind2Nop(wCommand *cmd,ScriptContext *ctx)
{
}
void AnyTypeBind3Nop(wOp *op,sTextBuffer &tb)
{
}
const sChar *AnyTypeWikiNop =
L"= AnyType : Nop\n"
L"\n"
L"!t 2 : 2 3\n"
L" !T 2\n"
L"  !i Name\n"
L"  !i Nop\n"
L"\n"
L"  !i Output Type\n"
L"  !i AnyType\n"
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
L" !i AnyType\n"
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

sBool AnyTypeCmdComment(wExecutive *exe,wCommand *cmd)
{
  AnyTypeParaComment sUNUSED *para = (AnyTypeParaComment *)(cmd->Data); para;
  AnyType *out = (AnyType *) cmd->Output;
  if(!out) { out=new AnyType; cmd->Output=out; }

  {
#line 168 "basic_ops.ops"
 return 1; ;
#line 809 "basic_ops.cpp"
    return 1;
  }
}

void AnyTypeGuiComment(wGridFrameHelper &gh,wOp *op)
{
  AnyTypeParaComment sUNUSED *para = (AnyTypeParaComment *)(op->EditData); para;
  gh.Group(op->Class->Label);

  gh.Left = 0;
  {
    sTextWindow *tw = gh.Text(op->EditString[0],5,gh.Grid->Columns-gh.Left);
    tw->SetFont(sGui->FixedFont);
  }

  gh.Label(L"Color");
  gh.Flags(&para->Color,L"white|red|yellow|green|cyan|blue|pink|gray",gh.ChangeMsg);
}

void AnyTypeDefComment(wOp *op)
{
  AnyTypeParaComment sUNUSED *para = (AnyTypeParaComment *)(op->EditData); para;
  op->ArrayGroupMode = 0;
}

void AnyTypeBindComment(wCommand *cmd,ScriptContext *ctx)
{
  ScriptValue *val;
  val = ctx->MakeValue(ScriptTypeString,1);
  val->StringPtr = ((sPoolString *)cmd->Strings)+0;
  ctx->BindLocal(ctx->AddSymbol(L"text"),val);
}
void AnyTypeBind2Comment(wCommand *cmd,ScriptContext *ctx)
{
  static sInt initdone = 0;
  static sPoolString name[2];
  if(!initdone)
  {
    initdone = 1; 
    name[0] = sPoolString(L"text");
    name[1] = sPoolString(L"color_");
  }
  ctx->AddImport(name[0],ScriptTypeString,1,cmd->Strings+0);
}
void AnyTypeBind3Comment(wOp *op,sTextBuffer &tb)
{
  tb.PrintF(L"  import text : string;\n");
}
const sChar *AnyTypeWikiComment =
L"= AnyType : Comment\n"
L"\n"
L"!t 2 : 2 3\n"
L" !T 2\n"
L"  !i Name\n"
L"  !i Comment\n"
L"\n"
L"  !i Output Type\n"
L"  !i AnyType\n"
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
L" !i Text\n"
L" !i Text\n"
L" !i string\n"
L" !i *\n"
L"\n"
L"!T 4 : 1 1 1 2\n"
L" !i Color\n"
L" !i Color\n"
L" !i white\n"
L" !i *\n"
L" !i \n"
L" !i \n"
L" !i red\n"
L" !i *\n"
L" !i \n"
L" !i \n"
L" !i yellow\n"
L" !i *\n"
L" !i \n"
L" !i \n"
L" !i green\n"
L" !i *\n"
L" !i \n"
L" !i \n"
L" !i cyan\n"
L" !i *\n"
L" !i \n"
L" !i \n"
L" !i blue\n"
L" !i *\n"
L" !i \n"
L" !i \n"
L" !i pink\n"
L" !i *\n"
L" !i \n"
L" !i \n"
L" !i gray\n"
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

void AnyTypeGuiBlockHandles(wGridFrameHelper &gh,wOp *op)
{
  AnyTypeParaBlockHandles sUNUSED *para = (AnyTypeParaBlockHandles *)(op->EditData); para;
}

void AnyTypeDefBlockHandles(wOp *op)
{
  AnyTypeParaBlockHandles sUNUSED *para = (AnyTypeParaBlockHandles *)(op->EditData); para;
  op->ArrayGroupMode = 0;
}

void AnyTypeBindBlockHandles(wCommand *cmd,ScriptContext *ctx)
{
}
void AnyTypeBind2BlockHandles(wCommand *cmd,ScriptContext *ctx)
{
}
void AnyTypeBind3BlockHandles(wOp *op,sTextBuffer &tb)
{
}
const sChar *AnyTypeWikiBlockHandles =
L"= AnyType : BlockHandles\n"
L"\n"
L"!t 2 : 2 3\n"
L" !T 2\n"
L"  !i Name\n"
L"  !i BlockHandles\n"
L"\n"
L"  !i Output Type\n"
L"  !i AnyType\n"
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
L" !i AnyType\n"
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

sBool AnyTypeCmdDummy(wExecutive *exe,wCommand *cmd)
{
  AnyTypeParaDummy sUNUSED *para = (AnyTypeParaDummy *)(cmd->Data); para;
  AnyType sUNUSED *in0 = cmd->GetInput<AnyType *>(0); in0;
  AnyType *out = (AnyType *) cmd->Output;
  if(!out) { out=new AnyType; cmd->Output=out; }

  {
#line 180 "basic_ops.ops"
 return 1; ;
#line 994 "basic_ops.cpp"
    return 1;
  }
}

void AnyTypeGuiDummy(wGridFrameHelper &gh,wOp *op)
{
  AnyTypeParaDummy sUNUSED *para = (AnyTypeParaDummy *)(op->EditData); para;
}

void AnyTypeDefDummy(wOp *op)
{
  AnyTypeParaDummy sUNUSED *para = (AnyTypeParaDummy *)(op->EditData); para;
  op->ArrayGroupMode = 0;
}

void AnyTypeBindDummy(wCommand *cmd,ScriptContext *ctx)
{
}
void AnyTypeBind2Dummy(wCommand *cmd,ScriptContext *ctx)
{
}
void AnyTypeBind3Dummy(wOp *op,sTextBuffer &tb)
{
}
const sChar *AnyTypeWikiDummy =
L"= AnyType : Dummy\n"
L"\n"
L"!t 2 : 2 3\n"
L" !T 2\n"
L"  !i Name\n"
L"  !i Dummy\n"
L"\n"
L"  !i Output Type\n"
L"  !i AnyType\n"
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
L" !i AnyType\n"
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

sBool AnyTypeCmdDummyObj(wExecutive *exe,wCommand *cmd)
{
  AnyTypeParaDummyObj sUNUSED *para = (AnyTypeParaDummyObj *)(cmd->Data); para;
  AnyType *out = (AnyType *) cmd->Output;
  if(!out) { out=new AnyType; cmd->Output=out; }

  {
#line 187 "basic_ops.ops"
 return 1; ;
#line 1063 "basic_ops.cpp"
    return 1;
  }
}

void AnyTypeGuiDummyObj(wGridFrameHelper &gh,wOp *op)
{
  AnyTypeParaDummyObj sUNUSED *para = (AnyTypeParaDummyObj *)(op->EditData); para;
}

void AnyTypeDefDummyObj(wOp *op)
{
  AnyTypeParaDummyObj sUNUSED *para = (AnyTypeParaDummyObj *)(op->EditData); para;
  op->ArrayGroupMode = 0;
}

void AnyTypeBindDummyObj(wCommand *cmd,ScriptContext *ctx)
{
}
void AnyTypeBind2DummyObj(wCommand *cmd,ScriptContext *ctx)
{
}
void AnyTypeBind3DummyObj(wOp *op,sTextBuffer &tb)
{
}
const sChar *AnyTypeWikiDummyObj =
L"= AnyType : DummyObj\n"
L"\n"
L"!t 2 : 2 3\n"
L" !T 2\n"
L"  !i Name\n"
L"  !i DummyObj\n"
L"\n"
L"  !i Output Type\n"
L"  !i AnyType\n"
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

void AnyTypeGuiStore(wGridFrameHelper &gh,wOp *op)
{
  AnyTypeParaStore sUNUSED *para = (AnyTypeParaStore *)(op->EditData); para;
}

void AnyTypeDefStore(wOp *op)
{
  AnyTypeParaStore sUNUSED *para = (AnyTypeParaStore *)(op->EditData); para;
  op->ArrayGroupMode = 0;
}

void AnyTypeBindStore(wCommand *cmd,ScriptContext *ctx)
{
}
void AnyTypeBind2Store(wCommand *cmd,ScriptContext *ctx)
{
}
void AnyTypeBind3Store(wOp *op,sTextBuffer &tb)
{
}
const sChar *AnyTypeWikiStore =
L"= AnyType : Store\n"
L"\n"
L"!t 2 : 2 3\n"
L" !T 2\n"
L"  !i Name\n"
L"  !i Store\n"
L"\n"
L"  !i Output Type\n"
L"  !i AnyType\n"
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
L" !i AnyType\n"
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

void AnyTypeGuiLoad(wGridFrameHelper &gh,wOp *op)
{
  AnyTypeParaLoad sUNUSED *para = (AnyTypeParaLoad *)(op->EditData); para;
  gh.Group(op->Class->Label);

  gh.Label(L"Link");
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

void AnyTypeDefLoad(wOp *op)
{
  AnyTypeParaLoad sUNUSED *para = (AnyTypeParaLoad *)(op->EditData); para;
  op->ArrayGroupMode = 0;
}

void AnyTypeBindLoad(wCommand *cmd,ScriptContext *ctx)
{
}
void AnyTypeBind2Load(wCommand *cmd,ScriptContext *ctx)
{
  static sInt initdone = 0;
  static sPoolString name[1];
  if(!initdone)
  {
    initdone = 1; 
    name[0] = sPoolString(L"link");
  }
}
void AnyTypeBind3Load(wOp *op,sTextBuffer &tb)
{
}
const sChar *AnyTypeWikiLoad =
L"= AnyType : Load\n"
L"\n"
L"!t 2 : 2 3\n"
L" !T 2\n"
L"  !i Name\n"
L"  !i Load\n"
L"\n"
L"  !i Output Type\n"
L"  !i AnyType\n"
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
L" !i AnyType\n"
L" !i link Link\n"
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
L" !i Link\n"
L" !i Link\n"
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

sBool AnyTypeCmdGroup(wExecutive *exe,wCommand *cmd)
{
  AnyTypeParaGroup sUNUSED *para = (AnyTypeParaGroup *)(cmd->Data); para;
  AnyType sUNUSED *in0 = cmd->GetInput<AnyType *>(0); in0;
  AnyType *out = (AnyType *) cmd->Output;
  if(!out) { out=new AnyType; cmd->Output=out; }

  {
#line 211 "basic_ops.ops"
 return 1; ;
#line 1270 "basic_ops.cpp"
    return 1;
  }
}

void AnyTypeGuiGroup(wGridFrameHelper &gh,wOp *op)
{
  AnyTypeParaGroup sUNUSED *para = (AnyTypeParaGroup *)(op->EditData); para;
}

void AnyTypeDefGroup(wOp *op)
{
  AnyTypeParaGroup sUNUSED *para = (AnyTypeParaGroup *)(op->EditData); para;
  op->ArrayGroupMode = 0;
}

void AnyTypeBindGroup(wCommand *cmd,ScriptContext *ctx)
{
}
void AnyTypeBind2Group(wCommand *cmd,ScriptContext *ctx)
{
}
void AnyTypeBind3Group(wOp *op,sTextBuffer &tb)
{
}
const sChar *AnyTypeWikiGroup =
L"= AnyType : Group\n"
L"\n"
L"!t 2 : 2 3\n"
L" !T 2\n"
L"  !i Name\n"
L"  !i Group\n"
L"\n"
L"  !i Output Type\n"
L"  !i AnyType\n"
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
L" !i AnyType\n"
L" !i multiple optional\n"
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

sBool GroupTypeCmdGroup3D(wExecutive *exe,wCommand *cmd)
{
  GroupTypeParaGroup3D sUNUSED *para = (GroupTypeParaGroup3D *)(cmd->Data); para;
  AnyType sUNUSED *in0 = cmd->GetInput<AnyType *>(0); in0;
  GroupType *out = (GroupType *) cmd->Output;
  if(!out) { out=new GroupType; cmd->Output=out; }

  {
#line 218 "basic_ops.ops"

    for(sInt i=0;i<cmd->InputCount;i++)
      out->Add(cmd->GetInput<wObject*>(i));
  ;
#line 1343 "basic_ops.cpp"
    return 1;
  }
}

void GroupTypeGuiGroup3D(wGridFrameHelper &gh,wOp *op)
{
  GroupTypeParaGroup3D sUNUSED *para = (GroupTypeParaGroup3D *)(op->EditData); para;
}

void GroupTypeDefGroup3D(wOp *op)
{
  GroupTypeParaGroup3D sUNUSED *para = (GroupTypeParaGroup3D *)(op->EditData); para;
  op->ArrayGroupMode = 0;
}

void GroupTypeBindGroup3D(wCommand *cmd,ScriptContext *ctx)
{
}
void GroupTypeBind2Group3D(wCommand *cmd,ScriptContext *ctx)
{
}
void GroupTypeBind3Group3D(wOp *op,sTextBuffer &tb)
{
}
const sChar *GroupTypeWikiGroup3D =
L"= GroupType : Group3D\n"
L"\n"
L"!t 2 : 2 3\n"
L" !T 2\n"
L"  !i Name\n"
L"  !i Group3D\n"
L"\n"
L"  !i Output Type\n"
L"  !i GroupType\n"
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
L" !i AnyType\n"
L" !i multiple optional\n"
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

sBool AnyTypeCmdSlow(wExecutive *exe,wCommand *cmd)
{
  AnyTypeParaSlow sUNUSED *para = (AnyTypeParaSlow *)(cmd->Data); para;
  AnyType sUNUSED *in0 = cmd->GetInput<AnyType *>(0); in0;
  AnyType *out = (AnyType *) cmd->Output;
  if(!out) { out=new AnyType; cmd->Output=out; }

  {
#line 230 "basic_ops.ops"
 
    cmd->Output->Release();
    cmd->Output = in0;
    cmd->Output->AddRef();
  ;
#line 1417 "basic_ops.cpp"
    return 1;
  }
}

void AnyTypeGuiSlow(wGridFrameHelper &gh,wOp *op)
{
  AnyTypeParaSlow sUNUSED *para = (AnyTypeParaSlow *)(op->EditData); para;
}

void AnyTypeDefSlow(wOp *op)
{
  AnyTypeParaSlow sUNUSED *para = (AnyTypeParaSlow *)(op->EditData); para;
  op->ArrayGroupMode = 0;
}

void AnyTypeBindSlow(wCommand *cmd,ScriptContext *ctx)
{
}
void AnyTypeBind2Slow(wCommand *cmd,ScriptContext *ctx)
{
}
void AnyTypeBind3Slow(wOp *op,sTextBuffer &tb)
{
}
const sChar *AnyTypeWikiSlow =
L"= AnyType : Slow\n"
L"\n"
L"!t 2 : 2 3\n"
L" !T 2\n"
L"  !i Name\n"
L"  !i Slow\n"
L"\n"
L"  !i Output Type\n"
L"  !i AnyType\n"
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
L" !i AnyType\n"
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

sBool AnyTypeCmdUnknownOp(wExecutive *exe,wCommand *cmd)
{
  AnyTypeParaUnknownOp sUNUSED *para = (AnyTypeParaUnknownOp *)(cmd->Data); para;
  AnyType *out = (AnyType *) cmd->Output;
  if(!out) { out=new AnyType; cmd->Output=out; }

  {
#line 242 "basic_ops.ops"

    return 0;
  ;
#line 1488 "basic_ops.cpp"
    return 1;
  }
}

void AnyTypeGuiUnknownOp(wGridFrameHelper &gh,wOp *op)
{
  AnyTypeParaUnknownOp sUNUSED *para = (AnyTypeParaUnknownOp *)(op->EditData); para;
}

void AnyTypeDefUnknownOp(wOp *op)
{
  AnyTypeParaUnknownOp sUNUSED *para = (AnyTypeParaUnknownOp *)(op->EditData); para;
  op->ArrayGroupMode = 0;
}

void AnyTypeBindUnknownOp(wCommand *cmd,ScriptContext *ctx)
{
}
void AnyTypeBind2UnknownOp(wCommand *cmd,ScriptContext *ctx)
{
}
void AnyTypeBind3UnknownOp(wOp *op,sTextBuffer &tb)
{
}
const sChar *AnyTypeWikiUnknownOp =
L"= AnyType : UnknownOp\n"
L"\n"
L"!t 2 : 2 3\n"
L" !T 2\n"
L"  !i Name\n"
L"  !i UnknownOp\n"
L"\n"
L"  !i Output Type\n"
L"  !i AnyType\n"
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

sBool AnyTypeCmdBlockChange(wExecutive *exe,wCommand *cmd)
{
  AnyTypeParaBlockChange sUNUSED *para = (AnyTypeParaBlockChange *)(cmd->Data); para;
  AnyType sUNUSED *in0 = cmd->GetInput<AnyType *>(0); in0;
  AnyType *out = (AnyType *) cmd->Output;
  if(!out) { out=new AnyType; cmd->Output=out; }

  {
#line 252 "basic_ops.ops"

    cmd->Output->Release();
    cmd->Output = in0;
    cmd->Output->AddRef();
  ;
#line 1550 "basic_ops.cpp"
    return 1;
  }
}

void AnyTypeGuiBlockChange(wGridFrameHelper &gh,wOp *op)
{
  AnyTypeParaBlockChange sUNUSED *para = (AnyTypeParaBlockChange *)(op->EditData); para;
}

void AnyTypeDefBlockChange(wOp *op)
{
  AnyTypeParaBlockChange sUNUSED *para = (AnyTypeParaBlockChange *)(op->EditData); para;
  op->ArrayGroupMode = 0;
}

void AnyTypeBindBlockChange(wCommand *cmd,ScriptContext *ctx)
{
}
void AnyTypeBind2BlockChange(wCommand *cmd,ScriptContext *ctx)
{
}
void AnyTypeBind3BlockChange(wOp *op,sTextBuffer &tb)
{
}
const sChar *AnyTypeWikiBlockChange =
L"= AnyType : BlockChange\n"
L"\n"
L"!t 2 : 2 3\n"
L" !T 2\n"
L"  !i Name\n"
L"  !i BlockChange\n"
L"\n"
L"  !i Output Type\n"
L"  !i AnyType\n"
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
L" !i AnyType\n"
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

sBool AnyTypeCmdCopy(wExecutive *exe,wCommand *cmd)
{
  AnyTypeParaCopy sUNUSED *para = (AnyTypeParaCopy *)(cmd->Data); para;
  AnyType sUNUSED *in0 = cmd->GetInput<AnyType *>(0); in0;
  AnyType *out = (AnyType *) cmd->Output;
  if(!out) { out=new AnyType; cmd->Output=out; }

  {
#line 264 "basic_ops.ops"

    cmd->Output->Release();
    cmd->Output = in0->Copy();
    if(cmd->Output==0)
    {
      sDPrintF(L"could not create a copy of objecte from type %q\n",in0->Type->Symbol);
      return 0;
    }
  ;
#line 1628 "basic_ops.cpp"
    return 1;
  }
}

void AnyTypeGuiCopy(wGridFrameHelper &gh,wOp *op)
{
  AnyTypeParaCopy sUNUSED *para = (AnyTypeParaCopy *)(op->EditData); para;
}

void AnyTypeDefCopy(wOp *op)
{
  AnyTypeParaCopy sUNUSED *para = (AnyTypeParaCopy *)(op->EditData); para;
  op->ArrayGroupMode = 0;
}

void AnyTypeBindCopy(wCommand *cmd,ScriptContext *ctx)
{
}
void AnyTypeBind2Copy(wCommand *cmd,ScriptContext *ctx)
{
}
void AnyTypeBind3Copy(wOp *op,sTextBuffer &tb)
{
}
const sChar *AnyTypeWikiCopy =
L"= AnyType : Copy\n"
L"\n"
L"!t 2 : 2 3\n"
L" !T 2\n"
L"  !i Name\n"
L"  !i Copy\n"
L"\n"
L"  !i Output Type\n"
L"  !i AnyType\n"
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
L" !i AnyType\n"
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

void AnyTypeGuiCall(wGridFrameHelper &gh,wOp *op)
{
  AnyTypeParaCall sUNUSED *para = (AnyTypeParaCall *)(op->EditData); para;
  gh.Group(op->Class->Label);

  gh.Label(L"Link");
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

  gh.Label(L"Spread Variables");
  gh.Flags(&para->Flags,L"on|off",gh.ChangeMsg);
}

void AnyTypeDefCall(wOp *op)
{
  AnyTypeParaCall sUNUSED *para = (AnyTypeParaCall *)(op->EditData); para;
  op->ArrayGroupMode = 0;
}

void AnyTypeBindCall(wCommand *cmd,ScriptContext *ctx)
{
}
void AnyTypeBind2Call(wCommand *cmd,ScriptContext *ctx)
{
  static sInt initdone = 0;
  static sPoolString name[2];
  if(!initdone)
  {
    initdone = 1; 
    name[0] = sPoolString(L"link");
    name[1] = sPoolString(L"flags");
  }
}
void AnyTypeBind3Call(wOp *op,sTextBuffer &tb)
{
}
const sChar *AnyTypeWikiCall =
L"= AnyType : Call\n"
L"\n"
L"!t 2 : 2 3\n"
L" !T 2\n"
L"  !i Name\n"
L"  !i Call\n"
L"\n"
L"  !i Output Type\n"
L"  !i AnyType\n"
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
L" !i AnyType\n"
L" !i link Link\n"
L" !i *\n"
L"\n"
L" !i AnyType\n"
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
L" !i Link\n"
L" !i Link\n"
L" !i link\n"
L" !i *\n"
L"\n"
L"!T 4 : 1 1 1 2\n"
L" !i Spread Variables\n"
L" !i Flags\n"
L" !i on\n"
L" !i *\n"
L" !i \n"
L" !i \n"
L" !i off\n"
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

void AnyTypeGuiCallWithInputLinks(wGridFrameHelper &gh,wOp *op)
{
  AnyTypeParaCallWithInputLinks sUNUSED *para = (AnyTypeParaCallWithInputLinks *)(op->EditData); para;
  gh.Group(op->Class->Label);

  gh.Label(L"Link");
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

  gh.Label(L"Link");
  gh.Flags(&op->Links[1].Select,L"|link|unused| 1| 2| 3| 4| 5",gh.ConnectLayoutMsg);
  if(op->Links[1].Select==1)
  {
    sControl *con=gh.String(op->Links[1].LinkName,gh.LabelWidth+gh.WideWidth-gh.Left);
    con->ChangeMsg = gh.ConnectMsg;
    con->DoneMsg = gh.ConnectLayoutMsg;
    sMessage msg = gh.LinkBrowserMsg; msg.Code = 1;
    gh.Box(L"...",msg);
    msg = gh.LinkPopupMsg; msg.Code = 1;
    gh.Box(L"..",msg);
    if(!op->Links[1].LinkName.IsEmpty())
    {
      msg = gh.LinkGotoMsg; msg.Code = 1;
      gh.Box(L"->",msg);
    }
  }

  gh.Label(L"Link");
  gh.Flags(&op->Links[2].Select,L"|link|unused| 1| 2| 3| 4| 5",gh.ConnectLayoutMsg);
  if(op->Links[2].Select==1)
  {
    sControl *con=gh.String(op->Links[2].LinkName,gh.LabelWidth+gh.WideWidth-gh.Left);
    con->ChangeMsg = gh.ConnectMsg;
    con->DoneMsg = gh.ConnectLayoutMsg;
    sMessage msg = gh.LinkBrowserMsg; msg.Code = 2;
    gh.Box(L"...",msg);
    msg = gh.LinkPopupMsg; msg.Code = 2;
    gh.Box(L"..",msg);
    if(!op->Links[2].LinkName.IsEmpty())
    {
      msg = gh.LinkGotoMsg; msg.Code = 2;
      gh.Box(L"->",msg);
    }
  }

  gh.Label(L"Link");
  gh.Flags(&op->Links[3].Select,L"|link|unused| 1| 2| 3| 4| 5",gh.ConnectLayoutMsg);
  if(op->Links[3].Select==1)
  {
    sControl *con=gh.String(op->Links[3].LinkName,gh.LabelWidth+gh.WideWidth-gh.Left);
    con->ChangeMsg = gh.ConnectMsg;
    con->DoneMsg = gh.ConnectLayoutMsg;
    sMessage msg = gh.LinkBrowserMsg; msg.Code = 3;
    gh.Box(L"...",msg);
    msg = gh.LinkPopupMsg; msg.Code = 3;
    gh.Box(L"..",msg);
    if(!op->Links[3].LinkName.IsEmpty())
    {
      msg = gh.LinkGotoMsg; msg.Code = 3;
      gh.Box(L"->",msg);
    }
  }

  gh.Label(L"Link");
  gh.Flags(&op->Links[4].Select,L"|link|unused| 1| 2| 3| 4| 5",gh.ConnectLayoutMsg);
  if(op->Links[4].Select==1)
  {
    sControl *con=gh.String(op->Links[4].LinkName,gh.LabelWidth+gh.WideWidth-gh.Left);
    con->ChangeMsg = gh.ConnectMsg;
    con->DoneMsg = gh.ConnectLayoutMsg;
    sMessage msg = gh.LinkBrowserMsg; msg.Code = 4;
    gh.Box(L"...",msg);
    msg = gh.LinkPopupMsg; msg.Code = 4;
    gh.Box(L"..",msg);
    if(!op->Links[4].LinkName.IsEmpty())
    {
      msg = gh.LinkGotoMsg; msg.Code = 4;
      gh.Box(L"->",msg);
    }
  }

  gh.Label(L"Spread Variables");
  gh.Flags(&para->Flags,L"on|off",gh.ChangeMsg);
}

void AnyTypeDefCallWithInputLinks(wOp *op)
{
  AnyTypeParaCallWithInputLinks sUNUSED *para = (AnyTypeParaCallWithInputLinks *)(op->EditData); para;
  op->ArrayGroupMode = 0;
}

void AnyTypeBindCallWithInputLinks(wCommand *cmd,ScriptContext *ctx)
{
}
void AnyTypeBind2CallWithInputLinks(wCommand *cmd,ScriptContext *ctx)
{
  static sInt initdone = 0;
  static sPoolString name[6];
  if(!initdone)
  {
    initdone = 1; 
    name[0] = sPoolString(L"link");
    name[1] = sPoolString(L"link");
    name[2] = sPoolString(L"link");
    name[3] = sPoolString(L"link");
    name[4] = sPoolString(L"link");
    name[5] = sPoolString(L"flags");
  }
}
void AnyTypeBind3CallWithInputLinks(wOp *op,sTextBuffer &tb)
{
}
const sChar *AnyTypeWikiCallWithInputLinks =
L"= AnyType : CallWithInputLinks\n"
L"\n"
L"!t 2 : 2 3\n"
L" !T 2\n"
L"  !i Name\n"
L"  !i CallWithInputLinks\n"
L"\n"
L"  !i Output Type\n"
L"  !i AnyType\n"
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
L" !i AnyType\n"
L" !i link Link\n"
L" !i *\n"
L"\n"
L" !i AnyType\n"
L" !i optional link Link\n"
L" !i *\n"
L"\n"
L" !i AnyType\n"
L" !i optional link Link\n"
L" !i *\n"
L"\n"
L" !i AnyType\n"
L" !i optional link Link\n"
L" !i *\n"
L"\n"
L" !i AnyType\n"
L" !i optional link Link\n"
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
L" !i Link\n"
L" !i Link\n"
L" !i link\n"
L" !i *\n"
L"\n"
L" !i Link\n"
L" !i Link\n"
L" !i link\n"
L" !i *\n"
L"\n"
L" !i Link\n"
L" !i Link\n"
L" !i link\n"
L" !i *\n"
L"\n"
L" !i Link\n"
L" !i Link\n"
L" !i link\n"
L" !i *\n"
L"\n"
L" !i Link\n"
L" !i Link\n"
L" !i link\n"
L" !i *\n"
L"\n"
L"!T 4 : 1 1 1 2\n"
L" !i Spread Variables\n"
L" !i Flags\n"
L" !i on\n"
L" !i *\n"
L" !i \n"
L" !i \n"
L" !i off\n"
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

void AnyTypeGuiInput(wGridFrameHelper &gh,wOp *op)
{
  AnyTypeParaInput sUNUSED *para = (AnyTypeParaInput *)(op->EditData); para;
  gh.Group(op->Class->Label);

  gh.Label(L"Input");
  sIntControl *int_Input = gh.Int(&para->Input,0,255,0.125000f);
  int_Input->Default = 0x00000000; int_Input->RightStep = 0.125000f;
}

void AnyTypeDefInput(wOp *op)
{
  AnyTypeParaInput sUNUSED *para = (AnyTypeParaInput *)(op->EditData); para;
  op->ArrayGroupMode = 0;
}

void AnyTypeBindInput(wCommand *cmd,ScriptContext *ctx)
{
  ScriptValue *val;
  val = ctx->MakeValue(ScriptTypeInt,1);
  val->IntPtr = ((sInt *)cmd->Data)+0;
  ctx->BindLocal(ctx->AddSymbol(L"input"),val);
}
void AnyTypeBind2Input(wCommand *cmd,ScriptContext *ctx)
{
  static sInt initdone = 0;
  static sPoolString name[1];
  if(!initdone)
  {
    initdone = 1; 
    name[0] = sPoolString(L"input");
  }
  ctx->AddImport(name[0],ScriptTypeInt,1,cmd->Data+0);
}
void AnyTypeBind3Input(wOp *op,sTextBuffer &tb)
{
  tb.PrintF(L"  import input : int;\n");
}
const sChar *AnyTypeWikiInput =
L"= AnyType : Input\n"
L"\n"
L"!t 2 : 2 3\n"
L" !T 2\n"
L"  !i Name\n"
L"  !i Input\n"
L"\n"
L"  !i Output Type\n"
L"  !i AnyType\n"
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
L" !i Input\n"
L" !i Input\n"
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

void AnyTypeGuiInjectGlobals(wGridFrameHelper &gh,wOp *op)
{
  AnyTypeParaInjectGlobals sUNUSED *para = (AnyTypeParaInjectGlobals *)(op->EditData); para;
  gh.Group(op->Class->Label);

  gh.Label(L"InjectFrom");
  {
    sControl *con=gh.String(op->Links[1].LinkName,gh.LabelWidth+gh.WideWidth-gh.Left);
    con->ChangeMsg = gh.ConnectMsg;
    con->DoneMsg = gh.ConnectLayoutMsg;
    sMessage msg = gh.LinkBrowserMsg; msg.Code = 1;
    gh.Box(L"...",msg);
    msg = gh.LinkPopupMsg; msg.Code = 1;
    gh.Box(L"..",msg);
    if(!op->Links[1].LinkName.IsEmpty())
    {
      msg = gh.LinkGotoMsg; msg.Code = 1;
      gh.Box(L"->",msg);
    }
  }
}

void AnyTypeDefInjectGlobals(wOp *op)
{
  AnyTypeParaInjectGlobals sUNUSED *para = (AnyTypeParaInjectGlobals *)(op->EditData); para;
  op->ArrayGroupMode = 0;
}

void AnyTypeBindInjectGlobals(wCommand *cmd,ScriptContext *ctx)
{
}
void AnyTypeBind2InjectGlobals(wCommand *cmd,ScriptContext *ctx)
{
  static sInt initdone = 0;
  static sPoolString name[1];
  if(!initdone)
  {
    initdone = 1; 
    name[0] = sPoolString(L"injectfrom");
  }
}
void AnyTypeBind3InjectGlobals(wOp *op,sTextBuffer &tb)
{
}
const sChar *AnyTypeWikiInjectGlobals =
L"= AnyType : InjectGlobals\n"
L"\n"
L"!t 2 : 2 3\n"
L" !T 2\n"
L"  !i Name\n"
L"  !i InjectGlobals\n"
L"\n"
L"  !i Output Type\n"
L"  !i AnyType\n"
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
L" !i AnyType\n"
L" !i defaults to: Dummy\n"
L" !i *\n"
L"\n"
L" !i AnyType\n"
L" !i link InjectFrom\n"
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
L" !i InjectFrom\n"
L" !i InjectFrom\n"
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

void AnyTypeGuiLoop(wGridFrameHelper &gh,wOp *op)
{
  AnyTypeParaLoop sUNUSED *para = (AnyTypeParaLoop *)(op->EditData); para;
  gh.Group(op->Class->Label);

  gh.Label(L"from 0 to n-1");
  sIntControl *int_Max = gh.Int(&para->Max,1,256,0.125000f);
  int_Max->Default = 0x00000004; int_Max->RightStep = 0.125000f;

  gh.Label(L"Variable");
  gh.String(op->EditString[0]);
}

void AnyTypeDefLoop(wOp *op)
{
  AnyTypeParaLoop sUNUSED *para = (AnyTypeParaLoop *)(op->EditData); para;
  op->ArrayGroupMode = 0;
  para->Max = 0x00000004;
  *op->EditString[0] = L"i";
}

void AnyTypeBindLoop(wCommand *cmd,ScriptContext *ctx)
{
  ScriptValue *val;
  val = ctx->MakeValue(ScriptTypeInt,1);
  val->IntPtr = ((sInt *)cmd->Data)+0;
  ctx->BindLocal(ctx->AddSymbol(L"max"),val);
  val = ctx->MakeValue(ScriptTypeString,1);
  val->StringPtr = ((sPoolString *)cmd->Strings)+0;
  ctx->BindLocal(ctx->AddSymbol(L"variable"),val);
}
void AnyTypeBind2Loop(wCommand *cmd,ScriptContext *ctx)
{
  static sInt initdone = 0;
  static sPoolString name[2];
  if(!initdone)
  {
    initdone = 1; 
    name[0] = sPoolString(L"max");
    name[1] = sPoolString(L"variable");
  }
  ctx->AddImport(name[0],ScriptTypeInt,1,cmd->Data+0);
  ctx->AddImport(name[1],ScriptTypeString,1,cmd->Strings+0);
}
void AnyTypeBind3Loop(wOp *op,sTextBuffer &tb)
{
  tb.PrintF(L"  import max : int;\n");
  tb.PrintF(L"  import variable : string;\n");
}
const sChar *AnyTypeWikiLoop =
L"= AnyType : Loop\n"
L"\n"
L"!t 2 : 2 3\n"
L" !T 2\n"
L"  !i Name\n"
L"  !i Loop\n"
L"\n"
L"  !i Output Type\n"
L"  !i AnyType\n"
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
L" !i AnyType\n"
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
L" !i from 0 to n-1\n"
L" !i Max\n"
L" !i int\n"
L" !i *\n"
L"\n"
L" !i Variable\n"
L" !i Variable\n"
L" !i string\n"
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

void AnyTypeGuiEndLoop(wGridFrameHelper &gh,wOp *op)
{
  AnyTypeParaEndLoop sUNUSED *para = (AnyTypeParaEndLoop *)(op->EditData); para;
}

void AnyTypeDefEndLoop(wOp *op)
{
  AnyTypeParaEndLoop sUNUSED *para = (AnyTypeParaEndLoop *)(op->EditData); para;
  op->ArrayGroupMode = 0;
}

void AnyTypeBindEndLoop(wCommand *cmd,ScriptContext *ctx)
{
}
void AnyTypeBind2EndLoop(wCommand *cmd,ScriptContext *ctx)
{
}
void AnyTypeBind3EndLoop(wOp *op,sTextBuffer &tb)
{
}
const sChar *AnyTypeWikiEndLoop =
L"= AnyType : EndLoop\n"
L"\n"
L"!t 2 : 2 3\n"
L" !T 2\n"
L"  !i Name\n"
L"  !i EndLoop\n"
L"\n"
L"  !i Output Type\n"
L"  !i AnyType\n"
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
L" !i AnyType\n"
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

void AnyTypeGuiShellSwitch(wGridFrameHelper &gh,wOp *op)
{
  AnyTypeParaShellSwitch sUNUSED *para = (AnyTypeParaShellSwitch *)(op->EditData); para;
  gh.Group(op->Class->Label);

  gh.Label(L"Condition");
  gh.Flags(&para->Condition,L"*8-|not",gh.ChangeMsg);

  gh.Label(L"Condition");
  gh.Flags(&para->Condition,Doc->ShellSwitchChoice,gh.ChangeMsg);
}

void AnyTypeDefShellSwitch(wOp *op)
{
  AnyTypeParaShellSwitch sUNUSED *para = (AnyTypeParaShellSwitch *)(op->EditData); para;
  op->ArrayGroupMode = 0;
}

void AnyTypeBindShellSwitch(wCommand *cmd,ScriptContext *ctx)
{
}
void AnyTypeBind2ShellSwitch(wCommand *cmd,ScriptContext *ctx)
{
  static sInt initdone = 0;
  static sPoolString name[2];
  if(!initdone)
  {
    initdone = 1; 
    name[0] = sPoolString(L"condition");
    name[1] = sPoolString(L"condition");
  }
}
void AnyTypeBind3ShellSwitch(wOp *op,sTextBuffer &tb)
{
}
const sChar *AnyTypeWikiShellSwitch =
L"= AnyType : ShellSwitch\n"
L"\n"
L"!t 2 : 2 3\n"
L" !T 2\n"
L"  !i Name\n"
L"  !i ShellSwitch\n"
L"\n"
L"  !i Output Type\n"
L"  !i AnyType\n"
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
L" !i AnyType\n"
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
L" !i Condition\n"
L" !i Condition\n"
L" !i not\n"
L" !i *\n"
L"!T 4 : 1 1 1 2\n"
L" !i Condition\n"
L" !i Condition\n"
L" !i *Doc->ShellSwitchChoice\n"
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

sBool Texture2DCmdMakeTexture(wExecutive *exe,wCommand *cmd)
{
  Texture2DParaMakeTexture sUNUSED *para = (Texture2DParaMakeTexture *)(cmd->Data); para;
  BitmapBase sUNUSED *in0 = cmd->GetInput<BitmapBase *>(0); in0;
  Texture2D *out = (Texture2D *) cmd->Output;
  if(!out) { out=new Texture2D; cmd->Output=out; }

  {
#line 390 "basic_ops.ops"

    static sInt modes[] = 
    { 
      sTEX_ARGB8888,sTEX_A8,sTEX_I8,sTEX_DXT1,sTEX_DXT1A,sTEX_DXT3,sTEX_DXT5 
    };

    sInt flags = modes[para->Format]|sTEX_2D;
    if(para->Flags & 1) flags |= sTEX_NOMIPMAPS;

    out->ConvertFrom(in0,flags);
    out->Atlas=in0->Atlas;
    return 1;
  ;
#line 2463 "basic_ops.cpp"
    return 1;
  }
}

void Texture2DGuiMakeTexture(wGridFrameHelper &gh,wOp *op)
{
  Texture2DParaMakeTexture sUNUSED *para = (Texture2DParaMakeTexture *)(op->EditData); para;
  gh.Group(op->Class->Label);

  gh.Label(L"Format");
  gh.Flags(&para->Format,L"argb8888|a8|i8|DXT1|DXT1A|DXT3|DXT5",gh.ChangeMsg);

  gh.Label(L"Flags");
  gh.Flags(&para->Flags,L"-|no mipmaps",gh.ChangeMsg);
}

void Texture2DDefMakeTexture(wOp *op)
{
  Texture2DParaMakeTexture sUNUSED *para = (Texture2DParaMakeTexture *)(op->EditData); para;
  op->ArrayGroupMode = 0;
}

void Texture2DBindMakeTexture(wCommand *cmd,ScriptContext *ctx)
{
}
void Texture2DBind2MakeTexture(wCommand *cmd,ScriptContext *ctx)
{
  static sInt initdone = 0;
  static sPoolString name[2];
  if(!initdone)
  {
    initdone = 1; 
    name[0] = sPoolString(L"format");
    name[1] = sPoolString(L"flags");
  }
}
void Texture2DBind3MakeTexture(wOp *op,sTextBuffer &tb)
{
}
const sChar *Texture2DWikiMakeTexture =
L"= Texture2D : MakeTexture\n"
L"\n"
L"!t 2 : 2 3\n"
L" !T 2\n"
L"  !i Name\n"
L"  !i MakeTexture\n"
L"\n"
L"  !i Output Type\n"
L"  !i Texture2D\n"
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
L" !i BitmapBase\n"
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
L" !i Format\n"
L" !i Format\n"
L" !i argb8888\n"
L" !i *\n"
L" !i \n"
L" !i \n"
L" !i a8\n"
L" !i *\n"
L" !i \n"
L" !i \n"
L" !i i8\n"
L" !i *\n"
L" !i \n"
L" !i \n"
L" !i DXT1\n"
L" !i *\n"
L" !i \n"
L" !i \n"
L" !i DXT1A\n"
L" !i *\n"
L" !i \n"
L" !i \n"
L" !i DXT3\n"
L" !i *\n"
L" !i \n"
L" !i \n"
L" !i DXT5\n"
L" !i *\n"
L"!T 4 : 1 1 1 2\n"
L" !i Flags\n"
L" !i Flags\n"
L" !i no mipmaps\n"
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

sBool Texture2DCmdExport(wExecutive *exe,wCommand *cmd)
{
  Texture2DParaExport sUNUSED *para = (Texture2DParaExport *)(cmd->Data); para;
  Texture2D sUNUSED *in0 = cmd->GetInput<Texture2D *>(0); in0;
  Texture2D *out = (Texture2D *) cmd->Output;
  if(!out) { out=new Texture2D; out->CopyFrom(in0); cmd->Output=out; }

  {
#line 417 "basic_ops.ops"

    sSaveObject(cmd->Strings[0],out);
    return 1;
  ;
#line 2595 "basic_ops.cpp"
    return 1;
  }
}

void Texture2DGuiExport(wGridFrameHelper &gh,wOp *op)
{
  Texture2DParaExport sUNUSED *para = (Texture2DParaExport *)(op->EditData); para;
  gh.Group(op->Class->Label);

  gh.Label(L"Filename");
  {
    sControl *con = gh.String(op->EditString[0]);
    con->DoneMsg = con->ChangeMsg;
    con->ChangeMsg = sMessage();
    gh.FileSaveDialogMsg.Code = 0;
    gh.Box(L"...",gh.FileSaveDialogMsg);
  }
}

void Texture2DDefExport(wOp *op)
{
  Texture2DParaExport sUNUSED *para = (Texture2DParaExport *)(op->EditData); para;
  op->ArrayGroupMode = 0;
}

void Texture2DBindExport(wCommand *cmd,ScriptContext *ctx)
{
  ScriptValue *val;
  val = ctx->MakeValue(ScriptTypeString,1);
  val->StringPtr = ((sPoolString *)cmd->Strings)+0;
  ctx->BindLocal(ctx->AddSymbol(L"filename"),val);
}
void Texture2DBind2Export(wCommand *cmd,ScriptContext *ctx)
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
void Texture2DBind3Export(wOp *op,sTextBuffer &tb)
{
  tb.PrintF(L"  import filename : string;\n");
}
const sChar *Texture2DWikiExport =
L"= Texture2D : Export\n"
L"\n"
L"!t 2 : 2 3\n"
L" !T 2\n"
L"  !i Name\n"
L"  !i Export\n"
L"\n"
L"  !i Output Type\n"
L"  !i Texture2D\n"
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
L" !i Filename\n"
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

sBool Texture2DCmdImport(wExecutive *exe,wCommand *cmd)
{
  Texture2DParaImport sUNUSED *para = (Texture2DParaImport *)(cmd->Data); para;
  Texture2D *out = (Texture2D *) cmd->Output;
  if(!out) { out=new Texture2D; cmd->Output=out; }

  {
#line 432 "basic_ops.ops"

    const sChar *name = cmd->Strings[0];
    return sLoadObject(name,out);
  ;
#line 2705 "basic_ops.cpp"
    return 1;
  }
}

void Texture2DGuiImport(wGridFrameHelper &gh,wOp *op)
{
  Texture2DParaImport sUNUSED *para = (Texture2DParaImport *)(op->EditData); para;
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
}

void Texture2DDefImport(wOp *op)
{
  Texture2DParaImport sUNUSED *para = (Texture2DParaImport *)(op->EditData); para;
  op->ArrayGroupMode = 0;
}

void Texture2DBindImport(wCommand *cmd,ScriptContext *ctx)
{
  ScriptValue *val;
  val = ctx->MakeValue(ScriptTypeString,1);
  val->StringPtr = ((sPoolString *)cmd->Strings)+0;
  ctx->BindLocal(ctx->AddSymbol(L"filename"),val);
}
void Texture2DBind2Import(wCommand *cmd,ScriptContext *ctx)
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
void Texture2DBind3Import(wOp *op,sTextBuffer &tb)
{
  tb.PrintF(L"  import filename : string;\n");
}
const sChar *Texture2DWikiImport =
L"= Texture2D : Import\n"
L"\n"
L"!t 2 : 2 3\n"
L" !T 2\n"
L"  !i Name\n"
L"  !i Import\n"
L"\n"
L"  !i Output Type\n"
L"  !i Texture2D\n"
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
L"== Comments\n"
L"\n"
L"*\n"
L"\n"
L"== See Also\n"
L"\n"
L"\n"
;

/****************************************************************************/

sBool TextureCubeCmdMakeCubeTex(wExecutive *exe,wCommand *cmd)
{
  TextureCubeParaMakeCubeTex sUNUSED *para = (TextureCubeParaMakeCubeTex *)(cmd->Data); para;
  CubemapBase sUNUSED *in0 = cmd->GetInput<CubemapBase *>(0); in0;
  TextureCube *out = (TextureCube *) cmd->Output;
  if(!out) { out=new TextureCube; cmd->Output=out; }

  {
#line 464 "basic_ops.ops"

    static sInt modes[] = 
    { 
      sTEX_ARGB8888,sTEX_A8,sTEX_I8,sTEX_DXT1,sTEX_DXT1A,sTEX_DXT3,sTEX_DXT5 
    };

    out->ConvertFrom(in0,modes[para->Format]);
    return 1;
  ;
#line 2810 "basic_ops.cpp"
    return 1;
  }
}

void TextureCubeGuiMakeCubeTex(wGridFrameHelper &gh,wOp *op)
{
  TextureCubeParaMakeCubeTex sUNUSED *para = (TextureCubeParaMakeCubeTex *)(op->EditData); para;
  gh.Group(op->Class->Label);

  gh.Label(L"Format");
  gh.Flags(&para->Format,L"argb8888|a8|i8|DXT1|DXT1A|DXT3|DXT5",gh.ChangeMsg);
}

void TextureCubeDefMakeCubeTex(wOp *op)
{
  TextureCubeParaMakeCubeTex sUNUSED *para = (TextureCubeParaMakeCubeTex *)(op->EditData); para;
  op->ArrayGroupMode = 0;
}

void TextureCubeBindMakeCubeTex(wCommand *cmd,ScriptContext *ctx)
{
}
void TextureCubeBind2MakeCubeTex(wCommand *cmd,ScriptContext *ctx)
{
  static sInt initdone = 0;
  static sPoolString name[1];
  if(!initdone)
  {
    initdone = 1; 
    name[0] = sPoolString(L"format");
  }
}
void TextureCubeBind3MakeCubeTex(wOp *op,sTextBuffer &tb)
{
}
const sChar *TextureCubeWikiMakeCubeTex =
L"= TextureCube : MakeCubeTex\n"
L"\n"
L"!t 2 : 2 3\n"
L" !T 2\n"
L"  !i Name\n"
L"  !i MakeCubeTex\n"
L"\n"
L"  !i Output Type\n"
L"  !i TextureCube\n"
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
L" !i CubemapBase\n"
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
L" !i Format\n"
L" !i Format\n"
L" !i argb8888\n"
L" !i *\n"
L" !i \n"
L" !i \n"
L" !i a8\n"
L" !i *\n"
L" !i \n"
L" !i \n"
L" !i i8\n"
L" !i *\n"
L" !i \n"
L" !i \n"
L" !i DXT1\n"
L" !i *\n"
L" !i \n"
L" !i \n"
L" !i DXT1A\n"
L" !i *\n"
L" !i \n"
L" !i \n"
L" !i DXT3\n"
L" !i *\n"
L" !i \n"
L" !i \n"
L" !i DXT5\n"
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

sBool SceneCmdAdd(wExecutive *exe,wCommand *cmd)
{
  SceneParaAdd sUNUSED *para = (SceneParaAdd *)(cmd->Data); para;
  Scene sUNUSED *in0 = cmd->GetInput<Scene *>(0); in0;
  Scene *out = (Scene *) cmd->Output;
  if(!out) { out=new Scene; cmd->Output=out; }

  {
#line 673 "basic_ops.ops"

    for(sInt i=0;i<cmd->InputCount;i++)
    {
      Scene *scene = cmd->GetInput<Scene *>(i);
      if(scene)
      {
        out->Childs.AddTail(scene);
        scene->AddRef();
      }
    } 
    return 1;
  ;
#line 2941 "basic_ops.cpp"
    return 1;
  }
}

void SceneGuiAdd(wGridFrameHelper &gh,wOp *op)
{
  SceneParaAdd sUNUSED *para = (SceneParaAdd *)(op->EditData); para;
}

void SceneDefAdd(wOp *op)
{
  SceneParaAdd sUNUSED *para = (SceneParaAdd *)(op->EditData); para;
  op->ArrayGroupMode = 0;
}

void SceneBindAdd(wCommand *cmd,ScriptContext *ctx)
{
}
void SceneBind2Add(wCommand *cmd,ScriptContext *ctx)
{
}
void SceneBind3Add(wOp *op,sTextBuffer &tb)
{
}
const sChar *SceneWikiAdd =
L"= Scene : Add\n"
L"\n"
L"!t 2 : 2 3\n"
L" !T 2\n"
L"  !i Name\n"
L"  !i Add\n"
L"\n"
L"  !i Output Type\n"
L"  !i Scene\n"
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
L" !i Scene\n"
L" !i multiple optional\n"
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

sBool SceneCmdConvertSceneNode(wExecutive *exe,wCommand *cmd)
{
  SceneParaConvertSceneNode sUNUSED *para = (SceneParaConvertSceneNode *)(cmd->Data); para;
  MeshBase sUNUSED *in0 = cmd->GetInput<MeshBase *>(0); in0;
  Scene *out = (Scene *) cmd->Output;
  if(!out) { out=new Scene; cmd->Output=out; }

  {
#line 691 "basic_ops.ops"

    if(!in0->IsType(MeshBaseType))
      return 0;

    out->Node = (MeshBase *)in0;
    in0->AddRef();
    return 1;
  ;
#line 3018 "basic_ops.cpp"
    return 1;
  }
}

void SceneGuiConvertSceneNode(wGridFrameHelper &gh,wOp *op)
{
  SceneParaConvertSceneNode sUNUSED *para = (SceneParaConvertSceneNode *)(op->EditData); para;
}

void SceneDefConvertSceneNode(wOp *op)
{
  SceneParaConvertSceneNode sUNUSED *para = (SceneParaConvertSceneNode *)(op->EditData); para;
  op->ArrayGroupMode = 0;
}

void SceneBindConvertSceneNode(wCommand *cmd,ScriptContext *ctx)
{
}
void SceneBind2ConvertSceneNode(wCommand *cmd,ScriptContext *ctx)
{
}
void SceneBind3ConvertSceneNode(wOp *op,sTextBuffer &tb)
{
}
const sChar *SceneWikiConvertSceneNode =
L"= Scene : ConvertSceneNode\n"
L"\n"
L"!t 2 : 2 3\n"
L" !T 2\n"
L"  !i Name\n"
L"  !i ConvertSceneNode\n"
L"\n"
L"  !i Output Type\n"
L"  !i Scene\n"
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
L" !i MeshBase\n"
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

sBool SceneCmdNode(wExecutive *exe,wCommand *cmd)
{
  SceneParaNode sUNUSED *para = (SceneParaNode *)(cmd->Data); para;
  MeshBase sUNUSED *in0 = cmd->GetInput<MeshBase *>(0); in0;
  Scene *out = (Scene *) cmd->Output;
  if(!out) { out=new Scene; cmd->Output=out; }

  {
#line 717 "basic_ops.ops"

    if(!in0->IsType(MeshBaseType))
    {
      cmd->SetError(L"Input needs to be a mesh of some kind.");
      return 0;
    }

    out->Node = (MeshBase *)in0;
    out->LightFlags = para->LFlags;
    in0->AddRef();
    out->NameId = para->NameId;
    if(para->Lods)
    {
      out->LodMapping = 0;
      if(!para->HighLod)
        out->LodMapping &= ~0x00ff0000;
      else
        out->LodMapping |= (para->HighLod<<16);
      if(!para->MediumLod)
        out->LodMapping &= ~0x0000ff00;
      else
        out->LodMapping |= (para->MediumLod<<8);
      if(!para->LowLod)
        out->LodMapping &= ~0x000000ff;
      else
        out->LodMapping |= para->LowLod;
    }
    return 1;
  ;
#line 3116 "basic_ops.cpp"
    return 1;
  }
}

void SceneGuiNode(wGridFrameHelper &gh,wOp *op)
{
  SceneParaNode sUNUSED *para = (SceneParaNode *)(op->EditData); para;
  gh.Group(op->Class->Label);

  gh.Label(L"static shadows");
  gh.Flags(&para->LFlags,L"-|cast:*30-|sky:*29-|cullbackfaces",gh.ChangeMsg);

  gh.Label(L"dynamic shadows");
  gh.Flags(&para->LFlags,L"*2-|cast:*3-|receive",gh.ChangeMsg);

  gh.Label(L"nameid (0=unchanged)");
  sIntControl *int_NameId = gh.Int(&para->NameId,0,65535,0.125000f,0,L"%06x");
  int_NameId->Default = 0x00000000; int_NameId->RightStep = 0.125000f;

  gh.Label(L"Lods");
  gh.Flags(&para->Lods,L"-|change",gh.LayoutMsg);

  if(para->Lods)
  {
    gh.Label(L"HighLod");
    gh.Flags(&para->HighLod,L"-|Low|Medium||High",gh.ChangeMsg);

    gh.Label(L"MediumLod");
    gh.Flags(&para->MediumLod,L"-|Low|Medium||High",gh.ChangeMsg);

    gh.Label(L"LowLod");
    gh.Flags(&para->LowLod,L"-|Low|Medium||High",gh.ChangeMsg);
  }
}

void SceneDefNode(wOp *op)
{
  SceneParaNode sUNUSED *para = (SceneParaNode *)(op->EditData); para;
  op->ArrayGroupMode = 0;
  para->LFlags = 0x00000001;
  para->HighLod = 0x00000004;
  para->MediumLod = 0x00000002;
  para->LowLod = 0x00000001;
}

void SceneBindNode(wCommand *cmd,ScriptContext *ctx)
{
  ScriptValue *val;
  val = ctx->MakeValue(ScriptTypeInt,1);
  val->IntPtr = ((sInt *)cmd->Data)+1;
  ctx->BindLocal(ctx->AddSymbol(L"nameid"),val);
}
void SceneBind2Node(wCommand *cmd,ScriptContext *ctx)
{
  static sInt initdone = 0;
  static sPoolString name[7];
  if(!initdone)
  {
    initdone = 1; 
    name[0] = sPoolString(L"lflags");
    name[1] = sPoolString(L"lflags");
    name[2] = sPoolString(L"nameid");
    name[3] = sPoolString(L"lods");
    name[4] = sPoolString(L"highlod");
    name[5] = sPoolString(L"mediumlod");
    name[6] = sPoolString(L"lowlod");
  }
  ctx->AddImport(name[2],ScriptTypeInt,1,cmd->Data+1);
}
void SceneBind3Node(wOp *op,sTextBuffer &tb)
{
  tb.PrintF(L"  import nameid : int;\n");
}
const sChar *SceneWikiNode =
L"= Scene : Node\n"
L"\n"
L"!t 2 : 2 3\n"
L" !T 2\n"
L"  !i Name\n"
L"  !i Node\n"
L"\n"
L"  !i Output Type\n"
L"  !i Scene\n"
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
L" !i MeshBase\n"
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
L" !i static shadows\n"
L" !i LFlags\n"
L" !i cast\n"
L" !i *\n"
L" !i\n"
L" !i\n"
L" !i\n"
L" !i\n"
L"\n"
L" !i \n"
L" !i \n"
L" !i sky\n"
L" !i *\n"
L" !i\n"
L" !i\n"
L" !i\n"
L" !i\n"
L"\n"
L" !i \n"
L" !i \n"
L" !i cullbackfaces\n"
L" !i *\n"
L"!T 4 : 1 1 1 2\n"
L" !i dynamic shadows\n"
L" !i LFlags\n"
L" !i cast\n"
L" !i *\n"
L" !i\n"
L" !i\n"
L" !i\n"
L" !i\n"
L"\n"
L" !i \n"
L" !i \n"
L" !i receive\n"
L" !i *\n"
L"!T 4 : 1 1 1 2\n"
L" !i nameid (0=unchanged)\n"
L" !i NameId\n"
L" !i int\n"
L" !i *\n"
L"\n"
L"!T 4 : 1 1 1 2\n"
L" !i Lods\n"
L" !i Lods\n"
L" !i change\n"
L" !i *\n"
L"!T 4 : 1 1 1 2\n"
L" !i HighLod\n"
L" !i HighLod\n"
L" !i Low\n"
L" !i *\n"
L" !i \n"
L" !i \n"
L" !i Medium\n"
L" !i *\n"
L" !i \n"
L" !i \n"
L" !i High\n"
L" !i *\n"
L"!T 4 : 1 1 1 2\n"
L" !i MediumLod\n"
L" !i MediumLod\n"
L" !i Low\n"
L" !i *\n"
L" !i \n"
L" !i \n"
L" !i Medium\n"
L" !i *\n"
L" !i \n"
L" !i \n"
L" !i High\n"
L" !i *\n"
L"!T 4 : 1 1 1 2\n"
L" !i LowLod\n"
L" !i LowLod\n"
L" !i Low\n"
L" !i *\n"
L" !i \n"
L" !i \n"
L" !i Medium\n"
L" !i *\n"
L" !i \n"
L" !i \n"
L" !i High\n"
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

sBool SceneCmdNameId(wExecutive *exe,wCommand *cmd)
{
  SceneParaNameId sUNUSED *para = (SceneParaNameId *)(cmd->Data); para;
  Scene sUNUSED *in0 = cmd->GetInput<Scene *>(0); in0;
  Scene *out = (Scene *) cmd->Output;
  if(!out) { out=new Scene; cmd->Output=out; }

  {
#line 755 "basic_ops.ops"

    for(sInt i=0;i<cmd->InputCount;i++)
    {
      Scene *scene = cmd->GetInput<Scene *>(i);
      if(scene)
      {
        out->Childs.AddTail(scene);
        scene->AddRef();
      }
    } 
    out->NameId = para->NameId;
    return 1;
  ;
#line 3344 "basic_ops.cpp"
    return 1;
  }
}

void SceneGuiNameId(wGridFrameHelper &gh,wOp *op)
{
  SceneParaNameId sUNUSED *para = (SceneParaNameId *)(op->EditData); para;
  gh.Group(op->Class->Label);

  gh.Label(L"nameid (0=unchanged)");
  sIntControl *int_NameId = gh.Int(&para->NameId,0,65535,0.125000f,0,L"%06x");
  int_NameId->Default = 0x00000000; int_NameId->RightStep = 0.125000f;
}

void SceneDefNameId(wOp *op)
{
  SceneParaNameId sUNUSED *para = (SceneParaNameId *)(op->EditData); para;
  op->ArrayGroupMode = 0;
}

void SceneBindNameId(wCommand *cmd,ScriptContext *ctx)
{
  ScriptValue *val;
  val = ctx->MakeValue(ScriptTypeInt,1);
  val->IntPtr = ((sInt *)cmd->Data)+0;
  ctx->BindLocal(ctx->AddSymbol(L"nameid"),val);
}
void SceneBind2NameId(wCommand *cmd,ScriptContext *ctx)
{
  static sInt initdone = 0;
  static sPoolString name[1];
  if(!initdone)
  {
    initdone = 1; 
    name[0] = sPoolString(L"nameid");
  }
  ctx->AddImport(name[0],ScriptTypeInt,1,cmd->Data+0);
}
void SceneBind3NameId(wOp *op,sTextBuffer &tb)
{
  tb.PrintF(L"  import nameid : int;\n");
}
const sChar *SceneWikiNameId =
L"= Scene : NameId\n"
L"\n"
L"!t 2 : 2 3\n"
L" !T 2\n"
L"  !i Name\n"
L"  !i NameId\n"
L"\n"
L"  !i Output Type\n"
L"  !i Scene\n"
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
L" !i Scene\n"
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
L" !i nameid (0=unchanged)\n"
L" !i NameId\n"
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

sBool SceneCmdSelectNameId(wExecutive *exe,wCommand *cmd)
{
  SceneParaSelectNameId sUNUSED *para = (SceneParaSelectNameId *)(cmd->Data); para;
  Scene sUNUSED *in0 = cmd->GetInput<Scene *>(0); in0;
  SceneSelectNameId *out = (SceneSelectNameId *) cmd->Output;
  if(!out) { out=new SceneSelectNameId; cmd->Output=out; }

  {
#line 813 "basic_ops.ops"

    out->Childs.AddTail(in0);
    in0->AddRef();
    out->DoFilter = 1;
    out->CompareId = para->NameId;
    out->Mode = para->Mode;
  ;
#line 3453 "basic_ops.cpp"
    return 1;
  }
}

void SceneGuiSelectNameId(wGridFrameHelper &gh,wOp *op)
{
  SceneParaSelectNameId sUNUSED *para = (SceneParaSelectNameId *)(op->EditData); para;
  gh.Group(op->Class->Label);

  gh.Label(L"nameid (0=unchanged)");
  sIntControl *int_NameId = gh.Int(&para->NameId,0,65535,0.125000f,0,L"%06x");
  int_NameId->Default = 0x00000000; int_NameId->RightStep = 0.125000f;

  gh.Label(L"Mode");
  gh.Flags(&para->Mode,L"equal|not equal",gh.ChangeMsg);
}

void SceneDefSelectNameId(wOp *op)
{
  SceneParaSelectNameId sUNUSED *para = (SceneParaSelectNameId *)(op->EditData); para;
  op->ArrayGroupMode = 0;
}

void SceneBindSelectNameId(wCommand *cmd,ScriptContext *ctx)
{
  ScriptValue *val;
  val = ctx->MakeValue(ScriptTypeInt,1);
  val->IntPtr = ((sInt *)cmd->Data)+0;
  ctx->BindLocal(ctx->AddSymbol(L"nameid"),val);
}
void SceneBind2SelectNameId(wCommand *cmd,ScriptContext *ctx)
{
  static sInt initdone = 0;
  static sPoolString name[2];
  if(!initdone)
  {
    initdone = 1; 
    name[0] = sPoolString(L"nameid");
    name[1] = sPoolString(L"mode");
  }
  ctx->AddImport(name[0],ScriptTypeInt,1,cmd->Data+0);
}
void SceneBind3SelectNameId(wOp *op,sTextBuffer &tb)
{
  tb.PrintF(L"  import nameid : int;\n");
}
const sChar *SceneWikiSelectNameId =
L"= Scene : SelectNameId\n"
L"\n"
L"!t 2 : 2 3\n"
L" !T 2\n"
L"  !i Name\n"
L"  !i SelectNameId\n"
L"\n"
L"  !i Output Type\n"
L"  !i Scene\n"
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
L" !i Scene\n"
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
L" !i nameid (0=unchanged)\n"
L" !i NameId\n"
L" !i int\n"
L" !i *\n"
L"\n"
L"!T 4 : 1 1 1 2\n"
L" !i Mode\n"
L" !i Mode\n"
L" !i equal\n"
L" !i *\n"
L" !i \n"
L" !i \n"
L" !i not equal\n"
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

sBool SceneCmdTransform(wExecutive *exe,wCommand *cmd)
{
  SceneParaTransform sUNUSED *para = (SceneParaTransform *)(cmd->Data); para;
  Scene sUNUSED *in0 = cmd->GetInput<Scene *>(0); in0;
  Scene *out = (Scene *) cmd->Output;
  if(!out) { out=new Scene; cmd->Output=out; }

  {
#line 836 "basic_ops.ops"

    sSRT srt;
    srt.Scale = para->Scale;
    srt.Rotate = para->Rotate;
    srt.Translate = para->Translate;

    srt.MakeMatrix(out->Transform);
    out->DoTransform = 1;

    for(sInt i=0;i<cmd->InputCount;i++)
    {
      Scene *scene = cmd->GetInput<Scene *>(i);
      if(scene)
      {
        out->Childs.AddTail(scene);
        scene->AddRef();
      }
    } 
    return 1;
  ;
#line 3588 "basic_ops.cpp"
    return 1;
  }
}

void SceneHndTransform(wPaintInfo &pi,wOp *op)
{
  SceneParaTransform sUNUSED *para = (SceneParaTransform *)(op->EditData); para;
#line 890 "basic_ops.ops"

    pi.Handle3D(op,1,para->Translate,wHM_PLANE);

    sSRT srt;
    sMatrix34 mat;
    srt.Scale = para->Scale;
    srt.Rotate = para->Rotate;
    srt.Translate = para->Translate;
    srt.MakeMatrix(mat);

    pi.Transform3D(mat);
  ;
#line 3609 "basic_ops.cpp"
}

sInt SceneActTransform(wOp *op,sInt code,sInt pos)
{
  SceneParaTransform sUNUSED *para = (SceneParaTransform *)(op->EditData); para;
#line 857 "basic_ops.ops"

    sSRT srt;
    sString<256> str;
    const sChar *clipStr;

    srt.Scale = para->Scale;
    srt.Rotate = para->Rotate;
    srt.Translate = para->Translate;

    switch(code)
    {
    case 1: // invert
      srt.Invert();
      break;

    case 2: // copy transform
      srt.ToString(str);
      sSetClipboard(str);
      break;

    case 3: // paste transform
      clipStr = sGetClipboard();
      srt.FromString(clipStr);
      delete[] clipStr;
      break;

    default:
      return 0;
    }

    para->Scale = srt.Scale;
    para->Rotate = srt.Rotate;
    para->Translate = srt.Translate;
    return 1;
  ;
#line 3651 "basic_ops.cpp"
}

void SceneGuiTransform(wGridFrameHelper &gh,wOp *op)
{
  SceneParaTransform sUNUSED *para = (SceneParaTransform *)(op->EditData); para;
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
  sFloatControl *float_Rotate_0 = gh.Float(&para->Rotate.x,-16.0000f,16.00000f,0.010000f);
  float_Rotate_0->Default = 0.000000f; float_Rotate_0->RightStep = 0.125000f;
  sFloatControl *float_Rotate_1 = gh.Float(&para->Rotate.y,-16.0000f,16.00000f,0.010000f);
  float_Rotate_1->Default = 0.000000f; float_Rotate_1->RightStep = 0.125000f;
  sFloatControl *float_Rotate_2 = gh.Float(&para->Rotate.z,-16.0000f,16.00000f,0.010000f);
  float_Rotate_2->Default = 0.000000f; float_Rotate_2->RightStep = 0.125000f;
  gh.EndTied();

  gh.Label(L"Translate");
  gh.BeginTied();
  sFloatControl *float_Translate_0 = gh.Float(&para->Translate.x,-65536.0f,65536.00f,0.010000f);
  float_Translate_0->Default = 0.000000f; float_Translate_0->RightStep = 0.125000f;
  sFloatControl *float_Translate_1 = gh.Float(&para->Translate.y,-65536.0f,65536.00f,0.010000f);
  float_Translate_1->Default = 0.000000f; float_Translate_1->RightStep = 0.125000f;
  sFloatControl *float_Translate_2 = gh.Float(&para->Translate.z,-65536.0f,65536.00f,0.010000f);
  float_Translate_2->Default = 0.000000f; float_Translate_2->RightStep = 0.125000f;
  gh.EndTied();

  gh.Label(L"Edit");

  gh.ActionMsg.Code = 1;
  gh.PushButton(L"Invert",gh.ActionMsg);

  gh.ActionMsg.Code = 2;
  gh.PushButton(L"Copy SRT",gh.ActionMsg);

  gh.ActionMsg.Code = 3;
  gh.PushButton(L"Paste SRT",gh.ActionMsg);
}

void SceneDefTransform(wOp *op)
{
  SceneParaTransform sUNUSED *para = (SceneParaTransform *)(op->EditData); para;
  op->ArrayGroupMode = 0;
  para->Scale.x = 1.000000f;
  para->Scale.y = 1.000000f;
  para->Scale.z = 1.000000f;
}

void SceneBindTransform(wCommand *cmd,ScriptContext *ctx)
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
  ctx->BindLocal(ctx->AddSymbol(L"translate"),val);
  val = ctx->MakeValue(ScriptTypeFloat,3);
  val->FloatPtr = ((sF32 *)cmd->Data)+6;
  ctx->BindLocal(ctx->AddSymbol(L"translate"),val);
  val = ctx->MakeValue(ScriptTypeFloat,3);
  val->FloatPtr = ((sF32 *)cmd->Data)+6;
  ctx->BindLocal(ctx->AddSymbol(L"translate"),val);
}
void SceneBind2Transform(wCommand *cmd,ScriptContext *ctx)
{
  static sInt initdone = 0;
  static sPoolString name[7];
  if(!initdone)
  {
    initdone = 1; 
    name[0] = sPoolString(L"scale");
    name[1] = sPoolString(L"rotate");
    name[2] = sPoolString(L"translate");
    name[3] = sPoolString(L"edit");
    name[4] = sPoolString(L"invert");
    name[5] = sPoolString(L"");
    name[6] = sPoolString(L"");
  }
  ctx->AddImport(name[0],ScriptTypeFloat,3,cmd->Data+0);
  ctx->AddImport(name[1],ScriptTypeFloat,3,cmd->Data+3);
  ctx->AddImport(name[2],ScriptTypeFloat,3,cmd->Data+6);
}
void SceneBind3Transform(wOp *op,sTextBuffer &tb)
{
  tb.PrintF(L"  import scale : float[3];\n");
  tb.PrintF(L"  import rotate : float[3];\n");
  tb.PrintF(L"  import translate : float[3];\n");
}
const sChar *SceneWikiTransform =
L"= Scene : Transform\n"
L"\n"
L"!t 2 : 2 3\n"
L" !T 2\n"
L"  !i Name\n"
L"  !i Transform\n"
L"\n"
L"  !i Output Type\n"
L"  !i Scene\n"
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
L" !i Scene\n"
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
L" !i Translate\n"
L" !i Translate\n"
L" !i float[3]\n"
L" !i *\n"
L"\n"
L" !i Invert\n"
L" !i \n"
L" !i action\n"
L" !i *\n"
L"\n"
L" !i Copy SRT\n"
L" !i \n"
L" !i action\n"
L" !i *\n"
L"\n"
L" !i Paste SRT\n"
L" !i \n"
L" !i action\n"
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

sBool SceneCmdMultiply(wExecutive *exe,wCommand *cmd)
{
  SceneParaMultiply sUNUSED *para = (SceneParaMultiply *)(cmd->Data); para;
  Scene sUNUSED *in0 = cmd->GetInput<Scene *>(0); in0;
  SceneMultiply *out = (SceneMultiply *) cmd->Output;
  if(!out) { out=new SceneMultiply; cmd->Output=out; }

  {
#line 945 "basic_ops.ops"

    sSRT srt;
    srt.Scale = para->Scale0;
    srt.Rotate = para->Rotate0;
    srt.Translate = para->Translate0;
    srt.MakeMatrix(out->GroupTrans);
    srt.Scale = para->Scale;
    srt.Rotate = para->Rotate;
    srt.Translate = para->Translate;
    srt.MakeMatrix(out->Transform);

    out->DoTransform = 1;
    out->Multiply = para->Count;

    for(sInt i=0;i<cmd->InputCount;i++)
    {
      Scene *scene = cmd->GetInput<Scene *>(i);
      if(scene)
      {
        out->Childs.AddTail(scene);
        scene->AddRef();
      }
    } 
    return 1;
  ;
#line 3875 "basic_ops.cpp"
    return 1;
  }
}

void SceneHndMultiply(wPaintInfo &pi,wOp *op)
{
  SceneParaMultiply sUNUSED *para = (SceneParaMultiply *)(op->EditData); para;
#line 972 "basic_ops.ops"

    sSRT srt;
    sMatrix34 mat;
    srt.Scale = para->Scale0;
    srt.Rotate = para->Rotate0;
    srt.Translate = para->Translate0;
    srt.MakeMatrix(mat);

    pi.Handle3D(op,1,para->Translate0,wHM_PLANE);
    pi.Transform3D(mat);
    pi.Handle3D(op,2,para->Translate,wHM_PLANE);
//    pi.Line3D(para->Translate,helper->Pos);
  ;
#line 3897 "basic_ops.cpp"
}

void SceneGuiMultiply(wGridFrameHelper &gh,wOp *op)
{
  SceneParaMultiply sUNUSED *para = (SceneParaMultiply *)(op->EditData); para;

  gh.Group(L"Group Transform");

  gh.Label(L"Scale0");
  gh.BeginTied();
  sFloatControl *float_Scale0_0 = gh.Float(&para->Scale0.x,-1024.00f,1024.000f,0.010000f);
  float_Scale0_0->Default = 1.000000f; float_Scale0_0->RightStep = 0.125000f;
  sFloatControl *float_Scale0_1 = gh.Float(&para->Scale0.y,-1024.00f,1024.000f,0.010000f);
  float_Scale0_1->Default = 1.000000f; float_Scale0_1->RightStep = 0.125000f;
  sFloatControl *float_Scale0_2 = gh.Float(&para->Scale0.z,-1024.00f,1024.000f,0.010000f);
  float_Scale0_2->Default = 1.000000f; float_Scale0_2->RightStep = 0.125000f;
  gh.EndTied();

  gh.Label(L"Rotate0");
  gh.BeginTied();
  sFloatControl *float_Rotate0_0 = gh.Float(&para->Rotate0.x,-16.0000f,16.00000f,0.010000f);
  float_Rotate0_0->Default = 0.000000f; float_Rotate0_0->RightStep = 0.125000f;
  sFloatControl *float_Rotate0_1 = gh.Float(&para->Rotate0.y,-16.0000f,16.00000f,0.010000f);
  float_Rotate0_1->Default = 0.000000f; float_Rotate0_1->RightStep = 0.125000f;
  sFloatControl *float_Rotate0_2 = gh.Float(&para->Rotate0.z,-16.0000f,16.00000f,0.010000f);
  float_Rotate0_2->Default = 0.000000f; float_Rotate0_2->RightStep = 0.125000f;
  gh.EndTied();

  gh.Label(L"Translate0");
  gh.BeginTied();
  sFloatControl *float_Translate0_0 = gh.Float(&para->Translate0.x,-65536.0f,65536.00f,0.010000f);
  float_Translate0_0->Default = 0.000000f; float_Translate0_0->RightStep = 0.125000f;
  sFloatControl *float_Translate0_1 = gh.Float(&para->Translate0.y,-65536.0f,65536.00f,0.010000f);
  float_Translate0_1->Default = 0.000000f; float_Translate0_1->RightStep = 0.125000f;
  sFloatControl *float_Translate0_2 = gh.Float(&para->Translate0.z,-65536.0f,65536.00f,0.010000f);
  float_Translate0_2->Default = 0.000000f; float_Translate0_2->RightStep = 0.125000f;
  gh.EndTied();

  gh.Group(L"Multiply Transform");

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
  sFloatControl *float_Rotate_0 = gh.Float(&para->Rotate.x,-16.0000f,16.00000f,0.001000f);
  float_Rotate_0->Default = 0.000000f; float_Rotate_0->RightStep = 0.125000f;
  sFloatControl *float_Rotate_1 = gh.Float(&para->Rotate.y,-16.0000f,16.00000f,0.001000f);
  float_Rotate_1->Default = 0.000000f; float_Rotate_1->RightStep = 0.125000f;
  sFloatControl *float_Rotate_2 = gh.Float(&para->Rotate.z,-16.0000f,16.00000f,0.001000f);
  float_Rotate_2->Default = 0.000000f; float_Rotate_2->RightStep = 0.125000f;
  gh.EndTied();

  gh.Label(L"Translate");
  gh.BeginTied();
  sFloatControl *float_Translate_0 = gh.Float(&para->Translate.x,-65536.0f,65536.00f,0.010000f);
  float_Translate_0->Default = 0.000000f; float_Translate_0->RightStep = 0.125000f;
  sFloatControl *float_Translate_1 = gh.Float(&para->Translate.y,-65536.0f,65536.00f,0.010000f);
  float_Translate_1->Default = 0.000000f; float_Translate_1->RightStep = 0.125000f;
  sFloatControl *float_Translate_2 = gh.Float(&para->Translate.z,-65536.0f,65536.00f,0.010000f);
  float_Translate_2->Default = 0.000000f; float_Translate_2->RightStep = 0.125000f;
  gh.EndTied();

  gh.Label(L"Count");
  sIntControl *int_Count = gh.Int(&para->Count,1,1024,0.125000f);
  int_Count->Default = 0x00000002; int_Count->RightStep = 0.125000f;
}

void SceneDefMultiply(wOp *op)
{
  SceneParaMultiply sUNUSED *para = (SceneParaMultiply *)(op->EditData); para;
  op->ArrayGroupMode = 0;
  para->Scale0.x = 1.000000f;
  para->Scale0.y = 1.000000f;
  para->Scale0.z = 1.000000f;
  para->Scale.x = 1.000000f;
  para->Scale.y = 1.000000f;
  para->Scale.z = 1.000000f;
  para->Count = 0x00000002;
}

void SceneBindMultiply(wCommand *cmd,ScriptContext *ctx)
{
  ScriptValue *val;
  val = ctx->MakeValue(ScriptTypeFloat,3);
  val->FloatPtr = ((sF32 *)cmd->Data)+10;
  ctx->BindLocal(ctx->AddSymbol(L"scale0"),val);
  val = ctx->MakeValue(ScriptTypeFloat,3);
  val->FloatPtr = ((sF32 *)cmd->Data)+10;
  ctx->BindLocal(ctx->AddSymbol(L"scale0"),val);
  val = ctx->MakeValue(ScriptTypeFloat,3);
  val->FloatPtr = ((sF32 *)cmd->Data)+10;
  ctx->BindLocal(ctx->AddSymbol(L"scale0"),val);
  val = ctx->MakeValue(ScriptTypeFloat,3);
  val->FloatPtr = ((sF32 *)cmd->Data)+13;
  ctx->BindLocal(ctx->AddSymbol(L"rotate0"),val);
  val = ctx->MakeValue(ScriptTypeFloat,3);
  val->FloatPtr = ((sF32 *)cmd->Data)+13;
  ctx->BindLocal(ctx->AddSymbol(L"rotate0"),val);
  val = ctx->MakeValue(ScriptTypeFloat,3);
  val->FloatPtr = ((sF32 *)cmd->Data)+13;
  ctx->BindLocal(ctx->AddSymbol(L"rotate0"),val);
  val = ctx->MakeValue(ScriptTypeFloat,3);
  val->FloatPtr = ((sF32 *)cmd->Data)+16;
  ctx->BindLocal(ctx->AddSymbol(L"translate0"),val);
  val = ctx->MakeValue(ScriptTypeFloat,3);
  val->FloatPtr = ((sF32 *)cmd->Data)+16;
  ctx->BindLocal(ctx->AddSymbol(L"translate0"),val);
  val = ctx->MakeValue(ScriptTypeFloat,3);
  val->FloatPtr = ((sF32 *)cmd->Data)+16;
  ctx->BindLocal(ctx->AddSymbol(L"translate0"),val);
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
  ctx->BindLocal(ctx->AddSymbol(L"translate"),val);
  val = ctx->MakeValue(ScriptTypeFloat,3);
  val->FloatPtr = ((sF32 *)cmd->Data)+6;
  ctx->BindLocal(ctx->AddSymbol(L"translate"),val);
  val = ctx->MakeValue(ScriptTypeFloat,3);
  val->FloatPtr = ((sF32 *)cmd->Data)+6;
  ctx->BindLocal(ctx->AddSymbol(L"translate"),val);
  val = ctx->MakeValue(ScriptTypeInt,1);
  val->IntPtr = ((sInt *)cmd->Data)+9;
  ctx->BindLocal(ctx->AddSymbol(L"count"),val);
}
void SceneBind2Multiply(wCommand *cmd,ScriptContext *ctx)
{
  static sInt initdone = 0;
  static sPoolString name[9];
  if(!initdone)
  {
    initdone = 1; 
    name[0] = sPoolString(L"");
    name[1] = sPoolString(L"scale0");
    name[2] = sPoolString(L"rotate0");
    name[3] = sPoolString(L"translate0");
    name[4] = sPoolString(L"");
    name[5] = sPoolString(L"scale");
    name[6] = sPoolString(L"rotate");
    name[7] = sPoolString(L"translate");
    name[8] = sPoolString(L"count");
  }
  ctx->AddImport(name[1],ScriptTypeFloat,3,cmd->Data+10);
  ctx->AddImport(name[2],ScriptTypeFloat,3,cmd->Data+13);
  ctx->AddImport(name[3],ScriptTypeFloat,3,cmd->Data+16);
  ctx->AddImport(name[5],ScriptTypeFloat,3,cmd->Data+0);
  ctx->AddImport(name[6],ScriptTypeFloat,3,cmd->Data+3);
  ctx->AddImport(name[7],ScriptTypeFloat,3,cmd->Data+6);
  ctx->AddImport(name[8],ScriptTypeInt,1,cmd->Data+9);
}
void SceneBind3Multiply(wOp *op,sTextBuffer &tb)
{
  tb.PrintF(L"  import scale0 : float[3];\n");
  tb.PrintF(L"  import rotate0 : float[3];\n");
  tb.PrintF(L"  import translate0 : float[3];\n");
  tb.PrintF(L"  import scale : float[3];\n");
  tb.PrintF(L"  import rotate : float[3];\n");
  tb.PrintF(L"  import translate : float[3];\n");
  tb.PrintF(L"  import count : int;\n");
}
const sChar *SceneWikiMultiply =
L"= Scene : Multiply\n"
L"\n"
L"!t 2 : 2 3\n"
L" !T 2\n"
L"  !i Name\n"
L"  !i Multiply\n"
L"\n"
L"  !i Output Type\n"
L"  !i Scene\n"
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
L" !i Scene\n"
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
L" !i Scale0\n"
L" !i Scale0\n"
L" !i float[3]\n"
L" !i *\n"
L"\n"
L" !i Rotate0\n"
L" !i Rotate0\n"
L" !i float[3]\n"
L" !i *\n"
L"\n"
L" !i Translate0\n"
L" !i Translate0\n"
L" !i float[3]\n"
L" !i *\n"
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
L" !i Translate\n"
L" !i Translate\n"
L" !i float[3]\n"
L" !i *\n"
L"\n"
L" !i Count\n"
L" !i Count\n"
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

sBool ScreenshotProxyCmdScreenshot(wExecutive *exe,wCommand *cmd)
{
  ScreenshotProxyParaScreenshot sUNUSED *para = (ScreenshotProxyParaScreenshot *)(cmd->Data); para;
  AnyType sUNUSED *in0 = cmd->GetInput<AnyType *>(0); in0;
  ScreenshotProxy *out = (ScreenshotProxy *) cmd->Output;
  if(!out) { out=new ScreenshotProxy; cmd->Output=out; }

  {
#line 1039 "basic_ops.ops"

    out->Root = in0;
    in0->AddRef();
    switch(para->Mode&15)
    {
    default:
      out->View.Camera.EulerXYZ(para->Rotate.x*sPI2F,para->Rotate.y*sPI2F,para->Rotate.z*sPI2F);
      out->View.Camera.l = para->Position;
      break;
    case 1:
      out->View.Camera.LookAt(para->Target,para->Position);
      out->View.Camera.l = para->Position;
      break;
    }
    out->Zoom = para->Zoom;
    out->SizeX = para->SizeX;
    out->SizeY = para->SizeY;
    out->Flags = para->Mode;
    out->Multisample = para->Multisample;
    if (para->TimeBase&1)
    {
      out->StartTime = sF32(Doc->BeatsToMilliseconds(sInt(65536*para->StartTime+0.5f)))/1000.0f;
      out->EndTime = sF32(Doc->BeatsToMilliseconds(sInt(65536*para->EndTime+0.5f)))/1000.0f;
    }
    else
    {
      out->StartTime = para->StartTime;
      out->EndTime = para->EndTime;
    }
    out->FPS = para->FPS;
    if(cmd->Op)
      out->Strobe = cmd->Op->Strobe;
    out->SaveName = cmd->Strings[0];
  ;
#line 4205 "basic_ops.cpp"
    return 1;
  }
}

sInt ScreenshotProxyActScreenshot(wOp *op,sInt code,sInt pos)
{
  ScreenshotProxyParaScreenshot sUNUSED *para = (ScreenshotProxyParaScreenshot *)(op->EditData); para;
#line 1075 "basic_ops.ops"

    if(code==1)
    {
      para->Zoom = Doc->LastView.ZoomY;

      sMatrix34 mat = Doc->LastView.Camera;
      para->Position = mat.l;
      switch(para->Mode&0x0f)
      {
      case 0:
        mat.FindEulerXYZ2(para->Rotate.x,para->Rotate.y,para->Rotate.z);
        para->Rotate *= 1.0f/sPI2F;
        break;
      case 1:
        para->Target = mat.l+mat.k*10;
        break;
      }
      Doc->Change(op);
      App->ChangeDoc();
      return 1;
    }
    else if (code==2)
    {
      return 1;
    }
    else
    {
      return 0;
    }
  ;
#line 4244 "basic_ops.cpp"
}

void ScreenshotProxyGuiScreenshot(wGridFrameHelper &gh,wOp *op)
{
  ScreenshotProxyParaScreenshot sUNUSED *para = (ScreenshotProxyParaScreenshot *)(op->EditData); para;
  gh.Group(op->Class->Label);

  gh.Label(L"MakeScreenshot");
  gh.Flags(&op->Strobe,L"-|Cheese",gh.ChangeMsg);

  gh.Group(L"Camera");

  gh.Label(L"Mode");
  gh.Flags(&para->Mode,L"rotate|target",gh.LayoutMsg);

  gh.ActionMsg.Code = 1;
  gh.PushButton(L"CopyCam",gh.ActionMsg);

  gh.Label(L"Rotate");
  gh.BeginTied();
  sFloatControl *float_Rotate_0 = gh.Float(&para->Rotate.x,-16.0000f,16.00000f,0.010000f);
  float_Rotate_0->Default = 0.000000f; float_Rotate_0->RightStep = 0.125000f;
  sFloatControl *float_Rotate_1 = gh.Float(&para->Rotate.y,-16.0000f,16.00000f,0.010000f);
  float_Rotate_1->Default = 0.000000f; float_Rotate_1->RightStep = 0.125000f;
  sFloatControl *float_Rotate_2 = gh.Float(&para->Rotate.z,-16.0000f,16.00000f,0.010000f);
  float_Rotate_2->Default = 0.000000f; float_Rotate_2->RightStep = 0.125000f;
  gh.EndTied();

  gh.Label(L"Position");
  gh.BeginTied();
  sFloatControl *float_Position_0 = gh.Float(&para->Position.x,-1024.00f,1024.000f,0.010000f);
  float_Position_0->Default = 0.000000f; float_Position_0->RightStep = 0.125000f;
  sFloatControl *float_Position_1 = gh.Float(&para->Position.y,-1024.00f,1024.000f,0.010000f);
  float_Position_1->Default = 0.000000f; float_Position_1->RightStep = 0.125000f;
  sFloatControl *float_Position_2 = gh.Float(&para->Position.z,-1024.00f,1024.000f,0.010000f);
  float_Position_2->Default = 0.000000f; float_Position_2->RightStep = 0.125000f;
  gh.EndTied();

  if(((para->Mode&0x000f)==0x0001))
  {
    gh.Label(L"Target");
    gh.BeginTied();
    sFloatControl *float_Target_0 = gh.Float(&para->Target.x,-1024.00f,1024.000f,0.010000f);
    float_Target_0->Default = 0.000000f; float_Target_0->RightStep = 0.125000f;
    sFloatControl *float_Target_1 = gh.Float(&para->Target.y,-1024.00f,1024.000f,0.010000f);
    float_Target_1->Default = 0.000000f; float_Target_1->RightStep = 0.125000f;
    sFloatControl *float_Target_2 = gh.Float(&para->Target.z,-1024.00f,1024.000f,0.010000f);
    float_Target_2->Default = 0.000000f; float_Target_2->RightStep = 0.125000f;
    gh.EndTied();

  }
  gh.Label(L"Zoom");
  sFloatControl *float_Zoom = gh.Float(&para->Zoom,0.000000f,256.0000f,0.010000f);
  float_Zoom->Default = 1.700000f; float_Zoom->RightStep = 0.125000f;

  gh.Group(L"Output");

  gh.Label(L"Size");
  gh.Flags(&para->Mode,L"*4window|keep aspect|as specified:*6-|AVI",gh.LayoutMsg);

  gh.Label(L"Resolution");

  sIntControl *int_SizeX = gh.Int(&para->SizeX,16,8192,16.00000f);
  int_SizeX->Default = 0x00000320; int_SizeX->RightStep = 0.125000f;

  sIntControl *int_SizeY = gh.Int(&para->SizeY,16,8192,16.00000f);
  int_SizeY->Default = 0x00000258; int_SizeY->RightStep = 0.125000f;

  gh.Flags(&para->Multisample,L"-|multisample",gh.ChangeMsg);

  gh.Label(L"SaveAs");
  {
    sControl *con = gh.String(op->EditString[0]);
    con->DoneMsg = con->ChangeMsg;
    con->ChangeMsg = sMessage();
    gh.FileSaveDialogMsg.Code = 0;
    gh.Box(L"...",gh.FileSaveDialogMsg);
  }

  if((para->Mode&0x0040))
  {
    gh.Group(L"Render AVI");

    gh.Label(L"Start time");
    sFloatControl *float_StartTime = gh.Float(&para->StartTime,0.000000f,60000.00f,1.000000f);
    float_StartTime->Default = 0.000000f; float_StartTime->RightStep = 0.125000f;

    gh.Flags(&para->TimeBase,L"seconds|beats",gh.LayoutMsg);

    gh.Label(L"End time");
    sFloatControl *float_EndTime = gh.Float(&para->EndTime,0.000000f,60000.00f,1.000000f);
    float_EndTime->Default = 60.00000f; float_EndTime->RightStep = 0.125000f;

    gh.Label(L"Frames/sec");
    sFloatControl *float_FPS = gh.Float(&para->FPS,0.010000f,1200.000f,1.000000f);
    float_FPS->Default = 30.00000f; float_FPS->RightStep = 0.125000f;
  }
}

void ScreenshotProxyDefScreenshot(wOp *op)
{
  ScreenshotProxyParaScreenshot sUNUSED *para = (ScreenshotProxyParaScreenshot *)(op->EditData); para;
  op->ArrayGroupMode = 0;
  para->Mode = 0x00000020;
  para->Zoom = 1.700000f;
  para->SizeX = 0x00000320;
  para->SizeY = 0x00000258;
  *op->EditString[0] = L"c:/temp/shot.bmp";
  para->EndTime = 60.00000f;
  para->FPS = 30.00000f;
}

void ScreenshotProxyBindScreenshot(wCommand *cmd,ScriptContext *ctx)
{
  ScriptValue *val;
  val = ctx->MakeValue(ScriptTypeFloat,3);
  val->FloatPtr = ((sF32 *)cmd->Data)+1;
  ctx->BindLocal(ctx->AddSymbol(L"rotate"),val);
  val = ctx->MakeValue(ScriptTypeFloat,3);
  val->FloatPtr = ((sF32 *)cmd->Data)+1;
  ctx->BindLocal(ctx->AddSymbol(L"rotate"),val);
  val = ctx->MakeValue(ScriptTypeFloat,3);
  val->FloatPtr = ((sF32 *)cmd->Data)+1;
  ctx->BindLocal(ctx->AddSymbol(L"rotate"),val);
  val = ctx->MakeValue(ScriptTypeFloat,3);
  val->FloatPtr = ((sF32 *)cmd->Data)+4;
  ctx->BindLocal(ctx->AddSymbol(L"position"),val);
  val = ctx->MakeValue(ScriptTypeFloat,3);
  val->FloatPtr = ((sF32 *)cmd->Data)+4;
  ctx->BindLocal(ctx->AddSymbol(L"position"),val);
  val = ctx->MakeValue(ScriptTypeFloat,3);
  val->FloatPtr = ((sF32 *)cmd->Data)+4;
  ctx->BindLocal(ctx->AddSymbol(L"position"),val);
  val = ctx->MakeValue(ScriptTypeFloat,3);
  val->FloatPtr = ((sF32 *)cmd->Data)+7;
  ctx->BindLocal(ctx->AddSymbol(L"target"),val);
  val = ctx->MakeValue(ScriptTypeFloat,3);
  val->FloatPtr = ((sF32 *)cmd->Data)+7;
  ctx->BindLocal(ctx->AddSymbol(L"target"),val);
  val = ctx->MakeValue(ScriptTypeFloat,3);
  val->FloatPtr = ((sF32 *)cmd->Data)+7;
  ctx->BindLocal(ctx->AddSymbol(L"target"),val);
  val = ctx->MakeValue(ScriptTypeFloat,1);
  val->FloatPtr = ((sF32 *)cmd->Data)+10;
  ctx->BindLocal(ctx->AddSymbol(L"zoom"),val);
  val = ctx->MakeValue(ScriptTypeInt,1);
  val->IntPtr = ((sInt *)cmd->Data)+11;
  ctx->BindLocal(ctx->AddSymbol(L"sizex"),val);
  val = ctx->MakeValue(ScriptTypeInt,1);
  val->IntPtr = ((sInt *)cmd->Data)+12;
  ctx->BindLocal(ctx->AddSymbol(L"sizey"),val);
  val = ctx->MakeValue(ScriptTypeString,1);
  val->StringPtr = ((sPoolString *)cmd->Strings)+0;
  ctx->BindLocal(ctx->AddSymbol(L"saveas"),val);
  val = ctx->MakeValue(ScriptTypeFloat,1);
  val->FloatPtr = ((sF32 *)cmd->Data)+14;
  ctx->BindLocal(ctx->AddSymbol(L"starttime"),val);
  val = ctx->MakeValue(ScriptTypeFloat,1);
  val->FloatPtr = ((sF32 *)cmd->Data)+16;
  ctx->BindLocal(ctx->AddSymbol(L"endtime"),val);
  val = ctx->MakeValue(ScriptTypeFloat,1);
  val->FloatPtr = ((sF32 *)cmd->Data)+17;
  ctx->BindLocal(ctx->AddSymbol(L"fps"),val);
}
void ScreenshotProxyBind2Screenshot(wCommand *cmd,ScriptContext *ctx)
{
  static sInt initdone = 0;
  static sPoolString name[20];
  if(!initdone)
  {
    initdone = 1; 
    name[0] = sPoolString(L"makescreenshot");
    name[1] = sPoolString(L"camera");
    name[2] = sPoolString(L"mode");
    name[3] = sPoolString(L"copycam");
    name[4] = sPoolString(L"rotate");
    name[5] = sPoolString(L"position");
    name[6] = sPoolString(L"target");
    name[7] = sPoolString(L"zoom");
    name[8] = sPoolString(L"output");
    name[9] = sPoolString(L"size");
    name[10] = sPoolString(L"resolution");
    name[11] = sPoolString(L"sizex");
    name[12] = sPoolString(L"sizey");
    name[13] = sPoolString(L"multisample");
    name[14] = sPoolString(L"saveas");
    name[15] = sPoolString(L"");
    name[16] = sPoolString(L"starttime");
    name[17] = sPoolString(L"timebase");
    name[18] = sPoolString(L"endtime");
    name[19] = sPoolString(L"fps");
  }
  ctx->AddImport(name[4],ScriptTypeFloat,3,cmd->Data+1);
  ctx->AddImport(name[5],ScriptTypeFloat,3,cmd->Data+4);
  ctx->AddImport(name[6],ScriptTypeFloat,3,cmd->Data+7);
  ctx->AddImport(name[7],ScriptTypeFloat,1,cmd->Data+10);
  ctx->AddImport(name[11],ScriptTypeInt,1,cmd->Data+11);
  ctx->AddImport(name[12],ScriptTypeInt,1,cmd->Data+12);
  ctx->AddImport(name[14],ScriptTypeString,1,cmd->Strings+0);
  ctx->AddImport(name[16],ScriptTypeFloat,1,cmd->Data+14);
  ctx->AddImport(name[18],ScriptTypeFloat,1,cmd->Data+16);
  ctx->AddImport(name[19],ScriptTypeFloat,1,cmd->Data+17);
}
void ScreenshotProxyBind3Screenshot(wOp *op,sTextBuffer &tb)
{
  tb.PrintF(L"  import rotate : float[3];\n");
  tb.PrintF(L"  import position : float[3];\n");
  tb.PrintF(L"  import target : float[3];\n");
  tb.PrintF(L"  import zoom : float;\n");
  tb.PrintF(L"  import sizex : int;\n");
  tb.PrintF(L"  import sizey : int;\n");
  tb.PrintF(L"  import saveas : string;\n");
  tb.PrintF(L"  import starttime : float;\n");
  tb.PrintF(L"  import endtime : float;\n");
  tb.PrintF(L"  import fps : float;\n");
}
const sChar *ScreenshotProxyWikiScreenshot =
L"= ScreenshotProxy : Screenshot\n"
L"\n"
L"!t 2 : 2 3\n"
L" !T 2\n"
L"  !i Name\n"
L"  !i Screenshot\n"
L"\n"
L"  !i Output Type\n"
L"  !i ScreenshotProxy\n"
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
L" !i AnyType\n"
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
L" !i MakeScreenshot\n"
L" !i MakeScreenshot\n"
L" !i strobe\n"
L" !i *\n"
L"\n"
L"!T 4 : 1 1 1 2\n"
L" !i Mode\n"
L" !i Mode\n"
L" !i rotate\n"
L" !i *\n"
L" !i \n"
L" !i \n"
L" !i target\n"
L" !i *\n"
L"!T 4 : 1 1 1 2\n"
L" !i CopyCam\n"
L" !i CopyCam\n"
L" !i action\n"
L" !i *\n"
L"\n"
L" !i Rotate\n"
L" !i Rotate\n"
L" !i float[3]\n"
L" !i *\n"
L"\n"
L" !i Position\n"
L" !i Position\n"
L" !i float[3]\n"
L" !i *\n"
L"\n"
L" !i Target\n"
L" !i Target\n"
L" !i float[3]\n"
L" !i *\n"
L"\n"
L" !i Zoom\n"
L" !i Zoom\n"
L" !i float\n"
L" !i *\n"
L"\n"
L"!T 4 : 1 1 1 2\n"
L" !i Size\n"
L" !i Mode\n"
L" !i window\n"
L" !i *\n"
L" !i \n"
L" !i \n"
L" !i keep aspect\n"
L" !i *\n"
L" !i \n"
L" !i \n"
L" !i as specified\n"
L" !i *\n"
L" !i\n"
L" !i\n"
L" !i\n"
L" !i\n"
L"\n"
L" !i \n"
L" !i \n"
L" !i AVI\n"
L" !i *\n"
L"!T 4 : 1 1 1 2\n"
L" !i SizeX\n"
L" !i SizeX\n"
L" !i int\n"
L" !i *\n"
L"\n"
L" !i SizeY\n"
L" !i SizeY\n"
L" !i int\n"
L" !i *\n"
L"\n"
L"!T 4 : 1 1 1 2\n"
L" !i <NULL>\n"
L" !i Multisample\n"
L" !i multisample\n"
L" !i *\n"
L"!T 4 : 1 1 1 2\n"
L" !i SaveAs\n"
L" !i SaveAs\n"
L" !i save file\n"
L" !i *\n"
L"\n"
L" !i Start time\n"
L" !i StartTime\n"
L" !i float\n"
L" !i *\n"
L"\n"
L"!T 4 : 1 1 1 2\n"
L" !i <NULL>\n"
L" !i TimeBase\n"
L" !i seconds\n"
L" !i *\n"
L" !i \n"
L" !i \n"
L" !i beats\n"
L" !i *\n"
L"!T 4 : 1 1 1 2\n"
L" !i End time\n"
L" !i EndTime\n"
L" !i float\n"
L" !i *\n"
L"\n"
L" !i Frames/sec\n"
L" !i FPS\n"
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

sBool UnitTestCmdUnitTestAdd(wExecutive *exe,wCommand *cmd)
{
  UnitTestParaUnitTestAdd sUNUSED *para = (UnitTestParaUnitTestAdd *)(cmd->Data); para;
  UnitTest sUNUSED *in0 = cmd->GetInput<UnitTest *>(0); in0;
  UnitTest *out = (UnitTest *) cmd->Output;
  if(!out) { out=new UnitTest; cmd->Output=out; }

  {
#line 1124 "basic_ops.ops"

    out->Errors = 0;
    out->Total = 0;
    out->Skipped = 0;
    for(sInt i=0;i<cmd->InputCount;i++)
    {
      UnitTest *ut = cmd->GetInput<UnitTest*>(i);
      out->Errors += ut->Errors;
      out->Total += ut->Total;
      out->Skipped += ut->Skipped;
    }
  ;
#line 4636 "basic_ops.cpp"
    return 1;
  }
}

void UnitTestGuiUnitTestAdd(wGridFrameHelper &gh,wOp *op)
{
  UnitTestParaUnitTestAdd sUNUSED *para = (UnitTestParaUnitTestAdd *)(op->EditData); para;
}

void UnitTestDefUnitTestAdd(wOp *op)
{
  UnitTestParaUnitTestAdd sUNUSED *para = (UnitTestParaUnitTestAdd *)(op->EditData); para;
  op->ArrayGroupMode = 0;
}

void UnitTestBindUnitTestAdd(wCommand *cmd,ScriptContext *ctx)
{
}
void UnitTestBind2UnitTestAdd(wCommand *cmd,ScriptContext *ctx)
{
}
void UnitTestBind3UnitTestAdd(wOp *op,sTextBuffer &tb)
{
}
const sChar *UnitTestWikiUnitTestAdd =
L"= UnitTest : UnitTestAdd\n"
L"\n"
L"!t 2 : 2 3\n"
L" !T 2\n"
L"  !i Name\n"
L"  !i UnitTestAdd\n"
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
L" !i UnitTest\n"
L" !i multiple optional\n"
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

sBool UnitTestCmdUnitTestScene(wExecutive *exe,wCommand *cmd)
{
  UnitTestParaUnitTestScene sUNUSED *para = (UnitTestParaUnitTestScene *)(cmd->Data); para;
  Scene sUNUSED *in0 = cmd->GetInput<Scene *>(0); in0;
  UnitTest *out = (UnitTest *) cmd->Output;
  if(!out) { out=new UnitTest; cmd->Output=out; }

  {
#line 1158 "basic_ops.ops"

    sInt xs = 1<<para->SizeX;
    sInt ys = 1<<para->SizeY;

    sInt tflags = sTEX_2D|sTEX_RENDERTARGET|sTEX_NOMIPMAPS;
    sTexture2D *rt = new sTexture2D(xs,ys,tflags|sTEX_ARGB8888);
    sTexture2D *db = new sTexture2D(xs,ys,tflags|sTEX_DEPTH24NOREAD);

    sRender3DBegin();

    wPaintInfo pi;
    sViewport view;



    pi.Spec.Init(rt,db);
    pi.Spec.Aspect = sF32(pi.Spec.Window.SizeX())/pi.Spec.Window.SizeY();

    view.Camera.EulerXYZ(para->Rotate.x*sPI2F,para->Rotate.y*sPI2F,para->Rotate.z*sPI2F);
    view.Camera.l = sVector31(view.Camera.k*-para->Distance);
    view.SetTarget(pi.Spec);
    view.SetZoom(para->Zoom);
    view.Prepare();
    pi.View = &view;
    sMaterialEnv env;
    pi.Env = &env;


    pi.BackColor = para->ClearColor;

    sSetTarget(sTargetPara(sST_CLEARALL,pi.BackColor,pi.Spec)); // clear the actual rendertarget


    Doc->Show(in0,pi);
    sResolveTarget();

    sImage img(xs,ys);
    const sU8 *data;
    sS32 pitch;
    sTextureFlags flags;
    sBeginReadTexture(data,pitch,flags,rt);
    sU32 *dest = img.Data;
    for(sInt y=0;y<ys;y++)
    {
      sCopyMem(dest,data,xs*sizeof(sU32));
      dest += xs;
      data += pitch;
    }
    sEndReadTexture();
    sRender3DEnd(0);

    delete rt;
    delete db;

    return out->Test(img,cmd->Strings[0],para->Flags);
  ;
#line 4761 "basic_ops.cpp"
    return 1;
  }
}

void UnitTestGuiUnitTestScene(wGridFrameHelper &gh,wOp *op)
{
  UnitTestParaUnitTestScene sUNUSED *para = (UnitTestParaUnitTestScene *)(op->EditData); para;
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

  gh.Group(L"Camera");

  gh.Label(L"Rotate");
  gh.BeginTied();
  sFloatControl *float_Rotate_0 = gh.Float(&para->Rotate.x,-16.0000f,16.00000f,0.010000f);
  float_Rotate_0->Default = 0.000000f; float_Rotate_0->RightStep = 0.125000f;
  sFloatControl *float_Rotate_1 = gh.Float(&para->Rotate.y,-16.0000f,16.00000f,0.010000f);
  float_Rotate_1->Default = 0.000000f; float_Rotate_1->RightStep = 0.125000f;
  sFloatControl *float_Rotate_2 = gh.Float(&para->Rotate.z,-16.0000f,16.00000f,0.010000f);
  float_Rotate_2->Default = 0.000000f; float_Rotate_2->RightStep = 0.125000f;
  gh.EndTied();

  gh.Label(L"Distance");
  sFloatControl *float_Distance = gh.Float(&para->Distance,-100.000f,1024.000f,0.010000f);
  float_Distance->Default = 5.000000f; float_Distance->RightStep = 0.125000f;

  gh.Label(L"Zoom");
  sFloatControl *float_Zoom = gh.Float(&para->Zoom,0.000000f,256.0000f,0.010000f);
  float_Zoom->Default = 1.700000f; float_Zoom->RightStep = 0.125000f;

  gh.Group(L"Output");

  gh.Label(L"Size");

  gh.Flags(&para->SizeX,L" 1| 2| 4| 8| 16| 32| 64| 128| 256| 512| 1024| 2048",gh.ChangeMsg);

  gh.Flags(&para->SizeY,L" 1| 2| 4| 8| 16| 32| 64| 128| 256| 512| 1024| 2048",gh.ChangeMsg);

  gh.Label(L"ClearColor");
  gh.ColorPick(&para->ClearColor,L"rgba",0);
}

void UnitTestDefUnitTestScene(wOp *op)
{
  UnitTestParaUnitTestScene sUNUSED *para = (UnitTestParaUnitTestScene *)(op->EditData); para;
  op->ArrayGroupMode = 0;
  para->Distance = 5.000000f;
  para->Zoom = 1.700000f;
  para->SizeX = 0x00000008;
  para->SizeY = 0x00000008;
}

void UnitTestBindUnitTestScene(wCommand *cmd,ScriptContext *ctx)
{
  ScriptValue *val;
  val = ctx->MakeValue(ScriptTypeString,1);
  val->StringPtr = ((sPoolString *)cmd->Strings)+0;
  ctx->BindLocal(ctx->AddSymbol(L"testname"),val);
  val = ctx->MakeValue(ScriptTypeFloat,3);
  val->FloatPtr = ((sF32 *)cmd->Data)+1;
  ctx->BindLocal(ctx->AddSymbol(L"rotate"),val);
  val = ctx->MakeValue(ScriptTypeFloat,3);
  val->FloatPtr = ((sF32 *)cmd->Data)+1;
  ctx->BindLocal(ctx->AddSymbol(L"rotate"),val);
  val = ctx->MakeValue(ScriptTypeFloat,3);
  val->FloatPtr = ((sF32 *)cmd->Data)+1;
  ctx->BindLocal(ctx->AddSymbol(L"rotate"),val);
  val = ctx->MakeValue(ScriptTypeFloat,1);
  val->FloatPtr = ((sF32 *)cmd->Data)+4;
  ctx->BindLocal(ctx->AddSymbol(L"distance"),val);
  val = ctx->MakeValue(ScriptTypeFloat,1);
  val->FloatPtr = ((sF32 *)cmd->Data)+5;
  ctx->BindLocal(ctx->AddSymbol(L"zoom"),val);
  val = ctx->MakeValue(ScriptTypeColor,1);
  val->ColorPtr = ((sU32 *)cmd->Data)+8;
  ctx->BindLocal(ctx->AddSymbol(L"clearcolor"),val);
}
void UnitTestBind2UnitTestScene(wCommand *cmd,ScriptContext *ctx)
{
  static sInt initdone = 0;
  static sPoolString name[11];
  if(!initdone)
  {
    initdone = 1; 
    name[0] = sPoolString(L"testname");
    name[1] = sPoolString(L"flags");
    name[2] = sPoolString(L"camera");
    name[3] = sPoolString(L"rotate");
    name[4] = sPoolString(L"distance");
    name[5] = sPoolString(L"zoom");
    name[6] = sPoolString(L"output");
    name[7] = sPoolString(L"size");
    name[8] = sPoolString(L"sizex");
    name[9] = sPoolString(L"sizey");
    name[10] = sPoolString(L"clearcolor");
  }
  ctx->AddImport(name[0],ScriptTypeString,1,cmd->Strings+0);
  ctx->AddImport(name[3],ScriptTypeFloat,3,cmd->Data+1);
  ctx->AddImport(name[4],ScriptTypeFloat,1,cmd->Data+4);
  ctx->AddImport(name[5],ScriptTypeFloat,1,cmd->Data+5);
  ctx->AddImport(name[10],ScriptTypeColor,1,cmd->Data+8);
}
void UnitTestBind3UnitTestScene(wOp *op,sTextBuffer &tb)
{
  tb.PrintF(L"  import testname : string;\n");
  tb.PrintF(L"  import rotate : float[3];\n");
  tb.PrintF(L"  import distance : float;\n");
  tb.PrintF(L"  import zoom : float;\n");
  tb.PrintF(L"  import clearcolor : color;\n");
}
const sChar *UnitTestWikiUnitTestScene =
L"= UnitTest : UnitTestScene\n"
L"\n"
L"!t 2 : 2 3\n"
L" !T 2\n"
L"  !i Name\n"
L"  !i UnitTestScene\n"
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
L" !i Scene\n"
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
L"!T 4 : 1 1 1 2\n"
L" !i Rotate\n"
L" !i Rotate\n"
L" !i float[3]\n"
L" !i *\n"
L"\n"
L" !i Distance\n"
L" !i Distance\n"
L" !i float\n"
L" !i *\n"
L"\n"
L" !i Zoom\n"
L" !i Zoom\n"
L" !i float\n"
L" !i *\n"
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
L" !i ClearColor\n"
L" !i ClearColor\n"
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

void TextObjectAnimText::Init(class ScriptContext *sc)
{
};

void TextObjectAnimText::Bind(class ScriptContext *sc,TextObjectParaText *para)
{
};

void TextObjectAnimTextEx::Init(class ScriptContext *sc)
{
};

void TextObjectAnimTextEx::Bind(class ScriptContext *sc,TextObjectParaTextEx *para)
{
};

void TextObjectAnimTextAdd::Init(class ScriptContext *sc)
{
};

void TextObjectAnimTextAdd::Bind(class ScriptContext *sc,TextObjectParaTextAdd *para)
{
};

void TextObjectAnimTextExport::Init(class ScriptContext *sc)
{
};

void TextObjectAnimTextExport::Bind(class ScriptContext *sc,TextObjectParaTextExport *para)
{
};

void AnyTypeAnimNop::Init(class ScriptContext *sc)
{
};

void AnyTypeAnimNop::Bind(class ScriptContext *sc,AnyTypeParaNop *para)
{
};

void AnyTypeAnimComment::Init(class ScriptContext *sc)
{
};

void AnyTypeAnimComment::Bind(class ScriptContext *sc,AnyTypeParaComment *para)
{
};

void AnyTypeAnimBlockHandles::Init(class ScriptContext *sc)
{
};

void AnyTypeAnimBlockHandles::Bind(class ScriptContext *sc,AnyTypeParaBlockHandles *para)
{
};

void AnyTypeAnimDummy::Init(class ScriptContext *sc)
{
};

void AnyTypeAnimDummy::Bind(class ScriptContext *sc,AnyTypeParaDummy *para)
{
};

void AnyTypeAnimDummyObj::Init(class ScriptContext *sc)
{
};

void AnyTypeAnimDummyObj::Bind(class ScriptContext *sc,AnyTypeParaDummyObj *para)
{
};

void AnyTypeAnimStore::Init(class ScriptContext *sc)
{
};

void AnyTypeAnimStore::Bind(class ScriptContext *sc,AnyTypeParaStore *para)
{
};

void AnyTypeAnimLoad::Init(class ScriptContext *sc)
{
};

void AnyTypeAnimLoad::Bind(class ScriptContext *sc,AnyTypeParaLoad *para)
{
};

void AnyTypeAnimGroup::Init(class ScriptContext *sc)
{
};

void AnyTypeAnimGroup::Bind(class ScriptContext *sc,AnyTypeParaGroup *para)
{
};

void GroupTypeAnimGroup3D::Init(class ScriptContext *sc)
{
};

void GroupTypeAnimGroup3D::Bind(class ScriptContext *sc,GroupTypeParaGroup3D *para)
{
};

void AnyTypeAnimSlow::Init(class ScriptContext *sc)
{
};

void AnyTypeAnimSlow::Bind(class ScriptContext *sc,AnyTypeParaSlow *para)
{
};

void AnyTypeAnimUnknownOp::Init(class ScriptContext *sc)
{
};

void AnyTypeAnimUnknownOp::Bind(class ScriptContext *sc,AnyTypeParaUnknownOp *para)
{
};

void AnyTypeAnimBlockChange::Init(class ScriptContext *sc)
{
};

void AnyTypeAnimBlockChange::Bind(class ScriptContext *sc,AnyTypeParaBlockChange *para)
{
};

void AnyTypeAnimCopy::Init(class ScriptContext *sc)
{
};

void AnyTypeAnimCopy::Bind(class ScriptContext *sc,AnyTypeParaCopy *para)
{
};

void AnyTypeAnimCall::Init(class ScriptContext *sc)
{
};

void AnyTypeAnimCall::Bind(class ScriptContext *sc,AnyTypeParaCall *para)
{
};

void AnyTypeAnimCallWithInputLinks::Init(class ScriptContext *sc)
{
};

void AnyTypeAnimCallWithInputLinks::Bind(class ScriptContext *sc,AnyTypeParaCallWithInputLinks *para)
{
};

void AnyTypeAnimInput::Init(class ScriptContext *sc)
{
};

void AnyTypeAnimInput::Bind(class ScriptContext *sc,AnyTypeParaInput *para)
{
};

void AnyTypeAnimInjectGlobals::Init(class ScriptContext *sc)
{
};

void AnyTypeAnimInjectGlobals::Bind(class ScriptContext *sc,AnyTypeParaInjectGlobals *para)
{
};

void AnyTypeAnimLoop::Init(class ScriptContext *sc)
{
};

void AnyTypeAnimLoop::Bind(class ScriptContext *sc,AnyTypeParaLoop *para)
{
};

void AnyTypeAnimEndLoop::Init(class ScriptContext *sc)
{
};

void AnyTypeAnimEndLoop::Bind(class ScriptContext *sc,AnyTypeParaEndLoop *para)
{
};

void AnyTypeAnimShellSwitch::Init(class ScriptContext *sc)
{
};

void AnyTypeAnimShellSwitch::Bind(class ScriptContext *sc,AnyTypeParaShellSwitch *para)
{
};

void Texture2DAnimMakeTexture::Init(class ScriptContext *sc)
{
};

void Texture2DAnimMakeTexture::Bind(class ScriptContext *sc,Texture2DParaMakeTexture *para)
{
};

void Texture2DAnimExport::Init(class ScriptContext *sc)
{
};

void Texture2DAnimExport::Bind(class ScriptContext *sc,Texture2DParaExport *para)
{
};

void Texture2DAnimImport::Init(class ScriptContext *sc)
{
};

void Texture2DAnimImport::Bind(class ScriptContext *sc,Texture2DParaImport *para)
{
};

void TextureCubeAnimMakeCubeTex::Init(class ScriptContext *sc)
{
};

void TextureCubeAnimMakeCubeTex::Bind(class ScriptContext *sc,TextureCubeParaMakeCubeTex *para)
{
};

void SceneAnimAdd::Init(class ScriptContext *sc)
{
};

void SceneAnimAdd::Bind(class ScriptContext *sc,SceneParaAdd *para)
{
};

void SceneAnimConvertSceneNode::Init(class ScriptContext *sc)
{
};

void SceneAnimConvertSceneNode::Bind(class ScriptContext *sc,SceneParaConvertSceneNode *para)
{
};

void SceneAnimNode::Init(class ScriptContext *sc)
{
};

void SceneAnimNode::Bind(class ScriptContext *sc,SceneParaNode *para)
{
};

void SceneAnimNameId::Init(class ScriptContext *sc)
{
};

void SceneAnimNameId::Bind(class ScriptContext *sc,SceneParaNameId *para)
{
};

void SceneAnimSelectNameId::Init(class ScriptContext *sc)
{
};

void SceneAnimSelectNameId::Bind(class ScriptContext *sc,SceneParaSelectNameId *para)
{
};

void SceneAnimTransform::Init(class ScriptContext *sc)
{
};

void SceneAnimTransform::Bind(class ScriptContext *sc,SceneParaTransform *para)
{
};

void SceneAnimMultiply::Init(class ScriptContext *sc)
{
};

void SceneAnimMultiply::Bind(class ScriptContext *sc,SceneParaMultiply *para)
{
};

void ScreenshotProxyAnimScreenshot::Init(class ScriptContext *sc)
{
};

void ScreenshotProxyAnimScreenshot::Bind(class ScriptContext *sc,ScreenshotProxyParaScreenshot *para)
{
};

void UnitTestAnimUnitTestAdd::Init(class ScriptContext *sc)
{
};

void UnitTestAnimUnitTestAdd::Bind(class ScriptContext *sc,UnitTestParaUnitTestAdd *para)
{
};

void UnitTestAnimUnitTestScene::Init(class ScriptContext *sc)
{
};

void UnitTestAnimUnitTestScene::Bind(class ScriptContext *sc,UnitTestParaUnitTestScene *para)
{
};


/****************************************************************************/

void AddTypes_basic_ops(sBool secondary)
{
  sVERIFY(Doc);

  Doc->Types.AddTail(AnyTypeType = new AnyTypeType_);
  AnyTypeType->Secondary = secondary;

  Doc->Types.AddTail(GroupTypeType = new GroupTypeType_);
  GroupTypeType->Secondary = secondary;

  Doc->Types.AddTail(TextObjectType = new TextObjectType_);
  TextObjectType->Secondary = secondary;

  Doc->Types.AddTail(BitmapBaseType = new BitmapBaseType_);
  BitmapBaseType->Secondary = secondary;

  Doc->Types.AddTail(Texture2DType = new Texture2DType_);
  Texture2DType->Secondary = secondary;

  Doc->Types.AddTail(CubemapBaseType = new CubemapBaseType_);
  CubemapBaseType->Secondary = secondary;

  Doc->Types.AddTail(TextureCubeType = new TextureCubeType_);
  TextureCubeType->Secondary = secondary;

  Doc->Types.AddTail(MeshBaseType = new MeshBaseType_);
  MeshBaseType->Secondary = secondary;

  Doc->Types.AddTail(SceneType = new SceneType_);
  SceneType->Secondary = secondary;

  Doc->Types.AddTail(ScreenshotProxyType = new ScreenshotProxyType_);
  ScreenshotProxyType->Secondary = secondary;

  Doc->Types.AddTail(UnitTestType = new UnitTestType_);
  UnitTestType->Secondary = secondary;

}

/****************************************************************************/

void AddOps_basic_ops(sBool secondary)
{
  sVERIFY(Doc);

  wClass sUNUSED *cl=0; cl;
  wClassInputInfo sUNUSED *in=0; in;



  cl= new wClass;
  cl->Name = L"Text";
  cl->Label = L"Text";
  cl->OutputType = TextObjectType;
  cl->TabType = TextObjectType;
  cl->Command = TextObjectCmdText;
  cl->MakeGui = TextObjectGuiText;
  cl->SetDefaults = TextObjectDefText;
  cl->BindPara = TextObjectBindText;
  cl->Bind2Para = TextObjectBind2Text;
  cl->Bind3Para = TextObjectBind3Text;
  cl->WikiText = TextObjectWikiText;
  cl->ParaStrings = 1;
  cl->Flags = 0x0000;
  Doc->Classes.AddTail(cl);

  cl= new wClass;
  cl->Name = L"TextEx";
  cl->Label = L"TextEx";
  cl->OutputType = TextObjectType;
  cl->TabType = TextObjectType;
  cl->Command = TextObjectCmdTextEx;
  cl->MakeGui = TextObjectGuiTextEx;
  cl->SetDefaults = TextObjectDefTextEx;
  cl->BindPara = TextObjectBindTextEx;
  cl->Bind2Para = TextObjectBind2TextEx;
  cl->Bind3Para = TextObjectBind3TextEx;
  cl->WikiText = TextObjectWikiTextEx;
  cl->ParaStrings = 1;
  cl->Flags = 0x0000;
  Doc->Classes.AddTail(cl);

  cl= new wClass;
  cl->Name = L"TextAdd";
  cl->Label = L"TextAdd";
  cl->OutputType = TextObjectType;
  cl->TabType = TextObjectType;
  cl->Command = TextObjectCmdTextAdd;
  cl->MakeGui = TextObjectGuiTextAdd;
  cl->SetDefaults = TextObjectDefTextAdd;
  cl->BindPara = TextObjectBindTextAdd;
  cl->Bind2Para = TextObjectBind2TextAdd;
  cl->Bind3Para = TextObjectBind3TextAdd;
  cl->WikiText = TextObjectWikiTextAdd;
  cl->Column = 2;
  cl->Flags = 0x0001;
  in = cl->Inputs.AddMany(1);
  in[0].Type = TextObjectType;
  in[0].DefaultClass = 0;
  in[0].Flags = 0|wCIF_OPTIONAL;
  Doc->Classes.AddTail(cl);

  cl= new wClass;
  cl->Name = L"TextExport";
  cl->Label = L"TextExport";
  cl->OutputType = TextObjectType;
  cl->TabType = TextObjectType;
  cl->Command = TextObjectCmdTextExport;
  cl->MakeGui = TextObjectGuiTextExport;
  cl->SetDefaults = TextObjectDefTextExport;
  cl->BindPara = TextObjectBindTextExport;
  cl->Bind2Para = TextObjectBind2TextExport;
  cl->Bind3Para = TextObjectBind3TextExport;
  cl->WikiText = TextObjectWikiTextExport;
  cl->ParaStrings = 1;
  cl->FileOutMask = 1;
  cl->Column = 1;
  cl->Flags = 0x0000;
  in = cl->Inputs.AddMany(1);
  in[0].Type = TextObjectType;
  in[0].DefaultClass = 0;
  in[0].Flags = 0;
  Doc->Classes.AddTail(cl);

  cl= new wClass;
  cl->Name = L"Nop";
  cl->Label = L"Nop";
  cl->OutputType = AnyTypeType;
  cl->TabType = AnyTypeType;
  cl->MakeGui = AnyTypeGuiNop;
  cl->SetDefaults = AnyTypeDefNop;
  cl->BindPara = AnyTypeBindNop;
  cl->Bind2Para = AnyTypeBind2Nop;
  cl->Bind3Para = AnyTypeBind3Nop;
  cl->WikiText = AnyTypeWikiNop;
  cl->Shortcut = '-';
  cl->Column = 30;
  cl->Flags = 0x810000;
  in = cl->Inputs.AddMany(1);
  in[0].Type = AnyTypeType;
  in[0].DefaultClass = 0;
  in[0].Flags = 0;
  Doc->Classes.AddTail(cl);

  cl= new wClass;
  cl->Name = L"Comment";
  cl->Label = L"Comment";
  cl->OutputType = AnyTypeType;
  cl->TabType = AnyTypeType;
  cl->Command = AnyTypeCmdComment;
  cl->MakeGui = AnyTypeGuiComment;
  cl->SetDefaults = AnyTypeDefComment;
  cl->BindPara = AnyTypeBindComment;
  cl->Bind2Para = AnyTypeBind2Comment;
  cl->Bind3Para = AnyTypeBind3Comment;
  cl->WikiText = AnyTypeWikiComment;
  cl->ParaStrings = 1;
  cl->ParaWords = 1;
  cl->Shortcut = '.';
  cl->Column = 30;
  cl->Flags = 0x30000;
  Doc->Classes.AddTail(cl);

  cl= new wClass;
  cl->Name = L"BlockHandles";
  cl->Label = L"BlockHandles";
  cl->OutputType = AnyTypeType;
  cl->TabType = AnyTypeType;
  cl->MakeGui = AnyTypeGuiBlockHandles;
  cl->SetDefaults = AnyTypeDefBlockHandles;
  cl->BindPara = AnyTypeBindBlockHandles;
  cl->Bind2Para = AnyTypeBind2BlockHandles;
  cl->Bind3Para = AnyTypeBind3BlockHandles;
  cl->WikiText = AnyTypeWikiBlockHandles;
  cl->Column = 30;
  cl->Flags = 0x800400;
  in = cl->Inputs.AddMany(1);
  in[0].Type = AnyTypeType;
  in[0].DefaultClass = 0;
  in[0].Flags = 0;
  Doc->Classes.AddTail(cl);

  cl= new wClass;
  cl->Name = L"Dummy";
  cl->Label = L"Dummy";
  cl->OutputType = AnyTypeType;
  cl->TabType = AnyTypeType;
  cl->Command = AnyTypeCmdDummy;
  cl->MakeGui = AnyTypeGuiDummy;
  cl->SetDefaults = AnyTypeDefDummy;
  cl->BindPara = AnyTypeBindDummy;
  cl->Bind2Para = AnyTypeBind2Dummy;
  cl->Bind3Para = AnyTypeBind3Dummy;
  cl->WikiText = AnyTypeWikiDummy;
  cl->Column = 30;
  cl->Flags = 0x0040;
  in = cl->Inputs.AddMany(1);
  in[0].Type = AnyTypeType;
  in[0].DefaultClass = 0;
  in[0].Flags = 0;
  Doc->Classes.AddTail(cl);

  cl= new wClass;
  cl->Name = L"DummyObj";
  cl->Label = L"Dummy";
  cl->OutputType = AnyTypeType;
  cl->TabType = AnyTypeType;
  cl->Command = AnyTypeCmdDummyObj;
  cl->MakeGui = AnyTypeGuiDummyObj;
  cl->SetDefaults = AnyTypeDefDummyObj;
  cl->BindPara = AnyTypeBindDummyObj;
  cl->Bind2Para = AnyTypeBind2DummyObj;
  cl->Bind3Para = AnyTypeBind3DummyObj;
  cl->WikiText = AnyTypeWikiDummyObj;
  cl->Column = 30;
  cl->Flags = 0x0000;
  Doc->Classes.AddTail(cl);

  cl= new wClass;
  cl->Name = L"Store";
  cl->Label = L"Store";
  cl->OutputType = AnyTypeType;
  cl->TabType = AnyTypeType;
  cl->MakeGui = AnyTypeGuiStore;
  cl->SetDefaults = AnyTypeDefStore;
  cl->BindPara = AnyTypeBindStore;
  cl->Bind2Para = AnyTypeBind2Store;
  cl->Bind3Para = AnyTypeBind3Store;
  cl->WikiText = AnyTypeWikiStore;
  cl->Shortcut = 's';
  cl->Column = 30;
  cl->Flags = 0x800008;
  in = cl->Inputs.AddMany(1);
  in[0].Type = AnyTypeType;
  in[0].DefaultClass = 0;
  in[0].Flags = 0;
  Doc->Classes.AddTail(cl);

  cl= new wClass;
  cl->Name = L"Load";
  cl->Label = L"Load";
  cl->OutputType = AnyTypeType;
  cl->TabType = AnyTypeType;
  cl->MakeGui = AnyTypeGuiLoad;
  cl->SetDefaults = AnyTypeDefLoad;
  cl->BindPara = AnyTypeBindLoad;
  cl->Bind2Para = AnyTypeBind2Load;
  cl->Bind3Para = AnyTypeBind3Load;
  cl->WikiText = AnyTypeWikiLoad;
  cl->Shortcut = 'l';
  cl->Column = 30;
  cl->Flags = 0x800004;
  in = cl->Inputs.AddMany(1);
  in[0].Type = AnyTypeType;
  in[0].DefaultClass = 0;
  in[0].Name = L"Link";
  in[0].Flags = 0|wCIF_METHODLINK;
  Doc->Classes.AddTail(cl);

  cl= new wClass;
  cl->Name = L"Group";
  cl->Label = L"Group";
  cl->OutputType = AnyTypeType;
  cl->TabType = AnyTypeType;
  cl->Command = AnyTypeCmdGroup;
  cl->MakeGui = AnyTypeGuiGroup;
  cl->SetDefaults = AnyTypeDefGroup;
  cl->BindPara = AnyTypeBindGroup;
  cl->Bind2Para = AnyTypeBind2Group;
  cl->Bind3Para = AnyTypeBind3Group;
  cl->WikiText = AnyTypeWikiGroup;
  cl->Column = 30;
  cl->Flags = 0x0001;
  in = cl->Inputs.AddMany(1);
  in[0].Type = AnyTypeType;
  in[0].DefaultClass = 0;
  in[0].Flags = 0|wCIF_OPTIONAL;
  Doc->Classes.AddTail(cl);

  cl= new wClass;
  cl->Name = L"Group3D";
  cl->Label = L"Group3D";
  cl->OutputType = GroupTypeType;
  cl->TabType = GroupTypeType;
  cl->Command = GroupTypeCmdGroup3D;
  cl->MakeGui = GroupTypeGuiGroup3D;
  cl->SetDefaults = GroupTypeDefGroup3D;
  cl->BindPara = GroupTypeBindGroup3D;
  cl->Bind2Para = GroupTypeBind2Group3D;
  cl->Bind3Para = GroupTypeBind3Group3D;
  cl->WikiText = GroupTypeWikiGroup3D;
  cl->Column = 30;
  cl->Flags = 0x0001;
  in = cl->Inputs.AddMany(1);
  in[0].Type = AnyTypeType;
  in[0].DefaultClass = 0;
  in[0].Flags = 0|wCIF_OPTIONAL;
  Doc->Classes.AddTail(cl);

  cl= new wClass;
  cl->Name = L"Slow";
  cl->Label = L"Slow";
  cl->OutputType = AnyTypeType;
  cl->TabType = AnyTypeType;
  cl->Command = AnyTypeCmdSlow;
  cl->MakeGui = AnyTypeGuiSlow;
  cl->SetDefaults = AnyTypeDefSlow;
  cl->BindPara = AnyTypeBindSlow;
  cl->Bind2Para = AnyTypeBind2Slow;
  cl->Bind3Para = AnyTypeBind3Slow;
  cl->WikiText = AnyTypeWikiSlow;
  cl->Column = 30;
  cl->Flags = 0x800200;
  in = cl->Inputs.AddMany(1);
  in[0].Type = AnyTypeType;
  in[0].DefaultClass = 0;
  in[0].Flags = 0;
  Doc->Classes.AddTail(cl);

  cl= new wClass;
  cl->Name = L"UnknownOp";
  cl->Label = L"UnknownOp";
  cl->OutputType = AnyTypeType;
  cl->TabType = AnyTypeType;
  cl->Command = AnyTypeCmdUnknownOp;
  cl->MakeGui = AnyTypeGuiUnknownOp;
  cl->SetDefaults = AnyTypeDefUnknownOp;
  cl->BindPara = AnyTypeBindUnknownOp;
  cl->Bind2Para = AnyTypeBind2UnknownOp;
  cl->Bind3Para = AnyTypeBind3UnknownOp;
  cl->WikiText = AnyTypeWikiUnknownOp;
  cl->Column = 30;
  cl->Flags = 0x0040;
  Doc->Classes.AddTail(cl);

  cl= new wClass;
  cl->Name = L"BlockChange";
  cl->Label = L"BlockChange";
  cl->OutputType = AnyTypeType;
  cl->TabType = AnyTypeType;
  cl->Command = AnyTypeCmdBlockChange;
  cl->MakeGui = AnyTypeGuiBlockChange;
  cl->SetDefaults = AnyTypeDefBlockChange;
  cl->BindPara = AnyTypeBindBlockChange;
  cl->Bind2Para = AnyTypeBind2BlockChange;
  cl->Bind3Para = AnyTypeBind3BlockChange;
  cl->WikiText = AnyTypeWikiBlockChange;
  cl->Column = 30;
  cl->Flags = 0x1800000;
  in = cl->Inputs.AddMany(1);
  in[0].Type = AnyTypeType;
  in[0].DefaultClass = 0;
  in[0].Flags = 0;
  Doc->Classes.AddTail(cl);

  cl= new wClass;
  cl->Name = L"Copy";
  cl->Label = L"Copy";
  cl->OutputType = AnyTypeType;
  cl->TabType = AnyTypeType;
  cl->Command = AnyTypeCmdCopy;
  cl->MakeGui = AnyTypeGuiCopy;
  cl->SetDefaults = AnyTypeDefCopy;
  cl->BindPara = AnyTypeBindCopy;
  cl->Bind2Para = AnyTypeBind2Copy;
  cl->Bind3Para = AnyTypeBind3Copy;
  cl->WikiText = AnyTypeWikiCopy;
  cl->Column = 30;
  cl->Flags = 0x800000;
  in = cl->Inputs.AddMany(1);
  in[0].Type = AnyTypeType;
  in[0].DefaultClass = 0;
  in[0].Flags = 0;
  Doc->Classes.AddTail(cl);

  cl= new wClass;
  cl->Name = L"Call";
  cl->Label = L"Call";
  cl->OutputType = AnyTypeType;
  cl->TabType = AnyTypeType;
  cl->MakeGui = AnyTypeGuiCall;
  cl->SetDefaults = AnyTypeDefCall;
  cl->BindPara = AnyTypeBindCall;
  cl->Bind2Para = AnyTypeBind2Call;
  cl->Bind3Para = AnyTypeBind3Call;
  cl->WikiText = AnyTypeWikiCall;
  cl->ParaWords = 1;
  cl->Column = 30;
  cl->Flags = 0x840001;
  in = cl->Inputs.AddMany(2);
  in[0].Type = AnyTypeType;
  in[0].DefaultClass = 0;
  in[0].Name = L"Link";
  in[0].Flags = 0|wCIF_METHODLINK;
  in[1].Type = AnyTypeType;
  in[1].DefaultClass = 0;
  in[1].Flags = 0|wCIF_OPTIONAL;
  Doc->Classes.AddTail(cl);

  cl= new wClass;
  cl->Name = L"CallWithInputLinks";
  cl->Label = L"CallWithInputLinks";
  cl->OutputType = AnyTypeType;
  cl->TabType = AnyTypeType;
  cl->MakeGui = AnyTypeGuiCallWithInputLinks;
  cl->SetDefaults = AnyTypeDefCallWithInputLinks;
  cl->BindPara = AnyTypeBindCallWithInputLinks;
  cl->Bind2Para = AnyTypeBind2CallWithInputLinks;
  cl->Bind3Para = AnyTypeBind3CallWithInputLinks;
  cl->WikiText = AnyTypeWikiCallWithInputLinks;
  cl->ParaWords = 1;
  cl->Column = 30;
  cl->Flags = 0x840000;
  in = cl->Inputs.AddMany(5);
  in[0].Type = AnyTypeType;
  in[0].DefaultClass = 0;
  in[0].Name = L"Link";
  in[0].Flags = 0|wCIF_METHODLINK;
  in[1].Type = AnyTypeType;
  in[1].DefaultClass = 0;
  in[1].Name = L"Link";
  in[1].Flags = 0|wCIF_OPTIONAL|wCIF_METHODCHOOSE;
  in[2].Type = AnyTypeType;
  in[2].DefaultClass = 0;
  in[2].Name = L"Link";
  in[2].Flags = 0|wCIF_OPTIONAL|wCIF_METHODCHOOSE;
  in[3].Type = AnyTypeType;
  in[3].DefaultClass = 0;
  in[3].Name = L"Link";
  in[3].Flags = 0|wCIF_OPTIONAL|wCIF_METHODCHOOSE;
  in[4].Type = AnyTypeType;
  in[4].DefaultClass = 0;
  in[4].Name = L"Link";
  in[4].Flags = 0|wCIF_OPTIONAL|wCIF_METHODCHOOSE;
  Doc->Classes.AddTail(cl);

  cl= new wClass;
  cl->Name = L"Input";
  cl->Label = L"Input";
  cl->OutputType = AnyTypeType;
  cl->TabType = AnyTypeType;
  cl->MakeGui = AnyTypeGuiInput;
  cl->SetDefaults = AnyTypeDefInput;
  cl->BindPara = AnyTypeBindInput;
  cl->Bind2Para = AnyTypeBind2Input;
  cl->Bind3Para = AnyTypeBind3Input;
  cl->WikiText = AnyTypeWikiInput;
  cl->ParaWords = 1;
  cl->Column = 30;
  cl->Flags = 0x80000;
  Doc->Classes.AddTail(cl);

  cl= new wClass;
  cl->Name = L"InjectGlobals";
  cl->Label = L"InjectGlobals";
  cl->OutputType = AnyTypeType;
  cl->TabType = AnyTypeType;
  cl->MakeGui = AnyTypeGuiInjectGlobals;
  cl->SetDefaults = AnyTypeDefInjectGlobals;
  cl->BindPara = AnyTypeBindInjectGlobals;
  cl->Bind2Para = AnyTypeBind2InjectGlobals;
  cl->Bind3Para = AnyTypeBind3InjectGlobals;
  cl->WikiText = AnyTypeWikiInjectGlobals;
  cl->Column = 30;
  cl->Flags = 0x800000;
  in = cl->Inputs.AddMany(2);
  in[0].Type = AnyTypeType;
  in[0].DefaultClass = Doc->FindClass(L"Dummy",L"AnyType");
  in[0].Flags = 0;
  in[1].Type = AnyTypeType;
  in[1].DefaultClass = 0;
  in[1].Name = L"InjectFrom";
  in[1].Flags = 0|wCIF_METHODLINK;
  Doc->Classes.AddTail(cl);

  cl= new wClass;
  cl->Name = L"Loop";
  cl->Label = L"Loop";
  cl->OutputType = AnyTypeType;
  cl->TabType = AnyTypeType;
  cl->MakeGui = AnyTypeGuiLoop;
  cl->SetDefaults = AnyTypeDefLoop;
  cl->BindPara = AnyTypeBindLoop;
  cl->Bind2Para = AnyTypeBind2Loop;
  cl->Bind3Para = AnyTypeBind3Loop;
  cl->WikiText = AnyTypeWikiLoop;
  cl->ParaStrings = 1;
  cl->ParaWords = 1;
  cl->Column = 30;
  cl->Flags = 0x900000;
  in = cl->Inputs.AddMany(1);
  in[0].Type = AnyTypeType;
  in[0].DefaultClass = 0;
  in[0].Flags = 0;
  Doc->Classes.AddTail(cl);

  cl= new wClass;
  cl->Name = L"EndLoop";
  cl->Label = L"EndLoop";
  cl->OutputType = AnyTypeType;
  cl->TabType = AnyTypeType;
  cl->MakeGui = AnyTypeGuiEndLoop;
  cl->SetDefaults = AnyTypeDefEndLoop;
  cl->BindPara = AnyTypeBindEndLoop;
  cl->Bind2Para = AnyTypeBind2EndLoop;
  cl->Bind3Para = AnyTypeBind3EndLoop;
  cl->WikiText = AnyTypeWikiEndLoop;
  cl->Column = 30;
  cl->Flags = 0xa00000;
  in = cl->Inputs.AddMany(1);
  in[0].Type = AnyTypeType;
  in[0].DefaultClass = 0;
  in[0].Flags = 0;
  Doc->Classes.AddTail(cl);

  cl= new wClass;
  cl->Name = L"ShellSwitch";
  cl->Label = L"ShellSwitch";
  cl->OutputType = AnyTypeType;
  cl->TabType = AnyTypeType;
  cl->MakeGui = AnyTypeGuiShellSwitch;
  cl->SetDefaults = AnyTypeDefShellSwitch;
  cl->BindPara = AnyTypeBindShellSwitch;
  cl->Bind2Para = AnyTypeBind2ShellSwitch;
  cl->Bind3Para = AnyTypeBind3ShellSwitch;
  cl->WikiText = AnyTypeWikiShellSwitch;
  cl->ParaWords = 1;
  cl->Column = 30;
  cl->Flags = 0xc00000;
  in = cl->Inputs.AddMany(1);
  in[0].Type = AnyTypeType;
  in[0].DefaultClass = 0;
  in[0].Flags = 0;
  Doc->Classes.AddTail(cl);

  cl= new wClass;
  cl->Name = L"MakeTexture";
  cl->Label = L"MakeTexture";
  cl->OutputType = Texture2DType;
  cl->TabType = Texture2DType;
  cl->Command = Texture2DCmdMakeTexture;
  cl->MakeGui = Texture2DGuiMakeTexture;
  cl->SetDefaults = Texture2DDefMakeTexture;
  cl->BindPara = Texture2DBindMakeTexture;
  cl->Bind2Para = Texture2DBind2MakeTexture;
  cl->Bind3Para = Texture2DBind3MakeTexture;
  cl->WikiText = Texture2DWikiMakeTexture;
  cl->ParaWords = 2;
  cl->Column = 3;
  cl->Flags = 0x0080;
  in = cl->Inputs.AddMany(1);
  in[0].Type = BitmapBaseType;
  in[0].DefaultClass = 0;
  in[0].Flags = 0;
  Doc->Classes.AddTail(cl);

  cl= new wClass;
  cl->Name = L"Export";
  cl->Label = L"Export";
  cl->OutputType = Texture2DType;
  cl->TabType = Texture2DType;
  cl->Command = Texture2DCmdExport;
  cl->MakeGui = Texture2DGuiExport;
  cl->SetDefaults = Texture2DDefExport;
  cl->BindPara = Texture2DBindExport;
  cl->Bind2Para = Texture2DBind2Export;
  cl->Bind3Para = Texture2DBind3Export;
  cl->WikiText = Texture2DWikiExport;
  cl->ParaStrings = 1;
  cl->FileOutMask = 1;
  cl->Column = 3;
  cl->Flags = 0x1800;
  in = cl->Inputs.AddMany(1);
  in[0].Type = Texture2DType;
  in[0].DefaultClass = 0;
  in[0].Flags = 0;
  Doc->Classes.AddTail(cl);

  cl= new wClass;
  cl->Name = L"Import";
  cl->Label = L"Import";
  cl->OutputType = Texture2DType;
  cl->TabType = Texture2DType;
  cl->Command = Texture2DCmdImport;
  cl->MakeGui = Texture2DGuiImport;
  cl->SetDefaults = Texture2DDefImport;
  cl->BindPara = Texture2DBindImport;
  cl->Bind2Para = Texture2DBind2Import;
  cl->Bind3Para = Texture2DBind3Import;
  cl->WikiText = Texture2DWikiImport;
  cl->ParaStrings = 1;
  cl->FileInMask = 1;
  cl->FileInFilter = L"wz4tex";
  cl->Column = 3;
  cl->Flags = 0x0000;
  Doc->Classes.AddTail(cl);

  cl= new wClass;
  cl->Name = L"MakeCubeTex";
  cl->Label = L"MakeCubeTex";
  cl->OutputType = TextureCubeType;
  cl->TabType = TextureCubeType;
  cl->Command = TextureCubeCmdMakeCubeTex;
  cl->MakeGui = TextureCubeGuiMakeCubeTex;
  cl->SetDefaults = TextureCubeDefMakeCubeTex;
  cl->BindPara = TextureCubeBindMakeCubeTex;
  cl->Bind2Para = TextureCubeBind2MakeCubeTex;
  cl->Bind3Para = TextureCubeBind3MakeCubeTex;
  cl->WikiText = TextureCubeWikiMakeCubeTex;
  cl->ParaWords = 1;
  cl->Column = 3;
  cl->Flags = 0x0080;
  in = cl->Inputs.AddMany(1);
  in[0].Type = CubemapBaseType;
  in[0].DefaultClass = 0;
  in[0].Flags = 0;
  Doc->Classes.AddTail(cl);

  cl= new wClass;
  cl->Name = L"Add";
  cl->Label = L"Add";
  cl->OutputType = SceneType;
  cl->TabType = SceneType;
  cl->Command = SceneCmdAdd;
  cl->MakeGui = SceneGuiAdd;
  cl->SetDefaults = SceneDefAdd;
  cl->BindPara = SceneBindAdd;
  cl->Bind2Para = SceneBind2Add;
  cl->Bind3Para = SceneBind3Add;
  cl->WikiText = SceneWikiAdd;
  cl->Column = 2;
  cl->Flags = 0x0001;
  in = cl->Inputs.AddMany(1);
  in[0].Type = SceneType;
  in[0].DefaultClass = 0;
  in[0].Flags = 0|wCIF_OPTIONAL;
  Doc->Classes.AddTail(cl);

  cl= new wClass;
  cl->Name = L"ConvertSceneNode";
  cl->Label = L"ConvertSceneNode";
  cl->OutputType = SceneType;
  cl->TabType = SceneType;
  cl->Command = SceneCmdConvertSceneNode;
  cl->MakeGui = SceneGuiConvertSceneNode;
  cl->SetDefaults = SceneDefConvertSceneNode;
  cl->BindPara = SceneBindConvertSceneNode;
  cl->Bind2Para = SceneBind2ConvertSceneNode;
  cl->Bind3Para = SceneBind3ConvertSceneNode;
  cl->WikiText = SceneWikiConvertSceneNode;
  cl->Column = 3;
  cl->Flags = 0x0080;
  in = cl->Inputs.AddMany(1);
  in[0].Type = MeshBaseType;
  in[0].DefaultClass = 0;
  in[0].Flags = 0;
  Doc->Classes.AddTail(cl);

  cl= new wClass;
  cl->Name = L"Node";
  cl->Label = L"Node";
  cl->OutputType = SceneType;
  cl->TabType = SceneType;
  cl->Command = SceneCmdNode;
  cl->MakeGui = SceneGuiNode;
  cl->SetDefaults = SceneDefNode;
  cl->BindPara = SceneBindNode;
  cl->Bind2Para = SceneBind2Node;
  cl->Bind3Para = SceneBind3Node;
  cl->WikiText = SceneWikiNode;
  cl->ParaWords = 6;
  cl->Column = 3;
  cl->Flags = 0x0000;
  in = cl->Inputs.AddMany(1);
  in[0].Type = MeshBaseType;
  in[0].DefaultClass = 0;
  in[0].Flags = 0;
  Doc->Classes.AddTail(cl);

  cl= new wClass;
  cl->Name = L"NameId";
  cl->Label = L"NameId";
  cl->OutputType = SceneType;
  cl->TabType = SceneType;
  cl->Command = SceneCmdNameId;
  cl->MakeGui = SceneGuiNameId;
  cl->SetDefaults = SceneDefNameId;
  cl->BindPara = SceneBindNameId;
  cl->Bind2Para = SceneBind2NameId;
  cl->Bind3Para = SceneBind3NameId;
  cl->WikiText = SceneWikiNameId;
  cl->ParaWords = 1;
  cl->Column = 2;
  cl->Flags = 0x0001;
  in = cl->Inputs.AddMany(1);
  in[0].Type = SceneType;
  in[0].DefaultClass = 0;
  in[0].Flags = 0|wCIF_OPTIONAL;
  Doc->Classes.AddTail(cl);

  cl= new wClass;
  cl->Name = L"SelectNameId";
  cl->Label = L"SelectNameId";
  cl->OutputType = SceneType;
  cl->TabType = SceneType;
  cl->Command = SceneCmdSelectNameId;
  cl->MakeGui = SceneGuiSelectNameId;
  cl->SetDefaults = SceneDefSelectNameId;
  cl->BindPara = SceneBindSelectNameId;
  cl->Bind2Para = SceneBind2SelectNameId;
  cl->Bind3Para = SceneBind3SelectNameId;
  cl->WikiText = SceneWikiSelectNameId;
  cl->ParaWords = 2;
  cl->Column = 1;
  cl->Flags = 0x0000;
  in = cl->Inputs.AddMany(1);
  in[0].Type = SceneType;
  in[0].DefaultClass = 0;
  in[0].Flags = 0;
  Doc->Classes.AddTail(cl);

  cl= new wClass;
  cl->Name = L"Transform";
  cl->Label = L"Transform";
  cl->OutputType = SceneType;
  cl->TabType = SceneType;
  cl->Command = SceneCmdTransform;
  cl->MakeGui = SceneGuiTransform;
  cl->SetDefaults = SceneDefTransform;
  cl->BindPara = SceneBindTransform;
  cl->Bind2Para = SceneBind2Transform;
  cl->Bind3Para = SceneBind3Transform;
  cl->WikiText = SceneWikiTransform;
  cl->Handles = SceneHndTransform;
  cl->Actions = SceneActTransform;
  cl->ParaWords = 9;
  cl->Shortcut = 't';
  cl->Column = 2;
  cl->Flags = 0x0001;
  in = cl->Inputs.AddMany(1);
  in[0].Type = SceneType;
  in[0].DefaultClass = 0;
  in[0].Flags = 0|wCIF_OPTIONAL;
  cl->ActionIds.AddMany(1)->Init(L"Invert",1);
  cl->ActionIds.AddMany(1)->Init(L"Copy SRT",2);
  cl->ActionIds.AddMany(1)->Init(L"Paste SRT",3);
  Doc->Classes.AddTail(cl);

  cl= new wClass;
  cl->Name = L"Multiply";
  cl->Label = L"Multiply";
  cl->OutputType = SceneType;
  cl->TabType = SceneType;
  cl->Command = SceneCmdMultiply;
  cl->MakeGui = SceneGuiMultiply;
  cl->SetDefaults = SceneDefMultiply;
  cl->BindPara = SceneBindMultiply;
  cl->Bind2Para = SceneBind2Multiply;
  cl->Bind3Para = SceneBind3Multiply;
  cl->WikiText = SceneWikiMultiply;
  cl->Handles = SceneHndMultiply;
  cl->ParaWords = 19;
  cl->Shortcut = 'm';
  cl->Column = 2;
  cl->Flags = 0x0001;
  in = cl->Inputs.AddMany(1);
  in[0].Type = SceneType;
  in[0].DefaultClass = 0;
  in[0].Flags = 0|wCIF_OPTIONAL;
  Doc->Classes.AddTail(cl);

  cl= new wClass;
  cl->Name = L"Screenshot";
  cl->Label = L"Screenshot";
  cl->OutputType = ScreenshotProxyType;
  cl->TabType = ScreenshotProxyType;
  cl->Command = ScreenshotProxyCmdScreenshot;
  cl->MakeGui = ScreenshotProxyGuiScreenshot;
  cl->SetDefaults = ScreenshotProxyDefScreenshot;
  cl->BindPara = ScreenshotProxyBindScreenshot;
  cl->Bind2Para = ScreenshotProxyBind2Screenshot;
  cl->Bind3Para = ScreenshotProxyBind3Screenshot;
  cl->WikiText = ScreenshotProxyWikiScreenshot;
  cl->Actions = ScreenshotProxyActScreenshot;
  cl->ParaStrings = 1;
  cl->ParaWords = 18;
  cl->FileOutMask = 1;
  cl->Column = 3;
  cl->Flags = 0x0000;
  in = cl->Inputs.AddMany(1);
  in[0].Type = AnyTypeType;
  in[0].DefaultClass = 0;
  in[0].Flags = 0;
  cl->ActionIds.AddMany(1)->Init(L"CopyCam",1);
  Doc->Classes.AddTail(cl);

  cl= new wClass;
  cl->Name = L"UnitTestAdd";
  cl->Label = L"UnitTestAdd";
  cl->OutputType = UnitTestType;
  cl->TabType = UnitTestType;
  cl->Command = UnitTestCmdUnitTestAdd;
  cl->MakeGui = UnitTestGuiUnitTestAdd;
  cl->SetDefaults = UnitTestDefUnitTestAdd;
  cl->BindPara = UnitTestBindUnitTestAdd;
  cl->Bind2Para = UnitTestBind2UnitTestAdd;
  cl->Bind3Para = UnitTestBind3UnitTestAdd;
  cl->WikiText = UnitTestWikiUnitTestAdd;
  cl->Column = 2;
  cl->Flags = 0x0001;
  in = cl->Inputs.AddMany(1);
  in[0].Type = UnitTestType;
  in[0].DefaultClass = 0;
  in[0].Flags = 0|wCIF_OPTIONAL;
  Doc->Classes.AddTail(cl);

  cl= new wClass;
  cl->Name = L"UnitTestScene";
  cl->Label = L"UnitTestScene";
  cl->OutputType = UnitTestType;
  cl->TabType = SceneType;
  cl->Command = UnitTestCmdUnitTestScene;
  cl->MakeGui = UnitTestGuiUnitTestScene;
  cl->SetDefaults = UnitTestDefUnitTestScene;
  cl->BindPara = UnitTestBindUnitTestScene;
  cl->Bind2Para = UnitTestBind2UnitTestScene;
  cl->Bind3Para = UnitTestBind3UnitTestScene;
  cl->WikiText = UnitTestWikiUnitTestScene;
  cl->ParaStrings = 1;
  cl->ParaWords = 9;
  cl->FileOutMask = 1;
  cl->Column = 3;
  cl->Flags = 0x0000;
  in = cl->Inputs.AddMany(1);
  in[0].Type = SceneType;
  in[0].DefaultClass = 0;
  in[0].Flags = 0;
  Doc->Classes.AddTail(cl);

}

// sADDSUBSYSTEM(basic_ops,0x101,AddOps_basic_ops,0);


/****************************************************************************/

