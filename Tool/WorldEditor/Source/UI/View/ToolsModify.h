/*******************************************************************************
*  Copyright ZNWL (C) 2007 - All Rights Reserved
*
* File: 	ToolsModify.h
* Date: 	05/29/2007
* Desc:
*
*******************************************************************************/
#ifndef _UI_VIEW_TOOLSMODIFY_H__
#define _UI_VIEW_TOOLSMODIFY_H__

////////////////////////////////////////////////////////////////////////////////
class CToolsModify : public CWnd
{
public:
					CToolsModify();
	DECLARE_DYNCREATE(CToolsModify)
	virtual			~CToolsModify();

	virtual void	OnInitialUpdate();

	void			SetActive();

	// Generated message map functions
protected:
	//{{AFX_MSG(CWorldExplorerView)
	afx_msg void	OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL	OnEraseBkgnd(CDC* pDC);
	afx_msg void	OnSetFocus(CWnd* pOldWnd);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
protected:
	CXTPToolBar		m_wndToolBar;

};

#endif	// _UI_VIEW_TOOLSMODIFY_H__