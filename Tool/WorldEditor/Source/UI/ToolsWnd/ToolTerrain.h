/*******************************************************************************
*  Copyright ZNWL (C) 2007 - All Rights Reserved
*
* File: 	ToolTerrain.h
* Date: 	05/30/2007
* Desc:
*
*******************************************************************************/
#ifndef _UI_TOOLSWND_TOOLTERRAIN_H__
#define _UI_TOOLSWND_TOOLTERRAIN_H__
class CToolVertex;
////////////////////////////////////////////////////////////////////////////////
class CToolTerrain : public CDialog
{
	DECLARE_DYNAMIC(CToolTerrain)

public:
					CToolTerrain(CToolTerrain* pParent = NULL);   // standard constructor
	virtual			~CToolTerrain();

	// Dialog Data
	enum { IDD = IDD_DLG_TERRAIN };
	
	void			SetActive( bool isModify = false );

	void			EditSizeChanged(float editSize);
protected:
	void			SetBrushShape( sInt32 shape );

protected:
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CToolTerrain)
	virtual void	DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL	OnInitDialog();
	virtual void	OnVScroll( UINT nSBCode, UINT nPos, CScrollBar* pScrollBar );
	virtual void	OnOK(){};
	virtual void	OnCancel(){};
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CToolTerrain)
	afx_msg void	OnChkApplyHeight();
	afx_msg void	OnKillFocusEditSize();

	CToolVertex*	GetToolVertex();
	afx_msg void	OnKillFocusEditStrength();
	afx_msg void	OnKillFocusEditSpeed();

	afx_msg void	OnBtnHeightClicked(UINT nID);

	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

protected:
	bool			m_isActive;
	BOOL			m_isApplyHeight;

	CBitmap			m_sizeBitmap;
	CImageList		m_sizeImageList;
	CButton			m_chkApplyHeight;
	CXTButton		m_btnHeight[4];
};

#endif	// _UI_TOOLSWND_TOOLTERRAIN_H__

