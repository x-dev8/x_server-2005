#ifndef __PASSWORDMESSAGE_H__
#define __PASSWORDMESSAGE_H__
/******************************************************
        财产保护消息定义
        Author:eliteYang
******************************************************/

#include "MsgBase.h"
#include "PasswordDefine.h"
#include "MessageRangeDefine.h"

#pragma pack(push, 1)

enum PasswordMessageDefine
{

    MSG_SETSECONDPASSWORDREQ = GAMEWORLD_PASSWORD_BEGIN,     // 设置密码请求
    MSG_RESETSECONDPASSWORDREQ      ,                        // 重设密码请求
    MSG_SETSECONDPASSWORDACK        ,                        // 密码设置回应
    MSG_CLEARSECONDEPASSWORDREQ     ,                        // 清除二级密码请求
    MSG_CLEARSECONDEPASSWORDACK     ,                        // 清除二级密码回应
    MSG_CHECKSECONDPASSWORDREQ      ,                        // 检查二级密码请求
    MSG_CHECKSECONDPASSWORDACK      ,                        // 检查二级密码回应
    MSG_CHECKSECONDPASSWORDRESULT   ,                        // 检查密码结果
    MSG_SETPROTECTREQ               ,                        // 设置保护
    MSG_SETPROTECTACK               ,                        // 设置保护回应
    MSG_CHANGEPROTECTREQ            ,                        // 更改保护类型请求
    MSG_CHANGEPROTECTACK            ,                        // 更改保护类型回应
    GS2CS_OPERNSETPROTECTWINDOW     ,                        // 打开设置保护界面
};
//////////////////////////////////////////////////////////////////////////
struct MsgPasswordModule : public Msg
{
    MsgPasswordModule()
    {
        SetModuleType( EMessageModule_Password );   // 设置当前模块为密码模块
    }
};
// 客户端请求设置2级密码
struct MsgSetSecondPasswordReq : public MsgPasswordModule
{
    MsgSetSecondPasswordReq()
    {
        header.dwType   = MSG_SETSECONDPASSWORDREQ;
        header.stLength = sizeof( *this );
        memset( szPassword, 0, sizeof( szPassword ) );
    }

    char szPassword[ PasswordDefine::MaxLength + 1 ];
};

// 客户端请求重新设置2级密码
struct MsgReSetSecondPasswordReq : public MsgPasswordModule
{
    MsgReSetSecondPasswordReq()
    {
        header.dwType   = MSG_RESETSECONDPASSWORDREQ;
        header.stLength = sizeof( *this );
        memset( szOldPassword, 0, sizeof( szOldPassword ) );
        memset( szNewPassword, 0, sizeof( szNewPassword ) );
    }

    char szOldPassword[ PasswordDefine::MaxLength + 1 ];
    char szNewPassword[ PasswordDefine::MaxLength + 1 ];
};

// 修改密码结果
struct MsgSetSecondPasswordAck : public MsgPasswordModule
{
    MsgSetSecondPasswordAck()
    {
        header.dwType   = MSG_SETSECONDPASSWORDACK;
        header.stLength = sizeof( *this );
    }

    enum EConstDefine
    {
        SetPasswordSuccess = 0,         // 设置密码成功
        ReSetPasswordSuccess,           // 重置密码成功
        OldPasswordError,               // 原始密码错误
        PasswordFormatError,            // 密码格式错误
        AlreadyHavePassword,            // 已经有密码了
        Unknow,
    };

    uint8 uchResult;     // 返回结果
};

// 客户端请求强制清除密码
struct MsgClearSecondPasswordReq : public MsgPasswordModule
{
    MsgClearSecondPasswordReq()
    {
        header.dwType   = MSG_CLEARSECONDEPASSWORDREQ;
        header.stLength = sizeof( *this );
    }
};

// 服务器回应强制清除密码
struct MsgClearSecondPasswordAck : public MsgPasswordModule
{
    MsgClearSecondPasswordAck()
    {
        header.dwType   = MSG_CLEARSECONDEPASSWORDACK;
        header.stLength = sizeof( *this );
        uchResult = ClearSuccess;
		spareTime = 0;
    }

    enum EConstDefine
    {
        ClearSuccess = 0,       // 强制清除2级密码请求成功, 3天后自动解锁
		BUnchaining = 1,     //已经在解除中
    };

    uint8 uchResult;     // 返回结果
	DWORD spareTime;
};

// 服务器发送请求客户端验证2级密码
struct MsgCheckSecondPasswordReq : public MsgPasswordModule
{
    MsgCheckSecondPasswordReq()
    {
        header.dwType   = MSG_CHECKSECONDPASSWORDREQ;
        header.stLength = sizeof( *this );
        nClearPasswordLeftTime = 0;
    };

    //uint8 uchOperator;      // 客户端把这个回传给服务器
    uint32 nClearPasswordLeftTime;  // 密码强制解除剩余时间
};

// 客户端输入密码验证
struct MsgCheckSecondPasswordAck : public MsgPasswordModule
{
    MsgCheckSecondPasswordAck()
    {
        header.dwType   = MSG_CHECKSECONDPASSWORDACK;
        header.stLength = sizeof( *this );
        memset( szPassword, 0, sizeof( szPassword ) );
    };

    //uint8 uchOperator;      // 将MsgCheckSecondPasswordReq消息里的 uchOperator回传
    char szPassword[ PasswordDefine::MaxLength + 1 ]; 
};

// 密码不对才回返回
struct MsgCheckSecondPasswordResult : public MsgPasswordModule
{
    MsgCheckSecondPasswordResult()
    {
        header.dwType   = MSG_CHECKSECONDPASSWORDRESULT;
        header.stLength = sizeof( *this );
        uchResult = Success;
    }

    enum EConstDefine
    {
        Success = 0,        
        SecondPasswordError,       // 你输入的2级密码不正确
        SuccessAndClear,           // 验证成功,你的强制解除密码已经取消
    };

    uint8 uchResult;     // 返回结果
};

struct MsgSetProtectReq : public MsgPasswordModule
{
    MsgSetProtectReq()
    {
        header.dwType = MSG_SETPROTECTREQ;
        header.stLength = sizeof(MsgSetProtectReq);
    }
};

// 设置保护 打开设置保护界面
struct MsgSetProtectAck : public MsgPasswordModule
{
    MsgSetProtectAck()
    {
        header.dwType = MSG_SETPROTECTACK;
        header.stLength = sizeof(MsgSetProtectAck);
    }
    unsigned int nResult;   // 设置保护结果
    unsigned int nProtectFlag;  // 设置保护选项的标志位
};

struct MsgChangeProtectReq : public MsgPasswordModule
{
    MsgChangeProtectReq()
    {
        header.dwType = MSG_CHANGEPROTECTREQ;
        header.stLength = sizeof(MsgChangeProtectReq);
    }
    unsigned int nProtectFlag;  //保护标志位
    // Client发送该消息过来，Server直接保存，不返回消息给Client
};

//struct MsgChangeProtectAck : public MsgPasswordModule 
//{
//    MsgChangeProtectAck()
//    {
//        header.dwType = MSG_CHANGEPROTECTACK;
//        header.stLength = sizeof(MsgChangeProtectAck);
//    }
//    unsigned int nProtectFlag;  //
//};

struct GS2CSOpenSetProtectWindow : public MsgPasswordModule
{
    GS2CSOpenSetProtectWindow()
    {
        header.dwType = GS2CS_OPERNSETPROTECTWINDOW;
        header.stLength = sizeof( GS2CSOpenSetProtectWindow );
    }

    uint32 nPlayerID;
};

#pragma  pack(pop)
#endif