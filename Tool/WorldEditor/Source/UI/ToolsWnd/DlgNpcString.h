#pragma once
#include "afxcmn.h"
#include "..\\..\\Edit\NpcString.h"

// CDlgNpcString dialog

class CDlgNpcString : public CDialog
{
	DECLARE_DYNAMIC(CDlgNpcString)

public:
	CDlgNpcString(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgNpcString();

// Dialog Data
	enum { IDD = IDD_NPCSTRING };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedLoadstring();
	CTreeCtrl m_treeCtrl;

public:
	bool InitTreeCtrlData();
	void SetStringProtery(CNpcString::npcTalk &cNpcTalk);
	bool GetStringProtery(CNpcString::npcTalk &cNpcTalk);



	afx_msg void OnTvnSelchangedTreestringid(NMHDR *pNMHDR, LRESULT *pResult);
	int m_StringID;
	CString m_strTalk;
	afx_msg void OnBnClickedStringadd();
	afx_msg void OnBnClickedStringdel();
	afx_msg void OnBnClickedStringsave();

	afx_msg void OnClose();
	afx_msg void OnCancel();
	afx_msg LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
};
