#include "StdAfx.h"
#include "Utility.h"

void Utility_WriteDebugInfoToConsole(const char *fmt, ...)
{
#ifdef _DEBUG
	static char buffer[512] = {0};

	va_list args;
	va_start(args, fmt);
		vsprintf_s(buffer, 512 - 1, fmt, args);
	va_end(args);

	OutputDebugStringA(buffer);
#endif
}

void Utility_EnableProperty(wxPropertyGrid *pg, const wxString &attr, bool enable)
{
	pg->EnableProperty(attr, enable);
}

void Utility_SetPropertyToSpinCtrl(wxPropertyGrid *pg, const wxString &attr,
								   wxVariant min, wxVariant max, wxVariant step, bool enable)
{
	if (pg == NULL)
		return;

	Utility_EnableProperty(pg, attr, enable);

	pg->SetPropertyEditor(attr, wxPGEditor_SpinCtrl);
	pg->SetPropertyAttribute(attr, wxPG_ATTR_MIN, min);
	pg->SetPropertyAttribute(attr, wxPG_ATTR_MAX, max);
	pg->SetPropertyAttribute(attr, wxPG_ATTR_SPINCTRL_STEP, step);
}

void Utility_SetPropertyToSpinCtrl(wxPGProperty *attr, wxVariant min, wxVariant max, wxVariant step, bool enable)
{
	if (attr == NULL)
		return;

	attr->Enable(enable);

	attr->SetEditor(wxPGEditor_SpinCtrl);
	attr->SetAttribute(wxPG_ATTR_MIN, min);
	attr->SetAttribute(wxPG_ATTR_MAX, max);
	attr->SetAttribute(wxPG_ATTR_SPINCTRL_STEP, step);
}

void Utility_SetPropertyToBoolWithCheckBox(wxPropertyGrid *pg, const wxString &attr, bool enable)
{
	Utility_EnableProperty(pg, attr, enable);

	pg->SetPropertyAttribute(attr, wxPG_BOOL_USE_CHECKBOX, true);
}

void Utility_SetPropertyToColorPickerWithAlpha(wxPropertyGrid *pg, const wxString &attr, bool enable)
{
	Utility_EnableProperty(pg, attr, enable);

	pg->SetPropertyAttribute(attr, wxPG_COLOUR_HAS_ALPHA, true);
}

void Utility_SafeDeleteModel(ModelObj *obj)
{
	if (obj == NULL)
		return;

	MeDelete obj;
	obj = NULL;
	
	GetMexResMgr()->RemoveUnusedModelWhenChangeMap();
}

bool Utility_Strnicmp(const char *str1, const char *str2)
{
	return strnicmp(str1, str2, strlen(str2)) == 0;
}

void Utility_AddHitPoint(MexCfgSequence *cfgSequence, int frameID)
{
	cfgSequence->m_hitpoints.m_vectorHitPoint.clear();
	MexCfgHitPoint hitPt;
	hitPt.m_npFrameId.SetNumber(frameID);
	cfgSequence->m_hitpoints.m_vectorHitPoint.push_back(&hitPt);
}

void Utility_SetHitPoint(MexCfgSequence *cfgSequence, int frameID)
{
	if (cfgSequence->m_hitpoints.m_vectorHitPoint.size() > 0)
		cfgSequence->m_hitpoints.m_vectorHitPoint[0]->m_npFrameId.SetNumber(frameID);
	else
		Utility_AddHitPoint(cfgSequence, frameID);
}

int Utility_GetHitPoint(MexCfgSequence *cfgSequence)
{
	if (cfgSequence->m_hitpoints.m_vectorHitPoint.size() > 0)
		return cfgSequence->m_hitpoints.m_vectorHitPoint[0]->m_npFrameId.GetNumber();
	else
		return 0;
}

void Utility_SaveAni(ModelObj *obj)
{
	wxFileName fn(obj->GetFilePath());
	fn.SetExt("ani");
	obj->model->GetMexCfg()->SaveToFile(fn.GetFullPath());
}

void Utility_TreeCtrlHitTest(wxTreeCtrl *tree, wxPoint &pos, wxTreeItemId &hitItem)
{
	pos = tree->ScreenToClient(wxGetMousePosition());
	hitItem = tree->HitTest(pos);
}

std::wstring Utility_ANSIToUnicode(const char *ansi)
{
	int len = ::MultiByteToWideChar(CP_ACP, 0, ansi, -1, NULL, 0);
	wchar_t *unicode_array = new wchar_t[len];
	memset(unicode_array, 0, len);
	MultiByteToWideChar(CP_ACP, 0, ansi, -1, unicode_array, len);

	wstring unicode(unicode_array);
	delete [] unicode_array;
	unicode_array = NULL;

	return unicode;
}