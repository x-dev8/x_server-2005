/*******************************************************************************
* Copyright ShenWang 2008 - All Rights Reserved
* 
* File: 	ToolFlyRouteDlg.h
* Create: 	11/04/08
* Desc:		
* Author:	Yuan Ding
*
* Modify:
* Modify by:
*******************************************************************************/

#ifndef __TOOL_FLYROUTE_DLG_H__
#define __TOOL_FLYROUTE_DLG_H__
#include "afxwin.h"
#include "afxcmn.h"


class CToolRoute;
////////////////////////////////////////////////////////////////////////////////
class CToolRouteDlg : public CDialog
{
	DECLARE_DYNAMIC(CToolRouteDlg)

public:
					CToolRouteDlg(CToolRouteDlg* pParent = NULL);   // standard constructor
	virtual			~CToolRouteDlg();

	// Dialog Data
	enum { IDD = IDD_DLG_FLYROUTE };

	typedef enum
	{
		NPC_ROUTE_MODE = 0,
		FLY_ROUTE_MODE
	} ERouteToolMode;
	void			SetActive( bool isModify = false );
	void				RefreshFlyRoute(CRouteRes* pt );

	void RefreshRoutePoint( CRouteRes* res, int index);
	void				UpdateLock( bool isLock );
	void				UpdateRouteList();
protected:
	CToolRoute*		GetToolRoute();

protected:
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CToolFlyRouteDlg)
	virtual void		OnVScroll( UINT nSBCode, UINT nPos, CScrollBar* pScrollBar );
	virtual void	DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL	OnInitDialog();
	virtual void	OnOK(){};
	virtual void	OnCancel(){};
	//}}AFX_VIRTUAL
	//{{AFX_MSG(CToolFlyRouteDlg)
	afx_msg void OnEnKillfocusEdtRoutePoint();
	afx_msg void OnEnKillfocusEdtRoute();
	afx_msg void OnBnClickedChkPick();
	afx_msg void OnBnClickedButtonAdd();
	afx_msg void OnBnClickedButtonDelete();
	afx_msg void OnLbnSelchangeListFlyroute();
	afx_msg void OnBnClickedRadioNpc();
	afx_msg void OnEnKillfocusEdtWalkSpeed();
	afx_msg void OnEnKillfocusEdtWalkLength();
	afx_msg void OnEnKillfocusEdtStayTime();

	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

protected:
	CEdit				m_editRouteX;
	CEdit				m_editRouteY;
	CEdit				m_editFlyRouteZ;
	CSpinButtonCtrl		m_spinRouteX;
	CSpinButtonCtrl		m_spinRouteY;
	CSpinButtonCtrl		m_spinFlyRouteZ;
	CEdit				m_editIndex;
	CEdit				m_editName;
	CEdit				m_editNextMapID;
	CEdit				m_editNextRouteID;
	CButton m_radio_NPC;
	CEdit m_edit_NPC_Walk_Speed;
	CEdit m_edit_NPC_Walk_Length;
	CEdit m_edit_NPC_Stay_Time;

	CEdit				m_readonlyTargetIndex;

	CButton				m_isPickRoute;
	CListBox m_RouteList;
	ERouteToolMode		m_eRouteToolMode;
public:
	afx_msg void OnBnClickedRadioFly();
	CEdit m_edit_StayAction;
	afx_msg void OnEnKillfocusEdtStayAction();
	afx_msg void OnBnClickedButtonGenerateclosedroute();
};







#endif //__TOOL_FLYROUTE_DLG_H__