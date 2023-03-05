#pragma once


// BugReporter dialog

class DumpInfo;

class CBugReporter : public CDialog
{
	DECLARE_DYNAMIC(CBugReporter)

public:
	CBugReporter(CWnd* pParent = NULL);   // standard constructor
	virtual ~CBugReporter();

// Dialog Data
	enum { IDD = IDD_BUGREPORTER };
public:
	CString m_strText;
	HICON     m_hIcon;

protected:
	void CheckOptions( DumpInfo& dumpinfo );

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnClose();
};
