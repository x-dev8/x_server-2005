/*******************************************************************************
*  Copyright ZWS (C) 2007 - All Rights Reserved
*
* File: 	ServerMapDlg.h
* Date: 	12/05/2007
* Desc:
*
*******************************************************************************/
#ifndef _UI_DLG_SERVERMAPDLG_H__
#define _UI_DLG_SERVERMAPDLG_H__


////////////////////////////////////////////////////////////////////////////////
class CServerMapDlg : public CDialog
{
	friend class		CWorldEditDoc;
	DECLARE_DYNAMIC(CServerMapDlg)
public:
	enum { IDD = IDD_DLG_SERVERMAP };
						CServerMapDlg(CWnd* pParent = NULL);   // standard constructor
	virtual				~CServerMapDlg();
						
protected:
	virtual void		DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL		OnInitDialog();
	virtual void		OnOK();
	
	DECLARE_MESSAGE_MAP()
	
protected:
	CXTBrowseEdit		m_editClientFileName;
	CXTBrowseEdit		m_editServerFileName;
	TCHAR				m_clientFileName[MAX_PATH];
	char				m_serverFileName[MAX_PATH*2];
};




#endif	// _UI_DLG_SERVERMAPDLG_H__