/*******************************************************************************
*  Copyright ZNWL (C) 2007 - All Rights Reserved
*
* File: 	ToolLiquid.h
* Date: 	05/31/2007
* Desc:
*
*******************************************************************************/
#ifndef _UI_TOOLWND_TOOLLIQUID_H__
#define _UI_TOOLWND_TOOLLIQUID_H__
#include "afxwin.h"


class CToolLiquid;
////////////////////////////////////////////////////////////////////////////////
class CToolLiquidDlg : public CDialog
{
	DECLARE_DYNAMIC(CToolLiquidDlg)
public:
	CToolLiquidDlg(CToolLiquidDlg* pParent = NULL);   // standard constructor
	virtual ~CToolLiquidDlg();

	// Dialog Data
	enum { IDD = IDD_DLG_LIQUID };

	void SetActive( bool isModify = false );
	void RefreshLiquid(flt32* pt );
	void UpdateLock( bool isLock );
protected:
	bool UpdateSetting( bool isModify );
	CToolLiquid* GetToolLiquid();

protected:
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CToolLiquidDlg)
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	virtual void OnOK(){};
	virtual void OnCancel(){};
	//}}AFX_VIRTUAL
	//{{AFX_MSG(CToolLiquidDlg)
	afx_msg void OnSelLiquidColor();

	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

protected:
	bool				m_isFillUI;
	CXTBrowseEdit		m_editTextureFile;
	CButton				m_chkLockLayer;

	CString				mWaterHeight;

	CSliderCtrl			mWaterAlphaCtrl;
	int					mWaterAlpha;
	CStatic				mWaterAlphaStatic;

	CStatic				m_TilePos;
	CXTColorPicker		m_cpLiquidColor;
	COLORREF			m_liquidColor;

	CButton				mDelLiquidBtn;
	
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
public:
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnBnClickedBtnDelChunkLiquid();
};

#endif	// _UI_TOOLWND_TOOLLIQUID_H__