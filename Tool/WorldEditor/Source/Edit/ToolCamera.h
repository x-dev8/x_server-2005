/*******************************************************************************
*  Copyright ZNWL (C) 2007 - All Rights Reserved
*
* File: 	ToolCamera.h
* Date: 	02/08/2007
* Desc:
*
*******************************************************************************/
#ifndef _EDIT_TOOLCAMERA_H__
#define _EDIT_TOOLCAMERA_H__

#include "BaseTool.h"
////////////////////////////////////////////////////////////////////////////////
class CToolCamera	: public CBaseTool
{
public:
					CToolCamera();
	virtual			~CToolCamera();
				
	virtual ToolID	GetToolId()	{ return TOOL_CAMERA; };

	virtual	void	SetActive( bool isActive = true );

	virtual bool	OnLMouseDown( UINT nFlags, CPoint point );
	virtual bool	OnLMouseUp( UINT nFlags, CPoint point );
	virtual bool	OnLMouseDblClk( UINT nFlags, CPoint point );
	virtual bool	OnRMouseDown( UINT nFlags, CPoint point );
	virtual bool	OnRMouseUp( UINT nFlags, CPoint point );
	virtual bool	OnMouseMove( UINT nFlags, CPoint point );
	virtual bool	OnKeyDown( UINT nChar, UINT nRepCnt, UINT nFlags );
	virtual bool	OnKeyUp( UINT nChar, UINT nRepCnt, UINT nFlags );
			
	
};


#endif	// _EDIT_TOOLCAMERA_H__

