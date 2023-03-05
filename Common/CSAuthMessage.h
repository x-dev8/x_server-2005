//���������
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
struct MsgCheckCSAuthReq : public MsgCSAuthModule//���������͵��ͻ��˵���֤��
{
    MsgCheckCSAuthReq()
    {
        header.dwType = MSG_CHECKCSAUTHREQ;
        header.stLength = sizeof( MsgCheckCSAuthReq );
    }
	unsigned int PlayerID;
	unsigned int size;
	BYTE packet[4096];//��֤����
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
	BYTE packet[4096];//��֤����
};