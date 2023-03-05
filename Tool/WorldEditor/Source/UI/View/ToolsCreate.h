/*******************************************************************************
*  Copyright ZNWL (C) 2007 - All Rights Reserved
*
* File: 	ToolsCreate.h
* Date: 	05/29/2007
* Desc:
*
*******************************************************************************/
#ifndef _UI_VIEW_TOOLSCREATE_H__
#define _UI_VIEW_TOOLSCREATE_H__
#include "ui/ToolsWnd/DlgNpcEditor.h"
#include "ui/ToolsWnd/ToolStaticLightDlg.h"
////////////////////////////////////////////////////////////////////////////////
enum emToolType
{
	emTT_Terrain = 0,
	emTT_Layer,
	emTT_Doodad,
	emTT_Model,
	emTT_Liquid,
	emTT_Transport = ID_TOOLS_TRANSPORT - ID_TOOLS_TERRAIN,
	emTT_Monster = ID_TOOLS_MONSTER - ID_TOOLS_TERRAIN,
	emTT_FlyRoute = ID_TOOLS_FLYROUTE - ID_TOOLS_TERRAIN,
	emIT_NPC = ID_TOOLS_NPC - ID_TOOLS_TERRAIN,
	emTT_Flight,
	emTT_StaticLight = ID_TOOLS_STATICLIGHT - ID_TOOLS_TERRAIN
};

////////////////////////////////////////////////////////////////////////////////
class CToolsCreate : public CWnd
{
public:
					CToolsCreate();
	DECLARE_DYNCREATE(CToolsCreate)
	virtual			~CToolsCreate();
	
	virtual void	OnInitialUpdate();
	
	void			SetActive();
	void			Reset();
protected:
	void			SetTool( emToolType toolType );
	// Generated message map function

protected:
	//{{AFX_MSG(CWorldExplorerView)
	afx_msg void	OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL	OnEraseBkgnd(CDC* pDC);
	afx_msg void	OnSetFocus(CWnd* pOldWnd);

	afx_msg void	OnToolsCommand(UINT nID);
	afx_msg void	OnToolsTransport();
	afx_msg void	OnToolsFlyRoute();
	afx_msg void	OnToolsMonster();
	afx_msg void	OnUpdateToolsCommand(CCmdUI* pCmdUI);
	afx_msg void    OnToolsNpc();
	afx_msg void    OnToolsStaticLight();

	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
protected:
	CXTPToolBar		m_wndToolBar;
	UINT			m_nCurrentTool;
	
	CToolTerrain	m_wndTerrain;
	CToolLayerDlg	m_wndLayer;
	CToolDoodadDlg	m_wndDoodad;	
	CToolModel		m_wndModel;
	CToolLiquidDlg	m_wndLiquid;
	CToolTransportDlg m_wndTransport;
	CToolRouteDlg m_wndFlyRoute;
	CToolMonsterQuadDlg m_wndMonsterQuad;
	CDlgNpcEditor       m_wndNpcEditor;
	CToolStaticLightDlg m_wndStaticLight;
};






#endif	// _UI_VIEW_TOOLSCREATE_H__