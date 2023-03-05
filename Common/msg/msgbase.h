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
    msgflag_normal   = 0     , // 普通标志
    msgflag_compress = 0x1   , // 压缩标志
    msgflag_xor      = 0x1<<1, // 加密标志 exclusive or 加密
    msgflag_des8     = 0x1<<2, // 加密标志 DES8 加密
    msgflag_blowfish = 0x1<<3, // 加密标志 blowfish
};

enum ESendRange
{ //发送的目标范围
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
{ //消息等级 目前分三个等级 高 中 低    
    // Normal队列
    level_high    = 0, // 只受队列大小控制
    level_normal  = 1, // 受队列大小 normal大小控制
    level_low     = 2, // 受队列大小 normal大小控制 low大小控制
    level_tiptop  = 3, // 不受限制

    // Vip队列
    level_vip     = 4, // 不受限制优先与Normal队列到达
};

typedef uint8  MessageModuleType;
typedef uint32 MessageLength;
typedef uint16 MessageType;

struct MessageBaseHeader
{ // 消息头的基本 凑足 16 字节 保持 8 字节对齐
    MessageBaseHeader()
    {   
        uMsgLevel  = level_high;
        cMsgFlag   = msgflag_normal;
        moduleType = ModuleType_None;
        stID       = InvalidGameObjectId;
    }

    MessageLength     stLength   ; // 消息长度     4
    MessageType       dwType     ; // 消息类型     2
    uint8             cMsgFlag   ; // 消息标志     1
    uint8             uMsgLevel  ; // 消息等级     1
    MessageModuleType moduleType ; // 消息模块类型 1
    GameObjectId      stID       ; // 代表ID       4
    uint8             reserved[3]; // 保留字段     3
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

// 凡是发到Gate去的消息都，附加一个尾巴
// header.stLength += sizeof( GateMsgAdditionalData );
struct GateMsgAdditionalData
{
    char cSendRange; // 发送目标范围

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
        uint16 ustlevel;     // 等级限制
        uint16 stExceptID;   // 某人不发
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
    MessageLength length; // 消息长度
    MessageType   type;   // 消息类型
};

struct S2SMsg : public Msg
{
    uint32 identifyId;  // CharId or ServerId
    uint32 identifyId2; // CharId or ServerId
};

struct MsgChildBegin : public Msg
{ //分割后的消息的头部
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
{ //分割的子消息
    enum EConstDefine
    { 
        CHILD_BUFSIZE = MSGMAXSIZE - sizeof( Msg ) - sizeof( short ), // ～= 512 - 16[header] - 2[stBufSize]
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
{ //分割后的消息的头部
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
{ //分割的子消息
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
