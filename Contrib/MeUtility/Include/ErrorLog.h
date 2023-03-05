/********************************************************************
    Filename:    ErrorLog.h
    MaintenanceMan Mail: debugcommand@hotmail.com
*********************************************************************/

#ifndef __UTILITY_ERRORLOG_H__
#define __UTILITY_ERRORLOG_H__

#pragma once

#include "MeRTLibs.h"

class CErrorLog
{
public:
    void logString( const char *string, ... );
    void logStringMsg( const char *string, ... );

private:
    HWND m_hWndDlg;
    HWND m_hWndEdit;

private:
    static INT_PTR CALLBACK ErrorLogMsgProc( HWND hDlg,UINT uMsg, WPARAM wParam, LPARAM lParam );

public:
    CErrorLog();
    ~CErrorLog();
};

extern CErrorLog* GetErrorLog();

#endif // __UTILITY_ERRORLOG_H__
