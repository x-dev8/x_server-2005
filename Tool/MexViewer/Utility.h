#pragma once

#include "ModelObj.h"

class AnimRGalleryClientData : public wxClientData
{
public:
	AnimRGalleryClientData(int index) : mAnimIndex(index) {}

	int GetAnimationIndex() const { return mAnimIndex; }

protected:
	int mAnimIndex;
};

/*
 * 在控制台输出Log信息
 */
void Utility_WriteDebugInfoToConsole(const char *fmt, ...);

/*
 * Enable/Disable Property控件
 */
void Utility_EnableProperty(wxPropertyGrid *pg, const wxString &attr, bool enable);

/*
 * 按label设置Property控件为Spin
 */
void Utility_SetPropertyToSpinCtrl(wxPropertyGrid *pg, const wxString &attr,
								   wxVariant min, wxVariant max, wxVariant step, bool enable);

/*
 * 按指针设置Property控件为Spin
 */
void Utility_SetPropertyToSpinCtrl(wxPGProperty *attr, wxVariant min, wxVariant max, wxVariant step, bool enable);

/*
 * 按label设置Property控件为CheckBox
 */
void Utility_SetPropertyToBoolWithCheckBox(wxPropertyGrid *pg, const wxString &attr, bool enable);

/*
 * 按label设置Property控件为带Alpha的Color Picker
 */
void Utility_SetPropertyToColorPickerWithAlpha(wxPropertyGrid *pg, const wxString &attr, bool enable);

/*
 * 释放模型数据的辅助函数
 */
void Utility_SafeDeleteModel(ModelObj *obj);

/*
 * 字符串比较辅助函数
 */
bool Utility_Strnicmp(const char *str1, const char *str2);

/*
 * 添加HitPoint
 */
void Utility_AddHitPoint(MexCfgSequence *cfgSequence, int frameID);

/*
 * 设置HitPoint
 */
void Utility_SetHitPoint(MexCfgSequence *cfgSequence, int frameID);

/*
 * 获取HitPoint
 */
int Utility_GetHitPoint(MexCfgSequence *cfgSequence);

/*
 * Author:	2012-8-22 wangshuai
 * Desc: 	保存Ani
 */
void Utility_SaveAni(ModelObj *obj);

/*
 * Author:	2012-8-22 wangshuai
 * Desc: 	wxTreeCtrl之HitTest处理
 */
void Utility_TreeCtrlHitTest(wxTreeCtrl *tree, wxPoint &pos, wxTreeItemId &hitItem);

/*
 * Author:	2012-8-23 wangshuai
 * Desc: 	ANSI转Unicode
 */
std::wstring Utility_ANSIToUnicode(const char *ansi);