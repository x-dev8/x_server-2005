#pragma once


// CDlgSelectPath dialog

class CDlgSelectPath : public CDialog
{
	DECLARE_DYNAMIC(CDlgSelectPath)

	CString selPath;
public:
	CDlgSelectPath(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgSelectPath();

// Dialog Data
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult);
};
