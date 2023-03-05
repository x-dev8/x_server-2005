/*
** Lua binding: compile
** Generated automatically by tolua++-1.0.92 on 12/18/10 17:48:06.
*/

#ifndef __cplusplus
#include "stdlib.h"
#endif
#include "string.h"

#include "tolua++.h"

/* Exported function */
TOLUA_API int  tolua_compile_open (lua_State* tolua_S);

#include "ui\RankList.h"

/* function to release collected object via destructor */
#ifdef __cplusplus

static int tolua_collect_CUI_ID_FRAME_RankList (lua_State* tolua_S)
{
 CUI_ID_FRAME_RankList* self = (CUI_ID_FRAME_RankList*) tolua_tousertype(tolua_S,1,0);
	delete self;
	return 0;
}
#endif


/* function to register type */
static void tolua_reg_types (lua_State* tolua_S)
{
 tolua_usertype(tolua_S,"CUIBase");
 tolua_usertype(tolua_S,"CUI_ID_FRAME_RankList");
}

/* method: new of class  CUI_ID_FRAME_RankList */
#ifndef TOLUA_DISABLE_tolua_compile_CUI_ID_FRAME_RankList_new00
static int tolua_compile_CUI_ID_FRAME_RankList_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CUI_ID_FRAME_RankList",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CUI_ID_FRAME_RankList* tolua_ret = (CUI_ID_FRAME_RankList*)  new CUI_ID_FRAME_RankList();
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"CUI_ID_FRAME_RankList");
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

/* method: new_local of class  CUI_ID_FRAME_RankList */
#ifndef TOLUA_DISABLE_tolua_compile_CUI_ID_FRAME_RankList_new00_local
static int tolua_compile_CUI_ID_FRAME_RankList_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CUI_ID_FRAME_RankList",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CUI_ID_FRAME_RankList* tolua_ret = (CUI_ID_FRAME_RankList*)  new CUI_ID_FRAME_RankList();
   tolua_pushusertype_and_takeownership(tolua_S,(void *)tolua_ret,"CUI_ID_FRAME_RankList");
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

