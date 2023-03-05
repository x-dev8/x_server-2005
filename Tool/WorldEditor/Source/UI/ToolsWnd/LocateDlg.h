#pragma once


// CLocateDlg dialog

class CLocateDlg : public CDialog
{
	DECLARE_DYNAMIC(CLocateDlg)

public:
	UINT m_pointX;
	UINT m_pointY;

public:
	CLocateDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CLocateDlg();

// Dialog Data
	enum { IDD = IDD_DLG_LOCATE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	
	
	virtual BOOL OnInitDialog();
};
