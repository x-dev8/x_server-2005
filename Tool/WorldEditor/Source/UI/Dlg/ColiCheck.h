#pragma once
#include "afxwin.h"


// CColiCheck dialog

class CColiCheck : public CDialog
{
	DECLARE_DYNAMIC(CColiCheck)

public:
	CColiCheck(CWnd* pParent = NULL);   // standard constructor
	virtual ~CColiCheck();

// Dialog Data
	enum { IDD = IDD_DIALOG_ColiCheckResult };


	void DoColiCheck();
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

	CEdit m_ColliResult;
};
