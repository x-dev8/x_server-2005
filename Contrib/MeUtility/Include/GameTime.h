/********************************************************************
    Filename:    GameTime.h
    MaintenanceMan Mail: debugcommand@hotmail.com
*********************************************************************/

#ifndef __UTILITY_GAMETIME_H__
#define __UTILITY_GAMETIME_H__

#pragma once

#include "MeRTLibs.h"

// 用64bit来保证时间不会越界
class GameTime
{
public:
    typedef __int64 Time64;

    static void   MyGetCurrentTime();
    static Time64 GetCurrentTime64();

    static bool   IsOverDeadLine( Time64 deadTime ); // 是否过的定的时间
    static bool   IsOverDeadLine( DWORD dwCurrentTime, Time64 n64DeadTime );

    // 使用这个函数来判断时间
    static bool   IsPassCurrentTime( DWORD dwBaseTime, DWORD dwKeepTime );
    static bool   IsPassCurrentTime( DWORD dwCurrentTime, DWORD dwBaseTime, DWORD dwKeepTime );

    // 获得剩余时间
    // dwCurrentTime 当前时间
    // dwBaseTime 上次保存时间
    // dwKeepTime  上次剩余时间
    static DWORD GetLeftKeepTime( DWORD dwCurrentTime, DWORD dwLastTime, DWORD dwKeepTime );

    // 获得游戏时间过了多久
    static DWORD GetPassTime( DWORD dwCurrentTime, DWORD dwLastTime );

private:
    static bool   IsLessOrEqualCurrentTime( Time64 n64DeadTime                );
    static bool   IsLessOrEqualCurrentTime( DWORD dwCurrentTime, Time64 n64DeadTime );

};

#endif // __UTILITY_GAMETIME_H__
