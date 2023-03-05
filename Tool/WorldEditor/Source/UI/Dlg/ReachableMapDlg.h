/*******************************************************************************
* Copyright ShenWang 2008 - All Rights Reserved
* 
* File: 	ReachableMapDlg.h
* Create: 	11/01/08
* Desc:		
* Author:	Yuan Ding
*
* Modify:
* Modify by:
*******************************************************************************/

#ifndef __REACHABLE_MAP_DLG_H__
#define __REACHABLE_MAP_DLG_H__
#include "afxwin.h"

////////////////////////////////////////////////////////////////////////////////
class CReachableMapDlg : public CDialog
{
	friend class		CToolWorld;
	DECLARE_DYNAMIC(CReachableMapDlg)
public:
	enum { IDD = IDD_REACHABLEMAP };
						CReachableMapDlg(CWnd* pParent = NULL);   // standard constructor
	virtual				~CReachableMapDlg();

protected:
	virtual void		DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL		OnInitDialog();
	virtual void		OnOK();

	DECLARE_MESSAGE_MAP()

protected:
	CString				m_tileName;
	CXTBrowseEdit		m_editFileName;
	char				m_fileName[MAX_PATH*2];
	CEdit				m_editMapScale;
	sInt32				m_mapScale;
};






#endif //__REACHABLE_MAP_DLG_H__