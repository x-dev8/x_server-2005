#pragma once
#include "afxwin.h"


// LightMapSettingDlg dialog

class LightMapSettingDlg : public CDialog
{
	DECLARE_DYNAMIC(LightMapSettingDlg)

public:
	LightMapSettingDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~LightMapSettingDlg();
	short GetShadowColor();

// Dialog Data
	enum { IDD = IDD_LIGHTMAP };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_shadowValue;
	short m_sShadowColor;

	
	afx_msg void OnBnClickedOk();
};
