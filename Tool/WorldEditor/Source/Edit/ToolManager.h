/*******************************************************************************
*  Copyright ZNWL (C) 2007 - All Rights Reserved
*
* File: 	ToolManager.h
* Date: 	02/08/2007
* Desc:
*
*******************************************************************************/
#ifndef _EDIT_TOOLMANAGER_H__
#define _EDIT_TOOLMANAGER_H__

////////////////////////////////////////////////////////////////////////////////
// 只能有一个 BaseTool 激活
class CToolManager
{
public:	
								CToolManager();
								~CToolManager();

	bool						Create( CWnd* parentWnd );
	void						Reset();
	CBaseTool*					GetActiveTool();
	void						SetActiveTool( ToolID id );
	void						SetActiveToolParam( uInt32 lParam=0, uInt32 wParam=0 );
	CBaseTool*					GetTool( ToolID id );
	UINT						BeginTimer( UINT timerID, UINT uElapse );
	void						EndTimer( UINT timerID );

	void						Render();
protected:
	CWnd*						m_parentWnd;
	ToolID						m_activeTool;
	std::vector< CBaseTool* >	m_toolList;
	
};

#endif	// _EDIT_TOOLMANAGER_H__


