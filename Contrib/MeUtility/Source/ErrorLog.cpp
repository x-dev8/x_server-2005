#include "Errorlog.h"
#include <shlwapi.h>

#pragma comment(lib, "shlwapi.lib")

#ifdef _SERVERGUI_

#endif

#ifdef _CLIENT_

#endif
#include "FuncPerformanceLog.h"

static CErrorLog s_errLog;
CErrorLog* GetErrorLog()
{
	guardfunc

	return &s_errLog;
	unguard;
}

INT_PTR CALLBACK CErrorLog::ErrorLogMsgProc( HWND /*hDlg*/,UINT /*uMsg*/,
											WPARAM /*wParam*/, LPARAM /*lParam*/ )
{
	guardfunc
	//switch (uMsg)
	//{
	//case WM_COMMAND:
	//	switch( LOWORD(wParam) )
	//	{
	//	case IDOK:
	//		break;
	//	}
	//}
	return FALSE;
	unguard;
}

CErrorLog::CErrorLog()
{
	guardfunc
	//OutputDebugStr("CGroundTypeMap");
	//HWND hWnd = FindWindow( "dbgviewClass", NULL );
	//if ( !hWnd )
	//{
	//	WinExec( "Dbgview.exe", SW_SHOW );
	//}
#ifdef _ERROR_LOG_

	HWND hWnd = FindWindow( "dbgviewClass", NULL );
	if ( !hWnd )
	{
#ifndef _DEBUG
        WinExec( "Dbgview.exe", SW_SHOW );
#endif	
	}

	//m_hWndDlg = CreateDialog( 
	//	NULL,
	//	MAKEINTRESOURCE(IDD_DIALOG_DEBUG),
	//	NULL,
	//	ErrorLogMsgProc );
	//ShowWindow( m_hWndDlg, SW_SHOW ); 
	////
	//m_hWndEdit = GetDlgItem( m_hWndDlg, IDC_EDIT_INFO );
#endif
	unguard;
}

CErrorLog::~CErrorLog()
{
	guardfunc
	unguard;
}

void CErrorLog::logStringMsg( const char *string, ... )
{
	guardfunc
	if( !string )
		return;
	va_list	va;
	char data[1024];
	va_start( va, string );
	wvnsprintf(data, sizeof(data)-1, string, va );
	va_end( va );
	OutputDebugStr( data );
	unguard;
}

void CErrorLog::logString( const char *string, ... )
{
	guardfunc
#ifdef _ERROR_LOG_
	//return;
	if( !string )
		return;
	va_list	va;
	char data[1024];
	va_start( va, string );
	wvnsprintf(data, sizeof(data)-1, string, va );
	va_end( va );
	OutputDebugStr( data );
	return;

	////static std::string strLog;
	////if ( strLog.size() > 1024*50 )
	////{
	////	strLog.clear();
	////}
	//////
	////strLog += data;
	////SetWindowText( m_hWndEdit, strLog.c_str() );
	////strLog += "\r\n";
	////int nLineCount = (int)SendMessage( m_hWndEdit, EM_GETLINECOUNT, 0, 0 );
	////SendMessage( m_hWndEdit, EM_LINESCROLL, 0, nLineCount );

	//static std::string strLog;
	//if ( strLog.size() > 1024*50 )
	//{
	//	strLog.clear();
	//}
	//std::string str = data;
	//str += "\r\n";
	//str += strLog;
	//strLog = str;
	//SetWindowText( m_hWndEdit, strLog.c_str() );
#else
#endif
	unguard;
}

