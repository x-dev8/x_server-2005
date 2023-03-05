/*******************************************************************************
* Copyright ShenWang 2011 - All Rights Reserved
* 
* File: 	ToolStaticLightDlg.h
* Create: 	02/21/2011
* Desc:		静态光源控制面板
* Author:	Qiu Li
*
* Modify:
* Modify by:
*******************************************************************************/
#ifndef TOOL_STATICLIGHT_DLG_H
#define TOOL_STATICLIGHT_DLG_H
#include "afxwin.h"
#include "afxcmn.h"
#include "Resource/resource.h"

class CToolStaticLight;
class LightRes;

class CToolStaticLightDlg : public CDialog
{
	DECLARE_DYNAMIC(CToolStaticLightDlg)

public:
	CToolStaticLightDlg(CToolStaticLightDlg* pParent = NULL);   // standard constructor
	virtual ~CToolStaticLightDlg();

// Dialog Data
	enum { IDD = IDD_DIALOG_STATIC_LIGHT };

	void	SetActive( bool isModify = false );

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnVScroll( UINT nSBCode, UINT nPos, CScrollBar* pScrollBar );
	virtual BOOL OnInitDialog();
	virtual void OnOK(){};
	virtual void OnCancel(){};


protected:
	CListBox m_listStaticLights;

	CEdit m_editWorldPosX;
	CEdit m_editWorldPosY;
	CEdit m_editWorldPosZ;
	CEdit m_editDistance;
	CEdit m_editNearDistance;

	CSpinButtonCtrl m_spinWorldPosX;
	CSpinButtonCtrl m_spinWorldPosY;
	CSpinButtonCtrl m_spinWorldPosZ;
	CSpinButtonCtrl m_spinDistance;
	CSpinButtonCtrl m_spinNearDistance;

	CXTColorPicker	m_cpLightColor;
	COLORREF		m_colorLightColor;

	CSliderCtrl		m_sliderH; //colorH
	CSliderCtrl		m_sliderS; //colorS
	CSliderCtrl		m_sliderL; //colorL

	CButton			m_btnRemoveLight;
	CButton			m_btnMoveToLight;

public:
	afx_msg void OnEnKillfocusEditSLWorldX();
	afx_msg void OnEnKillfocusEditSLWorldY();
	afx_msg void OnEnKillfocusEditSLWorldZ();
	afx_msg void OnEnKillfocusEditSLDistance();
	afx_msg void OnEnKillfocusEditSLNearDist();
	afx_msg void OnLbnSelchangeListStaticLight();
	afx_msg void OnSelEndOkLightColor();
	afx_msg void OnNMReleaseSliderColor(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnBnClickedDeleteLight();
	afx_msg void OnBnClickedMoveToLight();

	DECLARE_MESSAGE_MAP()

public:
	bool	AddLight( const Vector& pos );
	void	SelectLight(int index, BOOL bMulti);
	void	UnSelectLight(int index);
	void	CancelSelect();						// 取消选中

protected:
	void	InitData();

	bool	UpdateWorldPosX();
	bool	UpdateWorldPosY();
	bool	UpdateWorldPosZ();
	bool	UpdateDistance();
	bool	UpdateNearDist();

	bool	UpdateProperties();
	bool	UpdatePropertyByIndex(int index, BOOL bUpdatePos);
	bool	UpdateProperty(float fNearDist, float fDist, const Vector& pos, const NiColorB& color);

	void	EnableControls(BOOL bEnable = TRUE);

	CToolStaticLight* GetTool();

	LightRes* GetLightRes(int index);
	LightRes* GetLightResFromCurSel(int& index);

	void	UnSelectAll();
	void	SelectOneLight(int index, BOOL bUpdateProp);
	void	UnSelectOneLight(int index, BOOL bUpdateProp);
	bool	GetSelectedList(std::vector<int>& vecSelected);
	void	CalSelectNum();

	bool	UpdateLightColor();
	NiColor	RGBToHSL(NiColor color);
	NiColor	HSLToRGB(NiColor color);
	void	updateHSL();
	void	setHSL();

	std::vector<unsigned short>	m_vecLightRef;	// 列表对应StaticLightsContainer的map的key值
	int							m_nLastLightNo;
	int							m_nSelectedNum;
};

#endif /*TOOL_STATICLIGHT_DLG_H*/