/*******************************************************************************
*  Copyright ZNWL (C) 2007 - All Rights Reserved
*
* File: 	ToolZone.h
* Date: 	06/12/2007
* Desc:
*
*******************************************************************************/
#ifndef _UI_TOOLWND_ZONE_H__
#define _UI_TOOLWND_ZONE_H__
#include "afxwin.h"

class CToolZone;
////////////////////////////////////////////////////////////////////////////////
class CToolZoneDlg : public CDialog
{
	DECLARE_DYNAMIC(CToolZoneDlg)

public:
						CToolZoneDlg(CToolZoneDlg* pParent = NULL);   // standard constructor
	virtual				~CToolZoneDlg();

	// Dialog Data
	enum { IDD = IDD_DLG_ZONE };

	void				SetActive( bool isModify = false );
	
	void				SetSelectedZoneName(const char* pName);
	void				SetSaved(bool val) { m_saved = val; }
	bool				GetSavedFlag() const { return m_saved; }

	void				UpdateZoneInfo( sInt32 zoneId );
protected:
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CToolZONEDlg)
	virtual void		DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL		OnInitDialog();
	virtual void		OnOK(){};
	virtual void		OnCancel(){};
	//}}AFX_VIRTUAL
	
	//{{AFX_MSG(CToolZONEDlg)
	afx_msg void		OnClkListCtrl();

	CToolZone* GetToolZone();
	afx_msg void		OnKillfocusName();
	afx_msg void		OnKillfocusRadius();
	void				UpdateZoneList();
	afx_msg void		OnChkPickZone();
	afx_msg void		OnChkSetZone();

	afx_msg void		OnBtnSetZone();
	afx_msg void		OnBtnAddZone();
	afx_msg void		OnBtnDelZone();

	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
protected:
	bool				CreateZone( const char* zoneName, const char* musicPath, const RECT* pRect);
	void				UpdateWorldZone();
	void				UpdateSelect();

protected:
	sInt32				m_curSel;
	CListBox			m_listZone;
	CEdit				m_zoneName;
	CEdit				m_brushRadius;
	CEdit				m_selectedZone;
	CEdit				m_rectLeft;
	CEdit				m_rectTop;
	CEdit				m_rectRight;
	CEdit				m_rectButtom;
	CXTBrowseEdit		m_editMusic;
	bool				m_saved;
public:
	CButton m_ZoneSave;
	afx_msg void OnBnClickedBtnZoneSave();
};

#endif	// _UI_TOOLWND_ZONE_H__