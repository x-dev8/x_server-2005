// MainFrm.h : interface of the CMainFrame class
//

#pragma once



class CMainFrame : public CFrameWnd
{
	
protected: // create from serialization only
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// Attributes
public:

// Operations
public:

// Overrides
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// Implementation
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members
	CStatusBar  m_wndStatusBar;
	CToolBar    m_wndToolBar;


	bool m_bWindowsTop;

// Generated message map functions
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);



	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnFileBatch();
	afx_msg void OnFileOpen();
	afx_msg void OnFileSave();
	afx_msg void OnFileSaveAs();
	afx_msg void OnAppExit();
	afx_msg void OnFileTop();
	afx_msg void OnFileAdd();
	afx_msg void OnFileDelete();
	afx_msg void OnFileDeletequest();
	afx_msg void OnFileFind();
	afx_msg void OnFileNext();
	afx_msg void OnFileString();
	afx_msg void OnFileNpc();
	afx_msg void OnFileEdit();
	afx_msg void OnFileStringEdit();
	afx_msg void OnFilePosition();
	afx_msg void OnDropDelete();
};

extern CMainFrame *theMainFrame;