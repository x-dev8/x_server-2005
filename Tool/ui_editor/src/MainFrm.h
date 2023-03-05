// MainFrm.h : CMainFrame ��Ľӿ�
//
#pragma once
#include "CoolDialogBar.h"
#include "PropertyDlg.h"
#include "UIObjectdlg.h"

#include "MenuXp/MenuXP.h"
#include "MenuXp/ToolBarXP.h"
#include "MenuXp/StatusBarXP.h"

class CMainFrame : public CFrameWnd
{
	
protected: // �������л�����
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// ����
public:

private:
	CCoolDialogBar m_wndPropertyBar;
	CCoolDialogBar m_wndObjectBar;

// ����
public:

// ��д
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// ʵ��
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // �ؼ���Ƕ���Ա
	CStatusBarXP  m_wndStatusBar;
	CToolBarXP    m_wndToolBar;

// ���ɵ���Ϣӳ�亯��
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	DECLARE_MESSAGE_MAP()
	DECLARE_MENUXP()
public:
	afx_msg void OnViewProperty();
	afx_msg void OnViewObject();
	virtual BOOL LoadFrame(UINT nIDResource, DWORD dwDefaultStyle = WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE, CWnd* pParentWnd = NULL, CCreateContext* pContext = NULL);
};


