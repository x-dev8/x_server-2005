/*******************************************************************************
*  Copyright ZNWL (C) 2007 - All Rights Reserved
*
* File: 	ToolDoodadDlg.h
* Date: 	05/31/2007
* Desc:
*
*******************************************************************************/
#ifndef _UI_TOOLWND_TOOLDOODAD_H__
#define	_UI_TOOLWND_TOOLDOODAD_H__
class CWorldRes;
class CToolDoodad;
////////////////////////////////////////////////////////////////////////////////
class CToolDoodadDlg : public CDialog
{
	DECLARE_DYNAMIC(CToolDoodadDlg)

public:
					CToolDoodadDlg(CToolDoodadDlg* pParent = NULL);   // standard constructor
	virtual			~CToolDoodadDlg();

	// Dialog Data
	enum { IDD = IDD_DLG_DOODADS };

	void			SetActive( bool isModify = false );
	void				Refresh(flt32* pt );
	void				UpdateLock( bool isLock );
	void			RefreshChunckDoodadLevel();
	void			BrushChanged(int nSelect );
protected:

protected:
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CToolDoodadDlg)
	virtual void	DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL	OnInitDialog();
	virtual void	OnOK(){};
	virtual void	OnCancel(){};
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CToolDoodadDlg)
	afx_msg void	OnDoodadClassChange();
	afx_msg void	OnCurrDoodadChange();
	afx_msg void	OnBrushSelChange();
	afx_msg void	OnDoodadSelChange();
	afx_msg void	OnDoodadChange();
	afx_msg void	OnModeChange();
	afx_msg void	OnBtnNewLevel();
	afx_msg void	OnBtnDeleteLevel();
	afx_msg void	OnKillfocusEdtSizeFrom();
	afx_msg void	OnKillfocusEdtSizeTo();
	afx_msg void	OnKillfocusEdtDensity();
	
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

protected:
	CToolDoodad*	GetDoodadTool();
	void			UpdateSetting();

	void			FillDoodadClass();
	void			FillDoodad( sInt32 doodadClassId );
	bool							LoadDoodadRes();
	void							EnumDoodadFile( LPCTSTR strDir, sInt32 nType);

protected:
	bool			m_isFillData;

	CComboBox		m_doodadClassList;
	CListBox		m_doodadListBox;
	CComboBox		m_currChunkDoodadList;
	CComboBox		m_DoodadBrushList;
	CComboBox		m_modeList;
	
	CEdit			m_editSizeFrom;
	CEdit			m_editSizeTo;
	CEdit			m_editDensity;
	CButton				m_chkLockLayer;
	CStatic				m_TilePos;
	CStatic				m_LevelUnitSize;
	CStatic				m_LevelType;

	std::vector< CWorldRes* >		m_doodadResList;
	std::vector< CString* >			m_doodadTypeList;
};







#endif	// _UI_TOOLWND_TOOLDOODAD_H__



