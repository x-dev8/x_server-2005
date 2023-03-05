/*******************************************************************************
* Copyright ShenWang 2008 - All Rights Reserved
* 
* File: 	IWindow.h
* Create: 	10/06/06
* Desc:		´°¿Ú½Ó¿Ú
* Author:	Qiu Li
*
* Modify:
* Modify by:
*******************************************************************************/
#ifndef __IWINDOW_H__
#define __IWINDOW_H__

class IWindow
{
public:
	IWindow() {}
	virtual ~IWindow() {}

public:
	virtual bool	Create( HINSTANCE hInstance, const wchar_t* pName, int width, int height, bool isFullscreen )	= 0;
	virtual void	Destroy()									= 0;

	virtual void	Update( float pTime, float pDeltaTime )		= 0;
	virtual void	Render( float pTime, float pDeltaTime )		= 0;

	virtual bool	IsActive()									= 0;
	virtual HWND	GetHandle()									= 0;
	virtual LRESULT	HandleMessage( HWND pWnd, UINT pMsg, WPARAM pWp, LPARAM pLp ) = 0;

};

#endif	// __IWINDOW_H__
