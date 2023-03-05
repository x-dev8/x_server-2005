// ACDSeeTabView.h : header file
//
// This file is a part of the XTREME TOOLKIT PRO MFC class library.
// ?998-2005 Codejock Software, All Rights Reserved.
//
// THIS SOURCE FILE IS THE PROPERTY OF CODEJOCK SOFTWARE AND IS NOT TO BE
// RE-DISTRIBUTED BY ANY MEANS WHATSOEVER WITHOUT THE EXPRESSED WRITTEN
// CONSENT OF CODEJOCK SOFTWARE.
//
// THIS SOURCE CODE CAN ONLY BE USED UNDER THE TERMS AND CONDITIONS OUTLINED
// IN THE XTREME TOOLKIT PRO LICENSE AGREEMENT. CODEJOCK SOFTWARE GRANTS TO
// YOU (ONE SOFTWARE DEVELOPER) THE LIMITED RIGHT TO USE THIS SOFTWARE ON A
// SINGLE COMPUTER.
//
// CONTACT INFORMATION:
// support@codejock.com
// http://www.codejock.com
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_ACDSEETABVIEW_H__F50A9C2A_1994_410F_A9A7_9E6011408814__INCLUDED_)
#define AFX_ACDSEETABVIEW_H__F50A9C2A_1994_410F_A9A7_9E6011408814__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

enum emWndType
{
	emWT_Create,
	emWT_Scene,
	emWT_Flight
};

/////////////////////////////////////////////////////////////////////////////
// CToolsTabView view
class CToolsTabView : public CView
{
protected:
					CToolsTabView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CToolsTabView)

	void			SetWnd( emWndType wndType );

	CToolsScene&	GetToolSceneWnd() { return m_wndToolScene; };

	void			Reset();
protected:
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CACDSeeTabView)
	virtual void	OnInitialUpdate();

	virtual void	OnDraw(CDC* pDC);      // overridden to draw this view
	virtual BOOL	PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual			~CToolsTabView();
#ifdef _DEBUG
	virtual void	AssertValid() const;
	virtual void	Dump(CDumpContext& dc) const;
#endif

protected:
	//{{AFX_MSG(CACDSeeTabView)
	afx_msg void	OnSize(UINT nType, int cx, int cy);
	afx_msg void	OnCommandCreate();
	afx_msg void	OnCommandScene();

	afx_msg void	OnUpdateCommandCreate(CCmdUI* pCmdUI);
	afx_msg void	OnUpdateCommandScene(CCmdUI* pCmdUI);

	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

protected:
	CXTPToolBar		m_wndToolBar;
	emWndType		m_curWndType;

	CToolsCreate	m_wndToolCreate;
	CToolsModify	m_wndToolModify;
	CToolsScene		m_wndToolScene;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ACDSEETABVIEW_H__F50A9C2A_1994_410F_A9A7_9E6011408814__INCLUDED_)
