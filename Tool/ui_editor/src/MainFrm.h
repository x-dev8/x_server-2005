// MainFrm.h : CMainFrame 类的接口
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
	
protected: // 仅从序列化创建
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// 属性
public:

private:
	CCoolDialogBar m_wndPropertyBar;
	CCoolDialogBar m_wndObjectBar;

// 操作
public:

// 重写
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// 实现
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // 控件条嵌入成员
	CStatusBarXP  m_wndStatusBar;
	CToolBarXP    m_wndToolBar;

// 生成的消息映射函数
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	DECLARE_MESSAGE_MAP()
	DECLARE_MENUXP()
public:
	afx_msg void OnViewProperty();
	afx_msg void OnViewObject();
	virtual BOOL LoadFrame(UINT nIDResource, DWORD dwDefaultStyle = WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE, CWnd* pParentWnd = NULL, CCreateContext* pContext = NULL);
};


