/*******************************************************************************
*  Copyright ZWS (C) 2008 - All Rights Reserved
*
* File: 	ToolEnv.h
* Date: 	01/17/2008
* Desc:
*
*******************************************************************************/
#ifndef _EDIT_TOOL_ENV_H__
#define _EDIT_TOOL_ENV_H__

#include "BaseTool.h"
////////////////////////////////////////////////////////////////////////////////

class CWorldChunk;
class CNdlLightRes;
class CNdlFogRes;
class CNdlEnvRes;
class CToolEnvDlg;
////////////////////////////////////////////////////////////////////////////////
class CToolEnv	: public CBaseTool
{
	friend class			CToolEnvDlg;
public:
							CToolEnv();
	virtual					~CToolEnv();

	virtual ToolID			GetToolId()	{ return TOOL_ENV; };
	bool					Create( CToolManager* toolMgr );

	void					Bind( CToolEnvDlg* bindDlg );

	virtual bool			OnLMouseDown( UINT nFlags, CPoint point );
	virtual bool			OnLMouseUp( UINT nFlags, CPoint point );
	virtual bool			OnLMouseDblClk( UINT nFlags, CPoint point );
	virtual bool			OnRMouseDown( UINT nFlags, CPoint point );
	virtual bool			OnRMouseUp( UINT nFlags, CPoint point );
	virtual bool			OnMouseMove( UINT nFlags, CPoint point );
	virtual bool			OnKeyDown( UINT nChar, UINT nRepCnt, UINT nFlags );
	virtual bool			OnKeyUp( UINT nChar, UINT nRepCnt, UINT nFlags );

	virtual void			Render();
	
	void					SetPaintMode( bool isPaint );
protected:
	bool					PaintZone( flt32* pt, sInt32 brushSize );
	bool					UpdateZone( flt32* pt );
	void					UpdateZonePreview( sInt32 zoneId );

protected:
	CToolEnvDlg*			m_envDlg;
	bool					m_isPaintZone;
	sInt32					m_brushRadius;
	sInt32					m_brushZoneId;
};




#endif	// _EDIT_TOOL_ENV_H__