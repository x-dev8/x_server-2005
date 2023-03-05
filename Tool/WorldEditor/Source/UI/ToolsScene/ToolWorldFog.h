/*******************************************************************************
*  Copyright ZNWL (C) 2007 - All Rights Reserved
*
* File: 	ToolEnvironment.h
* Date: 	06/12/2007
* Desc:
*
*******************************************************************************/
#ifndef _UI_TOOLWND_TOOLWORLDFOG_H__
#define _UI_TOOLWND_TOOLWORLDFOG_H__

class CNdlFogRes;
////////////////////////////////////////////////////////////////////////////////
class CToolWorldFogDlg : public CDialog
{
	DECLARE_DYNAMIC(CToolWorldFogDlg)

public:
						CToolWorldFogDlg(CToolWorldFogDlg* pParent = NULL);   // standard constructor
	virtual				~CToolWorldFogDlg();

	// Dialog Data
	enum { IDD = IDD_DLG_FOG };

	void				SetActive( bool isModify = false );
protected:
	void				SetFog( CNdlFogRes* fogRes );
	bool				GetFog( CNdlFogRes* fogRes );

	void				UpdateList();
	void				Reset();

protected:
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CToolDoodadDlg)
	virtual void		DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL		OnInitDialog();
	virtual void		OnOK(){};
	virtual void		OnCancel(){};
	//}}AFX_VIRTUAL
	
	//{{AFX_MSG(CToolEnvironmentDlg)
	afx_msg void		OnSelEndOkColorLight();
	
	afx_msg void		OnFogChange();

	afx_msg void		OnKillfocusName();
	afx_msg void		OnKillfocusLightNear();
	afx_msg void		OnKillfocusLightFar();

	afx_msg void		OnKillfocusBloomScale();
	afx_msg void		OnKillfocusLuminance();
	afx_msg void		OnBnClickedBtnModify();
	afx_msg void		OnBnClickedBtnAdd();
	afx_msg void		OnBnClickedBtnDel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()


protected:
	sInt32				m_curSel;

	CEdit				m_editName;
	CListBox			mFogLB;
	
	CXTColorPicker		m_cpFogLight;

	COLORREF			m_colorFogLight;

	CEdit				m_editLightNear;
	CEdit				m_editLightFar;

	CEdit				m_editBloomScale;
	CEdit				m_editLuminance;
};





#endif	// _UI_TOOLWND_TOOLWORLDFOG_H__