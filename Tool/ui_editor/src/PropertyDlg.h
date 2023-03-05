/********************************************************************
	created:	2004/06/16
	created:	16:6:2004   10:16
	filename: 	e:\UIEditor\PropertyDlg.h
	file path:	e:\UIEditor
	file base:	PropertyDlg
	file ext:	h
	author:		WitSun
	
	purpose:	PropertyDlg
*********************************************************************/
#pragma once
#include "propertylist.h"
//#include "Control.h"
#include "BaseControl.h"

// CPropertyDlg 对话框

class CPropertyDlg : public CDialog
{
	DECLARE_DYNAMIC(CPropertyDlg)

public:
	void	Clear();
	void	AddItem( S_PropertyItem* pItem );
	bool	IsUpdate(){ return m_ProList.IsUpdate(); }

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()

public:
	CBaseControl*	m_pstControl;

private:
	BOOL m_bInit;

public:
	CPropertyList m_ProList;
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedOk();

public:
	CPropertyDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CPropertyDlg();
	enum { IDD = IDD_DIALOG_PROPERTY };
};

extern CPropertyDlg	thePropertyDlg;