/* method: LoadFrame of class  CUI_ID_FRAME_RankList */
#ifndef TOLUA_DISABLE_tolua_compile_CUI_ID_FRAME_RankList_LoadFrame00
static int tolua_compile_CUI_ID_FRAME_RankList_LoadFrame00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CUI_ID_FRAME_RankList",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CUI_ID_FRAME_RankList* self = (CUI_ID_FRAME_RankList*)  tolua_tousertype(tolua_S,1,0);
  const std::string filename = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
  const char* frameName = ((const char*)  tolua_tostring(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'LoadFrame'",NULL);
#endif
  {
   self->LoadFrame(filename,frameName);
   tolua_pushcppstring(tolua_S,(const char*)filename);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'LoadFrame'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: UnLoadFrame of class  CUI_ID_FRAME_RankList */
#ifndef TOLUA_DISABLE_tolua_compile_CUI_ID_FRAME_RankList_UnLoadFrame00
static int tolua_compile_CUI_ID_FRAME_RankList_UnLoadFrame00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CUI_ID_FRAME_RankList",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CUI_ID_FRAME_RankList* self = (CUI_ID_FRAME_RankList*)  tolua_tousertype(tolua_S,1,0);
  const std::string filename = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'UnLoadFrame'",NULL);
#endif
  {
   self->UnLoadFrame(filename);
   tolua_pushcppstring(tolua_S,(const char*)filename);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'UnLoadFrame'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetFrameVisible of class  CUI_ID_FRAME_RankList */
#ifndef TOLUA_DISABLE_tolua_compile_CUI_ID_FRAME_RankList_SetFrameVisible00
static int tolua_compile_CUI_ID_FRAME_RankList_SetFrameVisible00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CUI_ID_FRAME_RankList",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isboolean(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CUI_ID_FRAME_RankList* self = (CUI_ID_FRAME_RankList*)  tolua_tousertype(tolua_S,1,0);
  const char* frameName = ((const char*)  tolua_tostring(tolua_S,2,0));
  bool visible = ((bool)  tolua_toboolean(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetFrameVisible'",NULL);
#endif
  {
   self->SetFrameVisible(frameName,visible);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetFrameVisible'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetRankSortFunc of class  CUI_ID_FRAME_RankList */
#ifndef TOLUA_DISABLE_tolua_compile_CUI_ID_FRAME_RankList_SetRankSortFunc00
static int tolua_compile_CUI_ID_FRAME_RankList_SetRankSortFunc00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CUI_ID_FRAME_RankList",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isstring(tolua_S,4,0,&tolua_err) ||
     !tolua_isstring(tolua_S,5,0,&tolua_err) ||
     !tolua_isstring(tolua_S,6,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,7,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CUI_ID_FRAME_RankList* self = (CUI_ID_FRAME_RankList*)  tolua_tousertype(tolua_S,1,0);
  const char* frameName = ((const char*)  tolua_tostring(tolua_S,2,0));
  const char* relativeControlId = ((const char*)  tolua_tostring(tolua_S,3,0));
  const char* relativeArrowControlId = ((const char*)  tolua_tostring(tolua_S,4,0));
  const char* luaFunc = ((const char*)  tolua_tostring(tolua_S,5,0));
  const char* key = ((const char*)  tolua_tostring(tolua_S,6,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetRankSortFunc'",NULL);
#endif
  {
   self->SetRankSortFunc(frameName,relativeControlId,relativeArrowControlId,luaFunc,key);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetRankSortFunc'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetControlCheckBoxText of class  CUI_ID_FRAME_RankList */
#ifndef TOLUA_DISABLE_tolua_compile_CUI_ID_FRAME_RankList_SetControlCheckBoxText00
static int tolua_compile_CUI_ID_FRAME_RankList_SetControlCheckBoxText00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CUI_ID_FRAME_RankList",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isstring(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CUI_ID_FRAME_RankList* self = (CUI_ID_FRAME_RankList*)  tolua_tousertype(tolua_S,1,0);
  const char* frameName = ((const char*)  tolua_tostring(tolua_S,2,0));
  const char* controlId = ((const char*)  tolua_tostring(tolua_S,3,0));
  const char* text = ((const char*)  tolua_tostring(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetControlCheckBoxText'",NULL);
#endif
  {
   self->SetControlCheckBoxText(frameName,controlId,text);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetControlCheckBoxText'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetControlText of class  CUI_ID_FRAME_RankList */
#ifndef TOLUA_DISABLE_tolua_compile_CUI_ID_FRAME_RankList_SetControlText00
static int tolua_compile_CUI_ID_FRAME_RankList_SetControlText00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CUI_ID_FRAME_RankList",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isstring(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CUI_ID_FRAME_RankList* self = (CUI_ID_FRAME_RankList*)  tolua_tousertype(tolua_S,1,0);
  const char* frameName = ((const char*)  tolua_tostring(tolua_S,2,0));
  const char* controlId = ((const char*)  tolua_tostring(tolua_S,3,0));
  const char* text = ((const char*)  tolua_tostring(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetControlText'",NULL);
#endif
  {
   self->SetControlText(frameName,controlId,text);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetControlText'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetControlButtonText of class  CUI_ID_FRAME_RankList */
#ifndef TOLUA_DISABLE_tolua_compile_CUI_ID_FRAME_RankList_SetControlButtonText00
static int tolua_compile_CUI_ID_FRAME_RankList_SetControlButtonText00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CUI_ID_FRAME_RankList",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isstring(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CUI_ID_FRAME_RankList* self = (CUI_ID_FRAME_RankList*)  tolua_tousertype(tolua_S,1,0);
  const char* frameName = ((const char*)  tolua_tostring(tolua_S,2,0));
  const char* controlId = ((const char*)  tolua_tostring(tolua_S,3,0));
  const char* text = ((const char*)  tolua_tostring(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetControlButtonText'",NULL);
#endif
  {
   self->SetControlButtonText(frameName,controlId,text);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetControlButtonText'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: AssociateList of class  CUI_ID_FRAME_RankList */
#ifndef TOLUA_DISABLE_tolua_compile_CUI_ID_FRAME_RankList_AssociateList00
static int tolua_compile_CUI_ID_FRAME_RankList_AssociateList00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CUI_ID_FRAME_RankList",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isstring(tolua_S,4,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CUI_ID_FRAME_RankList* self = (CUI_ID_FRAME_RankList*)  tolua_tousertype(tolua_S,1,0);
  const char* frameName = ((const char*)  tolua_tostring(tolua_S,2,0));
  const char* fatherControlId = ((const char*)  tolua_tostring(tolua_S,3,0));
  const char* childControlId = ((const char*)  tolua_tostring(tolua_S,4,0));
  int drawFormat = ((int)  tolua_tonumber(tolua_S,5,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'AssociateList'",NULL);
#endif
  {
   self->AssociateList(frameName,fatherControlId,childControlId,drawFormat);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'AssociateList'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: AssociateListImg of class  CUI_ID_FRAME_RankList */
#ifndef TOLUA_DISABLE_tolua_compile_CUI_ID_FRAME_RankList_AssociateListImg00
static int tolua_compile_CUI_ID_FRAME_RankList_AssociateListImg00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CUI_ID_FRAME_RankList",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isstring(tolua_S,4,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CUI_ID_FRAME_RankList* self = (CUI_ID_FRAME_RankList*)  tolua_tousertype(tolua_S,1,0);
  const char* frameName = ((const char*)  tolua_tostring(tolua_S,2,0));
  const char* fatherControlId = ((const char*)  tolua_tostring(tolua_S,3,0));
  const char* controlId = ((const char*)  tolua_tostring(tolua_S,4,0));
  int drawFormat = ((int)  tolua_tonumber(tolua_S,5,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'AssociateListImg'",NULL);
#endif
  {
   self->AssociateListImg(frameName,fatherControlId,controlId,drawFormat);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'AssociateListImg'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: AddListItem of class  CUI_ID_FRAME_RankList */
#ifndef TOLUA_DISABLE_tolua_compile_CUI_ID_FRAME_RankList_AddListItem00
static int tolua_compile_CUI_ID_FRAME_RankList_AddListItem00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CUI_ID_FRAME_RankList",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isstring(tolua_S,4,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,0,&tolua_err) ||
     !tolua_isstring(tolua_S,6,0,&tolua_err) ||
     !tolua_isboolean(tolua_S,7,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,8,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CUI_ID_FRAME_RankList* self = (CUI_ID_FRAME_RankList*)  tolua_tousertype(tolua_S,1,0);
  const char* frameName = ((const char*)  tolua_tostring(tolua_S,2,0));
  const char* controlId = ((const char*)  tolua_tostring(tolua_S,3,0));
  const char* text = ((const char*)  tolua_tostring(tolua_S,4,0));
  unsigned int color = ((unsigned int)  tolua_tonumber(tolua_S,5,0));
  const char* data = ((const char*)  tolua_tostring(tolua_S,6,0));
  bool bMiddle = ((bool)  tolua_toboolean(tolua_S,7,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'AddListItem'",NULL);
#endif
  {
   self->AddListItem(frameName,controlId,text,color,data,bMiddle);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'AddListItem'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: AddListImageItem of class  CUI_ID_FRAME_RankList */
#ifndef TOLUA_DISABLE_tolua_compile_CUI_ID_FRAME_RankList_AddListImageItem00
static int tolua_compile_CUI_ID_FRAME_RankList_AddListImageItem00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CUI_ID_FRAME_RankList",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isstring(tolua_S,4,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,0,&tolua_err) ||
     !tolua_isstring(tolua_S,6,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,7,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CUI_ID_FRAME_RankList* self = (CUI_ID_FRAME_RankList*)  tolua_tousertype(tolua_S,1,0);
  const char* frameName = ((const char*)  tolua_tostring(tolua_S,2,0));
  const char* controlId = ((const char*)  tolua_tostring(tolua_S,3,0));
  const char* text = ((const char*)  tolua_tostring(tolua_S,4,0));
  unsigned int color = ((unsigned int)  tolua_tonumber(tolua_S,5,0));
  const char* data = ((const char*)  tolua_tostring(tolua_S,6,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'AddListImageItem'",NULL);
#endif
  {
   self->AddListImageItem(frameName,controlId,text,color,data);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'AddListImageItem'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

#ifndef TOLUA_DISABLE_tolua_compile_CUI_ID_FRAME_RankList_AddListImageCharItem00
static int tolua_compile_CUI_ID_FRAME_RankList_AddListImageCharItem00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
		!tolua_isusertype(tolua_S,1,"CUI_ID_FRAME_RankList",0,&tolua_err) ||
		!tolua_isstring(tolua_S,2,0,&tolua_err) ||
		!tolua_isstring(tolua_S,3,0,&tolua_err) ||
		!tolua_isstring(tolua_S,4,0,&tolua_err) ||
		!tolua_isnumber(tolua_S,5,0,&tolua_err) ||
		!tolua_isstring(tolua_S,6,0,&tolua_err) ||
		!tolua_isnoobj(tolua_S,7,&tolua_err)
		)
		goto tolua_lerror;
	else
#endif
	{
		CUI_ID_FRAME_RankList* self = (CUI_ID_FRAME_RankList*)  tolua_tousertype(tolua_S,1,0);
		const char* frameName = ((const char*)  tolua_tostring(tolua_S,2,0));
		const char* controlId = ((const char*)  tolua_tostring(tolua_S,3,0));
		const char* text = ((const char*)  tolua_tostring(tolua_S,4,0));
		unsigned int color = ((unsigned int)  tolua_tonumber(tolua_S,5,0));
		const char* data = ((const char*)  tolua_tostring(tolua_S,6,0));
#ifndef TOLUA_RELEASE
		if (!self) tolua_error(tolua_S,"invalid 'self' in function 'AddListImageCharItem'",NULL);
#endif
		{
			self->AddListImageCharItem(frameName,controlId,text,color,data);
		}
	}
	return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'AddListImageCharItem'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: ClearList of class  CUI_ID_FRAME_RankList */
#ifndef TOLUA_DISABLE_tolua_compile_CUI_ID_FRAME_RankList_ClearList00
static int tolua_compile_CUI_ID_FRAME_RankList_ClearList00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CUI_ID_FRAME_RankList",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CUI_ID_FRAME_RankList* self = (CUI_ID_FRAME_RankList*)  tolua_tousertype(tolua_S,1,0);
  const char* frameName = ((const char*)  tolua_tostring(tolua_S,2,0));
  const char* controlId = ((const char*)  tolua_tostring(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'ClearList'",NULL);
#endif
  {
   self->ClearList(frameName,controlId);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'ClearList'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: ClearListImage of class  CUI_ID_FRAME_RankList */
#ifndef TOLUA_DISABLE_tolua_compile_CUI_ID_FRAME_RankList_ClearListImage00
static int tolua_compile_CUI_ID_FRAME_RankList_ClearListImage00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CUI_ID_FRAME_RankList",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CUI_ID_FRAME_RankList* self = (CUI_ID_FRAME_RankList*)  tolua_tousertype(tolua_S,1,0);
  const char* frameName = ((const char*)  tolua_tostring(tolua_S,2,0));
  const char* controlId = ((const char*)  tolua_tostring(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'ClearListImage'",NULL);
#endif
  {
   self->ClearListImage(frameName,controlId);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'ClearListImage'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetRankRowSize of class  CUI_ID_FRAME_RankList */
#ifndef TOLUA_DISABLE_tolua_compile_CUI_ID_FRAME_RankList_GetRankRowSize00
static int tolua_compile_CUI_ID_FRAME_RankList_GetRankRowSize00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CUI_ID_FRAME_RankList",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CUI_ID_FRAME_RankList* self = (CUI_ID_FRAME_RankList*)  tolua_tousertype(tolua_S,1,0);
  const char* type = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetRankRowSize'",NULL);
#endif
  {
   int tolua_ret = (int)  self->GetRankRowSize(type);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetRankRowSize'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetRankContent of class  CUI_ID_FRAME_RankList */
#ifndef TOLUA_DISABLE_tolua_compile_CUI_ID_FRAME_RankList_GetRankContent00
static int tolua_compile_CUI_ID_FRAME_RankList_GetRankContent00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CUI_ID_FRAME_RankList",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isstring(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CUI_ID_FRAME_RankList* self = (CUI_ID_FRAME_RankList*)  tolua_tousertype(tolua_S,1,0);
  const char* type = ((const char*)  tolua_tostring(tolua_S,2,0));
  int row = ((int)  tolua_tonumber(tolua_S,3,0));
  const char* column = ((const char*)  tolua_tostring(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetRankContent'",NULL);
#endif
  {
   const char* tolua_ret = (const char*)  self->GetRankContent(type,row,column);
   tolua_pushstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetRankContent'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetProfessionName of class  CUI_ID_FRAME_RankList */
#ifndef TOLUA_DISABLE_tolua_compile_CUI_ID_FRAME_RankList_GetProfessionName00
static int tolua_compile_CUI_ID_FRAME_RankList_GetProfessionName00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CUI_ID_FRAME_RankList",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CUI_ID_FRAME_RankList* self = (CUI_ID_FRAME_RankList*)  tolua_tousertype(tolua_S,1,0);
  int type = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetProfessionName'",NULL);
#endif
  {
   const char* tolua_ret = (const char*)  self->GetProfessionName(type);
   tolua_pushstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetProfessionName'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetCountryName of class  CUI_ID_FRAME_RankList */
#ifndef TOLUA_DISABLE_tolua_compile_CUI_ID_FRAME_RankList_GetCountryName00
static int tolua_compile_CUI_ID_FRAME_RankList_GetCountryName00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CUI_ID_FRAME_RankList",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CUI_ID_FRAME_RankList* self = (CUI_ID_FRAME_RankList*)  tolua_tousertype(tolua_S,1,0);
  int nCountryId = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetCountryName'",NULL);
#endif
  {
   const char* tolua_ret = (const char*)  self->GetCountryName(nCountryId);
   tolua_pushstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetCountryName'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetMeName of class  CUI_ID_FRAME_RankList */
#ifndef TOLUA_DISABLE_tolua_compile_CUI_ID_FRAME_RankList_GetMeName00
static int tolua_compile_CUI_ID_FRAME_RankList_GetMeName00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CUI_ID_FRAME_RankList",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CUI_ID_FRAME_RankList* self = (CUI_ID_FRAME_RankList*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetMeName'",NULL);
#endif
  {
   const char* tolua_ret = (const char*)  self->GetMeName();
   tolua_pushstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetMeName'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetGuildName of class  CUI_ID_FRAME_RankList */
#ifndef TOLUA_DISABLE_tolua_compile_CUI_ID_FRAME_RankList_GetGuildName00
static int tolua_compile_CUI_ID_FRAME_RankList_GetGuildName00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CUI_ID_FRAME_RankList",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CUI_ID_FRAME_RankList* self = (CUI_ID_FRAME_RankList*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetGuildName'",NULL);
#endif
  {
   const char* tolua_ret = (const char*)  self->GetGuildName();
   tolua_pushstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetGuildName'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Log of class  CUI_ID_FRAME_RankList */
#ifndef TOLUA_DISABLE_tolua_compile_CUI_ID_FRAME_RankList_Log00
static int tolua_compile_CUI_ID_FRAME_RankList_Log00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CUI_ID_FRAME_RankList",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CUI_ID_FRAME_RankList* self = (CUI_ID_FRAME_RankList*)  tolua_tousertype(tolua_S,1,0);
  const std::string log = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Log'",NULL);
#endif
  {
   self->Log(log);
   tolua_pushcppstring(tolua_S,(const char*)log);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Log'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetCurrentPageIndex of class  CUI_ID_FRAME_RankList */
#ifndef TOLUA_DISABLE_tolua_compile_CUI_ID_FRAME_RankList_GetCurrentPageIndex00
static int tolua_compile_CUI_ID_FRAME_RankList_GetCurrentPageIndex00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CUI_ID_FRAME_RankList",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CUI_ID_FRAME_RankList* self = (CUI_ID_FRAME_RankList*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetCurrentPageIndex'",NULL);
#endif
  {
   int tolua_ret = (int)  self->GetCurrentPageIndex();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetCurrentPageIndex'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetShowNumPerPage of class  CUI_ID_FRAME_RankList */
#ifndef TOLUA_DISABLE_tolua_compile_CUI_ID_FRAME_RankList_GetShowNumPerPage00
static int tolua_compile_CUI_ID_FRAME_RankList_GetShowNumPerPage00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CUI_ID_FRAME_RankList",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CUI_ID_FRAME_RankList* self = (CUI_ID_FRAME_RankList*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetShowNumPerPage'",NULL);
#endif
  {
   int tolua_ret = (int)  self->GetShowNumPerPage();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetShowNumPerPage'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetExplain of class  CUI_ID_FRAME_RankList */
#ifndef TOLUA_DISABLE_tolua_compile_CUI_ID_FRAME_RankList_SetExplain00
static int tolua_compile_CUI_ID_FRAME_RankList_SetExplain00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CUI_ID_FRAME_RankList",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CUI_ID_FRAME_RankList* self = (CUI_ID_FRAME_RankList*)  tolua_tousertype(tolua_S,1,0);
  int nStringIndex = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetExplain'",NULL);
#endif
  {
   self->SetExplain(nStringIndex);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetExplain'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetInfomation of class  CUI_ID_FRAME_RankList */
#ifndef TOLUA_DISABLE_tolua_compile_CUI_ID_FRAME_RankList_SetInfomation00
static int tolua_compile_CUI_ID_FRAME_RankList_SetInfomation00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CUI_ID_FRAME_RankList",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CUI_ID_FRAME_RankList* self = (CUI_ID_FRAME_RankList*)  tolua_tousertype(tolua_S,1,0);
  const char* szType = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetInfomation'",NULL);
#endif
  {
   self->SetInfomation(szType);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetInfomation'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetTileText of class  CUI_ID_FRAME_RankList */
#ifndef TOLUA_DISABLE_tolua_compile_CUI_ID_FRAME_RankList_SetTileText00
static int tolua_compile_CUI_ID_FRAME_RankList_SetTileText00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CUI_ID_FRAME_RankList",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CUI_ID_FRAME_RankList* self = (CUI_ID_FRAME_RankList*)  tolua_tousertype(tolua_S,1,0);
  const char* szText = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetTileText'",NULL);
#endif
  {
   self->SetTileText(szText);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetTileText'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: Rank::GetRank */
#ifndef TOLUA_DISABLE_tolua_compile_Rank_GetRank00
static int tolua_compile_Rank_GetRank00(lua_State* tolua_S)
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
   CUI_ID_FRAME_RankList* tolua_ret = (CUI_ID_FRAME_RankList*)  Rank::GetRank();
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"CUI_ID_FRAME_RankList");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetRank'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* Open function */
TOLUA_API int tolua_compile_open (lua_State* tolua_S)
{
 tolua_open(tolua_S);
 tolua_reg_types(tolua_S);
 tolua_module(tolua_S,NULL,0);
 tolua_beginmodule(tolua_S,NULL);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"CUI_ID_FRAME_RankList","CUI_ID_FRAME_RankList","CUIBase",tolua_collect_CUI_ID_FRAME_RankList);
  #else
  tolua_cclass(tolua_S,"CUI_ID_FRAME_RankList","CUI_ID_FRAME_RankList","CUIBase",NULL);
  #endif
  tolua_beginmodule(tolua_S,"CUI_ID_FRAME_RankList");
   tolua_function(tolua_S,"new",tolua_compile_CUI_ID_FRAME_RankList_new00);
   tolua_function(tolua_S,"new_local",tolua_compile_CUI_ID_FRAME_RankList_new00_local);
   tolua_function(tolua_S,".call",tolua_compile_CUI_ID_FRAME_RankList_new00_local);
   tolua_function(tolua_S,"LoadFrame",tolua_compile_CUI_ID_FRAME_RankList_LoadFrame00);
   tolua_function(tolua_S,"UnLoadFrame",tolua_compile_CUI_ID_FRAME_RankList_UnLoadFrame00);
   tolua_function(tolua_S,"SetFrameVisible",tolua_compile_CUI_ID_FRAME_RankList_SetFrameVisible00);
   tolua_function(tolua_S,"SetRankSortFunc",tolua_compile_CUI_ID_FRAME_RankList_SetRankSortFunc00);
   tolua_function(tolua_S,"SetControlCheckBoxText",tolua_compile_CUI_ID_FRAME_RankList_SetControlCheckBoxText00);
   tolua_function(tolua_S,"SetControlText",tolua_compile_CUI_ID_FRAME_RankList_SetControlText00);
   tolua_function(tolua_S,"SetControlButtonText",tolua_compile_CUI_ID_FRAME_RankList_SetControlButtonText00);
   tolua_function(tolua_S,"AssociateList",tolua_compile_CUI_ID_FRAME_RankList_AssociateList00);
   tolua_function(tolua_S,"AssociateListImg",tolua_compile_CUI_ID_FRAME_RankList_AssociateListImg00);
   tolua_function(tolua_S,"AddListItem",tolua_compile_CUI_ID_FRAME_RankList_AddListItem00);
   tolua_function(tolua_S,"AddListImageItem",tolua_compile_CUI_ID_FRAME_RankList_AddListImageItem00);
   tolua_function(tolua_S,"AddListImageCharItem",tolua_compile_CUI_ID_FRAME_RankList_AddListImageCharItem00);
   tolua_function(tolua_S,"ClearList",tolua_compile_CUI_ID_FRAME_RankList_ClearList00);
   tolua_function(tolua_S,"ClearListImage",tolua_compile_CUI_ID_FRAME_RankList_ClearListImage00);
   tolua_function(tolua_S,"GetRankRowSize",tolua_compile_CUI_ID_FRAME_RankList_GetRankRowSize00);
   tolua_function(tolua_S,"GetRankContent",tolua_compile_CUI_ID_FRAME_RankList_GetRankContent00);
   tolua_function(tolua_S,"GetProfessionName",tolua_compile_CUI_ID_FRAME_RankList_GetProfessionName00);
   tolua_function(tolua_S,"GetCountryName",tolua_compile_CUI_ID_FRAME_RankList_GetCountryName00);
   tolua_function(tolua_S,"GetMeName",tolua_compile_CUI_ID_FRAME_RankList_GetMeName00);
   tolua_function(tolua_S,"GetGuildName",tolua_compile_CUI_ID_FRAME_RankList_GetGuildName00);
   tolua_function(tolua_S,"Log",tolua_compile_CUI_ID_FRAME_RankList_Log00);
   tolua_function(tolua_S,"GetCurrentPageIndex",tolua_compile_CUI_ID_FRAME_RankList_GetCurrentPageIndex00);
   tolua_function(tolua_S,"GetShowNumPerPage",tolua_compile_CUI_ID_FRAME_RankList_GetShowNumPerPage00);
   tolua_function(tolua_S,"SetExplain",tolua_compile_CUI_ID_FRAME_RankList_SetExplain00);
   tolua_function(tolua_S,"SetInfomation",tolua_compile_CUI_ID_FRAME_RankList_SetInfomation00);
   tolua_function(tolua_S,"SetTileText",tolua_compile_CUI_ID_FRAME_RankList_SetTileText00);
  tolua_endmodule(tolua_S);
  tolua_module(tolua_S,"Rank",0);
  tolua_beginmodule(tolua_S,"Rank");
   tolua_function(tolua_S,"GetRank",tolua_compile_Rank_GetRank00);
  tolua_endmodule(tolua_S);
 tolua_endmodule(tolua_S);
 return 1;
}


#if defined(LUA_VERSION_NUM) && LUA_VERSION_NUM >= 501
 TOLUA_API int luaopen_compile (lua_State* tolua_S) {
 return tolua_compile_open(tolua_S);
};
#endif

