/*******************************************************************************
*  Copyright ZNWL (C) 2007 - All Rights Reserved
*
* File: 	ToolWorld.h
* Date: 	06/07/2007
* Desc:
*
*******************************************************************************/
#ifndef _UI_TOOLSSCENE_TOOLWORLD_H__
#define _UI_TOOLSSCENE_TOOLWORLD_H__
#include "afxcmn.h"
#include "afxwin.h"
#include "MapContrastDlg.h"
#include "../Custom/ScrollableDialog.h"

class CTextureNavigationWnd;
////////////////////////////////////////////////////////////////////////////////
class CToolWorld : public ScrollableDialog
{
	DECLARE_DYNAMIC(CToolWorld)

public:
					CToolWorld(CToolWorld* pParent = NULL);   // standard constructor
	virtual			~CToolWorld();

	// Dialog Data
	enum { IDD = IDD_DLG_WORLD };

	void			SetActive( bool isModify = false );
	void			AddTile( CString& name );
	void			UpdateTree( const char* worldPath );
	void			Reset();
	
	void			UpdateMinimap();
	void			UpdateWorldTree( sInt32 tileId);
	void			SetTilePrompt( const TCHAR* strPmpt );

protected:
	void			GetCurrentPath(CString& pPath,bool isAbsolute = true);
	void			GetCurrentName(CString& pName,bool isAbsolute = true);
	bool			RefreshByTile(CWorldTile* pTile);
protected:
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CToolTerrain)
	virtual void	DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL	OnInitDialog();
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CToolTerrain)
	afx_msg void	OnBtnNewtile();
	afx_msg void	OnBtnRefresh();
	afx_msg void	OnBtnNewFolder();
	afx_msg void	OnBtnDelTile();
	afx_msg void	OnChkShowGrid();
	afx_msg void	OnChkReachable();
	afx_msg void	OnDbClkTreeCtrl(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void	OnRClkTreeCtrl(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void	OnListMenuSnapMinimap();
	afx_msg void	OnListMenuReachableMap();
	afx_msg void	OnListMenuReplaceTileTexture();
	afx_msg void	OnListMenuCleanModel();
	afx_msg void	OnListMenuConvert2GameMap();
	afx_msg void	OnListMenuMonsterData();
	afx_msg void	OnListMenuCalPFWeight();
	afx_msg void	OnListMenuWaterMap();
	afx_msg void	OnListMenuHeightMap();
	afx_msg void	OnListMenuMapModels();

	afx_msg void	OnNMCustomdrawSliderHeightscale(NMHDR *pNMHDR, LRESULT *pResult);

	void			UpdateHeightScale( int nPos );
	afx_msg void	OnNMCustomdrawSliderSizescale(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void	OnKillfocusReachableAngle();
    afx_msg void	OnListMenuSnapBBoxMinimap();
	//}}AFX_MSGO
	DECLARE_MESSAGE_MAP()

protected:
	sInt32					m_tile;
	
	CXTTreeCtrl				m_treeWorld;
	CBitmap					m_sizeBitmap;
	CImageList				m_sizeImageList;

	CTextureNavigationWnd	m_tileNavigation;

	void			EnumWTDFile( CString& strDir,HTREEITEM rootItem );

	void			DeleteWTDFiles( CString& strDir);

	static unsigned int __stdcall GenerateReachableMapThreadProc(void *args);

	HTREEITEM		AddChildLeafNode( CString strPath, HTREEITEM rootItem );
	HTREEITEM		FindTile( sInt32 tileHash );
	HTREEITEM		FindTile( sInt32 tileHash ,HTREEITEM rootItem);
	HTREEITEM		GetCurrSelFoler();
	CSliderCtrl				m_sliderHeightScale;
	CStatic					m_textHeightScale;
	sInt32					m_sliderHeightPos;
	
	CSliderCtrl				m_sliderSizeScale;
	CStatic					m_textSizeScale;
	sInt32					m_sliderSizePos;
	CEdit					m_editMesh;
	CSliderCtrl			m_sliderMeshHeight;
	sInt32					m_nMeshHeight;
	CEdit					m_editReachableAngle;

	CButton					m_ckShowReachable;
	CEdit					m_edit_ChineseName;
public:
	afx_msg void OnEnKillfocusEditChinesename();
	afx_msg void OnBnClickedChkShowfootprint();
	CButton m_check_ShowFootPrint;
	afx_msg void OnBnClickedButtonWorldattr();
	afx_msg void OnBnClickedButtonSetMesh();
	afx_msg void OnMeshHeightSizescale(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButtonContrast();
	afx_msg void OnBnClickedButtonBloom();
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnSize(UINT nType, int cx, int cy);
};

#endif	// _UI_TOOLSSCENE_TOOLWORLD_H__