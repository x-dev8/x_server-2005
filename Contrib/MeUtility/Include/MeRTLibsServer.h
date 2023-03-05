/********************************************************************
    Filename:    MeRTLibsServer.h
    MaintenanceMan Mail: debugcommand@hotmail.com
*********************************************************************/

#ifndef __UTILITY_RTLIBS_SERVER_H__
#define __UTILITY_RTLIBS_SERVER_H__

#ifdef _WIN32 // window
#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0501
#define WIN32_LEAN_AND_MEAN		// Exclude rarely-used stuff from Windows headers
#endif
#pragma warning( push )
#pragma warning( disable : 4005)
#include <WinSock2.h>
#include <Windows.h>
#pragma warning( pop )
#include <Windowsx.h>
#include <WTypes.h>
#include <shellapi.h>
#include <comutil.h>
#include <shlobj.h>
#include <tlhelp32.h>
#include <winsvc.h>

#include <stdlib.h>
#include <dbghelp.h>
#include <wtypes.h>

#else // linux
#include <sys/mman.h>
#endif // linux

#include "MeRTLibs.h"

#ifdef _USE_LOG4CXX_
#include "LogMessage.h"
#endif

//////////////////////////////////////////////////////////////////////////////////////
// 返回值检测宏
#define MES_NEW(className)                      CNewWithDebug<className>::Alloc(1,    "实例"#className)
#define MES_NEW_SIZE(className,size )           CNewWithDebug<className>::Alloc(size, "实例"#className)
#define MES_NEW_SIZE_NAME(className,size,name ) CNewWithDebug<className>::Alloc(size, name );
#define MES_DELETE(className)                   CNewWithDebug<className>::Free(this);
#define MES_DELETE_P(className, pointer)        CNewWithDebug<className>::Free(pointer);

#define RESULT_SUCCESS( res ) ((res) == 0 )
#define RESULT_FAILED( res )  !RESULT_SUCCESS(res)

#define INVALID_VALUE -1

#define SAVE_DELETE_POINTER( pointer ) if ( pointer )\
                                       { delete pointer; pointer = 0; }

#define ERROR_RETURN( result ) if ( result != 0 ) \
                               { return result; }

#define CHECK_RETURN( result, returnvalue ) if ( (result) ) \
                                            { return returnvalue; }

#endif // __MORE_RTLIBS_SERVER_H__
