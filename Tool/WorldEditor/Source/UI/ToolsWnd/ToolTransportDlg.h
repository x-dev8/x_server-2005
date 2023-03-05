/*******************************************************************************
* Copyright ShenWang 2008 - All Rights Reserved
* 
* File: 	ToolTransportDlg.h
* Create: 	11/04/08
* Desc:		
* Author:	Yuan Ding
*
* Modify:
* Modify by:
*******************************************************************************/

#ifndef __TOOL_TRANSPORT_DLG_H__
#define __TOOL_TRANSPORT_DLG_H__
#include "afxwin.h"
#include "afxcmn.h"


class CToolTransport;
////////////////////////////////////////////////////////////////////////////////
class CToolTransportDlg : public CDialog
{
	DECLARE_DYNAMIC(CToolTransportDlg)

public:
					CToolTransportDlg(CToolTransportDlg* pParent = NULL);   // standard constructor
	virtual			~CToolTransportDlg();

	// Dialog Data
	enum { IDD = IDD_DLG_TRANSPORT };

	void			SetActive( bool isModify = false );
	void				RefreshTransport(CTransportResBase* pt );
	void				UpdateLock( bool isLock );
protected:
	CToolTransport*		GetToolTransport();

protected:
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CToolTransportDlg)
	virtual void		OnVScroll( UINT nSBCode, UINT nPos, CScrollBar* pScrollBar );
	virtual void	DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL	OnInitDialog();
	virtual void	OnOK(){};
	virtual void	OnCancel(){};
	//}}AFX_VIRTUAL
	//{{AFX_MSG(CToolTransportDlg)
	afx_msg void OnEnKillfocusEdtTransport();
	afx_msg void OnEnKillfocusEdtTarget();
	afx_msg void OnEnKillfocusEdtTargetTile();
	afx_msg void OnBnClickedChkPicktransport();
	afx_msg void OnBnClickedRadioTransport();
	afx_msg void OnBnClickedRadioTarget();

	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

protected:
	CEdit				m_editTransportX;
	CEdit				m_editTransportY;
	CEdit				m_editTransportScaleX;
	CEdit				m_editTransportScaleY;
	CSpinButtonCtrl		m_spinTransportX;
	CSpinButtonCtrl		m_spinTransportY;
	CSpinButtonCtrl		m_spinTransportScaleX;
	CSpinButtonCtrl		m_spinTransportScaleY;
	CEdit				m_editTargetID;
	CXTBrowseEdit		m_editTargetFile;

protected:
	CEdit				m_editTargetX;
	CEdit				m_editTargetY;
	CEdit				m_editTargetDir;
	CSpinButtonCtrl		m_spinTargetX;
	CSpinButtonCtrl		m_spinTargetY;
	CSpinButtonCtrl		m_spinTargetDir;
	CEdit				m_readonlyTargetIndex;
protected:

	CButton				m_isPickTransport;
public:	
	afx_msg void OnBnClickedCheckTarget();
	afx_msg void OnBnClickedCheckRelive();
	afx_msg void OnBnClickedRadioIstarget();
	afx_msg void OnBnClickedRadioIsrelive();
	CButton m_checkRed;
	CComboBox m_comboVestType;
	CEdit m_editMapId;
};







#endif //__TOOL_TRANSPORT_DLG_H__