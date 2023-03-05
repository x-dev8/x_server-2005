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
 * �ڿ���̨���Log��Ϣ
 */
void Utility_WriteDebugInfoToConsole(const char *fmt, ...);

/*
 * Enable/Disable Property�ؼ�
 */
void Utility_EnableProperty(wxPropertyGrid *pg, const wxString &attr, bool enable);

/*
 * ��label����Property�ؼ�ΪSpin
 */
void Utility_SetPropertyToSpinCtrl(wxPropertyGrid *pg, const wxString &attr,
								   wxVariant min, wxVariant max, wxVariant step, bool enable);

/*
 * ��ָ������Property�ؼ�ΪSpin
 */
void Utility_SetPropertyToSpinCtrl(wxPGProperty *attr, wxVariant min, wxVariant max, wxVariant step, bool enable);

/*
 * ��label����Property�ؼ�ΪCheckBox
 */
void Utility_SetPropertyToBoolWithCheckBox(wxPropertyGrid *pg, const wxString &attr, bool enable);

/*
 * ��label����Property�ؼ�Ϊ��Alpha��Color Picker
 */
void Utility_SetPropertyToColorPickerWithAlpha(wxPropertyGrid *pg, const wxString &attr, bool enable);

/*
 * �ͷ�ģ�����ݵĸ�������
 */
void Utility_SafeDeleteModel(ModelObj *obj);

/*
 * �ַ����Ƚϸ�������
 */
bool Utility_Strnicmp(const char *str1, const char *str2);

/*
 * ���HitPoint
 */
void Utility_AddHitPoint(MexCfgSequence *cfgSequence, int frameID);

/*
 * ����HitPoint
 */
void Utility_SetHitPoint(MexCfgSequence *cfgSequence, int frameID);

/*
 * ��ȡHitPoint
 */
int Utility_GetHitPoint(MexCfgSequence *cfgSequence);

/*
 * Author:	2012-8-22 wangshuai
 * Desc: 	����Ani
 */
void Utility_SaveAni(ModelObj *obj);

/*
 * Author:	2012-8-22 wangshuai
 * Desc: 	wxTreeCtrl֮HitTest����
 */
void Utility_TreeCtrlHitTest(wxTreeCtrl *tree, wxPoint &pos, wxTreeItemId &hitItem);

/*
 * Author:	2012-8-23 wangshuai
 * Desc: 	ANSIתUnicode
 */
std::wstring Utility_ANSIToUnicode(const char *ansi);