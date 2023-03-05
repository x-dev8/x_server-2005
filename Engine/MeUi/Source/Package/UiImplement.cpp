/*
** Lua binding: CompileToLua
** Generated automatically by tolua++-1.0.92 on 04/24/10 21:30:31.
*/

#ifndef __cplusplus
#include "stdlib.h"
#endif
#include "string.h"

#include "tolua++.h"

/* Exported function */
TOLUA_API int  tolua_CompileToLua_open (lua_State* tolua_S);


/* function to release collected object via destructor */
#ifdef __cplusplus

static int tolua_collect_ControlProgress (lua_State* tolua_S)
{
 ControlProgress* self = (ControlProgress*) tolua_tousertype(tolua_S,1,0);
	delete self;
	return 0;
}

static int tolua_collect_S_IconInfoBase__sShowGem (lua_State* tolua_S)
{
 S_IconInfoBase::sShowGem* self = (S_IconInfoBase::sShowGem*) tolua_tousertype(tolua_S,1,0);
	delete self;
	return 0;
}

static int tolua_collect_ControlScrollBar (lua_State* tolua_S)
{
 ControlScrollBar* self = (ControlScrollBar*) tolua_tousertype(tolua_S,1,0);
	delete self;
	return 0;
}

static int tolua_collect_ControlIconDrag__S_ListImg (lua_State* tolua_S)
{
 ControlIconDrag::S_ListImg* self = (ControlIconDrag::S_ListImg*) tolua_tousertype(tolua_S,1,0);
	delete self;
	return 0;
}

static int tolua_collect_BtnState (lua_State* tolua_S)
{
 BtnState* self = (BtnState*) tolua_tousertype(tolua_S,1,0);
	delete self;
	return 0;
}

static int tolua_collect_COLORREF (lua_State* tolua_S)
{
 COLORREF* self = (COLORREF*) tolua_tousertype(tolua_S,1,0);
	delete self;
	return 0;
}

static int tolua_collect_ControlPicture (lua_State* tolua_S)
{
 ControlPicture* self = (ControlPicture*) tolua_tousertype(tolua_S,1,0);
	delete self;
	return 0;
}

static int tolua_collect_ControlList__S_List (lua_State* tolua_S)
{
 ControlList::S_List* self = (ControlList::S_List*) tolua_tousertype(tolua_S,1,0);
	delete self;
	return 0;
}

static int tolua_collect_ControlComboBox (lua_State* tolua_S)
{
 ControlComboBox* self = (ControlComboBox*) tolua_tousertype(tolua_S,1,0);
	delete self;
	return 0;
}

static int tolua_collect_UiManager__S_UI (lua_State* tolua_S)
{
 UiManager::S_UI* self = (UiManager::S_UI*) tolua_tousertype(tolua_S,1,0);
	delete self;
	return 0;
}

static int tolua_collect_S_IconInfoBase (lua_State* tolua_S)
{
 S_IconInfoBase* self = (S_IconInfoBase*) tolua_tousertype(tolua_S,1,0);
	delete self;
	return 0;
}

static int tolua_collect_std__vector_ControlList__S_List__ (lua_State* tolua_S)
{
 std::vector<ControlList::S_List*>* self = (std::vector<ControlList::S_List*>*) tolua_tousertype(tolua_S,1,0);
	delete self;
	return 0;
}

static int tolua_collect_ControlListImage (lua_State* tolua_S)
{
 ControlListImage* self = (ControlListImage*) tolua_tousertype(tolua_S,1,0);
	delete self;
	return 0;
}

static int tolua_collect_D3DCOLOR (lua_State* tolua_S)
{
 D3DCOLOR* self = (D3DCOLOR*) tolua_tousertype(tolua_S,1,0);
	delete self;
	return 0;
}

static int tolua_collect_ControlIconDragManager (lua_State* tolua_S)
{
 ControlIconDragManager* self = (ControlIconDragManager*) tolua_tousertype(tolua_S,1,0);
	delete self;
	return 0;
}

static int tolua_collect_SCharItem (lua_State* tolua_S)
{
 SCharItem* self = (SCharItem*) tolua_tousertype(tolua_S,1,0);
	delete self;
	return 0;
}

static int tolua_collect_DWORD (lua_State* tolua_S)
{
 DWORD* self = (DWORD*) tolua_tousertype(tolua_S,1,0);
	delete self;
	return 0;
}

static int tolua_collect_ControlButton (lua_State* tolua_S)
{
 ControlButton* self = (ControlButton*) tolua_tousertype(tolua_S,1,0);
	delete self;
	return 0;
}

static int tolua_collect_S_TextTipInfo (lua_State* tolua_S)
{
 S_TextTipInfo* self = (S_TextTipInfo*) tolua_tousertype(tolua_S,1,0);
	delete self;
	return 0;
}

static int tolua_collect_UiManager (lua_State* tolua_S)
{
 UiManager* self = (UiManager*) tolua_tousertype(tolua_S,1,0);
	delete self;
	return 0;
}

static int tolua_collect_ControlText (lua_State* tolua_S)
{
 ControlText* self = (ControlText*) tolua_tousertype(tolua_S,1,0);
	delete self;
	return 0;
}

static int tolua_collect_MouseManager (lua_State* tolua_S)
{
 MouseManager* self = (MouseManager*) tolua_tousertype(tolua_S,1,0);
	delete self;
	return 0;
}

static int tolua_collect_ControlIconDrag (lua_State* tolua_S)
{
 ControlIconDrag* self = (ControlIconDrag*) tolua_tousertype(tolua_S,1,0);
	delete self;
	return 0;
}

static int tolua_collect_ControlTab (lua_State* tolua_S)
{
 ControlTab* self = (ControlTab*) tolua_tousertype(tolua_S,1,0);
	delete self;
	return 0;
}

static int tolua_collect_ControlText__SText (lua_State* tolua_S)
{
 ControlText::SText* self = (ControlText::SText*) tolua_tousertype(tolua_S,1,0);
	delete self;
	return 0;
}

static int tolua_collect_ControlList (lua_State* tolua_S)
{
 ControlList* self = (ControlList*) tolua_tousertype(tolua_S,1,0);
	delete self;
	return 0;
}

static int tolua_collect_ControlScrollBarEx (lua_State* tolua_S)
{
 ControlScrollBarEx* self = (ControlScrollBarEx*) tolua_tousertype(tolua_S,1,0);
	delete self;
	return 0;
}

static int tolua_collect_ControlFrame (lua_State* tolua_S)
{
 ControlFrame* self = (ControlFrame*) tolua_tousertype(tolua_S,1,0);
	delete self;
	return 0;
}

static int tolua_collect_CIconInfoMouseTip (lua_State* tolua_S)
{
 CIconInfoMouseTip* self = (CIconInfoMouseTip*) tolua_tousertype(tolua_S,1,0);
	delete self;
	return 0;
}

static int tolua_collect_ControlEdit (lua_State* tolua_S)
{
 ControlEdit* self = (ControlEdit*) tolua_tousertype(tolua_S,1,0);
	delete self;
	return 0;
}

static int tolua_collect_POINT (lua_State* tolua_S)
{
 POINT* self = (POINT*) tolua_tousertype(tolua_S,1,0);
	delete self;
	return 0;
}

static int tolua_collect_ControlListEx (lua_State* tolua_S)
{
 ControlListEx* self = (ControlListEx*) tolua_tousertype(tolua_S,1,0);
	delete self;
	return 0;
}

static int tolua_collect_ControlCheckBox (lua_State* tolua_S)
{
 ControlCheckBox* self = (ControlCheckBox*) tolua_tousertype(tolua_S,1,0);
	delete self;
	return 0;
}

static int tolua_collect_S_IconInfoBase__stIconInfo (lua_State* tolua_S)
{
 S_IconInfoBase::stIconInfo* self = (S_IconInfoBase::stIconInfo*) tolua_tousertype(tolua_S,1,0);
	delete self;
	return 0;
}

static int tolua_collect_ControlObject (lua_State* tolua_S)
{
 ControlObject* self = (ControlObject*) tolua_tousertype(tolua_S,1,0);
	delete self;
	return 0;
}

static int tolua_collect_S_IconInfoHero (lua_State* tolua_S)
{
 S_IconInfoHero* self = (S_IconInfoHero*) tolua_tousertype(tolua_S,1,0);
	delete self;
	return 0;
}
#endif


/* function to register type */
static void tolua_reg_types (lua_State* tolua_S)
{
 tolua_usertype(tolua_S,"ControlList::funSelectChange");
 tolua_usertype(tolua_S,"zizi");
 tolua_usertype(tolua_S,"ControlProgress");
 tolua_usertype(tolua_S,"S_ButtonData::S_Pic");
 tolua_usertype(tolua_S,"std::wstring");
 tolua_usertype(tolua_S,"ControlScrollBar");
 tolua_usertype(tolua_S,"ControlIconDrag::S_ListImg");
 tolua_usertype(tolua_S,"ControlScrollBarEx");
 tolua_usertype(tolua_S,"ControlIconDrag::funLDBClick");
 tolua_usertype(tolua_S,"WPARAM");
 tolua_usertype(tolua_S,"ControlComboBox");
 tolua_usertype(tolua_S,"std::vector<ControlList::S_List*>");
 tolua_usertype(tolua_S,"ControlListImage");
 tolua_usertype(tolua_S,"ControlIconDragManager");
 tolua_usertype(tolua_S,"ControlList::funLDBClick");
 tolua_usertype(tolua_S,"ControlEdit::funOnEnter");
 tolua_usertype(tolua_S,"ControlText::STextData");
 tolua_usertype(tolua_S,"S_BaseData::S_Pic");
 tolua_usertype(tolua_S,"INT");
 tolua_usertype(tolua_S,"S_TextTipInfo");
 tolua_usertype(tolua_S,"ControlText");
 tolua_usertype(tolua_S,"ControlText::SText");
 tolua_usertype(tolua_S,"ControlList");
 tolua_usertype(tolua_S,"CIconInfoMouseTip");
 tolua_usertype(tolua_S,"ControlComboBox::funOnChange");
 tolua_usertype(tolua_S,"ControlListEx");
 tolua_usertype(tolua_S,"S_BaseData");
 tolua_usertype(tolua_S,"ControlButton::funOnButtonClick");
 tolua_usertype(tolua_S,"S_IconInfoHero");
 tolua_usertype(tolua_S,"ControlFrame::funRender");
 tolua_usertype(tolua_S,"S_IconInfoBase::sShowGem");
 tolua_usertype(tolua_S,"ControlText::funHyberClick");
 tolua_usertype(tolua_S,"ControlCheckBox::funOnCheck");
 tolua_usertype(tolua_S,"ControlFrame::funRun");
 tolua_usertype(tolua_S,"ControlTab");
 tolua_usertype(tolua_S,"BOOL");
 tolua_usertype(tolua_S,"UINT");
 tolua_usertype(tolua_S,"ControlList::S_List");
 tolua_usertype(tolua_S,"ControlScrollBar::funUpdatePos");
 tolua_usertype(tolua_S,"ICON_INFO_STRUCT");
 tolua_usertype(tolua_S,"UiManager::S_UI");
 tolua_usertype(tolua_S,"S_IconInfoBase");
 tolua_usertype(tolua_S,"CHAR");
 tolua_usertype(tolua_S,"D3DCOLOR");
 tolua_usertype(tolua_S,"SCharItem");
 tolua_usertype(tolua_S,"WCHAR");
 tolua_usertype(tolua_S,"ControlIconDrag");
 tolua_usertype(tolua_S,"ControlButton");
 tolua_usertype(tolua_S,"POINT");
 tolua_usertype(tolua_S,"ControlIconDrag::funRButtonUp");
 tolua_usertype(tolua_S,"ControlIconDrag::funDragOn");
 tolua_usertype(tolua_S,"BtnState");
 tolua_usertype(tolua_S,"MouseManager");
 tolua_usertype(tolua_S,"COLORREF");
 tolua_usertype(tolua_S,"SCRIPT_STRING_ANALYSIS");
 tolua_usertype(tolua_S,"ControlPicture");
 tolua_usertype(tolua_S,"std::vector<ControlText::STextData>");
 tolua_usertype(tolua_S,"RECT");
 tolua_usertype(tolua_S,"ControlFrame");
 tolua_usertype(tolua_S,"LPARAM");
 tolua_usertype(tolua_S,"ControlEdit");
 tolua_usertype(tolua_S,"HWND");
 tolua_usertype(tolua_S,"UiManager");
 tolua_usertype(tolua_S,"ControlCheckBox");
 tolua_usertype(tolua_S,"ControlObject");
 tolua_usertype(tolua_S,"DWORD");
 tolua_usertype(tolua_S,"S_IconInfoBase::stIconInfo");
}

/* method: Render of class  ControlButton */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlButton_Render00
static int tolua_CompileToLua_ControlButton_Render00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlButton",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlButton* self = (ControlButton*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Render'",NULL);
#endif
  {
   self->Render();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Render'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: OnKeyDown of class  ControlButton */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlButton_OnKeyDown00
static int tolua_CompileToLua_ControlButton_OnKeyDown00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlButton",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"UINT",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlButton* self = (ControlButton*)  tolua_tousertype(tolua_S,1,0);
  UINT nChar = *((UINT*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'OnKeyDown'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->OnKeyDown(nChar);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'OnKeyDown'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: OnKeyUp of class  ControlButton */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlButton_OnKeyUp00
static int tolua_CompileToLua_ControlButton_OnKeyUp00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlButton",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"UINT",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlButton* self = (ControlButton*)  tolua_tousertype(tolua_S,1,0);
  UINT nChar = *((UINT*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'OnKeyUp'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->OnKeyUp(nChar);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'OnKeyUp'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: OnMouseMove of class  ControlButton */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlButton_OnMouseMove00
static int tolua_CompileToLua_ControlButton_OnMouseMove00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlButton",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"UINT",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlButton* self = (ControlButton*)  tolua_tousertype(tolua_S,1,0);
  UINT nFlags = *((UINT*)  tolua_tousertype(tolua_S,2,0));
  const int nX = ((const int)  tolua_tonumber(tolua_S,3,0));
  const int nY = ((const int)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'OnMouseMove'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->OnMouseMove(nFlags,nX,nY);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'OnMouseMove'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: OnLButtonDown of class  ControlButton */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlButton_OnLButtonDown00
static int tolua_CompileToLua_ControlButton_OnLButtonDown00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlButton",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"UINT",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlButton* self = (ControlButton*)  tolua_tousertype(tolua_S,1,0);
  UINT nFlags = *((UINT*)  tolua_tousertype(tolua_S,2,0));
  const int nX = ((const int)  tolua_tonumber(tolua_S,3,0));
  const int nY = ((const int)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'OnLButtonDown'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->OnLButtonDown(nFlags,nX,nY);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'OnLButtonDown'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: OnLButtonUp of class  ControlButton */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlButton_OnLButtonUp00
static int tolua_CompileToLua_ControlButton_OnLButtonUp00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlButton",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"UINT",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlButton* self = (ControlButton*)  tolua_tousertype(tolua_S,1,0);
  UINT nFlags = *((UINT*)  tolua_tousertype(tolua_S,2,0));
  const int nX = ((const int)  tolua_tonumber(tolua_S,3,0));
  const int nY = ((const int)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'OnLButtonUp'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->OnLButtonUp(nFlags,nX,nY);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'OnLButtonUp'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: InitUIData of class  ControlButton */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlButton_InitUIData00
static int tolua_CompileToLua_ControlButton_InitUIData00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlButton",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"ControlObject",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"S_BaseData",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlButton* self = (ControlButton*)  tolua_tousertype(tolua_S,1,0);
  IN ControlObject* pFather = ((IN ControlObject*)  tolua_tousertype(tolua_S,2,0));
  IN S_BaseData* pData = ((IN S_BaseData*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'InitUIData'",NULL);
#endif
  {
   self->InitUIData(pFather,pData);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'InitUIData'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetButtonClickFun_2lua of class  ControlButton */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlButton_SetButtonClickFun_2lua00
static int tolua_CompileToLua_ControlButton_SetButtonClickFun_2lua00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlButton",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlButton* self = (ControlButton*)  tolua_tousertype(tolua_S,1,0);
  const char* luaTable = ((const char*)  tolua_tostring(tolua_S,2,0));
  const char* funName = ((const char*)  tolua_tostring(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetButtonClickFun_2lua'",NULL);
#endif
  {
   self->SetButtonClickFun_2lua(luaTable,funName);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetButtonClickFun_2lua'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetButtonMouseOnFun_2lua of class  ControlButton */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlButton_SetButtonMouseOnFun_2lua00
static int tolua_CompileToLua_ControlButton_SetButtonMouseOnFun_2lua00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlButton",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlButton* self = (ControlButton*)  tolua_tousertype(tolua_S,1,0);
  const char* luaTable = ((const char*)  tolua_tostring(tolua_S,2,0));
  const char* funName = ((const char*)  tolua_tostring(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetButtonMouseOnFun_2lua'",NULL);
#endif
  {
   self->SetButtonMouseOnFun_2lua(luaTable,funName);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetButtonMouseOnFun_2lua'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetPressPic of class  ControlButton */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlButton_SetPressPic00
static int tolua_CompileToLua_ControlButton_SetPressPic00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlButton",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlButton* self = (ControlButton*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetPressPic'",NULL);
#endif
  {
   self->SetPressPic();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetPressPic'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetNormalPic of class  ControlButton */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlButton_SetNormalPic00
static int tolua_CompileToLua_ControlButton_SetNormalPic00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlButton",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlButton* self = (ControlButton*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetNormalPic'",NULL);
#endif
  {
   self->SetNormalPic();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetNormalPic'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: IsDrag of class  ControlButton */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlButton_IsDrag00
static int tolua_CompileToLua_ControlButton_IsDrag00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlButton",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlButton* self = (ControlButton*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'IsDrag'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->IsDrag();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'IsDrag'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetEnable of class  ControlButton */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlButton_SetEnable00
static int tolua_CompileToLua_ControlButton_SetEnable00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlButton",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlButton* self = (ControlButton*)  tolua_tousertype(tolua_S,1,0);
  const bool b = ((const bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetEnable'",NULL);
#endif
  {
   self->SetEnable(b);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetEnable'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: IsEnable of class  ControlButton */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlButton_IsEnable00
static int tolua_CompileToLua_ControlButton_IsEnable00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlButton",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlButton* self = (ControlButton*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'IsEnable'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->IsEnable();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'IsEnable'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: IsPress of class  ControlButton */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlButton_IsPress00
static int tolua_CompileToLua_ControlButton_IsPress00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlButton",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlButton* self = (ControlButton*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'IsPress'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->IsPress();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'IsPress'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetMouseMove of class  ControlButton */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlButton_SetMouseMove00
static int tolua_CompileToLua_ControlButton_SetMouseMove00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlButton",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlButton* self = (ControlButton*)  tolua_tousertype(tolua_S,1,0);
  bool bMove = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetMouseMove'",NULL);
#endif
  {
   self->SetMouseMove(bMove);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetMouseMove'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetCaption of class  ControlButton */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlButton_SetCaption00
static int tolua_CompileToLua_ControlButton_SetCaption00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlButton",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlButton* self = (ControlButton*)  tolua_tousertype(tolua_S,1,0);
  const char* strObjName = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetCaption'",NULL);
#endif
  {
   self->SetCaption(strObjName);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetCaption'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetCaption of class  ControlButton */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlButton_GetCaption00
static int tolua_CompileToLua_ControlButton_GetCaption00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlButton",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlButton* self = (ControlButton*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetCaption'",NULL);
#endif
  {
   const char* tolua_ret = (const char*)  self->GetCaption();
   tolua_pushstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetCaption'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetState of class  ControlButton */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlButton_SetState00
static int tolua_CompileToLua_ControlButton_SetState00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlButton",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"BtnState",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlButton* self = (ControlButton*)  tolua_tousertype(tolua_S,1,0);
  BtnState nState = *((BtnState*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetState'",NULL);
#endif
  {
   self->SetState(nState);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetState'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetState of class  ControlButton */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlButton_GetState00
static int tolua_CompileToLua_ControlButton_GetState00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlButton",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlButton* self = (ControlButton*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetState'",NULL);
#endif
  {
   BtnState tolua_ret = (BtnState)  self->GetState();
   {
#ifdef __cplusplus
    void* tolua_obj = new BtnState(tolua_ret);
    tolua_pushusertype_and_takeownership(tolua_S,tolua_obj,"BtnState");
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(BtnState));
    tolua_pushusertype_and_takeownership(tolua_S,tolua_obj,"BtnState");
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetState'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getMouseMovePic of class  ControlButton */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlButton_getMouseMovePic00
static int tolua_CompileToLua_ControlButton_getMouseMovePic00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlButton",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlButton* self = (ControlButton*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getMouseMovePic'",NULL);
#endif
  {
   S_ButtonData::S_Pic* tolua_ret = (S_ButtonData::S_Pic*)  self->getMouseMovePic();
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"S_ButtonData::S_Pic");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getMouseMovePic'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getMousePressPic of class  ControlButton */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlButton_getMousePressPic00
static int tolua_CompileToLua_ControlButton_getMousePressPic00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlButton",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlButton* self = (ControlButton*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getMousePressPic'",NULL);
#endif
  {
   S_ButtonData::S_Pic* tolua_ret = (S_ButtonData::S_Pic*)  self->getMousePressPic();
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"S_ButtonData::S_Pic");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getMousePressPic'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getDisabledPic of class  ControlButton */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlButton_getDisabledPic00
static int tolua_CompileToLua_ControlButton_getDisabledPic00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlButton",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlButton* self = (ControlButton*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getDisabledPic'",NULL);
#endif
  {
   S_ButtonData::S_Pic* tolua_ret = (S_ButtonData::S_Pic*)  self->getDisabledPic();
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"S_ButtonData::S_Pic");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getDisabledPic'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setMouseMovePic of class  ControlButton */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlButton_setMouseMovePic00
static int tolua_CompileToLua_ControlButton_setMouseMovePic00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlButton",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"S_ButtonData::S_Pic",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlButton* self = (ControlButton*)  tolua_tousertype(tolua_S,1,0);
  S_ButtonData::S_Pic* pic = ((S_ButtonData::S_Pic*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setMouseMovePic'",NULL);
#endif
  {
   self->setMouseMovePic(pic);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setMouseMovePic'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setMousePressPic of class  ControlButton */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlButton_setMousePressPic00
static int tolua_CompileToLua_ControlButton_setMousePressPic00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlButton",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"S_ButtonData::S_Pic",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlButton* self = (ControlButton*)  tolua_tousertype(tolua_S,1,0);
  S_ButtonData::S_Pic* pic = ((S_ButtonData::S_Pic*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setMousePressPic'",NULL);
#endif
  {
   self->setMousePressPic(pic);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setMousePressPic'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setDisabledPic of class  ControlButton */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlButton_setDisabledPic00
static int tolua_CompileToLua_ControlButton_setDisabledPic00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlButton",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"S_ButtonData::S_Pic",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlButton* self = (ControlButton*)  tolua_tousertype(tolua_S,1,0);
  S_ButtonData::S_Pic* pic = ((S_ButtonData::S_Pic*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setDisabledPic'",NULL);
#endif
  {
   self->setDisabledPic(pic);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setDisabledPic'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetShowTip of class  ControlButton */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlButton_SetShowTip00
static int tolua_CompileToLua_ControlButton_SetShowTip00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlButton",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlButton* self = (ControlButton*)  tolua_tousertype(tolua_S,1,0);
  bool show = ((bool)  tolua_toboolean(tolua_S,2,true));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetShowTip'",NULL);
#endif
  {
   self->SetShowTip(show);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetShowTip'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setTip of class  ControlButton */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlButton_setTip00
static int tolua_CompileToLua_ControlButton_setTip00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlButton",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlButton* self = (ControlButton*)  tolua_tousertype(tolua_S,1,0);
  const char* data = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setTip'",NULL);
#endif
  {
   self->setTip(data);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setTip'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: OnButton of class  ControlButton */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlButton_OnButton00
static int tolua_CompileToLua_ControlButton_OnButton00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlButton",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlButton* self = (ControlButton*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'OnButton'",NULL);
#endif
  {
   self->OnButton();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'OnButton'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  ControlButton */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlButton_new00
static int tolua_CompileToLua_ControlButton_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"ControlButton",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   ControlButton* tolua_ret = (ControlButton*)  new ControlButton();
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"ControlButton");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  ControlButton */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlButton_new00_local
static int tolua_CompileToLua_ControlButton_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"ControlButton",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   ControlButton* tolua_ret = (ControlButton*)  new ControlButton();
   tolua_pushusertype_and_takeownership(tolua_S,(void *)tolua_ret,"ControlButton");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: delete of class  ControlButton */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlButton_delete00
static int tolua_CompileToLua_ControlButton_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlButton",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlButton* self = (ControlButton*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'",NULL);
#endif
  delete self;
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetAlias of class  ControlObject */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlObject_GetAlias00
static int tolua_CompileToLua_ControlObject_GetAlias00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlObject",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlObject* self = (ControlObject*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetAlias'",NULL);
#endif
  {
   const char* tolua_ret = (const char*)  self->GetAlias();
   tolua_pushstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetAlias'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Render of class  ControlObject */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlObject_Render00
static int tolua_CompileToLua_ControlObject_Render00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlObject",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlObject* self = (ControlObject*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Render'",NULL);
#endif
  {
   self->Render();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Render'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Run of class  ControlObject */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlObject_Run00
static int tolua_CompileToLua_ControlObject_Run00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlObject",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlObject* self = (ControlObject*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Run'",NULL);
#endif
  {
   self->Run();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Run'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: ReleaseUI of class  ControlObject */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlObject_ReleaseUI00
static int tolua_CompileToLua_ControlObject_ReleaseUI00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlObject",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlObject* self = (ControlObject*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'ReleaseUI'",NULL);
#endif
  {
   self->ReleaseUI();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'ReleaseUI'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: InitUIData of class  ControlObject */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlObject_InitUIData00
static int tolua_CompileToLua_ControlObject_InitUIData00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlObject",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"ControlObject",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"S_BaseData",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlObject* self = (ControlObject*)  tolua_tousertype(tolua_S,1,0);
  IN ControlObject* pFather = ((IN ControlObject*)  tolua_tousertype(tolua_S,2,0));
  IN S_BaseData* pData = ((IN S_BaseData*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'InitUIData'",NULL);
#endif
  {
   self->InitUIData(pFather,pData);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'InitUIData'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: UseFocus of class  ControlObject */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlObject_UseFocus00
static int tolua_CompileToLua_ControlObject_UseFocus00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlObject",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlObject* self = (ControlObject*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'UseFocus'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->UseFocus();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'UseFocus'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: IsNeedRender of class  ControlObject */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlObject_IsNeedRender00
static int tolua_CompileToLua_ControlObject_IsNeedRender00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlObject",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlObject* self = (ControlObject*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'IsNeedRender'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->IsNeedRender();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'IsNeedRender'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: PtInObject of class  ControlObject */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlObject_PtInObject00
static int tolua_CompileToLua_ControlObject_PtInObject00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlObject",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlObject* self = (ControlObject*)  tolua_tousertype(tolua_S,1,0);
  const int nX = ((const int)  tolua_tonumber(tolua_S,2,0));
  const int nY = ((const int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'PtInObject'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->PtInObject(nX,nY);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'PtInObject'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: PtInObject of class  ControlObject */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlObject_PtInObject01
static int tolua_CompileToLua_ControlObject_PtInObject01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlObject",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"const RECT",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  ControlObject* self = (ControlObject*)  tolua_tousertype(tolua_S,1,0);
  const RECT* rc = ((const RECT*)  tolua_tousertype(tolua_S,2,0));
  const int nX = ((const int)  tolua_tonumber(tolua_S,3,0));
  const int nY = ((const int)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'PtInObject'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->PtInObject(*rc,nX,nY);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
tolua_lerror:
 return tolua_CompileToLua_ControlObject_PtInObject00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetVisable of class  ControlObject */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlObject_SetVisable00
static int tolua_CompileToLua_ControlObject_SetVisable00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlObject",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isboolean(tolua_S,3,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlObject* self = (ControlObject*)  tolua_tousertype(tolua_S,1,0);
  const bool bVisable = ((const bool)  tolua_toboolean(tolua_S,2,0));
  const bool bFadeInorFadeOut = ((const bool)  tolua_toboolean(tolua_S,3,false));
  const int bColor = ((const int)  tolua_tonumber(tolua_S,4,0xff));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetVisable'",NULL);
#endif
  {
   self->SetVisable(bVisable,bFadeInorFadeOut,bColor);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetVisable'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: StartFlash of class  ControlObject */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlObject_StartFlash00
static int tolua_CompileToLua_ControlObject_StartFlash00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlObject",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isboolean(tolua_S,3,1,&tolua_err) ||
     !tolua_isboolean(tolua_S,4,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlObject* self = (ControlObject*)  tolua_tousertype(tolua_S,1,0);
  const int nFlashCount = ((const int)  tolua_tonumber(tolua_S,2,0));
  const bool bAutoClose = ((const bool)  tolua_toboolean(tolua_S,3,false));
  const bool bFadeIn = ((const bool)  tolua_toboolean(tolua_S,4,false));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'StartFlash'",NULL);
#endif
  {
   self->StartFlash(nFlashCount,bAutoClose,bFadeIn);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'StartFlash'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetRealRect of class  ControlObject */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlObject_SetRealRect00
static int tolua_CompileToLua_ControlObject_SetRealRect00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlObject",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"const RECT",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlObject* self = (ControlObject*)  tolua_tousertype(tolua_S,1,0);
  IN  const RECT* prc = ((IN  const RECT*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetRealRect'",NULL);
#endif
  {
   self->SetRealRect(prc);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetRealRect'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: MsgProc of class  ControlObject */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlObject_MsgProc00
static int tolua_CompileToLua_ControlObject_MsgProc00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlObject",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"UINT",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"WPARAM",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,4,"LPARAM",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,5,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlObject* self = (ControlObject*)  tolua_tousertype(tolua_S,1,0);
  UINT msg = *((UINT*)  tolua_tousertype(tolua_S,2,0));
  WPARAM wParam = *((WPARAM*)  tolua_tousertype(tolua_S,3,0));
  LPARAM lParam = *((LPARAM*)  tolua_tousertype(tolua_S,4,0));
  bool bMsgUsed = ((bool)  tolua_toboolean(tolua_S,5,false));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'MsgProc'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->MsgProc(msg,wParam,lParam,bMsgUsed);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'MsgProc'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: FindControl of class  ControlObject */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlObject_FindControl00
static int tolua_CompileToLua_ControlObject_FindControl00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlObject",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlObject* self = (ControlObject*)  tolua_tousertype(tolua_S,1,0);
  IN  const char* szControlID = ((IN  const char*)  tolua_tostring(tolua_S,2,0));
  IN  const char* szFrameID = ((IN  const char*)  tolua_tostring(tolua_S,3,NULL));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'FindControl'",NULL);
#endif
  {
   ControlObject* tolua_ret = (ControlObject*)  self->FindControl(szControlID,szFrameID);
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"ControlObject");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'FindControl'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: FindFrame of class  ControlObject */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlObject_FindFrame00
static int tolua_CompileToLua_ControlObject_FindFrame00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlObject",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlObject* self = (ControlObject*)  tolua_tousertype(tolua_S,1,0);
  IN  const char* szFrameID = ((IN  const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'FindFrame'",NULL);
#endif
  {
   ControlObject* tolua_ret = (ControlObject*)  self->FindFrame(szFrameID);
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"ControlObject");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'FindFrame'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetArrayMode of class  ControlObject */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlObject_GetArrayMode00
static int tolua_CompileToLua_ControlObject_GetArrayMode00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlObject",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlObject* self = (ControlObject*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetArrayMode'",NULL);
#endif
  {
   int tolua_ret = (int)  self->GetArrayMode();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetArrayMode'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: IsChild of class  ControlObject */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlObject_IsChild00
static int tolua_CompileToLua_ControlObject_IsChild00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlObject",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"const ControlObject",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlObject* self = (ControlObject*)  tolua_tousertype(tolua_S,1,0);
  IN  const ControlObject* pChild = ((IN  const ControlObject*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'IsChild'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->IsChild(pChild);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'IsChild'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: OnMouseMove of class  ControlObject */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlObject_OnMouseMove00
static int tolua_CompileToLua_ControlObject_OnMouseMove00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlObject",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"UINT",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlObject* self = (ControlObject*)  tolua_tousertype(tolua_S,1,0);
  UINT nFlags = *((UINT*)  tolua_tousertype(tolua_S,2,0));
  const int nX = ((const int)  tolua_tonumber(tolua_S,3,0));
  const int nY = ((const int)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'OnMouseMove'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->OnMouseMove(nFlags,nX,nY);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'OnMouseMove'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: OnMouseLeave of class  ControlObject */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlObject_OnMouseLeave00
static int tolua_CompileToLua_ControlObject_OnMouseLeave00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlObject",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlObject* self = (ControlObject*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'OnMouseLeave'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->OnMouseLeave();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'OnMouseLeave'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: OnMouseWheel of class  ControlObject */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlObject_OnMouseWheel00
static int tolua_CompileToLua_ControlObject_OnMouseWheel00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlObject",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlObject* self = (ControlObject*)  tolua_tousertype(tolua_S,1,0);
  bool bUp = ((bool)  tolua_toboolean(tolua_S,2,0));
  const int nX = ((const int)  tolua_tonumber(tolua_S,3,0));
  const int nY = ((const int)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'OnMouseWheel'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->OnMouseWheel(bUp,nX,nY);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'OnMouseWheel'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: OnLButtonDown of class  ControlObject */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlObject_OnLButtonDown00
static int tolua_CompileToLua_ControlObject_OnLButtonDown00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlObject",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"UINT",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlObject* self = (ControlObject*)  tolua_tousertype(tolua_S,1,0);
  UINT nFlags = *((UINT*)  tolua_tousertype(tolua_S,2,0));
  const int nX = ((const int)  tolua_tonumber(tolua_S,3,0));
  const int nY = ((const int)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'OnLButtonDown'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->OnLButtonDown(nFlags,nX,nY);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'OnLButtonDown'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: OnRButtonDown of class  ControlObject */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlObject_OnRButtonDown00
static int tolua_CompileToLua_ControlObject_OnRButtonDown00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlObject",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"UINT",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlObject* self = (ControlObject*)  tolua_tousertype(tolua_S,1,0);
  UINT nFlags = *((UINT*)  tolua_tousertype(tolua_S,2,0));
  const int nX = ((const int)  tolua_tonumber(tolua_S,3,0));
  const int nY = ((const int)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'OnRButtonDown'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->OnRButtonDown(nFlags,nX,nY);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'OnRButtonDown'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: OnLButtonUp of class  ControlObject */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlObject_OnLButtonUp00
static int tolua_CompileToLua_ControlObject_OnLButtonUp00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlObject",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"UINT",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlObject* self = (ControlObject*)  tolua_tousertype(tolua_S,1,0);
  UINT nFlags = *((UINT*)  tolua_tousertype(tolua_S,2,0));
  const int nX = ((const int)  tolua_tonumber(tolua_S,3,0));
  const int nY = ((const int)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'OnLButtonUp'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->OnLButtonUp(nFlags,nX,nY);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'OnLButtonUp'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: OnRButtonUp of class  ControlObject */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlObject_OnRButtonUp00
static int tolua_CompileToLua_ControlObject_OnRButtonUp00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlObject",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"UINT",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlObject* self = (ControlObject*)  tolua_tousertype(tolua_S,1,0);
  UINT nFlags = *((UINT*)  tolua_tousertype(tolua_S,2,0));
  const int nX = ((const int)  tolua_tonumber(tolua_S,3,0));
  const int nY = ((const int)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'OnRButtonUp'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->OnRButtonUp(nFlags,nX,nY);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'OnRButtonUp'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: OnLButtonDBClick of class  ControlObject */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlObject_OnLButtonDBClick00
static int tolua_CompileToLua_ControlObject_OnLButtonDBClick00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlObject",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"UINT",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlObject* self = (ControlObject*)  tolua_tousertype(tolua_S,1,0);
  UINT nFlags = *((UINT*)  tolua_tousertype(tolua_S,2,0));
  const int nX = ((const int)  tolua_tonumber(tolua_S,3,0));
  const int nY = ((const int)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'OnLButtonDBClick'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->OnLButtonDBClick(nFlags,nX,nY);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'OnLButtonDBClick'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: OnRButtonDBClick of class  ControlObject */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlObject_OnRButtonDBClick00
static int tolua_CompileToLua_ControlObject_OnRButtonDBClick00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlObject",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"UINT",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlObject* self = (ControlObject*)  tolua_tousertype(tolua_S,1,0);
  UINT nFlags = *((UINT*)  tolua_tousertype(tolua_S,2,0));
  const int nX = ((const int)  tolua_tonumber(tolua_S,3,0));
  const int nY = ((const int)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'OnRButtonDBClick'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->OnRButtonDBClick(nFlags,nX,nY);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'OnRButtonDBClick'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: OnKeyDown of class  ControlObject */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlObject_OnKeyDown00
static int tolua_CompileToLua_ControlObject_OnKeyDown00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlObject",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"UINT",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlObject* self = (ControlObject*)  tolua_tousertype(tolua_S,1,0);
  UINT nChar = *((UINT*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'OnKeyDown'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->OnKeyDown(nChar);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'OnKeyDown'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: OnKeyUp of class  ControlObject */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlObject_OnKeyUp00
static int tolua_CompileToLua_ControlObject_OnKeyUp00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlObject",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"UINT",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlObject* self = (ControlObject*)  tolua_tousertype(tolua_S,1,0);
  UINT nChar = *((UINT*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'OnKeyUp'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->OnKeyUp(nChar);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'OnKeyUp'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: OnChar of class  ControlObject */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlObject_OnChar00
static int tolua_CompileToLua_ControlObject_OnChar00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlObject",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"UINT",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlObject* self = (ControlObject*)  tolua_tousertype(tolua_S,1,0);
  UINT nChar = *((UINT*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'OnChar'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->OnChar(nChar);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'OnChar'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: IsLButtonDrag of class  ControlObject */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlObject_IsLButtonDrag00
static int tolua_CompileToLua_ControlObject_IsLButtonDrag00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlObject",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlObject* self = (ControlObject*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'IsLButtonDrag'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->IsLButtonDrag();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'IsLButtonDrag'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetRealRect of class  ControlObject */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlObject_GetRealRect00
static int tolua_CompileToLua_ControlObject_GetRealRect00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlObject",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"RECT",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlObject* self = (ControlObject*)  tolua_tousertype(tolua_S,1,0);
  OUT RECT* prc = ((OUT RECT*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetRealRect'",NULL);
#endif
  {
   self->GetRealRect(prc);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetRealRect'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetControlID of class  ControlObject */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlObject_GetControlID00
static int tolua_CompileToLua_ControlObject_GetControlID00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlObject",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlObject* self = (ControlObject*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetControlID'",NULL);
#endif
  {
   char* tolua_ret = (char*)  self->GetControlID();
   tolua_pushstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetControlID'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetControlType of class  ControlObject */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlObject_GetControlType00
static int tolua_CompileToLua_ControlObject_GetControlType00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlObject",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlObject* self = (ControlObject*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetControlType'",NULL);
#endif
  {
   int tolua_ret = (int)  self->GetControlType();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetControlType'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetFontSize of class  ControlObject */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlObject_GetFontSize00
static int tolua_CompileToLua_ControlObject_GetFontSize00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlObject",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlObject* self = (ControlObject*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetFontSize'",NULL);
#endif
  {
   int tolua_ret = (int)  self->GetFontSize();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetFontSize'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetFontIndex of class  ControlObject */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlObject_GetFontIndex00
static int tolua_CompileToLua_ControlObject_GetFontIndex00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlObject",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlObject* self = (ControlObject*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetFontIndex'",NULL);
#endif
  {
   int tolua_ret = (int)  self->GetFontIndex();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetFontIndex'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetFont of class  ControlObject */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlObject_SetFont00
static int tolua_CompileToLua_ControlObject_SetFont00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlObject",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"const ControlObject",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlObject* self = (ControlObject*)  tolua_tousertype(tolua_S,1,0);
  const ControlObject* pSrc = ((const ControlObject*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetFont'",NULL);
#endif
  {
   self->SetFont(pSrc);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetFont'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetFontColor of class  ControlObject */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlObject_GetFontColor00
static int tolua_CompileToLua_ControlObject_GetFontColor00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlObject",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlObject* self = (ControlObject*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetFontColor'",NULL);
#endif
  {
   COLORREF tolua_ret = (COLORREF)  self->GetFontColor();
   {
#ifdef __cplusplus
    void* tolua_obj = new COLORREF(tolua_ret);
    tolua_pushusertype_and_takeownership(tolua_S,tolua_obj,"COLORREF");
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(COLORREF));
    tolua_pushusertype_and_takeownership(tolua_S,tolua_obj,"COLORREF");
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetFontColor'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetWidth of class  ControlObject */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlObject_GetWidth00
static int tolua_CompileToLua_ControlObject_GetWidth00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlObject",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlObject* self = (ControlObject*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetWidth'",NULL);
#endif
  {
   int tolua_ret = (int)  self->GetWidth();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetWidth'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetHeight of class  ControlObject */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlObject_GetHeight00
static int tolua_CompileToLua_ControlObject_GetHeight00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlObject",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlObject* self = (ControlObject*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetHeight'",NULL);
#endif
  {
   int tolua_ret = (int)  self->GetHeight();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetHeight'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetPic of class  ControlObject */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlObject_SetPic00
static int tolua_CompileToLua_ControlObject_SetPic00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlObject",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"S_BaseData::S_Pic",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,3,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlObject* self = (ControlObject*)  tolua_tousertype(tolua_S,1,0);
  IN S_BaseData::S_Pic* pPic = ((IN S_BaseData::S_Pic*)  tolua_tousertype(tolua_S,2,0));
  bool bCoverData = ((bool)  tolua_toboolean(tolua_S,3,false));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetPic'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->SetPic(pPic,bCoverData);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetPic'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetPos of class  ControlObject */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlObject_SetPos00
static int tolua_CompileToLua_ControlObject_SetPos00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlObject",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isboolean(tolua_S,4,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlObject* self = (ControlObject*)  tolua_tousertype(tolua_S,1,0);
  const int nX = ((const int)  tolua_tonumber(tolua_S,2,0));
  const int nY = ((const int)  tolua_tonumber(tolua_S,3,0));
  bool bReal = ((bool)  tolua_toboolean(tolua_S,4,true));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetPos'",NULL);
#endif
  {
   self->SetPos(nX,nY,bReal);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetPos'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetXPos of class  ControlObject */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlObject_SetXPos00
static int tolua_CompileToLua_ControlObject_SetXPos00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlObject",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlObject* self = (ControlObject*)  tolua_tousertype(tolua_S,1,0);
  const int nX = ((const int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetXPos'",NULL);
#endif
  {
   self->SetXPos(nX);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetXPos'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetYPos of class  ControlObject */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlObject_SetYPos00
static int tolua_CompileToLua_ControlObject_SetYPos00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlObject",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlObject* self = (ControlObject*)  tolua_tousertype(tolua_S,1,0);
  const int nY = ((const int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetYPos'",NULL);
#endif
  {
   self->SetYPos(nY);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetYPos'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetWidth of class  ControlObject */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlObject_SetWidth00
static int tolua_CompileToLua_ControlObject_SetWidth00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlObject",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlObject* self = (ControlObject*)  tolua_tousertype(tolua_S,1,0);
  const int nW = ((const int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetWidth'",NULL);
#endif
  {
   self->SetWidth(nW);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetWidth'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetHeight of class  ControlObject */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlObject_SetHeight00
static int tolua_CompileToLua_ControlObject_SetHeight00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlObject",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlObject* self = (ControlObject*)  tolua_tousertype(tolua_S,1,0);
  const int nH = ((const int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetHeight'",NULL);
#endif
  {
   self->SetHeight(nH);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetHeight'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetCovered of class  ControlObject */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlObject_SetCovered00
static int tolua_CompileToLua_ControlObject_SetCovered00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlObject",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlObject* self = (ControlObject*)  tolua_tousertype(tolua_S,1,0);
  const bool bCovered = ((const bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetCovered'",NULL);
#endif
  {
   self->SetCovered(bCovered);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetCovered'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: IsVisable of class  ControlObject */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlObject_IsVisable00
static int tolua_CompileToLua_ControlObject_IsVisable00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlObject",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlObject* self = (ControlObject*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'IsVisable'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->IsVisable();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'IsVisable'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: IsCovered of class  ControlObject */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlObject_IsCovered00
static int tolua_CompileToLua_ControlObject_IsCovered00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlObject",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlObject* self = (ControlObject*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'IsCovered'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->IsCovered();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'IsCovered'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: IsBeCovered of class  ControlObject */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlObject_IsBeCovered00
static int tolua_CompileToLua_ControlObject_IsBeCovered00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlObject",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"ControlObject",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlObject* self = (ControlObject*)  tolua_tousertype(tolua_S,1,0);
  IN ControlObject* pCover = ((IN ControlObject*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'IsBeCovered'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->IsBeCovered(pCover);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'IsBeCovered'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetActivate of class  ControlObject */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlObject_SetActivate00
static int tolua_CompileToLua_ControlObject_SetActivate00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlObject",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlObject* self = (ControlObject*)  tolua_tousertype(tolua_S,1,0);
  const bool bActivate = ((const bool)  tolua_toboolean(tolua_S,2,true));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetActivate'",NULL);
#endif
  {
   self->SetActivate(bActivate);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetActivate'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: IsActivated of class  ControlObject */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlObject_IsActivated00
static int tolua_CompileToLua_ControlObject_IsActivated00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlObject",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlObject* self = (ControlObject*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'IsActivated'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->IsActivated();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'IsActivated'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: MoveTo of class  ControlObject */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlObject_MoveTo00
static int tolua_CompileToLua_ControlObject_MoveTo00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlObject",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlObject* self = (ControlObject*)  tolua_tousertype(tolua_S,1,0);
  const int nX = ((const int)  tolua_tonumber(tolua_S,2,0));
  const int nY = ((const int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'MoveTo'",NULL);
#endif
  {
   self->MoveTo(nX,nY);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'MoveTo'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetMsgHoldup of class  ControlObject */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlObject_SetMsgHoldup00
static int tolua_CompileToLua_ControlObject_SetMsgHoldup00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlObject",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlObject* self = (ControlObject*)  tolua_tousertype(tolua_S,1,0);
  const bool b = ((const bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetMsgHoldup'",NULL);
#endif
  {
   self->SetMsgHoldup(b);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetMsgHoldup'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: IsMsgHoldup of class  ControlObject */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlObject_IsMsgHoldup00
static int tolua_CompileToLua_ControlObject_IsMsgHoldup00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlObject",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlObject* self = (ControlObject*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'IsMsgHoldup'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->IsMsgHoldup();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'IsMsgHoldup'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetBackPicZValue of class  ControlObject */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlObject_SetBackPicZValue00
static int tolua_CompileToLua_ControlObject_SetBackPicZValue00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlObject",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlObject* self = (ControlObject*)  tolua_tousertype(tolua_S,1,0);
  const float fZ = ((const float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetBackPicZValue'",NULL);
#endif
  {
   self->SetBackPicZValue(fZ);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetBackPicZValue'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetBackColor of class  ControlObject */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlObject_SetBackColor00
static int tolua_CompileToLua_ControlObject_SetBackColor00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlObject",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"D3DCOLOR",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,3,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlObject* self = (ControlObject*)  tolua_tousertype(tolua_S,1,0);
  D3DCOLOR col = *((D3DCOLOR*)  tolua_tousertype(tolua_S,2,0));
  bool bFrame = ((bool)  tolua_toboolean(tolua_S,3,false));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetBackColor'",NULL);
#endif
  {
   self->SetBackColor(col,bFrame);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetBackColor'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetBackColor of class  ControlObject */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlObject_GetBackColor00
static int tolua_CompileToLua_ControlObject_GetBackColor00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlObject",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlObject* self = (ControlObject*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetBackColor'",NULL);
#endif
  {
   D3DCOLOR tolua_ret = (D3DCOLOR)  self->GetBackColor();
   {
#ifdef __cplusplus
    void* tolua_obj = new D3DCOLOR(tolua_ret);
    tolua_pushusertype_and_takeownership(tolua_S,tolua_obj,"D3DCOLOR");
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(D3DCOLOR));
    tolua_pushusertype_and_takeownership(tolua_S,tolua_obj,"D3DCOLOR");
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetBackColor'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetBlendColor of class  ControlObject */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlObject_SetBlendColor00
static int tolua_CompileToLua_ControlObject_SetBlendColor00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlObject",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlObject* self = (ControlObject*)  tolua_tousertype(tolua_S,1,0);
  int col = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetBlendColor'",NULL);
#endif
  {
   self->SetBlendColor(col);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetBlendColor'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetBlendColor of class  ControlObject */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlObject_GetBlendColor00
static int tolua_CompileToLua_ControlObject_GetBlendColor00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlObject",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlObject* self = (ControlObject*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetBlendColor'",NULL);
#endif
  {
   int tolua_ret = (int)  self->GetBlendColor();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetBlendColor'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: PlaySound of class  ControlObject */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlObject_PlaySound00
static int tolua_CompileToLua_ControlObject_PlaySound00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlObject",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlObject* self = (ControlObject*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'PlaySound'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->PlaySound();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'PlaySound'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetFadeInval of class  ControlObject */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlObject_SetFadeInval00
static int tolua_CompileToLua_ControlObject_SetFadeInval00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlObject",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlObject* self = (ControlObject*)  tolua_tousertype(tolua_S,1,0);
  bool bInval = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetFadeInval'",NULL);
#endif
  {
   self->SetFadeInval(bInval);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetFadeInval'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: IsFadeInval of class  ControlObject */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlObject_IsFadeInval00
static int tolua_CompileToLua_ControlObject_IsFadeInval00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlObject",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlObject* self = (ControlObject*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'IsFadeInval'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->IsFadeInval();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'IsFadeInval'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetMaxMinFade of class  ControlObject */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlObject_SetMaxMinFade00
static int tolua_CompileToLua_ControlObject_SetMaxMinFade00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlObject",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlObject* self = (ControlObject*)  tolua_tousertype(tolua_S,1,0);
  const int nMaxFade = ((const int)  tolua_tonumber(tolua_S,2,0));
  const int nMinFade = ((const int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetMaxMinFade'",NULL);
#endif
  {
   self->SetMaxMinFade(nMaxFade,nMinFade);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetMaxMinFade'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetPicName of class  ControlObject */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlObject_SetPicName00
static int tolua_CompileToLua_ControlObject_SetPicName00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlObject",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlObject* self = (ControlObject*)  tolua_tousertype(tolua_S,1,0);
  const char* szPath = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetPicName'",NULL);
#endif
  {
   self->SetPicName(szPath);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetPicName'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetPic of class  ControlObject */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlObject_GetPic00
static int tolua_CompileToLua_ControlObject_GetPic00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlObject",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlObject* self = (ControlObject*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetPic'",NULL);
#endif
  {
   S_BaseData::S_Pic* tolua_ret = (S_BaseData::S_Pic*)  self->GetPic();
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"S_BaseData::S_Pic");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetPic'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetData of class  ControlObject */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlObject_GetData00
static int tolua_CompileToLua_ControlObject_GetData00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlObject",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlObject* self = (ControlObject*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetData'",NULL);
#endif
  {
   S_BaseData* tolua_ret = (S_BaseData*)  self->GetData();
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"S_BaseData");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetData'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetAllVisableDlg of class  ControlObject */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlObject_SetAllVisableDlg00
static int tolua_CompileToLua_ControlObject_SetAllVisableDlg00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlObject",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlObject* self = (ControlObject*)  tolua_tousertype(tolua_S,1,0);
  bool bAllVisable = ((bool)  tolua_toboolean(tolua_S,2,true));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetAllVisableDlg'",NULL);
#endif
  {
   self->SetAllVisableDlg(bAllVisable);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetAllVisableDlg'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetAllVisableDlg of class  ControlObject */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlObject_GetAllVisableDlg00
static int tolua_CompileToLua_ControlObject_GetAllVisableDlg00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const ControlObject",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const ControlObject* self = (const ControlObject*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetAllVisableDlg'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->GetAllVisableDlg();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetAllVisableDlg'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: BitBlt of class  ControlObject */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlObject_BitBlt00
static int tolua_CompileToLua_ControlObject_BitBlt00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlObject",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,6,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,7,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,8,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,9,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,10,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,11,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,12,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,13,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,14,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlObject* self = (ControlObject*)  tolua_tousertype(tolua_S,1,0);
  IN OUT int pPicId = ((IN OUT int)  tolua_tonumber(tolua_S,2,0));
  IN  const char* szPicName = ((IN  const char*)  tolua_tostring(tolua_S,3,0));
  const int nDstX = ((const int)  tolua_tonumber(tolua_S,4,0));
  const int nDstY = ((const int)  tolua_tonumber(tolua_S,5,0));
  const int nDstWidth = ((const int)  tolua_tonumber(tolua_S,6,0));
  const int nDstHeight = ((const int)  tolua_tonumber(tolua_S,7,0));
  const int nSrcX = ((const int)  tolua_tonumber(tolua_S,8,0));
  const int nSrcY = ((const int)  tolua_tonumber(tolua_S,9,0));
  const int nSrcWidth = ((const int)  tolua_tonumber(tolua_S,10,0));
  const int nSrcHeight = ((const int)  tolua_tonumber(tolua_S,11,0));
  const int nDrawMode = ((const int)  tolua_tonumber(tolua_S,12,0));
  const int col = ((const int)  tolua_tonumber(tolua_S,13,0xffffffff));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'BitBlt'",NULL);
#endif
  {
   self->BitBlt(&pPicId,szPicName,nDstX,nDstY,nDstWidth,nDstHeight,nSrcX,nSrcY,nSrcWidth,nSrcHeight,nDrawMode,col);
   tolua_pushnumber(tolua_S,(lua_Number)pPicId);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'BitBlt'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetFatherRect of class  ControlObject */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlObject_GetFatherRect00
static int tolua_CompileToLua_ControlObject_GetFatherRect00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlObject",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"RECT",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlObject* self = (ControlObject*)  tolua_tousertype(tolua_S,1,0);
  OUT RECT* prc = ((OUT RECT*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetFatherRect'",NULL);
#endif
  {
   self->GetFatherRect(prc);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetFatherRect'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  ControlObject */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlObject_new00
static int tolua_CompileToLua_ControlObject_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"ControlObject",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   ControlObject* tolua_ret = (ControlObject*)  new ControlObject();
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"ControlObject");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  ControlObject */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlObject_new00_local
static int tolua_CompileToLua_ControlObject_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"ControlObject",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   ControlObject* tolua_ret = (ControlObject*)  new ControlObject();
   tolua_pushusertype_and_takeownership(tolua_S,(void *)tolua_ret,"ControlObject");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: delete of class  ControlObject */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlObject_delete00
static int tolua_CompileToLua_ControlObject_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlObject",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlObject* self = (ControlObject*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'",NULL);
#endif
  delete self;
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Render of class  ControlCheckBox */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlCheckBox_Render00
static int tolua_CompileToLua_ControlCheckBox_Render00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlCheckBox",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlCheckBox* self = (ControlCheckBox*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Render'",NULL);
#endif
  {
   self->Render();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Render'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: InitUIData of class  ControlCheckBox */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlCheckBox_InitUIData00
static int tolua_CompileToLua_ControlCheckBox_InitUIData00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlCheckBox",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"ControlObject",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"S_BaseData",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlCheckBox* self = (ControlCheckBox*)  tolua_tousertype(tolua_S,1,0);
  IN ControlObject* pFather = ((IN ControlObject*)  tolua_tousertype(tolua_S,2,0));
  IN S_BaseData* pData = ((IN S_BaseData*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'InitUIData'",NULL);
#endif
  {
   self->InitUIData(pFather,pData);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'InitUIData'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: OnLButtonDown of class  ControlCheckBox */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlCheckBox_OnLButtonDown00
static int tolua_CompileToLua_ControlCheckBox_OnLButtonDown00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlCheckBox",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"UINT",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlCheckBox* self = (ControlCheckBox*)  tolua_tousertype(tolua_S,1,0);
  UINT nFlags = *((UINT*)  tolua_tousertype(tolua_S,2,0));
  const int nX = ((const int)  tolua_tonumber(tolua_S,3,0));
  const int nY = ((const int)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'OnLButtonDown'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->OnLButtonDown(nFlags,nX,nY);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'OnLButtonDown'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: OnMouseMove of class  ControlCheckBox */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlCheckBox_OnMouseMove00
static int tolua_CompileToLua_ControlCheckBox_OnMouseMove00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlCheckBox",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"UINT",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlCheckBox* self = (ControlCheckBox*)  tolua_tousertype(tolua_S,1,0);
  UINT nFlags = *((UINT*)  tolua_tousertype(tolua_S,2,0));
  const int nX = ((const int)  tolua_tonumber(tolua_S,3,0));
  const int nY = ((const int)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'OnMouseMove'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->OnMouseMove(nFlags,nX,nY);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'OnMouseMove'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetCheckFun_2lua of class  ControlCheckBox */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlCheckBox_SetCheckFun_2lua00
static int tolua_CompileToLua_ControlCheckBox_SetCheckFun_2lua00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlCheckBox",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlCheckBox* self = (ControlCheckBox*)  tolua_tousertype(tolua_S,1,0);
  const char* luaTable = ((const char*)  tolua_tostring(tolua_S,2,0));
  const char* funName = ((const char*)  tolua_tostring(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetCheckFun_2lua'",NULL);
#endif
  {
   self->SetCheckFun_2lua(luaTable,funName);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetCheckFun_2lua'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: IsChecked of class  ControlCheckBox */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlCheckBox_IsChecked00
static int tolua_CompileToLua_ControlCheckBox_IsChecked00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlCheckBox",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlCheckBox* self = (ControlCheckBox*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'IsChecked'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->IsChecked();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'IsChecked'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetCheck of class  ControlCheckBox */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlCheckBox_SetCheck00
static int tolua_CompileToLua_ControlCheckBox_SetCheck00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlCheckBox",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlCheckBox* self = (ControlCheckBox*)  tolua_tousertype(tolua_S,1,0);
  const bool bCheck = ((const bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetCheck'",NULL);
#endif
  {
   self->SetCheck(bCheck);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetCheck'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetShowTip of class  ControlCheckBox */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlCheckBox_SetShowTip00
static int tolua_CompileToLua_ControlCheckBox_SetShowTip00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlCheckBox",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlCheckBox* self = (ControlCheckBox*)  tolua_tousertype(tolua_S,1,0);
  bool bShow = ((bool)  tolua_toboolean(tolua_S,2,true));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetShowTip'",NULL);
#endif
  {
   self->SetShowTip(bShow);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetShowTip'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetShowTip of class  ControlCheckBox */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlCheckBox_GetShowTip00
static int tolua_CompileToLua_ControlCheckBox_GetShowTip00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlCheckBox",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlCheckBox* self = (ControlCheckBox*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetShowTip'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->GetShowTip();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetShowTip'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetCaption of class  ControlCheckBox */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlCheckBox_SetCaption00
static int tolua_CompileToLua_ControlCheckBox_SetCaption00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlCheckBox",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlCheckBox* self = (ControlCheckBox*)  tolua_tousertype(tolua_S,1,0);
  const char* szText = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetCaption'",NULL);
#endif
  {
   self->SetCaption(szText);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetCaption'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: OnCheck of class  ControlCheckBox */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlCheckBox_OnCheck00
static int tolua_CompileToLua_ControlCheckBox_OnCheck00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlCheckBox",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlCheckBox* self = (ControlCheckBox*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'OnCheck'",NULL);
#endif
  {
   self->OnCheck();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'OnCheck'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  ControlCheckBox */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlCheckBox_new00
static int tolua_CompileToLua_ControlCheckBox_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"ControlCheckBox",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   ControlCheckBox* tolua_ret = (ControlCheckBox*)  new ControlCheckBox();
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"ControlCheckBox");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  ControlCheckBox */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlCheckBox_new00_local
static int tolua_CompileToLua_ControlCheckBox_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"ControlCheckBox",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   ControlCheckBox* tolua_ret = (ControlCheckBox*)  new ControlCheckBox();
   tolua_pushusertype_and_takeownership(tolua_S,(void *)tolua_ret,"ControlCheckBox");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: delete of class  ControlCheckBox */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlCheckBox_delete00
static int tolua_CompileToLua_ControlCheckBox_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlCheckBox",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlCheckBox* self = (ControlCheckBox*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'",NULL);
#endif
  delete self;
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Render of class  ControlComboBox */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlComboBox_Render00
static int tolua_CompileToLua_ControlComboBox_Render00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlComboBox",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlComboBox* self = (ControlComboBox*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Render'",NULL);
#endif
  {
   self->Render();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Render'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: InitUIData of class  ControlComboBox */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlComboBox_InitUIData00
static int tolua_CompileToLua_ControlComboBox_InitUIData00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlComboBox",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"ControlObject",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"S_BaseData",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlComboBox* self = (ControlComboBox*)  tolua_tousertype(tolua_S,1,0);
  IN ControlObject* pFather = ((IN ControlObject*)  tolua_tousertype(tolua_S,2,0));
  IN S_BaseData* pData = ((IN S_BaseData*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'InitUIData'",NULL);
#endif
  {
   self->InitUIData(pFather,pData);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'InitUIData'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: OnMouseMove of class  ControlComboBox */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlComboBox_OnMouseMove00
static int tolua_CompileToLua_ControlComboBox_OnMouseMove00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlComboBox",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"UINT",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlComboBox* self = (ControlComboBox*)  tolua_tousertype(tolua_S,1,0);
  UINT nFlags = *((UINT*)  tolua_tousertype(tolua_S,2,0));
  const int nX = ((const int)  tolua_tonumber(tolua_S,3,0));
  const int nY = ((const int)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'OnMouseMove'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->OnMouseMove(nFlags,nX,nY);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'OnMouseMove'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: OnMouseWheel of class  ControlComboBox */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlComboBox_OnMouseWheel00
static int tolua_CompileToLua_ControlComboBox_OnMouseWheel00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlComboBox",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlComboBox* self = (ControlComboBox*)  tolua_tousertype(tolua_S,1,0);
  bool bUp = ((bool)  tolua_toboolean(tolua_S,2,0));
  const int nX = ((const int)  tolua_tonumber(tolua_S,3,0));
  const int nY = ((const int)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'OnMouseWheel'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->OnMouseWheel(bUp,nX,nY);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'OnMouseWheel'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: OnLButtonDown of class  ControlComboBox */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlComboBox_OnLButtonDown00
static int tolua_CompileToLua_ControlComboBox_OnLButtonDown00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlComboBox",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"UINT",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlComboBox* self = (ControlComboBox*)  tolua_tousertype(tolua_S,1,0);
  UINT nFlags = *((UINT*)  tolua_tousertype(tolua_S,2,0));
  const int nX = ((const int)  tolua_tonumber(tolua_S,3,0));
  const int nY = ((const int)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'OnLButtonDown'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->OnLButtonDown(nFlags,nX,nY);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'OnLButtonDown'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: OnLButtonUp of class  ControlComboBox */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlComboBox_OnLButtonUp00
static int tolua_CompileToLua_ControlComboBox_OnLButtonUp00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlComboBox",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"UINT",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlComboBox* self = (ControlComboBox*)  tolua_tousertype(tolua_S,1,0);
  UINT nFlags = *((UINT*)  tolua_tousertype(tolua_S,2,0));
  const int nX = ((const int)  tolua_tonumber(tolua_S,3,0));
  const int nY = ((const int)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'OnLButtonUp'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->OnLButtonUp(nFlags,nX,nY);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'OnLButtonUp'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: OnChar of class  ControlComboBox */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlComboBox_OnChar00
static int tolua_CompileToLua_ControlComboBox_OnChar00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlComboBox",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"UINT",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlComboBox* self = (ControlComboBox*)  tolua_tousertype(tolua_S,1,0);
  UINT nChar = *((UINT*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'OnChar'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->OnChar(nChar);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'OnChar'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetListBox of class  ControlComboBox */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlComboBox_GetListBox00
static int tolua_CompileToLua_ControlComboBox_GetListBox00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlComboBox",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlComboBox* self = (ControlComboBox*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetListBox'",NULL);
#endif
  {
   ControlList& tolua_ret = (ControlList&)  self->GetListBox();
   tolua_pushusertype(tolua_S,(void*)&tolua_ret,"ControlList");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetListBox'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetEditInput of class  ControlComboBox */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlComboBox_GetEditInput00
static int tolua_CompileToLua_ControlComboBox_GetEditInput00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlComboBox",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlComboBox* self = (ControlComboBox*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetEditInput'",NULL);
#endif
  {
   ControlEdit& tolua_ret = (ControlEdit&)  self->GetEditInput();
   tolua_pushusertype(tolua_S,(void*)&tolua_ret,"ControlEdit");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetEditInput'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetChangeFun_2lua of class  ControlComboBox */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlComboBox_SetChangeFun_2lua00
static int tolua_CompileToLua_ControlComboBox_SetChangeFun_2lua00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlComboBox",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlComboBox* self = (ControlComboBox*)  tolua_tousertype(tolua_S,1,0);
  const char* luaTable = ((const char*)  tolua_tostring(tolua_S,2,0));
  const char* funName = ((const char*)  tolua_tostring(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetChangeFun_2lua'",NULL);
#endif
  {
   self->SetChangeFun_2lua(luaTable,funName);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetChangeFun_2lua'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetShowListFun_2lua of class  ControlComboBox */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlComboBox_SetShowListFun_2lua00
static int tolua_CompileToLua_ControlComboBox_SetShowListFun_2lua00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlComboBox",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlComboBox* self = (ControlComboBox*)  tolua_tousertype(tolua_S,1,0);
  const char* luaTable = ((const char*)  tolua_tostring(tolua_S,2,0));
  const char* funName = ((const char*)  tolua_tostring(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetShowListFun_2lua'",NULL);
#endif
  {
   self->SetShowListFun_2lua(luaTable,funName);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetShowListFun_2lua'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: OnChange of class  ControlComboBox */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlComboBox_OnChange00
static int tolua_CompileToLua_ControlComboBox_OnChange00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlComboBox",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlComboBox* self = (ControlComboBox*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'OnChange'",NULL);
#endif
  {
   self->OnChange();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'OnChange'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: OnShowList of class  ControlComboBox */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlComboBox_OnShowList00
static int tolua_CompileToLua_ControlComboBox_OnShowList00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlComboBox",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlComboBox* self = (ControlComboBox*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'OnShowList'",NULL);
#endif
  {
   self->OnShowList();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'OnShowList'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  ControlComboBox */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlComboBox_new00
static int tolua_CompileToLua_ControlComboBox_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"ControlComboBox",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   ControlComboBox* tolua_ret = (ControlComboBox*)  new ControlComboBox();
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"ControlComboBox");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  ControlComboBox */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlComboBox_new00_local
static int tolua_CompileToLua_ControlComboBox_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"ControlComboBox",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   ControlComboBox* tolua_ret = (ControlComboBox*)  new ControlComboBox();
   tolua_pushusertype_and_takeownership(tolua_S,(void *)tolua_ret,"ControlComboBox");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: delete of class  ControlComboBox */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlComboBox_delete00
static int tolua_CompileToLua_ControlComboBox_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlComboBox",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlComboBox* self = (ControlComboBox*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'",NULL);
#endif
  delete self;
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: InitUIData of class  ControlEdit */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlEdit_InitUIData00
static int tolua_CompileToLua_ControlEdit_InitUIData00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlEdit",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"ControlObject",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"S_BaseData",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlEdit* self = (ControlEdit*)  tolua_tousertype(tolua_S,1,0);
  IN ControlObject* pFather = ((IN ControlObject*)  tolua_tousertype(tolua_S,2,0));
  IN S_BaseData* pData = ((IN S_BaseData*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'InitUIData'",NULL);
#endif
  {
   self->InitUIData(pFather,pData);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'InitUIData'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Render of class  ControlEdit */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlEdit_Render00
static int tolua_CompileToLua_ControlEdit_Render00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlEdit",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlEdit* self = (ControlEdit*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Render'",NULL);
#endif
  {
   self->Render();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Render'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Create of class  ControlEdit */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlEdit_Create00
static int tolua_CompileToLua_ControlEdit_Create00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlEdit",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"const RECT",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,1,&tolua_err) ||
     !tolua_isboolean(tolua_S,4,1,&tolua_err) ||
     !tolua_isboolean(tolua_S,5,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,6,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,7,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlEdit* self = (ControlEdit*)  tolua_tousertype(tolua_S,1,0);
  IN  const RECT* pRect = ((IN  const RECT*)  tolua_tousertype(tolua_S,2,0));
  const int colText = ((const int)  tolua_tonumber(tolua_S,3,0xffffffff));
  const bool bMultiline = ((const bool)  tolua_toboolean(tolua_S,4,true));
  const bool bReadOnly = ((const bool)  tolua_toboolean(tolua_S,5,true));
  const int colBack = ((const int)  tolua_tonumber(tolua_S,6,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Create'",NULL);
#endif
  {
   self->Create(pRect,colText,bMultiline,bReadOnly,colBack);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Create'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: OnMouseMove of class  ControlEdit */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlEdit_OnMouseMove00
static int tolua_CompileToLua_ControlEdit_OnMouseMove00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlEdit",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"UINT",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlEdit* self = (ControlEdit*)  tolua_tousertype(tolua_S,1,0);
  UINT nFlags = *((UINT*)  tolua_tousertype(tolua_S,2,0));
  const int nX = ((const int)  tolua_tonumber(tolua_S,3,0));
  const int nY = ((const int)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'OnMouseMove'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->OnMouseMove(nFlags,nX,nY);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'OnMouseMove'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: OnLButtonDown of class  ControlEdit */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlEdit_OnLButtonDown00
static int tolua_CompileToLua_ControlEdit_OnLButtonDown00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlEdit",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"UINT",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlEdit* self = (ControlEdit*)  tolua_tousertype(tolua_S,1,0);
  UINT nFlags = *((UINT*)  tolua_tousertype(tolua_S,2,0));
  const int nX = ((const int)  tolua_tonumber(tolua_S,3,0));
  const int nY = ((const int)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'OnLButtonDown'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->OnLButtonDown(nFlags,nX,nY);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'OnLButtonDown'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: OnLButtonUp of class  ControlEdit */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlEdit_OnLButtonUp00
static int tolua_CompileToLua_ControlEdit_OnLButtonUp00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlEdit",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"UINT",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlEdit* self = (ControlEdit*)  tolua_tousertype(tolua_S,1,0);
  UINT nFlags = *((UINT*)  tolua_tousertype(tolua_S,2,0));
  const int nX = ((const int)  tolua_tonumber(tolua_S,3,0));
  const int nY = ((const int)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'OnLButtonUp'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->OnLButtonUp(nFlags,nX,nY);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'OnLButtonUp'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: OnLButtonDBClick of class  ControlEdit */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlEdit_OnLButtonDBClick00
static int tolua_CompileToLua_ControlEdit_OnLButtonDBClick00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlEdit",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"UINT",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlEdit* self = (ControlEdit*)  tolua_tousertype(tolua_S,1,0);
  UINT nFlags = *((UINT*)  tolua_tousertype(tolua_S,2,0));
  const int nX = ((const int)  tolua_tonumber(tolua_S,3,0));
  const int nY = ((const int)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'OnLButtonDBClick'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->OnLButtonDBClick(nFlags,nX,nY);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'OnLButtonDBClick'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: OnChar of class  ControlEdit */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlEdit_OnChar00
static int tolua_CompileToLua_ControlEdit_OnChar00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlEdit",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"UINT",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlEdit* self = (ControlEdit*)  tolua_tousertype(tolua_S,1,0);
  UINT nChar = *((UINT*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'OnChar'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->OnChar(nChar);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'OnChar'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: OnKeyDown of class  ControlEdit */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlEdit_OnKeyDown00
static int tolua_CompileToLua_ControlEdit_OnKeyDown00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlEdit",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"UINT",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlEdit* self = (ControlEdit*)  tolua_tousertype(tolua_S,1,0);
  UINT nChar = *((UINT*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'OnKeyDown'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->OnKeyDown(nChar);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'OnKeyDown'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetText of class  ControlEdit */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlEdit_SetText00
static int tolua_CompileToLua_ControlEdit_SetText00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlEdit",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlEdit* self = (ControlEdit*)  tolua_tousertype(tolua_S,1,0);
  const std::string strText = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetText'",NULL);
#endif
  {
   self->SetText(strText);
   tolua_pushcppstring(tolua_S,(const char*)strText);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetText'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetText of class  ControlEdit */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlEdit_SetText01
static int tolua_CompileToLua_ControlEdit_SetText01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlEdit",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"const CHAR",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  ControlEdit* self = (ControlEdit*)  tolua_tousertype(tolua_S,1,0);
  const CHAR* pszText = ((const CHAR*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetText'",NULL);
#endif
  {
   self->SetText(pszText);
  }
 }
 return 0;
tolua_lerror:
 return tolua_CompileToLua_ControlEdit_SetText00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetText of class  ControlEdit */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlEdit_SetText02
static int tolua_CompileToLua_ControlEdit_SetText02(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlEdit",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  ControlEdit* self = (ControlEdit*)  tolua_tousertype(tolua_S,1,0);
  const int n = ((const int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetText'",NULL);
#endif
  {
   self->SetText(n);
  }
 }
 return 0;
tolua_lerror:
 return tolua_CompileToLua_ControlEdit_SetText01(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetTextW of class  ControlEdit */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlEdit_SetTextW00
static int tolua_CompileToLua_ControlEdit_SetTextW00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlEdit",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"const WCHAR",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlEdit* self = (ControlEdit*)  tolua_tousertype(tolua_S,1,0);
  const WCHAR* pwText = ((const WCHAR*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetTextW'",NULL);
#endif
  {
   self->SetTextW(pwText);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetTextW'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetText of class  ControlEdit */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlEdit_GetText00
static int tolua_CompileToLua_ControlEdit_GetText00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlEdit",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlEdit* self = (ControlEdit*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetText'",NULL);
#endif
  {
   const CHAR* tolua_ret = (const CHAR*)  self->GetText();
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"const CHAR");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetText'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetTextW of class  ControlEdit */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlEdit_GetTextW00
static int tolua_CompileToLua_ControlEdit_GetTextW00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlEdit",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlEdit* self = (ControlEdit*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetTextW'",NULL);
#endif
  {
   const WCHAR* tolua_ret = (const WCHAR*)  self->GetTextW();
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"const WCHAR");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetTextW'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: addChar of class  ControlEdit */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlEdit_addChar00
static int tolua_CompileToLua_ControlEdit_addChar00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlEdit",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"WCHAR",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlEdit* self = (ControlEdit*)  tolua_tousertype(tolua_S,1,0);
  WCHAR wChar = *((WCHAR*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'addChar'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->addChar(wChar);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'addChar'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: DelByte of class  ControlEdit */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlEdit_DelByte00
static int tolua_CompileToLua_ControlEdit_DelByte00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlEdit",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlEdit* self = (ControlEdit*)  tolua_tousertype(tolua_S,1,0);
  bool bBack = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'DelByte'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->DelByte(bBack);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'DelByte'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: addText of class  ControlEdit */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlEdit_addText00
static int tolua_CompileToLua_ControlEdit_addText00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlEdit",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlEdit* self = (ControlEdit*)  tolua_tousertype(tolua_S,1,0);
  const char* text = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'addText'",NULL);
#endif
  {
   self->addText(text);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'addText'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetEnterFun_2lua of class  ControlEdit */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlEdit_SetEnterFun_2lua00
static int tolua_CompileToLua_ControlEdit_SetEnterFun_2lua00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlEdit",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlEdit* self = (ControlEdit*)  tolua_tousertype(tolua_S,1,0);
  const char* luaTable = ((const char*)  tolua_tostring(tolua_S,2,0));
  const char* funName = ((const char*)  tolua_tostring(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetEnterFun_2lua'",NULL);
#endif
  {
   self->SetEnterFun_2lua(luaTable,funName);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetEnterFun_2lua'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetTabFun_2lua of class  ControlEdit */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlEdit_SetTabFun_2lua00
static int tolua_CompileToLua_ControlEdit_SetTabFun_2lua00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlEdit",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlEdit* self = (ControlEdit*)  tolua_tousertype(tolua_S,1,0);
  const char* luaTable = ((const char*)  tolua_tostring(tolua_S,2,0));
  const char* funName = ((const char*)  tolua_tostring(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetTabFun_2lua'",NULL);
#endif
  {
   self->SetTabFun_2lua(luaTable,funName);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetTabFun_2lua'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetLBtnDownFun_2lua of class  ControlEdit */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlEdit_SetLBtnDownFun_2lua00
static int tolua_CompileToLua_ControlEdit_SetLBtnDownFun_2lua00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlEdit",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlEdit* self = (ControlEdit*)  tolua_tousertype(tolua_S,1,0);
  const char* luaTable = ((const char*)  tolua_tostring(tolua_S,2,0));
  const char* funName = ((const char*)  tolua_tostring(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetLBtnDownFun_2lua'",NULL);
#endif
  {
   self->SetLBtnDownFun_2lua(luaTable,funName);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetLBtnDownFun_2lua'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetLBtnUpFun_2lua of class  ControlEdit */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlEdit_SetLBtnUpFun_2lua00
static int tolua_CompileToLua_ControlEdit_SetLBtnUpFun_2lua00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlEdit",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlEdit* self = (ControlEdit*)  tolua_tousertype(tolua_S,1,0);
  const char* luaTable = ((const char*)  tolua_tostring(tolua_S,2,0));
  const char* funName = ((const char*)  tolua_tostring(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetLBtnUpFun_2lua'",NULL);
#endif
  {
   self->SetLBtnUpFun_2lua(luaTable,funName);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetLBtnUpFun_2lua'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetDelByteFun_2lua of class  ControlEdit */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlEdit_SetDelByteFun_2lua00
static int tolua_CompileToLua_ControlEdit_SetDelByteFun_2lua00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlEdit",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlEdit* self = (ControlEdit*)  tolua_tousertype(tolua_S,1,0);
  const char* luaTable = ((const char*)  tolua_tostring(tolua_S,2,0));
  const char* funName = ((const char*)  tolua_tostring(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetDelByteFun_2lua'",NULL);
#endif
  {
   self->SetDelByteFun_2lua(luaTable,funName);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetDelByteFun_2lua'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: IsReadOnly of class  ControlEdit */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlEdit_IsReadOnly00
static int tolua_CompileToLua_ControlEdit_IsReadOnly00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlEdit",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlEdit* self = (ControlEdit*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'IsReadOnly'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->IsReadOnly();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'IsReadOnly'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetIsNumber of class  ControlEdit */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlEdit_SetIsNumber00
static int tolua_CompileToLua_ControlEdit_SetIsNumber00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlEdit",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlEdit* self = (ControlEdit*)  tolua_tousertype(tolua_S,1,0);
  const bool b = ((const bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetIsNumber'",NULL);
#endif
  {
   self->SetIsNumber(b);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetIsNumber'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetMaxLength of class  ControlEdit */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlEdit_SetMaxLength00
static int tolua_CompileToLua_ControlEdit_SetMaxLength00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlEdit",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlEdit* self = (ControlEdit*)  tolua_tousertype(tolua_S,1,0);
  const int n = ((const int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetMaxLength'",NULL);
#endif
  {
   self->SetMaxLength(n);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetMaxLength'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetReadOnly of class  ControlEdit */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlEdit_SetReadOnly00
static int tolua_CompileToLua_ControlEdit_SetReadOnly00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlEdit",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlEdit* self = (ControlEdit*)  tolua_tousertype(tolua_S,1,0);
  const bool b = ((const bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetReadOnly'",NULL);
#endif
  {
   self->SetReadOnly(b);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetReadOnly'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetIsPassword of class  ControlEdit */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlEdit_SetIsPassword00
static int tolua_CompileToLua_ControlEdit_SetIsPassword00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlEdit",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlEdit* self = (ControlEdit*)  tolua_tousertype(tolua_S,1,0);
  bool b = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetIsPassword'",NULL);
#endif
  {
   self->SetIsPassword(b);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetIsPassword'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: IsPassword of class  ControlEdit */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlEdit_IsPassword00
static int tolua_CompileToLua_ControlEdit_IsPassword00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlEdit",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlEdit* self = (ControlEdit*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'IsPassword'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->IsPassword();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'IsPassword'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setNoPitchOn of class  ControlEdit */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlEdit_setNoPitchOn00
static int tolua_CompileToLua_ControlEdit_setNoPitchOn00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlEdit",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlEdit* self = (ControlEdit*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setNoPitchOn'",NULL);
#endif
  {
   self->setNoPitchOn();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setNoPitchOn'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetMaxCnt of class  ControlEdit */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlEdit_SetMaxCnt00
static int tolua_CompileToLua_ControlEdit_SetMaxCnt00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlEdit",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlEdit* self = (ControlEdit*)  tolua_tousertype(tolua_S,1,0);
  int nMax = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetMaxCnt'",NULL);
#endif
  {
   self->SetMaxCnt(nMax);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetMaxCnt'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setDefaultColor of class  ControlEdit */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlEdit_setDefaultColor00
static int tolua_CompileToLua_ControlEdit_setDefaultColor00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlEdit",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"D3DCOLOR",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlEdit* self = (ControlEdit*)  tolua_tousertype(tolua_S,1,0);
  D3DCOLOR color = *((D3DCOLOR*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setDefaultColor'",NULL);
#endif
  {
   self->setDefaultColor(color);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setDefaultColor'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetCurIndex of class  ControlEdit */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlEdit_SetCurIndex00
static int tolua_CompileToLua_ControlEdit_SetCurIndex00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlEdit",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlEdit* self = (ControlEdit*)  tolua_tousertype(tolua_S,1,0);
  int nIndex = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetCurIndex'",NULL);
#endif
  {
   self->SetCurIndex(nIndex);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetCurIndex'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: CopyToClipboard of class  ControlEdit */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlEdit_CopyToClipboard00
static int tolua_CompileToLua_ControlEdit_CopyToClipboard00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlEdit",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlEdit* self = (ControlEdit*)  tolua_tousertype(tolua_S,1,0);
  const char* szText = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'CopyToClipboard'",NULL);
#endif
  {
   self->CopyToClipboard(szText);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'CopyToClipboard'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetTextFromClipboard of class  ControlEdit */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlEdit_GetTextFromClipboard00
static int tolua_CompileToLua_ControlEdit_GetTextFromClipboard00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlEdit",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlEdit* self = (ControlEdit*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetTextFromClipboard'",NULL);
#endif
  {
   char* tolua_ret = (char*)  self->GetTextFromClipboard();
   tolua_pushstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetTextFromClipboard'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: DataChanged of class  ControlEdit */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlEdit_DataChanged00
static int tolua_CompileToLua_ControlEdit_DataChanged00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlEdit",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlEdit* self = (ControlEdit*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'DataChanged'",NULL);
#endif
  {
   self->DataChanged();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'DataChanged'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: CPtoX of class  ControlEdit */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlEdit_CPtoX00
static int tolua_CompileToLua_ControlEdit_CPtoX00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlEdit",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"BOOL",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlEdit* self = (ControlEdit*)  tolua_tousertype(tolua_S,1,0);
  int nCP = ((int)  tolua_tonumber(tolua_S,2,0));
  BOOL bTrail = *((BOOL*)  tolua_tousertype(tolua_S,3,0));
  int pX = ((int)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'CPtoX'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->CPtoX(nCP,bTrail,&pX);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
   tolua_pushnumber(tolua_S,(lua_Number)pX);
  }
 }
 return 2;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'CPtoX'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: XtoCP of class  ControlEdit */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlEdit_XtoCP00
static int tolua_CompileToLua_ControlEdit_XtoCP00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlEdit",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlEdit* self = (ControlEdit*)  tolua_tousertype(tolua_S,1,0);
  int nX = ((int)  tolua_tonumber(tolua_S,2,0));
  int pCP = ((int)  tolua_tonumber(tolua_S,3,0));
  int pnTrail = ((int)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'XtoCP'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->XtoCP(nX,&pCP,&pnTrail);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
   tolua_pushnumber(tolua_S,(lua_Number)pCP);
   tolua_pushnumber(tolua_S,(lua_Number)pnTrail);
  }
 }
 return 3;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'XtoCP'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: OnEnter of class  ControlEdit */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlEdit_OnEnter00
static int tolua_CompileToLua_ControlEdit_OnEnter00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlEdit",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlEdit* self = (ControlEdit*)  tolua_tousertype(tolua_S,1,0);
  const char* szData = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'OnEnter'",NULL);
#endif
  {
   self->OnEnter(szData);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'OnEnter'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: OnTab of class  ControlEdit */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlEdit_OnTab00
static int tolua_CompileToLua_ControlEdit_OnTab00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlEdit",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlEdit* self = (ControlEdit*)  tolua_tousertype(tolua_S,1,0);
  IN  const char* szData = ((IN  const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'OnTab'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->OnTab(szData);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'OnTab'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  ControlEdit */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlEdit_new00
static int tolua_CompileToLua_ControlEdit_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"ControlEdit",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   ControlEdit* tolua_ret = (ControlEdit*)  new ControlEdit();
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"ControlEdit");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  ControlEdit */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlEdit_new00_local
static int tolua_CompileToLua_ControlEdit_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"ControlEdit",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   ControlEdit* tolua_ret = (ControlEdit*)  new ControlEdit();
   tolua_pushusertype_and_takeownership(tolua_S,(void *)tolua_ret,"ControlEdit");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: delete of class  ControlEdit */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlEdit_delete00
static int tolua_CompileToLua_ControlEdit_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlEdit",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlEdit* self = (ControlEdit*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'",NULL);
#endif
  delete self;
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Render of class  ControlFrame */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlFrame_Render00
static int tolua_CompileToLua_ControlFrame_Render00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlFrame",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlFrame* self = (ControlFrame*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Render'",NULL);
#endif
  {
   self->Render();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Render'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Run of class  ControlFrame */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlFrame_Run00
static int tolua_CompileToLua_ControlFrame_Run00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlFrame",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlFrame* self = (ControlFrame*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Run'",NULL);
#endif
  {
   self->Run();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Run'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: UseFocus of class  ControlFrame */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlFrame_UseFocus00
static int tolua_CompileToLua_ControlFrame_UseFocus00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlFrame",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlFrame* self = (ControlFrame*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'UseFocus'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->UseFocus();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'UseFocus'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: PtInObject of class  ControlFrame */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlFrame_PtInObject00
static int tolua_CompileToLua_ControlFrame_PtInObject00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlFrame",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlFrame* self = (ControlFrame*)  tolua_tousertype(tolua_S,1,0);
  const int nX = ((const int)  tolua_tonumber(tolua_S,2,0));
  const int nY = ((const int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'PtInObject'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->PtInObject(nX,nY);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'PtInObject'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: PtInOnlyFrame of class  ControlFrame */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlFrame_PtInOnlyFrame00
static int tolua_CompileToLua_ControlFrame_PtInOnlyFrame00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlFrame",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlFrame* self = (ControlFrame*)  tolua_tousertype(tolua_S,1,0);
  const int x = ((const int)  tolua_tonumber(tolua_S,2,0));
  const int y = ((const int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'PtInOnlyFrame'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->PtInOnlyFrame(x,y);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'PtInOnlyFrame'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: StartFlash of class  ControlFrame */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlFrame_StartFlash00
static int tolua_CompileToLua_ControlFrame_StartFlash00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlFrame",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isboolean(tolua_S,3,1,&tolua_err) ||
     !tolua_isboolean(tolua_S,4,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlFrame* self = (ControlFrame*)  tolua_tousertype(tolua_S,1,0);
  const int nFlashCount = ((const int)  tolua_tonumber(tolua_S,2,0));
  const bool bAutoClose = ((const bool)  tolua_toboolean(tolua_S,3,false));
  const bool bFadeIn = ((const bool)  tolua_toboolean(tolua_S,4,false));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'StartFlash'",NULL);
#endif
  {
   self->StartFlash(nFlashCount,bAutoClose,bFadeIn);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'StartFlash'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetArrayMode of class  ControlFrame */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlFrame_GetArrayMode00
static int tolua_CompileToLua_ControlFrame_GetArrayMode00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlFrame",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlFrame* self = (ControlFrame*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetArrayMode'",NULL);
#endif
  {
   int tolua_ret = (int)  self->GetArrayMode();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetArrayMode'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: IsChild of class  ControlFrame */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlFrame_IsChild00
static int tolua_CompileToLua_ControlFrame_IsChild00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlFrame",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"const ControlObject",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlFrame* self = (ControlFrame*)  tolua_tousertype(tolua_S,1,0);
  IN  const ControlObject* pChild = ((IN  const ControlObject*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'IsChild'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->IsChild(pChild);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'IsChild'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: ReleaseUI of class  ControlFrame */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlFrame_ReleaseUI00
static int tolua_CompileToLua_ControlFrame_ReleaseUI00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlFrame",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlFrame* self = (ControlFrame*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'ReleaseUI'",NULL);
#endif
  {
   self->ReleaseUI();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'ReleaseUI'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: FindControl of class  ControlFrame */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlFrame_FindControl00
static int tolua_CompileToLua_ControlFrame_FindControl00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlFrame",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlFrame* self = (ControlFrame*)  tolua_tousertype(tolua_S,1,0);
  IN  const char* szControlID = ((IN  const char*)  tolua_tostring(tolua_S,2,0));
  IN  const char* szFrameID = ((IN  const char*)  tolua_tostring(tolua_S,3,NULL));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'FindControl'",NULL);
#endif
  {
   ControlObject* tolua_ret = (ControlObject*)  self->FindControl(szControlID,szFrameID);
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"ControlObject");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'FindControl'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: FindFrame of class  ControlFrame */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlFrame_FindFrame00
static int tolua_CompileToLua_ControlFrame_FindFrame00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlFrame",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlFrame* self = (ControlFrame*)  tolua_tousertype(tolua_S,1,0);
  IN  const char* szFrameID = ((IN  const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'FindFrame'",NULL);
#endif
  {
   ControlObject* tolua_ret = (ControlObject*)  self->FindFrame(szFrameID);
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"ControlObject");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'FindFrame'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: OnMouseMove of class  ControlFrame */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlFrame_OnMouseMove00
static int tolua_CompileToLua_ControlFrame_OnMouseMove00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlFrame",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"UINT",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlFrame* self = (ControlFrame*)  tolua_tousertype(tolua_S,1,0);
  UINT nFlags = *((UINT*)  tolua_tousertype(tolua_S,2,0));
  const int nX = ((const int)  tolua_tonumber(tolua_S,3,0));
  const int nY = ((const int)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'OnMouseMove'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->OnMouseMove(nFlags,nX,nY);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'OnMouseMove'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: OnMouseWheel of class  ControlFrame */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlFrame_OnMouseWheel00
static int tolua_CompileToLua_ControlFrame_OnMouseWheel00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlFrame",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlFrame* self = (ControlFrame*)  tolua_tousertype(tolua_S,1,0);
  bool bUp = ((bool)  tolua_toboolean(tolua_S,2,0));
  const int nX = ((const int)  tolua_tonumber(tolua_S,3,0));
  const int nY = ((const int)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'OnMouseWheel'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->OnMouseWheel(bUp,nX,nY);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'OnMouseWheel'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: OnLButtonDown of class  ControlFrame */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlFrame_OnLButtonDown00
static int tolua_CompileToLua_ControlFrame_OnLButtonDown00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlFrame",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"UINT",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlFrame* self = (ControlFrame*)  tolua_tousertype(tolua_S,1,0);
  UINT nFlags = *((UINT*)  tolua_tousertype(tolua_S,2,0));
  const int nX = ((const int)  tolua_tonumber(tolua_S,3,0));
  const int nY = ((const int)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'OnLButtonDown'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->OnLButtonDown(nFlags,nX,nY);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'OnLButtonDown'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: OnLButtonUp of class  ControlFrame */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlFrame_OnLButtonUp00
static int tolua_CompileToLua_ControlFrame_OnLButtonUp00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlFrame",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"UINT",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlFrame* self = (ControlFrame*)  tolua_tousertype(tolua_S,1,0);
  UINT nFlags = *((UINT*)  tolua_tousertype(tolua_S,2,0));
  const int nX = ((const int)  tolua_tonumber(tolua_S,3,0));
  const int nY = ((const int)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'OnLButtonUp'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->OnLButtonUp(nFlags,nX,nY);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'OnLButtonUp'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: OnLButtonDBClick of class  ControlFrame */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlFrame_OnLButtonDBClick00
static int tolua_CompileToLua_ControlFrame_OnLButtonDBClick00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlFrame",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"UINT",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlFrame* self = (ControlFrame*)  tolua_tousertype(tolua_S,1,0);
  UINT nFlags = *((UINT*)  tolua_tousertype(tolua_S,2,0));
  const int nX = ((const int)  tolua_tonumber(tolua_S,3,0));
  const int nY = ((const int)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'OnLButtonDBClick'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->OnLButtonDBClick(nFlags,nX,nY);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'OnLButtonDBClick'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: OnRButtonDown of class  ControlFrame */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlFrame_OnRButtonDown00
static int tolua_CompileToLua_ControlFrame_OnRButtonDown00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlFrame",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"UINT",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlFrame* self = (ControlFrame*)  tolua_tousertype(tolua_S,1,0);
  UINT nFlags = *((UINT*)  tolua_tousertype(tolua_S,2,0));
  const int nX = ((const int)  tolua_tonumber(tolua_S,3,0));
  const int nY = ((const int)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'OnRButtonDown'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->OnRButtonDown(nFlags,nX,nY);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'OnRButtonDown'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: OnRButtonUp of class  ControlFrame */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlFrame_OnRButtonUp00
static int tolua_CompileToLua_ControlFrame_OnRButtonUp00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlFrame",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"UINT",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlFrame* self = (ControlFrame*)  tolua_tousertype(tolua_S,1,0);
  UINT nFlags = *((UINT*)  tolua_tousertype(tolua_S,2,0));
  const int nX = ((const int)  tolua_tonumber(tolua_S,3,0));
  const int nY = ((const int)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'OnRButtonUp'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->OnRButtonUp(nFlags,nX,nY);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'OnRButtonUp'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: OnRButtonDBClick of class  ControlFrame */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlFrame_OnRButtonDBClick00
static int tolua_CompileToLua_ControlFrame_OnRButtonDBClick00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlFrame",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"UINT",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlFrame* self = (ControlFrame*)  tolua_tousertype(tolua_S,1,0);
  UINT nFlags = *((UINT*)  tolua_tousertype(tolua_S,2,0));
  const int nX = ((const int)  tolua_tonumber(tolua_S,3,0));
  const int nY = ((const int)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'OnRButtonDBClick'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->OnRButtonDBClick(nFlags,nX,nY);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'OnRButtonDBClick'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: OnMouseLeave of class  ControlFrame */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlFrame_OnMouseLeave00
static int tolua_CompileToLua_ControlFrame_OnMouseLeave00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlFrame",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlFrame* self = (ControlFrame*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'OnMouseLeave'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->OnMouseLeave();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'OnMouseLeave'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: OnKeyDown of class  ControlFrame */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlFrame_OnKeyDown00
static int tolua_CompileToLua_ControlFrame_OnKeyDown00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlFrame",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"UINT",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlFrame* self = (ControlFrame*)  tolua_tousertype(tolua_S,1,0);
  UINT nChar = *((UINT*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'OnKeyDown'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->OnKeyDown(nChar);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'OnKeyDown'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: OnKeyUp of class  ControlFrame */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlFrame_OnKeyUp00
static int tolua_CompileToLua_ControlFrame_OnKeyUp00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlFrame",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"UINT",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlFrame* self = (ControlFrame*)  tolua_tousertype(tolua_S,1,0);
  UINT nChar = *((UINT*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'OnKeyUp'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->OnKeyUp(nChar);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'OnKeyUp'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: OnChar of class  ControlFrame */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlFrame_OnChar00
static int tolua_CompileToLua_ControlFrame_OnChar00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlFrame",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"UINT",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlFrame* self = (ControlFrame*)  tolua_tousertype(tolua_S,1,0);
  UINT nChar = *((UINT*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'OnChar'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->OnChar(nChar);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'OnChar'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: IsLButtonDrag of class  ControlFrame */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlFrame_IsLButtonDrag00
static int tolua_CompileToLua_ControlFrame_IsLButtonDrag00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlFrame",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlFrame* self = (ControlFrame*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'IsLButtonDrag'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->IsLButtonDrag();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'IsLButtonDrag'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: LoadUIFormFile of class  ControlFrame */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlFrame_LoadUIFormFile00
static int tolua_CompileToLua_ControlFrame_LoadUIFormFile00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlFrame",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"ControlObject",1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlFrame* self = (ControlFrame*)  tolua_tousertype(tolua_S,1,0);
  IN  const char* szFileName = ((IN  const char*)  tolua_tostring(tolua_S,2,0));
  IN ControlObject* pFather = ((IN ControlObject*)  tolua_tousertype(tolua_S,3,NULL));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'LoadUIFormFile'",NULL);
#endif
  {
   DWORD tolua_ret = (DWORD)  self->LoadUIFormFile(szFileName,pFather);
   {
#ifdef __cplusplus
    void* tolua_obj = new DWORD(tolua_ret);
    tolua_pushusertype_and_takeownership(tolua_S,tolua_obj,"DWORD");
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(DWORD));
    tolua_pushusertype_and_takeownership(tolua_S,tolua_obj,"DWORD");
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'LoadUIFormFile'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetArrayMode of class  ControlFrame */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlFrame_SetArrayMode00
static int tolua_CompileToLua_ControlFrame_SetArrayMode00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlFrame",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlFrame* self = (ControlFrame*)  tolua_tousertype(tolua_S,1,0);
  const int nMode = ((const int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetArrayMode'",NULL);
#endif
  {
   self->SetArrayMode(nMode);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetArrayMode'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetRunFun_2lua of class  ControlFrame */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlFrame_SetRunFun_2lua00
static int tolua_CompileToLua_ControlFrame_SetRunFun_2lua00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlFrame",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlFrame* self = (ControlFrame*)  tolua_tousertype(tolua_S,1,0);
  const char* luaTable = ((const char*)  tolua_tostring(tolua_S,2,0));
  const char* funName = ((const char*)  tolua_tostring(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetRunFun_2lua'",NULL);
#endif
  {
   self->SetRunFun_2lua(luaTable,funName);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetRunFun_2lua'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetRenderFun_2lua of class  ControlFrame */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlFrame_SetRenderFun_2lua00
static int tolua_CompileToLua_ControlFrame_SetRenderFun_2lua00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlFrame",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlFrame* self = (ControlFrame*)  tolua_tousertype(tolua_S,1,0);
  const char* luaTable = ((const char*)  tolua_tostring(tolua_S,2,0));
  const char* funName = ((const char*)  tolua_tostring(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetRenderFun_2lua'",NULL);
#endif
  {
   self->SetRenderFun_2lua(luaTable,funName);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetRenderFun_2lua'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetOnClickFun_2lua of class  ControlFrame */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlFrame_SetOnClickFun_2lua00
static int tolua_CompileToLua_ControlFrame_SetOnClickFun_2lua00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlFrame",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlFrame* self = (ControlFrame*)  tolua_tousertype(tolua_S,1,0);
  const char* luaTable = ((const char*)  tolua_tostring(tolua_S,2,0));
  const char* funName = ((const char*)  tolua_tostring(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetOnClickFun_2lua'",NULL);
#endif
  {
   self->SetOnClickFun_2lua(luaTable,funName);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetOnClickFun_2lua'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetOnRBtnDown_2lua of class  ControlFrame */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlFrame_SetOnRBtnDown_2lua00
static int tolua_CompileToLua_ControlFrame_SetOnRBtnDown_2lua00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlFrame",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlFrame* self = (ControlFrame*)  tolua_tousertype(tolua_S,1,0);
  const char* luaTable = ((const char*)  tolua_tostring(tolua_S,2,0));
  const char* funName = ((const char*)  tolua_tostring(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetOnRBtnDown_2lua'",NULL);
#endif
  {
   self->SetOnRBtnDown_2lua(luaTable,funName);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetOnRBtnDown_2lua'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetMouseMoveOn_2lua of class  ControlFrame */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlFrame_SetMouseMoveOn_2lua00
static int tolua_CompileToLua_ControlFrame_SetMouseMoveOn_2lua00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlFrame",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlFrame* self = (ControlFrame*)  tolua_tousertype(tolua_S,1,0);
  const char* luaTable = ((const char*)  tolua_tostring(tolua_S,2,0));
  const char* funName = ((const char*)  tolua_tostring(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetMouseMoveOn_2lua'",NULL);
#endif
  {
   self->SetMouseMoveOn_2lua(luaTable,funName);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetMouseMoveOn_2lua'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetMouseMoveLevel_2lua of class  ControlFrame */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlFrame_SetMouseMoveLevel_2lua00
static int tolua_CompileToLua_ControlFrame_SetMouseMoveLevel_2lua00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlFrame",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlFrame* self = (ControlFrame*)  tolua_tousertype(tolua_S,1,0);
  const char* luaTable = ((const char*)  tolua_tostring(tolua_S,2,0));
  const char* funName = ((const char*)  tolua_tostring(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetMouseMoveLevel_2lua'",NULL);
#endif
  {
   self->SetMouseMoveLevel_2lua(luaTable,funName);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetMouseMoveLevel_2lua'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetOnTab_2lua of class  ControlFrame */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlFrame_SetOnTab_2lua00
static int tolua_CompileToLua_ControlFrame_SetOnTab_2lua00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlFrame",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlFrame* self = (ControlFrame*)  tolua_tousertype(tolua_S,1,0);
  const char* luaTable = ((const char*)  tolua_tostring(tolua_S,2,0));
  const char* funName = ((const char*)  tolua_tostring(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetOnTab_2lua'",NULL);
#endif
  {
   self->SetOnTab_2lua(luaTable,funName);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetOnTab_2lua'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetFrameMove_2lua of class  ControlFrame */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlFrame_SetFrameMove_2lua00
static int tolua_CompileToLua_ControlFrame_SetFrameMove_2lua00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlFrame",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlFrame* self = (ControlFrame*)  tolua_tousertype(tolua_S,1,0);
  const char* luaTable = ((const char*)  tolua_tostring(tolua_S,2,0));
  const char* funName = ((const char*)  tolua_tostring(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetFrameMove_2lua'",NULL);
#endif
  {
   self->SetFrameMove_2lua(luaTable,funName);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetFrameMove_2lua'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetAllVisable of class  ControlFrame */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlFrame_SetAllVisable00
static int tolua_CompileToLua_ControlFrame_SetAllVisable00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlFrame",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isboolean(tolua_S,3,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlFrame* self = (ControlFrame*)  tolua_tousertype(tolua_S,1,0);
  const bool bVisable = ((const bool)  tolua_toboolean(tolua_S,2,0));
  const bool bFadeInorFadeOut = ((const bool)  tolua_toboolean(tolua_S,3,false));
  const int nColor = ((const int)  tolua_tonumber(tolua_S,4,0xff));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetAllVisable'",NULL);
#endif
  {
   self->SetAllVisable(bVisable,bFadeInorFadeOut,nColor);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetAllVisable'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetAllFadeVal of class  ControlFrame */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlFrame_SetAllFadeVal00
static int tolua_CompileToLua_ControlFrame_SetAllFadeVal00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlFrame",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlFrame* self = (ControlFrame*)  tolua_tousertype(tolua_S,1,0);
  const int nMaxFade = ((const int)  tolua_tonumber(tolua_S,2,0));
  const int nMinFade = ((const int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetAllFadeVal'",NULL);
#endif
  {
   self->SetAllFadeVal(nMaxFade,nMinFade);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetAllFadeVal'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetAllBlendColor of class  ControlFrame */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlFrame_SetAllBlendColor00
static int tolua_CompileToLua_ControlFrame_SetAllBlendColor00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlFrame",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlFrame* self = (ControlFrame*)  tolua_tousertype(tolua_S,1,0);
  const int nColor = ((const int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetAllBlendColor'",NULL);
#endif
  {
   self->SetAllBlendColor(nColor);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetAllBlendColor'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: AppendChild of class  ControlFrame */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlFrame_AppendChild00
static int tolua_CompileToLua_ControlFrame_AppendChild00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlFrame",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"ControlObject",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlFrame* self = (ControlFrame*)  tolua_tousertype(tolua_S,1,0);
  ControlObject* pChlid = ((ControlObject*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'AppendChild'",NULL);
#endif
  {
   self->AppendChild(pChlid);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'AppendChild'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  ControlFrame */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlFrame_new00
static int tolua_CompileToLua_ControlFrame_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"ControlFrame",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   ControlFrame* tolua_ret = (ControlFrame*)  new ControlFrame();
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"ControlFrame");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  ControlFrame */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlFrame_new00_local
static int tolua_CompileToLua_ControlFrame_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"ControlFrame",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   ControlFrame* tolua_ret = (ControlFrame*)  new ControlFrame();
   tolua_pushusertype_and_takeownership(tolua_S,(void *)tolua_ret,"ControlFrame");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: delete of class  ControlFrame */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlFrame_delete00
static int tolua_CompileToLua_ControlFrame_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlFrame",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlFrame* self = (ControlFrame*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'",NULL);
#endif
  delete self;
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Id of class  S_IconInfoBase */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_S_IconInfoBase_Id00
static int tolua_CompileToLua_S_IconInfoBase_Id00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"S_IconInfoBase",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  S_IconInfoBase* self = (S_IconInfoBase*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Id'",NULL);
#endif
  {
   unsigned short tolua_ret = (unsigned short)  self->Id();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Id'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Count of class  S_IconInfoBase */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_S_IconInfoBase_Count00
static int tolua_CompileToLua_S_IconInfoBase_Count00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"S_IconInfoBase",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  S_IconInfoBase* self = (S_IconInfoBase*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Count'",NULL);
#endif
  {
   int tolua_ret = (int)  self->Count();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Count'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: IsLocked of class  S_IconInfoBase */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_S_IconInfoBase_IsLocked00
static int tolua_CompileToLua_S_IconInfoBase_IsLocked00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"S_IconInfoBase",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  S_IconInfoBase* self = (S_IconInfoBase*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'IsLocked'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->IsLocked();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'IsLocked'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: MaxCount of class  S_IconInfoBase */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_S_IconInfoBase_MaxCount00
static int tolua_CompileToLua_S_IconInfoBase_MaxCount00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"S_IconInfoBase",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  S_IconInfoBase* self = (S_IconInfoBase*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'MaxCount'",NULL);
#endif
  {
   int tolua_ret = (int)  self->MaxCount();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'MaxCount'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SpareTime of class  S_IconInfoBase */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_S_IconInfoBase_SpareTime00
static int tolua_CompileToLua_S_IconInfoBase_SpareTime00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"S_IconInfoBase",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  S_IconInfoBase* self = (S_IconInfoBase*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SpareTime'",NULL);
#endif
  {
   int tolua_ret = (int)  self->SpareTime();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SpareTime'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetSpareTime of class  S_IconInfoBase */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_S_IconInfoBase_GetSpareTime00
static int tolua_CompileToLua_S_IconInfoBase_GetSpareTime00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"S_IconInfoBase",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  S_IconInfoBase* self = (S_IconInfoBase*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetSpareTime'",NULL);
#endif
  {
   int tolua_ret = (int)  self->GetSpareTime();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetSpareTime'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: IsNextLvl of class  S_IconInfoBase */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_S_IconInfoBase_IsNextLvl00
static int tolua_CompileToLua_S_IconInfoBase_IsNextLvl00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"S_IconInfoBase",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  S_IconInfoBase* self = (S_IconInfoBase*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'IsNextLvl'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->IsNextLvl();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'IsNextLvl'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: IsNull of class  S_IconInfoBase */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_S_IconInfoBase_IsNull00
static int tolua_CompileToLua_S_IconInfoBase_IsNull00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"S_IconInfoBase",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  S_IconInfoBase* self = (S_IconInfoBase*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'IsNull'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->IsNull();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'IsNull'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetData of class  S_IconInfoBase */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_S_IconInfoBase_SetData00
static int tolua_CompileToLua_S_IconInfoBase_SetData00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"S_IconInfoBase",0,&tolua_err) ||
     !tolua_isuserdata(tolua_S,2,0,&tolua_err) ||
     !tolua_isboolean(tolua_S,3,1,&tolua_err) ||
     !tolua_isboolean(tolua_S,4,1,&tolua_err) ||
     !tolua_isuserdata(tolua_S,5,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,6,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,7,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  S_IconInfoBase* self = (S_IconInfoBase*)  tolua_tousertype(tolua_S,1,0);
  void* pData = ((void*)  tolua_touserdata(tolua_S,2,0));
  const bool bShowCount = ((const bool)  tolua_toboolean(tolua_S,3,false));
  const bool bNext = ((const bool)  tolua_toboolean(tolua_S,4,false));
  void* pCompareData = ((void*)  tolua_touserdata(tolua_S,5,NULL));
  int nPlayerID = ((int)  tolua_tonumber(tolua_S,6,-1));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetData'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->SetData(pData,bShowCount,bNext,pCompareData,nPlayerID);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetData'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetData of class  S_IconInfoBase */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_S_IconInfoBase_SetData01
static int tolua_CompileToLua_S_IconInfoBase_SetData01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"S_IconInfoBase",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isboolean(tolua_S,4,1,&tolua_err) ||
     !tolua_isboolean(tolua_S,5,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,6,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,7,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,8,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  S_IconInfoBase* self = (S_IconInfoBase*)  tolua_tousertype(tolua_S,1,0);
  const int nId = ((const int)  tolua_tonumber(tolua_S,2,0));
  const int nCount = ((const int)  tolua_tonumber(tolua_S,3,0));
  const bool bShowCount = ((const bool)  tolua_toboolean(tolua_S,4,false));
  const bool bNext = ((const bool)  tolua_toboolean(tolua_S,5,false));
  int nCompareId = ((int)  tolua_tonumber(tolua_S,6,0xffff));
  int nPlayerID = ((int)  tolua_tonumber(tolua_S,7,-1));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetData'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->SetData(nId,nCount,bShowCount,bNext,nCompareId,nPlayerID);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
tolua_lerror:
 return tolua_CompileToLua_S_IconInfoBase_SetData00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: PlaySound of class  S_IconInfoBase */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_S_IconInfoBase_PlaySound00
static int tolua_CompileToLua_S_IconInfoBase_PlaySound00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"S_IconInfoBase",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  S_IconInfoBase* self = (S_IconInfoBase*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'PlaySound'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->PlaySound();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'PlaySound'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: IconFileName of class  S_IconInfoBase */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_S_IconInfoBase_IconFileName00
static int tolua_CompileToLua_S_IconInfoBase_IconFileName00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"S_IconInfoBase",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  S_IconInfoBase* self = (S_IconInfoBase*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'IconFileName'",NULL);
#endif
  {
   std::string tolua_ret = (std::string)  self->IconFileName();
   tolua_pushcppstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'IconFileName'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: DisableIconFileName of class  S_IconInfoBase */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_S_IconInfoBase_DisableIconFileName00
static int tolua_CompileToLua_S_IconInfoBase_DisableIconFileName00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"S_IconInfoBase",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  S_IconInfoBase* self = (S_IconInfoBase*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'DisableIconFileName'",NULL);
#endif
  {
   std::string tolua_ret = (std::string)  self->DisableIconFileName();
   tolua_pushcppstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'DisableIconFileName'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: ShopIconFileName of class  S_IconInfoBase */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_S_IconInfoBase_ShopIconFileName00
static int tolua_CompileToLua_S_IconInfoBase_ShopIconFileName00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"S_IconInfoBase",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  S_IconInfoBase* self = (S_IconInfoBase*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'ShopIconFileName'",NULL);
#endif
  {
   std::string tolua_ret = (std::string)  self->ShopIconFileName();
   tolua_pushcppstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'ShopIconFileName'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Cost of class  S_IconInfoBase */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_S_IconInfoBase_Cost00
static int tolua_CompileToLua_S_IconInfoBase_Cost00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"S_IconInfoBase",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  S_IconInfoBase* self = (S_IconInfoBase*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Cost'",NULL);
#endif
  {
   int tolua_ret = (int)  self->Cost();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Cost'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Clear of class  S_IconInfoBase */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_S_IconInfoBase_Clear00
static int tolua_CompileToLua_S_IconInfoBase_Clear00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"S_IconInfoBase",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  S_IconInfoBase* self = (S_IconInfoBase*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Clear'",NULL);
#endif
  {
   self->Clear();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Clear'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: DisplayIcon of class  S_IconInfoBase */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_S_IconInfoBase_DisplayIcon00
static int tolua_CompileToLua_S_IconInfoBase_DisplayIcon00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"S_IconInfoBase",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"RECT",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"COLORREF",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,0,&tolua_err) ||
     !tolua_isusertype(tolua_S,6,"COLORREF",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,7,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,8,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  S_IconInfoBase* self = (S_IconInfoBase*)  tolua_tousertype(tolua_S,1,0);
  RECT* prcDst = ((RECT*)  tolua_tousertype(tolua_S,2,0));
  COLORREF col = *((COLORREF*)  tolua_tousertype(tolua_S,3,0));
  int nFontIndex = ((int)  tolua_tonumber(tolua_S,4,0));
  int nFontSize = ((int)  tolua_tonumber(tolua_S,5,0));
  COLORREF colFont = *((COLORREF*)  tolua_tousertype(tolua_S,6,0));
  eIconDrawState bEnable = ((eIconDrawState) (int)  tolua_tonumber(tolua_S,7,eIcon_Enable));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'DisplayIcon'",NULL);
#endif
  {
   self->DisplayIcon(prcDst,col,nFontIndex,nFontSize,colFont,bEnable);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'DisplayIcon'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: DisplayInfo of class  S_IconInfoBase */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_S_IconInfoBase_DisplayInfo00
static int tolua_CompileToLua_S_IconInfoBase_DisplayInfo00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"S_IconInfoBase",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"RECT",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,0,&tolua_err) ||
     !tolua_isusertype(tolua_S,6,"const COLORREF",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,7,1,&tolua_err) ||
     !tolua_isboolean(tolua_S,8,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,9,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  S_IconInfoBase* self = (S_IconInfoBase*)  tolua_tousertype(tolua_S,1,0);
  RECT* prc = ((RECT*)  tolua_tousertype(tolua_S,2,0));
  const bool bIsShop = ((const bool)  tolua_toboolean(tolua_S,3,0));
  const int nFontIndex = ((const int)  tolua_tonumber(tolua_S,4,0));
  const int nFontSize = ((const int)  tolua_tonumber(tolua_S,5,0));
  const COLORREF col = *((const COLORREF*)  tolua_tousertype(tolua_S,6,0));
  const bool bFaveFrame = ((const bool)  tolua_toboolean(tolua_S,7,true));
  const bool bShowAllInfo = ((const bool)  tolua_toboolean(tolua_S,8,true));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'DisplayInfo'",NULL);
#endif
  {
   self->DisplayInfo(prc,bIsShop,nFontIndex,nFontSize,col,bFaveFrame,bShowAllInfo);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'DisplayInfo'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: DisplayInfo of class  S_IconInfoBase */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_S_IconInfoBase_DisplayInfo01
static int tolua_CompileToLua_S_IconInfoBase_DisplayInfo01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"S_IconInfoBase",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isboolean(tolua_S,4,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,6,0,&tolua_err) ||
     !tolua_isusertype(tolua_S,7,"const COLORREF",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,8,1,&tolua_err) ||
     !tolua_isboolean(tolua_S,9,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,10,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  S_IconInfoBase* self = (S_IconInfoBase*)  tolua_tousertype(tolua_S,1,0);
  const int nX = ((const int)  tolua_tonumber(tolua_S,2,0));
  const int nY = ((const int)  tolua_tonumber(tolua_S,3,0));
  const bool bIsShop = ((const bool)  tolua_toboolean(tolua_S,4,0));
  const int nFontIndex = ((const int)  tolua_tonumber(tolua_S,5,0));
  const int nFontSize = ((const int)  tolua_tonumber(tolua_S,6,0));
  const COLORREF col = *((const COLORREF*)  tolua_tousertype(tolua_S,7,0));
  const bool bFaveFrame = ((const bool)  tolua_toboolean(tolua_S,8,true));
  const bool bShowAllInfo = ((const bool)  tolua_toboolean(tolua_S,9,true));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'DisplayInfo'",NULL);
#endif
  {
   self->DisplayInfo(nX,nY,bIsShop,nFontIndex,nFontSize,col,bFaveFrame,bShowAllInfo);
  }
 }
 return 0;
tolua_lerror:
 return tolua_CompileToLua_S_IconInfoBase_DisplayInfo00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetInfo of class  S_IconInfoBase */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_S_IconInfoBase_SetInfo00
static int tolua_CompileToLua_S_IconInfoBase_SetInfo00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"S_IconInfoBase",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  S_IconInfoBase* self = (S_IconInfoBase*)  tolua_tousertype(tolua_S,1,0);
  const char* szInfo = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetInfo'",NULL);
#endif
  {
   self->SetInfo(szInfo);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetInfo'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetOtherInfo of class  S_IconInfoBase */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_S_IconInfoBase_SetOtherInfo00
static int tolua_CompileToLua_S_IconInfoBase_SetOtherInfo00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"S_IconInfoBase",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  S_IconInfoBase* self = (S_IconInfoBase*)  tolua_tousertype(tolua_S,1,0);
  const char* szInfo = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetOtherInfo'",NULL);
#endif
  {
   self->SetOtherInfo(szInfo);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetOtherInfo'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetFontSize of class  S_IconInfoBase */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_S_IconInfoBase_SetFontSize00
static int tolua_CompileToLua_S_IconInfoBase_SetFontSize00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"S_IconInfoBase",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  S_IconInfoBase* self = (S_IconInfoBase*)  tolua_tousertype(tolua_S,1,0);
  int size = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetFontSize'",NULL);
#endif
  {
   self->SetFontSize(size);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetFontSize'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: delete of class  S_IconInfoBase */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_S_IconInfoBase_delete00
static int tolua_CompileToLua_S_IconInfoBase_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"S_IconInfoBase",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  S_IconInfoBase* self = (S_IconInfoBase*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'",NULL);
#endif
  delete self;
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  stIconInfo */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_S_IconInfoBase_stIconInfo_new00
static int tolua_CompileToLua_S_IconInfoBase_stIconInfo_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"S_IconInfoBase::stIconInfo",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   S_IconInfoBase::stIconInfo* tolua_ret = (S_IconInfoBase::stIconInfo*)  new S_IconInfoBase::stIconInfo();
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"S_IconInfoBase::stIconInfo");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  stIconInfo */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_S_IconInfoBase_stIconInfo_new00_local
static int tolua_CompileToLua_S_IconInfoBase_stIconInfo_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"S_IconInfoBase::stIconInfo",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   S_IconInfoBase::stIconInfo* tolua_ret = (S_IconInfoBase::stIconInfo*)  new S_IconInfoBase::stIconInfo();
   tolua_pushusertype_and_takeownership(tolua_S,(void *)tolua_ret,"S_IconInfoBase::stIconInfo");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: m_col of class  stIconInfo */
#ifndef TOLUA_DISABLE_tolua_get_S_IconInfoBase__stIconInfo_m_col
static int tolua_get_S_IconInfoBase__stIconInfo_m_col(lua_State* tolua_S)
{
  S_IconInfoBase::stIconInfo* self = (S_IconInfoBase::stIconInfo*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_col'",NULL);
#endif
  tolua_pushusertype(tolua_S,(void*)&self->m_col,"D3DCOLOR");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: m_col of class  stIconInfo */
#ifndef TOLUA_DISABLE_tolua_set_S_IconInfoBase__stIconInfo_m_col
static int tolua_set_S_IconInfoBase__stIconInfo_m_col(lua_State* tolua_S)
{
  S_IconInfoBase::stIconInfo* self = (S_IconInfoBase::stIconInfo*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_col'",NULL);
  if (!tolua_isusertype(tolua_S,2,"D3DCOLOR",0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->m_col = *((D3DCOLOR*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: m_strInfo of class  stIconInfo */
#ifndef TOLUA_DISABLE_tolua_get_S_IconInfoBase__stIconInfo_m_strInfo
static int tolua_get_S_IconInfoBase__stIconInfo_m_strInfo(lua_State* tolua_S)
{
  S_IconInfoBase::stIconInfo* self = (S_IconInfoBase::stIconInfo*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_strInfo'",NULL);
#endif
  tolua_pushcppstring(tolua_S,(const char*)self->m_strInfo);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: m_strInfo of class  stIconInfo */
#ifndef TOLUA_DISABLE_tolua_set_S_IconInfoBase__stIconInfo_m_strInfo
static int tolua_set_S_IconInfoBase__stIconInfo_m_strInfo(lua_State* tolua_S)
{
  S_IconInfoBase::stIconInfo* self = (S_IconInfoBase::stIconInfo*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_strInfo'",NULL);
  if (!tolua_iscppstring(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->m_strInfo = ((std::string)  tolua_tocppstring(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  sShowGem */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_S_IconInfoBase_sShowGem_new00
static int tolua_CompileToLua_S_IconInfoBase_sShowGem_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"S_IconInfoBase::sShowGem",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   S_IconInfoBase::sShowGem* tolua_ret = (S_IconInfoBase::sShowGem*)  new S_IconInfoBase::sShowGem();
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"S_IconInfoBase::sShowGem");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  sShowGem */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_S_IconInfoBase_sShowGem_new00_local
static int tolua_CompileToLua_S_IconInfoBase_sShowGem_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"S_IconInfoBase::sShowGem",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   S_IconInfoBase::sShowGem* tolua_ret = (S_IconInfoBase::sShowGem*)  new S_IconInfoBase::sShowGem();
   tolua_pushusertype_and_takeownership(tolua_S,(void *)tolua_ret,"S_IconInfoBase::sShowGem");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: nGemPhysicAtt of class  sShowGem */
#ifndef TOLUA_DISABLE_tolua_get_S_IconInfoBase__sShowGem_nGemPhysicAtt
static int tolua_get_S_IconInfoBase__sShowGem_nGemPhysicAtt(lua_State* tolua_S)
{
  S_IconInfoBase::sShowGem* self = (S_IconInfoBase::sShowGem*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nGemPhysicAtt'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->nGemPhysicAtt);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: nGemPhysicAtt of class  sShowGem */
#ifndef TOLUA_DISABLE_tolua_set_S_IconInfoBase__sShowGem_nGemPhysicAtt
static int tolua_set_S_IconInfoBase__sShowGem_nGemPhysicAtt(lua_State* tolua_S)
{
  S_IconInfoBase::sShowGem* self = (S_IconInfoBase::sShowGem*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nGemPhysicAtt'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->nGemPhysicAtt = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: nGemMagicAtt of class  sShowGem */
#ifndef TOLUA_DISABLE_tolua_get_S_IconInfoBase__sShowGem_nGemMagicAtt
static int tolua_get_S_IconInfoBase__sShowGem_nGemMagicAtt(lua_State* tolua_S)
{
  S_IconInfoBase::sShowGem* self = (S_IconInfoBase::sShowGem*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nGemMagicAtt'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->nGemMagicAtt);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: nGemMagicAtt of class  sShowGem */
#ifndef TOLUA_DISABLE_tolua_set_S_IconInfoBase__sShowGem_nGemMagicAtt
static int tolua_set_S_IconInfoBase__sShowGem_nGemMagicAtt(lua_State* tolua_S)
{
  S_IconInfoBase::sShowGem* self = (S_IconInfoBase::sShowGem*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nGemMagicAtt'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->nGemMagicAtt = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: nGemPhysicDef of class  sShowGem */
#ifndef TOLUA_DISABLE_tolua_get_S_IconInfoBase__sShowGem_nGemPhysicDef
static int tolua_get_S_IconInfoBase__sShowGem_nGemPhysicDef(lua_State* tolua_S)
{
  S_IconInfoBase::sShowGem* self = (S_IconInfoBase::sShowGem*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nGemPhysicDef'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->nGemPhysicDef);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: nGemPhysicDef of class  sShowGem */
#ifndef TOLUA_DISABLE_tolua_set_S_IconInfoBase__sShowGem_nGemPhysicDef
static int tolua_set_S_IconInfoBase__sShowGem_nGemPhysicDef(lua_State* tolua_S)
{
  S_IconInfoBase::sShowGem* self = (S_IconInfoBase::sShowGem*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nGemPhysicDef'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->nGemPhysicDef = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: nGemAttSpeed of class  sShowGem */
#ifndef TOLUA_DISABLE_tolua_get_S_IconInfoBase__sShowGem_nGemAttSpeed
static int tolua_get_S_IconInfoBase__sShowGem_nGemAttSpeed(lua_State* tolua_S)
{
  S_IconInfoBase::sShowGem* self = (S_IconInfoBase::sShowGem*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nGemAttSpeed'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->nGemAttSpeed);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: nGemAttSpeed of class  sShowGem */
#ifndef TOLUA_DISABLE_tolua_set_S_IconInfoBase__sShowGem_nGemAttSpeed
static int tolua_set_S_IconInfoBase__sShowGem_nGemAttSpeed(lua_State* tolua_S)
{
  S_IconInfoBase::sShowGem* self = (S_IconInfoBase::sShowGem*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nGemAttSpeed'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->nGemAttSpeed = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: nGemExact of class  sShowGem */
#ifndef TOLUA_DISABLE_tolua_get_S_IconInfoBase__sShowGem_nGemExact
static int tolua_get_S_IconInfoBase__sShowGem_nGemExact(lua_State* tolua_S)
{
  S_IconInfoBase::sShowGem* self = (S_IconInfoBase::sShowGem*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nGemExact'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->nGemExact);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: nGemExact of class  sShowGem */
#ifndef TOLUA_DISABLE_tolua_set_S_IconInfoBase__sShowGem_nGemExact
static int tolua_set_S_IconInfoBase__sShowGem_nGemExact(lua_State* tolua_S)
{
  S_IconInfoBase::sShowGem* self = (S_IconInfoBase::sShowGem*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nGemExact'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->nGemExact = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: nGemDodge of class  sShowGem */
#ifndef TOLUA_DISABLE_tolua_get_S_IconInfoBase__sShowGem_nGemDodge
static int tolua_get_S_IconInfoBase__sShowGem_nGemDodge(lua_State* tolua_S)
{
  S_IconInfoBase::sShowGem* self = (S_IconInfoBase::sShowGem*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nGemDodge'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->nGemDodge);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: nGemDodge of class  sShowGem */
#ifndef TOLUA_DISABLE_tolua_set_S_IconInfoBase__sShowGem_nGemDodge
static int tolua_set_S_IconInfoBase__sShowGem_nGemDodge(lua_State* tolua_S)
{
  S_IconInfoBase::sShowGem* self = (S_IconInfoBase::sShowGem*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nGemDodge'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->nGemDodge = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: nGemAtt of class  sShowGem */
#ifndef TOLUA_DISABLE_tolua_get_CompileToLua_S_IconInfoBase_sShowGem_nGemAtt
static int tolua_get_CompileToLua_S_IconInfoBase_sShowGem_nGemAtt(lua_State* tolua_S)
{
 int tolua_index;
  S_IconInfoBase::sShowGem* self;
 lua_pushstring(tolua_S,".self");
 lua_rawget(tolua_S,1);
 self = (S_IconInfoBase::sShowGem*)  lua_touserdata(tolua_S,-1);
#ifndef TOLUA_RELEASE
 {
  tolua_Error tolua_err;
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in array indexing.",&tolua_err);
 }
#endif
 tolua_index = (int)tolua_tonumber(tolua_S,2,0)-1;
#ifndef TOLUA_RELEASE
 if (tolua_index<0 || tolua_index>=S_IconInfoBase::sShowGem::eElement_Max)
  tolua_error(tolua_S,"array indexing out of range.",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->nGemAtt[tolua_index]);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: nGemAtt of class  sShowGem */
#ifndef TOLUA_DISABLE_tolua_set_CompileToLua_S_IconInfoBase_sShowGem_nGemAtt
static int tolua_set_CompileToLua_S_IconInfoBase_sShowGem_nGemAtt(lua_State* tolua_S)
{
 int tolua_index;
  S_IconInfoBase::sShowGem* self;
 lua_pushstring(tolua_S,".self");
 lua_rawget(tolua_S,1);
 self = (S_IconInfoBase::sShowGem*)  lua_touserdata(tolua_S,-1);
#ifndef TOLUA_RELEASE
 {
  tolua_Error tolua_err;
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in array indexing.",&tolua_err);
 }
#endif
 tolua_index = (int)tolua_tonumber(tolua_S,2,0)-1;
#ifndef TOLUA_RELEASE
 if (tolua_index<0 || tolua_index>=S_IconInfoBase::sShowGem::eElement_Max)
  tolua_error(tolua_S,"array indexing out of range.",NULL);
#endif
  self->nGemAtt[tolua_index] = ((int)  tolua_tonumber(tolua_S,3,0));
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: nGemDef of class  sShowGem */
#ifndef TOLUA_DISABLE_tolua_get_CompileToLua_S_IconInfoBase_sShowGem_nGemDef
static int tolua_get_CompileToLua_S_IconInfoBase_sShowGem_nGemDef(lua_State* tolua_S)
{
 int tolua_index;
  S_IconInfoBase::sShowGem* self;
 lua_pushstring(tolua_S,".self");
 lua_rawget(tolua_S,1);
 self = (S_IconInfoBase::sShowGem*)  lua_touserdata(tolua_S,-1);
#ifndef TOLUA_RELEASE
 {
  tolua_Error tolua_err;
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in array indexing.",&tolua_err);
 }
#endif
 tolua_index = (int)tolua_tonumber(tolua_S,2,0)-1;
#ifndef TOLUA_RELEASE
 if (tolua_index<0 || tolua_index>=S_IconInfoBase::sShowGem::eElement_Max)
  tolua_error(tolua_S,"array indexing out of range.",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->nGemDef[tolua_index]);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: nGemDef of class  sShowGem */
#ifndef TOLUA_DISABLE_tolua_set_CompileToLua_S_IconInfoBase_sShowGem_nGemDef
static int tolua_set_CompileToLua_S_IconInfoBase_sShowGem_nGemDef(lua_State* tolua_S)
{
 int tolua_index;
  S_IconInfoBase::sShowGem* self;
 lua_pushstring(tolua_S,".self");
 lua_rawget(tolua_S,1);
 self = (S_IconInfoBase::sShowGem*)  lua_touserdata(tolua_S,-1);
#ifndef TOLUA_RELEASE
 {
  tolua_Error tolua_err;
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in array indexing.",&tolua_err);
 }
#endif
 tolua_index = (int)tolua_tonumber(tolua_S,2,0)-1;
#ifndef TOLUA_RELEASE
 if (tolua_index<0 || tolua_index>=S_IconInfoBase::sShowGem::eElement_Max)
  tolua_error(tolua_S,"array indexing out of range.",NULL);
#endif
  self->nGemDef[tolua_index] = ((int)  tolua_tonumber(tolua_S,3,0));
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: nGemAddHp of class  sShowGem */
#ifndef TOLUA_DISABLE_tolua_get_S_IconInfoBase__sShowGem_nGemAddHp
static int tolua_get_S_IconInfoBase__sShowGem_nGemAddHp(lua_State* tolua_S)
{
  S_IconInfoBase::sShowGem* self = (S_IconInfoBase::sShowGem*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nGemAddHp'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->nGemAddHp);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: nGemAddHp of class  sShowGem */
#ifndef TOLUA_DISABLE_tolua_set_S_IconInfoBase__sShowGem_nGemAddHp
static int tolua_set_S_IconInfoBase__sShowGem_nGemAddHp(lua_State* tolua_S)
{
  S_IconInfoBase::sShowGem* self = (S_IconInfoBase::sShowGem*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nGemAddHp'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->nGemAddHp = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: nGemAddMp of class  sShowGem */
#ifndef TOLUA_DISABLE_tolua_get_S_IconInfoBase__sShowGem_nGemAddMp
static int tolua_get_S_IconInfoBase__sShowGem_nGemAddMp(lua_State* tolua_S)
{
  S_IconInfoBase::sShowGem* self = (S_IconInfoBase::sShowGem*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nGemAddMp'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->nGemAddMp);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: nGemAddMp of class  sShowGem */
#ifndef TOLUA_DISABLE_tolua_set_S_IconInfoBase__sShowGem_nGemAddMp
static int tolua_set_S_IconInfoBase__sShowGem_nGemAddMp(lua_State* tolua_S)
{
  S_IconInfoBase::sShowGem* self = (S_IconInfoBase::sShowGem*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nGemAddMp'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->nGemAddMp = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: nGemAddHpRestor of class  sShowGem */
#ifndef TOLUA_DISABLE_tolua_get_S_IconInfoBase__sShowGem_nGemAddHpRestor
static int tolua_get_S_IconInfoBase__sShowGem_nGemAddHpRestor(lua_State* tolua_S)
{
  S_IconInfoBase::sShowGem* self = (S_IconInfoBase::sShowGem*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nGemAddHpRestor'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->nGemAddHpRestor);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: nGemAddHpRestor of class  sShowGem */
#ifndef TOLUA_DISABLE_tolua_set_S_IconInfoBase__sShowGem_nGemAddHpRestor
static int tolua_set_S_IconInfoBase__sShowGem_nGemAddHpRestor(lua_State* tolua_S)
{
  S_IconInfoBase::sShowGem* self = (S_IconInfoBase::sShowGem*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nGemAddHpRestor'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->nGemAddHpRestor = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: nGemAddMpRestor of class  sShowGem */
#ifndef TOLUA_DISABLE_tolua_get_S_IconInfoBase__sShowGem_nGemAddMpRestor
static int tolua_get_S_IconInfoBase__sShowGem_nGemAddMpRestor(lua_State* tolua_S)
{
  S_IconInfoBase::sShowGem* self = (S_IconInfoBase::sShowGem*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nGemAddMpRestor'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->nGemAddMpRestor);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: nGemAddMpRestor of class  sShowGem */
#ifndef TOLUA_DISABLE_tolua_set_S_IconInfoBase__sShowGem_nGemAddMpRestor
static int tolua_set_S_IconInfoBase__sShowGem_nGemAddMpRestor(lua_State* tolua_S)
{
  S_IconInfoBase::sShowGem* self = (S_IconInfoBase::sShowGem*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nGemAddMpRestor'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->nGemAddMpRestor = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* method: Render of class  CIconInfoMouseTip */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_CIconInfoMouseTip_Render00
static int tolua_CompileToLua_CIconInfoMouseTip_Render00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CIconInfoMouseTip",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CIconInfoMouseTip* self = (CIconInfoMouseTip*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Render'",NULL);
#endif
  {
   self->Render();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Render'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Clear of class  CIconInfoMouseTip */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_CIconInfoMouseTip_Clear00
static int tolua_CompileToLua_CIconInfoMouseTip_Clear00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CIconInfoMouseTip",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CIconInfoMouseTip* self = (CIconInfoMouseTip*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Clear'",NULL);
#endif
  {
   self->Clear();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Clear'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetDisplayInfo of class  CIconInfoMouseTip */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_CIconInfoMouseTip_SetDisplayInfo00
static int tolua_CompileToLua_CIconInfoMouseTip_SetDisplayInfo00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CIconInfoMouseTip",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"S_IconInfoBase",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isboolean(tolua_S,5,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,6,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,7,0,&tolua_err) ||
     !tolua_isusertype(tolua_S,8,"const COLORREF",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,9,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,10,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CIconInfoMouseTip* self = (CIconInfoMouseTip*)  tolua_tousertype(tolua_S,1,0);
  S_IconInfoBase* pIconInfo = ((S_IconInfoBase*)  tolua_tousertype(tolua_S,2,0));
  const int nX = ((const int)  tolua_tonumber(tolua_S,3,0));
  const int nY = ((const int)  tolua_tonumber(tolua_S,4,0));
  const bool bShowPrice = ((const bool)  tolua_toboolean(tolua_S,5,0));
  const int nFontIndex = ((const int)  tolua_tonumber(tolua_S,6,0));
  const int nFontSize = ((const int)  tolua_tonumber(tolua_S,7,0));
  const COLORREF col = *((const COLORREF*)  tolua_tousertype(tolua_S,8,0));
  const bool bShowAllInfo = ((const bool)  tolua_toboolean(tolua_S,9,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetDisplayInfo'",NULL);
#endif
  {
   self->SetDisplayInfo(pIconInfo,nX,nY,bShowPrice,nFontIndex,nFontSize,col,bShowAllInfo);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetDisplayInfo'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: m_bShopOpen of class  CIconInfoMouseTip */
#ifndef TOLUA_DISABLE_tolua_get_CIconInfoMouseTip_m_bShopOpen
static int tolua_get_CIconInfoMouseTip_m_bShopOpen(lua_State* tolua_S)
{
  CIconInfoMouseTip* self = (CIconInfoMouseTip*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_bShopOpen'",NULL);
#endif
  tolua_pushboolean(tolua_S,(bool)self->m_bShopOpen);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: m_bShopOpen of class  CIconInfoMouseTip */
#ifndef TOLUA_DISABLE_tolua_set_CIconInfoMouseTip_m_bShopOpen
static int tolua_set_CIconInfoMouseTip_m_bShopOpen(lua_State* tolua_S)
{
  CIconInfoMouseTip* self = (CIconInfoMouseTip*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_bShopOpen'",NULL);
  if (!tolua_isboolean(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->m_bShopOpen = ((bool)  tolua_toboolean(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  CIconInfoMouseTip */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_CIconInfoMouseTip_new00
static int tolua_CompileToLua_CIconInfoMouseTip_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CIconInfoMouseTip",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CIconInfoMouseTip* tolua_ret = (CIconInfoMouseTip*)  new CIconInfoMouseTip();
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"CIconInfoMouseTip");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  CIconInfoMouseTip */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_CIconInfoMouseTip_new00_local
static int tolua_CompileToLua_CIconInfoMouseTip_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CIconInfoMouseTip",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CIconInfoMouseTip* tolua_ret = (CIconInfoMouseTip*)  new CIconInfoMouseTip();
   tolua_pushusertype_and_takeownership(tolua_S,(void *)tolua_ret,"CIconInfoMouseTip");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Id of class  S_TextTipInfo */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_S_TextTipInfo_Id00
static int tolua_CompileToLua_S_TextTipInfo_Id00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"S_TextTipInfo",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  S_TextTipInfo* self = (S_TextTipInfo*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Id'",NULL);
#endif
  {
   unsigned short tolua_ret = (unsigned short)  self->Id();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Id'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Count of class  S_TextTipInfo */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_S_TextTipInfo_Count00
static int tolua_CompileToLua_S_TextTipInfo_Count00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"S_TextTipInfo",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  S_TextTipInfo* self = (S_TextTipInfo*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Count'",NULL);
#endif
  {
   int tolua_ret = (int)  self->Count();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Count'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: IsLocked of class  S_TextTipInfo */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_S_TextTipInfo_IsLocked00
static int tolua_CompileToLua_S_TextTipInfo_IsLocked00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"S_TextTipInfo",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  S_TextTipInfo* self = (S_TextTipInfo*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'IsLocked'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->IsLocked();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'IsLocked'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: MaxCount of class  S_TextTipInfo */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_S_TextTipInfo_MaxCount00
static int tolua_CompileToLua_S_TextTipInfo_MaxCount00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"S_TextTipInfo",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  S_TextTipInfo* self = (S_TextTipInfo*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'MaxCount'",NULL);
#endif
  {
   int tolua_ret = (int)  self->MaxCount();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'MaxCount'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SpareTime of class  S_TextTipInfo */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_S_TextTipInfo_SpareTime00
static int tolua_CompileToLua_S_TextTipInfo_SpareTime00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"S_TextTipInfo",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  S_TextTipInfo* self = (S_TextTipInfo*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SpareTime'",NULL);
#endif
  {
   int tolua_ret = (int)  self->SpareTime();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SpareTime'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetSpareTime of class  S_TextTipInfo */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_S_TextTipInfo_GetSpareTime00
static int tolua_CompileToLua_S_TextTipInfo_GetSpareTime00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"S_TextTipInfo",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  S_TextTipInfo* self = (S_TextTipInfo*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetSpareTime'",NULL);
#endif
  {
   int tolua_ret = (int)  self->GetSpareTime();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetSpareTime'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: IsNextLvl of class  S_TextTipInfo */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_S_TextTipInfo_IsNextLvl00
static int tolua_CompileToLua_S_TextTipInfo_IsNextLvl00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"S_TextTipInfo",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  S_TextTipInfo* self = (S_TextTipInfo*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'IsNextLvl'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->IsNextLvl();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'IsNextLvl'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: IsNull of class  S_TextTipInfo */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_S_TextTipInfo_IsNull00
static int tolua_CompileToLua_S_TextTipInfo_IsNull00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"S_TextTipInfo",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  S_TextTipInfo* self = (S_TextTipInfo*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'IsNull'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->IsNull();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'IsNull'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetData of class  S_TextTipInfo */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_S_TextTipInfo_SetData00
static int tolua_CompileToLua_S_TextTipInfo_SetData00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"S_TextTipInfo",0,&tolua_err) ||
     !tolua_isuserdata(tolua_S,2,0,&tolua_err) ||
     !tolua_isboolean(tolua_S,3,1,&tolua_err) ||
     !tolua_isboolean(tolua_S,4,1,&tolua_err) ||
     !tolua_isuserdata(tolua_S,5,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,6,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,7,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  S_TextTipInfo* self = (S_TextTipInfo*)  tolua_tousertype(tolua_S,1,0);
  void* pData = ((void*)  tolua_touserdata(tolua_S,2,0));
  const bool bShowCount = ((const bool)  tolua_toboolean(tolua_S,3,false));
  const bool bNext = ((const bool)  tolua_toboolean(tolua_S,4,false));
  void* pCompareData = ((void*)  tolua_touserdata(tolua_S,5,NULL));
  int nPlayerID = ((int)  tolua_tonumber(tolua_S,6,-1));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetData'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->SetData(pData,bShowCount,bNext,pCompareData,nPlayerID);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetData'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetData of class  S_TextTipInfo */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_S_TextTipInfo_SetData01
static int tolua_CompileToLua_S_TextTipInfo_SetData01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"S_TextTipInfo",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isboolean(tolua_S,4,1,&tolua_err) ||
     !tolua_isboolean(tolua_S,5,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,6,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,7,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,8,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  S_TextTipInfo* self = (S_TextTipInfo*)  tolua_tousertype(tolua_S,1,0);
  const int nId = ((const int)  tolua_tonumber(tolua_S,2,0));
  const int nCount = ((const int)  tolua_tonumber(tolua_S,3,0));
  const bool bShowCount = ((const bool)  tolua_toboolean(tolua_S,4,false));
  const bool bNext = ((const bool)  tolua_toboolean(tolua_S,5,false));
  int nCompareId = ((int)  tolua_tonumber(tolua_S,6,0xffff));
  int nPlayerID = ((int)  tolua_tonumber(tolua_S,7,-1));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetData'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->SetData(nId,nCount,bShowCount,bNext,nCompareId,nPlayerID);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
tolua_lerror:
 return tolua_CompileToLua_S_TextTipInfo_SetData00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: PlaySound of class  S_TextTipInfo */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_S_TextTipInfo_PlaySound00
static int tolua_CompileToLua_S_TextTipInfo_PlaySound00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"S_TextTipInfo",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  S_TextTipInfo* self = (S_TextTipInfo*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'PlaySound'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->PlaySound();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'PlaySound'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: IconFileName of class  S_TextTipInfo */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_S_TextTipInfo_IconFileName00
static int tolua_CompileToLua_S_TextTipInfo_IconFileName00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"S_TextTipInfo",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  S_TextTipInfo* self = (S_TextTipInfo*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'IconFileName'",NULL);
#endif
  {
   std::string tolua_ret = (std::string)  self->IconFileName();
   tolua_pushcppstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'IconFileName'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: DisableIconFileName of class  S_TextTipInfo */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_S_TextTipInfo_DisableIconFileName00
static int tolua_CompileToLua_S_TextTipInfo_DisableIconFileName00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"S_TextTipInfo",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  S_TextTipInfo* self = (S_TextTipInfo*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'DisableIconFileName'",NULL);
#endif
  {
   std::string tolua_ret = (std::string)  self->DisableIconFileName();
   tolua_pushcppstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'DisableIconFileName'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: ShopIconFileName of class  S_TextTipInfo */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_S_TextTipInfo_ShopIconFileName00
static int tolua_CompileToLua_S_TextTipInfo_ShopIconFileName00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"S_TextTipInfo",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  S_TextTipInfo* self = (S_TextTipInfo*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'ShopIconFileName'",NULL);
#endif
  {
   std::string tolua_ret = (std::string)  self->ShopIconFileName();
   tolua_pushcppstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'ShopIconFileName'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Cost of class  S_TextTipInfo */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_S_TextTipInfo_Cost00
static int tolua_CompileToLua_S_TextTipInfo_Cost00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"S_TextTipInfo",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  S_TextTipInfo* self = (S_TextTipInfo*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Cost'",NULL);
#endif
  {
   int tolua_ret = (int)  self->Cost();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Cost'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  S_TextTipInfo */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_S_TextTipInfo_new00
static int tolua_CompileToLua_S_TextTipInfo_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"S_TextTipInfo",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   S_TextTipInfo* tolua_ret = (S_TextTipInfo*)  new S_TextTipInfo();
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"S_TextTipInfo");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  S_TextTipInfo */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_S_TextTipInfo_new00_local
static int tolua_CompileToLua_S_TextTipInfo_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"S_TextTipInfo",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   S_TextTipInfo* tolua_ret = (S_TextTipInfo*)  new S_TextTipInfo();
   tolua_pushusertype_and_takeownership(tolua_S,(void *)tolua_ret,"S_TextTipInfo");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Clear of class  S_TextTipInfo */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_S_TextTipInfo_Clear00
static int tolua_CompileToLua_S_TextTipInfo_Clear00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"S_TextTipInfo",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  S_TextTipInfo* self = (S_TextTipInfo*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Clear'",NULL);
#endif
  {
   self->Clear();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Clear'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Id of class  S_IconInfoHero */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_S_IconInfoHero_Id00
static int tolua_CompileToLua_S_IconInfoHero_Id00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"S_IconInfoHero",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  S_IconInfoHero* self = (S_IconInfoHero*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Id'",NULL);
#endif
  {
   unsigned short tolua_ret = (unsigned short)  self->Id();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Id'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Count of class  S_IconInfoHero */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_S_IconInfoHero_Count00
static int tolua_CompileToLua_S_IconInfoHero_Count00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"S_IconInfoHero",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  S_IconInfoHero* self = (S_IconInfoHero*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Count'",NULL);
#endif
  {
   int tolua_ret = (int)  self->Count();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Count'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: IsLocked of class  S_IconInfoHero */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_S_IconInfoHero_IsLocked00
static int tolua_CompileToLua_S_IconInfoHero_IsLocked00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"S_IconInfoHero",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  S_IconInfoHero* self = (S_IconInfoHero*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'IsLocked'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->IsLocked();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'IsLocked'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: MaxCount of class  S_IconInfoHero */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_S_IconInfoHero_MaxCount00
static int tolua_CompileToLua_S_IconInfoHero_MaxCount00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"S_IconInfoHero",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  S_IconInfoHero* self = (S_IconInfoHero*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'MaxCount'",NULL);
#endif
  {
   int tolua_ret = (int)  self->MaxCount();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'MaxCount'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SpareTime of class  S_IconInfoHero */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_S_IconInfoHero_SpareTime00
static int tolua_CompileToLua_S_IconInfoHero_SpareTime00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"S_IconInfoHero",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  S_IconInfoHero* self = (S_IconInfoHero*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SpareTime'",NULL);
#endif
  {
   int tolua_ret = (int)  self->SpareTime();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SpareTime'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetSpareTime of class  S_IconInfoHero */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_S_IconInfoHero_GetSpareTime00
static int tolua_CompileToLua_S_IconInfoHero_GetSpareTime00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"S_IconInfoHero",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  S_IconInfoHero* self = (S_IconInfoHero*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetSpareTime'",NULL);
#endif
  {
   int tolua_ret = (int)  self->GetSpareTime();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetSpareTime'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: IsNextLvl of class  S_IconInfoHero */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_S_IconInfoHero_IsNextLvl00
static int tolua_CompileToLua_S_IconInfoHero_IsNextLvl00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"S_IconInfoHero",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  S_IconInfoHero* self = (S_IconInfoHero*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'IsNextLvl'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->IsNextLvl();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'IsNextLvl'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: IsNull of class  S_IconInfoHero */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_S_IconInfoHero_IsNull00
static int tolua_CompileToLua_S_IconInfoHero_IsNull00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"S_IconInfoHero",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  S_IconInfoHero* self = (S_IconInfoHero*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'IsNull'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->IsNull();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'IsNull'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetData of class  S_IconInfoHero */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_S_IconInfoHero_SetData00
static int tolua_CompileToLua_S_IconInfoHero_SetData00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"S_IconInfoHero",0,&tolua_err) ||
     !tolua_isuserdata(tolua_S,2,0,&tolua_err) ||
     !tolua_isboolean(tolua_S,3,1,&tolua_err) ||
     !tolua_isboolean(tolua_S,4,1,&tolua_err) ||
     !tolua_isuserdata(tolua_S,5,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,6,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,7,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  S_IconInfoHero* self = (S_IconInfoHero*)  tolua_tousertype(tolua_S,1,0);
  void* pData = ((void*)  tolua_touserdata(tolua_S,2,0));
  const bool bShowCount = ((const bool)  tolua_toboolean(tolua_S,3,false));
  const bool bNext = ((const bool)  tolua_toboolean(tolua_S,4,false));
  void* pCompareData = ((void*)  tolua_touserdata(tolua_S,5,NULL));
  int nPlayerID = ((int)  tolua_tonumber(tolua_S,6,-1));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetData'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->SetData(pData,bShowCount,bNext,pCompareData,nPlayerID);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetData'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetData of class  S_IconInfoHero */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_S_IconInfoHero_SetData01
static int tolua_CompileToLua_S_IconInfoHero_SetData01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"S_IconInfoHero",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isboolean(tolua_S,4,1,&tolua_err) ||
     !tolua_isboolean(tolua_S,5,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,6,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,7,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,8,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  S_IconInfoHero* self = (S_IconInfoHero*)  tolua_tousertype(tolua_S,1,0);
  const int nId = ((const int)  tolua_tonumber(tolua_S,2,0));
  const int nCount = ((const int)  tolua_tonumber(tolua_S,3,0));
  const bool bShowCount = ((const bool)  tolua_toboolean(tolua_S,4,false));
  const bool bNext = ((const bool)  tolua_toboolean(tolua_S,5,false));
  int nCompareId = ((int)  tolua_tonumber(tolua_S,6,ErrorUnsignedShortID));
  int nPlayerID = ((int)  tolua_tonumber(tolua_S,7,-1));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetData'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->SetData(nId,nCount,bShowCount,bNext,nCompareId,nPlayerID);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
tolua_lerror:
 return tolua_CompileToLua_S_IconInfoHero_SetData00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: PlaySound of class  S_IconInfoHero */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_S_IconInfoHero_PlaySound00
static int tolua_CompileToLua_S_IconInfoHero_PlaySound00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"S_IconInfoHero",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  S_IconInfoHero* self = (S_IconInfoHero*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'PlaySound'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->PlaySound();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'PlaySound'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetSpareTime of class  S_IconInfoHero */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_S_IconInfoHero_SetSpareTime00
static int tolua_CompileToLua_S_IconInfoHero_SetSpareTime00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"S_IconInfoHero",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  S_IconInfoHero* self = (S_IconInfoHero*)  tolua_tousertype(tolua_S,1,0);
  int nSpareTime = ((int)  tolua_tonumber(tolua_S,2,0));
  int nStartTime = ((int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetSpareTime'",NULL);
#endif
  {
   self->SetSpareTime(nSpareTime,nStartTime);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetSpareTime'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetQualityColor of class  S_IconInfoHero */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_S_IconInfoHero_GetQualityColor00
static int tolua_CompileToLua_S_IconInfoHero_GetQualityColor00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"S_IconInfoHero",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"DWORD",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  DWORD dwQuality = *((DWORD*)  tolua_tousertype(tolua_S,2,0));
  {
   DWORD tolua_ret = (DWORD)  S_IconInfoHero::GetQualityColor(dwQuality);
   {
#ifdef __cplusplus
    void* tolua_obj = new DWORD(tolua_ret);
    tolua_pushusertype_and_takeownership(tolua_S,tolua_obj,"DWORD");
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(DWORD));
    tolua_pushusertype_and_takeownership(tolua_S,tolua_obj,"DWORD");
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetQualityColor'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: IconFileName of class  S_IconInfoHero */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_S_IconInfoHero_IconFileName00
static int tolua_CompileToLua_S_IconInfoHero_IconFileName00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"S_IconInfoHero",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  S_IconInfoHero* self = (S_IconInfoHero*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'IconFileName'",NULL);
#endif
  {
   std::string tolua_ret = (std::string)  self->IconFileName();
   tolua_pushcppstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'IconFileName'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: DisableIconFileName of class  S_IconInfoHero */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_S_IconInfoHero_DisableIconFileName00
static int tolua_CompileToLua_S_IconInfoHero_DisableIconFileName00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"S_IconInfoHero",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  S_IconInfoHero* self = (S_IconInfoHero*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'DisableIconFileName'",NULL);
#endif
  {
   std::string tolua_ret = (std::string)  self->DisableIconFileName();
   tolua_pushcppstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'DisableIconFileName'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: ShopIconFileName of class  S_IconInfoHero */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_S_IconInfoHero_ShopIconFileName00
static int tolua_CompileToLua_S_IconInfoHero_ShopIconFileName00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"S_IconInfoHero",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  S_IconInfoHero* self = (S_IconInfoHero*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'ShopIconFileName'",NULL);
#endif
  {
   std::string tolua_ret = (std::string)  self->ShopIconFileName();
   tolua_pushcppstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'ShopIconFileName'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Cost of class  S_IconInfoHero */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_S_IconInfoHero_Cost00
static int tolua_CompileToLua_S_IconInfoHero_Cost00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"S_IconInfoHero",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  S_IconInfoHero* self = (S_IconInfoHero*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Cost'",NULL);
#endif
  {
   int tolua_ret = (int)  self->Cost();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Cost'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: ShowBaseInfo of class  S_IconInfoHero */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_S_IconInfoHero_ShowBaseInfo00
static int tolua_CompileToLua_S_IconInfoHero_ShowBaseInfo00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"S_IconInfoHero",0,&tolua_err) ||
     !tolua_isuserdata(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isuserdata(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  S_IconInfoHero* self = (S_IconInfoHero*)  tolua_tousertype(tolua_S,1,0);
  void* pItemDetail = ((void*)  tolua_touserdata(tolua_S,2,0));
  int nType = ((int)  tolua_tonumber(tolua_S,3,0));
  void* pComItemDetail = ((void*)  tolua_touserdata(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'ShowBaseInfo'",NULL);
#endif
  {
   self->ShowBaseInfo(pItemDetail,nType,pComItemDetail);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'ShowBaseInfo'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: ShowCanWeapon of class  S_IconInfoHero */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_S_IconInfoHero_ShowCanWeapon00
static int tolua_CompileToLua_S_IconInfoHero_ShowCanWeapon00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"S_IconInfoHero",0,&tolua_err) ||
     !tolua_isuserdata(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isuserdata(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  S_IconInfoHero* self = (S_IconInfoHero*)  tolua_tousertype(tolua_S,1,0);
  void* pItemDetail = ((void*)  tolua_touserdata(tolua_S,2,0));
  int nType = ((int)  tolua_tonumber(tolua_S,3,0));
  void* pComItemDetail = ((void*)  tolua_touserdata(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'ShowCanWeapon'",NULL);
#endif
  {
   self->ShowCanWeapon(pItemDetail,nType,pComItemDetail);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'ShowCanWeapon'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: ShowWeapon of class  S_IconInfoHero */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_S_IconInfoHero_ShowWeapon00
static int tolua_CompileToLua_S_IconInfoHero_ShowWeapon00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"S_IconInfoHero",0,&tolua_err) ||
     !tolua_isuserdata(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isuserdata(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  S_IconInfoHero* self = (S_IconInfoHero*)  tolua_tousertype(tolua_S,1,0);
  void* pItemDetail = ((void*)  tolua_touserdata(tolua_S,2,0));
  int nType = ((int)  tolua_tonumber(tolua_S,3,0));
  void* pComItemDetail = ((void*)  tolua_touserdata(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'ShowWeapon'",NULL);
#endif
  {
   self->ShowWeapon(pItemDetail,nType,pComItemDetail);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'ShowWeapon'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: ShowArmour of class  S_IconInfoHero */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_S_IconInfoHero_ShowArmour00
static int tolua_CompileToLua_S_IconInfoHero_ShowArmour00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"S_IconInfoHero",0,&tolua_err) ||
     !tolua_isuserdata(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isuserdata(tolua_S,4,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,6,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,7,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  S_IconInfoHero* self = (S_IconInfoHero*)  tolua_tousertype(tolua_S,1,0);
  void* pItemDetail = ((void*)  tolua_touserdata(tolua_S,2,0));
  int nType = ((int)  tolua_tonumber(tolua_S,3,0));
  void* pComItemDetail = ((void*)  tolua_touserdata(tolua_S,4,0));
  int nPlayerID = ((int)  tolua_tonumber(tolua_S,5,0));
  int dwDestColor = ((int)  tolua_tonumber(tolua_S,6,0xCACBCCCD));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'ShowArmour'",NULL);
#endif
  {
   self->ShowArmour(pItemDetail,nType,pComItemDetail,nPlayerID,dwDestColor);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'ShowArmour'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: ShowSkill of class  S_IconInfoHero */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_S_IconInfoHero_ShowSkill00
static int tolua_CompileToLua_S_IconInfoHero_ShowSkill00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"S_IconInfoHero",0,&tolua_err) ||
     !tolua_isuserdata(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  S_IconInfoHero* self = (S_IconInfoHero*)  tolua_tousertype(tolua_S,1,0);
  void* pItemDetail = ((void*)  tolua_touserdata(tolua_S,2,0));
  int nType = ((int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'ShowSkill'",NULL);
#endif
  {
   self->ShowSkill(pItemDetail,nType);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'ShowSkill'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: ShowRestore of class  S_IconInfoHero */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_S_IconInfoHero_ShowRestore00
static int tolua_CompileToLua_S_IconInfoHero_ShowRestore00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"S_IconInfoHero",0,&tolua_err) ||
     !tolua_isuserdata(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  S_IconInfoHero* self = (S_IconInfoHero*)  tolua_tousertype(tolua_S,1,0);
  void* pItemDetail = ((void*)  tolua_touserdata(tolua_S,2,0));
  int nType = ((int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'ShowRestore'",NULL);
#endif
  {
   self->ShowRestore(pItemDetail,nType);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'ShowRestore'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: ShowGem of class  S_IconInfoHero */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_S_IconInfoHero_ShowGem00
static int tolua_CompileToLua_S_IconInfoHero_ShowGem00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"S_IconInfoHero",0,&tolua_err) ||
     !tolua_isuserdata(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isuserdata(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  S_IconInfoHero* self = (S_IconInfoHero*)  tolua_tousertype(tolua_S,1,0);
  void* pItemDetail = ((void*)  tolua_touserdata(tolua_S,2,0));
  int nType = ((int)  tolua_tonumber(tolua_S,3,0));
  void* pComItemDetail = ((void*)  tolua_touserdata(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'ShowGem'",NULL);
#endif
  {
   self->ShowGem(pItemDetail,nType,pComItemDetail);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'ShowGem'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetGemCount of class  S_IconInfoHero */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_S_IconInfoHero_SetGemCount00
static int tolua_CompileToLua_S_IconInfoHero_SetGemCount00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"S_IconInfoHero",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"S_IconInfoBase::sShowGem",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  S_IconInfoHero* self = (S_IconInfoHero*)  tolua_tousertype(tolua_S,1,0);
  short stIntensifyPart = ((short)  tolua_tonumber(tolua_S,2,0));
  S_IconInfoBase::sShowGem* pShowGem = ((S_IconInfoBase::sShowGem*)  tolua_tousertype(tolua_S,3,0));
  int nGemCount = ((int)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetGemCount'",NULL);
#endif
  {
   self->SetGemCount(stIntensifyPart,pShowGem,nGemCount);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetGemCount'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Clear of class  S_IconInfoHero */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_S_IconInfoHero_Clear00
static int tolua_CompileToLua_S_IconInfoHero_Clear00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"S_IconInfoHero",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  S_IconInfoHero* self = (S_IconInfoHero*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Clear'",NULL);
#endif
  {
   self->Clear();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Clear'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  S_IconInfoHero */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_S_IconInfoHero_new00
static int tolua_CompileToLua_S_IconInfoHero_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"S_IconInfoHero",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   S_IconInfoHero* tolua_ret = (S_IconInfoHero*)  new S_IconInfoHero();
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"S_IconInfoHero");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  S_IconInfoHero */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_S_IconInfoHero_new00_local
static int tolua_CompileToLua_S_IconInfoHero_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"S_IconInfoHero",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   S_IconInfoHero* tolua_ret = (S_IconInfoHero*)  new S_IconInfoHero();
   tolua_pushusertype_and_takeownership(tolua_S,(void *)tolua_ret,"S_IconInfoHero");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  S_ListImg */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlIconDrag_S_ListImg_new00
static int tolua_CompileToLua_ControlIconDrag_S_ListImg_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"ControlIconDrag::S_ListImg",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   ControlIconDrag::S_ListImg* tolua_ret = (ControlIconDrag::S_ListImg*)  new ControlIconDrag::S_ListImg();
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"ControlIconDrag::S_ListImg");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  S_ListImg */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlIconDrag_S_ListImg_new00_local
static int tolua_CompileToLua_ControlIconDrag_S_ListImg_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"ControlIconDrag::S_ListImg",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   ControlIconDrag::S_ListImg* tolua_ret = (ControlIconDrag::S_ListImg*)  new ControlIconDrag::S_ListImg();
   tolua_pushusertype_and_takeownership(tolua_S,(void *)tolua_ret,"ControlIconDrag::S_ListImg");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Clear of class  S_ListImg */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlIconDrag_S_ListImg_Clear00
static int tolua_CompileToLua_ControlIconDrag_S_ListImg_Clear00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlIconDrag::S_ListImg",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlIconDrag::S_ListImg* self = (ControlIconDrag::S_ListImg*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Clear'",NULL);
#endif
  {
   self->Clear();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Clear'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: IsNull of class  S_ListImg */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlIconDrag_S_ListImg_IsNull00
static int tolua_CompileToLua_ControlIconDrag_S_ListImg_IsNull00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlIconDrag::S_ListImg",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlIconDrag::S_ListImg* self = (ControlIconDrag::S_ListImg*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'IsNull'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->IsNull();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'IsNull'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: ChangeCount of class  S_ListImg */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlIconDrag_S_ListImg_ChangeCount00
static int tolua_CompileToLua_ControlIconDrag_S_ListImg_ChangeCount00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlIconDrag::S_ListImg",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlIconDrag::S_ListImg* self = (ControlIconDrag::S_ListImg*)  tolua_tousertype(tolua_S,1,0);
  const bool bAdd = ((const bool)  tolua_toboolean(tolua_S,2,0));
  const int nCount = ((const int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'ChangeCount'",NULL);
#endif
  {
   self->ChangeCount(bAdd,nCount);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'ChangeCount'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetData of class  S_ListImg */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlIconDrag_S_ListImg_SetData00
static int tolua_CompileToLua_ControlIconDrag_S_ListImg_SetData00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlIconDrag::S_ListImg",0,&tolua_err) ||
     !tolua_isuserdata(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,1,&tolua_err) ||
     !tolua_isuserdata(tolua_S,5,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,6,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,7,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlIconDrag::S_ListImg* self = (ControlIconDrag::S_ListImg*)  tolua_tousertype(tolua_S,1,0);
  IN void* pData = ((IN void*)  tolua_touserdata(tolua_S,2,0));
  eIconDrawState eEnable = ((eIconDrawState) (int)  tolua_tonumber(tolua_S,3,eIcon_Enable));
  eTipFlag eFlags = ((eTipFlag) (int)  tolua_tonumber(tolua_S,4,eTipFlag_Normal));
  IN void* pCompareData = ((IN void*)  tolua_touserdata(tolua_S,5,NULL));
  int nPlayerID = ((int)  tolua_tonumber(tolua_S,6,-1));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetData'",NULL);
#endif
  {
   self->SetData(pData,eEnable,eFlags,pCompareData,nPlayerID);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetData'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetData of class  S_ListImg */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlIconDrag_S_ListImg_SetData01
static int tolua_CompileToLua_ControlIconDrag_S_ListImg_SetData01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlIconDrag::S_ListImg",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,1,&tolua_err) ||
     !tolua_isboolean(tolua_S,5,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,6,1,&tolua_err) ||
     !tolua_isboolean(tolua_S,7,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,8,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  ControlIconDrag::S_ListImg* self = (ControlIconDrag::S_ListImg*)  tolua_tousertype(tolua_S,1,0);
  int nID = ((int)  tolua_tonumber(tolua_S,2,0));
  int nCount = ((int)  tolua_tonumber(tolua_S,3,0));
  eIconDrawState eEnable = ((eIconDrawState) (int)  tolua_tonumber(tolua_S,4,eIcon_Enable));
  bool bShowCount = ((bool)  tolua_toboolean(tolua_S,5,false));
  eTipFlag eFlags = ((eTipFlag) (int)  tolua_tonumber(tolua_S,6,eTipFlag_Normal));
  bool bNext = ((bool)  tolua_toboolean(tolua_S,7,false));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetData'",NULL);
#endif
  {
   self->SetData(nID,nCount,eEnable,bShowCount,eFlags,bNext);
  }
 }
 return 0;
tolua_lerror:
 return tolua_CompileToLua_ControlIconDrag_S_ListImg_SetData00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetFlags of class  S_ListImg */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlIconDrag_S_ListImg_SetFlags00
static int tolua_CompileToLua_ControlIconDrag_S_ListImg_SetFlags00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlIconDrag::S_ListImg",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlIconDrag::S_ListImg* self = (ControlIconDrag::S_ListImg*)  tolua_tousertype(tolua_S,1,0);
  int Flags = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetFlags'",NULL);
#endif
  {
   self->SetFlags(Flags);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetFlags'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetTime of class  S_ListImg */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlIconDrag_S_ListImg_SetTime00
static int tolua_CompileToLua_ControlIconDrag_S_ListImg_SetTime00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlIconDrag::S_ListImg",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlIconDrag::S_ListImg* self = (ControlIconDrag::S_ListImg*)  tolua_tousertype(tolua_S,1,0);
  int dwStartTime = ((int)  tolua_tonumber(tolua_S,2,0));
  int dwPeriod = ((int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetTime'",NULL);
#endif
  {
   self->SetTime(dwStartTime,dwPeriod);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetTime'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetOtherInfo of class  S_ListImg */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlIconDrag_S_ListImg_SetOtherInfo00
static int tolua_CompileToLua_ControlIconDrag_S_ListImg_SetOtherInfo00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlIconDrag::S_ListImg",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlIconDrag::S_ListImg* self = (ControlIconDrag::S_ListImg*)  tolua_tousertype(tolua_S,1,0);
  const char* szInfo = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetOtherInfo'",NULL);
#endif
  {
   self->SetOtherInfo(szInfo);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetOtherInfo'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetCol of class  S_ListImg */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlIconDrag_S_ListImg_SetCol00
static int tolua_CompileToLua_ControlIconDrag_S_ListImg_SetCol00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlIconDrag::S_ListImg",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"const COLORREF",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlIconDrag::S_ListImg* self = (ControlIconDrag::S_ListImg*)  tolua_tousertype(tolua_S,1,0);
  const COLORREF* col = ((const COLORREF*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetCol'",NULL);
#endif
  {
   self->SetCol(*col);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetCol'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetEnable of class  S_ListImg */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlIconDrag_S_ListImg_SetEnable00
static int tolua_CompileToLua_ControlIconDrag_S_ListImg_SetEnable00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlIconDrag::S_ListImg",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlIconDrag::S_ListImg* self = (ControlIconDrag::S_ListImg*)  tolua_tousertype(tolua_S,1,0);
  eIconDrawState eEnable = ((eIconDrawState) (int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetEnable'",NULL);
#endif
  {
   self->SetEnable(eEnable);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetEnable'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: m_eEnable of class  S_ListImg */
#ifndef TOLUA_DISABLE_tolua_get_ControlIconDrag__S_ListImg_m_eEnable
static int tolua_get_ControlIconDrag__S_ListImg_m_eEnable(lua_State* tolua_S)
{
  ControlIconDrag::S_ListImg* self = (ControlIconDrag::S_ListImg*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_eEnable'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->m_eEnable);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: m_eEnable of class  S_ListImg */
#ifndef TOLUA_DISABLE_tolua_set_ControlIconDrag__S_ListImg_m_eEnable
static int tolua_set_ControlIconDrag__S_ListImg_m_eEnable(lua_State* tolua_S)
{
  ControlIconDrag::S_ListImg* self = (ControlIconDrag::S_ListImg*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_eEnable'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->m_eEnable = ((eIconDrawState) (int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: m_stIcon of class  S_ListImg */
#ifndef TOLUA_DISABLE_tolua_get_ControlIconDrag__S_ListImg_m_stIcon
static int tolua_get_ControlIconDrag__S_ListImg_m_stIcon(lua_State* tolua_S)
{
  ControlIconDrag::S_ListImg* self = (ControlIconDrag::S_ListImg*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_stIcon'",NULL);
#endif
  tolua_pushusertype(tolua_S,(void*)&self->m_stIcon,"ICON_INFO_STRUCT");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: m_stIcon of class  S_ListImg */
#ifndef TOLUA_DISABLE_tolua_set_ControlIconDrag__S_ListImg_m_stIcon
static int tolua_set_ControlIconDrag__S_ListImg_m_stIcon(lua_State* tolua_S)
{
  ControlIconDrag::S_ListImg* self = (ControlIconDrag::S_ListImg*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_stIcon'",NULL);
  if (!tolua_isusertype(tolua_S,2,"ICON_INFO_STRUCT",0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->m_stIcon = *((ICON_INFO_STRUCT*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: m_dwFlags of class  S_ListImg */
#ifndef TOLUA_DISABLE_tolua_get_ControlIconDrag__S_ListImg_m_dwFlags
static int tolua_get_ControlIconDrag__S_ListImg_m_dwFlags(lua_State* tolua_S)
{
  ControlIconDrag::S_ListImg* self = (ControlIconDrag::S_ListImg*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_dwFlags'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->m_dwFlags);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: m_dwFlags of class  S_ListImg */
#ifndef TOLUA_DISABLE_tolua_set_ControlIconDrag__S_ListImg_m_dwFlags
static int tolua_set_ControlIconDrag__S_ListImg_m_dwFlags(lua_State* tolua_S)
{
  ControlIconDrag::S_ListImg* self = (ControlIconDrag::S_ListImg*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_dwFlags'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->m_dwFlags = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: m_dwColor of class  S_ListImg */
#ifndef TOLUA_DISABLE_tolua_get_ControlIconDrag__S_ListImg_m_dwColor
static int tolua_get_ControlIconDrag__S_ListImg_m_dwColor(lua_State* tolua_S)
{
  ControlIconDrag::S_ListImg* self = (ControlIconDrag::S_ListImg*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_dwColor'",NULL);
#endif
  tolua_pushusertype(tolua_S,(void*)&self->m_dwColor,"COLORREF");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: m_dwColor of class  S_ListImg */
#ifndef TOLUA_DISABLE_tolua_set_ControlIconDrag__S_ListImg_m_dwColor
static int tolua_set_ControlIconDrag__S_ListImg_m_dwColor(lua_State* tolua_S)
{
  ControlIconDrag::S_ListImg* self = (ControlIconDrag::S_ListImg*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_dwColor'",NULL);
  if (!tolua_isusertype(tolua_S,2,"COLORREF",0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->m_dwColor = *((COLORREF*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: m_dwStartTime of class  S_ListImg */
#ifndef TOLUA_DISABLE_tolua_get_ControlIconDrag__S_ListImg_m_dwStartTime
static int tolua_get_ControlIconDrag__S_ListImg_m_dwStartTime(lua_State* tolua_S)
{
  ControlIconDrag::S_ListImg* self = (ControlIconDrag::S_ListImg*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_dwStartTime'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->m_dwStartTime);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: m_dwStartTime of class  S_ListImg */
#ifndef TOLUA_DISABLE_tolua_set_ControlIconDrag__S_ListImg_m_dwStartTime
static int tolua_set_ControlIconDrag__S_ListImg_m_dwStartTime(lua_State* tolua_S)
{
  ControlIconDrag::S_ListImg* self = (ControlIconDrag::S_ListImg*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_dwStartTime'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->m_dwStartTime = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: m_dwPeriod of class  S_ListImg */
#ifndef TOLUA_DISABLE_tolua_get_ControlIconDrag__S_ListImg_m_dwPeriod
static int tolua_get_ControlIconDrag__S_ListImg_m_dwPeriod(lua_State* tolua_S)
{
  ControlIconDrag::S_ListImg* self = (ControlIconDrag::S_ListImg*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_dwPeriod'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->m_dwPeriod);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: m_dwPeriod of class  S_ListImg */
#ifndef TOLUA_DISABLE_tolua_set_ControlIconDrag__S_ListImg_m_dwPeriod
static int tolua_set_ControlIconDrag__S_ListImg_m_dwPeriod(lua_State* tolua_S)
{
  ControlIconDrag::S_ListImg* self = (ControlIconDrag::S_ListImg*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_dwPeriod'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->m_dwPeriod = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: m_col of class  S_ListImg */
#ifndef TOLUA_DISABLE_tolua_get_ControlIconDrag__S_ListImg_m_col
static int tolua_get_ControlIconDrag__S_ListImg_m_col(lua_State* tolua_S)
{
  ControlIconDrag::S_ListImg* self = (ControlIconDrag::S_ListImg*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_col'",NULL);
#endif
  tolua_pushusertype(tolua_S,(void*)&self->m_col,"COLORREF");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: m_col of class  S_ListImg */
#ifndef TOLUA_DISABLE_tolua_set_ControlIconDrag__S_ListImg_m_col
static int tolua_set_ControlIconDrag__S_ListImg_m_col(lua_State* tolua_S)
{
  ControlIconDrag::S_ListImg* self = (ControlIconDrag::S_ListImg*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_col'",NULL);
  if (!tolua_isusertype(tolua_S,2,"COLORREF",0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->m_col = *((COLORREF*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: m_bUseCol of class  S_ListImg */
#ifndef TOLUA_DISABLE_tolua_get_ControlIconDrag__S_ListImg_m_bUseCol
static int tolua_get_ControlIconDrag__S_ListImg_m_bUseCol(lua_State* tolua_S)
{
  ControlIconDrag::S_ListImg* self = (ControlIconDrag::S_ListImg*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_bUseCol'",NULL);
#endif
  tolua_pushboolean(tolua_S,(bool)self->m_bUseCol);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: m_bUseCol of class  S_ListImg */
#ifndef TOLUA_DISABLE_tolua_set_ControlIconDrag__S_ListImg_m_bUseCol
static int tolua_set_ControlIconDrag__S_ListImg_m_bUseCol(lua_State* tolua_S)
{
  ControlIconDrag::S_ListImg* self = (ControlIconDrag::S_ListImg*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_bUseCol'",NULL);
  if (!tolua_isboolean(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->m_bUseCol = ((bool)  tolua_toboolean(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* method: Run of class  ControlIconDrag */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlIconDrag_Run00
static int tolua_CompileToLua_ControlIconDrag_Run00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlIconDrag",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlIconDrag* self = (ControlIconDrag*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Run'",NULL);
#endif
  {
   self->Run();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Run'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: OnMouseMove of class  ControlIconDrag */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlIconDrag_OnMouseMove00
static int tolua_CompileToLua_ControlIconDrag_OnMouseMove00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlIconDrag",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"UINT",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlIconDrag* self = (ControlIconDrag*)  tolua_tousertype(tolua_S,1,0);
  UINT nFlags = *((UINT*)  tolua_tousertype(tolua_S,2,0));
  const int nX = ((const int)  tolua_tonumber(tolua_S,3,0));
  const int nY = ((const int)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'OnMouseMove'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->OnMouseMove(nFlags,nX,nY);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'OnMouseMove'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: OnMouseWheel of class  ControlIconDrag */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlIconDrag_OnMouseWheel00
static int tolua_CompileToLua_ControlIconDrag_OnMouseWheel00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlIconDrag",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlIconDrag* self = (ControlIconDrag*)  tolua_tousertype(tolua_S,1,0);
  bool bUp = ((bool)  tolua_toboolean(tolua_S,2,0));
  const int nX = ((const int)  tolua_tonumber(tolua_S,3,0));
  const int nY = ((const int)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'OnMouseWheel'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->OnMouseWheel(bUp,nX,nY);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'OnMouseWheel'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: OnLButtonDown of class  ControlIconDrag */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlIconDrag_OnLButtonDown00
static int tolua_CompileToLua_ControlIconDrag_OnLButtonDown00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlIconDrag",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"UINT",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlIconDrag* self = (ControlIconDrag*)  tolua_tousertype(tolua_S,1,0);
  UINT nFlags = *((UINT*)  tolua_tousertype(tolua_S,2,0));
  const int nX = ((const int)  tolua_tonumber(tolua_S,3,0));
  const int nY = ((const int)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'OnLButtonDown'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->OnLButtonDown(nFlags,nX,nY);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'OnLButtonDown'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: OnLButtonUp of class  ControlIconDrag */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlIconDrag_OnLButtonUp00
static int tolua_CompileToLua_ControlIconDrag_OnLButtonUp00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlIconDrag",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"UINT",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlIconDrag* self = (ControlIconDrag*)  tolua_tousertype(tolua_S,1,0);
  UINT nFlags = *((UINT*)  tolua_tousertype(tolua_S,2,0));
  const int nX = ((const int)  tolua_tonumber(tolua_S,3,0));
  const int nY = ((const int)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'OnLButtonUp'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->OnLButtonUp(nFlags,nX,nY);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'OnLButtonUp'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: OnRButtonUp of class  ControlIconDrag */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlIconDrag_OnRButtonUp00
static int tolua_CompileToLua_ControlIconDrag_OnRButtonUp00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlIconDrag",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"UINT",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlIconDrag* self = (ControlIconDrag*)  tolua_tousertype(tolua_S,1,0);
  UINT nFlags = *((UINT*)  tolua_tousertype(tolua_S,2,0));
  const int nX = ((const int)  tolua_tonumber(tolua_S,3,0));
  const int nY = ((const int)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'OnRButtonUp'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->OnRButtonUp(nFlags,nX,nY);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'OnRButtonUp'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: OnLButtonDBClick of class  ControlIconDrag */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlIconDrag_OnLButtonDBClick00
static int tolua_CompileToLua_ControlIconDrag_OnLButtonDBClick00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlIconDrag",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"UINT",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlIconDrag* self = (ControlIconDrag*)  tolua_tousertype(tolua_S,1,0);
  UINT nFlags = *((UINT*)  tolua_tousertype(tolua_S,2,0));
  const int nX = ((const int)  tolua_tonumber(tolua_S,3,0));
  const int nY = ((const int)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'OnLButtonDBClick'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->OnLButtonDBClick(nFlags,nX,nY);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'OnLButtonDBClick'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetIconSize of class  ControlIconDrag */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlIconDrag_GetIconSize00
static int tolua_CompileToLua_ControlIconDrag_GetIconSize00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlIconDrag",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlIconDrag* self = (ControlIconDrag*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetIconSize'",NULL);
#endif
  {
   int tolua_ret = (int)  self->GetIconSize();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetIconSize'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetTilePt of class  ControlIconDrag */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlIconDrag_GetTilePt00
static int tolua_CompileToLua_ControlIconDrag_GetTilePt00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlIconDrag",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isusertype(tolua_S,4,"POINT",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlIconDrag* self = (ControlIconDrag*)  tolua_tousertype(tolua_S,1,0);
  const int nX = ((const int)  tolua_tonumber(tolua_S,2,0));
  const int nY = ((const int)  tolua_tonumber(tolua_S,3,0));
  OUT POINT* ptTile = ((OUT POINT*)  tolua_tousertype(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetTilePt'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->GetTilePt(nX,nY,ptTile);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetTilePt'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: CanbePick of class  ControlIconDrag */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlIconDrag_CanbePick00
static int tolua_CompileToLua_ControlIconDrag_CanbePick00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlIconDrag",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlIconDrag* self = (ControlIconDrag*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'CanbePick'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->CanbePick();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'CanbePick'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetCanbePick of class  ControlIconDrag */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlIconDrag_SetCanbePick00
static int tolua_CompileToLua_ControlIconDrag_SetCanbePick00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlIconDrag",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlIconDrag* self = (ControlIconDrag*)  tolua_tousertype(tolua_S,1,0);
  const bool b = ((const bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetCanbePick'",NULL);
#endif
  {
   self->SetCanbePick(b);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetCanbePick'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: OnDragOn of class  ControlIconDrag */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlIconDrag_OnDragOn00
static int tolua_CompileToLua_ControlIconDrag_OnDragOn00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlIconDrag",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isusertype(tolua_S,4,"ControlIconDrag::S_ListImg",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,5,"ControlObject",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlIconDrag* self = (ControlIconDrag*)  tolua_tousertype(tolua_S,1,0);
  const int nX = ((const int)  tolua_tonumber(tolua_S,2,0));
  const int nY = ((const int)  tolua_tonumber(tolua_S,3,0));
  OUT IN ControlIconDrag::S_ListImg* pItem = ((OUT IN ControlIconDrag::S_ListImg*)  tolua_tousertype(tolua_S,4,0));
  IN ControlObject* pSender = ((IN ControlObject*)  tolua_tousertype(tolua_S,5,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'OnDragOn'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->OnDragOn(nX,nY,pItem,pSender);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'OnDragOn'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetItem of class  ControlIconDrag */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlIconDrag_SetItem00
static int tolua_CompileToLua_ControlIconDrag_SetItem00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlIconDrag",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"ControlIconDrag::S_ListImg",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,1,&tolua_err) ||
     !tolua_isboolean(tolua_S,4,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlIconDrag* self = (ControlIconDrag*)  tolua_tousertype(tolua_S,1,0);
  IN ControlIconDrag::S_ListImg* pItem = ((IN ControlIconDrag::S_ListImg*)  tolua_tousertype(tolua_S,2,0));
  const int nIndex = ((const int)  tolua_tonumber(tolua_S,3,-1));
  bool reverse = ((bool)  tolua_toboolean(tolua_S,4,false));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetItem'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->SetItem(pItem,nIndex,reverse);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetItem'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: RemoveItemById of class  ControlIconDrag */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlIconDrag_RemoveItemById00
static int tolua_CompileToLua_ControlIconDrag_RemoveItemById00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlIconDrag",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlIconDrag* self = (ControlIconDrag*)  tolua_tousertype(tolua_S,1,0);
  const int nItemID = ((const int)  tolua_tonumber(tolua_S,2,0));
  const int nCount = ((const int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'RemoveItemById'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->RemoveItemById(nItemID,nCount);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'RemoveItemById'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: RemoveItemByIndex of class  ControlIconDrag */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlIconDrag_RemoveItemByIndex00
static int tolua_CompileToLua_ControlIconDrag_RemoveItemByIndex00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlIconDrag",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlIconDrag* self = (ControlIconDrag*)  tolua_tousertype(tolua_S,1,0);
  int nIndex = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'RemoveItemByIndex'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->RemoveItemByIndex(nIndex);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'RemoveItemByIndex'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Clear of class  ControlIconDrag */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlIconDrag_Clear00
static int tolua_CompileToLua_ControlIconDrag_Clear00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlIconDrag",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlIconDrag* self = (ControlIconDrag*)  tolua_tousertype(tolua_S,1,0);
  bool bChangeStartIndex = ((bool)  tolua_toboolean(tolua_S,2,false));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Clear'",NULL);
#endif
  {
   self->Clear(bChangeStartIndex);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Clear'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetItem of class  ControlIconDrag */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlIconDrag_GetItem00
static int tolua_CompileToLua_ControlIconDrag_GetItem00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlIconDrag",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlIconDrag* self = (ControlIconDrag*)  tolua_tousertype(tolua_S,1,0);
  unsigned const int nX = ((unsigned const int)  tolua_tonumber(tolua_S,2,0));
  unsigned const int nY = ((unsigned const int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetItem'",NULL);
#endif
  {
   ControlIconDrag::S_ListImg* tolua_ret = (ControlIconDrag::S_ListImg*)  self->GetItem(nX,nY);
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"ControlIconDrag::S_ListImg");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetItem'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetCurSelItem of class  ControlIconDrag */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlIconDrag_GetCurSelItem00
static int tolua_CompileToLua_ControlIconDrag_GetCurSelItem00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlIconDrag",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlIconDrag* self = (ControlIconDrag*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetCurSelItem'",NULL);
#endif
  {
   ControlIconDrag::S_ListImg* tolua_ret = (ControlIconDrag::S_ListImg*)  self->GetCurSelItem();
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"ControlIconDrag::S_ListImg");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetCurSelItem'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetItemByIndex of class  ControlIconDrag */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlIconDrag_GetItemByIndex00
static int tolua_CompileToLua_ControlIconDrag_GetItemByIndex00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlIconDrag",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlIconDrag* self = (ControlIconDrag*)  tolua_tousertype(tolua_S,1,0);
  unsigned const int nIndex = ((unsigned const int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetItemByIndex'",NULL);
#endif
  {
   ControlIconDrag::S_ListImg* tolua_ret = (ControlIconDrag::S_ListImg*)  self->GetItemByIndex(nIndex);
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"ControlIconDrag::S_ListImg");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetItemByIndex'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetLastIndex of class  ControlIconDrag */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlIconDrag_GetLastIndex00
static int tolua_CompileToLua_ControlIconDrag_GetLastIndex00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlIconDrag",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlIconDrag* self = (ControlIconDrag*)  tolua_tousertype(tolua_S,1,0);
  int index = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetLastIndex'",NULL);
#endif
  {
   ControlIconDrag::S_ListImg* tolua_ret = (ControlIconDrag::S_ListImg*)  self->GetLastIndex(index);
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"ControlIconDrag::S_ListImg");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetLastIndex'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetItemById of class  ControlIconDrag */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlIconDrag_GetItemById00
static int tolua_CompileToLua_ControlIconDrag_GetItemById00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlIconDrag",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlIconDrag* self = (ControlIconDrag*)  tolua_tousertype(tolua_S,1,0);
  const int nId = ((const int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetItemById'",NULL);
#endif
  {
   ControlIconDrag::S_ListImg* tolua_ret = (ControlIconDrag::S_ListImg*)  self->GetItemById(nId);
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"ControlIconDrag::S_ListImg");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetItemById'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetItemIndex of class  ControlIconDrag */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlIconDrag_GetItemIndex00
static int tolua_CompileToLua_ControlIconDrag_GetItemIndex00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlIconDrag",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"const ControlIconDrag::S_ListImg",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlIconDrag* self = (ControlIconDrag*)  tolua_tousertype(tolua_S,1,0);
  IN  const ControlIconDrag::S_ListImg* pItem = ((IN  const ControlIconDrag::S_ListImg*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetItemIndex'",NULL);
#endif
  {
   int tolua_ret = (int)  self->GetItemIndex(pItem);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetItemIndex'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetNullItem of class  ControlIconDrag */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlIconDrag_GetNullItem00
static int tolua_CompileToLua_ControlIconDrag_GetNullItem00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlIconDrag",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlIconDrag* self = (ControlIconDrag*)  tolua_tousertype(tolua_S,1,0);
  bool reverse = ((bool)  tolua_toboolean(tolua_S,2,false));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetNullItem'",NULL);
#endif
  {
   int tolua_ret = (int)  self->GetNullItem(reverse);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetNullItem'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetIsShop of class  ControlIconDrag */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlIconDrag_SetIsShop00
static int tolua_CompileToLua_ControlIconDrag_SetIsShop00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlIconDrag",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlIconDrag* self = (ControlIconDrag*)  tolua_tousertype(tolua_S,1,0);
  const bool b = ((const bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetIsShop'",NULL);
#endif
  {
   self->SetIsShop(b);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetIsShop'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetShowAllInfo of class  ControlIconDrag */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlIconDrag_SetShowAllInfo00
static int tolua_CompileToLua_ControlIconDrag_SetShowAllInfo00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlIconDrag",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlIconDrag* self = (ControlIconDrag*)  tolua_tousertype(tolua_S,1,0);
  const bool b = ((const bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetShowAllInfo'",NULL);
#endif
  {
   self->SetShowAllInfo(b);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetShowAllInfo'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetItemCnt of class  ControlIconDrag */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlIconDrag_GetItemCnt00
static int tolua_CompileToLua_ControlIconDrag_GetItemCnt00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlIconDrag",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlIconDrag* self = (ControlIconDrag*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetItemCnt'",NULL);
#endif
  {
   int tolua_ret = (int)  self->GetItemCnt();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetItemCnt'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetSpareTime of class  ControlIconDrag */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlIconDrag_SetSpareTime00
static int tolua_CompileToLua_ControlIconDrag_SetSpareTime00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlIconDrag",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlIconDrag* self = (ControlIconDrag*)  tolua_tousertype(tolua_S,1,0);
  int nIndex = ((int)  tolua_tonumber(tolua_S,2,0));
  int nTime = ((int)  tolua_tonumber(tolua_S,3,0));
  int nStartTime = ((int)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetSpareTime'",NULL);
#endif
  {
   self->SetSpareTime(nIndex,nTime,nStartTime);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetSpareTime'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetStartIndex of class  ControlIconDrag */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlIconDrag_GetStartIndex00
static int tolua_CompileToLua_ControlIconDrag_GetStartIndex00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const ControlIconDrag",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const ControlIconDrag* self = (const ControlIconDrag*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetStartIndex'",NULL);
#endif
  {
   int tolua_ret = (int)  self->GetStartIndex();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetStartIndex'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetScrollVisable of class  ControlIconDrag */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlIconDrag_SetScrollVisable00
static int tolua_CompileToLua_ControlIconDrag_SetScrollVisable00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlIconDrag",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlIconDrag* self = (ControlIconDrag*)  tolua_tousertype(tolua_S,1,0);
  bool bShow = ((bool)  tolua_toboolean(tolua_S,2,true));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetScrollVisable'",NULL);
#endif
  {
   self->SetScrollVisable(bShow);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetScrollVisable'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetStartIndex of class  ControlIconDrag */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlIconDrag_SetStartIndex00
static int tolua_CompileToLua_ControlIconDrag_SetStartIndex00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlIconDrag",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlIconDrag* self = (ControlIconDrag*)  tolua_tousertype(tolua_S,1,0);
  int nStartIndex = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetStartIndex'",NULL);
#endif
  {
   self->SetStartIndex(nStartIndex);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetStartIndex'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetScrollBarEnable of class  ControlIconDrag */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlIconDrag_SetScrollBarEnable00
static int tolua_CompileToLua_ControlIconDrag_SetScrollBarEnable00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlIconDrag",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlIconDrag* self = (ControlIconDrag*)  tolua_tousertype(tolua_S,1,0);
  bool bEnable = ((bool)  tolua_toboolean(tolua_S,2,true));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetScrollBarEnable'",NULL);
#endif
  {
   self->SetScrollBarEnable(bEnable);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetScrollBarEnable'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: IsDisableCanbePick of class  ControlIconDrag */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlIconDrag_IsDisableCanbePick00
static int tolua_CompileToLua_ControlIconDrag_IsDisableCanbePick00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlIconDrag",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlIconDrag* self = (ControlIconDrag*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'IsDisableCanbePick'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->IsDisableCanbePick();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'IsDisableCanbePick'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetDisableCanbePick of class  ControlIconDrag */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlIconDrag_SetDisableCanbePick00
static int tolua_CompileToLua_ControlIconDrag_SetDisableCanbePick00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlIconDrag",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlIconDrag* self = (ControlIconDrag*)  tolua_tousertype(tolua_S,1,0);
  bool b = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetDisableCanbePick'",NULL);
#endif
  {
   self->SetDisableCanbePick(b);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetDisableCanbePick'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetHeightShowMaxCnt of class  ControlIconDrag */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlIconDrag_SetHeightShowMaxCnt00
static int tolua_CompileToLua_ControlIconDrag_SetHeightShowMaxCnt00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlIconDrag",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlIconDrag* self = (ControlIconDrag*)  tolua_tousertype(tolua_S,1,0);
  int max = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetHeightShowMaxCnt'",NULL);
#endif
  {
   self->SetHeightShowMaxCnt(max);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetHeightShowMaxCnt'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetEnableRowCnt of class  ControlIconDrag */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlIconDrag_SetEnableRowCnt00
static int tolua_CompileToLua_ControlIconDrag_SetEnableRowCnt00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlIconDrag",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlIconDrag* self = (ControlIconDrag*)  tolua_tousertype(tolua_S,1,0);
  int cnt = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetEnableRowCnt'",NULL);
#endif
  {
   self->SetEnableRowCnt(cnt);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetEnableRowCnt'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetNotMsgClick of class  ControlIconDrag */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlIconDrag_SetNotMsgClick00
static int tolua_CompileToLua_ControlIconDrag_SetNotMsgClick00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlIconDrag",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlIconDrag* self = (ControlIconDrag*)  tolua_tousertype(tolua_S,1,0);
  bool b = ((bool)  tolua_toboolean(tolua_S,2,true));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetNotMsgClick'",NULL);
#endif
  {
   self->SetNotMsgClick(b);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetNotMsgClick'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: OnLDBClick of class  ControlIconDrag */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlIconDrag_OnLDBClick00
static int tolua_CompileToLua_ControlIconDrag_OnLDBClick00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlIconDrag",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isusertype(tolua_S,4,"ControlIconDrag::S_ListImg",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,5,"ControlObject",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlIconDrag* self = (ControlIconDrag*)  tolua_tousertype(tolua_S,1,0);
  const int nX = ((const int)  tolua_tonumber(tolua_S,2,0));
  const int nY = ((const int)  tolua_tonumber(tolua_S,3,0));
  OUT IN ControlIconDrag::S_ListImg* pItem = ((OUT IN ControlIconDrag::S_ListImg*)  tolua_tousertype(tolua_S,4,0));
  IN ControlObject* pSender = ((IN ControlObject*)  tolua_tousertype(tolua_S,5,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'OnLDBClick'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->OnLDBClick(nX,nY,pItem,pSender);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'OnLDBClick'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Refeash of class  ControlIconDrag */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlIconDrag_Refeash00
static int tolua_CompileToLua_ControlIconDrag_Refeash00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlIconDrag",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlIconDrag* self = (ControlIconDrag*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Refeash'",NULL);
#endif
  {
   int tolua_ret = (int)  self->Refeash();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Refeash'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: InitItemDate of class  ControlIconDrag */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlIconDrag_InitItemDate00
static int tolua_CompileToLua_ControlIconDrag_InitItemDate00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlIconDrag",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlIconDrag* self = (ControlIconDrag*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'InitItemDate'",NULL);
#endif
  {
   self->InitItemDate();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'InitItemDate'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: delete of class  ControlIconDrag */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlIconDrag_delete00
static int tolua_CompileToLua_ControlIconDrag_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlIconDrag",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlIconDrag* self = (ControlIconDrag*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'",NULL);
#endif
  delete self;
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Render of class  ControlIconDragManager */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlIconDragManager_Render00
static int tolua_CompileToLua_ControlIconDragManager_Render00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlIconDragManager",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlIconDragManager* self = (ControlIconDragManager*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Render'",NULL);
#endif
  {
   self->Render();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Render'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Run of class  ControlIconDragManager */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlIconDragManager_Run00
static int tolua_CompileToLua_ControlIconDragManager_Run00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlIconDragManager",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlIconDragManager* self = (ControlIconDragManager*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Run'",NULL);
#endif
  {
   self->Run();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Run'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: OnMouseMove of class  ControlIconDragManager */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlIconDragManager_OnMouseMove00
static int tolua_CompileToLua_ControlIconDragManager_OnMouseMove00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlIconDragManager",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"UINT",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlIconDragManager* self = (ControlIconDragManager*)  tolua_tousertype(tolua_S,1,0);
  UINT nFlags = *((UINT*)  tolua_tousertype(tolua_S,2,0));
  const int nX = ((const int)  tolua_tonumber(tolua_S,3,0));
  const int nY = ((const int)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'OnMouseMove'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->OnMouseMove(nFlags,nX,nY);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'OnMouseMove'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: OnLButtonDown of class  ControlIconDragManager */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlIconDragManager_OnLButtonDown00
static int tolua_CompileToLua_ControlIconDragManager_OnLButtonDown00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlIconDragManager",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"UINT",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlIconDragManager* self = (ControlIconDragManager*)  tolua_tousertype(tolua_S,1,0);
  UINT nFlags = *((UINT*)  tolua_tousertype(tolua_S,2,0));
  const int nX = ((const int)  tolua_tonumber(tolua_S,3,0));
  const int nY = ((const int)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'OnLButtonDown'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->OnLButtonDown(nFlags,nX,nY);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'OnLButtonDown'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: OnRButtonDown of class  ControlIconDragManager */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlIconDragManager_OnRButtonDown00
static int tolua_CompileToLua_ControlIconDragManager_OnRButtonDown00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlIconDragManager",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"UINT",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlIconDragManager* self = (ControlIconDragManager*)  tolua_tousertype(tolua_S,1,0);
  UINT nFlags = *((UINT*)  tolua_tousertype(tolua_S,2,0));
  const int nX = ((const int)  tolua_tonumber(tolua_S,3,0));
  const int nY = ((const int)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'OnRButtonDown'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->OnRButtonDown(nFlags,nX,nY);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'OnRButtonDown'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: OnLButtonUp of class  ControlIconDragManager */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlIconDragManager_OnLButtonUp00
static int tolua_CompileToLua_ControlIconDragManager_OnLButtonUp00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlIconDragManager",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"UINT",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isboolean(tolua_S,5,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,6,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,7,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlIconDragManager* self = (ControlIconDragManager*)  tolua_tousertype(tolua_S,1,0);
  UINT nFlags = *((UINT*)  tolua_tousertype(tolua_S,2,0));
  const int nX = ((const int)  tolua_tonumber(tolua_S,3,0));
  const int nY = ((const int)  tolua_tonumber(tolua_S,4,0));
  bool otheruser = ((bool)  tolua_toboolean(tolua_S,5,0));
  int index = ((int)  tolua_tonumber(tolua_S,6,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'OnLButtonUp'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->OnLButtonUp(nFlags,nX,nY,otheruser,index);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'OnLButtonUp'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: OnRButtonUp of class  ControlIconDragManager */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlIconDragManager_OnRButtonUp00
static int tolua_CompileToLua_ControlIconDragManager_OnRButtonUp00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlIconDragManager",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"UINT",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlIconDragManager* self = (ControlIconDragManager*)  tolua_tousertype(tolua_S,1,0);
  UINT nFlags = *((UINT*)  tolua_tousertype(tolua_S,2,0));
  const int nX = ((const int)  tolua_tonumber(tolua_S,3,0));
  const int nY = ((const int)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'OnRButtonUp'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->OnRButtonUp(nFlags,nX,nY);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'OnRButtonUp'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: OnLButtonDBClick of class  ControlIconDragManager */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlIconDragManager_OnLButtonDBClick00
static int tolua_CompileToLua_ControlIconDragManager_OnLButtonDBClick00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlIconDragManager",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"UINT",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlIconDragManager* self = (ControlIconDragManager*)  tolua_tousertype(tolua_S,1,0);
  UINT nFlags = *((UINT*)  tolua_tousertype(tolua_S,2,0));
  const int nX = ((const int)  tolua_tonumber(tolua_S,3,0));
  const int nY = ((const int)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'OnLButtonDBClick'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->OnLButtonDBClick(nFlags,nX,nY);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'OnLButtonDBClick'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: OnRButtonDBClick of class  ControlIconDragManager */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlIconDragManager_OnRButtonDBClick00
static int tolua_CompileToLua_ControlIconDragManager_OnRButtonDBClick00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlIconDragManager",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"UINT",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlIconDragManager* self = (ControlIconDragManager*)  tolua_tousertype(tolua_S,1,0);
  UINT nFlags = *((UINT*)  tolua_tousertype(tolua_S,2,0));
  const int nX = ((const int)  tolua_tonumber(tolua_S,3,0));
  const int nY = ((const int)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'OnRButtonDBClick'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->OnRButtonDBClick(nFlags,nX,nY);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'OnRButtonDBClick'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetDrag of class  ControlIconDragManager */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlIconDragManager_SetDrag00
static int tolua_CompileToLua_ControlIconDragManager_SetDrag00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlIconDragManager",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"ControlIconDrag",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"ControlIconDrag::S_ListImg",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,4,"const POINT",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,5,"const POINT",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,6,"const POINT",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,7,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlIconDragManager* self = (ControlIconDragManager*)  tolua_tousertype(tolua_S,1,0);
  IN ControlIconDrag* pList = ((IN ControlIconDrag*)  tolua_tousertype(tolua_S,2,0));
  IN ControlIconDrag::S_ListImg* pItem = ((IN ControlIconDrag::S_ListImg*)  tolua_tousertype(tolua_S,3,0));
  const POINT ptItemPos = *((const POINT*)  tolua_tousertype(tolua_S,4,0));
  const POINT* realPos = ((const POINT*)  tolua_tousertype(tolua_S,5,0));
  const POINT* mousePos = ((const POINT*)  tolua_tousertype(tolua_S,6,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetDrag'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->SetDrag(pList,pItem,ptItemPos,*realPos,*mousePos);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetDrag'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetDstListImg of class  ControlIconDragManager */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlIconDragManager_SetDstListImg00
static int tolua_CompileToLua_ControlIconDragManager_SetDstListImg00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlIconDragManager",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"ControlIconDrag",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlIconDragManager* self = (ControlIconDragManager*)  tolua_tousertype(tolua_S,1,0);
  IN ControlIconDrag* pList = ((IN ControlIconDrag*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetDstListImg'",NULL);
#endif
  {
   self->SetDstListImg(pList);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetDstListImg'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: ClearDrag of class  ControlIconDragManager */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlIconDragManager_ClearDrag00
static int tolua_CompileToLua_ControlIconDragManager_ClearDrag00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlIconDragManager",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlIconDragManager* self = (ControlIconDragManager*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'ClearDrag'",NULL);
#endif
  {
   self->ClearDrag();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'ClearDrag'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetCurItem of class  ControlIconDragManager */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlIconDragManager_GetCurItem00
static int tolua_CompileToLua_ControlIconDragManager_GetCurItem00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlIconDragManager",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlIconDragManager* self = (ControlIconDragManager*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetCurItem'",NULL);
#endif
  {
   ControlIconDrag::S_ListImg* tolua_ret = (ControlIconDrag::S_ListImg*)  self->GetCurItem();
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"ControlIconDrag::S_ListImg");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetCurItem'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: m_pLastSelItem of class  ControlIconDragManager */
#ifndef TOLUA_DISABLE_tolua_get_ControlIconDragManager_m_pLastSelItem_ptr
static int tolua_get_ControlIconDragManager_m_pLastSelItem_ptr(lua_State* tolua_S)
{
  ControlIconDragManager* self = (ControlIconDragManager*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_pLastSelItem'",NULL);
#endif
  tolua_pushusertype(tolua_S,(void*)self->m_pLastSelItem,"ControlIconDrag::S_ListImg");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: m_pLastSelItem of class  ControlIconDragManager */
#ifndef TOLUA_DISABLE_tolua_set_ControlIconDragManager_m_pLastSelItem_ptr
static int tolua_set_ControlIconDragManager_m_pLastSelItem_ptr(lua_State* tolua_S)
{
  ControlIconDragManager* self = (ControlIconDragManager*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_pLastSelItem'",NULL);
  if (!tolua_isusertype(tolua_S,2,"ControlIconDrag::S_ListImg",0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->m_pLastSelItem = ((ControlIconDrag::S_ListImg*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  ControlIconDragManager */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlIconDragManager_new00
static int tolua_CompileToLua_ControlIconDragManager_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"ControlIconDragManager",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   ControlIconDragManager* tolua_ret = (ControlIconDragManager*)  new ControlIconDragManager();
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"ControlIconDragManager");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  ControlIconDragManager */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlIconDragManager_new00_local
static int tolua_CompileToLua_ControlIconDragManager_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"ControlIconDragManager",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   ControlIconDragManager* tolua_ret = (ControlIconDragManager*)  new ControlIconDragManager();
   tolua_pushusertype_and_takeownership(tolua_S,(void *)tolua_ret,"ControlIconDragManager");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: delete of class  ControlIconDragManager */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlIconDragManager_delete00
static int tolua_CompileToLua_ControlIconDragManager_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlIconDragManager",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlIconDragManager* self = (ControlIconDragManager*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'",NULL);
#endif
  delete self;
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: theIconDragManager */
#ifndef TOLUA_DISABLE_tolua_get_theIconDragManager
static int tolua_get_theIconDragManager(lua_State* tolua_S)
{
  tolua_pushusertype(tolua_S,(void*)&theIconDragManager,"ControlIconDragManager");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: theIconDragManager */
#ifndef TOLUA_DISABLE_tolua_set_theIconDragManager
static int tolua_set_theIconDragManager(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!tolua_isusertype(tolua_S,2,"ControlIconDragManager",0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  theIconDragManager = *((ControlIconDragManager*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  S_List */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlList_S_List_new00
static int tolua_CompileToLua_ControlList_S_List_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"ControlList::S_List",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   ControlList::S_List* tolua_ret = (ControlList::S_List*)  new ControlList::S_List();
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"ControlList::S_List");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  S_List */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlList_S_List_new00_local
static int tolua_CompileToLua_ControlList_S_List_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"ControlList::S_List",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   ControlList::S_List* tolua_ret = (ControlList::S_List*)  new ControlList::S_List();
   tolua_pushusertype_and_takeownership(tolua_S,(void *)tolua_ret,"ControlList::S_List");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: clear of class  S_List */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlList_S_List_clear00
static int tolua_CompileToLua_ControlList_S_List_clear00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlList::S_List",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlList::S_List* self = (ControlList::S_List*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'clear'",NULL);
#endif
  {
   self->clear();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'clear'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetData of class  S_List */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlList_S_List_SetData00
static int tolua_CompileToLua_ControlList_S_List_SetData00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlList::S_List",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,1,&tolua_err) ||
     !tolua_isuserdata(tolua_S,4,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,1,&tolua_err) ||
     !tolua_isstring(tolua_S,6,1,&tolua_err) ||
     !tolua_isstring(tolua_S,7,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,8,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,9,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlList::S_List* self = (ControlList::S_List*)  tolua_tousertype(tolua_S,1,0);
  IN  const char* szText = ((IN  const char*)  tolua_tostring(tolua_S,2,0));
  int nID = ((int)  tolua_tonumber(tolua_S,3,0));
  IN void* pData = ((IN void*)  tolua_touserdata(tolua_S,4,NULL));
  int col = ((int)  tolua_tonumber(tolua_S,5,0));
  char* szNote = ((char*)  tolua_tostring(tolua_S,6,NULL));
  char* hyberItemInfo = ((char*)  tolua_tostring(tolua_S,7,NULL));
  int hyberItemCnt = ((int)  tolua_tonumber(tolua_S,8,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetData'",NULL);
#endif
  {
   self->SetData(szText,nID,pData,col,szNote,hyberItemInfo,hyberItemCnt);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetData'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setColor of class  S_List */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlList_S_List_setColor00
static int tolua_CompileToLua_ControlList_S_List_setColor00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlList::S_List",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"D3DCOLOR",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlList::S_List* self = (ControlList::S_List*)  tolua_tousertype(tolua_S,1,0);
  D3DCOLOR col = *((D3DCOLOR*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setColor'",NULL);
#endif
  {
   self->setColor(col);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setColor'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setTextCustomKey of class  S_List */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlList_S_List_setTextCustomKey00
static int tolua_CompileToLua_ControlList_S_List_setTextCustomKey00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlList::S_List",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlList::S_List* self = (ControlList::S_List*)  tolua_tousertype(tolua_S,1,0);
  const char* key = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setTextCustomKey'",NULL);
#endif
  {
   self->setTextCustomKey(key);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setTextCustomKey'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setTip of class  S_List */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlList_S_List_setTip00
static int tolua_CompileToLua_ControlList_S_List_setTip00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlList::S_List",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"DWORD",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlList::S_List* self = (ControlList::S_List*)  tolua_tousertype(tolua_S,1,0);
  const char* tip = ((const char*)  tolua_tostring(tolua_S,2,0));
  DWORD dwAlign = *((DWORD*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setTip'",NULL);
#endif
  {
   self->setTip(tip,dwAlign);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setTip'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setTip of class  S_List */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlList_S_List_setTip01
static int tolua_CompileToLua_ControlList_S_List_setTip01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlList::S_List",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  ControlList::S_List* self = (ControlList::S_List*)  tolua_tousertype(tolua_S,1,0);
  const char* tip = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setTip'",NULL);
#endif
  {
   self->setTip(tip);
  }
 }
 return 0;
tolua_lerror:
 return tolua_CompileToLua_ControlList_S_List_setTip00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: setIsOnline of class  S_List */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlList_S_List_setIsOnline00
static int tolua_CompileToLua_ControlList_S_List_setIsOnline00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlList::S_List",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlList::S_List* self = (ControlList::S_List*)  tolua_tousertype(tolua_S,1,0);
  bool online = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setIsOnline'",NULL);
#endif
  {
   self->setIsOnline(online);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setIsOnline'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: m_szText of class  S_List */
#ifndef TOLUA_DISABLE_tolua_get_ControlList__S_List_m_szText
static int tolua_get_ControlList__S_List_m_szText(lua_State* tolua_S)
{
  ControlList::S_List* self = (ControlList::S_List*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_szText'",NULL);
#endif
  tolua_pushstring(tolua_S,(const char*)self->m_szText);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: m_szText of class  S_List */
#ifndef TOLUA_DISABLE_tolua_set_ControlList__S_List_m_szText
static int tolua_set_ControlList__S_List_m_szText(lua_State* tolua_S)
{
  ControlList::S_List* self = (ControlList::S_List*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_szText'",NULL);
  if (!tolua_istable(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
 strncpy(self->m_szText,tolua_tostring(tolua_S,2,0),256-1);
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: m_szNote of class  S_List */
#ifndef TOLUA_DISABLE_tolua_get_ControlList__S_List_m_szNote
static int tolua_get_ControlList__S_List_m_szNote(lua_State* tolua_S)
{
  ControlList::S_List* self = (ControlList::S_List*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_szNote'",NULL);
#endif
  tolua_pushstring(tolua_S,(const char*)self->m_szNote);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: m_szNote of class  S_List */
#ifndef TOLUA_DISABLE_tolua_set_ControlList__S_List_m_szNote
static int tolua_set_ControlList__S_List_m_szNote(lua_State* tolua_S)
{
  ControlList::S_List* self = (ControlList::S_List*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_szNote'",NULL);
  if (!tolua_istable(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
 strncpy(self->m_szNote,tolua_tostring(tolua_S,2,0),32-1);
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: m_nID of class  S_List */
#ifndef TOLUA_DISABLE_tolua_get_ControlList__S_List_m_nID
static int tolua_get_ControlList__S_List_m_nID(lua_State* tolua_S)
{
  ControlList::S_List* self = (ControlList::S_List*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_nID'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->m_nID);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: m_nID of class  S_List */
#ifndef TOLUA_DISABLE_tolua_set_ControlList__S_List_m_nID
static int tolua_set_ControlList__S_List_m_nID(lua_State* tolua_S)
{
  ControlList::S_List* self = (ControlList::S_List*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_nID'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->m_nID = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: m_pData of class  S_List */
#ifndef TOLUA_DISABLE_tolua_get_ControlList__S_List_m_pData
static int tolua_get_ControlList__S_List_m_pData(lua_State* tolua_S)
{
  ControlList::S_List* self = (ControlList::S_List*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_pData'",NULL);
#endif
  tolua_pushuserdata(tolua_S,(void*)self->m_pData);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: m_pData of class  S_List */
#ifndef TOLUA_DISABLE_tolua_set_ControlList__S_List_m_pData
static int tolua_set_ControlList__S_List_m_pData(lua_State* tolua_S)
{
  ControlList::S_List* self = (ControlList::S_List*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_pData'",NULL);
  if (!tolua_isuserdata(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->m_pData = ((void*)  tolua_touserdata(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: _hyberItemInfo of class  S_List */
#ifndef TOLUA_DISABLE_tolua_get_CompileToLua_ControlList_S_List__hyberItemInfo
static int tolua_get_CompileToLua_ControlList_S_List__hyberItemInfo(lua_State* tolua_S)
{
 int tolua_index;
  ControlList::S_List* self;
 lua_pushstring(tolua_S,".self");
 lua_rawget(tolua_S,1);
 self = (ControlList::S_List*)  lua_touserdata(tolua_S,-1);
#ifndef TOLUA_RELEASE
 {
  tolua_Error tolua_err;
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in array indexing.",&tolua_err);
 }
#endif
 tolua_index = (int)tolua_tonumber(tolua_S,2,0)-1;
#ifndef TOLUA_RELEASE
 if (tolua_index<0 || tolua_index>=ITEM_HYBER_MAX_CNT)
  tolua_error(tolua_S,"array indexing out of range.",NULL);
#endif
 tolua_pushusertype(tolua_S,(void*)&self->_hyberItemInfo[tolua_index],"SCharItem");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: _hyberItemInfo of class  S_List */
#ifndef TOLUA_DISABLE_tolua_set_CompileToLua_ControlList_S_List__hyberItemInfo
static int tolua_set_CompileToLua_ControlList_S_List__hyberItemInfo(lua_State* tolua_S)
{
 int tolua_index;
  ControlList::S_List* self;
 lua_pushstring(tolua_S,".self");
 lua_rawget(tolua_S,1);
 self = (ControlList::S_List*)  lua_touserdata(tolua_S,-1);
#ifndef TOLUA_RELEASE
 {
  tolua_Error tolua_err;
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in array indexing.",&tolua_err);
 }
#endif
 tolua_index = (int)tolua_tonumber(tolua_S,2,0)-1;
#ifndef TOLUA_RELEASE
 if (tolua_index<0 || tolua_index>=ITEM_HYBER_MAX_CNT)
  tolua_error(tolua_S,"array indexing out of range.",NULL);
#endif
  self->_hyberItemInfo[tolua_index] = *((SCharItem*)  tolua_tousertype(tolua_S,3,0));
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: m_colTextCol of class  S_List */
#ifndef TOLUA_DISABLE_tolua_get_ControlList__S_List_m_colTextCol
static int tolua_get_ControlList__S_List_m_colTextCol(lua_State* tolua_S)
{
  ControlList::S_List* self = (ControlList::S_List*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_colTextCol'",NULL);
#endif
  tolua_pushusertype(tolua_S,(void*)&self->m_colTextCol,"D3DCOLOR");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: m_colTextCol of class  S_List */
#ifndef TOLUA_DISABLE_tolua_set_ControlList__S_List_m_colTextCol
static int tolua_set_ControlList__S_List_m_colTextCol(lua_State* tolua_S)
{
  ControlList::S_List* self = (ControlList::S_List*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_colTextCol'",NULL);
  if (!tolua_isusertype(tolua_S,2,"D3DCOLOR",0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->m_colTextCol = *((D3DCOLOR*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: _bOnline of class  S_List */
#ifndef TOLUA_DISABLE_tolua_get_ControlList__S_List__bOnline
static int tolua_get_ControlList__S_List__bOnline(lua_State* tolua_S)
{
  ControlList::S_List* self = (ControlList::S_List*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable '_bOnline'",NULL);
#endif
  tolua_pushboolean(tolua_S,(bool)self->_bOnline);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: _bOnline of class  S_List */
#ifndef TOLUA_DISABLE_tolua_set_ControlList__S_List__bOnline
static int tolua_set_ControlList__S_List__bOnline(lua_State* tolua_S)
{
  ControlList::S_List* self = (ControlList::S_List*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable '_bOnline'",NULL);
  if (!tolua_isboolean(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->_bOnline = ((bool)  tolua_toboolean(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: m_pTipInfo of class  S_List */
#ifndef TOLUA_DISABLE_tolua_get_ControlList__S_List_m_pTipInfo_ptr
static int tolua_get_ControlList__S_List_m_pTipInfo_ptr(lua_State* tolua_S)
{
  ControlList::S_List* self = (ControlList::S_List*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_pTipInfo'",NULL);
#endif
  tolua_pushusertype(tolua_S,(void*)self->m_pTipInfo,"S_TextTipInfo");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: m_pTipInfo of class  S_List */
#ifndef TOLUA_DISABLE_tolua_set_ControlList__S_List_m_pTipInfo_ptr
static int tolua_set_ControlList__S_List_m_pTipInfo_ptr(lua_State* tolua_S)
{
  ControlList::S_List* self = (ControlList::S_List*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_pTipInfo'",NULL);
  if (!tolua_isusertype(tolua_S,2,"S_TextTipInfo",0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->m_pTipInfo = ((S_TextTipInfo*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: UseSelColor of class  S_List */
#ifndef TOLUA_DISABLE_tolua_get_ControlList__S_List_UseSelColor
static int tolua_get_ControlList__S_List_UseSelColor(lua_State* tolua_S)
{
  ControlList::S_List* self = (ControlList::S_List*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'UseSelColor'",NULL);
#endif
  tolua_pushusertype(tolua_S,(void*)&self->UseSelColor,"BOOL");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: UseSelColor of class  S_List */
#ifndef TOLUA_DISABLE_tolua_set_ControlList__S_List_UseSelColor
static int tolua_set_ControlList__S_List_UseSelColor(lua_State* tolua_S)
{
  ControlList::S_List* self = (ControlList::S_List*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'UseSelColor'",NULL);
  if (!tolua_isusertype(tolua_S,2,"BOOL",0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->UseSelColor = *((BOOL*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* method: Render of class  ControlList */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlList_Render00
static int tolua_CompileToLua_ControlList_Render00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlList",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlList* self = (ControlList*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Render'",NULL);
#endif
  {
   self->Render();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Render'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: PtInObject of class  ControlList */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlList_PtInObject00
static int tolua_CompileToLua_ControlList_PtInObject00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlList",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlList* self = (ControlList*)  tolua_tousertype(tolua_S,1,0);
  const int nX = ((const int)  tolua_tonumber(tolua_S,2,0));
  const int nY = ((const int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'PtInObject'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->PtInObject(nX,nY);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'PtInObject'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: InitUIData of class  ControlList */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlList_InitUIData00
static int tolua_CompileToLua_ControlList_InitUIData00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlList",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"ControlObject",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"S_BaseData",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlList* self = (ControlList*)  tolua_tousertype(tolua_S,1,0);
  IN ControlObject* pFather = ((IN ControlObject*)  tolua_tousertype(tolua_S,2,0));
  IN S_BaseData* pData = ((IN S_BaseData*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'InitUIData'",NULL);
#endif
  {
   self->InitUIData(pFather,pData);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'InitUIData'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: OnMouseMove of class  ControlList */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlList_OnMouseMove00
static int tolua_CompileToLua_ControlList_OnMouseMove00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlList",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"UINT",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlList* self = (ControlList*)  tolua_tousertype(tolua_S,1,0);
  UINT nFlags = *((UINT*)  tolua_tousertype(tolua_S,2,0));
  const int nX = ((const int)  tolua_tonumber(tolua_S,3,0));
  const int nY = ((const int)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'OnMouseMove'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->OnMouseMove(nFlags,nX,nY);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'OnMouseMove'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: OnMouseWheel of class  ControlList */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlList_OnMouseWheel00
static int tolua_CompileToLua_ControlList_OnMouseWheel00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlList",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlList* self = (ControlList*)  tolua_tousertype(tolua_S,1,0);
  bool bUp = ((bool)  tolua_toboolean(tolua_S,2,0));
  const int nX = ((const int)  tolua_tonumber(tolua_S,3,0));
  const int nY = ((const int)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'OnMouseWheel'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->OnMouseWheel(bUp,nX,nY);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'OnMouseWheel'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: OnLButtonDown of class  ControlList */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlList_OnLButtonDown00
static int tolua_CompileToLua_ControlList_OnLButtonDown00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlList",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"UINT",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlList* self = (ControlList*)  tolua_tousertype(tolua_S,1,0);
  UINT nFlags = *((UINT*)  tolua_tousertype(tolua_S,2,0));
  const int nX = ((const int)  tolua_tonumber(tolua_S,3,0));
  const int nY = ((const int)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'OnLButtonDown'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->OnLButtonDown(nFlags,nX,nY);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'OnLButtonDown'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: OnLButtonUp of class  ControlList */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlList_OnLButtonUp00
static int tolua_CompileToLua_ControlList_OnLButtonUp00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlList",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"UINT",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlList* self = (ControlList*)  tolua_tousertype(tolua_S,1,0);
  UINT nFlags = *((UINT*)  tolua_tousertype(tolua_S,2,0));
  const int nX = ((const int)  tolua_tonumber(tolua_S,3,0));
  const int nY = ((const int)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'OnLButtonUp'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->OnLButtonUp(nFlags,nX,nY);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'OnLButtonUp'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: OnLButtonDBClick of class  ControlList */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlList_OnLButtonDBClick00
static int tolua_CompileToLua_ControlList_OnLButtonDBClick00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlList",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"UINT",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlList* self = (ControlList*)  tolua_tousertype(tolua_S,1,0);
  UINT nFlags = *((UINT*)  tolua_tousertype(tolua_S,2,0));
  const int nX = ((const int)  tolua_tonumber(tolua_S,3,0));
  const int nY = ((const int)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'OnLButtonDBClick'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->OnLButtonDBClick(nFlags,nX,nY);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'OnLButtonDBClick'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: OnRButtonDown of class  ControlList */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlList_OnRButtonDown00
static int tolua_CompileToLua_ControlList_OnRButtonDown00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlList",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"UINT",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlList* self = (ControlList*)  tolua_tousertype(tolua_S,1,0);
  UINT nFlags = *((UINT*)  tolua_tousertype(tolua_S,2,0));
  const int nX = ((const int)  tolua_tonumber(tolua_S,3,0));
  const int nY = ((const int)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'OnRButtonDown'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->OnRButtonDown(nFlags,nX,nY);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'OnRButtonDown'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: OnKeyDown of class  ControlList */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlList_OnKeyDown00
static int tolua_CompileToLua_ControlList_OnKeyDown00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlList",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"UINT",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlList* self = (ControlList*)  tolua_tousertype(tolua_S,1,0);
  UINT nChar = *((UINT*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'OnKeyDown'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->OnKeyDown(nChar);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'OnKeyDown'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: AddItem of class  ControlList */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlList_AddItem00
static int tolua_CompileToLua_ControlList_AddItem00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlList",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"const ControlList::S_List",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,3,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlList* self = (ControlList*)  tolua_tousertype(tolua_S,1,0);
  IN  const ControlList::S_List* pItem = ((IN  const ControlList::S_List*)  tolua_tousertype(tolua_S,2,0));
  const bool bMoveDonw = ((const bool)  tolua_toboolean(tolua_S,3,true));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'AddItem'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->AddItem(pItem,bMoveDonw);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'AddItem'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: AddArrayItem of class  ControlList */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlList_AddArrayItem00
static int tolua_CompileToLua_ControlList_AddArrayItem00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlList",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"const ControlList::S_List",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isboolean(tolua_S,4,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlList* self = (ControlList*)  tolua_tousertype(tolua_S,1,0);
  IN  const ControlList::S_List* pItem = ((IN  const ControlList::S_List*)  tolua_tousertype(tolua_S,2,0));
  const int nItemCount = ((const int)  tolua_tonumber(tolua_S,3,0));
  const bool bMoveDonw = ((const bool)  tolua_toboolean(tolua_S,4,true));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'AddArrayItem'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->AddArrayItem(pItem,nItemCount,bMoveDonw);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'AddArrayItem'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: ResetItem of class  ControlList */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlList_ResetItem00
static int tolua_CompileToLua_ControlList_ResetItem00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlList",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"const ControlList::S_List",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlList* self = (ControlList*)  tolua_tousertype(tolua_S,1,0);
  IN  const ControlList::S_List* pItem = ((IN  const ControlList::S_List*)  tolua_tousertype(tolua_S,2,0));
  const int nItemCount = ((const int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'ResetItem'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->ResetItem(pItem,nItemCount);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'ResetItem'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetCurSelItem of class  ControlList */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlList_GetCurSelItem00
static int tolua_CompileToLua_ControlList_GetCurSelItem00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlList",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlList* self = (ControlList*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetCurSelItem'",NULL);
#endif
  {
   ControlList::S_List* tolua_ret = (ControlList::S_List*)  self->GetCurSelItem();
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"ControlList::S_List");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetCurSelItem'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetOldCurSelItem of class  ControlList */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlList_GetOldCurSelItem00
static int tolua_CompileToLua_ControlList_GetOldCurSelItem00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlList",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlList* self = (ControlList*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetOldCurSelItem'",NULL);
#endif
  {
   ControlList::S_List* tolua_ret = (ControlList::S_List*)  self->GetOldCurSelItem();
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"ControlList::S_List");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetOldCurSelItem'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: FindItemByID of class  ControlList */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlList_FindItemByID00
static int tolua_CompileToLua_ControlList_FindItemByID00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlList",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlList* self = (ControlList*)  tolua_tousertype(tolua_S,1,0);
  const int nID = ((const int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'FindItemByID'",NULL);
#endif
  {
   ControlList::S_List* tolua_ret = (ControlList::S_List*)  self->FindItemByID(nID);
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"ControlList::S_List");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'FindItemByID'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setItemTip of class  ControlList */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlList_setItemTip00
static int tolua_CompileToLua_ControlList_setItemTip00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlList",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlList* self = (ControlList*)  tolua_tousertype(tolua_S,1,0);
  int index = ((int)  tolua_tonumber(tolua_S,2,0));
  const char* tip = ((const char*)  tolua_tostring(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setItemTip'",NULL);
#endif
  {
   self->setItemTip(index,tip);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setItemTip'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: FindItemByItem of class  ControlList */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlList_FindItemByItem00
static int tolua_CompileToLua_ControlList_FindItemByItem00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlList",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlList* self = (ControlList*)  tolua_tousertype(tolua_S,1,0);
  const char* item = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'FindItemByItem'",NULL);
#endif
  {
   int tolua_ret = (int)  self->FindItemByItem(item);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'FindItemByItem'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetCurSelIndex of class  ControlList */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlList_GetCurSelIndex00
static int tolua_CompileToLua_ControlList_GetCurSelIndex00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlList",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlList* self = (ControlList*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetCurSelIndex'",NULL);
#endif
  {
   int tolua_ret = (int)  self->GetCurSelIndex();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetCurSelIndex'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetCurSelIndex of class  ControlList */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlList_SetCurSelIndex00
static int tolua_CompileToLua_ControlList_SetCurSelIndex00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlList",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlList* self = (ControlList*)  tolua_tousertype(tolua_S,1,0);
  const int nIndex = ((const int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetCurSelIndex'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->SetCurSelIndex(nIndex);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetCurSelIndex'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Clear of class  ControlList */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlList_Clear00
static int tolua_CompileToLua_ControlList_Clear00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlList",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlList* self = (ControlList*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Clear'",NULL);
#endif
  {
   self->Clear();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Clear'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetSelectChangeFun_2lua of class  ControlList */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlList_SetSelectChangeFun_2lua00
static int tolua_CompileToLua_ControlList_SetSelectChangeFun_2lua00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlList",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlList* self = (ControlList*)  tolua_tousertype(tolua_S,1,0);
  const char* luaTable = ((const char*)  tolua_tostring(tolua_S,2,0));
  const char* funName = ((const char*)  tolua_tostring(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetSelectChangeFun_2lua'",NULL);
#endif
  {
   self->SetSelectChangeFun_2lua(luaTable,funName);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetSelectChangeFun_2lua'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetRBClickFun_2lua of class  ControlList */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlList_SetRBClickFun_2lua00
static int tolua_CompileToLua_ControlList_SetRBClickFun_2lua00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlList",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlList* self = (ControlList*)  tolua_tousertype(tolua_S,1,0);
  const char* luaTable = ((const char*)  tolua_tostring(tolua_S,2,0));
  const char* funName = ((const char*)  tolua_tostring(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetRBClickFun_2lua'",NULL);
#endif
  {
   self->SetRBClickFun_2lua(luaTable,funName);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetRBClickFun_2lua'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetShiftRBClickFun_2lua of class  ControlList */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlList_SetShiftRBClickFun_2lua00
static int tolua_CompileToLua_ControlList_SetShiftRBClickFun_2lua00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlList",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlList* self = (ControlList*)  tolua_tousertype(tolua_S,1,0);
  const char* luaTable = ((const char*)  tolua_tostring(tolua_S,2,0));
  const char* funName = ((const char*)  tolua_tostring(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetShiftRBClickFun_2lua'",NULL);
#endif
  {
   self->SetShiftRBClickFun_2lua(luaTable,funName);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetShiftRBClickFun_2lua'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetShiftLBClickFun_2lua of class  ControlList */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlList_SetShiftLBClickFun_2lua00
static int tolua_CompileToLua_ControlList_SetShiftLBClickFun_2lua00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlList",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlList* self = (ControlList*)  tolua_tousertype(tolua_S,1,0);
  const char* luaTable = ((const char*)  tolua_tostring(tolua_S,2,0));
  const char* funName = ((const char*)  tolua_tostring(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetShiftLBClickFun_2lua'",NULL);
#endif
  {
   self->SetShiftLBClickFun_2lua(luaTable,funName);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetShiftLBClickFun_2lua'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetLDBClickFun_2lua of class  ControlList */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlList_SetLDBClickFun_2lua00
static int tolua_CompileToLua_ControlList_SetLDBClickFun_2lua00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlList",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlList* self = (ControlList*)  tolua_tousertype(tolua_S,1,0);
  const char* luaTable = ((const char*)  tolua_tostring(tolua_S,2,0));
  const char* funName = ((const char*)  tolua_tostring(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetLDBClickFun_2lua'",NULL);
#endif
  {
   self->SetLDBClickFun_2lua(luaTable,funName);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetLDBClickFun_2lua'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetHyberClickFun_2lua of class  ControlList */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlList_SetHyberClickFun_2lua00
static int tolua_CompileToLua_ControlList_SetHyberClickFun_2lua00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlList",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlList* self = (ControlList*)  tolua_tousertype(tolua_S,1,0);
  const char* luaTable = ((const char*)  tolua_tostring(tolua_S,2,0));
  const char* funName = ((const char*)  tolua_tostring(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetHyberClickFun_2lua'",NULL);
#endif
  {
   self->SetHyberClickFun_2lua(luaTable,funName);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetHyberClickFun_2lua'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetHyberRBtnDown_2lua of class  ControlList */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlList_SetHyberRBtnDown_2lua00
static int tolua_CompileToLua_ControlList_SetHyberRBtnDown_2lua00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlList",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlList* self = (ControlList*)  tolua_tousertype(tolua_S,1,0);
  const char* luaTable = ((const char*)  tolua_tostring(tolua_S,2,0));
  const char* funName = ((const char*)  tolua_tostring(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetHyberRBtnDown_2lua'",NULL);
#endif
  {
   self->SetHyberRBtnDown_2lua(luaTable,funName);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetHyberRBtnDown_2lua'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetHyberItemClick_2lua of class  ControlList */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlList_SetHyberItemClick_2lua00
static int tolua_CompileToLua_ControlList_SetHyberItemClick_2lua00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlList",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlList* self = (ControlList*)  tolua_tousertype(tolua_S,1,0);
  const char* luaTable = ((const char*)  tolua_tostring(tolua_S,2,0));
  const char* funName = ((const char*)  tolua_tostring(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetHyberItemClick_2lua'",NULL);
#endif
  {
   self->SetHyberItemClick_2lua(luaTable,funName);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetHyberItemClick_2lua'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: HaveSelBar of class  ControlList */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlList_HaveSelBar00
static int tolua_CompileToLua_ControlList_HaveSelBar00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlList",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isboolean(tolua_S,3,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlList* self = (ControlList*)  tolua_tousertype(tolua_S,1,0);
  const bool b = ((const bool)  tolua_toboolean(tolua_S,2,0));
  const bool bShow = ((const bool)  tolua_toboolean(tolua_S,3,LIST_SHOWBAR));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'HaveSelBar'",NULL);
#endif
  {
   self->HaveSelBar(b,bShow);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'HaveSelBar'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetScrollPos of class  ControlList */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlList_SetScrollPos00
static int tolua_CompileToLua_ControlList_SetScrollPos00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlList",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlList* self = (ControlList*)  tolua_tousertype(tolua_S,1,0);
  const int nX = ((const int)  tolua_tonumber(tolua_S,2,0));
  const int nY = ((const int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetScrollPos'",NULL);
#endif
  {
   self->SetScrollPos(nX,nY);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetScrollPos'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetItemMaxCount of class  ControlList */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlList_SetItemMaxCount00
static int tolua_CompileToLua_ControlList_SetItemMaxCount00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlList",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"const DWORD",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlList* self = (ControlList*)  tolua_tousertype(tolua_S,1,0);
  const DWORD dw = *((const DWORD*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetItemMaxCount'",NULL);
#endif
  {
   self->SetItemMaxCount(dw);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetItemMaxCount'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetItemMaxCount of class  ControlList */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlList_GetItemMaxCount00
static int tolua_CompileToLua_ControlList_GetItemMaxCount00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlList",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlList* self = (ControlList*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetItemMaxCount'",NULL);
#endif
  {
   int tolua_ret = (int)  self->GetItemMaxCount();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetItemMaxCount'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetItemShowCount of class  ControlList */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlList_SetItemShowCount00
static int tolua_CompileToLua_ControlList_SetItemShowCount00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlList",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlList* self = (ControlList*)  tolua_tousertype(tolua_S,1,0);
  const int nCount = ((const int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetItemShowCount'",NULL);
#endif
  {
   self->SetItemShowCount(nCount);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetItemShowCount'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetItemShowCount of class  ControlList */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlList_GetItemShowCount00
static int tolua_CompileToLua_ControlList_GetItemShowCount00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlList",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlList* self = (ControlList*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetItemShowCount'",NULL);
#endif
  {
   int tolua_ret = (int)  self->GetItemShowCount();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetItemShowCount'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetListItemHeight of class  ControlList */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlList_GetListItemHeight00
static int tolua_CompileToLua_ControlList_GetListItemHeight00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlList",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlList* self = (ControlList*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetListItemHeight'",NULL);
#endif
  {
   int tolua_ret = (int)  self->GetListItemHeight();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetListItemHeight'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetUIScrollBlend of class  ControlList */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlList_SetUIScrollBlend00
static int tolua_CompileToLua_ControlList_SetUIScrollBlend00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlList",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlList* self = (ControlList*)  tolua_tousertype(tolua_S,1,0);
  const int nBlend = ((const int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetUIScrollBlend'",NULL);
#endif
  {
   self->SetUIScrollBlend(nBlend);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetUIScrollBlend'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetScrollHeight of class  ControlList */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlList_SetScrollHeight00
static int tolua_CompileToLua_ControlList_SetScrollHeight00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlList",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlList* self = (ControlList*)  tolua_tousertype(tolua_S,1,0);
  const int nHeight = ((const int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetScrollHeight'",NULL);
#endif
  {
   self->SetScrollHeight(nHeight);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetScrollHeight'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetScrollValue of class  ControlList */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlList_SetScrollValue00
static int tolua_CompileToLua_ControlList_SetScrollValue00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlList",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlList* self = (ControlList*)  tolua_tousertype(tolua_S,1,0);
  int nValue = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetScrollValue'",NULL);
#endif
  {
   self->SetScrollValue(nValue);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetScrollValue'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetStartIndex of class  ControlList */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlList_GetStartIndex00
static int tolua_CompileToLua_ControlList_GetStartIndex00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlList",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlList* self = (ControlList*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetStartIndex'",NULL);
#endif
  {
   int tolua_ret = (int)  self->GetStartIndex();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetStartIndex'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetStartIndex of class  ControlList */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlList_SetStartIndex00
static int tolua_CompileToLua_ControlList_SetStartIndex00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlList",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlList* self = (ControlList*)  tolua_tousertype(tolua_S,1,0);
  int nStartIndex = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetStartIndex'",NULL);
#endif
  {
   self->SetStartIndex(nStartIndex);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetStartIndex'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetScrollVisable of class  ControlList */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlList_SetScrollVisable00
static int tolua_CompileToLua_ControlList_SetScrollVisable00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlList",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlList* self = (ControlList*)  tolua_tousertype(tolua_S,1,0);
  bool bShow = ((bool)  tolua_toboolean(tolua_S,2,true));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetScrollVisable'",NULL);
#endif
  {
   self->SetScrollVisable(bShow);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetScrollVisable'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetScrollBarEnable of class  ControlList */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlList_SetScrollBarEnable00
static int tolua_CompileToLua_ControlList_SetScrollBarEnable00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlList",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlList* self = (ControlList*)  tolua_tousertype(tolua_S,1,0);
  bool bEnable = ((bool)  tolua_toboolean(tolua_S,2,true));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetScrollBarEnable'",NULL);
#endif
  {
   self->SetScrollBarEnable(bEnable);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetScrollBarEnable'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetRBSelectEnable of class  ControlList */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlList_SetRBSelectEnable00
static int tolua_CompileToLua_ControlList_SetRBSelectEnable00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlList",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlList* self = (ControlList*)  tolua_tousertype(tolua_S,1,0);
  bool bEnable = ((bool)  tolua_toboolean(tolua_S,2,true));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetRBSelectEnable'",NULL);
#endif
  {
   self->SetRBSelectEnable(bEnable);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetRBSelectEnable'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetListItem of class  ControlList */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlList_GetListItem00
static int tolua_CompileToLua_ControlList_GetListItem00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlList",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlList* self = (ControlList*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetListItem'",NULL);
#endif
  {
   std::vector<ControlList::S_List*> tolua_ret = (std::vector<ControlList::S_List*>)  self->GetListItem();
   {
#ifdef __cplusplus
    void* tolua_obj = new std::vector<ControlList::S_List*>(tolua_ret);
    tolua_pushusertype_and_takeownership(tolua_S,tolua_obj,"std::vector<ControlList::S_List*>");
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(std::vector<ControlList::S_List*>));
    tolua_pushusertype_and_takeownership(tolua_S,tolua_obj,"std::vector<ControlList::S_List*>");
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetListItem'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetListItemCnt of class  ControlList */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlList_GetListItemCnt00
static int tolua_CompileToLua_ControlList_GetListItemCnt00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlList",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlList* self = (ControlList*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetListItemCnt'",NULL);
#endif
  {
   int tolua_ret = (int)  self->GetListItemCnt();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetListItemCnt'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetScrollBar of class  ControlList */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlList_GetScrollBar00
static int tolua_CompileToLua_ControlList_GetScrollBar00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlList",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlList* self = (ControlList*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetScrollBar'",NULL);
#endif
  {
   ControlScrollBar* tolua_ret = (ControlScrollBar*)  self->GetScrollBar();
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"ControlScrollBar");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetScrollBar'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: PtInHyber of class  ControlList */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlList_PtInHyber00
static int tolua_CompileToLua_ControlList_PtInHyber00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlList",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlList* self = (ControlList*)  tolua_tousertype(tolua_S,1,0);
  const int nX = ((const int)  tolua_tonumber(tolua_S,2,0));
  const int nY = ((const int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'PtInHyber'",NULL);
#endif
  {
   HyberReturnType tolua_ret = (HyberReturnType)  self->PtInHyber(nX,nY);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'PtInHyber'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: UpdataLine2D of class  ControlList */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlList_UpdataLine2D00
static int tolua_CompileToLua_ControlList_UpdataLine2D00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlList",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlList* self = (ControlList*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'UpdataLine2D'",NULL);
#endif
  {
   self->UpdataLine2D();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'UpdataLine2D'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: findHyber_player of class  ControlList */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlList_findHyber_player00
static int tolua_CompileToLua_ControlList_findHyber_player00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlList",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlList* self = (ControlList*)  tolua_tousertype(tolua_S,1,0);
  int index = ((int)  tolua_tonumber(tolua_S,2,0));
  int x = ((int)  tolua_tonumber(tolua_S,3,0));
  int y = ((int)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'findHyber_player'",NULL);
#endif
  {
   HyberReturnType tolua_ret = (HyberReturnType)  self->findHyber_player(index,x,y);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'findHyber_player'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: findHyber_item of class  ControlList */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlList_findHyber_item00
static int tolua_CompileToLua_ControlList_findHyber_item00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlList",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlList* self = (ControlList*)  tolua_tousertype(tolua_S,1,0);
  int index = ((int)  tolua_tonumber(tolua_S,2,0));
  int x = ((int)  tolua_tonumber(tolua_S,3,-1));
  int y = ((int)  tolua_tonumber(tolua_S,4,-1));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'findHyber_item'",NULL);
#endif
  {
   HyberReturnType tolua_ret = (HyberReturnType)  self->findHyber_item(index,x,y);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'findHyber_item'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setShowTip of class  ControlList */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlList_setShowTip00
static int tolua_CompileToLua_ControlList_setShowTip00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlList",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlList* self = (ControlList*)  tolua_tousertype(tolua_S,1,0);
  bool show = ((bool)  tolua_toboolean(tolua_S,2,true));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setShowTip'",NULL);
#endif
  {
   self->setShowTip(show);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setShowTip'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: IsShowTip of class  ControlList */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlList_IsShowTip00
static int tolua_CompileToLua_ControlList_IsShowTip00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const ControlList",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const ControlList* self = (const ControlList*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'IsShowTip'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->IsShowTip();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'IsShowTip'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: BeginUpdate of class  ControlList */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlList_BeginUpdate00
static int tolua_CompileToLua_ControlList_BeginUpdate00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlList",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlList* self = (ControlList*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'BeginUpdate'",NULL);
#endif
  {
   self->BeginUpdate();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'BeginUpdate'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: EndUpdate of class  ControlList */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlList_EndUpdate00
static int tolua_CompileToLua_ControlList_EndUpdate00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlList",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlList* self = (ControlList*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'EndUpdate'",NULL);
#endif
  {
   self->EndUpdate();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'EndUpdate'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetAutoSetCurIndex of class  ControlList */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlList_SetAutoSetCurIndex00
static int tolua_CompileToLua_ControlList_SetAutoSetCurIndex00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlList",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlList* self = (ControlList*)  tolua_tousertype(tolua_S,1,0);
  bool b = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetAutoSetCurIndex'",NULL);
#endif
  {
   self->SetAutoSetCurIndex(b);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetAutoSetCurIndex'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: OnSelectChange of class  ControlList */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlList_OnSelectChange00
static int tolua_CompileToLua_ControlList_OnSelectChange00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlList",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"ControlList::S_List",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlList* self = (ControlList*)  tolua_tousertype(tolua_S,1,0);
  IN ControlList::S_List* pItem = ((IN ControlList::S_List*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'OnSelectChange'",NULL);
#endif
  {
   self->OnSelectChange(pItem);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'OnSelectChange'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: OnLDBClick of class  ControlList */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlList_OnLDBClick00
static int tolua_CompileToLua_ControlList_OnLDBClick00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlList",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"ControlList::S_List",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlList* self = (ControlList*)  tolua_tousertype(tolua_S,1,0);
  IN ControlList::S_List* pItem = ((IN ControlList::S_List*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'OnLDBClick'",NULL);
#endif
  {
   self->OnLDBClick(pItem);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'OnLDBClick'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Refeash of class  ControlList */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlList_Refeash00
static int tolua_CompileToLua_ControlList_Refeash00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlList",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlList* self = (ControlList*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Refeash'",NULL);
#endif
  {
   int tolua_ret = (int)  self->Refeash();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Refeash'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: OnRBDown of class  ControlList */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlList_OnRBDown00
static int tolua_CompileToLua_ControlList_OnRBDown00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlList",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"ControlList::S_List",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlList* self = (ControlList*)  tolua_tousertype(tolua_S,1,0);
  IN ControlList::S_List* pItem = ((IN ControlList::S_List*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'OnRBDown'",NULL);
#endif
  {
   self->OnRBDown(pItem);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'OnRBDown'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: OnShiftRBDown of class  ControlList */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlList_OnShiftRBDown00
static int tolua_CompileToLua_ControlList_OnShiftRBDown00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlList",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"ControlList::S_List",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlList* self = (ControlList*)  tolua_tousertype(tolua_S,1,0);
  IN ControlList::S_List* pItem = ((IN ControlList::S_List*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'OnShiftRBDown'",NULL);
#endif
  {
   self->OnShiftRBDown(pItem);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'OnShiftRBDown'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: OnShiftLBDown of class  ControlList */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlList_OnShiftLBDown00
static int tolua_CompileToLua_ControlList_OnShiftLBDown00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlList",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"ControlList::S_List",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlList* self = (ControlList*)  tolua_tousertype(tolua_S,1,0);
  IN ControlList::S_List* pItem = ((IN ControlList::S_List*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'OnShiftLBDown'",NULL);
#endif
  {
   self->OnShiftLBDown(pItem);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'OnShiftLBDown'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  ControlList */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlList_new00
static int tolua_CompileToLua_ControlList_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"ControlList",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   ControlList* tolua_ret = (ControlList*)  new ControlList();
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"ControlList");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  ControlList */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlList_new00_local
static int tolua_CompileToLua_ControlList_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"ControlList",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   ControlList* tolua_ret = (ControlList*)  new ControlList();
   tolua_pushusertype_and_takeownership(tolua_S,(void *)tolua_ret,"ControlList");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: delete of class  ControlList */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlList_delete00
static int tolua_CompileToLua_ControlList_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlList",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlList* self = (ControlList*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'",NULL);
#endif
  delete self;
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Render of class  ControlListEx */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlListEx_Render00
static int tolua_CompileToLua_ControlListEx_Render00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlListEx",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlListEx* self = (ControlListEx*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Render'",NULL);
#endif
  {
   self->Render();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Render'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: InitUIData of class  ControlListEx */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlListEx_InitUIData00
static int tolua_CompileToLua_ControlListEx_InitUIData00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlListEx",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"ControlObject",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"S_BaseData",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlListEx* self = (ControlListEx*)  tolua_tousertype(tolua_S,1,0);
  IN ControlObject* pFather = ((IN ControlObject*)  tolua_tousertype(tolua_S,2,0));
  IN S_BaseData* pData = ((IN S_BaseData*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'InitUIData'",NULL);
#endif
  {
   self->InitUIData(pFather,pData);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'InitUIData'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetTilePt of class  ControlListEx */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlListEx_GetTilePt00
static int tolua_CompileToLua_ControlListEx_GetTilePt00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlListEx",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isusertype(tolua_S,4,"POINT",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlListEx* self = (ControlListEx*)  tolua_tousertype(tolua_S,1,0);
  const int nX = ((const int)  tolua_tonumber(tolua_S,2,0));
  const int nY = ((const int)  tolua_tonumber(tolua_S,3,0));
  OUT POINT* ptTile = ((OUT POINT*)  tolua_tousertype(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetTilePt'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->GetTilePt(nX,nY,ptTile);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetTilePt'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetIconSize of class  ControlListEx */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlListEx_GetIconSize00
static int tolua_CompileToLua_ControlListEx_GetIconSize00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlListEx",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlListEx* self = (ControlListEx*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetIconSize'",NULL);
#endif
  {
   int tolua_ret = (int)  self->GetIconSize();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetIconSize'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: CanbePick of class  ControlListEx */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlListEx_CanbePick00
static int tolua_CompileToLua_ControlListEx_CanbePick00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlListEx",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlListEx* self = (ControlListEx*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'CanbePick'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->CanbePick();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'CanbePick'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetCanbePick of class  ControlListEx */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlListEx_SetCanbePick00
static int tolua_CompileToLua_ControlListEx_SetCanbePick00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlListEx",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlListEx* self = (ControlListEx*)  tolua_tousertype(tolua_S,1,0);
  const bool b = ((const bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetCanbePick'",NULL);
#endif
  {
   self->SetCanbePick(b);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetCanbePick'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetDrawInfoFun_2lua of class  ControlListEx */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlListEx_SetDrawInfoFun_2lua00
static int tolua_CompileToLua_ControlListEx_SetDrawInfoFun_2lua00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlListEx",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlListEx* self = (ControlListEx*)  tolua_tousertype(tolua_S,1,0);
  const char* luaTable = ((const char*)  tolua_tostring(tolua_S,2,0));
  const char* funName = ((const char*)  tolua_tostring(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetDrawInfoFun_2lua'",NULL);
#endif
  {
   self->SetDrawInfoFun_2lua(luaTable,funName);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetDrawInfoFun_2lua'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetHaveSelFrame of class  ControlListEx */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlListEx_SetHaveSelFrame00
static int tolua_CompileToLua_ControlListEx_SetHaveSelFrame00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlListEx",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlListEx* self = (ControlListEx*)  tolua_tousertype(tolua_S,1,0);
  bool b = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetHaveSelFrame'",NULL);
#endif
  {
   self->SetHaveSelFrame(b);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetHaveSelFrame'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetOnlyIcon of class  ControlListEx */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlListEx_SetOnlyIcon00
static int tolua_CompileToLua_ControlListEx_SetOnlyIcon00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlListEx",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlListEx* self = (ControlListEx*)  tolua_tousertype(tolua_S,1,0);
  bool b = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetOnlyIcon'",NULL);
#endif
  {
   self->SetOnlyIcon(b);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetOnlyIcon'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getCurItemPos of class  ControlListEx */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlListEx_getCurItemPos00
static int tolua_CompileToLua_ControlListEx_getCurItemPos00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlListEx",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlListEx* self = (ControlListEx*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getCurItemPos'",NULL);
#endif
  {
   POINT tolua_ret = (POINT)  self->getCurItemPos();
   {
#ifdef __cplusplus
    void* tolua_obj = new POINT(tolua_ret);
    tolua_pushusertype_and_takeownership(tolua_S,tolua_obj,"POINT");
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(POINT));
    tolua_pushusertype_and_takeownership(tolua_S,tolua_obj,"POINT");
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getCurItemPos'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  ControlListEx */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlListEx_new00
static int tolua_CompileToLua_ControlListEx_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"ControlListEx",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   ControlListEx* tolua_ret = (ControlListEx*)  new ControlListEx();
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"ControlListEx");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  ControlListEx */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlListEx_new00_local
static int tolua_CompileToLua_ControlListEx_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"ControlListEx",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   ControlListEx* tolua_ret = (ControlListEx*)  new ControlListEx();
   tolua_pushusertype_and_takeownership(tolua_S,(void *)tolua_ret,"ControlListEx");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: delete of class  ControlListEx */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlListEx_delete00
static int tolua_CompileToLua_ControlListEx_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlListEx",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlListEx* self = (ControlListEx*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'",NULL);
#endif
  delete self;
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: m_nCurLvl of class  ControlListImage */
#ifndef TOLUA_DISABLE_tolua_get_ControlListImage_m_nCurLvl
static int tolua_get_ControlListImage_m_nCurLvl(lua_State* tolua_S)
{
  ControlListImage* self = (ControlListImage*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_nCurLvl'",NULL);
#endif
  tolua_pushusertype(tolua_S,(void*)&self->m_nCurLvl,"INT");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: m_nCurLvl of class  ControlListImage */
#ifndef TOLUA_DISABLE_tolua_set_ControlListImage_m_nCurLvl
static int tolua_set_ControlListImage_m_nCurLvl(lua_State* tolua_S)
{
  ControlListImage* self = (ControlListImage*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_nCurLvl'",NULL);
  if (!tolua_isusertype(tolua_S,2,"INT",0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->m_nCurLvl = *((INT*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: m_nMaxLvl of class  ControlListImage */
#ifndef TOLUA_DISABLE_tolua_get_ControlListImage_m_nMaxLvl
static int tolua_get_ControlListImage_m_nMaxLvl(lua_State* tolua_S)
{
  ControlListImage* self = (ControlListImage*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_nMaxLvl'",NULL);
#endif
  tolua_pushusertype(tolua_S,(void*)&self->m_nMaxLvl,"INT");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: m_nMaxLvl of class  ControlListImage */
#ifndef TOLUA_DISABLE_tolua_set_ControlListImage_m_nMaxLvl
static int tolua_set_ControlListImage_m_nMaxLvl(lua_State* tolua_S)
{
  ControlListImage* self = (ControlListImage*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_nMaxLvl'",NULL);
  if (!tolua_isusertype(tolua_S,2,"INT",0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->m_nMaxLvl = *((INT*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: _bOrder of class  ControlListImage */
#ifndef TOLUA_DISABLE_tolua_get_ControlListImage__bOrder
static int tolua_get_ControlListImage__bOrder(lua_State* tolua_S)
{
  ControlListImage* self = (ControlListImage*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable '_bOrder'",NULL);
#endif
  tolua_pushboolean(tolua_S,(bool)self->_bOrder);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: _bOrder of class  ControlListImage */
#ifndef TOLUA_DISABLE_tolua_set_ControlListImage__bOrder
static int tolua_set_ControlListImage__bOrder(lua_State* tolua_S)
{
  ControlListImage* self = (ControlListImage*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable '_bOrder'",NULL);
  if (!tolua_isboolean(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->_bOrder = ((bool)  tolua_toboolean(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* method: Render of class  ControlListImage */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlListImage_Render00
static int tolua_CompileToLua_ControlListImage_Render00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlListImage",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlListImage* self = (ControlListImage*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Render'",NULL);
#endif
  {
   self->Render();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Render'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: InitUIData of class  ControlListImage */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlListImage_InitUIData00
static int tolua_CompileToLua_ControlListImage_InitUIData00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlListImage",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"ControlObject",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"S_BaseData",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlListImage* self = (ControlListImage*)  tolua_tousertype(tolua_S,1,0);
  IN ControlObject* pFather = ((IN ControlObject*)  tolua_tousertype(tolua_S,2,0));
  IN S_BaseData* pData = ((IN S_BaseData*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'InitUIData'",NULL);
#endif
  {
   self->InitUIData(pFather,pData);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'InitUIData'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetIconSize of class  ControlListImage */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlListImage_GetIconSize00
static int tolua_CompileToLua_ControlListImage_GetIconSize00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlListImage",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlListImage* self = (ControlListImage*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetIconSize'",NULL);
#endif
  {
   int tolua_ret = (int)  self->GetIconSize();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetIconSize'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetTilePt of class  ControlListImage */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlListImage_GetTilePt00
static int tolua_CompileToLua_ControlListImage_GetTilePt00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlListImage",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isusertype(tolua_S,4,"POINT",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlListImage* self = (ControlListImage*)  tolua_tousertype(tolua_S,1,0);
  const int nX = ((const int)  tolua_tonumber(tolua_S,2,0));
  const int nY = ((const int)  tolua_tonumber(tolua_S,3,0));
  OUT POINT* ptTile = ((OUT POINT*)  tolua_tousertype(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetTilePt'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->GetTilePt(nX,nY,ptTile);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetTilePt'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: CanbePick of class  ControlListImage */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlListImage_CanbePick00
static int tolua_CompileToLua_ControlListImage_CanbePick00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlListImage",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlListImage* self = (ControlListImage*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'CanbePick'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->CanbePick();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'CanbePick'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetCanbePick of class  ControlListImage */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlListImage_SetCanbePick00
static int tolua_CompileToLua_ControlListImage_SetCanbePick00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlListImage",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlListImage* self = (ControlListImage*)  tolua_tousertype(tolua_S,1,0);
  const bool b = ((const bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetCanbePick'",NULL);
#endif
  {
   self->SetCanbePick(b);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetCanbePick'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetLvlInfo of class  ControlListImage */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlListImage_SetLvlInfo00
static int tolua_CompileToLua_ControlListImage_SetLvlInfo00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlListImage",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"INT",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"INT",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlListImage* self = (ControlListImage*)  tolua_tousertype(tolua_S,1,0);
  INT nCurLvl = *((INT*)  tolua_tousertype(tolua_S,2,0));
  INT nMaxLvl = *((INT*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetLvlInfo'",NULL);
#endif
  {
   self->SetLvlInfo(nCurLvl,nMaxLvl);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetLvlInfo'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetScrollValue of class  ControlListImage */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlListImage_SetScrollValue00
static int tolua_CompileToLua_ControlListImage_SetScrollValue00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlListImage",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlListImage* self = (ControlListImage*)  tolua_tousertype(tolua_S,1,0);
  int nValue = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetScrollValue'",NULL);
#endif
  {
   self->SetScrollValue(nValue);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetScrollValue'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setOrderType of class  ControlListImage */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlListImage_setOrderType00
static int tolua_CompileToLua_ControlListImage_setOrderType00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlListImage",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlListImage* self = (ControlListImage*)  tolua_tousertype(tolua_S,1,0);
  bool bBeginRight = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setOrderType'",NULL);
#endif
  {
   self->setOrderType(bBeginRight);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setOrderType'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetMouseOnSel of class  ControlListImage */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlListImage_GetMouseOnSel00
static int tolua_CompileToLua_ControlListImage_GetMouseOnSel00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlListImage",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlListImage* self = (ControlListImage*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetMouseOnSel'",NULL);
#endif
  {
   POINT tolua_ret = (POINT)  self->GetMouseOnSel();
   {
#ifdef __cplusplus
    void* tolua_obj = new POINT(tolua_ret);
    tolua_pushusertype_and_takeownership(tolua_S,tolua_obj,"POINT");
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(POINT));
    tolua_pushusertype_and_takeownership(tolua_S,tolua_obj,"POINT");
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetMouseOnSel'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  ControlListImage */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlListImage_new00
static int tolua_CompileToLua_ControlListImage_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"ControlListImage",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   ControlListImage* tolua_ret = (ControlListImage*)  new ControlListImage();
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"ControlListImage");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  ControlListImage */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlListImage_new00_local
static int tolua_CompileToLua_ControlListImage_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"ControlListImage",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   ControlListImage* tolua_ret = (ControlListImage*)  new ControlListImage();
   tolua_pushusertype_and_takeownership(tolua_S,(void *)tolua_ret,"ControlListImage");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: delete of class  ControlListImage */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlListImage_delete00
static int tolua_CompileToLua_ControlListImage_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlListImage",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlListImage* self = (ControlListImage*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'",NULL);
#endif
  delete self;
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: OnLButtonDown of class  ControlPicture */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlPicture_OnLButtonDown00
static int tolua_CompileToLua_ControlPicture_OnLButtonDown00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlPicture",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"UINT",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlPicture* self = (ControlPicture*)  tolua_tousertype(tolua_S,1,0);
  UINT nFlags = *((UINT*)  tolua_tousertype(tolua_S,2,0));
  const int nX = ((const int)  tolua_tonumber(tolua_S,3,0));
  const int nY = ((const int)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'OnLButtonDown'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->OnLButtonDown(nFlags,nX,nY);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'OnLButtonDown'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: OnMouseMove of class  ControlPicture */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlPicture_OnMouseMove00
static int tolua_CompileToLua_ControlPicture_OnMouseMove00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlPicture",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"UINT",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlPicture* self = (ControlPicture*)  tolua_tousertype(tolua_S,1,0);
  UINT nFlags = *((UINT*)  tolua_tousertype(tolua_S,2,0));
  const int nX = ((const int)  tolua_tonumber(tolua_S,3,0));
  const int nY = ((const int)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'OnMouseMove'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->OnMouseMove(nFlags,nX,nY);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'OnMouseMove'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: OnMouseLeave of class  ControlPicture */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlPicture_OnMouseLeave00
static int tolua_CompileToLua_ControlPicture_OnMouseLeave00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlPicture",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"UINT",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlPicture* self = (ControlPicture*)  tolua_tousertype(tolua_S,1,0);
  UINT nFlags = *((UINT*)  tolua_tousertype(tolua_S,2,0));
  const int nX = ((const int)  tolua_tonumber(tolua_S,3,0));
  const int nY = ((const int)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'OnMouseLeave'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->OnMouseLeave(nFlags,nX,nY);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'OnMouseLeave'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: OnLButtonDBClick of class  ControlPicture */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlPicture_OnLButtonDBClick00
static int tolua_CompileToLua_ControlPicture_OnLButtonDBClick00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlPicture",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"UINT",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlPicture* self = (ControlPicture*)  tolua_tousertype(tolua_S,1,0);
  UINT nFlags = *((UINT*)  tolua_tousertype(tolua_S,2,0));
  const int nX = ((const int)  tolua_tonumber(tolua_S,3,0));
  const int nY = ((const int)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'OnLButtonDBClick'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->OnLButtonDBClick(nFlags,nX,nY);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'OnLButtonDBClick'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetPicClickFun_2lua of class  ControlPicture */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlPicture_SetPicClickFun_2lua00
static int tolua_CompileToLua_ControlPicture_SetPicClickFun_2lua00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlPicture",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlPicture* self = (ControlPicture*)  tolua_tousertype(tolua_S,1,0);
  const char* luaTable = ((const char*)  tolua_tostring(tolua_S,2,0));
  const char* funName = ((const char*)  tolua_tostring(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetPicClickFun_2lua'",NULL);
#endif
  {
   self->SetPicClickFun_2lua(luaTable,funName);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetPicClickFun_2lua'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetOnMouseOn_2lua of class  ControlPicture */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlPicture_SetOnMouseOn_2lua00
static int tolua_CompileToLua_ControlPicture_SetOnMouseOn_2lua00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlPicture",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlPicture* self = (ControlPicture*)  tolua_tousertype(tolua_S,1,0);
  const char* luaTable = ((const char*)  tolua_tostring(tolua_S,2,0));
  const char* funName = ((const char*)  tolua_tostring(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetOnMouseOn_2lua'",NULL);
#endif
  {
   self->SetOnMouseOn_2lua(luaTable,funName);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetOnMouseOn_2lua'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetOnMouseLeave_2lua of class  ControlPicture */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlPicture_SetOnMouseLeave_2lua00
static int tolua_CompileToLua_ControlPicture_SetOnMouseLeave_2lua00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlPicture",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlPicture* self = (ControlPicture*)  tolua_tousertype(tolua_S,1,0);
  const char* luaTable = ((const char*)  tolua_tostring(tolua_S,2,0));
  const char* funName = ((const char*)  tolua_tostring(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetOnMouseLeave_2lua'",NULL);
#endif
  {
   self->SetOnMouseLeave_2lua(luaTable,funName);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetOnMouseLeave_2lua'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetOnLDBClickFun_2lua of class  ControlPicture */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlPicture_SetOnLDBClickFun_2lua00
static int tolua_CompileToLua_ControlPicture_SetOnLDBClickFun_2lua00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlPicture",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlPicture* self = (ControlPicture*)  tolua_tousertype(tolua_S,1,0);
  const char* luaTable = ((const char*)  tolua_tostring(tolua_S,2,0));
  const char* funName = ((const char*)  tolua_tostring(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetOnLDBClickFun_2lua'",NULL);
#endif
  {
   self->SetOnLDBClickFun_2lua(luaTable,funName);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetOnLDBClickFun_2lua'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setTip of class  ControlPicture */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlPicture_setTip00
static int tolua_CompileToLua_ControlPicture_setTip00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlPicture",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlPicture* self = (ControlPicture*)  tolua_tousertype(tolua_S,1,0);
  const char* data = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setTip'",NULL);
#endif
  {
   self->setTip(data);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setTip'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setShowTip of class  ControlPicture */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlPicture_setShowTip00
static int tolua_CompileToLua_ControlPicture_setShowTip00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlPicture",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlPicture* self = (ControlPicture*)  tolua_tousertype(tolua_S,1,0);
  bool show = ((bool)  tolua_toboolean(tolua_S,2,true));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setShowTip'",NULL);
#endif
  {
   self->setShowTip(show);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setShowTip'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: IsShowTip of class  ControlPicture */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlPicture_IsShowTip00
static int tolua_CompileToLua_ControlPicture_IsShowTip00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlPicture",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlPicture* self = (ControlPicture*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'IsShowTip'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->IsShowTip();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'IsShowTip'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: OnClick of class  ControlPicture */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlPicture_OnClick00
static int tolua_CompileToLua_ControlPicture_OnClick00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlPicture",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlPicture* self = (ControlPicture*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'OnClick'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->OnClick();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'OnClick'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  ControlPicture */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlPicture_new00
static int tolua_CompileToLua_ControlPicture_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"ControlPicture",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   ControlPicture* tolua_ret = (ControlPicture*)  new ControlPicture();
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"ControlPicture");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  ControlPicture */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlPicture_new00_local
static int tolua_CompileToLua_ControlPicture_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"ControlPicture",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   ControlPicture* tolua_ret = (ControlPicture*)  new ControlPicture();
   tolua_pushusertype_and_takeownership(tolua_S,(void *)tolua_ret,"ControlPicture");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: delete of class  ControlPicture */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlPicture_delete00
static int tolua_CompileToLua_ControlPicture_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlPicture",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlPicture* self = (ControlPicture*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'",NULL);
#endif
  delete self;
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: UseFocus of class  ControlProgress */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlProgress_UseFocus00
static int tolua_CompileToLua_ControlProgress_UseFocus00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlProgress",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlProgress* self = (ControlProgress*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'UseFocus'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->UseFocus();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'UseFocus'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: InitUIData of class  ControlProgress */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlProgress_InitUIData00
static int tolua_CompileToLua_ControlProgress_InitUIData00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlProgress",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"ControlObject",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"S_BaseData",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlProgress* self = (ControlProgress*)  tolua_tousertype(tolua_S,1,0);
  IN ControlObject* pFather = ((IN ControlObject*)  tolua_tousertype(tolua_S,2,0));
  IN S_BaseData* pData = ((IN S_BaseData*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'InitUIData'",NULL);
#endif
  {
   self->InitUIData(pFather,pData);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'InitUIData'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetVisable of class  ControlProgress */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlProgress_SetVisable00
static int tolua_CompileToLua_ControlProgress_SetVisable00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlProgress",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isboolean(tolua_S,3,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlProgress* self = (ControlProgress*)  tolua_tousertype(tolua_S,1,0);
  const bool bVisable = ((const bool)  tolua_toboolean(tolua_S,2,0));
  const bool bFadeInorFadeOut = ((const bool)  tolua_toboolean(tolua_S,3,false));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetVisable'",NULL);
#endif
  {
   self->SetVisable(bVisable,bFadeInorFadeOut);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetVisable'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: OnMouseMove of class  ControlProgress */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlProgress_OnMouseMove00
static int tolua_CompileToLua_ControlProgress_OnMouseMove00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlProgress",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"UINT",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlProgress* self = (ControlProgress*)  tolua_tousertype(tolua_S,1,0);
  UINT nFlags = *((UINT*)  tolua_tousertype(tolua_S,2,0));
  const int nX = ((const int)  tolua_tonumber(tolua_S,3,0));
  const int nY = ((const int)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'OnMouseMove'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->OnMouseMove(nFlags,nX,nY);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'OnMouseMove'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetValue of class  ControlProgress */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlProgress_GetValue00
static int tolua_CompileToLua_ControlProgress_GetValue00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlProgress",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlProgress* self = (ControlProgress*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetValue'",NULL);
#endif
  {
   int tolua_ret = (int)  self->GetValue();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetValue'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetValue of class  ControlProgress */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlProgress_SetValue00
static int tolua_CompileToLua_ControlProgress_SetValue00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlProgress",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlProgress* self = (ControlProgress*)  tolua_tousertype(tolua_S,1,0);
  const int n = ((const int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetValue'",NULL);
#endif
  {
   self->SetValue(n);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetValue'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetMaxValue of class  ControlProgress */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlProgress_GetMaxValue00
static int tolua_CompileToLua_ControlProgress_GetMaxValue00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlProgress",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlProgress* self = (ControlProgress*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetMaxValue'",NULL);
#endif
  {
   int tolua_ret = (int)  self->GetMaxValue();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetMaxValue'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetMaxValue of class  ControlProgress */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlProgress_SetMaxValue00
static int tolua_CompileToLua_ControlProgress_SetMaxValue00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlProgress",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlProgress* self = (ControlProgress*)  tolua_tousertype(tolua_S,1,0);
  int n = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetMaxValue'",NULL);
#endif
  {
   self->SetMaxValue(n);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetMaxValue'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetRealWidth of class  ControlProgress */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlProgress_GetRealWidth00
static int tolua_CompileToLua_ControlProgress_GetRealWidth00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlProgress",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlProgress* self = (ControlProgress*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetRealWidth'",NULL);
#endif
  {
   int tolua_ret = (int)  self->GetRealWidth();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetRealWidth'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Create of class  ControlProgress */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlProgress_Create00
static int tolua_CompileToLua_ControlProgress_Create00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlProgress",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"const RECT",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"const D3DCOLOR",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlProgress* self = (ControlProgress*)  tolua_tousertype(tolua_S,1,0);
  IN  const RECT* pRect = ((IN  const RECT*)  tolua_tousertype(tolua_S,2,0));
  const D3DCOLOR colBack = *((const D3DCOLOR*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Create'",NULL);
#endif
  {
   self->Create(pRect,colBack);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Create'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Render of class  ControlProgress */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlProgress_Render00
static int tolua_CompileToLua_ControlProgress_Render00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlProgress",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlProgress* self = (ControlProgress*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Render'",NULL);
#endif
  {
   self->Render();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Render'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setTipName of class  ControlProgress */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlProgress_setTipName00
static int tolua_CompileToLua_ControlProgress_setTipName00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlProgress",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlProgress* self = (ControlProgress*)  tolua_tousertype(tolua_S,1,0);
  const char* ch = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setTipName'",NULL);
#endif
  {
   self->setTipName(ch);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setTipName'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: IsShowTip of class  ControlProgress */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlProgress_IsShowTip00
static int tolua_CompileToLua_ControlProgress_IsShowTip00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlProgress",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlProgress* self = (ControlProgress*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'IsShowTip'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->IsShowTip();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'IsShowTip'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setShowTip of class  ControlProgress */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlProgress_setShowTip00
static int tolua_CompileToLua_ControlProgress_setShowTip00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlProgress",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlProgress* self = (ControlProgress*)  tolua_tousertype(tolua_S,1,0);
  bool bShow = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setShowTip'",NULL);
#endif
  {
   self->setShowTip(bShow);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setShowTip'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  ControlProgress */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlProgress_new00
static int tolua_CompileToLua_ControlProgress_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"ControlProgress",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   ControlProgress* tolua_ret = (ControlProgress*)  new ControlProgress();
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"ControlProgress");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  ControlProgress */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlProgress_new00_local
static int tolua_CompileToLua_ControlProgress_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"ControlProgress",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   ControlProgress* tolua_ret = (ControlProgress*)  new ControlProgress();
   tolua_pushusertype_and_takeownership(tolua_S,(void *)tolua_ret,"ControlProgress");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: delete of class  ControlProgress */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlProgress_delete00
static int tolua_CompileToLua_ControlProgress_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlProgress",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlProgress* self = (ControlProgress*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'",NULL);
#endif
  delete self;
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Render of class  ControlScrollBar */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlScrollBar_Render00
static int tolua_CompileToLua_ControlScrollBar_Render00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlScrollBar",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlScrollBar* self = (ControlScrollBar*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Render'",NULL);
#endif
  {
   self->Render();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Render'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: InitUIData of class  ControlScrollBar */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlScrollBar_InitUIData00
static int tolua_CompileToLua_ControlScrollBar_InitUIData00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlScrollBar",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"ControlObject",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"S_BaseData",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlScrollBar* self = (ControlScrollBar*)  tolua_tousertype(tolua_S,1,0);
  IN ControlObject* pFather = ((IN ControlObject*)  tolua_tousertype(tolua_S,2,0));
  IN S_BaseData* pData = ((IN S_BaseData*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'InitUIData'",NULL);
#endif
  {
   self->InitUIData(pFather,pData);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'InitUIData'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: OnMouseMove of class  ControlScrollBar */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlScrollBar_OnMouseMove00
static int tolua_CompileToLua_ControlScrollBar_OnMouseMove00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlScrollBar",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"UINT",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlScrollBar* self = (ControlScrollBar*)  tolua_tousertype(tolua_S,1,0);
  UINT nFlags = *((UINT*)  tolua_tousertype(tolua_S,2,0));
  const int nX = ((const int)  tolua_tonumber(tolua_S,3,0));
  const int nY = ((const int)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'OnMouseMove'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->OnMouseMove(nFlags,nX,nY);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'OnMouseMove'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: OnLButtonDown of class  ControlScrollBar */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlScrollBar_OnLButtonDown00
static int tolua_CompileToLua_ControlScrollBar_OnLButtonDown00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlScrollBar",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"UINT",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlScrollBar* self = (ControlScrollBar*)  tolua_tousertype(tolua_S,1,0);
  UINT nFlags = *((UINT*)  tolua_tousertype(tolua_S,2,0));
  const int nX = ((const int)  tolua_tonumber(tolua_S,3,0));
  const int nY = ((const int)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'OnLButtonDown'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->OnLButtonDown(nFlags,nX,nY);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'OnLButtonDown'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: OnLButtonUp of class  ControlScrollBar */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlScrollBar_OnLButtonUp00
static int tolua_CompileToLua_ControlScrollBar_OnLButtonUp00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlScrollBar",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"UINT",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlScrollBar* self = (ControlScrollBar*)  tolua_tousertype(tolua_S,1,0);
  UINT nFlags = *((UINT*)  tolua_tousertype(tolua_S,2,0));
  const int nX = ((const int)  tolua_tonumber(tolua_S,3,0));
  const int nY = ((const int)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'OnLButtonUp'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->OnLButtonUp(nFlags,nX,nY);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'OnLButtonUp'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetValue of class  ControlScrollBar */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlScrollBar_GetValue00
static int tolua_CompileToLua_ControlScrollBar_GetValue00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlScrollBar",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlScrollBar* self = (ControlScrollBar*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetValue'",NULL);
#endif
  {
   int tolua_ret = (int)  self->GetValue();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetValue'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetValue of class  ControlScrollBar */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlScrollBar_SetValue00
static int tolua_CompileToLua_ControlScrollBar_SetValue00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlScrollBar",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlScrollBar* self = (ControlScrollBar*)  tolua_tousertype(tolua_S,1,0);
  const int n = ((const int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetValue'",NULL);
#endif
  {
   self->SetValue(n);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetValue'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: IsDrag of class  ControlScrollBar */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlScrollBar_IsDrag00
static int tolua_CompileToLua_ControlScrollBar_IsDrag00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlScrollBar",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlScrollBar* self = (ControlScrollBar*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'IsDrag'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->IsDrag();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'IsDrag'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: ClearDrag of class  ControlScrollBar */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlScrollBar_ClearDrag00
static int tolua_CompileToLua_ControlScrollBar_ClearDrag00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlScrollBar",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlScrollBar* self = (ControlScrollBar*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'ClearDrag'",NULL);
#endif
  {
   self->ClearDrag();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'ClearDrag'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetEnable of class  ControlScrollBar */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlScrollBar_SetEnable00
static int tolua_CompileToLua_ControlScrollBar_SetEnable00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlScrollBar",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlScrollBar* self = (ControlScrollBar*)  tolua_tousertype(tolua_S,1,0);
  bool bEnable = ((bool)  tolua_toboolean(tolua_S,2,true));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetEnable'",NULL);
#endif
  {
   self->SetEnable(bEnable);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetEnable'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetEnable of class  ControlScrollBar */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlScrollBar_GetEnable00
static int tolua_CompileToLua_ControlScrollBar_GetEnable00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlScrollBar",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlScrollBar* self = (ControlScrollBar*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetEnable'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->GetEnable();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetEnable'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetUIScrollBarBlend of class  ControlScrollBar */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlScrollBar_SetUIScrollBarBlend00
static int tolua_CompileToLua_ControlScrollBar_SetUIScrollBarBlend00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlScrollBar",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlScrollBar* self = (ControlScrollBar*)  tolua_tousertype(tolua_S,1,0);
  int nBlend = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetUIScrollBarBlend'",NULL);
#endif
  {
   self->SetUIScrollBarBlend(nBlend);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetUIScrollBarBlend'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetScrollHeight of class  ControlScrollBar */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlScrollBar_SetScrollHeight00
static int tolua_CompileToLua_ControlScrollBar_SetScrollHeight00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlScrollBar",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlScrollBar* self = (ControlScrollBar*)  tolua_tousertype(tolua_S,1,0);
  const int nHeight = ((const int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetScrollHeight'",NULL);
#endif
  {
   self->SetScrollHeight(nHeight);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetScrollHeight'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetMaxValue of class  ControlScrollBar */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlScrollBar_GetMaxValue00
static int tolua_CompileToLua_ControlScrollBar_GetMaxValue00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlScrollBar",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlScrollBar* self = (ControlScrollBar*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetMaxValue'",NULL);
#endif
  {
   int tolua_ret = (int)  self->GetMaxValue();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetMaxValue'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetMaxValue of class  ControlScrollBar */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlScrollBar_SetMaxValue00
static int tolua_CompileToLua_ControlScrollBar_SetMaxValue00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlScrollBar",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlScrollBar* self = (ControlScrollBar*)  tolua_tousertype(tolua_S,1,0);
  int nMax = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetMaxValue'",NULL);
#endif
  {
   self->SetMaxValue(nMax);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetMaxValue'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetStepValue of class  ControlScrollBar */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlScrollBar_SetStepValue00
static int tolua_CompileToLua_ControlScrollBar_SetStepValue00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlScrollBar",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlScrollBar* self = (ControlScrollBar*)  tolua_tousertype(tolua_S,1,0);
  int nStep = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetStepValue'",NULL);
#endif
  {
   self->SetStepValue(nStep);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetStepValue'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: OnUpdatePos of class  ControlScrollBar */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlScrollBar_OnUpdatePos00
static int tolua_CompileToLua_ControlScrollBar_OnUpdatePos00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlScrollBar",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlScrollBar* self = (ControlScrollBar*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'OnUpdatePos'",NULL);
#endif
  {
   self->OnUpdatePos();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'OnUpdatePos'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  ControlScrollBar */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlScrollBar_new00
static int tolua_CompileToLua_ControlScrollBar_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"ControlScrollBar",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   ControlScrollBar* tolua_ret = (ControlScrollBar*)  new ControlScrollBar();
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"ControlScrollBar");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  ControlScrollBar */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlScrollBar_new00_local
static int tolua_CompileToLua_ControlScrollBar_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"ControlScrollBar",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   ControlScrollBar* tolua_ret = (ControlScrollBar*)  new ControlScrollBar();
   tolua_pushusertype_and_takeownership(tolua_S,(void *)tolua_ret,"ControlScrollBar");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: delete of class  ControlScrollBar */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlScrollBar_delete00
static int tolua_CompileToLua_ControlScrollBar_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlScrollBar",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlScrollBar* self = (ControlScrollBar*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'",NULL);
#endif
  delete self;
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: OnMouseMove of class  ControlScrollBarEx */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlScrollBarEx_OnMouseMove00
static int tolua_CompileToLua_ControlScrollBarEx_OnMouseMove00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlScrollBarEx",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"UINT",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlScrollBarEx* self = (ControlScrollBarEx*)  tolua_tousertype(tolua_S,1,0);
  UINT nFlags = *((UINT*)  tolua_tousertype(tolua_S,2,0));
  const int nX = ((const int)  tolua_tonumber(tolua_S,3,0));
  const int nY = ((const int)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'OnMouseMove'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->OnMouseMove(nFlags,nX,nY);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'OnMouseMove'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: OnLButtonDown of class  ControlScrollBarEx */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlScrollBarEx_OnLButtonDown00
static int tolua_CompileToLua_ControlScrollBarEx_OnLButtonDown00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlScrollBarEx",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"UINT",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlScrollBarEx* self = (ControlScrollBarEx*)  tolua_tousertype(tolua_S,1,0);
  UINT nFlags = *((UINT*)  tolua_tousertype(tolua_S,2,0));
  const int nX = ((const int)  tolua_tonumber(tolua_S,3,0));
  const int nY = ((const int)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'OnLButtonDown'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->OnLButtonDown(nFlags,nX,nY);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'OnLButtonDown'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: OnUpdatePos of class  ControlScrollBarEx */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlScrollBarEx_OnUpdatePos00
static int tolua_CompileToLua_ControlScrollBarEx_OnUpdatePos00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlScrollBarEx",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlScrollBarEx* self = (ControlScrollBarEx*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'OnUpdatePos'",NULL);
#endif
  {
   self->OnUpdatePos();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'OnUpdatePos'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  ControlScrollBarEx */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlScrollBarEx_new00
static int tolua_CompileToLua_ControlScrollBarEx_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"ControlScrollBarEx",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   ControlScrollBarEx* tolua_ret = (ControlScrollBarEx*)  new ControlScrollBarEx();
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"ControlScrollBarEx");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  ControlScrollBarEx */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlScrollBarEx_new00_local
static int tolua_CompileToLua_ControlScrollBarEx_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"ControlScrollBarEx",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   ControlScrollBarEx* tolua_ret = (ControlScrollBarEx*)  new ControlScrollBarEx();
   tolua_pushusertype_and_takeownership(tolua_S,(void *)tolua_ret,"ControlScrollBarEx");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: delete of class  ControlScrollBarEx */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlScrollBarEx_delete00
static int tolua_CompileToLua_ControlScrollBarEx_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlScrollBarEx",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlScrollBarEx* self = (ControlScrollBarEx*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'",NULL);
#endif
  delete self;
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Render of class  ControlTab */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlTab_Render00
static int tolua_CompileToLua_ControlTab_Render00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlTab",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlTab* self = (ControlTab*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Render'",NULL);
#endif
  {
   self->Render();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Render'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: IsChild of class  ControlTab */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlTab_IsChild00
static int tolua_CompileToLua_ControlTab_IsChild00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlTab",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"const ControlObject",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlTab* self = (ControlTab*)  tolua_tousertype(tolua_S,1,0);
  IN  const ControlObject* pChild = ((IN  const ControlObject*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'IsChild'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->IsChild(pChild);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'IsChild'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: FindControl of class  ControlTab */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlTab_FindControl00
static int tolua_CompileToLua_ControlTab_FindControl00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlTab",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlTab* self = (ControlTab*)  tolua_tousertype(tolua_S,1,0);
  IN  const char* szControlID = ((IN  const char*)  tolua_tostring(tolua_S,2,0));
  IN  const char* szFrameID = ((IN  const char*)  tolua_tostring(tolua_S,3,NULL));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'FindControl'",NULL);
#endif
  {
   ControlObject* tolua_ret = (ControlObject*)  self->FindControl(szControlID,szFrameID);
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"ControlObject");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'FindControl'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: FindFrame of class  ControlTab */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlTab_FindFrame00
static int tolua_CompileToLua_ControlTab_FindFrame00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlTab",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlTab* self = (ControlTab*)  tolua_tousertype(tolua_S,1,0);
  IN  const char* szFrameID = ((IN  const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'FindFrame'",NULL);
#endif
  {
   ControlObject* tolua_ret = (ControlObject*)  self->FindFrame(szFrameID);
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"ControlObject");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'FindFrame'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: InitUIData of class  ControlTab */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlTab_InitUIData00
static int tolua_CompileToLua_ControlTab_InitUIData00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlTab",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"ControlObject",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"S_BaseData",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlTab* self = (ControlTab*)  tolua_tousertype(tolua_S,1,0);
  IN ControlObject* pFather = ((IN ControlObject*)  tolua_tousertype(tolua_S,2,0));
  IN S_BaseData* pData = ((IN S_BaseData*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'InitUIData'",NULL);
#endif
  {
   self->InitUIData(pFather,pData);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'InitUIData'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: OnChar of class  ControlTab */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlTab_OnChar00
static int tolua_CompileToLua_ControlTab_OnChar00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlTab",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"UINT",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlTab* self = (ControlTab*)  tolua_tousertype(tolua_S,1,0);
  UINT nChar = *((UINT*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'OnChar'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->OnChar(nChar);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'OnChar'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: OnMouseMove of class  ControlTab */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlTab_OnMouseMove00
static int tolua_CompileToLua_ControlTab_OnMouseMove00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlTab",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"UINT",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlTab* self = (ControlTab*)  tolua_tousertype(tolua_S,1,0);
  UINT nFlags = *((UINT*)  tolua_tousertype(tolua_S,2,0));
  const int nX = ((const int)  tolua_tonumber(tolua_S,3,0));
  const int nY = ((const int)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'OnMouseMove'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->OnMouseMove(nFlags,nX,nY);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'OnMouseMove'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: OnMouseWheel of class  ControlTab */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlTab_OnMouseWheel00
static int tolua_CompileToLua_ControlTab_OnMouseWheel00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlTab",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlTab* self = (ControlTab*)  tolua_tousertype(tolua_S,1,0);
  bool bUp = ((bool)  tolua_toboolean(tolua_S,2,0));
  const int nX = ((const int)  tolua_tonumber(tolua_S,3,0));
  const int nY = ((const int)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'OnMouseWheel'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->OnMouseWheel(bUp,nX,nY);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'OnMouseWheel'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: OnLButtonUp of class  ControlTab */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlTab_OnLButtonUp00
static int tolua_CompileToLua_ControlTab_OnLButtonUp00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlTab",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"UINT",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlTab* self = (ControlTab*)  tolua_tousertype(tolua_S,1,0);
  UINT nFlags = *((UINT*)  tolua_tousertype(tolua_S,2,0));
  const int nX = ((const int)  tolua_tonumber(tolua_S,3,0));
  const int nY = ((const int)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'OnLButtonUp'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->OnLButtonUp(nFlags,nX,nY);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'OnLButtonUp'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: OnLButtonDown of class  ControlTab */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlTab_OnLButtonDown00
static int tolua_CompileToLua_ControlTab_OnLButtonDown00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlTab",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"UINT",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlTab* self = (ControlTab*)  tolua_tousertype(tolua_S,1,0);
  UINT nFlags = *((UINT*)  tolua_tousertype(tolua_S,2,0));
  const int nX = ((const int)  tolua_tonumber(tolua_S,3,0));
  const int nY = ((const int)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'OnLButtonDown'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->OnLButtonDown(nFlags,nX,nY);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'OnLButtonDown'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: OnLButtonDBClick of class  ControlTab */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlTab_OnLButtonDBClick00
static int tolua_CompileToLua_ControlTab_OnLButtonDBClick00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlTab",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"UINT",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlTab* self = (ControlTab*)  tolua_tousertype(tolua_S,1,0);
  UINT nFlags = *((UINT*)  tolua_tousertype(tolua_S,2,0));
  const int nX = ((const int)  tolua_tonumber(tolua_S,3,0));
  const int nY = ((const int)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'OnLButtonDBClick'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->OnLButtonDBClick(nFlags,nX,nY);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'OnLButtonDBClick'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: OnRButtonUp of class  ControlTab */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlTab_OnRButtonUp00
static int tolua_CompileToLua_ControlTab_OnRButtonUp00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlTab",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"UINT",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlTab* self = (ControlTab*)  tolua_tousertype(tolua_S,1,0);
  UINT nFlags = *((UINT*)  tolua_tousertype(tolua_S,2,0));
  const int nX = ((const int)  tolua_tonumber(tolua_S,3,0));
  const int nY = ((const int)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'OnRButtonUp'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->OnRButtonUp(nFlags,nX,nY);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'OnRButtonUp'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: OnRButtonDown of class  ControlTab */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlTab_OnRButtonDown00
static int tolua_CompileToLua_ControlTab_OnRButtonDown00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlTab",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"UINT",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlTab* self = (ControlTab*)  tolua_tousertype(tolua_S,1,0);
  UINT nFlags = *((UINT*)  tolua_tousertype(tolua_S,2,0));
  const int nX = ((const int)  tolua_tonumber(tolua_S,3,0));
  const int nY = ((const int)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'OnRButtonDown'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->OnRButtonDown(nFlags,nX,nY);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'OnRButtonDown'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: OnRButtonDBClick of class  ControlTab */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlTab_OnRButtonDBClick00
static int tolua_CompileToLua_ControlTab_OnRButtonDBClick00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlTab",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"UINT",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlTab* self = (ControlTab*)  tolua_tousertype(tolua_S,1,0);
  UINT nFlags = *((UINT*)  tolua_tousertype(tolua_S,2,0));
  const int nX = ((const int)  tolua_tonumber(tolua_S,3,0));
  const int nY = ((const int)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'OnRButtonDBClick'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->OnRButtonDBClick(nFlags,nX,nY);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'OnRButtonDBClick'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: OnKeyDown of class  ControlTab */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlTab_OnKeyDown00
static int tolua_CompileToLua_ControlTab_OnKeyDown00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlTab",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"UINT",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlTab* self = (ControlTab*)  tolua_tousertype(tolua_S,1,0);
  UINT nChar = *((UINT*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'OnKeyDown'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->OnKeyDown(nChar);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'OnKeyDown'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: OnKeyUp of class  ControlTab */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlTab_OnKeyUp00
static int tolua_CompileToLua_ControlTab_OnKeyUp00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlTab",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"UINT",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlTab* self = (ControlTab*)  tolua_tousertype(tolua_S,1,0);
  UINT nChar = *((UINT*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'OnKeyUp'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->OnKeyUp(nChar);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'OnKeyUp'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: OnFrameChange of class  ControlTab */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlTab_OnFrameChange00
static int tolua_CompileToLua_ControlTab_OnFrameChange00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlTab",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlTab* self = (ControlTab*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'OnFrameChange'",NULL);
#endif
  {
   self->OnFrameChange();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'OnFrameChange'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  ControlTab */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlTab_new00
static int tolua_CompileToLua_ControlTab_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"ControlTab",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   ControlTab* tolua_ret = (ControlTab*)  new ControlTab();
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"ControlTab");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  ControlTab */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlTab_new00_local
static int tolua_CompileToLua_ControlTab_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"ControlTab",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   ControlTab* tolua_ret = (ControlTab*)  new ControlTab();
   tolua_pushusertype_and_takeownership(tolua_S,(void *)tolua_ret,"ControlTab");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: delete of class  ControlTab */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlTab_delete00
static int tolua_CompileToLua_ControlTab_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlTab",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlTab* self = (ControlTab*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'",NULL);
#endif
  delete self;
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: InitUIData of class  ControlText */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlText_InitUIData00
static int tolua_CompileToLua_ControlText_InitUIData00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlText",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"ControlObject",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"S_BaseData",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlText* self = (ControlText*)  tolua_tousertype(tolua_S,1,0);
  IN ControlObject* pFather = ((IN ControlObject*)  tolua_tousertype(tolua_S,2,0));
  IN S_BaseData* pData = ((IN S_BaseData*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'InitUIData'",NULL);
#endif
  {
   self->InitUIData(pFather,pData);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'InitUIData'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Render of class  ControlText */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlText_Render00
static int tolua_CompileToLua_ControlText_Render00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlText",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlText* self = (ControlText*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Render'",NULL);
#endif
  {
   self->Render();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Render'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: OnMouseMove of class  ControlText */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlText_OnMouseMove00
static int tolua_CompileToLua_ControlText_OnMouseMove00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlText",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"UINT",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlText* self = (ControlText*)  tolua_tousertype(tolua_S,1,0);
  UINT nFlags = *((UINT*)  tolua_tousertype(tolua_S,2,0));
  const int nX = ((const int)  tolua_tonumber(tolua_S,3,0));
  const int nY = ((const int)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'OnMouseMove'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->OnMouseMove(nFlags,nX,nY);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'OnMouseMove'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: OnLButtonDown of class  ControlText */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlText_OnLButtonDown00
static int tolua_CompileToLua_ControlText_OnLButtonDown00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlText",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"UINT",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlText* self = (ControlText*)  tolua_tousertype(tolua_S,1,0);
  UINT nFlags = *((UINT*)  tolua_tousertype(tolua_S,2,0));
  const int nX = ((const int)  tolua_tonumber(tolua_S,3,0));
  const int nY = ((const int)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'OnLButtonDown'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->OnLButtonDown(nFlags,nX,nY);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'OnLButtonDown'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetText of class  ControlText */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlText_SetText00
static int tolua_CompileToLua_ControlText_SetText00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlText",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlText* self = (ControlText*)  tolua_tousertype(tolua_S,1,0);
  const std::string szData = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
  int col = ((int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetText'",NULL);
#endif
  {
   self->SetText(szData,col);
   tolua_pushcppstring(tolua_S,(const char*)szData);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetText'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetText of class  ControlText */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlText_SetText01
static int tolua_CompileToLua_ControlText_SetText01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlText",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  ControlText* self = (ControlText*)  tolua_tousertype(tolua_S,1,0);
  const int nNum = ((const int)  tolua_tonumber(tolua_S,2,0));
  int col = ((int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetText'",NULL);
#endif
  {
   self->SetText(nNum,col);
  }
 }
 return 0;
tolua_lerror:
 return tolua_CompileToLua_ControlText_SetText00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetText of class  ControlText */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlText_SetText02
static int tolua_CompileToLua_ControlText_SetText02(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlText",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"const CHAR",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  ControlText* self = (ControlText*)  tolua_tousertype(tolua_S,1,0);
  const CHAR* szText = ((const CHAR*)  tolua_tousertype(tolua_S,2,0));
  int col = ((int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetText'",NULL);
#endif
  {
   self->SetText(szText,col);
  }
 }
 return 0;
tolua_lerror:
 return tolua_CompileToLua_ControlText_SetText01(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetTextW of class  ControlText */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlText_SetTextW00
static int tolua_CompileToLua_ControlText_SetTextW00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlText",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"const WCHAR",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlText* self = (ControlText*)  tolua_tousertype(tolua_S,1,0);
  const WCHAR* wText = ((const WCHAR*)  tolua_tousertype(tolua_S,2,0));
  int col = ((int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetTextW'",NULL);
#endif
  {
   self->SetTextW(wText,col);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetTextW'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetCurLine of class  ControlText */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlText_SetCurLine00
static int tolua_CompileToLua_ControlText_SetCurLine00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlText",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlText* self = (ControlText*)  tolua_tousertype(tolua_S,1,0);
  unsigned int nLine = ((unsigned int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetCurLine'",NULL);
#endif
  {
   self->SetCurLine(nLine);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetCurLine'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetText of class  ControlText */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlText_GetText00
static int tolua_CompileToLua_ControlText_GetText00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlText",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlText* self = (ControlText*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetText'",NULL);
#endif
  {
   const char* tolua_ret = (const char*)  self->GetText();
   tolua_pushstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetText'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Create of class  ControlText */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlText_Create00
static int tolua_CompileToLua_ControlText_Create00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlText",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"const RECT",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"const D3DCOLOR",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlText* self = (ControlText*)  tolua_tousertype(tolua_S,1,0);
  IN  const RECT* pRect = ((IN  const RECT*)  tolua_tousertype(tolua_S,2,0));
  const D3DCOLOR colText = *((const D3DCOLOR*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Create'",NULL);
#endif
  {
   self->Create(pRect,colText);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Create'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetText_HyberClickFun_2lua of class  ControlText */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlText_SetText_HyberClickFun_2lua00
static int tolua_CompileToLua_ControlText_SetText_HyberClickFun_2lua00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlText",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlText* self = (ControlText*)  tolua_tousertype(tolua_S,1,0);
  const char* luaTable = ((const char*)  tolua_tostring(tolua_S,2,0));
  const char* funName = ((const char*)  tolua_tostring(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetText_HyberClickFun_2lua'",NULL);
#endif
  {
   self->SetText_HyberClickFun_2lua(luaTable,funName);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetText_HyberClickFun_2lua'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setDesIconTip of class  ControlText */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlText_setDesIconTip00
static int tolua_CompileToLua_ControlText_setDesIconTip00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlText",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlText* self = (ControlText*)  tolua_tousertype(tolua_S,1,0);
  int nID = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setDesIconTip'",NULL);
#endif
  {
   self->setDesIconTip(nID);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setDesIconTip'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setShowDesIconTip of class  ControlText */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlText_setShowDesIconTip00
static int tolua_CompileToLua_ControlText_setShowDesIconTip00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlText",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlText* self = (ControlText*)  tolua_tousertype(tolua_S,1,0);
  bool show = ((bool)  tolua_toboolean(tolua_S,2,true));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setShowDesIconTip'",NULL);
#endif
  {
   self->setShowDesIconTip(show);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setShowDesIconTip'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Clear of class  ControlText */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlText_Clear00
static int tolua_CompileToLua_ControlText_Clear00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlText",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlText* self = (ControlText*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Clear'",NULL);
#endif
  {
   self->Clear();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Clear'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetIsShowLine of class  ControlText */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlText_SetIsShowLine00
static int tolua_CompileToLua_ControlText_SetIsShowLine00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlText",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlText* self = (ControlText*)  tolua_tousertype(tolua_S,1,0);
  bool bShow = ((bool)  tolua_toboolean(tolua_S,2,true));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetIsShowLine'",NULL);
#endif
  {
   self->SetIsShowLine(bShow);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetIsShowLine'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setTip of class  ControlText */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlText_setTip00
static int tolua_CompileToLua_ControlText_setTip00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlText",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlText* self = (ControlText*)  tolua_tousertype(tolua_S,1,0);
  const char* data = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setTip'",NULL);
#endif
  {
   self->setTip(data);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setTip'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setShowTip of class  ControlText */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlText_setShowTip00
static int tolua_CompileToLua_ControlText_setShowTip00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlText",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlText* self = (ControlText*)  tolua_tousertype(tolua_S,1,0);
  bool show = ((bool)  tolua_toboolean(tolua_S,2,true));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setShowTip'",NULL);
#endif
  {
   self->setShowTip(show);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setShowTip'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetSingleMaxTextCnt of class  ControlText */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlText_SetSingleMaxTextCnt00
static int tolua_CompileToLua_ControlText_SetSingleMaxTextCnt00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlText",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlText* self = (ControlText*)  tolua_tousertype(tolua_S,1,0);
  int cnt = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetSingleMaxTextCnt'",NULL);
#endif
  {
   self->SetSingleMaxTextCnt(cnt);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetSingleMaxTextCnt'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetOffsetY of class  ControlText */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlText_SetOffsetY00
static int tolua_CompileToLua_ControlText_SetOffsetY00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlText",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlText* self = (ControlText*)  tolua_tousertype(tolua_S,1,0);
  int oy = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetOffsetY'",NULL);
#endif
  {
   self->SetOffsetY(oy);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetOffsetY'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: str of class  STextData */
#ifndef TOLUA_DISABLE_tolua_get_ControlText__STextData_str
static int tolua_get_ControlText__STextData_str(lua_State* tolua_S)
{
  ControlText::STextData* self = (ControlText::STextData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'str'",NULL);
#endif
  tolua_pushusertype(tolua_S,(void*)&self->str,"std::wstring");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: str of class  STextData */
#ifndef TOLUA_DISABLE_tolua_set_ControlText__STextData_str
static int tolua_set_ControlText__STextData_str(lua_State* tolua_S)
{
  ControlText::STextData* self = (ControlText::STextData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'str'",NULL);
  if (!tolua_isusertype(tolua_S,2,"std::wstring",0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->str = *((std::wstring*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: nTextureID of class  STextData */
#ifndef TOLUA_DISABLE_tolua_get_ControlText__STextData_nTextureID
static int tolua_get_ControlText__STextData_nTextureID(lua_State* tolua_S)
{
  ControlText::STextData* self = (ControlText::STextData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nTextureID'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->nTextureID);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: nTextureID of class  STextData */
#ifndef TOLUA_DISABLE_tolua_set_ControlText__STextData_nTextureID
static int tolua_set_ControlText__STextData_nTextureID(lua_State* tolua_S)
{
  ControlText::STextData* self = (ControlText::STextData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nTextureID'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->nTextureID = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: rc of class  STextData */
#ifndef TOLUA_DISABLE_tolua_get_ControlText__STextData_rc
static int tolua_get_ControlText__STextData_rc(lua_State* tolua_S)
{
  ControlText::STextData* self = (ControlText::STextData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'rc'",NULL);
#endif
  tolua_pushusertype(tolua_S,(void*)&self->rc,"RECT");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: rc of class  STextData */
#ifndef TOLUA_DISABLE_tolua_set_ControlText__STextData_rc
static int tolua_set_ControlText__STextData_rc(lua_State* tolua_S)
{
  ControlText::STextData* self = (ControlText::STextData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'rc'",NULL);
  if (!tolua_isusertype(tolua_S,2,"RECT",0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->rc = *((RECT*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: nLine of class  STextData */
#ifndef TOLUA_DISABLE_tolua_get_ControlText__STextData_nLine
static int tolua_get_ControlText__STextData_nLine(lua_State* tolua_S)
{
  ControlText::STextData* self = (ControlText::STextData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nLine'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->nLine);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: nLine of class  STextData */
#ifndef TOLUA_DISABLE_tolua_set_ControlText__STextData_nLine
static int tolua_set_ControlText__STextData_nLine(lua_State* tolua_S)
{
  ControlText::STextData* self = (ControlText::STextData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nLine'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->nLine = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  SText */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlText_SText_new00
static int tolua_CompileToLua_ControlText_SText_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"ControlText::SText",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   ControlText::SText* tolua_ret = (ControlText::SText*)  new ControlText::SText();
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"ControlText::SText");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  SText */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlText_SText_new00_local
static int tolua_CompileToLua_ControlText_SText_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"ControlText::SText",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   ControlText::SText* tolua_ret = (ControlText::SText*)  new ControlText::SText();
   tolua_pushusertype_and_takeownership(tolua_S,(void *)tolua_ret,"ControlText::SText");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: type of class  SText */
#ifndef TOLUA_DISABLE_tolua_get_ControlText__SText_type
static int tolua_get_ControlText__SText_type(lua_State* tolua_S)
{
  ControlText::SText* self = (ControlText::SText*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'type'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->type);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: type of class  SText */
#ifndef TOLUA_DISABLE_tolua_set_ControlText__SText_type
static int tolua_set_ControlText__SText_type(lua_State* tolua_S)
{
  ControlText::SText* self = (ControlText::SText*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'type'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->type = ((EKeyType) (int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: col of class  SText */
#ifndef TOLUA_DISABLE_tolua_get_ControlText__SText_col
static int tolua_get_ControlText__SText_col(lua_State* tolua_S)
{
  ControlText::SText* self = (ControlText::SText*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'col'",NULL);
#endif
  tolua_pushusertype(tolua_S,(void*)&self->col,"DWORD");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: col of class  SText */
#ifndef TOLUA_DISABLE_tolua_set_ControlText__SText_col
static int tolua_set_ControlText__SText_col(lua_State* tolua_S)
{
  ControlText::SText* self = (ControlText::SText*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'col'",NULL);
  if (!tolua_isusertype(tolua_S,2,"DWORD",0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->col = *((DWORD*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: vtTextData of class  SText */
#ifndef TOLUA_DISABLE_tolua_get_ControlText__SText_vtTextData
static int tolua_get_ControlText__SText_vtTextData(lua_State* tolua_S)
{
  ControlText::SText* self = (ControlText::SText*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'vtTextData'",NULL);
#endif
  tolua_pushusertype(tolua_S,(void*)&self->vtTextData,"std::vector<ControlText::STextData>");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: vtTextData of class  SText */
#ifndef TOLUA_DISABLE_tolua_set_ControlText__SText_vtTextData
static int tolua_set_ControlText__SText_vtTextData(lua_State* tolua_S)
{
  ControlText::SText* self = (ControlText::SText*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'vtTextData'",NULL);
  if (!tolua_isusertype(tolua_S,2,"std::vector<ControlText::STextData>",0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->vtTextData = *((std::vector<ControlText::STextData>*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: bPtInText of class  SText */
#ifndef TOLUA_DISABLE_tolua_get_ControlText__SText_bPtInText
static int tolua_get_ControlText__SText_bPtInText(lua_State* tolua_S)
{
  ControlText::SText* self = (ControlText::SText*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'bPtInText'",NULL);
#endif
  tolua_pushboolean(tolua_S,(bool)self->bPtInText);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: bPtInText of class  SText */
#ifndef TOLUA_DISABLE_tolua_set_ControlText__SText_bPtInText
static int tolua_set_ControlText__SText_bPtInText(lua_State* tolua_S)
{
  ControlText::SText* self = (ControlText::SText*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'bPtInText'",NULL);
  if (!tolua_isboolean(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->bPtInText = ((bool)  tolua_toboolean(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* method: CheckPtInText of class  SText */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlText_SText_CheckPtInText00
static int tolua_CompileToLua_ControlText_SText_CheckPtInText00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlText::SText",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlText::SText* self = (ControlText::SText*)  tolua_tousertype(tolua_S,1,0);
  int x = ((int)  tolua_tonumber(tolua_S,2,0));
  int y = ((int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'CheckPtInText'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->CheckPtInText(x,y);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'CheckPtInText'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetTextW of class  SText */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlText_SText_GetTextW00
static int tolua_CompileToLua_ControlText_SText_GetTextW00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlText::SText",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"std::wstring",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlText::SText* self = (ControlText::SText*)  tolua_tousertype(tolua_S,1,0);
  std::wstring* pString = ((std::wstring*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetTextW'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->GetTextW(pString);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetTextW'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetTextA of class  SText */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlText_SText_GetTextA00
static int tolua_CompileToLua_ControlText_SText_GetTextA00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlText::SText",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlText::SText* self = (ControlText::SText*)  tolua_tousertype(tolua_S,1,0);
  std::string pString = ((std::string)  tolua_tocppstring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetTextA'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->GetTextA(&pString);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
   tolua_pushcppstring(tolua_S,(const char*)pString);
  }
 }
 return 2;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetTextA'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: WordBreak of class  ControlText */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlText_WordBreak00
static int tolua_CompileToLua_ControlText_WordBreak00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlText",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"std::wstring",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"const WCHAR",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlText* self = (ControlText*)  tolua_tousertype(tolua_S,1,0);
  std::wstring* pOutText = ((std::wstring*)  tolua_tousertype(tolua_S,2,0));
  const WCHAR* wInText = ((const WCHAR*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'WordBreak'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->WordBreak(pOutText,wInText);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'WordBreak'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetTextData of class  ControlText */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlText_GetTextData00
static int tolua_CompileToLua_ControlText_GetTextData00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlText",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"const std::wstring",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isusertype(tolua_S,4,"std::wstring",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,5,"DWORD",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlText* self = (ControlText*)  tolua_tousertype(tolua_S,1,0);
  const std::wstring* strString = ((const std::wstring*)  tolua_tousertype(tolua_S,2,0));
  unsigned int pnOff = ((unsigned int)  tolua_tonumber(tolua_S,3,0));
  std::wstring* pstrText = ((std::wstring*)  tolua_tousertype(tolua_S,4,0));
  DWORD* dwKey = ((DWORD*)  tolua_tousertype(tolua_S,5,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetTextData'",NULL);
#endif
  {
   EKeyType tolua_ret = (EKeyType)  self->GetTextData(*strString,&pnOff,pstrText,dwKey);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
   tolua_pushnumber(tolua_S,(lua_Number)pnOff);
  }
 }
 return 2;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetTextData'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: CalculatePoint of class  ControlText */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlText_CalculatePoint00
static int tolua_CompileToLua_ControlText_CalculatePoint00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlText",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlText* self = (ControlText*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'CalculatePoint'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->CalculatePoint();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'CalculatePoint'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: CheckDrawMode of class  ControlText */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlText_CheckDrawMode00
static int tolua_CompileToLua_ControlText_CheckDrawMode00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlText",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlText* self = (ControlText*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'CheckDrawMode'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->CheckDrawMode();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'CheckDrawMode'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: CPtoX of class  ControlText */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlText_CPtoX00
static int tolua_CompileToLua_ControlText_CPtoX00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlText",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"SCRIPT_STRING_ANALYSIS",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isusertype(tolua_S,4,"BOOL",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlText* self = (ControlText*)  tolua_tousertype(tolua_S,1,0);
  SCRIPT_STRING_ANALYSIS* analysis = ((SCRIPT_STRING_ANALYSIS*)  tolua_tousertype(tolua_S,2,0));
  int nCP = ((int)  tolua_tonumber(tolua_S,3,0));
  BOOL bTrail = *((BOOL*)  tolua_tousertype(tolua_S,4,0));
  int pX = ((int)  tolua_tonumber(tolua_S,5,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'CPtoX'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->CPtoX(analysis,nCP,bTrail,&pX);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
   tolua_pushnumber(tolua_S,(lua_Number)pX);
  }
 }
 return 2;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'CPtoX'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: XtoCP of class  ControlText */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlText_XtoCP00
static int tolua_CompileToLua_ControlText_XtoCP00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlText",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"SCRIPT_STRING_ANALYSIS",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"std::wstring",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,6,0,&tolua_err) ||
     !tolua_isusertype(tolua_S,7,"BOOL",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,8,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlText* self = (ControlText*)  tolua_tousertype(tolua_S,1,0);
  SCRIPT_STRING_ANALYSIS* analysis = ((SCRIPT_STRING_ANALYSIS*)  tolua_tousertype(tolua_S,2,0));
  std::wstring* str = ((std::wstring*)  tolua_tousertype(tolua_S,3,0));
  int nX = ((int)  tolua_tonumber(tolua_S,4,0));
  int pCP = ((int)  tolua_tonumber(tolua_S,5,0));
  int pnTrail = ((int)  tolua_tonumber(tolua_S,6,0));
  BOOL* pbEnd = ((BOOL*)  tolua_tousertype(tolua_S,7,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'XtoCP'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->XtoCP(analysis,*str,nX,&pCP,&pnTrail,pbEnd);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
   tolua_pushnumber(tolua_S,(lua_Number)pCP);
   tolua_pushnumber(tolua_S,(lua_Number)pnTrail);
  }
 }
 return 3;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'XtoCP'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: MoveTextDataPos of class  ControlText */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlText_MoveTextDataPos00
static int tolua_CompileToLua_ControlText_MoveTextDataPos00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlText",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlText* self = (ControlText*)  tolua_tousertype(tolua_S,1,0);
  int nLine = ((int)  tolua_tonumber(tolua_S,2,0));
  int nEndIndex = ((int)  tolua_tonumber(tolua_S,3,0));
  int nOffsetX = ((int)  tolua_tonumber(tolua_S,4,0));
  int nOffsetY = ((int)  tolua_tonumber(tolua_S,5,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'MoveTextDataPos'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->MoveTextDataPos(nLine,nEndIndex,nOffsetX,nOffsetY);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'MoveTextDataPos'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  ControlText */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlText_new00
static int tolua_CompileToLua_ControlText_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"ControlText",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   ControlText* tolua_ret = (ControlText*)  new ControlText();
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"ControlText");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  ControlText */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlText_new00_local
static int tolua_CompileToLua_ControlText_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"ControlText",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   ControlText* tolua_ret = (ControlText*)  new ControlText();
   tolua_pushusertype_and_takeownership(tolua_S,(void *)tolua_ret,"ControlText");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: delete of class  ControlText */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_ControlText_delete00
static int tolua_CompileToLua_ControlText_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ControlText",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ControlText* self = (ControlText*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'",NULL);
#endif
  delete self;
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Render of class  MouseManager */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_MouseManager_Render00
static int tolua_CompileToLua_MouseManager_Render00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"MouseManager",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  MouseManager* self = (MouseManager*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Render'",NULL);
#endif
  {
   self->Render();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Render'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  MouseManager */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_MouseManager_new00
static int tolua_CompileToLua_MouseManager_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"MouseManager",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   MouseManager* tolua_ret = (MouseManager*)  new MouseManager();
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"MouseManager");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  MouseManager */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_MouseManager_new00_local
static int tolua_CompileToLua_MouseManager_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"MouseManager",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   MouseManager* tolua_ret = (MouseManager*)  new MouseManager();
   tolua_pushusertype_and_takeownership(tolua_S,(void *)tolua_ret,"MouseManager");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: delete of class  MouseManager */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_MouseManager_delete00
static int tolua_CompileToLua_MouseManager_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"MouseManager",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  MouseManager* self = (MouseManager*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'",NULL);
#endif
  delete self;
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  S_UI */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_UiManager_S_UI_new00
static int tolua_CompileToLua_UiManager_S_UI_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"UiManager::S_UI",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   UiManager::S_UI* tolua_ret = (UiManager::S_UI*)  new UiManager::S_UI();
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"UiManager::S_UI");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  S_UI */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_UiManager_S_UI_new00_local
static int tolua_CompileToLua_UiManager_S_UI_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"UiManager::S_UI",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   UiManager::S_UI* tolua_ret = (UiManager::S_UI*)  new UiManager::S_UI();
   tolua_pushusertype_and_takeownership(tolua_S,(void *)tolua_ret,"UiManager::S_UI");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Release of class  S_UI */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_UiManager_S_UI_Release00
static int tolua_CompileToLua_UiManager_S_UI_Release00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UiManager::S_UI",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UiManager::S_UI* self = (UiManager::S_UI*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Release'",NULL);
#endif
  {
   self->Release();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Release'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: m_strFileName of class  S_UI */
#ifndef TOLUA_DISABLE_tolua_get_UiManager__S_UI_m_strFileName
static int tolua_get_UiManager__S_UI_m_strFileName(lua_State* tolua_S)
{
  UiManager::S_UI* self = (UiManager::S_UI*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_strFileName'",NULL);
#endif
  tolua_pushcppstring(tolua_S,(const char*)self->m_strFileName);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: m_strFileName of class  S_UI */
#ifndef TOLUA_DISABLE_tolua_set_UiManager__S_UI_m_strFileName
static int tolua_set_UiManager__S_UI_m_strFileName(lua_State* tolua_S)
{
  UiManager::S_UI* self = (UiManager::S_UI*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_strFileName'",NULL);
  if (!tolua_iscppstring(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->m_strFileName = ((std::string)  tolua_tocppstring(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: m_pUI of class  S_UI */
#ifndef TOLUA_DISABLE_tolua_get_UiManager__S_UI_m_pUI_ptr
static int tolua_get_UiManager__S_UI_m_pUI_ptr(lua_State* tolua_S)
{
  UiManager::S_UI* self = (UiManager::S_UI*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_pUI'",NULL);
#endif
  tolua_pushusertype(tolua_S,(void*)self->m_pUI,"ControlFrame");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: m_pUI of class  S_UI */
#ifndef TOLUA_DISABLE_tolua_set_UiManager__S_UI_m_pUI_ptr
static int tolua_set_UiManager__S_UI_m_pUI_ptr(lua_State* tolua_S)
{
  UiManager::S_UI* self = (UiManager::S_UI*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_pUI'",NULL);
  if (!tolua_isusertype(tolua_S,2,"ControlFrame",0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->m_pUI = ((ControlFrame*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: m_bNeedRelease of class  S_UI */
#ifndef TOLUA_DISABLE_tolua_get_UiManager__S_UI_m_bNeedRelease
static int tolua_get_UiManager__S_UI_m_bNeedRelease(lua_State* tolua_S)
{
  UiManager::S_UI* self = (UiManager::S_UI*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_bNeedRelease'",NULL);
#endif
  tolua_pushboolean(tolua_S,(bool)self->m_bNeedRelease);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: m_bNeedRelease of class  S_UI */
#ifndef TOLUA_DISABLE_tolua_set_UiManager__S_UI_m_bNeedRelease
static int tolua_set_UiManager__S_UI_m_bNeedRelease(lua_State* tolua_S)
{
  UiManager::S_UI* self = (UiManager::S_UI*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_bNeedRelease'",NULL);
  if (!tolua_isboolean(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->m_bNeedRelease = ((bool)  tolua_toboolean(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* method: FrameMove of class  UiManager */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_UiManager_FrameMove00
static int tolua_CompileToLua_UiManager_FrameMove00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UiManager",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UiManager* self = (UiManager*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'FrameMove'",NULL);
#endif
  {
   self->FrameMove();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'FrameMove'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Render of class  UiManager */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_UiManager_Render00
static int tolua_CompileToLua_UiManager_Render00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UiManager",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UiManager* self = (UiManager*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Render'",NULL);
#endif
  {
   self->Render();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Render'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: RenderTips of class  UiManager */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_UiManager_RenderTips00
static int tolua_CompileToLua_UiManager_RenderTips00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UiManager",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UiManager* self = (UiManager*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'RenderTips'",NULL);
#endif
  {
   self->RenderTips();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'RenderTips'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: InvalidateDeviceObjects of class  UiManager */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_UiManager_InvalidateDeviceObjects00
static int tolua_CompileToLua_UiManager_InvalidateDeviceObjects00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UiManager",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UiManager* self = (UiManager*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'InvalidateDeviceObjects'",NULL);
#endif
  {
   self->InvalidateDeviceObjects();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'InvalidateDeviceObjects'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: RestoreDeviceObjects of class  UiManager */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_UiManager_RestoreDeviceObjects00
static int tolua_CompileToLua_UiManager_RestoreDeviceObjects00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UiManager",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UiManager* self = (UiManager*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'RestoreDeviceObjects'",NULL);
#endif
  {
   self->RestoreDeviceObjects();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'RestoreDeviceObjects'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: MsgProc of class  UiManager */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_UiManager_MsgProc00
static int tolua_CompileToLua_UiManager_MsgProc00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UiManager",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"HWND",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"UINT",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,4,"WPARAM",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,5,"LPARAM",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UiManager* self = (UiManager*)  tolua_tousertype(tolua_S,1,0);
  HWND hWnd = *((HWND*)  tolua_tousertype(tolua_S,2,0));
  UINT msg = *((UINT*)  tolua_tousertype(tolua_S,3,0));
  WPARAM wParam = *((WPARAM*)  tolua_tousertype(tolua_S,4,0));
  LPARAM lParam = *((LPARAM*)  tolua_tousertype(tolua_S,5,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'MsgProc'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->MsgProc(hWnd,msg,wParam,lParam);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'MsgProc'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetPlaySoundFun_2lua of class  UiManager */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_UiManager_SetPlaySoundFun_2lua00
static int tolua_CompileToLua_UiManager_SetPlaySoundFun_2lua00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UiManager",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UiManager* self = (UiManager*)  tolua_tousertype(tolua_S,1,0);
  const char* luaTable = ((const char*)  tolua_tostring(tolua_S,2,0));
  const char* funName = ((const char*)  tolua_tostring(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetPlaySoundFun_2lua'",NULL);
#endif
  {
   self->SetPlaySoundFun_2lua(luaTable,funName);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetPlaySoundFun_2lua'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: PlaySound of class  UiManager */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_UiManager_PlaySound00
static int tolua_CompileToLua_UiManager_PlaySound00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UiManager",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UiManager* self = (UiManager*)  tolua_tousertype(tolua_S,1,0);
  std::string strFileName = ((std::string)  tolua_tocppstring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'PlaySound'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->PlaySound(strFileName);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
   tolua_pushcppstring(tolua_S,(const char*)strFileName);
  }
 }
 return 2;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'PlaySound'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: AddFrame of class  UiManager */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_UiManager_AddFrame00
static int tolua_CompileToLua_UiManager_AddFrame00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UiManager",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isboolean(tolua_S,3,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UiManager* self = (UiManager*)  tolua_tousertype(tolua_S,1,0);
  IN  const char* szFileName = ((IN  const char*)  tolua_tostring(tolua_S,2,0));
  bool bAllVisable = ((bool)  tolua_toboolean(tolua_S,3,false));
  UI_Render_Layer layer = ((UI_Render_Layer) (int)  tolua_tonumber(tolua_S,4,UI_Render_LayerFirst));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'AddFrame'",NULL);
#endif
  {
   DWORD tolua_ret = (DWORD)  self->AddFrame(szFileName,bAllVisable,layer);
   {
#ifdef __cplusplus
    void* tolua_obj = new DWORD(tolua_ret);
    tolua_pushusertype_and_takeownership(tolua_S,tolua_obj,"DWORD");
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(DWORD));
    tolua_pushusertype_and_takeownership(tolua_S,tolua_obj,"DWORD");
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'AddFrame'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: RemoveFrame of class  UiManager */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_UiManager_RemoveFrame00
static int tolua_CompileToLua_UiManager_RemoveFrame00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UiManager",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UiManager* self = (UiManager*)  tolua_tousertype(tolua_S,1,0);
  IN  const char* szFileName = ((IN  const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'RemoveFrame'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->RemoveFrame(szFileName);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'RemoveFrame'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: AddFrame of class  UiManager */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_UiManager_AddFrame01
static int tolua_CompileToLua_UiManager_AddFrame01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UiManager",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"ControlFrame",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,3,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  UiManager* self = (UiManager*)  tolua_tousertype(tolua_S,1,0);
  IN ControlFrame* pObject = ((IN ControlFrame*)  tolua_tousertype(tolua_S,2,0));
  bool bAllVisable = ((bool)  tolua_toboolean(tolua_S,3,false));
  UI_Render_Layer layer = ((UI_Render_Layer) (int)  tolua_tonumber(tolua_S,4,UI_Render_LayerFirst));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'AddFrame'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->AddFrame(pObject,bAllVisable,layer);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
tolua_lerror:
 return tolua_CompileToLua_UiManager_AddFrame00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: RemoveFrame of class  UiManager */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_UiManager_RemoveFrame01
static int tolua_CompileToLua_UiManager_RemoveFrame01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UiManager",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"const ControlFrame",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  UiManager* self = (UiManager*)  tolua_tousertype(tolua_S,1,0);
  IN  const ControlFrame* pObject = ((IN  const ControlFrame*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'RemoveFrame'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->RemoveFrame(pObject);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
tolua_lerror:
 return tolua_CompileToLua_UiManager_RemoveFrame00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: HasModalWindow of class  UiManager */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_UiManager_HasModalWindow00
static int tolua_CompileToLua_UiManager_HasModalWindow00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UiManager",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UiManager* self = (UiManager*)  tolua_tousertype(tolua_S,1,0);
  int layer = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'HasModalWindow'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->HasModalWindow(layer);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'HasModalWindow'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: OnFrameRun of class  UiManager */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_UiManager_OnFrameRun00
static int tolua_CompileToLua_UiManager_OnFrameRun00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UiManager",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"ControlFrame::funRun",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UiManager* self = (UiManager*)  tolua_tousertype(tolua_S,1,0);
  IN  const char* szFrameID = ((IN  const char*)  tolua_tostring(tolua_S,2,0));
  IN ControlFrame::funRun pFun = *((IN ControlFrame::funRun*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'OnFrameRun'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->OnFrameRun(szFrameID,pFun);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'OnFrameRun'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: OnFrameRender of class  UiManager */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_UiManager_OnFrameRender00
static int tolua_CompileToLua_UiManager_OnFrameRender00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UiManager",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"ControlFrame::funRender",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,4,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UiManager* self = (UiManager*)  tolua_tousertype(tolua_S,1,0);
  IN  const char* szFrameID = ((IN  const char*)  tolua_tostring(tolua_S,2,0));
  IN ControlFrame::funRender pFun = *((IN ControlFrame::funRender*)  tolua_tousertype(tolua_S,3,0));
  const bool bBeforeRender = ((const bool)  tolua_toboolean(tolua_S,4,false));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'OnFrameRender'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->OnFrameRender(szFrameID,pFun,bBeforeRender);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'OnFrameRender'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: OnButtonClick of class  UiManager */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_UiManager_OnButtonClick00
static int tolua_CompileToLua_UiManager_OnButtonClick00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UiManager",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isusertype(tolua_S,4,"ControlButton::funOnButtonClick",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UiManager* self = (UiManager*)  tolua_tousertype(tolua_S,1,0);
  IN  const char* szFrameID = ((IN  const char*)  tolua_tostring(tolua_S,2,0));
  IN  const char* szControlID = ((IN  const char*)  tolua_tostring(tolua_S,3,0));
  IN ControlButton::funOnButtonClick pFun = *((IN ControlButton::funOnButtonClick*)  tolua_tousertype(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'OnButtonClick'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->OnButtonClick(szFrameID,szControlID,pFun);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'OnButtonClick'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: OnEditEnter of class  UiManager */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_UiManager_OnEditEnter00
static int tolua_CompileToLua_UiManager_OnEditEnter00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UiManager",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isusertype(tolua_S,4,"ControlEdit::funOnEnter",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UiManager* self = (UiManager*)  tolua_tousertype(tolua_S,1,0);
  IN  const char* szFrameID = ((IN  const char*)  tolua_tostring(tolua_S,2,0));
  IN  const char* szControlID = ((IN  const char*)  tolua_tostring(tolua_S,3,0));
  IN ControlEdit::funOnEnter pFun = *((IN ControlEdit::funOnEnter*)  tolua_tousertype(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'OnEditEnter'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->OnEditEnter(szFrameID,szControlID,pFun);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'OnEditEnter'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: OnCheckBoxCheck of class  UiManager */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_UiManager_OnCheckBoxCheck00
static int tolua_CompileToLua_UiManager_OnCheckBoxCheck00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UiManager",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isusertype(tolua_S,4,"ControlCheckBox::funOnCheck",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UiManager* self = (UiManager*)  tolua_tousertype(tolua_S,1,0);
  IN  const char* szFrameID = ((IN  const char*)  tolua_tostring(tolua_S,2,0));
  IN  const char* szControlID = ((IN  const char*)  tolua_tostring(tolua_S,3,0));
  IN ControlCheckBox::funOnCheck pFun = *((IN ControlCheckBox::funOnCheck*)  tolua_tousertype(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'OnCheckBoxCheck'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->OnCheckBoxCheck(szFrameID,szControlID,pFun);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'OnCheckBoxCheck'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: OnListSelectChange of class  UiManager */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_UiManager_OnListSelectChange00
static int tolua_CompileToLua_UiManager_OnListSelectChange00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UiManager",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isusertype(tolua_S,4,"ControlList::funSelectChange",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UiManager* self = (UiManager*)  tolua_tousertype(tolua_S,1,0);
  IN  const char* szFrameID = ((IN  const char*)  tolua_tostring(tolua_S,2,0));
  IN  const char* szControlID = ((IN  const char*)  tolua_tostring(tolua_S,3,0));
  IN ControlList::funSelectChange pFun = *((IN ControlList::funSelectChange*)  tolua_tousertype(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'OnListSelectChange'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->OnListSelectChange(szFrameID,szControlID,pFun);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'OnListSelectChange'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: OnListLDBClick of class  UiManager */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_UiManager_OnListLDBClick00
static int tolua_CompileToLua_UiManager_OnListLDBClick00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UiManager",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isusertype(tolua_S,4,"ControlList::funLDBClick",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UiManager* self = (UiManager*)  tolua_tousertype(tolua_S,1,0);
  IN  const char* szFrameID = ((IN  const char*)  tolua_tostring(tolua_S,2,0));
  IN  const char* szControlID = ((IN  const char*)  tolua_tostring(tolua_S,3,0));
  IN ControlList::funLDBClick pFun = *((IN ControlList::funLDBClick*)  tolua_tousertype(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'OnListLDBClick'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->OnListLDBClick(szFrameID,szControlID,pFun);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'OnListLDBClick'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: OnIconDragOn of class  UiManager */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_UiManager_OnIconDragOn00
static int tolua_CompileToLua_UiManager_OnIconDragOn00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UiManager",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isusertype(tolua_S,4,"ControlIconDrag::funDragOn",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UiManager* self = (UiManager*)  tolua_tousertype(tolua_S,1,0);
  IN  const char* szFrameID = ((IN  const char*)  tolua_tostring(tolua_S,2,0));
  IN  const char* szControlID = ((IN  const char*)  tolua_tostring(tolua_S,3,0));
  IN ControlIconDrag::funDragOn pFun = *((IN ControlIconDrag::funDragOn*)  tolua_tousertype(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'OnIconDragOn'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->OnIconDragOn(szFrameID,szControlID,pFun);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'OnIconDragOn'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: OnIconLDBClick of class  UiManager */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_UiManager_OnIconLDBClick00
static int tolua_CompileToLua_UiManager_OnIconLDBClick00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UiManager",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isusertype(tolua_S,4,"ControlIconDrag::funLDBClick",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UiManager* self = (UiManager*)  tolua_tousertype(tolua_S,1,0);
  IN  const char* szFrameID = ((IN  const char*)  tolua_tostring(tolua_S,2,0));
  IN  const char* szControlID = ((IN  const char*)  tolua_tostring(tolua_S,3,0));
  IN ControlIconDrag::funLDBClick pFun = *((IN ControlIconDrag::funLDBClick*)  tolua_tousertype(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'OnIconLDBClick'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->OnIconLDBClick(szFrameID,szControlID,pFun);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'OnIconLDBClick'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: OnIconRButtonUp of class  UiManager */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_UiManager_OnIconRButtonUp00
static int tolua_CompileToLua_UiManager_OnIconRButtonUp00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UiManager",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isusertype(tolua_S,4,"ControlIconDrag::funRButtonUp",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UiManager* self = (UiManager*)  tolua_tousertype(tolua_S,1,0);
  IN  const char* szFrameID = ((IN  const char*)  tolua_tostring(tolua_S,2,0));
  IN  const char* szControlID = ((IN  const char*)  tolua_tostring(tolua_S,3,0));
  IN ControlIconDrag::funRButtonUp pFun = *((IN ControlIconDrag::funRButtonUp*)  tolua_tousertype(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'OnIconRButtonUp'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->OnIconRButtonUp(szFrameID,szControlID,pFun);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'OnIconRButtonUp'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: OnScrollBarUpdatePos of class  UiManager */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_UiManager_OnScrollBarUpdatePos00
static int tolua_CompileToLua_UiManager_OnScrollBarUpdatePos00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UiManager",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isusertype(tolua_S,4,"ControlScrollBar::funUpdatePos",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UiManager* self = (UiManager*)  tolua_tousertype(tolua_S,1,0);
  IN  const char* szFrameID = ((IN  const char*)  tolua_tostring(tolua_S,2,0));
  IN  const char* szControlID = ((IN  const char*)  tolua_tostring(tolua_S,3,0));
  IN ControlScrollBar::funUpdatePos pFun = *((IN ControlScrollBar::funUpdatePos*)  tolua_tousertype(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'OnScrollBarUpdatePos'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->OnScrollBarUpdatePos(szFrameID,szControlID,pFun);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'OnScrollBarUpdatePos'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: OnScrollBarExUpdatePos of class  UiManager */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_UiManager_OnScrollBarExUpdatePos00
static int tolua_CompileToLua_UiManager_OnScrollBarExUpdatePos00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UiManager",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isusertype(tolua_S,4,"ControlScrollBar::funUpdatePos",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UiManager* self = (UiManager*)  tolua_tousertype(tolua_S,1,0);
  IN  const char* szFrameID = ((IN  const char*)  tolua_tostring(tolua_S,2,0));
  IN  const char* szControlID = ((IN  const char*)  tolua_tostring(tolua_S,3,0));
  IN ControlScrollBar::funUpdatePos pFun = *((IN ControlScrollBar::funUpdatePos*)  tolua_tousertype(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'OnScrollBarExUpdatePos'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->OnScrollBarExUpdatePos(szFrameID,szControlID,pFun);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'OnScrollBarExUpdatePos'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: OnComboBoxChange of class  UiManager */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_UiManager_OnComboBoxChange00
static int tolua_CompileToLua_UiManager_OnComboBoxChange00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UiManager",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isusertype(tolua_S,4,"ControlComboBox::funOnChange",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UiManager* self = (UiManager*)  tolua_tousertype(tolua_S,1,0);
  IN  const char* szFrameID = ((IN  const char*)  tolua_tostring(tolua_S,2,0));
  IN  const char* szControlID = ((IN  const char*)  tolua_tostring(tolua_S,3,0));
  IN ControlComboBox::funOnChange pFun = *((IN ControlComboBox::funOnChange*)  tolua_tousertype(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'OnComboBoxChange'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->OnComboBoxChange(szFrameID,szControlID,pFun);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'OnComboBoxChange'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: OnTextHyberClick of class  UiManager */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_UiManager_OnTextHyberClick00
static int tolua_CompileToLua_UiManager_OnTextHyberClick00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UiManager",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isusertype(tolua_S,4,"ControlText::funHyberClick",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UiManager* self = (UiManager*)  tolua_tousertype(tolua_S,1,0);
  IN  const char* szFrameID = ((IN  const char*)  tolua_tostring(tolua_S,2,0));
  IN  const char* szControlID = ((IN  const char*)  tolua_tostring(tolua_S,3,0));
  IN ControlText::funHyberClick pFun = *((IN ControlText::funHyberClick*)  tolua_tousertype(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'OnTextHyberClick'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->OnTextHyberClick(szFrameID,szControlID,pFun);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'OnTextHyberClick'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: FindControl of class  UiManager */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_UiManager_FindControl00
static int tolua_CompileToLua_UiManager_FindControl00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UiManager",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UiManager* self = (UiManager*)  tolua_tousertype(tolua_S,1,0);
  IN  const char* szFrameID = ((IN  const char*)  tolua_tostring(tolua_S,2,0));
  IN  const char* szControlID = ((IN  const char*)  tolua_tostring(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'FindControl'",NULL);
#endif
  {
   ControlObject* tolua_ret = (ControlObject*)  self->FindControl(szFrameID,szControlID);
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"ControlObject");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'FindControl'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: FindFrame of class  UiManager */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_UiManager_FindFrame00
static int tolua_CompileToLua_UiManager_FindFrame00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UiManager",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UiManager* self = (UiManager*)  tolua_tousertype(tolua_S,1,0);
  IN  const char* szFrameID = ((IN  const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'FindFrame'",NULL);
#endif
  {
   ControlObject* tolua_ret = (ControlObject*)  self->FindFrame(szFrameID);
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"ControlObject");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'FindFrame'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: CreateWidget of class  UiManager */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_UiManager_CreateWidget00
static int tolua_CompileToLua_UiManager_CreateWidget00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UiManager",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"S_BaseData",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"ControlObject",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UiManager* self = (UiManager*)  tolua_tousertype(tolua_S,1,0);
  S_BaseData* sBaseData = ((S_BaseData*)  tolua_tousertype(tolua_S,2,0));
  ControlObject* pFather = ((ControlObject*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'CreateWidget'",NULL);
#endif
  {
   ControlObject* tolua_ret = (ControlObject*)  self->CreateWidget(sBaseData,pFather);
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"ControlObject");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'CreateWidget'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Compositor of class  UiManager */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_UiManager_Compositor00
static int tolua_CompileToLua_UiManager_Compositor00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UiManager",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UiManager* self = (UiManager*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Compositor'",NULL);
#endif
  {
   self->Compositor();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Compositor'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: ToTop of class  UiManager */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_UiManager_ToTop00
static int tolua_CompileToLua_UiManager_ToTop00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UiManager",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"const ControlObject",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"ControlObject",1,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UiManager* self = (UiManager*)  tolua_tousertype(tolua_S,1,0);
  IN  const ControlObject* pObject = ((IN  const ControlObject*)  tolua_tousertype(tolua_S,2,0));
  ControlObject* pObjectPos = ((ControlObject*)  tolua_tousertype(tolua_S,3,NULL));
  int toIndex = ((int)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'ToTop'",NULL);
#endif
  {
   ControlObject* tolua_ret = (ControlObject*)  self->ToTop(pObject,pObjectPos,toIndex);
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"ControlObject");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'ToTop'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: ToBottom of class  UiManager */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_UiManager_ToBottom00
static int tolua_CompileToLua_UiManager_ToBottom00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UiManager",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"const ControlObject",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UiManager* self = (UiManager*)  tolua_tousertype(tolua_S,1,0);
  IN  const ControlObject* pObject = ((IN  const ControlObject*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'ToBottom'",NULL);
#endif
  {
   ControlObject* tolua_ret = (ControlObject*)  self->ToBottom(pObject);
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"ControlObject");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'ToBottom'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: IsMouseInUI of class  UiManager */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_UiManager_IsMouseInUI00
static int tolua_CompileToLua_UiManager_IsMouseInUI00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UiManager",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UiManager* self = (UiManager*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'IsMouseInUI'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->IsMouseInUI();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'IsMouseInUI'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetFrameFocus of class  UiManager */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_UiManager_GetFrameFocus00
static int tolua_CompileToLua_UiManager_GetFrameFocus00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UiManager",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UiManager* self = (UiManager*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetFrameFocus'",NULL);
#endif
  {
   ControlObject* tolua_ret = (ControlObject*)  self->GetFrameFocus();
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"ControlObject");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetFrameFocus'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: HideDlg of class  UiManager */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_UiManager_HideDlg00
static int tolua_CompileToLua_UiManager_HideDlg00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UiManager",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UiManager* self = (UiManager*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'HideDlg'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->HideDlg();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'HideDlg'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetFocus of class  UiManager */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_UiManager_SetFocus00
static int tolua_CompileToLua_UiManager_SetFocus00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UiManager",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"ControlObject",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UiManager* self = (UiManager*)  tolua_tousertype(tolua_S,1,0);
  ControlObject* pObj = ((ControlObject*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetFocus'",NULL);
#endif
  {
   self->SetFocus(pObj);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetFocus'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetFocus of class  UiManager */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_UiManager_GetFocus00
static int tolua_CompileToLua_UiManager_GetFocus00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UiManager",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UiManager* self = (UiManager*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetFocus'",NULL);
#endif
  {
   ControlObject* tolua_ret = (ControlObject*)  self->GetFocus();
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"ControlObject");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetFocus'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isInUI of class  UiManager */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_UiManager_isInUI00
static int tolua_CompileToLua_UiManager_isInUI00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UiManager",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UiManager* self = (UiManager*)  tolua_tousertype(tolua_S,1,0);
  int x = ((int)  tolua_tonumber(tolua_S,2,0));
  int y = ((int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isInUI'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->isInUI(x,y);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isInUI'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: UpdataFrame of class  UiManager */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_UiManager_UpdataFrame00
static int tolua_CompileToLua_UiManager_UpdataFrame00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UiManager",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UiManager* self = (UiManager*)  tolua_tousertype(tolua_S,1,0);
  const int nX = ((const int)  tolua_tonumber(tolua_S,2,0));
  const int nY = ((const int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'UpdataFrame'",NULL);
#endif
  {
   self->UpdataFrame(nX,nY);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'UpdataFrame'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Cover of class  UiManager */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_UiManager_Cover00
static int tolua_CompileToLua_UiManager_Cover00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UiManager",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UiManager* self = (UiManager*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Cover'",NULL);
#endif
  {
   self->Cover();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Cover'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Destroy of class  UiManager */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_UiManager_Destroy00
static int tolua_CompileToLua_UiManager_Destroy00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UiManager",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UiManager* self = (UiManager*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Destroy'",NULL);
#endif
  {
   self->Destroy();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Destroy'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  UiManager */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_UiManager_new00
static int tolua_CompileToLua_UiManager_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"UiManager",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   UiManager* tolua_ret = (UiManager*)  new UiManager();
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"UiManager");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  UiManager */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_UiManager_new00_local
static int tolua_CompileToLua_UiManager_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"UiManager",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   UiManager* tolua_ret = (UiManager*)  new UiManager();
   tolua_pushusertype_and_takeownership(tolua_S,(void *)tolua_ret,"UiManager");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: delete of class  UiManager */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_UiManager_delete00
static int tolua_CompileToLua_UiManager_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UiManager",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UiManager* self = (UiManager*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'",NULL);
#endif
  delete self;
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: irr::UiManagerInstance */
#ifndef TOLUA_DISABLE_tolua_CompileToLua_irr_UiManagerInstance00
static int tolua_CompileToLua_irr_UiManagerInstance00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnoobj(tolua_S,1,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   UiManager* tolua_ret = (UiManager*)  irr::UiManagerInstance();
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"UiManager");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'UiManagerInstance'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* Open function */
TOLUA_API int tolua_CompileToLua_open (lua_State* tolua_S)
{
 tolua_open(tolua_S);
 tolua_reg_types(tolua_S);
 tolua_module(tolua_S,NULL,1);
 tolua_beginmodule(tolua_S,NULL);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"ControlButton","ControlButton","ControlObject",tolua_collect_ControlButton);
  #else
  tolua_cclass(tolua_S,"ControlButton","ControlButton","ControlObject",NULL);
  #endif
  tolua_beginmodule(tolua_S,"ControlButton");
   tolua_function(tolua_S,"Render",tolua_CompileToLua_ControlButton_Render00);
   tolua_function(tolua_S,"OnKeyDown",tolua_CompileToLua_ControlButton_OnKeyDown00);
   tolua_function(tolua_S,"OnKeyUp",tolua_CompileToLua_ControlButton_OnKeyUp00);
   tolua_function(tolua_S,"OnMouseMove",tolua_CompileToLua_ControlButton_OnMouseMove00);
   tolua_function(tolua_S,"OnLButtonDown",tolua_CompileToLua_ControlButton_OnLButtonDown00);
   tolua_function(tolua_S,"OnLButtonUp",tolua_CompileToLua_ControlButton_OnLButtonUp00);
   tolua_function(tolua_S,"InitUIData",tolua_CompileToLua_ControlButton_InitUIData00);
   tolua_function(tolua_S,"SetButtonClickFun_2lua",tolua_CompileToLua_ControlButton_SetButtonClickFun_2lua00);
   tolua_function(tolua_S,"SetButtonMouseOnFun_2lua",tolua_CompileToLua_ControlButton_SetButtonMouseOnFun_2lua00);
   tolua_function(tolua_S,"SetPressPic",tolua_CompileToLua_ControlButton_SetPressPic00);
   tolua_function(tolua_S,"SetNormalPic",tolua_CompileToLua_ControlButton_SetNormalPic00);
   tolua_function(tolua_S,"IsDrag",tolua_CompileToLua_ControlButton_IsDrag00);
   tolua_function(tolua_S,"SetEnable",tolua_CompileToLua_ControlButton_SetEnable00);
   tolua_function(tolua_S,"IsEnable",tolua_CompileToLua_ControlButton_IsEnable00);
   tolua_function(tolua_S,"IsPress",tolua_CompileToLua_ControlButton_IsPress00);
   tolua_function(tolua_S,"SetMouseMove",tolua_CompileToLua_ControlButton_SetMouseMove00);
   tolua_function(tolua_S,"SetCaption",tolua_CompileToLua_ControlButton_SetCaption00);
   tolua_function(tolua_S,"GetCaption",tolua_CompileToLua_ControlButton_GetCaption00);
   tolua_function(tolua_S,"SetState",tolua_CompileToLua_ControlButton_SetState00);
   tolua_function(tolua_S,"GetState",tolua_CompileToLua_ControlButton_GetState00);
   tolua_function(tolua_S,"getMouseMovePic",tolua_CompileToLua_ControlButton_getMouseMovePic00);
   tolua_function(tolua_S,"getMousePressPic",tolua_CompileToLua_ControlButton_getMousePressPic00);
   tolua_function(tolua_S,"getDisabledPic",tolua_CompileToLua_ControlButton_getDisabledPic00);
   tolua_function(tolua_S,"setMouseMovePic",tolua_CompileToLua_ControlButton_setMouseMovePic00);
   tolua_function(tolua_S,"setMousePressPic",tolua_CompileToLua_ControlButton_setMousePressPic00);
   tolua_function(tolua_S,"setDisabledPic",tolua_CompileToLua_ControlButton_setDisabledPic00);
   tolua_function(tolua_S,"SetShowTip",tolua_CompileToLua_ControlButton_SetShowTip00);
   tolua_function(tolua_S,"setTip",tolua_CompileToLua_ControlButton_setTip00);
   tolua_function(tolua_S,"OnButton",tolua_CompileToLua_ControlButton_OnButton00);
   tolua_function(tolua_S,"new",tolua_CompileToLua_ControlButton_new00);
   tolua_function(tolua_S,"new_local",tolua_CompileToLua_ControlButton_new00_local);
   tolua_function(tolua_S,".call",tolua_CompileToLua_ControlButton_new00_local);
   tolua_function(tolua_S,"delete",tolua_CompileToLua_ControlButton_delete00);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"ControlObject","ControlObject","zizi",tolua_collect_ControlObject);
  #else
  tolua_cclass(tolua_S,"ControlObject","ControlObject","zizi",NULL);
  #endif
  tolua_beginmodule(tolua_S,"ControlObject");
   tolua_function(tolua_S,"GetAlias",tolua_CompileToLua_ControlObject_GetAlias00);
   tolua_function(tolua_S,"Render",tolua_CompileToLua_ControlObject_Render00);
   tolua_function(tolua_S,"Run",tolua_CompileToLua_ControlObject_Run00);
   tolua_function(tolua_S,"ReleaseUI",tolua_CompileToLua_ControlObject_ReleaseUI00);
   tolua_function(tolua_S,"InitUIData",tolua_CompileToLua_ControlObject_InitUIData00);
   tolua_function(tolua_S,"UseFocus",tolua_CompileToLua_ControlObject_UseFocus00);
   tolua_function(tolua_S,"IsNeedRender",tolua_CompileToLua_ControlObject_IsNeedRender00);
   tolua_function(tolua_S,"PtInObject",tolua_CompileToLua_ControlObject_PtInObject00);
   tolua_function(tolua_S,"PtInObject",tolua_CompileToLua_ControlObject_PtInObject01);
   tolua_function(tolua_S,"SetVisable",tolua_CompileToLua_ControlObject_SetVisable00);
   tolua_function(tolua_S,"StartFlash",tolua_CompileToLua_ControlObject_StartFlash00);
   tolua_function(tolua_S,"SetRealRect",tolua_CompileToLua_ControlObject_SetRealRect00);
   tolua_function(tolua_S,"MsgProc",tolua_CompileToLua_ControlObject_MsgProc00);
   tolua_function(tolua_S,"FindControl",tolua_CompileToLua_ControlObject_FindControl00);
   tolua_function(tolua_S,"FindFrame",tolua_CompileToLua_ControlObject_FindFrame00);
   tolua_function(tolua_S,"GetArrayMode",tolua_CompileToLua_ControlObject_GetArrayMode00);
   tolua_function(tolua_S,"IsChild",tolua_CompileToLua_ControlObject_IsChild00);
   tolua_function(tolua_S,"OnMouseMove",tolua_CompileToLua_ControlObject_OnMouseMove00);
   tolua_function(tolua_S,"OnMouseLeave",tolua_CompileToLua_ControlObject_OnMouseLeave00);
   tolua_function(tolua_S,"OnMouseWheel",tolua_CompileToLua_ControlObject_OnMouseWheel00);
   tolua_function(tolua_S,"OnLButtonDown",tolua_CompileToLua_ControlObject_OnLButtonDown00);
   tolua_function(tolua_S,"OnRButtonDown",tolua_CompileToLua_ControlObject_OnRButtonDown00);
   tolua_function(tolua_S,"OnLButtonUp",tolua_CompileToLua_ControlObject_OnLButtonUp00);
   tolua_function(tolua_S,"OnRButtonUp",tolua_CompileToLua_ControlObject_OnRButtonUp00);
   tolua_function(tolua_S,"OnLButtonDBClick",tolua_CompileToLua_ControlObject_OnLButtonDBClick00);
   tolua_function(tolua_S,"OnRButtonDBClick",tolua_CompileToLua_ControlObject_OnRButtonDBClick00);
   tolua_function(tolua_S,"OnKeyDown",tolua_CompileToLua_ControlObject_OnKeyDown00);
   tolua_function(tolua_S,"OnKeyUp",tolua_CompileToLua_ControlObject_OnKeyUp00);
   tolua_function(tolua_S,"OnChar",tolua_CompileToLua_ControlObject_OnChar00);
   tolua_function(tolua_S,"IsLButtonDrag",tolua_CompileToLua_ControlObject_IsLButtonDrag00);
   tolua_function(tolua_S,"GetRealRect",tolua_CompileToLua_ControlObject_GetRealRect00);
   tolua_function(tolua_S,"GetControlID",tolua_CompileToLua_ControlObject_GetControlID00);
   tolua_function(tolua_S,"GetControlType",tolua_CompileToLua_ControlObject_GetControlType00);
   tolua_function(tolua_S,"GetFontSize",tolua_CompileToLua_ControlObject_GetFontSize00);
   tolua_function(tolua_S,"GetFontIndex",tolua_CompileToLua_ControlObject_GetFontIndex00);
   tolua_function(tolua_S,"SetFont",tolua_CompileToLua_ControlObject_SetFont00);
   tolua_function(tolua_S,"GetFontColor",tolua_CompileToLua_ControlObject_GetFontColor00);
   tolua_function(tolua_S,"GetWidth",tolua_CompileToLua_ControlObject_GetWidth00);
   tolua_function(tolua_S,"GetHeight",tolua_CompileToLua_ControlObject_GetHeight00);
   tolua_function(tolua_S,"SetPic",tolua_CompileToLua_ControlObject_SetPic00);
   tolua_function(tolua_S,"SetPos",tolua_CompileToLua_ControlObject_SetPos00);
   tolua_function(tolua_S,"SetXPos",tolua_CompileToLua_ControlObject_SetXPos00);
   tolua_function(tolua_S,"SetYPos",tolua_CompileToLua_ControlObject_SetYPos00);
   tolua_function(tolua_S,"SetWidth",tolua_CompileToLua_ControlObject_SetWidth00);
   tolua_function(tolua_S,"SetHeight",tolua_CompileToLua_ControlObject_SetHeight00);
   tolua_function(tolua_S,"SetCovered",tolua_CompileToLua_ControlObject_SetCovered00);
   tolua_function(tolua_S,"IsVisable",tolua_CompileToLua_ControlObject_IsVisable00);
   tolua_function(tolua_S,"IsCovered",tolua_CompileToLua_ControlObject_IsCovered00);
   tolua_function(tolua_S,"IsBeCovered",tolua_CompileToLua_ControlObject_IsBeCovered00);
   tolua_function(tolua_S,"SetActivate",tolua_CompileToLua_ControlObject_SetActivate00);
   tolua_function(tolua_S,"IsActivated",tolua_CompileToLua_ControlObject_IsActivated00);
   tolua_function(tolua_S,"MoveTo",tolua_CompileToLua_ControlObject_MoveTo00);
   tolua_function(tolua_S,"SetMsgHoldup",tolua_CompileToLua_ControlObject_SetMsgHoldup00);
   tolua_function(tolua_S,"IsMsgHoldup",tolua_CompileToLua_ControlObject_IsMsgHoldup00);
   tolua_function(tolua_S,"SetBackPicZValue",tolua_CompileToLua_ControlObject_SetBackPicZValue00);
   tolua_function(tolua_S,"SetBackColor",tolua_CompileToLua_ControlObject_SetBackColor00);
   tolua_function(tolua_S,"GetBackColor",tolua_CompileToLua_ControlObject_GetBackColor00);
   tolua_function(tolua_S,"SetBlendColor",tolua_CompileToLua_ControlObject_SetBlendColor00);
   tolua_function(tolua_S,"GetBlendColor",tolua_CompileToLua_ControlObject_GetBlendColor00);
   tolua_function(tolua_S,"PlaySound",tolua_CompileToLua_ControlObject_PlaySound00);
   tolua_function(tolua_S,"SetFadeInval",tolua_CompileToLua_ControlObject_SetFadeInval00);
   tolua_function(tolua_S,"IsFadeInval",tolua_CompileToLua_ControlObject_IsFadeInval00);
   tolua_function(tolua_S,"SetMaxMinFade",tolua_CompileToLua_ControlObject_SetMaxMinFade00);
   tolua_function(tolua_S,"SetPicName",tolua_CompileToLua_ControlObject_SetPicName00);
   tolua_function(tolua_S,"GetPic",tolua_CompileToLua_ControlObject_GetPic00);
   tolua_function(tolua_S,"GetData",tolua_CompileToLua_ControlObject_GetData00);
   tolua_function(tolua_S,"SetAllVisableDlg",tolua_CompileToLua_ControlObject_SetAllVisableDlg00);
   tolua_function(tolua_S,"GetAllVisableDlg",tolua_CompileToLua_ControlObject_GetAllVisableDlg00);
   tolua_function(tolua_S,"BitBlt",tolua_CompileToLua_ControlObject_BitBlt00);
   tolua_function(tolua_S,"GetFatherRect",tolua_CompileToLua_ControlObject_GetFatherRect00);
   tolua_function(tolua_S,"new",tolua_CompileToLua_ControlObject_new00);
   tolua_function(tolua_S,"new_local",tolua_CompileToLua_ControlObject_new00_local);
   tolua_function(tolua_S,".call",tolua_CompileToLua_ControlObject_new00_local);
   tolua_function(tolua_S,"delete",tolua_CompileToLua_ControlObject_delete00);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"ControlCheckBox","ControlCheckBox","ControlObject",tolua_collect_ControlCheckBox);
  #else
  tolua_cclass(tolua_S,"ControlCheckBox","ControlCheckBox","ControlObject",NULL);
  #endif
  tolua_beginmodule(tolua_S,"ControlCheckBox");
   tolua_function(tolua_S,"Render",tolua_CompileToLua_ControlCheckBox_Render00);
   tolua_function(tolua_S,"InitUIData",tolua_CompileToLua_ControlCheckBox_InitUIData00);
   tolua_function(tolua_S,"OnLButtonDown",tolua_CompileToLua_ControlCheckBox_OnLButtonDown00);
   tolua_function(tolua_S,"OnMouseMove",tolua_CompileToLua_ControlCheckBox_OnMouseMove00);
   tolua_function(tolua_S,"SetCheckFun_2lua",tolua_CompileToLua_ControlCheckBox_SetCheckFun_2lua00);
   tolua_function(tolua_S,"IsChecked",tolua_CompileToLua_ControlCheckBox_IsChecked00);
   tolua_function(tolua_S,"SetCheck",tolua_CompileToLua_ControlCheckBox_SetCheck00);
   tolua_function(tolua_S,"SetShowTip",tolua_CompileToLua_ControlCheckBox_SetShowTip00);
   tolua_function(tolua_S,"GetShowTip",tolua_CompileToLua_ControlCheckBox_GetShowTip00);
   tolua_function(tolua_S,"SetCaption",tolua_CompileToLua_ControlCheckBox_SetCaption00);
   tolua_function(tolua_S,"OnCheck",tolua_CompileToLua_ControlCheckBox_OnCheck00);
   tolua_function(tolua_S,"new",tolua_CompileToLua_ControlCheckBox_new00);
   tolua_function(tolua_S,"new_local",tolua_CompileToLua_ControlCheckBox_new00_local);
   tolua_function(tolua_S,".call",tolua_CompileToLua_ControlCheckBox_new00_local);
   tolua_function(tolua_S,"delete",tolua_CompileToLua_ControlCheckBox_delete00);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"ControlComboBox","ControlComboBox","ControlObject",tolua_collect_ControlComboBox);
  #else
  tolua_cclass(tolua_S,"ControlComboBox","ControlComboBox","ControlObject",NULL);
  #endif
  tolua_beginmodule(tolua_S,"ControlComboBox");
   tolua_function(tolua_S,"Render",tolua_CompileToLua_ControlComboBox_Render00);
   tolua_function(tolua_S,"InitUIData",tolua_CompileToLua_ControlComboBox_InitUIData00);
   tolua_function(tolua_S,"OnMouseMove",tolua_CompileToLua_ControlComboBox_OnMouseMove00);
   tolua_function(tolua_S,"OnMouseWheel",tolua_CompileToLua_ControlComboBox_OnMouseWheel00);
   tolua_function(tolua_S,"OnLButtonDown",tolua_CompileToLua_ControlComboBox_OnLButtonDown00);
   tolua_function(tolua_S,"OnLButtonUp",tolua_CompileToLua_ControlComboBox_OnLButtonUp00);
   tolua_function(tolua_S,"OnChar",tolua_CompileToLua_ControlComboBox_OnChar00);
   tolua_function(tolua_S,"GetListBox",tolua_CompileToLua_ControlComboBox_GetListBox00);
   tolua_function(tolua_S,"GetEditInput",tolua_CompileToLua_ControlComboBox_GetEditInput00);
   tolua_function(tolua_S,"SetChangeFun_2lua",tolua_CompileToLua_ControlComboBox_SetChangeFun_2lua00);
   tolua_function(tolua_S,"SetShowListFun_2lua",tolua_CompileToLua_ControlComboBox_SetShowListFun_2lua00);
   tolua_function(tolua_S,"OnChange",tolua_CompileToLua_ControlComboBox_OnChange00);
   tolua_function(tolua_S,"OnShowList",tolua_CompileToLua_ControlComboBox_OnShowList00);
   tolua_function(tolua_S,"new",tolua_CompileToLua_ControlComboBox_new00);
   tolua_function(tolua_S,"new_local",tolua_CompileToLua_ControlComboBox_new00_local);
   tolua_function(tolua_S,".call",tolua_CompileToLua_ControlComboBox_new00_local);
   tolua_function(tolua_S,"delete",tolua_CompileToLua_ControlComboBox_delete00);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"ControlEdit","ControlEdit","ControlObject",tolua_collect_ControlEdit);
  #else
  tolua_cclass(tolua_S,"ControlEdit","ControlEdit","ControlObject",NULL);
  #endif
  tolua_beginmodule(tolua_S,"ControlEdit");
   tolua_function(tolua_S,"InitUIData",tolua_CompileToLua_ControlEdit_InitUIData00);
   tolua_function(tolua_S,"Render",tolua_CompileToLua_ControlEdit_Render00);
   tolua_function(tolua_S,"Create",tolua_CompileToLua_ControlEdit_Create00);
   tolua_function(tolua_S,"OnMouseMove",tolua_CompileToLua_ControlEdit_OnMouseMove00);
   tolua_function(tolua_S,"OnLButtonDown",tolua_CompileToLua_ControlEdit_OnLButtonDown00);
   tolua_function(tolua_S,"OnLButtonUp",tolua_CompileToLua_ControlEdit_OnLButtonUp00);
   tolua_function(tolua_S,"OnLButtonDBClick",tolua_CompileToLua_ControlEdit_OnLButtonDBClick00);
   tolua_function(tolua_S,"OnChar",tolua_CompileToLua_ControlEdit_OnChar00);
   tolua_function(tolua_S,"OnKeyDown",tolua_CompileToLua_ControlEdit_OnKeyDown00);
   tolua_function(tolua_S,"SetText",tolua_CompileToLua_ControlEdit_SetText00);
   tolua_function(tolua_S,"SetText",tolua_CompileToLua_ControlEdit_SetText01);
   tolua_function(tolua_S,"SetText",tolua_CompileToLua_ControlEdit_SetText02);
   tolua_function(tolua_S,"SetTextW",tolua_CompileToLua_ControlEdit_SetTextW00);
   tolua_function(tolua_S,"GetText",tolua_CompileToLua_ControlEdit_GetText00);
   tolua_function(tolua_S,"GetTextW",tolua_CompileToLua_ControlEdit_GetTextW00);
   tolua_function(tolua_S,"addChar",tolua_CompileToLua_ControlEdit_addChar00);
   tolua_function(tolua_S,"DelByte",tolua_CompileToLua_ControlEdit_DelByte00);
   tolua_function(tolua_S,"addText",tolua_CompileToLua_ControlEdit_addText00);
   tolua_function(tolua_S,"SetEnterFun_2lua",tolua_CompileToLua_ControlEdit_SetEnterFun_2lua00);
   tolua_function(tolua_S,"SetTabFun_2lua",tolua_CompileToLua_ControlEdit_SetTabFun_2lua00);
   tolua_function(tolua_S,"SetLBtnDownFun_2lua",tolua_CompileToLua_ControlEdit_SetLBtnDownFun_2lua00);
   tolua_function(tolua_S,"SetLBtnUpFun_2lua",tolua_CompileToLua_ControlEdit_SetLBtnUpFun_2lua00);
   tolua_function(tolua_S,"SetDelByteFun_2lua",tolua_CompileToLua_ControlEdit_SetDelByteFun_2lua00);
   tolua_function(tolua_S,"IsReadOnly",tolua_CompileToLua_ControlEdit_IsReadOnly00);
   tolua_function(tolua_S,"SetIsNumber",tolua_CompileToLua_ControlEdit_SetIsNumber00);
   tolua_function(tolua_S,"SetMaxLength",tolua_CompileToLua_ControlEdit_SetMaxLength00);
   tolua_function(tolua_S,"SetReadOnly",tolua_CompileToLua_ControlEdit_SetReadOnly00);
   tolua_function(tolua_S,"SetIsPassword",tolua_CompileToLua_ControlEdit_SetIsPassword00);
   tolua_function(tolua_S,"IsPassword",tolua_CompileToLua_ControlEdit_IsPassword00);
   tolua_function(tolua_S,"setNoPitchOn",tolua_CompileToLua_ControlEdit_setNoPitchOn00);
   tolua_function(tolua_S,"SetMaxCnt",tolua_CompileToLua_ControlEdit_SetMaxCnt00);
   tolua_function(tolua_S,"setDefaultColor",tolua_CompileToLua_ControlEdit_setDefaultColor00);
   tolua_function(tolua_S,"SetCurIndex",tolua_CompileToLua_ControlEdit_SetCurIndex00);
   tolua_function(tolua_S,"CopyToClipboard",tolua_CompileToLua_ControlEdit_CopyToClipboard00);
   tolua_function(tolua_S,"GetTextFromClipboard",tolua_CompileToLua_ControlEdit_GetTextFromClipboard00);
   tolua_function(tolua_S,"DataChanged",tolua_CompileToLua_ControlEdit_DataChanged00);
   tolua_function(tolua_S,"CPtoX",tolua_CompileToLua_ControlEdit_CPtoX00);
   tolua_function(tolua_S,"XtoCP",tolua_CompileToLua_ControlEdit_XtoCP00);
   tolua_function(tolua_S,"OnEnter",tolua_CompileToLua_ControlEdit_OnEnter00);
   tolua_function(tolua_S,"OnTab",tolua_CompileToLua_ControlEdit_OnTab00);
   tolua_function(tolua_S,"new",tolua_CompileToLua_ControlEdit_new00);
   tolua_function(tolua_S,"new_local",tolua_CompileToLua_ControlEdit_new00_local);
   tolua_function(tolua_S,".call",tolua_CompileToLua_ControlEdit_new00_local);
   tolua_function(tolua_S,"delete",tolua_CompileToLua_ControlEdit_delete00);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"ControlFrame","ControlFrame","ControlObject",tolua_collect_ControlFrame);
  #else
  tolua_cclass(tolua_S,"ControlFrame","ControlFrame","ControlObject",NULL);
  #endif
  tolua_beginmodule(tolua_S,"ControlFrame");
   tolua_function(tolua_S,"Render",tolua_CompileToLua_ControlFrame_Render00);
   tolua_function(tolua_S,"Run",tolua_CompileToLua_ControlFrame_Run00);
   tolua_function(tolua_S,"UseFocus",tolua_CompileToLua_ControlFrame_UseFocus00);
   tolua_function(tolua_S,"PtInObject",tolua_CompileToLua_ControlFrame_PtInObject00);
   tolua_function(tolua_S,"PtInOnlyFrame",tolua_CompileToLua_ControlFrame_PtInOnlyFrame00);
   tolua_function(tolua_S,"StartFlash",tolua_CompileToLua_ControlFrame_StartFlash00);
   tolua_function(tolua_S,"GetArrayMode",tolua_CompileToLua_ControlFrame_GetArrayMode00);
   tolua_function(tolua_S,"IsChild",tolua_CompileToLua_ControlFrame_IsChild00);
   tolua_function(tolua_S,"ReleaseUI",tolua_CompileToLua_ControlFrame_ReleaseUI00);
   tolua_function(tolua_S,"FindControl",tolua_CompileToLua_ControlFrame_FindControl00);
   tolua_function(tolua_S,"FindFrame",tolua_CompileToLua_ControlFrame_FindFrame00);
   tolua_function(tolua_S,"OnMouseMove",tolua_CompileToLua_ControlFrame_OnMouseMove00);
   tolua_function(tolua_S,"OnMouseWheel",tolua_CompileToLua_ControlFrame_OnMouseWheel00);
   tolua_function(tolua_S,"OnLButtonDown",tolua_CompileToLua_ControlFrame_OnLButtonDown00);
   tolua_function(tolua_S,"OnLButtonUp",tolua_CompileToLua_ControlFrame_OnLButtonUp00);
   tolua_function(tolua_S,"OnLButtonDBClick",tolua_CompileToLua_ControlFrame_OnLButtonDBClick00);
   tolua_function(tolua_S,"OnRButtonDown",tolua_CompileToLua_ControlFrame_OnRButtonDown00);
   tolua_function(tolua_S,"OnRButtonUp",tolua_CompileToLua_ControlFrame_OnRButtonUp00);
   tolua_function(tolua_S,"OnRButtonDBClick",tolua_CompileToLua_ControlFrame_OnRButtonDBClick00);
   tolua_function(tolua_S,"OnMouseLeave",tolua_CompileToLua_ControlFrame_OnMouseLeave00);
   tolua_function(tolua_S,"OnKeyDown",tolua_CompileToLua_ControlFrame_OnKeyDown00);
   tolua_function(tolua_S,"OnKeyUp",tolua_CompileToLua_ControlFrame_OnKeyUp00);
   tolua_function(tolua_S,"OnChar",tolua_CompileToLua_ControlFrame_OnChar00);
   tolua_function(tolua_S,"IsLButtonDrag",tolua_CompileToLua_ControlFrame_IsLButtonDrag00);
   tolua_function(tolua_S,"LoadUIFormFile",tolua_CompileToLua_ControlFrame_LoadUIFormFile00);
   tolua_function(tolua_S,"SetArrayMode",tolua_CompileToLua_ControlFrame_SetArrayMode00);
   tolua_function(tolua_S,"SetRunFun_2lua",tolua_CompileToLua_ControlFrame_SetRunFun_2lua00);
   tolua_function(tolua_S,"SetRenderFun_2lua",tolua_CompileToLua_ControlFrame_SetRenderFun_2lua00);
   tolua_function(tolua_S,"SetOnClickFun_2lua",tolua_CompileToLua_ControlFrame_SetOnClickFun_2lua00);
   tolua_function(tolua_S,"SetOnRBtnDown_2lua",tolua_CompileToLua_ControlFrame_SetOnRBtnDown_2lua00);
   tolua_function(tolua_S,"SetMouseMoveOn_2lua",tolua_CompileToLua_ControlFrame_SetMouseMoveOn_2lua00);
   tolua_function(tolua_S,"SetMouseMoveLevel_2lua",tolua_CompileToLua_ControlFrame_SetMouseMoveLevel_2lua00);
   tolua_function(tolua_S,"SetOnTab_2lua",tolua_CompileToLua_ControlFrame_SetOnTab_2lua00);
   tolua_function(tolua_S,"SetFrameMove_2lua",tolua_CompileToLua_ControlFrame_SetFrameMove_2lua00);
   tolua_function(tolua_S,"SetAllVisable",tolua_CompileToLua_ControlFrame_SetAllVisable00);
   tolua_function(tolua_S,"SetAllFadeVal",tolua_CompileToLua_ControlFrame_SetAllFadeVal00);
   tolua_function(tolua_S,"SetAllBlendColor",tolua_CompileToLua_ControlFrame_SetAllBlendColor00);
   tolua_function(tolua_S,"AppendChild",tolua_CompileToLua_ControlFrame_AppendChild00);
   tolua_function(tolua_S,"new",tolua_CompileToLua_ControlFrame_new00);
   tolua_function(tolua_S,"new_local",tolua_CompileToLua_ControlFrame_new00_local);
   tolua_function(tolua_S,".call",tolua_CompileToLua_ControlFrame_new00_local);
   tolua_function(tolua_S,"delete",tolua_CompileToLua_ControlFrame_delete00);
  tolua_endmodule(tolua_S);
  tolua_constant(tolua_S,"eIcon_Disable",eIcon_Disable);
  tolua_constant(tolua_S,"eIcon_Enable",eIcon_Enable);
  tolua_constant(tolua_S,"eIcon_Shop",eIcon_Shop);
  tolua_constant(tolua_S,"eIcon_Max",eIcon_Max);
  tolua_constant(tolua_S,"eCharItem",eCharItem);
  tolua_constant(tolua_S,"eTaskItem",eTaskItem);
  tolua_constant(tolua_S,"eTipFlag_Normal",eTipFlag_Normal);
  tolua_constant(tolua_S,"eTipFlag_SkillNoNextLevel",eTipFlag_SkillNoNextLevel);
  tolua_constant(tolua_S,"eTipFlag_SkillWithNextLevel",eTipFlag_SkillWithNextLevel);
  tolua_constant(tolua_S,"eTipFlag_SkillTree",eTipFlag_SkillTree);
  tolua_constant(tolua_S,"eTipFlag_Status",eTipFlag_Status);
  tolua_constant(tolua_S,"eTipFlag_Count",eTipFlag_Count);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"S_IconInfoBase","S_IconInfoBase","",tolua_collect_S_IconInfoBase);
  #else
  tolua_cclass(tolua_S,"S_IconInfoBase","S_IconInfoBase","",NULL);
  #endif
  tolua_beginmodule(tolua_S,"S_IconInfoBase");
   tolua_function(tolua_S,"Id",tolua_CompileToLua_S_IconInfoBase_Id00);
   tolua_function(tolua_S,"Count",tolua_CompileToLua_S_IconInfoBase_Count00);
   tolua_function(tolua_S,"IsLocked",tolua_CompileToLua_S_IconInfoBase_IsLocked00);
   tolua_function(tolua_S,"MaxCount",tolua_CompileToLua_S_IconInfoBase_MaxCount00);
   tolua_function(tolua_S,"SpareTime",tolua_CompileToLua_S_IconInfoBase_SpareTime00);
   tolua_function(tolua_S,"GetSpareTime",tolua_CompileToLua_S_IconInfoBase_GetSpareTime00);
   tolua_function(tolua_S,"IsNextLvl",tolua_CompileToLua_S_IconInfoBase_IsNextLvl00);
   tolua_function(tolua_S,"IsNull",tolua_CompileToLua_S_IconInfoBase_IsNull00);
   tolua_function(tolua_S,"SetData",tolua_CompileToLua_S_IconInfoBase_SetData00);
   tolua_function(tolua_S,"SetData",tolua_CompileToLua_S_IconInfoBase_SetData01);
   tolua_function(tolua_S,"PlaySound",tolua_CompileToLua_S_IconInfoBase_PlaySound00);
   tolua_function(tolua_S,"IconFileName",tolua_CompileToLua_S_IconInfoBase_IconFileName00);
   tolua_function(tolua_S,"DisableIconFileName",tolua_CompileToLua_S_IconInfoBase_DisableIconFileName00);
   tolua_function(tolua_S,"ShopIconFileName",tolua_CompileToLua_S_IconInfoBase_ShopIconFileName00);
   tolua_function(tolua_S,"Cost",tolua_CompileToLua_S_IconInfoBase_Cost00);
   tolua_function(tolua_S,"Clear",tolua_CompileToLua_S_IconInfoBase_Clear00);
   tolua_function(tolua_S,"DisplayIcon",tolua_CompileToLua_S_IconInfoBase_DisplayIcon00);
   tolua_function(tolua_S,"DisplayInfo",tolua_CompileToLua_S_IconInfoBase_DisplayInfo00);
   tolua_function(tolua_S,"DisplayInfo",tolua_CompileToLua_S_IconInfoBase_DisplayInfo01);
   tolua_function(tolua_S,"SetInfo",tolua_CompileToLua_S_IconInfoBase_SetInfo00);
   tolua_function(tolua_S,"SetOtherInfo",tolua_CompileToLua_S_IconInfoBase_SetOtherInfo00);
   tolua_function(tolua_S,"SetFontSize",tolua_CompileToLua_S_IconInfoBase_SetFontSize00);
   tolua_function(tolua_S,"delete",tolua_CompileToLua_S_IconInfoBase_delete00);
   #ifdef __cplusplus
   tolua_cclass(tolua_S,"stIconInfo","S_IconInfoBase::stIconInfo","",tolua_collect_S_IconInfoBase__stIconInfo);
   #else
   tolua_cclass(tolua_S,"stIconInfo","S_IconInfoBase::stIconInfo","",NULL);
   #endif
   tolua_beginmodule(tolua_S,"stIconInfo");
    tolua_function(tolua_S,"new",tolua_CompileToLua_S_IconInfoBase_stIconInfo_new00);
    tolua_function(tolua_S,"new_local",tolua_CompileToLua_S_IconInfoBase_stIconInfo_new00_local);
    tolua_function(tolua_S,".call",tolua_CompileToLua_S_IconInfoBase_stIconInfo_new00_local);
    tolua_variable(tolua_S,"m_col",tolua_get_S_IconInfoBase__stIconInfo_m_col,tolua_set_S_IconInfoBase__stIconInfo_m_col);
    tolua_variable(tolua_S,"m_strInfo",tolua_get_S_IconInfoBase__stIconInfo_m_strInfo,tolua_set_S_IconInfoBase__stIconInfo_m_strInfo);
   tolua_endmodule(tolua_S);
   #ifdef __cplusplus
   tolua_cclass(tolua_S,"sShowGem","S_IconInfoBase::sShowGem","",tolua_collect_S_IconInfoBase__sShowGem);
   #else
   tolua_cclass(tolua_S,"sShowGem","S_IconInfoBase::sShowGem","",NULL);
   #endif
   tolua_beginmodule(tolua_S,"sShowGem");
    tolua_constant(tolua_S,"eElement_Ice",S_IconInfoBase::sShowGem::eElement_Ice);
    tolua_constant(tolua_S,"eElement_Fire",S_IconInfoBase::sShowGem::eElement_Fire);
    tolua_constant(tolua_S,"eElement_Thunder",S_IconInfoBase::sShowGem::eElement_Thunder);
    tolua_constant(tolua_S,"eElement_Poison",S_IconInfoBase::sShowGem::eElement_Poison);
    tolua_constant(tolua_S,"eElement_Max",S_IconInfoBase::sShowGem::eElement_Max);
    tolua_function(tolua_S,"new",tolua_CompileToLua_S_IconInfoBase_sShowGem_new00);
    tolua_function(tolua_S,"new_local",tolua_CompileToLua_S_IconInfoBase_sShowGem_new00_local);
    tolua_function(tolua_S,".call",tolua_CompileToLua_S_IconInfoBase_sShowGem_new00_local);
    tolua_variable(tolua_S,"nGemPhysicAtt",tolua_get_S_IconInfoBase__sShowGem_nGemPhysicAtt,tolua_set_S_IconInfoBase__sShowGem_nGemPhysicAtt);
    tolua_variable(tolua_S,"nGemMagicAtt",tolua_get_S_IconInfoBase__sShowGem_nGemMagicAtt,tolua_set_S_IconInfoBase__sShowGem_nGemMagicAtt);
    tolua_variable(tolua_S,"nGemPhysicDef",tolua_get_S_IconInfoBase__sShowGem_nGemPhysicDef,tolua_set_S_IconInfoBase__sShowGem_nGemPhysicDef);
    tolua_variable(tolua_S,"nGemAttSpeed",tolua_get_S_IconInfoBase__sShowGem_nGemAttSpeed,tolua_set_S_IconInfoBase__sShowGem_nGemAttSpeed);
    tolua_variable(tolua_S,"nGemExact",tolua_get_S_IconInfoBase__sShowGem_nGemExact,tolua_set_S_IconInfoBase__sShowGem_nGemExact);
    tolua_variable(tolua_S,"nGemDodge",tolua_get_S_IconInfoBase__sShowGem_nGemDodge,tolua_set_S_IconInfoBase__sShowGem_nGemDodge);
    tolua_array(tolua_S,"nGemAtt",tolua_get_CompileToLua_S_IconInfoBase_sShowGem_nGemAtt,tolua_set_CompileToLua_S_IconInfoBase_sShowGem_nGemAtt);
    tolua_array(tolua_S,"nGemDef",tolua_get_CompileToLua_S_IconInfoBase_sShowGem_nGemDef,tolua_set_CompileToLua_S_IconInfoBase_sShowGem_nGemDef);
    tolua_variable(tolua_S,"nGemAddHp",tolua_get_S_IconInfoBase__sShowGem_nGemAddHp,tolua_set_S_IconInfoBase__sShowGem_nGemAddHp);
    tolua_variable(tolua_S,"nGemAddMp",tolua_get_S_IconInfoBase__sShowGem_nGemAddMp,tolua_set_S_IconInfoBase__sShowGem_nGemAddMp);
    tolua_variable(tolua_S,"nGemAddHpRestor",tolua_get_S_IconInfoBase__sShowGem_nGemAddHpRestor,tolua_set_S_IconInfoBase__sShowGem_nGemAddHpRestor);
    tolua_variable(tolua_S,"nGemAddMpRestor",tolua_get_S_IconInfoBase__sShowGem_nGemAddMpRestor,tolua_set_S_IconInfoBase__sShowGem_nGemAddMpRestor);
   tolua_endmodule(tolua_S);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"CIconInfoMouseTip","CIconInfoMouseTip","",tolua_collect_CIconInfoMouseTip);
  #else
  tolua_cclass(tolua_S,"CIconInfoMouseTip","CIconInfoMouseTip","",NULL);
  #endif
  tolua_beginmodule(tolua_S,"CIconInfoMouseTip");
   tolua_function(tolua_S,"Render",tolua_CompileToLua_CIconInfoMouseTip_Render00);
   tolua_function(tolua_S,"Clear",tolua_CompileToLua_CIconInfoMouseTip_Clear00);
   tolua_function(tolua_S,"SetDisplayInfo",tolua_CompileToLua_CIconInfoMouseTip_SetDisplayInfo00);
   tolua_variable(tolua_S,"m_bShopOpen",tolua_get_CIconInfoMouseTip_m_bShopOpen,tolua_set_CIconInfoMouseTip_m_bShopOpen);
   tolua_function(tolua_S,"new",tolua_CompileToLua_CIconInfoMouseTip_new00);
   tolua_function(tolua_S,"new_local",tolua_CompileToLua_CIconInfoMouseTip_new00_local);
   tolua_function(tolua_S,".call",tolua_CompileToLua_CIconInfoMouseTip_new00_local);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"S_TextTipInfo","S_TextTipInfo","S_IconInfoBase",tolua_collect_S_TextTipInfo);
  #else
  tolua_cclass(tolua_S,"S_TextTipInfo","S_TextTipInfo","S_IconInfoBase",NULL);
  #endif
  tolua_beginmodule(tolua_S,"S_TextTipInfo");
   tolua_function(tolua_S,"Id",tolua_CompileToLua_S_TextTipInfo_Id00);
   tolua_function(tolua_S,"Count",tolua_CompileToLua_S_TextTipInfo_Count00);
   tolua_function(tolua_S,"IsLocked",tolua_CompileToLua_S_TextTipInfo_IsLocked00);
   tolua_function(tolua_S,"MaxCount",tolua_CompileToLua_S_TextTipInfo_MaxCount00);
   tolua_function(tolua_S,"SpareTime",tolua_CompileToLua_S_TextTipInfo_SpareTime00);
   tolua_function(tolua_S,"GetSpareTime",tolua_CompileToLua_S_TextTipInfo_GetSpareTime00);
   tolua_function(tolua_S,"IsNextLvl",tolua_CompileToLua_S_TextTipInfo_IsNextLvl00);
   tolua_function(tolua_S,"IsNull",tolua_CompileToLua_S_TextTipInfo_IsNull00);
   tolua_function(tolua_S,"SetData",tolua_CompileToLua_S_TextTipInfo_SetData00);
   tolua_function(tolua_S,"SetData",tolua_CompileToLua_S_TextTipInfo_SetData01);
   tolua_function(tolua_S,"PlaySound",tolua_CompileToLua_S_TextTipInfo_PlaySound00);
   tolua_function(tolua_S,"IconFileName",tolua_CompileToLua_S_TextTipInfo_IconFileName00);
   tolua_function(tolua_S,"DisableIconFileName",tolua_CompileToLua_S_TextTipInfo_DisableIconFileName00);
   tolua_function(tolua_S,"ShopIconFileName",tolua_CompileToLua_S_TextTipInfo_ShopIconFileName00);
   tolua_function(tolua_S,"Cost",tolua_CompileToLua_S_TextTipInfo_Cost00);
   tolua_function(tolua_S,"new",tolua_CompileToLua_S_TextTipInfo_new00);
   tolua_function(tolua_S,"new_local",tolua_CompileToLua_S_TextTipInfo_new00_local);
   tolua_function(tolua_S,".call",tolua_CompileToLua_S_TextTipInfo_new00_local);
   tolua_function(tolua_S,"Clear",tolua_CompileToLua_S_TextTipInfo_Clear00);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"S_IconInfoHero","S_IconInfoHero","S_IconInfoBase",tolua_collect_S_IconInfoHero);
  #else
  tolua_cclass(tolua_S,"S_IconInfoHero","S_IconInfoHero","S_IconInfoBase",NULL);
  #endif
  tolua_beginmodule(tolua_S,"S_IconInfoHero");
   tolua_function(tolua_S,"Id",tolua_CompileToLua_S_IconInfoHero_Id00);
   tolua_function(tolua_S,"Count",tolua_CompileToLua_S_IconInfoHero_Count00);
   tolua_function(tolua_S,"IsLocked",tolua_CompileToLua_S_IconInfoHero_IsLocked00);
   tolua_function(tolua_S,"MaxCount",tolua_CompileToLua_S_IconInfoHero_MaxCount00);
   tolua_function(tolua_S,"SpareTime",tolua_CompileToLua_S_IconInfoHero_SpareTime00);
   tolua_function(tolua_S,"GetSpareTime",tolua_CompileToLua_S_IconInfoHero_GetSpareTime00);
   tolua_function(tolua_S,"IsNextLvl",tolua_CompileToLua_S_IconInfoHero_IsNextLvl00);
   tolua_function(tolua_S,"IsNull",tolua_CompileToLua_S_IconInfoHero_IsNull00);
   tolua_function(tolua_S,"SetData",tolua_CompileToLua_S_IconInfoHero_SetData00);
   tolua_function(tolua_S,"SetData",tolua_CompileToLua_S_IconInfoHero_SetData01);
   tolua_function(tolua_S,"PlaySound",tolua_CompileToLua_S_IconInfoHero_PlaySound00);
   tolua_function(tolua_S,"SetSpareTime",tolua_CompileToLua_S_IconInfoHero_SetSpareTime00);
   tolua_function(tolua_S,"GetQualityColor",tolua_CompileToLua_S_IconInfoHero_GetQualityColor00);
   tolua_function(tolua_S,"IconFileName",tolua_CompileToLua_S_IconInfoHero_IconFileName00);
   tolua_function(tolua_S,"DisableIconFileName",tolua_CompileToLua_S_IconInfoHero_DisableIconFileName00);
   tolua_function(tolua_S,"ShopIconFileName",tolua_CompileToLua_S_IconInfoHero_ShopIconFileName00);
   tolua_function(tolua_S,"Cost",tolua_CompileToLua_S_IconInfoHero_Cost00);
   tolua_function(tolua_S,"ShowBaseInfo",tolua_CompileToLua_S_IconInfoHero_ShowBaseInfo00);
   tolua_function(tolua_S,"ShowCanWeapon",tolua_CompileToLua_S_IconInfoHero_ShowCanWeapon00);
   tolua_function(tolua_S,"ShowWeapon",tolua_CompileToLua_S_IconInfoHero_ShowWeapon00);
   tolua_function(tolua_S,"ShowArmour",tolua_CompileToLua_S_IconInfoHero_ShowArmour00);
   tolua_function(tolua_S,"ShowSkill",tolua_CompileToLua_S_IconInfoHero_ShowSkill00);
   tolua_function(tolua_S,"ShowRestore",tolua_CompileToLua_S_IconInfoHero_ShowRestore00);
   tolua_function(tolua_S,"ShowGem",tolua_CompileToLua_S_IconInfoHero_ShowGem00);
   tolua_function(tolua_S,"SetGemCount",tolua_CompileToLua_S_IconInfoHero_SetGemCount00);
   tolua_function(tolua_S,"Clear",tolua_CompileToLua_S_IconInfoHero_Clear00);
   tolua_function(tolua_S,"new",tolua_CompileToLua_S_IconInfoHero_new00);
   tolua_function(tolua_S,"new_local",tolua_CompileToLua_S_IconInfoHero_new00_local);
   tolua_function(tolua_S,".call",tolua_CompileToLua_S_IconInfoHero_new00_local);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"ControlIconDrag","ControlIconDrag","ControlObject",tolua_collect_ControlIconDrag);
  #else
  tolua_cclass(tolua_S,"ControlIconDrag","ControlIconDrag","ControlObject",NULL);
  #endif
  tolua_beginmodule(tolua_S,"ControlIconDrag");
   #ifdef __cplusplus
   tolua_cclass(tolua_S,"S_ListImg","ControlIconDrag::S_ListImg","",tolua_collect_ControlIconDrag__S_ListImg);
   #else
   tolua_cclass(tolua_S,"S_ListImg","ControlIconDrag::S_ListImg","",NULL);
   #endif
   tolua_beginmodule(tolua_S,"S_ListImg");
    tolua_function(tolua_S,"new",tolua_CompileToLua_ControlIconDrag_S_ListImg_new00);
    tolua_function(tolua_S,"new_local",tolua_CompileToLua_ControlIconDrag_S_ListImg_new00_local);
    tolua_function(tolua_S,".call",tolua_CompileToLua_ControlIconDrag_S_ListImg_new00_local);
    tolua_function(tolua_S,"Clear",tolua_CompileToLua_ControlIconDrag_S_ListImg_Clear00);
    tolua_function(tolua_S,"IsNull",tolua_CompileToLua_ControlIconDrag_S_ListImg_IsNull00);
    tolua_function(tolua_S,"ChangeCount",tolua_CompileToLua_ControlIconDrag_S_ListImg_ChangeCount00);
    tolua_function(tolua_S,"SetData",tolua_CompileToLua_ControlIconDrag_S_ListImg_SetData00);
    tolua_function(tolua_S,"SetData",tolua_CompileToLua_ControlIconDrag_S_ListImg_SetData01);
    tolua_function(tolua_S,"SetFlags",tolua_CompileToLua_ControlIconDrag_S_ListImg_SetFlags00);
    tolua_function(tolua_S,"SetTime",tolua_CompileToLua_ControlIconDrag_S_ListImg_SetTime00);
    tolua_function(tolua_S,"SetOtherInfo",tolua_CompileToLua_ControlIconDrag_S_ListImg_SetOtherInfo00);
    tolua_function(tolua_S,"SetCol",tolua_CompileToLua_ControlIconDrag_S_ListImg_SetCol00);
    tolua_function(tolua_S,"SetEnable",tolua_CompileToLua_ControlIconDrag_S_ListImg_SetEnable00);
    tolua_variable(tolua_S,"m_eEnable",tolua_get_ControlIconDrag__S_ListImg_m_eEnable,tolua_set_ControlIconDrag__S_ListImg_m_eEnable);
    tolua_variable(tolua_S,"m_stIcon",tolua_get_ControlIconDrag__S_ListImg_m_stIcon,tolua_set_ControlIconDrag__S_ListImg_m_stIcon);
    tolua_variable(tolua_S,"m_dwFlags",tolua_get_ControlIconDrag__S_ListImg_m_dwFlags,tolua_set_ControlIconDrag__S_ListImg_m_dwFlags);
    tolua_variable(tolua_S,"m_dwColor",tolua_get_ControlIconDrag__S_ListImg_m_dwColor,tolua_set_ControlIconDrag__S_ListImg_m_dwColor);
    tolua_variable(tolua_S,"m_dwStartTime",tolua_get_ControlIconDrag__S_ListImg_m_dwStartTime,tolua_set_ControlIconDrag__S_ListImg_m_dwStartTime);
    tolua_variable(tolua_S,"m_dwPeriod",tolua_get_ControlIconDrag__S_ListImg_m_dwPeriod,tolua_set_ControlIconDrag__S_ListImg_m_dwPeriod);
    tolua_variable(tolua_S,"m_col",tolua_get_ControlIconDrag__S_ListImg_m_col,tolua_set_ControlIconDrag__S_ListImg_m_col);
    tolua_variable(tolua_S,"m_bUseCol",tolua_get_ControlIconDrag__S_ListImg_m_bUseCol,tolua_set_ControlIconDrag__S_ListImg_m_bUseCol);
   tolua_endmodule(tolua_S);
   tolua_function(tolua_S,"Run",tolua_CompileToLua_ControlIconDrag_Run00);
   tolua_function(tolua_S,"OnMouseMove",tolua_CompileToLua_ControlIconDrag_OnMouseMove00);
   tolua_function(tolua_S,"OnMouseWheel",tolua_CompileToLua_ControlIconDrag_OnMouseWheel00);
   tolua_function(tolua_S,"OnLButtonDown",tolua_CompileToLua_ControlIconDrag_OnLButtonDown00);
   tolua_function(tolua_S,"OnLButtonUp",tolua_CompileToLua_ControlIconDrag_OnLButtonUp00);
   tolua_function(tolua_S,"OnRButtonUp",tolua_CompileToLua_ControlIconDrag_OnRButtonUp00);
   tolua_function(tolua_S,"OnLButtonDBClick",tolua_CompileToLua_ControlIconDrag_OnLButtonDBClick00);
   tolua_function(tolua_S,"GetIconSize",tolua_CompileToLua_ControlIconDrag_GetIconSize00);
   tolua_function(tolua_S,"GetTilePt",tolua_CompileToLua_ControlIconDrag_GetTilePt00);
   tolua_function(tolua_S,"CanbePick",tolua_CompileToLua_ControlIconDrag_CanbePick00);
   tolua_function(tolua_S,"SetCanbePick",tolua_CompileToLua_ControlIconDrag_SetCanbePick00);
   tolua_function(tolua_S,"OnDragOn",tolua_CompileToLua_ControlIconDrag_OnDragOn00);
   tolua_function(tolua_S,"SetItem",tolua_CompileToLua_ControlIconDrag_SetItem00);
   tolua_function(tolua_S,"RemoveItemById",tolua_CompileToLua_ControlIconDrag_RemoveItemById00);
   tolua_function(tolua_S,"RemoveItemByIndex",tolua_CompileToLua_ControlIconDrag_RemoveItemByIndex00);
   tolua_function(tolua_S,"Clear",tolua_CompileToLua_ControlIconDrag_Clear00);
   tolua_function(tolua_S,"GetItem",tolua_CompileToLua_ControlIconDrag_GetItem00);
   tolua_function(tolua_S,"GetCurSelItem",tolua_CompileToLua_ControlIconDrag_GetCurSelItem00);
   tolua_function(tolua_S,"GetItemByIndex",tolua_CompileToLua_ControlIconDrag_GetItemByIndex00);
   tolua_function(tolua_S,"GetLastIndex",tolua_CompileToLua_ControlIconDrag_GetLastIndex00);
   tolua_function(tolua_S,"GetItemById",tolua_CompileToLua_ControlIconDrag_GetItemById00);
   tolua_function(tolua_S,"GetItemIndex",tolua_CompileToLua_ControlIconDrag_GetItemIndex00);
   tolua_function(tolua_S,"GetNullItem",tolua_CompileToLua_ControlIconDrag_GetNullItem00);
   tolua_function(tolua_S,"SetIsShop",tolua_CompileToLua_ControlIconDrag_SetIsShop00);
   tolua_function(tolua_S,"SetShowAllInfo",tolua_CompileToLua_ControlIconDrag_SetShowAllInfo00);
   tolua_function(tolua_S,"GetItemCnt",tolua_CompileToLua_ControlIconDrag_GetItemCnt00);
   tolua_function(tolua_S,"SetSpareTime",tolua_CompileToLua_ControlIconDrag_SetSpareTime00);
   tolua_function(tolua_S,"GetStartIndex",tolua_CompileToLua_ControlIconDrag_GetStartIndex00);
   tolua_function(tolua_S,"SetScrollVisable",tolua_CompileToLua_ControlIconDrag_SetScrollVisable00);
   tolua_function(tolua_S,"SetStartIndex",tolua_CompileToLua_ControlIconDrag_SetStartIndex00);
   tolua_function(tolua_S,"SetScrollBarEnable",tolua_CompileToLua_ControlIconDrag_SetScrollBarEnable00);
   tolua_function(tolua_S,"IsDisableCanbePick",tolua_CompileToLua_ControlIconDrag_IsDisableCanbePick00);
   tolua_function(tolua_S,"SetDisableCanbePick",tolua_CompileToLua_ControlIconDrag_SetDisableCanbePick00);
   tolua_function(tolua_S,"SetHeightShowMaxCnt",tolua_CompileToLua_ControlIconDrag_SetHeightShowMaxCnt00);
   tolua_function(tolua_S,"SetEnableRowCnt",tolua_CompileToLua_ControlIconDrag_SetEnableRowCnt00);
   tolua_function(tolua_S,"SetNotMsgClick",tolua_CompileToLua_ControlIconDrag_SetNotMsgClick00);
   tolua_function(tolua_S,"OnLDBClick",tolua_CompileToLua_ControlIconDrag_OnLDBClick00);
   tolua_function(tolua_S,"Refeash",tolua_CompileToLua_ControlIconDrag_Refeash00);
   tolua_function(tolua_S,"InitItemDate",tolua_CompileToLua_ControlIconDrag_InitItemDate00);
   tolua_function(tolua_S,"delete",tolua_CompileToLua_ControlIconDrag_delete00);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"ControlIconDragManager","ControlIconDragManager","",tolua_collect_ControlIconDragManager);
  #else
  tolua_cclass(tolua_S,"ControlIconDragManager","ControlIconDragManager","",NULL);
  #endif
  tolua_beginmodule(tolua_S,"ControlIconDragManager");
   tolua_function(tolua_S,"Render",tolua_CompileToLua_ControlIconDragManager_Render00);
   tolua_function(tolua_S,"Run",tolua_CompileToLua_ControlIconDragManager_Run00);
   tolua_function(tolua_S,"OnMouseMove",tolua_CompileToLua_ControlIconDragManager_OnMouseMove00);
   tolua_function(tolua_S,"OnLButtonDown",tolua_CompileToLua_ControlIconDragManager_OnLButtonDown00);
   tolua_function(tolua_S,"OnRButtonDown",tolua_CompileToLua_ControlIconDragManager_OnRButtonDown00);
   tolua_function(tolua_S,"OnLButtonUp",tolua_CompileToLua_ControlIconDragManager_OnLButtonUp00);
   tolua_function(tolua_S,"OnRButtonUp",tolua_CompileToLua_ControlIconDragManager_OnRButtonUp00);
   tolua_function(tolua_S,"OnLButtonDBClick",tolua_CompileToLua_ControlIconDragManager_OnLButtonDBClick00);
   tolua_function(tolua_S,"OnRButtonDBClick",tolua_CompileToLua_ControlIconDragManager_OnRButtonDBClick00);
   tolua_function(tolua_S,"SetDrag",tolua_CompileToLua_ControlIconDragManager_SetDrag00);
   tolua_function(tolua_S,"SetDstListImg",tolua_CompileToLua_ControlIconDragManager_SetDstListImg00);
   tolua_function(tolua_S,"ClearDrag",tolua_CompileToLua_ControlIconDragManager_ClearDrag00);
   tolua_function(tolua_S,"GetCurItem",tolua_CompileToLua_ControlIconDragManager_GetCurItem00);
   tolua_variable(tolua_S,"m_pLastSelItem",tolua_get_ControlIconDragManager_m_pLastSelItem_ptr,tolua_set_ControlIconDragManager_m_pLastSelItem_ptr);
   tolua_function(tolua_S,"new",tolua_CompileToLua_ControlIconDragManager_new00);
   tolua_function(tolua_S,"new_local",tolua_CompileToLua_ControlIconDragManager_new00_local);
   tolua_function(tolua_S,".call",tolua_CompileToLua_ControlIconDragManager_new00_local);
   tolua_function(tolua_S,"delete",tolua_CompileToLua_ControlIconDragManager_delete00);
  tolua_endmodule(tolua_S);
  tolua_variable(tolua_S,"theIconDragManager",tolua_get_theIconDragManager,tolua_set_theIconDragManager);
  tolua_constant(tolua_S,"HYBER_NONE",HYBER_NONE);
  tolua_constant(tolua_S,"HYBER_PLAYER",HYBER_PLAYER);
  tolua_constant(tolua_S,"HYBER_ITEM",HYBER_ITEM);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"ControlList","ControlList","ControlObject",tolua_collect_ControlList);
  #else
  tolua_cclass(tolua_S,"ControlList","ControlList","ControlObject",NULL);
  #endif
  tolua_beginmodule(tolua_S,"ControlList");
   #ifdef __cplusplus
   tolua_cclass(tolua_S,"S_List","ControlList::S_List","",tolua_collect_ControlList__S_List);
   #else
   tolua_cclass(tolua_S,"S_List","ControlList::S_List","",NULL);
   #endif
   tolua_beginmodule(tolua_S,"S_List");
    tolua_function(tolua_S,"new",tolua_CompileToLua_ControlList_S_List_new00);
    tolua_function(tolua_S,"new_local",tolua_CompileToLua_ControlList_S_List_new00_local);
    tolua_function(tolua_S,".call",tolua_CompileToLua_ControlList_S_List_new00_local);
    tolua_function(tolua_S,"clear",tolua_CompileToLua_ControlList_S_List_clear00);
    tolua_function(tolua_S,"SetData",tolua_CompileToLua_ControlList_S_List_SetData00);
    tolua_function(tolua_S,"setColor",tolua_CompileToLua_ControlList_S_List_setColor00);
    tolua_function(tolua_S,"setTextCustomKey",tolua_CompileToLua_ControlList_S_List_setTextCustomKey00);
    tolua_function(tolua_S,"setTip",tolua_CompileToLua_ControlList_S_List_setTip00);
    tolua_function(tolua_S,"setTip",tolua_CompileToLua_ControlList_S_List_setTip01);
    tolua_function(tolua_S,"setIsOnline",tolua_CompileToLua_ControlList_S_List_setIsOnline00);
    tolua_variable(tolua_S,"m_szText",tolua_get_ControlList__S_List_m_szText,tolua_set_ControlList__S_List_m_szText);
    tolua_variable(tolua_S,"m_szNote",tolua_get_ControlList__S_List_m_szNote,tolua_set_ControlList__S_List_m_szNote);
    tolua_variable(tolua_S,"m_nID",tolua_get_ControlList__S_List_m_nID,tolua_set_ControlList__S_List_m_nID);
    tolua_variable(tolua_S,"m_pData",tolua_get_ControlList__S_List_m_pData,tolua_set_ControlList__S_List_m_pData);
    tolua_array(tolua_S,"_hyberItemInfo",tolua_get_CompileToLua_ControlList_S_List__hyberItemInfo,tolua_set_CompileToLua_ControlList_S_List__hyberItemInfo);
    tolua_variable(tolua_S,"m_colTextCol",tolua_get_ControlList__S_List_m_colTextCol,tolua_set_ControlList__S_List_m_colTextCol);
    tolua_variable(tolua_S,"_bOnline",tolua_get_ControlList__S_List__bOnline,tolua_set_ControlList__S_List__bOnline);
    tolua_variable(tolua_S,"m_pTipInfo",tolua_get_ControlList__S_List_m_pTipInfo_ptr,tolua_set_ControlList__S_List_m_pTipInfo_ptr);
    tolua_variable(tolua_S,"UseSelColor",tolua_get_ControlList__S_List_UseSelColor,tolua_set_ControlList__S_List_UseSelColor);
   tolua_endmodule(tolua_S);
   tolua_function(tolua_S,"Render",tolua_CompileToLua_ControlList_Render00);
   tolua_function(tolua_S,"PtInObject",tolua_CompileToLua_ControlList_PtInObject00);
   tolua_function(tolua_S,"InitUIData",tolua_CompileToLua_ControlList_InitUIData00);
   tolua_function(tolua_S,"OnMouseMove",tolua_CompileToLua_ControlList_OnMouseMove00);
   tolua_function(tolua_S,"OnMouseWheel",tolua_CompileToLua_ControlList_OnMouseWheel00);
   tolua_function(tolua_S,"OnLButtonDown",tolua_CompileToLua_ControlList_OnLButtonDown00);
   tolua_function(tolua_S,"OnLButtonUp",tolua_CompileToLua_ControlList_OnLButtonUp00);
   tolua_function(tolua_S,"OnLButtonDBClick",tolua_CompileToLua_ControlList_OnLButtonDBClick00);
   tolua_function(tolua_S,"OnRButtonDown",tolua_CompileToLua_ControlList_OnRButtonDown00);
   tolua_function(tolua_S,"OnKeyDown",tolua_CompileToLua_ControlList_OnKeyDown00);
   tolua_function(tolua_S,"AddItem",tolua_CompileToLua_ControlList_AddItem00);
   tolua_function(tolua_S,"AddArrayItem",tolua_CompileToLua_ControlList_AddArrayItem00);
   tolua_function(tolua_S,"ResetItem",tolua_CompileToLua_ControlList_ResetItem00);
   tolua_function(tolua_S,"GetCurSelItem",tolua_CompileToLua_ControlList_GetCurSelItem00);
   tolua_function(tolua_S,"GetOldCurSelItem",tolua_CompileToLua_ControlList_GetOldCurSelItem00);
   tolua_function(tolua_S,"FindItemByID",tolua_CompileToLua_ControlList_FindItemByID00);
   tolua_function(tolua_S,"setItemTip",tolua_CompileToLua_ControlList_setItemTip00);
   tolua_function(tolua_S,"FindItemByItem",tolua_CompileToLua_ControlList_FindItemByItem00);
   tolua_function(tolua_S,"GetCurSelIndex",tolua_CompileToLua_ControlList_GetCurSelIndex00);
   tolua_function(tolua_S,"SetCurSelIndex",tolua_CompileToLua_ControlList_SetCurSelIndex00);
   tolua_function(tolua_S,"Clear",tolua_CompileToLua_ControlList_Clear00);
   tolua_function(tolua_S,"SetSelectChangeFun_2lua",tolua_CompileToLua_ControlList_SetSelectChangeFun_2lua00);
   tolua_function(tolua_S,"SetRBClickFun_2lua",tolua_CompileToLua_ControlList_SetRBClickFun_2lua00);
   tolua_function(tolua_S,"SetShiftRBClickFun_2lua",tolua_CompileToLua_ControlList_SetShiftRBClickFun_2lua00);
   tolua_function(tolua_S,"SetShiftLBClickFun_2lua",tolua_CompileToLua_ControlList_SetShiftLBClickFun_2lua00);
   tolua_function(tolua_S,"SetLDBClickFun_2lua",tolua_CompileToLua_ControlList_SetLDBClickFun_2lua00);
   tolua_function(tolua_S,"SetHyberClickFun_2lua",tolua_CompileToLua_ControlList_SetHyberClickFun_2lua00);
   tolua_function(tolua_S,"SetHyberRBtnDown_2lua",tolua_CompileToLua_ControlList_SetHyberRBtnDown_2lua00);
   tolua_function(tolua_S,"SetHyberItemClick_2lua",tolua_CompileToLua_ControlList_SetHyberItemClick_2lua00);
   tolua_function(tolua_S,"HaveSelBar",tolua_CompileToLua_ControlList_HaveSelBar00);
   tolua_function(tolua_S,"SetScrollPos",tolua_CompileToLua_ControlList_SetScrollPos00);
   tolua_function(tolua_S,"SetItemMaxCount",tolua_CompileToLua_ControlList_SetItemMaxCount00);
   tolua_function(tolua_S,"GetItemMaxCount",tolua_CompileToLua_ControlList_GetItemMaxCount00);
   tolua_function(tolua_S,"SetItemShowCount",tolua_CompileToLua_ControlList_SetItemShowCount00);
   tolua_function(tolua_S,"GetItemShowCount",tolua_CompileToLua_ControlList_GetItemShowCount00);
   tolua_function(tolua_S,"GetListItemHeight",tolua_CompileToLua_ControlList_GetListItemHeight00);
   tolua_function(tolua_S,"SetUIScrollBlend",tolua_CompileToLua_ControlList_SetUIScrollBlend00);
   tolua_function(tolua_S,"SetScrollHeight",tolua_CompileToLua_ControlList_SetScrollHeight00);
   tolua_function(tolua_S,"SetScrollValue",tolua_CompileToLua_ControlList_SetScrollValue00);
   tolua_function(tolua_S,"GetStartIndex",tolua_CompileToLua_ControlList_GetStartIndex00);
   tolua_function(tolua_S,"SetStartIndex",tolua_CompileToLua_ControlList_SetStartIndex00);
   tolua_function(tolua_S,"SetScrollVisable",tolua_CompileToLua_ControlList_SetScrollVisable00);
   tolua_function(tolua_S,"SetScrollBarEnable",tolua_CompileToLua_ControlList_SetScrollBarEnable00);
   tolua_function(tolua_S,"SetRBSelectEnable",tolua_CompileToLua_ControlList_SetRBSelectEnable00);
   tolua_function(tolua_S,"GetListItem",tolua_CompileToLua_ControlList_GetListItem00);
   tolua_function(tolua_S,"GetListItemCnt",tolua_CompileToLua_ControlList_GetListItemCnt00);
   tolua_function(tolua_S,"GetScrollBar",tolua_CompileToLua_ControlList_GetScrollBar00);
   tolua_function(tolua_S,"PtInHyber",tolua_CompileToLua_ControlList_PtInHyber00);
   tolua_function(tolua_S,"UpdataLine2D",tolua_CompileToLua_ControlList_UpdataLine2D00);
   tolua_function(tolua_S,"findHyber_player",tolua_CompileToLua_ControlList_findHyber_player00);
   tolua_function(tolua_S,"findHyber_item",tolua_CompileToLua_ControlList_findHyber_item00);
   tolua_function(tolua_S,"setShowTip",tolua_CompileToLua_ControlList_setShowTip00);
   tolua_function(tolua_S,"IsShowTip",tolua_CompileToLua_ControlList_IsShowTip00);
   tolua_function(tolua_S,"BeginUpdate",tolua_CompileToLua_ControlList_BeginUpdate00);
   tolua_function(tolua_S,"EndUpdate",tolua_CompileToLua_ControlList_EndUpdate00);
   tolua_function(tolua_S,"SetAutoSetCurIndex",tolua_CompileToLua_ControlList_SetAutoSetCurIndex00);
   tolua_function(tolua_S,"OnSelectChange",tolua_CompileToLua_ControlList_OnSelectChange00);
   tolua_function(tolua_S,"OnLDBClick",tolua_CompileToLua_ControlList_OnLDBClick00);
   tolua_function(tolua_S,"Refeash",tolua_CompileToLua_ControlList_Refeash00);
   tolua_function(tolua_S,"OnRBDown",tolua_CompileToLua_ControlList_OnRBDown00);
   tolua_function(tolua_S,"OnShiftRBDown",tolua_CompileToLua_ControlList_OnShiftRBDown00);
   tolua_function(tolua_S,"OnShiftLBDown",tolua_CompileToLua_ControlList_OnShiftLBDown00);
   tolua_function(tolua_S,"new",tolua_CompileToLua_ControlList_new00);
   tolua_function(tolua_S,"new_local",tolua_CompileToLua_ControlList_new00_local);
   tolua_function(tolua_S,".call",tolua_CompileToLua_ControlList_new00_local);
   tolua_function(tolua_S,"delete",tolua_CompileToLua_ControlList_delete00);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"ControlListEx","ControlListEx","ControlIconDrag",tolua_collect_ControlListEx);
  #else
  tolua_cclass(tolua_S,"ControlListEx","ControlListEx","ControlIconDrag",NULL);
  #endif
  tolua_beginmodule(tolua_S,"ControlListEx");
   tolua_function(tolua_S,"Render",tolua_CompileToLua_ControlListEx_Render00);
   tolua_function(tolua_S,"InitUIData",tolua_CompileToLua_ControlListEx_InitUIData00);
   tolua_function(tolua_S,"GetTilePt",tolua_CompileToLua_ControlListEx_GetTilePt00);
   tolua_function(tolua_S,"GetIconSize",tolua_CompileToLua_ControlListEx_GetIconSize00);
   tolua_function(tolua_S,"CanbePick",tolua_CompileToLua_ControlListEx_CanbePick00);
   tolua_function(tolua_S,"SetCanbePick",tolua_CompileToLua_ControlListEx_SetCanbePick00);
   tolua_function(tolua_S,"SetDrawInfoFun_2lua",tolua_CompileToLua_ControlListEx_SetDrawInfoFun_2lua00);
   tolua_function(tolua_S,"SetHaveSelFrame",tolua_CompileToLua_ControlListEx_SetHaveSelFrame00);
   tolua_function(tolua_S,"SetOnlyIcon",tolua_CompileToLua_ControlListEx_SetOnlyIcon00);
   tolua_function(tolua_S,"getCurItemPos",tolua_CompileToLua_ControlListEx_getCurItemPos00);
   tolua_function(tolua_S,"new",tolua_CompileToLua_ControlListEx_new00);
   tolua_function(tolua_S,"new_local",tolua_CompileToLua_ControlListEx_new00_local);
   tolua_function(tolua_S,".call",tolua_CompileToLua_ControlListEx_new00_local);
   tolua_function(tolua_S,"delete",tolua_CompileToLua_ControlListEx_delete00);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"ControlListImage","ControlListImage","ControlIconDrag",tolua_collect_ControlListImage);
  #else
  tolua_cclass(tolua_S,"ControlListImage","ControlListImage","ControlIconDrag",NULL);
  #endif
  tolua_beginmodule(tolua_S,"ControlListImage");
   tolua_variable(tolua_S,"m_nCurLvl",tolua_get_ControlListImage_m_nCurLvl,tolua_set_ControlListImage_m_nCurLvl);
   tolua_variable(tolua_S,"m_nMaxLvl",tolua_get_ControlListImage_m_nMaxLvl,tolua_set_ControlListImage_m_nMaxLvl);
   tolua_variable(tolua_S,"_bOrder",tolua_get_ControlListImage__bOrder,tolua_set_ControlListImage__bOrder);
   tolua_function(tolua_S,"Render",tolua_CompileToLua_ControlListImage_Render00);
   tolua_function(tolua_S,"InitUIData",tolua_CompileToLua_ControlListImage_InitUIData00);
   tolua_function(tolua_S,"GetIconSize",tolua_CompileToLua_ControlListImage_GetIconSize00);
   tolua_function(tolua_S,"GetTilePt",tolua_CompileToLua_ControlListImage_GetTilePt00);
   tolua_function(tolua_S,"CanbePick",tolua_CompileToLua_ControlListImage_CanbePick00);
   tolua_function(tolua_S,"SetCanbePick",tolua_CompileToLua_ControlListImage_SetCanbePick00);
   tolua_function(tolua_S,"SetLvlInfo",tolua_CompileToLua_ControlListImage_SetLvlInfo00);
   tolua_function(tolua_S,"SetScrollValue",tolua_CompileToLua_ControlListImage_SetScrollValue00);
   tolua_function(tolua_S,"setOrderType",tolua_CompileToLua_ControlListImage_setOrderType00);
   tolua_function(tolua_S,"GetMouseOnSel",tolua_CompileToLua_ControlListImage_GetMouseOnSel00);
   tolua_function(tolua_S,"new",tolua_CompileToLua_ControlListImage_new00);
   tolua_function(tolua_S,"new_local",tolua_CompileToLua_ControlListImage_new00_local);
   tolua_function(tolua_S,".call",tolua_CompileToLua_ControlListImage_new00_local);
   tolua_function(tolua_S,"delete",tolua_CompileToLua_ControlListImage_delete00);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"ControlPicture","ControlPicture","ControlObject",tolua_collect_ControlPicture);
  #else
  tolua_cclass(tolua_S,"ControlPicture","ControlPicture","ControlObject",NULL);
  #endif
  tolua_beginmodule(tolua_S,"ControlPicture");
   tolua_function(tolua_S,"OnLButtonDown",tolua_CompileToLua_ControlPicture_OnLButtonDown00);
   tolua_function(tolua_S,"OnMouseMove",tolua_CompileToLua_ControlPicture_OnMouseMove00);
   tolua_function(tolua_S,"OnMouseLeave",tolua_CompileToLua_ControlPicture_OnMouseLeave00);
   tolua_function(tolua_S,"OnLButtonDBClick",tolua_CompileToLua_ControlPicture_OnLButtonDBClick00);
   tolua_function(tolua_S,"SetPicClickFun_2lua",tolua_CompileToLua_ControlPicture_SetPicClickFun_2lua00);
   tolua_function(tolua_S,"SetOnMouseOn_2lua",tolua_CompileToLua_ControlPicture_SetOnMouseOn_2lua00);
   tolua_function(tolua_S,"SetOnMouseLeave_2lua",tolua_CompileToLua_ControlPicture_SetOnMouseLeave_2lua00);
   tolua_function(tolua_S,"SetOnLDBClickFun_2lua",tolua_CompileToLua_ControlPicture_SetOnLDBClickFun_2lua00);
   tolua_function(tolua_S,"setTip",tolua_CompileToLua_ControlPicture_setTip00);
   tolua_function(tolua_S,"setShowTip",tolua_CompileToLua_ControlPicture_setShowTip00);
   tolua_function(tolua_S,"IsShowTip",tolua_CompileToLua_ControlPicture_IsShowTip00);
   tolua_function(tolua_S,"OnClick",tolua_CompileToLua_ControlPicture_OnClick00);
   tolua_function(tolua_S,"new",tolua_CompileToLua_ControlPicture_new00);
   tolua_function(tolua_S,"new_local",tolua_CompileToLua_ControlPicture_new00_local);
   tolua_function(tolua_S,".call",tolua_CompileToLua_ControlPicture_new00_local);
   tolua_function(tolua_S,"delete",tolua_CompileToLua_ControlPicture_delete00);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"ControlProgress","ControlProgress","ControlObject",tolua_collect_ControlProgress);
  #else
  tolua_cclass(tolua_S,"ControlProgress","ControlProgress","ControlObject",NULL);
  #endif
  tolua_beginmodule(tolua_S,"ControlProgress");
   tolua_function(tolua_S,"UseFocus",tolua_CompileToLua_ControlProgress_UseFocus00);
   tolua_function(tolua_S,"InitUIData",tolua_CompileToLua_ControlProgress_InitUIData00);
   tolua_function(tolua_S,"SetVisable",tolua_CompileToLua_ControlProgress_SetVisable00);
   tolua_function(tolua_S,"OnMouseMove",tolua_CompileToLua_ControlProgress_OnMouseMove00);
   tolua_function(tolua_S,"GetValue",tolua_CompileToLua_ControlProgress_GetValue00);
   tolua_function(tolua_S,"SetValue",tolua_CompileToLua_ControlProgress_SetValue00);
   tolua_function(tolua_S,"GetMaxValue",tolua_CompileToLua_ControlProgress_GetMaxValue00);
   tolua_function(tolua_S,"SetMaxValue",tolua_CompileToLua_ControlProgress_SetMaxValue00);
   tolua_function(tolua_S,"GetRealWidth",tolua_CompileToLua_ControlProgress_GetRealWidth00);
   tolua_function(tolua_S,"Create",tolua_CompileToLua_ControlProgress_Create00);
   tolua_function(tolua_S,"Render",tolua_CompileToLua_ControlProgress_Render00);
   tolua_function(tolua_S,"setTipName",tolua_CompileToLua_ControlProgress_setTipName00);
   tolua_function(tolua_S,"IsShowTip",tolua_CompileToLua_ControlProgress_IsShowTip00);
   tolua_function(tolua_S,"setShowTip",tolua_CompileToLua_ControlProgress_setShowTip00);
   tolua_function(tolua_S,"new",tolua_CompileToLua_ControlProgress_new00);
   tolua_function(tolua_S,"new_local",tolua_CompileToLua_ControlProgress_new00_local);
   tolua_function(tolua_S,".call",tolua_CompileToLua_ControlProgress_new00_local);
   tolua_function(tolua_S,"delete",tolua_CompileToLua_ControlProgress_delete00);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"ControlScrollBar","ControlScrollBar","ControlObject",tolua_collect_ControlScrollBar);
  #else
  tolua_cclass(tolua_S,"ControlScrollBar","ControlScrollBar","ControlObject",NULL);
  #endif
  tolua_beginmodule(tolua_S,"ControlScrollBar");
   tolua_function(tolua_S,"Render",tolua_CompileToLua_ControlScrollBar_Render00);
   tolua_function(tolua_S,"InitUIData",tolua_CompileToLua_ControlScrollBar_InitUIData00);
   tolua_function(tolua_S,"OnMouseMove",tolua_CompileToLua_ControlScrollBar_OnMouseMove00);
   tolua_function(tolua_S,"OnLButtonDown",tolua_CompileToLua_ControlScrollBar_OnLButtonDown00);
   tolua_function(tolua_S,"OnLButtonUp",tolua_CompileToLua_ControlScrollBar_OnLButtonUp00);
   tolua_function(tolua_S,"GetValue",tolua_CompileToLua_ControlScrollBar_GetValue00);
   tolua_function(tolua_S,"SetValue",tolua_CompileToLua_ControlScrollBar_SetValue00);
   tolua_function(tolua_S,"IsDrag",tolua_CompileToLua_ControlScrollBar_IsDrag00);
   tolua_function(tolua_S,"ClearDrag",tolua_CompileToLua_ControlScrollBar_ClearDrag00);
   tolua_function(tolua_S,"SetEnable",tolua_CompileToLua_ControlScrollBar_SetEnable00);
   tolua_function(tolua_S,"GetEnable",tolua_CompileToLua_ControlScrollBar_GetEnable00);
   tolua_function(tolua_S,"SetUIScrollBarBlend",tolua_CompileToLua_ControlScrollBar_SetUIScrollBarBlend00);
   tolua_function(tolua_S,"SetScrollHeight",tolua_CompileToLua_ControlScrollBar_SetScrollHeight00);
   tolua_function(tolua_S,"GetMaxValue",tolua_CompileToLua_ControlScrollBar_GetMaxValue00);
   tolua_function(tolua_S,"SetMaxValue",tolua_CompileToLua_ControlScrollBar_SetMaxValue00);
   tolua_function(tolua_S,"SetStepValue",tolua_CompileToLua_ControlScrollBar_SetStepValue00);
   tolua_function(tolua_S,"OnUpdatePos",tolua_CompileToLua_ControlScrollBar_OnUpdatePos00);
   tolua_function(tolua_S,"new",tolua_CompileToLua_ControlScrollBar_new00);
   tolua_function(tolua_S,"new_local",tolua_CompileToLua_ControlScrollBar_new00_local);
   tolua_function(tolua_S,".call",tolua_CompileToLua_ControlScrollBar_new00_local);
   tolua_function(tolua_S,"delete",tolua_CompileToLua_ControlScrollBar_delete00);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"ControlScrollBarEx","ControlScrollBarEx","ControlScrollBar",tolua_collect_ControlScrollBarEx);
  #else
  tolua_cclass(tolua_S,"ControlScrollBarEx","ControlScrollBarEx","ControlScrollBar",NULL);
  #endif
  tolua_beginmodule(tolua_S,"ControlScrollBarEx");
   tolua_function(tolua_S,"OnMouseMove",tolua_CompileToLua_ControlScrollBarEx_OnMouseMove00);
   tolua_function(tolua_S,"OnLButtonDown",tolua_CompileToLua_ControlScrollBarEx_OnLButtonDown00);
   tolua_function(tolua_S,"OnUpdatePos",tolua_CompileToLua_ControlScrollBarEx_OnUpdatePos00);
   tolua_function(tolua_S,"new",tolua_CompileToLua_ControlScrollBarEx_new00);
   tolua_function(tolua_S,"new_local",tolua_CompileToLua_ControlScrollBarEx_new00_local);
   tolua_function(tolua_S,".call",tolua_CompileToLua_ControlScrollBarEx_new00_local);
   tolua_function(tolua_S,"delete",tolua_CompileToLua_ControlScrollBarEx_delete00);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"ControlTab","ControlTab","ControlObject",tolua_collect_ControlTab);
  #else
  tolua_cclass(tolua_S,"ControlTab","ControlTab","ControlObject",NULL);
  #endif
  tolua_beginmodule(tolua_S,"ControlTab");
   tolua_function(tolua_S,"Render",tolua_CompileToLua_ControlTab_Render00);
   tolua_function(tolua_S,"IsChild",tolua_CompileToLua_ControlTab_IsChild00);
   tolua_function(tolua_S,"FindControl",tolua_CompileToLua_ControlTab_FindControl00);
   tolua_function(tolua_S,"FindFrame",tolua_CompileToLua_ControlTab_FindFrame00);
   tolua_function(tolua_S,"InitUIData",tolua_CompileToLua_ControlTab_InitUIData00);
   tolua_function(tolua_S,"OnChar",tolua_CompileToLua_ControlTab_OnChar00);
   tolua_function(tolua_S,"OnMouseMove",tolua_CompileToLua_ControlTab_OnMouseMove00);
   tolua_function(tolua_S,"OnMouseWheel",tolua_CompileToLua_ControlTab_OnMouseWheel00);
   tolua_function(tolua_S,"OnLButtonUp",tolua_CompileToLua_ControlTab_OnLButtonUp00);
   tolua_function(tolua_S,"OnLButtonDown",tolua_CompileToLua_ControlTab_OnLButtonDown00);
   tolua_function(tolua_S,"OnLButtonDBClick",tolua_CompileToLua_ControlTab_OnLButtonDBClick00);
   tolua_function(tolua_S,"OnRButtonUp",tolua_CompileToLua_ControlTab_OnRButtonUp00);
   tolua_function(tolua_S,"OnRButtonDown",tolua_CompileToLua_ControlTab_OnRButtonDown00);
   tolua_function(tolua_S,"OnRButtonDBClick",tolua_CompileToLua_ControlTab_OnRButtonDBClick00);
   tolua_function(tolua_S,"OnKeyDown",tolua_CompileToLua_ControlTab_OnKeyDown00);
   tolua_function(tolua_S,"OnKeyUp",tolua_CompileToLua_ControlTab_OnKeyUp00);
   tolua_function(tolua_S,"OnFrameChange",tolua_CompileToLua_ControlTab_OnFrameChange00);
   tolua_function(tolua_S,"new",tolua_CompileToLua_ControlTab_new00);
   tolua_function(tolua_S,"new_local",tolua_CompileToLua_ControlTab_new00_local);
   tolua_function(tolua_S,".call",tolua_CompileToLua_ControlTab_new00_local);
   tolua_function(tolua_S,"delete",tolua_CompileToLua_ControlTab_delete00);
  tolua_endmodule(tolua_S);
  tolua_constant(tolua_S,"eKeyNormal",eKeyNormal);
  tolua_constant(tolua_S,"eKeyColor",eKeyColor);
  tolua_constant(tolua_S,"eKeyUrl",eKeyUrl);
  tolua_constant(tolua_S,"eKeyImg",eKeyImg);
  tolua_constant(tolua_S,"eKeyEnd",eKeyEnd);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"ControlText","ControlText","ControlObject",tolua_collect_ControlText);
  #else
  tolua_cclass(tolua_S,"ControlText","ControlText","ControlObject",NULL);
  #endif
  tolua_beginmodule(tolua_S,"ControlText");
   tolua_function(tolua_S,"InitUIData",tolua_CompileToLua_ControlText_InitUIData00);
   tolua_function(tolua_S,"Render",tolua_CompileToLua_ControlText_Render00);
   tolua_function(tolua_S,"OnMouseMove",tolua_CompileToLua_ControlText_OnMouseMove00);
   tolua_function(tolua_S,"OnLButtonDown",tolua_CompileToLua_ControlText_OnLButtonDown00);
   tolua_function(tolua_S,"SetText",tolua_CompileToLua_ControlText_SetText00);
   tolua_function(tolua_S,"SetText",tolua_CompileToLua_ControlText_SetText01);
   tolua_function(tolua_S,"SetText",tolua_CompileToLua_ControlText_SetText02);
   tolua_function(tolua_S,"SetTextW",tolua_CompileToLua_ControlText_SetTextW00);
   tolua_function(tolua_S,"SetCurLine",tolua_CompileToLua_ControlText_SetCurLine00);
   tolua_function(tolua_S,"GetText",tolua_CompileToLua_ControlText_GetText00);
   tolua_function(tolua_S,"Create",tolua_CompileToLua_ControlText_Create00);
   tolua_function(tolua_S,"SetText_HyberClickFun_2lua",tolua_CompileToLua_ControlText_SetText_HyberClickFun_2lua00);
   tolua_function(tolua_S,"setDesIconTip",tolua_CompileToLua_ControlText_setDesIconTip00);
   tolua_function(tolua_S,"setShowDesIconTip",tolua_CompileToLua_ControlText_setShowDesIconTip00);
   tolua_function(tolua_S,"Clear",tolua_CompileToLua_ControlText_Clear00);
   tolua_function(tolua_S,"SetIsShowLine",tolua_CompileToLua_ControlText_SetIsShowLine00);
   tolua_function(tolua_S,"setTip",tolua_CompileToLua_ControlText_setTip00);
   tolua_function(tolua_S,"setShowTip",tolua_CompileToLua_ControlText_setShowTip00);
   tolua_function(tolua_S,"SetSingleMaxTextCnt",tolua_CompileToLua_ControlText_SetSingleMaxTextCnt00);
   tolua_function(tolua_S,"SetOffsetY",tolua_CompileToLua_ControlText_SetOffsetY00);
   tolua_cclass(tolua_S,"STextData","ControlText::STextData","",NULL);
   tolua_beginmodule(tolua_S,"STextData");
    tolua_variable(tolua_S,"str",tolua_get_ControlText__STextData_str,tolua_set_ControlText__STextData_str);
    tolua_variable(tolua_S,"nTextureID",tolua_get_ControlText__STextData_nTextureID,tolua_set_ControlText__STextData_nTextureID);
    tolua_variable(tolua_S,"rc",tolua_get_ControlText__STextData_rc,tolua_set_ControlText__STextData_rc);
    tolua_variable(tolua_S,"nLine",tolua_get_ControlText__STextData_nLine,tolua_set_ControlText__STextData_nLine);
   tolua_endmodule(tolua_S);
   #ifdef __cplusplus
   tolua_cclass(tolua_S,"SText","ControlText::SText","",tolua_collect_ControlText__SText);
   #else
   tolua_cclass(tolua_S,"SText","ControlText::SText","",NULL);
   #endif
   tolua_beginmodule(tolua_S,"SText");
    tolua_function(tolua_S,"new",tolua_CompileToLua_ControlText_SText_new00);
    tolua_function(tolua_S,"new_local",tolua_CompileToLua_ControlText_SText_new00_local);
    tolua_function(tolua_S,".call",tolua_CompileToLua_ControlText_SText_new00_local);
    tolua_variable(tolua_S,"type",tolua_get_ControlText__SText_type,tolua_set_ControlText__SText_type);
    tolua_variable(tolua_S,"col",tolua_get_ControlText__SText_col,tolua_set_ControlText__SText_col);
    tolua_variable(tolua_S,"vtTextData",tolua_get_ControlText__SText_vtTextData,tolua_set_ControlText__SText_vtTextData);
    tolua_variable(tolua_S,"bPtInText",tolua_get_ControlText__SText_bPtInText,tolua_set_ControlText__SText_bPtInText);
    tolua_function(tolua_S,"CheckPtInText",tolua_CompileToLua_ControlText_SText_CheckPtInText00);
    tolua_function(tolua_S,"GetTextW",tolua_CompileToLua_ControlText_SText_GetTextW00);
    tolua_function(tolua_S,"GetTextA",tolua_CompileToLua_ControlText_SText_GetTextA00);
   tolua_endmodule(tolua_S);
   tolua_function(tolua_S,"WordBreak",tolua_CompileToLua_ControlText_WordBreak00);
   tolua_function(tolua_S,"GetTextData",tolua_CompileToLua_ControlText_GetTextData00);
   tolua_function(tolua_S,"CalculatePoint",tolua_CompileToLua_ControlText_CalculatePoint00);
   tolua_function(tolua_S,"CheckDrawMode",tolua_CompileToLua_ControlText_CheckDrawMode00);
   tolua_function(tolua_S,"CPtoX",tolua_CompileToLua_ControlText_CPtoX00);
   tolua_function(tolua_S,"XtoCP",tolua_CompileToLua_ControlText_XtoCP00);
   tolua_function(tolua_S,"MoveTextDataPos",tolua_CompileToLua_ControlText_MoveTextDataPos00);
   tolua_function(tolua_S,"new",tolua_CompileToLua_ControlText_new00);
   tolua_function(tolua_S,"new_local",tolua_CompileToLua_ControlText_new00_local);
   tolua_function(tolua_S,".call",tolua_CompileToLua_ControlText_new00_local);
   tolua_function(tolua_S,"delete",tolua_CompileToLua_ControlText_delete00);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"MouseManager","MouseManager","",tolua_collect_MouseManager);
  #else
  tolua_cclass(tolua_S,"MouseManager","MouseManager","",NULL);
  #endif
  tolua_beginmodule(tolua_S,"MouseManager");
   tolua_constant(tolua_S,"Type_Arrow",MouseManager::Type_Arrow);
   tolua_constant(tolua_S,"Type_Rotate",MouseManager::Type_Rotate);
   tolua_constant(tolua_S,"Type_Wait",MouseManager::Type_Wait);
   tolua_constant(tolua_S,"Type_LockTarget",MouseManager::Type_LockTarget);
   tolua_constant(tolua_S,"Type_Attack",MouseManager::Type_Attack);
   tolua_constant(tolua_S,"Type_Dialog",MouseManager::Type_Dialog);
   tolua_constant(tolua_S,"Type_Shop",MouseManager::Type_Shop);
   tolua_constant(tolua_S,"Type_Pick",MouseManager::Type_Pick);
   tolua_constant(tolua_S,"Type_Group",MouseManager::Type_Group);
   tolua_constant(tolua_S,"Type_CollectHerb",MouseManager::Type_CollectHerb);
   tolua_constant(tolua_S,"Type_CollectMine",MouseManager::Type_CollectMine);
   tolua_constant(tolua_S,"Type_CollectWood",MouseManager::Type_CollectWood);
   tolua_constant(tolua_S,"Type_LockItem",MouseManager::Type_LockItem);
   tolua_constant(tolua_S,"Type_UnLockItem",MouseManager::Type_UnLockItem);
   tolua_constant(tolua_S,"Type_UseItem",MouseManager::Type_UseItem);
   tolua_constant(tolua_S,"Type_Max",MouseManager::Type_Max);
   tolua_function(tolua_S,"Render",tolua_CompileToLua_MouseManager_Render00);
   tolua_function(tolua_S,"new",tolua_CompileToLua_MouseManager_new00);
   tolua_function(tolua_S,"new_local",tolua_CompileToLua_MouseManager_new00_local);
   tolua_function(tolua_S,".call",tolua_CompileToLua_MouseManager_new00_local);
   tolua_function(tolua_S,"delete",tolua_CompileToLua_MouseManager_delete00);
  tolua_endmodule(tolua_S);
  tolua_constant(tolua_S,"UI_Render_LayerFirst",UI_Render_LayerFirst);
  tolua_constant(tolua_S,"UI_Render_LayerSecond",UI_Render_LayerSecond);
  tolua_constant(tolua_S,"UI_Render_LayerThree",UI_Render_LayerThree);
  tolua_constant(tolua_S,"UI_Render_LayerMax",UI_Render_LayerMax);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"UiManager","UiManager","",tolua_collect_UiManager);
  #else
  tolua_cclass(tolua_S,"UiManager","UiManager","",NULL);
  #endif
  tolua_beginmodule(tolua_S,"UiManager");
   #ifdef __cplusplus
   tolua_cclass(tolua_S,"S_UI","UiManager::S_UI","",tolua_collect_UiManager__S_UI);
   #else
   tolua_cclass(tolua_S,"S_UI","UiManager::S_UI","",NULL);
   #endif
   tolua_beginmodule(tolua_S,"S_UI");
    tolua_function(tolua_S,"new",tolua_CompileToLua_UiManager_S_UI_new00);
    tolua_function(tolua_S,"new_local",tolua_CompileToLua_UiManager_S_UI_new00_local);
    tolua_function(tolua_S,".call",tolua_CompileToLua_UiManager_S_UI_new00_local);
    tolua_function(tolua_S,"Release",tolua_CompileToLua_UiManager_S_UI_Release00);
    tolua_variable(tolua_S,"m_strFileName",tolua_get_UiManager__S_UI_m_strFileName,tolua_set_UiManager__S_UI_m_strFileName);
    tolua_variable(tolua_S,"m_pUI",tolua_get_UiManager__S_UI_m_pUI_ptr,tolua_set_UiManager__S_UI_m_pUI_ptr);
    tolua_variable(tolua_S,"m_bNeedRelease",tolua_get_UiManager__S_UI_m_bNeedRelease,tolua_set_UiManager__S_UI_m_bNeedRelease);
   tolua_endmodule(tolua_S);
   tolua_function(tolua_S,"FrameMove",tolua_CompileToLua_UiManager_FrameMove00);
   tolua_function(tolua_S,"Render",tolua_CompileToLua_UiManager_Render00);
   tolua_function(tolua_S,"RenderTips",tolua_CompileToLua_UiManager_RenderTips00);
   tolua_function(tolua_S,"InvalidateDeviceObjects",tolua_CompileToLua_UiManager_InvalidateDeviceObjects00);
   tolua_function(tolua_S,"RestoreDeviceObjects",tolua_CompileToLua_UiManager_RestoreDeviceObjects00);
   tolua_function(tolua_S,"MsgProc",tolua_CompileToLua_UiManager_MsgProc00);
   tolua_function(tolua_S,"SetPlaySoundFun_2lua",tolua_CompileToLua_UiManager_SetPlaySoundFun_2lua00);
   tolua_function(tolua_S,"PlaySound",tolua_CompileToLua_UiManager_PlaySound00);
   tolua_function(tolua_S,"AddFrame",tolua_CompileToLua_UiManager_AddFrame00);
   tolua_function(tolua_S,"RemoveFrame",tolua_CompileToLua_UiManager_RemoveFrame00);
   tolua_function(tolua_S,"AddFrame",tolua_CompileToLua_UiManager_AddFrame01);
   tolua_function(tolua_S,"RemoveFrame",tolua_CompileToLua_UiManager_RemoveFrame01);
   tolua_function(tolua_S,"HasModalWindow",tolua_CompileToLua_UiManager_HasModalWindow00);
   tolua_function(tolua_S,"OnFrameRun",tolua_CompileToLua_UiManager_OnFrameRun00);
   tolua_function(tolua_S,"OnFrameRender",tolua_CompileToLua_UiManager_OnFrameRender00);
   tolua_function(tolua_S,"OnButtonClick",tolua_CompileToLua_UiManager_OnButtonClick00);
   tolua_function(tolua_S,"OnEditEnter",tolua_CompileToLua_UiManager_OnEditEnter00);
   tolua_function(tolua_S,"OnCheckBoxCheck",tolua_CompileToLua_UiManager_OnCheckBoxCheck00);
   tolua_function(tolua_S,"OnListSelectChange",tolua_CompileToLua_UiManager_OnListSelectChange00);
   tolua_function(tolua_S,"OnListLDBClick",tolua_CompileToLua_UiManager_OnListLDBClick00);
   tolua_function(tolua_S,"OnIconDragOn",tolua_CompileToLua_UiManager_OnIconDragOn00);
   tolua_function(tolua_S,"OnIconLDBClick",tolua_CompileToLua_UiManager_OnIconLDBClick00);
   tolua_function(tolua_S,"OnIconRButtonUp",tolua_CompileToLua_UiManager_OnIconRButtonUp00);
   tolua_function(tolua_S,"OnScrollBarUpdatePos",tolua_CompileToLua_UiManager_OnScrollBarUpdatePos00);
   tolua_function(tolua_S,"OnScrollBarExUpdatePos",tolua_CompileToLua_UiManager_OnScrollBarExUpdatePos00);
   tolua_function(tolua_S,"OnComboBoxChange",tolua_CompileToLua_UiManager_OnComboBoxChange00);
   tolua_function(tolua_S,"OnTextHyberClick",tolua_CompileToLua_UiManager_OnTextHyberClick00);
   tolua_function(tolua_S,"FindControl",tolua_CompileToLua_UiManager_FindControl00);
   tolua_function(tolua_S,"FindFrame",tolua_CompileToLua_UiManager_FindFrame00);
   tolua_function(tolua_S,"CreateWidget",tolua_CompileToLua_UiManager_CreateWidget00);
   tolua_function(tolua_S,"Compositor",tolua_CompileToLua_UiManager_Compositor00);
   tolua_function(tolua_S,"ToTop",tolua_CompileToLua_UiManager_ToTop00);
   tolua_function(tolua_S,"ToBottom",tolua_CompileToLua_UiManager_ToBottom00);
   tolua_function(tolua_S,"IsMouseInUI",tolua_CompileToLua_UiManager_IsMouseInUI00);
   tolua_function(tolua_S,"GetFrameFocus",tolua_CompileToLua_UiManager_GetFrameFocus00);
   tolua_function(tolua_S,"HideDlg",tolua_CompileToLua_UiManager_HideDlg00);
   tolua_function(tolua_S,"SetFocus",tolua_CompileToLua_UiManager_SetFocus00);
   tolua_function(tolua_S,"GetFocus",tolua_CompileToLua_UiManager_GetFocus00);
   tolua_function(tolua_S,"isInUI",tolua_CompileToLua_UiManager_isInUI00);
   tolua_function(tolua_S,"UpdataFrame",tolua_CompileToLua_UiManager_UpdataFrame00);
   tolua_function(tolua_S,"Cover",tolua_CompileToLua_UiManager_Cover00);
   tolua_function(tolua_S,"Destroy",tolua_CompileToLua_UiManager_Destroy00);
   tolua_function(tolua_S,"new",tolua_CompileToLua_UiManager_new00);
   tolua_function(tolua_S,"new_local",tolua_CompileToLua_UiManager_new00_local);
   tolua_function(tolua_S,".call",tolua_CompileToLua_UiManager_new00_local);
   tolua_function(tolua_S,"delete",tolua_CompileToLua_UiManager_delete00);
  tolua_endmodule(tolua_S);
  tolua_module(tolua_S,"irr",0);
  tolua_beginmodule(tolua_S,"irr");
   tolua_function(tolua_S,"UiManagerInstance",tolua_CompileToLua_irr_UiManagerInstance00);
  tolua_endmodule(tolua_S);
 tolua_endmodule(tolua_S);
 return 1;
}


#if defined(LUA_VERSION_NUM) && LUA_VERSION_NUM >= 501
 TOLUA_API int luaopen_CompileToLua (lua_State* tolua_S) {
 return tolua_CompileToLua_open(tolua_S);
};
#endif

