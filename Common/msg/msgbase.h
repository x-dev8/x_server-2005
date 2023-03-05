/********************************************************************
Filename:     MsgBase.h
MaintenanceMan Mail: Luo_157@hotmail.com
*********************************************************************/

#ifndef __MENETWORK_MSGBASE_H__
#define __MENETWORK_MSGBASE_H__

#pragma once

#include "MeRTLibsServer.h"

typedef int32 GameObjectId;
#define InvalidGameObjectId -1

#define MSGMAXSIZE 512

#pragma pack( push, 1 ) 

enum EMeNetworkReservedType
{
    ModuleType_None    = 0,
    CUT_MSG_CHILDBEGIN = 65535,
    CUT_MSG_CHILD      = 65534,
    INVALID_MSG_LOGIC  = CUT_MSG_CHILD,
};

enum EMsgFlag
{
    msgflag_normal   = 0     , // ��ͨ��־
    msgflag_compress = 0x1   , // ѹ����־
    msgflag_xor      = 0x1<<1, // ���ܱ�־ exclusive or ����
    msgflag_des8     = 0x1<<2, // ���ܱ�־ DES8 ����
    msgflag_blowfish = 0x1<<3, // ���ܱ�־ blowfish
};

enum ESendRange
{ //���͵�Ŀ�귶Χ
    sendrange_single       = 0,
    sendrange_view         = 1,
    sendrange_viewexceptme = 2,
    sendrange_area         = 3,
    sendrange_region       = 4,
    sendrange_stage        = 5,
    sendrange_world        = 6,
    sendrange_country      = 7,
};

enum EMsgLevel
{ //��Ϣ�ȼ� Ŀǰ�������ȼ� �� �� ��    
    // Normal����
    level_high    = 0, // ֻ�ܶ��д�С����
    level_normal  = 1, // �ܶ��д�С normal��С����
    level_low     = 2, // �ܶ��д�С normal��С���� low��С����
    level_tiptop  = 3, // ��������

    // Vip����
    level_vip     = 4, // ��������������Normal���е���
};

typedef uint8  MessageModuleType;
typedef uint32 MessageLength;
typedef uint16 MessageType;

struct MessageBaseHeader
{ // ��Ϣͷ�Ļ��� ���� 16 �ֽ� ���� 8 �ֽڶ���
    MessageBaseHeader()
    {   
        uMsgLevel  = level_high;
        cMsgFlag   = msgflag_normal;
        moduleType = ModuleType_None;
        stID       = InvalidGameObjectId;
    }

    MessageLength     stLength   ; // ��Ϣ����     4
    MessageType       dwType     ; // ��Ϣ����     2
    uint8             cMsgFlag   ; // ��Ϣ��־     1
    uint8             uMsgLevel  ; // ��Ϣ�ȼ�     1
    MessageModuleType moduleType ; // ��Ϣģ������ 1
    GameObjectId      stID       ; // ����ID       4
    uint8             reserved[3]; // �����ֶ�     3
};

#define Desc 

struct Msg
{
    MessageBaseHeader header;

    MessageLength     GetLength()     { return header.stLength  ; }
    MessageType       GetType()       { return header.dwType    ; }
    uint8             GetLevel()      { return header.uMsgLevel ; }
    MessageModuleType GetModuleType() { return header.moduleType; }

    void              SetLength    ( uint32 length    ) { header.stLength = length; }
    void              SetType      ( MessageType type ) { header.dwType = type    ; }    
    void              SetLevel     ( uint8 level      ) { header.uMsgLevel  = level     ; }
    void              SetModuleType( uint8 moduleType ) { header.moduleType = moduleType; }
    void              SetCompress  ()                   { _SET_FLAG( header.cMsgFlag , msgflag_compress); }
};

// ���Ƿ���Gateȥ����Ϣ��������һ��β��
// header.stLength += sizeof( GateMsgAdditionalData );
struct GateMsgAdditionalData
{
    char cSendRange; // ����Ŀ�귶Χ

    struct SSingle 
    { GameObjectId stSendTarget; };

    struct SView 
    { GameObjectId stSendTarget; };

    struct SArea 
    {
        uint32 dwMapId;
        short stAreaX;
        short stAreaY;
    };

    struct SState 
    { uint32 dwMapId; };

    struct SWorld 
    {
    };

    struct SCountry
    { 
        uint8 country;
        uint16 ustlevel;     // �ȼ�����
        uint16 stExceptID;   // ĳ�˲���
    };

    union
    {
        SSingle  single;
        SView    view;
        SArea    area;
        SState   stage;
        SWorld   world;
        SCountry country;
    }data;
};

struct MsgThirdParty
{
    MessageLength length; // ��Ϣ����
    MessageType   type;   // ��Ϣ����
};

struct S2SMsg : public Msg
{
    uint32 identifyId;  // CharId or ServerId
    uint32 identifyId2; // CharId or ServerId
};

struct MsgChildBegin : public Msg
{ //�ָ�����Ϣ��ͷ��
    MsgChildBegin()
    {
        header.dwType = CUT_MSG_CHILDBEGIN;
        header.stLength = sizeof( MsgChildBegin );
    }
    unsigned int nMsgSize;
    short stChildMsgNum;
};

#define DECLARE_MESSAGEENGIN_BEGIN( messageType, messageId ) \
struct messageType : public Msg \
{ \
    messageType() \
{ \
    header.dwType = messageId; \
    header.stLength = sizeof( messageType ); \
    memset( (uint8*)this + sizeof( Msg ), 0, sizeof( messageType ) - sizeof( Msg )); \
} 

#define DECLARE_MESSAGEENGIN_END( messageType ) \
};

struct MsgChild : public Msg
{ //�ָ������Ϣ
    enum EConstDefine
    { 
        CHILD_BUFSIZE = MSGMAXSIZE - sizeof( Msg ) - sizeof( short ), // ��= 512 - 16[header] - 2[stBufSize]
    };

    MsgChild()
    {
        header.dwType   = CUT_MSG_CHILD;
        header.stLength = sizeof( MsgChild );
    }

    short stBufSize;
    char  szBuf[ CHILD_BUFSIZE ];
};

struct MsgThirdPartyChildBegin : public MsgThirdParty
{ //�ָ�����Ϣ��ͷ��
    MsgThirdPartyChildBegin()
    {
        type   = CUT_MSG_CHILDBEGIN;
        length = sizeof( MsgThirdPartyChildBegin );

        nMsgSize      = 0;
        stChildMsgNum = 0;
    }

    uint32 nMsgSize;
    int16  stChildMsgNum;
};

struct MsgThirdPartyChild : public MsgThirdParty
{ //�ָ������Ϣ
    enum EChildMsg
    {
        CHILD_BUFSIZE = 490,
    };

    MsgThirdPartyChild()
    {
        type   = CUT_MSG_CHILD;
        length = sizeof( MsgThirdPartyChild );
    }

    short stBufSize;
    char  szBuf[ CHILD_BUFSIZE ];
};

#pragma pack( pop ) 

#endif // __MENETWORK_MSGBASE_H__
