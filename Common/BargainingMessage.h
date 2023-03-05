#ifndef __BARGAININTMESSAGE_H__
#define __BARGAININTMESSAGE_H__

/************************************************************************
            ��̯��Ϣ����
            MaintenanceMan Mail: lori227@live.cn
************************************************************************/
#include "MsgBase.h"
#include "BargainingDefine.h"
#include "MessageRangeDefine.h"

#pragma pack( push, 1 )

enum BargainingMessageDefine
{
    MSG_BARGAININGREQ = GAMEWORD_BARGAININGMSG_BEGIN,
    MSG_BARGAININGACK,
    MSG_BARGAININGREQUESTREQ,
    MSG_BARGAININGREQUESTACK,
    MSG_BARGAININGSTART,
    MSG_BARGAININGFINISH,
    MSG_BARGAININGSTATUS,
    MSG_BARGAININGDATAREQ,
    MSG_BARGAININGDATAACK,
    MSG_BARGAININGDATAERROR,
    MSG_SHOWBARGAININGDATA,
    MSG_BARGAININGLOCKREQ,
    MSG_BARGAININGFIXREQ,
    MSG_BARGAININGCANCELREQ,
    MSG_REMOVEBARGAININGDATAREQ,
    MSG_REMOVEBARGAININGDATAACK,
};

struct MsgBargainingModule : public Msg
{
    MsgBargainingModule()
    {
        SetModuleType( EMessageModule_Bargaining );
    }
};

// ������ĳ��ҽ���
struct MsgBargainingReq : public MsgBargainingModule
{   
    MsgBargainingReq()
    {
        header.dwType   = MSG_BARGAININGREQ;
        header.stLength = sizeof( MsgBargainingReq );
    }

    GameObjectId ustPlayerID;     // ��Ҷ�̬ID
};

// �����������
struct MsgBargainingAck : public MsgBargainingModule
{   
    MsgBargainingAck()
    {
        header.dwType   = MSG_BARGAININGACK;
        header.stLength = sizeof( MsgBargainingAck );
    }

    unsigned char uchResult;
};

// ֪ͨ�ͻ���, ĳ���������㽻��
struct MsgBargainingRequestReq : public MsgBargainingModule
{   
    MsgBargainingRequestReq()
    {
        header.dwType   = MSG_BARGAININGREQUESTREQ;
        header.stLength = sizeof( MsgBargainingRequestReq );
    }

    GameObjectId ustPlayerID;     // ��Ҷ�̬ID
};

// �Է���Ӧ�Ƿ�ͬ�⽻��
struct MsgBargainingRequestAck : public MsgBargainingModule
{   
    MsgBargainingRequestAck()
    {
        header.dwType   = MSG_BARGAININGREQUESTACK;
        header.stLength = sizeof( MsgBargainingRequestAck );
    }

    bool bBargainintAgree;
};

// ֪ͨ�ͻ���  ��ĳ�˵Ľ��׿�ʼ
struct MsgBargainingStart : public MsgBargainingModule
{   
    MsgBargainingStart()
    {
        header.dwType   = MSG_BARGAININGSTART;
        header.stLength = sizeof( MsgBargainingStart );
    }

    GameObjectId ustPlayerID;     // ��Ҷ�̬ID
};

// ֪ͨ�ͻ���  ���׽���
struct MsgBargainingFinish : public MsgBargainingModule
{   
    MsgBargainingFinish()
    {
        header.dwType   = MSG_BARGAININGFINISH;
        header.stLength = sizeof( MsgBargainingFinish );
    }

    unsigned char uchFinishType;
};

// ֪ͨ�ͻ��� ĳ��ҵĽ���״̬
struct MsgBargainingStatus : public MsgBargainingModule
{   
    MsgBargainingStatus()
    {
        header.dwType   = MSG_BARGAININGSTATUS;
        header.stLength = sizeof( MsgBargainingStatus );
    }

    GameObjectId ustPlayerID;     // ��Ҷ�̬ID
    unsigned char uchStatus;
};

// ����������������з�Ǯ ���߷���Ʒ
struct MsgBargainingDataReq : public MsgBargainingModule
{
    MsgBargainingDataReq()
    {
        header.dwType   = MSG_BARGAININGDATAREQ;
        header.stLength = sizeof( MsgBargainingDataReq );
    }

    unsigned char uchBargainintType;    // �������� ...BargainingMoney...

