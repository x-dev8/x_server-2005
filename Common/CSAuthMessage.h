//反外挂命令
#pragma once
#include "MsgBase.h"
#include "MessageRangeDefine.h"
enum CSAuthMessageDefine
{
	MSG_CHECKCSAUTHREQ = CSAUTH_BEGIN,
	MSG_CHECKCSAUTHACK,
};
struct MsgCSAuthModule : public Msg
{
    MsgCSAuthModule()
    {
        SetModuleType( EMessageModule_CSAuth );
    }
};
struct MsgCheckCSAuthReq : public MsgCSAuthModule//服务器发送到客户端的验证码
{
    MsgCheckCSAuthReq()
    {
        header.dwType = MSG_CHECKCSAUTHREQ;
        header.stLength = sizeof( MsgCheckCSAuthReq );
    }
	unsigned int PlayerID;
	unsigned int size;
	BYTE packet[4096];//验证数据
};
struct MsgCheckCSAuthAck : public MsgCSAuthModule
{
    MsgCheckCSAuthAck()
    {
        header.dwType = MSG_CHECKCSAUTHACK;
        header.stLength = sizeof( MsgCheckCSAuthAck );
    }
	unsigned int PlayerID;
	unsigned int size;
	BYTE packet[4096];//验证数据
};