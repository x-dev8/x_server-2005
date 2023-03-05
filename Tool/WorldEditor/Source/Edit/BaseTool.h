/*******************************************************************************
*  Copyright ZNWL (C) 2007 - All Rights Reserved
*
* File: 	BaseTool.h
* Date: 	02/08/2007
* Desc:
*
*******************************************************************************/
#ifndef _EDIT_BASETOOL_H__
#define _EDIT_BASETOOL_H__
#include "wintab/EditTablet.h"

////////////////////////////////////////////////////////////////////////////////
enum ToolID
{
	TOOL_NONE = -1,
	TOOL_CAMERA,
	TOOL_GAMECAMERA,
	TOOL_VERTEX,
	TOOL_LAYER,
	TOOL_DOODAD,
	TOOL_OBJECT,
	TOOL_LIQUID,
	TOOL_TRANSPORT,
	TOOL_FLYROUTE,
	TOOL_MONSTERQUAD,
	TOOL_ENV,
	TOOL_ZONE,
	TOOL_LIGHT,
	TOOL_CLICK2ADD,
	TOOL_NPC,
	TOOL_FREEBLOCK, // 自动阻挡功能 [12/7/2010 zhangjiayi]
	TOOL_STATICLIGHT,	// 静态灯光
	TOOL_DISPLAY,

	TOOL_FLIGHT
};

class CToolManager;
////////////////////////////////////////////////////////////////////////////////
class IBaseTool
{
public:
	virtual			~IBaseTool()											{};
	
	virtual ToolID	GetToolId()												= 0;
	virtual bool	OnLMouseDown( UINT nFlags, CPoint point )				= 0;
	virtual bool	OnLMouseUp( UINT nFlags, CPoint point )					= 0;
	virtual bool	OnLMouseDblClk( UINT nFlags, CPoint point )				= 0;
	virtual bool	OnRMouseDown( UINT nFlags, CPoint point )				= 0;
	virtual bool	OnRMouseUp( UINT nFlags, CPoint point )					= 0;
	virtual bool	OnMouseMove( UINT nFlags, CPoint point )				= 0;
	virtual bool	OnMouseWheel( UINT nFlags, short zDelta, CPoint point)	= 0;
	virtual bool	OnKeyDown( UINT nChar, UINT nRepCnt, UINT nFlags )		= 0;
	virtual bool	OnKeyUp( UINT nChar, UINT nRepCnt, UINT nFlags )		= 0;
	virtual bool	OnWTPacket(PACKET&,CPoint& point)								= 0;
};

////////////////////////////////////////////////////////////////////////////////
class CBaseTool		: public IBaseTool
{
public:
	CBaseTool() : m_isLDrag(false), m_isRDrag(false), m_isActiveTool(false), m_lParam(0), m_wParam(0), m_toolMgr(NULL), m_activeTimer(0),CAMERA_HUGE_STEP(8.0f* WORLD_SCALE) {}
	virtual			~CBaseTool()											{};
	
	virtual bool	Create( CToolManager* toolMgr )							{ m_toolMgr = toolMgr; return true; };
	bool			IsActiveTool( void )									{ return m_isActiveTool; }
	void			SetParam( uInt32 lParam, uInt32 wParam )				{ m_lParam = lParam; m_wParam = wParam; OnSetParam(); }
	void			GetParam( uInt32& lParam, uInt32& wParam )				{ lParam = m_lParam; wParam = m_wParam; }
	virtual	void	SetActive( bool isActive = true )						{ m_isActiveTool = isActive; }
	virtual ToolID	GetToolId()												{ return TOOL_NONE; };
	virtual bool	OnLMouseDown( UINT nFlags, CPoint point )				{ return false; }
	virtual bool	OnLMouseUp( UINT nFlags, CPoint point )					{ return false; }
	virtual bool	OnLMouseDblClk( UINT nFlags, CPoint point )				{ return false; }
	virtual bool	OnRMouseDown( UINT nFlags, CPoint point )				{ return false; }
	virtual bool	OnRMouseUp( UINT nFlags, CPoint point )					{ return false; }
	virtual bool	OnMouseMove( UINT nFlags, CPoint point )				{ return false; }
	virtual bool	OnMouseWheel( UINT nFlags, short zDelta, CPoint point);
	virtual bool	OnKeyDown( UINT nChar, UINT nRepCnt, UINT nFlags )		{ return false; }
	virtual bool	OnKeyUp( UINT nChar, UINT nRepCnt, UINT nFlags );
	virtual bool	OnWTPacket(PACKET& packet,CPoint& point)					{ return false; }
	virtual bool	OnTimer()												{ return false; }
	virtual void	Render()												{}

	virtual void Redo(void){}
	virtual void Undo(void){}
	virtual bool CanRedo(void){return false;}
	virtual bool CanUndo(void){return false;}

	void					GetRelativePath( LPCTSTR fullModelName, char * localName );

	
protected:
	int						GetCloseIndex( const TPickResult &pickResult ,int except );
	virtual void	OnSetParam()											{};

	void			BeginTimer( UINT uElapse );
	void			EndTimer();

	bool			CameraAdjust( CPoint point, UINT nFlags );
	void			CameraFarNear( Vector deltaPos );

protected:
	UINT			m_activeTimer;
	CToolManager*	m_toolMgr;
	uInt32			m_lParam;
	uInt32			m_wParam;
	bool			m_isActiveTool;	
	bool			m_isLDrag;
	bool			m_isRDrag;

	CPoint			m_oldPos;
	const flt32		CAMERA_HUGE_STEP ;
};

////////////////////////////////////////////////////////////////////////////////
struct TNameInfo 
{
	char	path[MAX_PATH];
	char	name[RES_NAME_LEN];
	sInt32	format;
};


#endif	// _EDIT_BASETOOL_H__

