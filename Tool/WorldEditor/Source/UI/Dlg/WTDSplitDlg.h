/*******************************************************************************
* Copyright ShenWang 2008 - All Rights Reserved
* 
* File: 	WTDSplitDlg.h
* Create: 	11/18/08
* Desc:		
* Author:	Yuan Ding
*
* Modify:
* Modify by:
*******************************************************************************/

#pragma once


// CWTDSplitDlg dialog

class CWTDSplitDlg : public CDialog
{
	DECLARE_DYNAMIC(CWTDSplitDlg)

public:
	CWTDSplitDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CWTDSplitDlg(){;}

// Dialog Data
	enum { IDD = IDD_DLG_SPLIT_WTD };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL		OnInitDialog();
	virtual void		OnOK();

	DECLARE_MESSAGE_MAP()

	CXTBrowseEdit		m_editSourceFileName;
	CEdit				m_editUpLeft;
	bool				m_isUpDown;
	char				m_SourcefileName[MAX_PATH*2];
	int					m_UpLeft;

public:
	afx_msg void OnBnClickedRadioLeftright();
	afx_msg void OnBnClickedRadioUpdown();
};
