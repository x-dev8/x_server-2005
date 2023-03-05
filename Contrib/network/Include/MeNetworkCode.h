/********************************************************************
    Filename:    MeNetworkCode.h
    MaintenanceMan Mail: Luo_157@hotmail.com
*********************************************************************/

#ifndef __MENETWORK_MENETWORKCODE_H__
#define __MENETWORK_MENETWORKCODE_H__

#pragma once

// 函数返回类型枚举
enum EResultNetworkCode
{
    ERNC_Success                = 0x0000,
    ERNC_RecvMessageLawless     = 0x0001,
    ERNC_RecvException          = 0x0002,
    ERNC_RecvBufferSizeLessZero = 0x0003,
    ERNC_SocketStartupError     = 0x0004,
    ERNC_SocketCreateError      = 0x0005,
    ERNC_SocketListenerError    = 0x0006,
    ERNC_SocketStartIOCPError   = 0x0007,
    ERNC_SocketAcceptError      = 0x0008,
    ERNC_SocketConnectError     = 0x0009,
    ERNC_NullPointer            = 0x000a,
    ERNC_SocketClose            = 0x000b,
    ERNC_MessageLengthError     = 0x000c,
    ERNC_RecvMessageLawless1    = 0x000d,
    ERNC_RecvMessageLawless2    = 0x000e,
};

#endif // __MENETWORK_MENETWORKCODE_H__
