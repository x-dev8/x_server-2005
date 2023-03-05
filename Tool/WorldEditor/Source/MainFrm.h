// MainFrm.h : interface of the CMainFrame class
//
#pragma once
#include "DockPaneWnd.h"
////////////////////////////////////////////////////////////////////////////////

class CWorldExplorerView;
////////////////////////////////////////////////////////////////////////////////
class CMainFrame : public CXTPFrameWnd
{
	
protected: // create from serialization only
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

public:
	virtual BOOL			PreCreateWindow(CREATESTRUCT& cs);

// Implementation
public:
	virtual					~CMainFrame();
#ifdef _DEBUG
	virtual void			AssertValid() const;
	virtual void			Dump(CDumpContext& dc) const;
#endif
	void					UpdateProgress( int pos );
	void					SetPromptText( LPCTSTR szText, DWORD dwTimeAfter = 0, LPCTSTR szNextText = NULL);
	void					SetMousePosText( sInt32 posX, sInt32 posY, const Vector& rayPt, const Vector& rayDir );
	void					SetWorldPosText( flt32 posX, flt32 posY, flt32 posZ,flt32 angle );
	void					SetLoopCountText( sInt32 countA, sInt32 countB );
protected:
	virtual BOOL			OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);

protected:
	CWnd*					CreateTerrainWnd();
	CWnd*					CreateLayerWnd();
	
// Generated message map functions
protected:
	afx_msg int				OnCreate( LPCREATESTRUCT lpCreateStruct );
	afx_msg void			OnClose();
	afx_msg void			OnCustomize();
	afx_msg int				OnCreateControl( LPCREATECONTROLSTRUCT lpCreateControl );
	afx_msg LRESULT			OnDockingPaneNotify( WPARAM wParam, LPARAM lParam );
	afx_msg void			OnActivateApp( BOOL bActive, DWORD dwThreadID );

	DECLARE_MESSAGE_MAP()

protected:  // control bar embedded members
	CXTSplitterWnd			m_wndSpliter;
	CXTPStatusBar			m_wndStatusBar;
	CXTPDockingPaneManager	m_paneManager;
	CXTPPropertyGrid		m_wndPropertyGrid;
	CProgressCtrl			m_wndProgCtrl;
	CWnd*					m_wndWorldExplorerView;
};


