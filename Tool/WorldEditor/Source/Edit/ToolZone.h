/*******************************************************************************
*  Copyright ZWS (C) 2008 - All Rights Reserved
*
* File: 	ToolZone.h
* Date: 	01/17/2008
* Desc:
*
*******************************************************************************/
#ifndef _EDIT_TOOL_ZONE_H__
#define _EDIT_TOOL_ZONE_H__

#include "BaseTool.h"
////////////////////////////////////////////////////////////////////////////////

class CWorldChunk;
class CNdlLightRes;
class CNdlFogRes;
class CNdlZoneRes;
class CToolZoneDlg;
////////////////////////////////////////////////////////////////////////////////
class CToolZone	: public CBaseTool
{
	friend class			CToolZoneDlg;
public:
							CToolZone();
	virtual					~CToolZone();

	virtual ToolID			GetToolId()	{ return TOOL_ZONE; };
	virtual	void			SetActive( bool isActive = true );
	bool					Create( CToolManager* toolMgr );

	void					Bind( CToolZoneDlg* bindDlg );

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
	CToolZoneDlg*			m_zoneDlg;
	bool					m_isPaintZone;
	sInt32					m_brushRadius;
	sInt32					m_brushZoneId;
};




#endif	// _EDIT_TOOL_ZONE_H__