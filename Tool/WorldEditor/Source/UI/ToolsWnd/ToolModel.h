/*******************************************************************************
*  Copyright ZNWL (C) 2007 - All Rights Reserved
*
* File: 	ToolModel.h
* Date: 	05/30/2007
* Desc:
*
*******************************************************************************/
#ifndef _UI_TOOLSWND_TOOLMODEL_H__
#define _UI_TOOLSWND_TOOLMODEL_H__
#include "afxcmn.h"
#include "afxwin.h"

#include "../Custom/ScrollableDialog.h"

class CToolObject;
class CToolModel : public ScrollableDialog
{
	DECLARE_DYNAMIC(CToolModel)

public:
						CToolModel(CToolModel* pParent = NULL);   // standard constructor
	virtual				~CToolModel();

	// Dialog Data
	enum { IDD = IDD_DLG_MODEL };

	void				SetActive( bool isModify = false );

	CToolObject*		GetToolObject();
	void				RefreshInfo();
	void				UpdatePickedModelList(TPickResult& pickResult);
	void				RefreshPickedModelName(int nIndex,LPCTSTR strName);
	bool				SelectNextModelInModelTree();
	bool				SelectPreModelInModelTree();			
protected:
	void				UpdateModelTree(LPCTSTR ppathName, bool isRecursion);
	void				UpdateWorldPos();
	void				UpdateOff(UINT nPos, CScrollBar* pScrollBar);
	void				UpdateOff();
	void				UpdateRot();
	void				UpdateScl();
	void				CreateModelTree(LPCTSTR ppathName,HTREEITEM rootItem, bool isRecursion);
	HTREEITEM			AddChildLeafNode( CString strPath, HTREEITEM rootItem );

	bool			GetCurrentPath(CString& pPath,bool isAbsolute = true);
	bool			GetCurrentName(CString& pName,bool isAbsolute = true);
	HTREEITEM		GetCurrSelFoler();
protected:
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CToolModel)
	virtual void		DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL		OnInitDialog();
	virtual void		OnOK(){};
	virtual void		OnCancel(){};

	//}}AFX_VIRTUAL

	//{{AFX_MSG(CToolModel)
	afx_msg void		OnChkRecursion();
	afx_msg void		OnBtnAddModel();
	afx_msg void		OnModelChange(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void		OnChkPickobj();
	afx_msg void		OnChkLockParam();
	afx_msg void		OnBnClickedBtnSync();
	afx_msg void		OnBnClickedBtnReset();
	afx_msg void		OnKillfocusEdtWorld();
	afx_msg void		OnKillfocusEdtOff();
	afx_msg void		OnKillfocusEdtRot();
	afx_msg void		OnKillfocusEdtScl();
	afx_msg void		OnLbnSelchangeListPickedModel();
	afx_msg void		OnBnClickedBtnModelChange();
	afx_msg void		OnChkLightmapCastShadow();
	afx_msg void		OnCbnSelchangeLightmapResolution();
	afx_msg void		OnBnClickedBuildLightmapOneModel();

	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

protected:
	CBitmap				m_sizeBitmap;
	CImageList			m_sizeImageList;
	CXTTreeCtrl			m_treeModel;
	CString				m_currRoot;

	CButton				m_chkRecursion;
	CButton				m_chkPickObj;
	CButton				m_chkLockParam;
// 	CButton				m_chkLockParamOff;
// 	CButton				m_chkLockParamRot;
// 	CButton				m_chkLockParamScl;

	CEdit				m_editPosX;
	CEdit				m_editPosY;
	CEdit				m_editPosZ;
	CEdit				m_editOffX;
	CEdit				m_editOffY;
	CEdit				m_editOffZ;
	CEdit				m_editRotX;
	CEdit				m_editRotY;
	CEdit				m_editRotZ;
	CEdit				m_editSclXYZ;
	CSpinButtonCtrl		m_spinPosX;
	CSpinButtonCtrl		m_spinPosY;
	CSpinButtonCtrl		m_spinPosZ;
	CSpinButtonCtrl		m_spinOffX;
	CSpinButtonCtrl		m_spinOffY;
	CSpinButtonCtrl		m_spinOffZ;
	CSpinButtonCtrl		m_spinRotX;
	CSpinButtonCtrl		m_spinRotY;
	CSpinButtonCtrl		m_spinRotZ;
	CSpinButtonCtrl		m_spinSclXYZ;

	CListBox			m_listPickedModel;
	CXTBrowseEdit		m_editChangeModelPath;
	CButton				m_checkCastShadow;
	CComboBox			m_comboLightmapResolution;
public:
	afx_msg void OnPopmodelmove();
	afx_msg void OnPopmodelrotate();
	afx_msg void OnPopmodelscale();
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnSize(UINT nType, int cx, int cy);
};


#endif	// _UI_TOOLSWND_TOOLMODEL_H__