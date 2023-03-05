/*******************************************************************************
*  Copyright ZNWL (C) 2007 - All Rights Reserved
*
* File: 	ToolEnvironment.h
* Date: 	06/12/2007
* Desc:
*
*******************************************************************************/
#ifndef _UI_TOOLWND_TOOLENVIRONMENT_H__
#define _UI_TOOLWND_TOOLENVIRONMENT_H__


////////////////////////////////////////////////////////////////////////////////
class CToolEnvDlg : public CDialog
{
	DECLARE_DYNAMIC(CToolEnvDlg)

public:
						CToolEnvDlg(CToolEnvDlg* pParent = NULL);   // standard constructor
	virtual				~CToolEnvDlg();

	// Dialog Data
	enum { IDD = IDD_DLG_ENV };

	void				SetActive( bool isModify = false );
	
	void				SetSelectedZoneName(const char* pName);

	void				UpdateZoneInfo( sInt32 zoneId );
protected:
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CToolEnvDlg)
	virtual void		DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL		OnInitDialog();
	virtual void		OnOK(){};
	virtual void		OnCancel(){};
	//}}AFX_VIRTUAL
	
	//{{AFX_MSG(CToolEnvDlg)
	afx_msg void		OnClkListCtrl();

	CToolEnv*			GetToolZone();
	afx_msg void		OnKillfocusName();
	afx_msg void		OnKillfocusRadius();
	void				UpdateZoneList();
	afx_msg void		OnLightChange();
	afx_msg void		OnFogChange();
	afx_msg void		OnChkPickZone();
	afx_msg void		OnChkSetZone();

	afx_msg void		OnBtnSetZone();
	afx_msg void		OnBtnAddZone();
	afx_msg void		OnBtnDelZone();

	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
protected:
	bool				CreateZone( const char* zoneName, sInt32 lightId, sInt32 fogId );
	void				UpdateWorldZone();
	void				UpdateLightList();
	void				UpdateFogList();
	void				UpdateSelect();

	void				SaveEnv();
protected:
	sInt32				m_curSel;
	CListBox			m_listEnv;
	CEdit				m_envName;
	CEdit				m_brushRadius;
	CEdit				m_selectedEnv;
	CComboBox			m_listLight;
	CComboBox			m_listFog;
};

#endif	// _UI_TOOLWND_TOOLENVIRONMENT_H__