// MainFrm.h : CMainFrame ��Ľӿ�
//


#pragma once

class LoginInfo;
class CMainFrame : public CFrameWnd
{
	
protected: // �������л�����
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// ����
public:

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

public:  // �ؼ���Ƕ���Ա
	CStatusBar  m_wndStatusBar;
	CToolBar    m_wndToolBar;
	LoginInfo	*m_pLoginInfo;

// ���ɵ���Ϣӳ�亯��
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
    afx_msg void OnClose();

	DECLARE_MESSAGE_MAP()
public:
    virtual BOOL DestroyWindow();
public:
    afx_msg void OnAppLog();
public:
    afx_msg void OnAppOption();
	afx_msg void OnAppLogin();
    afx_msg void OnAppGMOption();
    afx_msg void OnPlatform();
	afx_msg void OnShowAddFrm();
};
extern CMainFrame* theMainFrame;

