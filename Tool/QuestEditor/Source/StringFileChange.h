#pragma once
#include "afxwin.h"


// StringFileChange dialog

class StringFileChange : public CDialog
{
	DECLARE_DYNAMIC(StringFileChange)

public:
	StringFileChange(CWnd* pParent = NULL);   // standard constructor
	virtual ~StringFileChange();

	bool LoadFromSlk( char* szFileName );

// Dialog Data
	enum { IDD = IDD_DIALOG_CHANGE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_editSlkFile;
	CEdit m_editXmlFile;
	afx_msg void OnBnClickedButton19();
	afx_msg void OnBnClickedButton18();
	afx_msg void OnBnClickedOk();
};
