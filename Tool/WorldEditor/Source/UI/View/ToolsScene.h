/*******************************************************************************
*  Copyright ZNWL (C) 2007 - All Rights Reserved
*
* File: 	ToolsScene.h
* Date: 	06/07/2007
* Desc:
*
*******************************************************************************/
#ifndef _UI_VIEW_TOOLSSCENE_H__
#define _UI_VIEW_TOOLSSCENE_H__

////////////////////////////////////////////////////////////////////////////////
class CToolWorldLightDlg;
class CToolWorldFogDlg;
////////////////////////////////////////////////////////////////////////////////
enum emSceneWndType
{
	emSWT_World = 0,
	emSWT_Environment,
	emSWT_WorldLight,
	emSWT_WorldFog,
	emSWT_Zone,
	emTT_Click2Add = ID_TOOLS_CLICK2ADD - ID_TOOLBAR_SECNE_WORLD,
	emSWT_Flight
};

////////////////////////////////////////////////////////////////////////////////
class CToolsScene : public CWnd
{
public:
						CToolsScene();
	DECLARE_DYNCREATE(CToolsScene)
	virtual				~CToolsScene();

	virtual void		OnInitialUpdate();

public:
	void				SetActive();
	CToolWorld&			GetToolWorldWnd() { return m_wndWorld; } ;

protected:
	void				SwitchWnd( emSceneWndType wndType );

protected:
	//{{AFX_MSG(CToolsScene)
	afx_msg void		OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL		OnEraseBkgnd(CDC* pDC);
	afx_msg void		OnSetFocus(CWnd* pOldWnd);

	afx_msg void		OnToolsCommand(UINT nID);
	afx_msg void		OnToolsClick2Add();
	afx_msg void		OnUpdateToolsCommandWorld(CCmdUI* pCmdUI);
	afx_msg void		OnUpdateToolsCommandEnvironment(CCmdUI* pCmdUI);
	afx_msg void		OnUpdateToolsCommandWorldLight(CCmdUI* pCmdUI);
	afx_msg void		OnUpdateToolsCommandWorldFog(CCmdUI* pCmdUI);
	afx_msg void		OnUpdateToolsCommandZone(CCmdUI* pCmdUI);

	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
protected:
	CXTPToolBar			m_wndToolBar;
	UINT				m_nCurrentTool;

	CToolWorld			m_wndWorld;
	CToolEnvDlg			m_wndEnvironment;
	CToolWorldLightDlg	m_wndWorldLight;
	CToolWorldFogDlg	m_wndWorldFog;
	CToolZoneDlg		m_wndZone;
	CToolClick2AddDlg m_wndClick2Add;

	emSceneWndType		m_curSceneWndType;
};







#endif	// _UI_VIEW_TOOLSSCENE_H__