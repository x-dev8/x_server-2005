/********************************************************************
    Filename:    gDebug.h
    MaintenanceMan Mail: debugcommand@hotmail.com
*********************************************************************/

#ifndef __UTILITY_GDEBUG_H__
#define __UTILITY_GDEBUG_H__

#pragma once

////////////////////////////////////////////////////////////////////////////
// 信息输出类
//////////////////////////////////////////////////////////////////////////

//信息显示最大长度
#define LOGSTR_MAXLENGTH    4096    
//信息类名最大长度
#define LOGSTR_MAXNAMELEN   8192
#pragma warning(disable:4311)
//是否强制无log
//#define NOLOG

#include "MeRTLibs.h"

class gDebugLog
{
//private:
//    //输出文件名
//    char m_logfile[MAX_PATH];
//    //信息类名
//    char m_logname[LOGSTR_MAXNAMELEN];
//    //有效与否
//    bool m_enable;
//    //字符缓冲
//    static char TmpBuf[LOGSTR_MAXLENGTH];
//    static char MsgBuf[LOGSTR_MAXLENGTH+MAX_PATH+10];


public:
    gDebugLog();
    ~gDebugLog();
	gDebugLog( char* file );
    
    //设置输出文件
    bool SetFile( char *file );
    //设置信息类名
    bool SetName( char *name );
    //重置
    bool Reset( char *file, char *name );
    //输出
    bool Output( LPCTSTR szError, ... );
	bool OutputWithTime( LPCTSTR szError,... );

	// output bin data chunk
	bool Output( BYTE* pBuffer, int nSize );
    void MsgBox( LPCTSTR szError, ... );

    //有效
    void Enable();
    //失效
    void Disable();
};

#endif //__COMMON_GDEBUG_H__