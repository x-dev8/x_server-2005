/*******************************************************************************
* Copyright ShenWang 2008 - All Rights Reserved
* 
* File: 	WTDMergeDlg.h
* Create: 	11/18/08
* Desc:		
* Author:	Yuan Ding
*
* Modify:
* Modify by:
*******************************************************************************/

#pragma once


// CWTDMergeDlg dialog

class CWTDMergeDlg : public CDialog
{
	DECLARE_DYNAMIC(CWTDMergeDlg)

public:
	CWTDMergeDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CWTDMergeDlg(){;}

// Dialog Data
	enum { IDD = IDD_DLG_MERGE_WTD };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL		OnInitDialog();
	virtual void		OnOK();

	DECLARE_MESSAGE_MAP()

	CXTBrowseEdit		m_editSourceFileName;
	CXTBrowseEdit		m_editUpLeft;
	bool				m_isUpDown;
	char				m_SourcefileName[MAX_PATH*2];
	char				m_UpLeft[MAX_PATH*2];

public:
	afx_msg void OnBnClickedRadioLeftright();
	afx_msg void OnBnClickedRadioUpdown();
};
