#ifndef __GLOBAL_OBJECT_H__
#define __GLOBAL_OBJECT_H__

#include "stdafx.h"

#define WM_SHOWTRAY WM_USER + 1002

#pragma warning( push, 0 )
#pragma warning( disable, 4996 )

class GlobalObject
{
public:
    static HWND g_hMainWin;

    static HINSTANCE g_hMainInstance;

    static std::string g_strServerName;

    static void makeTrayShow( bool bShow = true );
};

HWND GlobalObject::g_hMainWin = NULL;

HINSTANCE GlobalObject::g_hMainInstance = NULL;

std::string GlobalObject::g_strServerName = "ApplicationManager";

void GlobalObject::makeTrayShow( bool bShow )
{   
    NOTIFYICONDATA nid;
    nid.cbSize = (DWORD)sizeof(NOTIFYICONDATA);
    nid.hWnd   = GlobalObject::g_hMainWin;
    nid.uID    = IDR_MAINFRAME;

    if ( bShow )
    {
        nid.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP ;
        nid.uCallbackMessage = WM_SHOWTRAY;
        nid.hIcon = LoadIcon( g_hMainInstance, MAKEINTRESOURCE(IDR_MAINFRAME));
        strncpy( nid.szTip, GlobalObject::g_strServerName.c_str(), (sizeof(nid.szTip)-1) / 2);
        Shell_NotifyIcon(NIM_ADD,&nid); 
    }
    else
    {
        // É¾³ýÍÐÅÌÍ¼±ê
        Shell_NotifyIcon(NIM_DELETE,&nid);
    }
}

#pragma warning( pop )

#endif
