#ifndef __PASSWORDMESSAGE_H__
#define __PASSWORDMESSAGE_H__
/******************************************************
        �Ʋ�������Ϣ����
        Author:eliteYang
******************************************************/

#include "MsgBase.h"
#include "PasswordDefine.h"
#include "MessageRangeDefine.h"

#pragma pack(push, 1)

enum PasswordMessageDefine
{

    MSG_SETSECONDPASSWORDREQ = GAMEWORLD_PASSWORD_BEGIN,     // ������������
    MSG_RESETSECONDPASSWORDREQ      ,                        // ������������
    MSG_SETSECONDPASSWORDACK        ,                        // �������û�Ӧ
    MSG_CLEARSECONDEPASSWORDREQ     ,                        // ���������������
    MSG_CLEARSECONDEPASSWORDACK     ,                        // ������������Ӧ
    MSG_CHECKSECONDPASSWORDREQ      ,                        // ��������������
    MSG_CHECKSECONDPASSWORDACK      ,                        // �����������Ӧ
    MSG_CHECKSECONDPASSWORDRESULT   ,                        // ���������
    MSG_SETPROTECTREQ               ,                        // ���ñ���
    MSG_SETPROTECTACK               ,                        // ���ñ�����Ӧ
    MSG_CHANGEPROTECTREQ            ,                        // ���ı�����������
    MSG_CHANGEPROTECTACK            ,                        // ���ı������ͻ�Ӧ
    GS2CS_OPERNSETPROTECTWINDOW     ,                        // �����ñ�������
};
//////////////////////////////////////////////////////////////////////////
struct MsgPasswordModule : public Msg
{
    MsgPasswordModule()
    {
        SetModuleType( EMessageModule_Password );   // ���õ�ǰģ��Ϊ����ģ��
    }
};
// �ͻ�����������2������
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

// �ͻ���������������2������
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

// �޸�������
struct MsgSetSecondPasswordAck : public MsgPasswordModule
{
    MsgSetSecondPasswordAck()
    {
        header.dwType   = MSG_SETSECONDPASSWORDACK;
        header.stLength = sizeof( *this );
    }

    enum EConstDefine
    {
        SetPasswordSuccess = 0,         // ��������ɹ�
        ReSetPasswordSuccess,           // ��������ɹ�
        OldPasswordError,               // ԭʼ�������
        PasswordFormatError,            // �����ʽ����
        AlreadyHavePassword,            // �Ѿ���������
        Unknow,
    };

    uint8 uchResult;     // ���ؽ��
};

// �ͻ�������ǿ���������
struct MsgClearSecondPasswordReq : public MsgPasswordModule
{
    MsgClearSecondPasswordReq()
    {
        header.dwType   = MSG_CLEARSECONDEPASSWORDREQ;
        header.stLength = sizeof( *this );
    }
};

// ��������Ӧǿ���������
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
        ClearSuccess = 0,       // ǿ�����2����������ɹ�, 3����Զ�����
		BUnchaining = 1,     //�Ѿ��ڽ����
    };

    uint8 uchResult;     // ���ؽ��
	DWORD spareTime;
};

// ��������������ͻ�����֤2������
struct MsgCheckSecondPasswordReq : public MsgPasswordModule
{
    MsgCheckSecondPasswordReq()
    {
        header.dwType   = MSG_CHECKSECONDPASSWORDREQ;
        header.stLength = sizeof( *this );
        nClearPasswordLeftTime = 0;
    };

    //uint8 uchOperator;      // �ͻ��˰�����ش���������
    uint32 nClearPasswordLeftTime;  // ����ǿ�ƽ��ʣ��ʱ��
};

// �ͻ�������������֤
struct MsgCheckSecondPasswordAck : public MsgPasswordModule
{
    MsgCheckSecondPasswordAck()
    {
        header.dwType   = MSG_CHECKSECONDPASSWORDACK;
        header.stLength = sizeof( *this );
        memset( szPassword, 0, sizeof( szPassword ) );
    };

    //uint8 uchOperator;      // ��MsgCheckSecondPasswordReq��Ϣ��� uchOperator�ش�
    char szPassword[ PasswordDefine::MaxLength + 1 ]; 
};

// ���벻�ԲŻط���
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
        SecondPasswordError,       // �������2�����벻��ȷ
        SuccessAndClear,           // ��֤�ɹ�,���ǿ�ƽ�������Ѿ�ȡ��
    };

    uint8 uchResult;     // ���ؽ��
};

struct MsgSetProtectReq : public MsgPasswordModule
{
    MsgSetProtectReq()
    {
        header.dwType = MSG_SETPROTECTREQ;
        header.stLength = sizeof(MsgSetProtectReq);
    }
};

// ���ñ��� �����ñ�������
struct MsgSetProtectAck : public MsgPasswordModule
{
    MsgSetProtectAck()
    {
        header.dwType = MSG_SETPROTECTACK;
        header.stLength = sizeof(MsgSetProtectAck);
    }
    unsigned int nResult;   // ���ñ������
    unsigned int nProtectFlag;  // ���ñ���ѡ��ı�־λ
};

struct MsgChangeProtectReq : public MsgPasswordModule
{
    MsgChangeProtectReq()
    {
        header.dwType = MSG_CHANGEPROTECTREQ;
        header.stLength = sizeof(MsgChangeProtectReq);
    }
    unsigned int nProtectFlag;  //������־λ
    // Client���͸���Ϣ������Serverֱ�ӱ��棬��������Ϣ��Client
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