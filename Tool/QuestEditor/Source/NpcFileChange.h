#pragma once
#include "afxwin.h"


// NpcFileChange dialog

class NpcFileChange : public CDialog
{
	DECLARE_DYNAMIC(NpcFileChange)

public:
	NpcFileChange(CWnd* pParent = NULL);   // standard constructor
	virtual ~NpcFileChange();

// Dialog Data
	enum { IDD = IDD_DIALOG_NPC };

	bool LoadFromSlk( char* szFileName );
	bool LoadNpcActionSlk( char* szFileName );
	bool LoadNpcFightSlk( char* szFileName );
	bool LoadNpcSaluteSlk(char* szFileName);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_editNpcSlk;
	CEdit m_editNpcAction;
	CEdit m_editNpcFight;
	CEdit m_editNpcXml;
	CEdit m_edotNpcSalute;
	afx_msg void OnBnClickedButtonSlk();
	afx_msg void OnBnClickedButtonAction();
	afx_msg void OnBnClickedButtonFight();
	afx_msg void OnBnClickedButtonSalute();//¾´Àñ¶¯×÷
	afx_msg void OnBnClickedButtonXml();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedButton22();
	afx_msg void OnEnChangeEdit13();
	afx_msg void OnEnChangeEdit14();
};
