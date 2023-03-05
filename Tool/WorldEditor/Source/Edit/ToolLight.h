/*******************************************************************************
*  Copyright ZWS (C) 2008 - All Rights Reserved
*
* File: 	ToolLight.h
* Date: 	01/17/2008
* Desc:
*
*******************************************************************************/
#ifndef _EDIT_TOOLLIGHT_H__
#define _EDIT_TOOLLIGHT_H__

#include "BaseTool.h"
////////////////////////////////////////////////////////////////////////////////

class CWorldChunk;
class CNdlLightRes;
class CNdlFogRes;
class CNdlEnvRes;
class CToolWorldLightDlg;
////////////////////////////////////////////////////////////////////////////////
class CToolLight	: public CBaseTool
{
	friend class			CToolEnvDlg;
public:
	CToolLight();
	virtual					~CToolLight();

	virtual ToolID			GetToolId()	{ return TOOL_LIGHT; };
	bool					Create( CToolManager* toolMgr );

	void					Bind( CToolWorldLightDlg* bindDlg );

	virtual bool			OnLMouseDown( UINT nFlags, CPoint point );
	virtual bool			OnLMouseUp( UINT nFlags, CPoint point );
	virtual bool			OnLMouseDblClk( UINT nFlags, CPoint point );
	virtual bool			OnRMouseDown( UINT nFlags, CPoint point );
	virtual bool			OnRMouseUp( UINT nFlags, CPoint point );
	virtual bool			OnMouseMove( UINT nFlags, CPoint point );
	virtual bool			OnKeyDown( UINT nChar, UINT nRepCnt, UINT nFlags );
	virtual bool			OnKeyUp( UINT nChar, UINT nRepCnt, UINT nFlags );

	virtual void			Render();
	
	void					SetLightDir(Vector dir);
protected:
	bool					LoadDirModel();
	bool					CalcLightPosition();
	void					UpdateLightLight();

	void					UpdateLightNode();
protected:
	Vector				m_lightOrigin;
	Vector				m_lightDir;		
	
	TObjectEditInfo				m_lightNode;
	CToolWorldLightDlg*		m_bindDlg;
};

#endif	// _EDIT_TOOLZONE_H__