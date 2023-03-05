/********************************************************************
    Filename:    gDebug.h
    MaintenanceMan Mail: debugcommand@hotmail.com
*********************************************************************/

#ifndef __UTILITY_GDEBUG_H__
#define __UTILITY_GDEBUG_H__

#pragma once

////////////////////////////////////////////////////////////////////////////
// ��Ϣ�����
//////////////////////////////////////////////////////////////////////////

//��Ϣ��ʾ��󳤶�
#define LOGSTR_MAXLENGTH    4096    
//��Ϣ������󳤶�
#define LOGSTR_MAXNAMELEN   8192
#pragma warning(disable:4311)
//�Ƿ�ǿ����log
//#define NOLOG

#include "MeRTLibs.h"

class gDebugLog
{
//private:
//    //����ļ���
//    char m_logfile[MAX_PATH];
//    //��Ϣ����
//    char m_logname[LOGSTR_MAXNAMELEN];
//    //��Ч���
//    bool m_enable;
//    //�ַ�����
//    static char TmpBuf[LOGSTR_MAXLENGTH];
//    static char MsgBuf[LOGSTR_MAXLENGTH+MAX_PATH+10];


public:
    gDebugLog();
    ~gDebugLog();
	gDebugLog( char* file );
    
    //��������ļ�
    bool SetFile( char *file );
    //������Ϣ����
    bool SetName( char *name );
    //����
    bool Reset( char *file, char *name );
    //���
    bool Output( LPCTSTR szError, ... );
	bool OutputWithTime( LPCTSTR szError,... );

	// output bin data chunk
	bool Output( BYTE* pBuffer, int nSize );
    void MsgBox( LPCTSTR szError, ... );

    //��Ч
    void Enable();
    //ʧЧ
    void Disable();
};

#endif //__COMMON_GDEBUG_H__