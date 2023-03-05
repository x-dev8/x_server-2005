#pragma once


// CHelpDialog dialog

class CHelpDialog : public CDialog
{
	DECLARE_DYNAMIC(CHelpDialog)

public:
	CHelpDialog(CWnd* pParent = NULL);   // standard constructor
	virtual ~CHelpDialog();

// Dialog Data
	enum { IDD = IDD_DIALOG_HELP };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};
