// NewDlgDlg.h : header file
//

#pragma once
#include "NewBackDlg.h"
#define DRAGGING	0x01	// dragging flag
// CNewDlgDlg dialog
class CNewDlgDlg : public CDialog
{
// Construction
public:
	CNewDlgDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_NEWDLG_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

	CNewBackDlg  *pChildWnd;
	Image *image;

	CRect  rcWindowRaw;

	
	void LoadXML(CString filename);
	DWORD	m_dwFlags;		// flags
	POINT	m_pntMouse;		// Mouse position for dragging
	TiXmlDocument	m_TiXmlDoc;	//保存xml用于写入文件
	TiXmlElement*	m_TiElemRoot;	//保存root节点 这个不用更改 


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMove(int x, int y);
};
