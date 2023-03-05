/*******************************************************************************
*  Copyright ZWS (C) 2007 - All Rights Reserved
*
* File: 	SnapMiniMapDlg.h
* Date: 	12/04/2007
* Desc:
*
*******************************************************************************/
#ifndef _UI_DLG_SNAPMINIMAPDLG_H__
#define _UI_DLG_SNAPMINIMAPDLG_H__

////////////////////////////////////////////////////////////////////////////////
class CWorldTile;
class CSnapMinimapDlg : public CDialog
{
	friend class		CToolWorld;
	DECLARE_DYNAMIC(CSnapMinimapDlg)
public:
	enum { IDD = IDD_DLG_SNAPMINIMAP };
						CSnapMinimapDlg(CWnd* pParent = NULL);   // standard constructor
	virtual				~CSnapMinimapDlg();

protected:
	virtual void		DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL		OnInitDialog();
	virtual void		OnOK();

	DECLARE_MESSAGE_MAP()

protected:
	CString				m_tileName;
	CWorldTile*			m_tile;
	CXTBrowseEdit		m_editFileName;
	char				m_fileName[MAX_PATH*2];
};





#endif	// _UI_DLG_SNAPMINIMAPDLG_H__