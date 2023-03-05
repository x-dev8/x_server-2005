#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include "MapConfig.h"

// WorldAttribute dialog

class WorldAttribute : public CDialog
{
	DECLARE_DYNAMIC(WorldAttribute)

public:
	WorldAttribute(CWnd* pParent = NULL);   // standard constructor
	virtual ~WorldAttribute();

// Dialog Data
	enum { IDD = IDD_DIALOG_ATTRIBUTE };


	void InitInformation();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);

	DECLARE_MESSAGE_MAP()



private:
	void SetEditInt(CEdit &xEdit, int nValue);
	int GetEditInt(CEdit &xEdit, int nDefault);

	void ChangeTypeInfo(int nType);
    int GetSelectItemIndex(HTREEITEM select);

public:
	CEdit m_editName;
	CEdit m_editScripFile;
	CComboBox m_comboType;
	CEdit m_editMinLevel;

	CButton m_checkShowFoot;
	CButton m_checkRide;
	CButton m_checkCanCallPet;
	CButton m_sunLightRender; //add by yanli 2010-6-21
	CButton m_systemCreate; //add by yanli 2010-6-21
	
	CEdit m_editDuration;
	CEdit m_editCount;
	CEdit m_editUnitCount;
	
    //CButton m_checkCanPk;
    CComboBox m_ComboCanPK;
    CTreeCtrl StatusTree;
    CComboBox ComboStatus;
    short ValueStatusLevel;

    MapConfig::MapData* CurMap;

	afx_msg void OnBnClickedOk();
	afx_msg void OnCbnSelchangeComboType();

    afx_msg void OnBnClickedButtonAdd();
    afx_msg void OnBnClickedButtonDel();
    afx_msg void OnBnClickedButtonModifiy();
    afx_msg void OnTvnSelchangedTreeStatus(NMHDR *pNMHDR, LRESULT *pResult);
    //BOOL SystemCreate;
	//BOOL SunLightRander; //add by yanli 2010-6-21
    int ValueRegionOffsetX;
    int ValueRegionOffsetY;
    int ValueRegionEdge;
    
    CString m_CStrMapTip;
    CString m_CStrMapNameColor;
};
