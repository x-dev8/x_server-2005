// UIEditor.h : UIEditor 应用程序的主头文件
//
#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "../res/resource.h"       // 主符号
#include "MeUi\ControlData.h"
//#include "Control.h"
#include "BaseControl.h"

enum E_AppState
{
	State_Dialog
	,State_Control
	,State_Pic
};

// CUIEditorApp:
// 有关此类的实现，请参阅 UIEditor.cpp
//

class CUIEditorApp : public CWinApp
{
public:
	E_ControlType	m_enOperateType;

private:
	bool	m_bUpdateView;

private:
	void	RefeashOperatorType( const E_ControlType enType, CCmdUI* pCmdUI );

// 重写
public:
	virtual BOOL InitInstance();

// 实现
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
	afx_msg void OnEditAddButton();
	afx_msg void OnUpdateEditAddButton(CCmdUI *pCmdUI);
	afx_msg void OnEditAddCheckbox();
	afx_msg void OnUpdateEditAddCheckbox(CCmdUI *pCmdUI);
	afx_msg void OnEditAddEdit();
	afx_msg void OnUpdateEditAddEdit(CCmdUI *pCmdUI);
	afx_msg void OnEditAddText();
	afx_msg void OnUpdateEditAddText(CCmdUI *pCmdUI);
	afx_msg void OnEditAddList();
	afx_msg void OnUpdateEditAddList(CCmdUI *pCmdUI);
	afx_msg void OnEditAddListimg();
	afx_msg void OnUpdateEditAddListimg(CCmdUI *pCmdUI);

	afx_msg void OnEditAddTree();
	afx_msg void OnUpdateEditAddTree(CCmdUI *pCmdUI);
public:
	CUIEditorApp();
	virtual BOOL OnIdle(LONG lCount);
	afx_msg void OnEditAddPoint();
	afx_msg void OnUpdateEditAddPoint(CCmdUI *pCmdUI);
	afx_msg void OnEditAddScrollbar();
	afx_msg void OnUpdateEditAddScrollbar(CCmdUI *pCmdUI);
	afx_msg void OnEditAddScrollbarEx();
	afx_msg void OnUpdateEditAddScrollbarEx(CCmdUI *pCmdUI);
	afx_msg void OnEditAddComboBox();
	afx_msg void OnUpdateEditAddComboBox(CCmdUI *pCmdUI);
	afx_msg void OnEditAddPicture();
	afx_msg void OnUpdateEditAddPicture(CCmdUI *pCmdUI);
	afx_msg void OnEditAddProgress();
	afx_msg void OnUpdateEditAddProgress(CCmdUI *pCmdUI);
	virtual int ExitInstance();
	afx_msg void OnEditCopy();
	afx_msg void OnEditPaste();
	afx_msg void OnEditCut();
	afx_msg void OnEditTestdlg();
	afx_msg void OnEditAddTab();
	afx_msg void OnUpdateEditAddTab(CCmdUI *pCmdUI);
	afx_msg void OnEditAddListex();
	afx_msg void OnUpdateEditAddListex(CCmdUI *pCmdUI);
};

extern CUIEditorApp theApp;
extern E_AppState g_enState;
extern char g_stPath[MAX_PATH];
extern char	g_stFileName[MAX_PATH];

