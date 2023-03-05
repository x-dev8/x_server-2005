/********************************************************************
    Filename:    GameTime.h
    MaintenanceMan Mail: debugcommand@hotmail.com
*********************************************************************/

#ifndef __UTILITY_GAMETIME_H__
#define __UTILITY_GAMETIME_H__

#pragma once

#include "MeRTLibs.h"

// ��64bit����֤ʱ�䲻��Խ��
class GameTime
{
public:
    typedef __int64 Time64;

    static void   MyGetCurrentTime();
    static Time64 GetCurrentTime64();

    static bool   IsOverDeadLine( Time64 deadTime ); // �Ƿ���Ķ���ʱ��
    static bool   IsOverDeadLine( DWORD dwCurrentTime, Time64 n64DeadTime );

    // ʹ������������ж�ʱ��
    static bool   IsPassCurrentTime( DWORD dwBaseTime, DWORD dwKeepTime );
    static bool   IsPassCurrentTime( DWORD dwCurrentTime, DWORD dwBaseTime, DWORD dwKeepTime );

    // ���ʣ��ʱ��
    // dwCurrentTime ��ǰʱ��
    // dwBaseTime �ϴα���ʱ��
    // dwKeepTime  �ϴ�ʣ��ʱ��
    static DWORD GetLeftKeepTime( DWORD dwCurrentTime, DWORD dwLastTime, DWORD dwKeepTime );

    // �����Ϸʱ����˶��
    static DWORD GetPassTime( DWORD dwCurrentTime, DWORD dwLastTime );

private:
    static bool   IsLessOrEqualCurrentTime( Time64 n64DeadTime                );
    static bool   IsLessOrEqualCurrentTime( DWORD dwCurrentTime, Time64 n64DeadTime );

};

#endif // __UTILITY_GAMETIME_H__