    // ��Ϸ��, ��ʹ���������
    unsigned int nBargainingValue;      // ���׵���ֵ
    
    // ������ ʹ����4������
    unsigned char uchBargainingIndex;  // ����������
    unsigned char uchBagType;          // ��������
    unsigned char uchIndex;            // ��������
    __int64 n64Guid;                   // ��Ʒguid
};

// ֪ͨ��Ҽ�������Ʒ����������
struct MsgBargainingDataAck : public MsgBargainingModule
{
    MsgBargainingDataAck()
    {
        header.dwType   = MSG_BARGAININGDATAACK;
        header.stLength = sizeof( MsgBargainingDataAck );
    }

    unsigned char uchBargainintType;    // �������� ...BargainingMoney.��..

    // ��Ϸ��, ��ʹ���������
    unsigned int nBargainingValue;      // ���׵���ֵ

    // ������ ʹ����3������
    unsigned char uchBargainingIndex;  // ����������
    unsigned char uchBagType;          // ��������
    unsigned char uchIndex;            // ��������
    __int64 n64Guid;                   // ��Ʒguid
};

// ֪ͨ�ͻ��˽�����Ʒ�ĸ������
struct MsgBargainingDataError : public MsgBargainingModule
{
    MsgBargainingDataError()
    {
        header.dwType   = MSG_BARGAININGDATAERROR;
        header.stLength = sizeof( MsgBargainingDataError );
    }

    GameObjectId ustPlayerID;     // ��Ҷ�̬ID
    unsigned char uchResult;        // ��������
};

// ֪ͨ�Է���ҽ��׵�����
struct MsgShowBargainingData : public MsgBargainingModule
{
    MsgShowBargainingData()
    {
        header.dwType   = MSG_SHOWBARGAININGDATA;
        header.stLength = sizeof( MsgShowBargainingData ) - sizeof( szBargainingData );

        memset( szBargainingData, 0, sizeof( szBargainingData ) );
    }

    unsigned char uchBargainintType;    // �������� ...BargainingMoney...
    unsigned int nBargainingValue;      // ���׵���ֵ( ��Ǯ, ��ʹ��������� )
    unsigned char uchBargainingIndex;   // ����������
    char szBargainingData[ BargainingDefine::DataLength ];  // ���׵�����

    void AddBargainingData( void* pData, int nSize )
    {
        if ( pData == NULL || nSize > sizeof( szBargainingData ) )
        { return; }

        memcpy_s( szBargainingData, sizeof( szBargainingData ), pData, nSize );
        header.stLength += nSize;
    }
};

// ��������
struct MsgBargainingLockReq : public MsgBargainingModule
{
    MsgBargainingLockReq()
    {
        header.dwType   = MSG_BARGAININGLOCKREQ;
        header.stLength = sizeof( MsgBargainingLockReq );
    }
};

// ������ȷ��
struct MsgBargainingFixReq : public MsgBargainingModule
{
    MsgBargainingFixReq()
    {
        header.dwType   = MSG_BARGAININGFIXREQ;
        header.stLength = sizeof( MsgBargainingFixReq );
    }
};

// �����������
struct MsgBargainingCancelReq : public MsgBargainingModule
{
    MsgBargainingCancelReq()
    {
        header.dwType   = MSG_BARGAININGCANCELREQ;
        header.stLength = sizeof( MsgBargainingCancelReq );
    }
};


// �����Ƴ�������Ʒ, ( ������, ȷ��״̬��, �����Ƴ�, �ͻ��˲��ܷ���Ϣ )
struct MsgRemoveBargainingDataReq : public MsgBargainingModule
{
    MsgRemoveBargainingDataReq()
    {
        header.dwType   = MSG_REMOVEBARGAININGDATAREQ;
        header.stLength = sizeof( MsgRemoveBargainingDataReq );
    }

    unsigned char uchBargainingIndex;
};

// ��Ӧ�Ƴ�������Ʒ, �ͻ���ɾ����λ�õ���Ʒ
struct MsgRemoveBargainingDataAck : public MsgBargainingModule
{
    MsgRemoveBargainingDataAck()
    {
        header.dwType   = MSG_REMOVEBARGAININGDATAACK;
        header.stLength = sizeof( MsgRemoveBargainingDataAck );
    }

    GameObjectId ustPlayerID;
    unsigned char uchBargainingIndex;
};

#pragma pack( pop )

#endif