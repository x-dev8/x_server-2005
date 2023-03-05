/*******************************************************************************
*  Copyright ZNWL (C) 2007 - All Rights Reserved
*
* File: 	ToolEnvironment.h
* Date: 	06/12/2007
* Desc:
*
*******************************************************************************/
#ifndef _UI_TOOLWND_TOOLWORLDLIGHT_H__
#define _UI_TOOLWND_TOOLWORLDLIGHT_H__
#include "afxwin.h"

////////////////////////////////////////////////////////////////////////////////
class CNdlLightRes;
class CToolLight;
////////////////////////////////////////////////////////////////////////////////

class CToolWorldLightDlg : public CDialog
{
	DECLARE_DYNAMIC(CToolWorldLightDlg)

public:
	CToolWorldLightDlg(CToolWorldLightDlg* pParent = NULL);   // standard constructor
	virtual				~CToolWorldLightDlg();

	// Dialog Data
	enum { IDD = IDD_DLG_LIGHT };

	void				SetActive( bool isModify = false );

	void				UpdateDirLight( const Vector& dirLight );	

protected:
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CToolWorldLightDlg)
	virtual void		DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL		OnInitDialog();
	virtual void		OnOK(){};
	virtual void		OnCancel(){};
	virtual void		OnVScroll( UINT nSBCode, UINT nPos, CScrollBar* pScrollBar );
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CToolEnvironmentDlg)
	afx_msg void		OnSelEndOkAmbientLight();
	afx_msg void		OnSelEndOkDiffuseLight();
	afx_msg void		OnSelEndOkSpecularLight();
	afx_msg void		OnSelEndOkSunLess();
	afx_msg void		OnLightChange();
	afx_msg void		OnKillfocusLightLongitude();
	afx_msg void		OnKillfocusLightLatitude();


	afx_msg void		OnClickAddBtn();
	afx_msg void		OnClickDelBtn();
	afx_msg void		OnBnClickedBtnLightModify();

	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
protected:
	CToolLight*			GetLightTool()const;
	void				SetLight( CNdlLightRes* lightRes );
	bool				GetLight( CNdlLightRes* lightRes );

	void				UpdateLightsLB();
	void				Reset();
	void				RefreshLight();
	float				StringToAngle(CString& sAngle);
	void				AngleToString(float angle,CString& sAngle);
protected:
	sInt32				m_curSel;
	CListBox			mLightsLB;

	CSliderCtrl			m_sliderH; //colorH
	CSliderCtrl			m_sliderS; //colorS
	CSliderCtrl			m_sliderL; //colorL
	CXTColorPicker		m_cpAmbientLight;
	CXTColorPicker		m_cpDiffuseLight;
	CXTColorPicker		m_cpSpecularLight;
	CXTColorPicker		m_cpSunlessColor;

	COLORREF			m_colorAmbientLight;
	COLORREF			m_colorDiffuseLight;
	COLORREF			m_colorSpecularLight;
	COLORREF			m_colorSunless;

	CEdit				m_editName;
	CEdit				m_editLightLongitude; //经度
	CEdit				m_editLightLatitude;//纬度

	CSpinButtonCtrl				m_spinLongitude; //经度
	CSpinButtonCtrl				m_spinLatitude;//纬度

	Vector			m_ptSphericalPos;

	NiColor			RGBToHSL(NiColor color);
	NiColor			HSLToRGB(NiColor color);
	void			updateHSL();
	void			setHSL();

public:
	afx_msg void OnBnClickedRadioAmbient();
	afx_msg void OnBnClickedRadioDiffuse();
	afx_msg void OnBnClickedRadioSpecular();
	afx_msg void OnBnClickedRadioSunless();

	afx_msg void OnNMReleaseSliderColorH(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMReleaseSliderColorS(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMReleaseSliderColorL(NMHDR *pNMHDR, LRESULT *pResult);

	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnDestroy();
};





#endif	// _UI_TOOLWND_TOOLWORLDLIGHT_H__