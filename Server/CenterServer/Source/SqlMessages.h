#ifndef __CENTERSERVER_SQLMESSAGES_H__
#define __CENTERSERVER_SQLMESSAGES_H__

#pragma once

#include "Memory_Pool.h"
#include "PlatformMessageDefine.h"
#include "CenterGameMessage.h"
#include "CountryMessage.h"
#include "RelationMessage.h"
#include "GuildMessage.h"
#include "ConsignmentMessage.h"
#include "SystemVarMessage.h"
#include "FamilyMessage.h"
#include "LevelLimitMessage.h"
#include "GlobalDBMessage.h"
//xuda #include "EmperorMessage.h"
//xuda #include "WantedMessage.h"
#include "QuestEntrustMessage.h"
#include "GameBattleMessage.h"
#pragma pack ( push, 1 )

union ReadCharData
{
    BYTE*   byte;
    bool*   boolean;
    int*    i;
    DWORD*  dw;
    char*   c;
    void*   p;
    float*  f;
    short*  s;

    ReadCharData(void* in) :p(in)
    {}
};

bool CheckString( const std::string& strName ); // 返回false 不合法
const char*   BigInt2String( __int64 nInt);
const __int64 String2BigInt( const char* szBigInt);

// 编码函数（用于二进制人物数据编码成可视字符串方便数据库存储）
// pDec : 存放编码过后的字串地址 pSrc : 需要进行编码的二进制数值地址
// 返回值: 编码过后的pDec字串长度
int EnCodeToString(const unsigned char* pszSrc, char *pszDest, size_t nSrcLen, size_t nDestLen);

// 解码函数（用于从数据库中载入可视字符串还原成二进制人物数据）
// pDec : 存放解码过后的二进制数值地址 pSrc : 需要进行解码的字符串地址
// 返回值: 解码过后的pDec二进制数值长度
int    DeCodeFromString(const uint8* pszSrc, char* pszDest,  size_t nDestLen);
uint32 DeCodeToBuffer  (const int8* pszSrc,  uint8* pszDest, size_t nDestLen);

extern int G_PrinfInfo;
#define  NOPRINT 0
#define  PRINTFQUEUESIZE 1
#define  PRINTFSAVEROLETIME 2

#define TRYBEGIN  try {

#define TRYEND } \
    catch (mysqlpp::BadQuery er) \
    { \
        int errCode = er.errnum(); \
        LOG_MESSAGE( SQLOBJECT, LOG_PRIORITY_ERROR,"BadQuery [%s:%d] Error:%s",szSql, errCode, er.what()); \
        result = ER_Failed; \
        if (errCode == 2013 || errCode == 2006) \
        { result = ER_SystemException; }\
    } \
        catch (const mysqlpp::BadConversion& er)  \
    { \
        LOG_MESSAGE( SQLOBJECT, LOG_PRIORITY_ERROR,"BadConversion [%s] Error:%s retrieved data size:%d, actual size:%d",szSql,er.what(), er.retrieved, er.actual_size); \
        result = ER_Failed; \
    } \
    catch (const mysqlpp::Exception& er) \
    { \
        LOG_MESSAGE( SQLOBJECT, LOG_PRIORITY_ERROR,"mysqlpp::Exception [%s] Error:%s",szSql, er.what()); \
        result = ER_Failed; \
    }\
    catch(exception &er) \
    { \
        LOG_MESSAGE( SQLOBJECT, LOG_PRIORITY_ERROR,"std::exception [%s] Error:%s",szSql, er.what()); \
        result = ER_Failed; \
    }

#define FREESTOREPROCEDURE_TRY \
    try \
    { \
        while(mysqlQuery.more_results()) \
    { mysqlQuery.store_next(); } \
    } \
    catch ( ... ) \
    { }

#define FREESTOREPROCEDURE \
    while(mysqlQuery.more_results()) \
        { mysqlQuery.store_next(); } \

#define CHECK_RESULT \
    if ( ER_SystemException == result ) \
    { \
        _workState = SS_ReConnected; \
        while( _workState == SS_ReConnected) \
        { \
            _TryConnectToSqlDb(); \
            Sleep(20);\
        }\
        result = ER_Success; \
        goto Begin; \
    }

// Z_OK Z_BUF_ERROR Z_DATA_ERROR 
#define CHECK_ZIP_UNZIP_RESULT( code ) \
    int result = code; \
    if ( result != Z_OK ) \
    { \
        LOG_MESSAGE( SQLOBJECT, LOG_PRIORITY_ERROR, "%s [%d]", #code, result ); \
        return;\
    }

#define CHECK_BUFFER_OVERFLOW( activeSize, bufferSize ) \
    if ( activeSize > bufferSize ) \
    { \
        LOG_MESSAGE( SQLOBJECT, LOG_PRIORITY_CRITICAL, "[%s][%s]", __FUNCTION__, __LINE__ ); \
        return;\
    }

#define CHECK_LOAD( result ) \
    if ( !result ) \
    { \
        LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_ERROR, "[%s][%s]", __FUNCTION__, __LINE__ ); \
        return; \
    }

#define CHECK_SQL_RESULT( result ) \
    if ( RESULT_FAILED(result)) \
    { return; }

//////////////////////////////////////////////////////////////////////////
class BaseSqlMessage
{
public:
    BaseSqlMessage(): nClientId( -1 ), type( ErrorUnsignedShortID ), time(0){}

public:
    int32       nClientId; // 消息发起者
    MessageType type;      // 消息类型
    uint32      time;      // 时间搓
    virtual void   Release()          {             }
    virtual void*  GetMessageAddress(){ return NULL;}
    virtual uint32 GetMessageSize()   { return 0;   }
};

#define DECLARE_SQLMESSAGE(xDbMsg)   \
    DECLARE_SQLMESSAGE_BEGIN(xDbMsg) \
    DECLARE_SQLMESSAGE_END(xDbMsg)   \
    
#define DECLARE_SQLMESSAGE_BEGIN(xDbMsg) \
class SqlMessage##xDbMsg : public BaseSqlMessage, INHERIT_POOL_PARAM(SqlMessage##xDbMsg, 50) \
{ \
public: \
    static  BaseSqlMessage* CreateInstance()    { return MES_NEW(SqlMessage##xDbMsg); } \
    virtual void            Release()           { MES_DELETE(SqlMessage##xDbMsg); } \
    virtual void*           GetMessageAddress() { return &msg;        } \
    virtual uint32          GetMessageSize()    { return sizeof(msg); } \
public: \
    xDbMsg msg;

#define DECLARE_SQLMESSAGE_END(xDbMsg) \
};

#define SQLMSGCLASS(xDbMsg) SqlMessage##xDbMsg

// 物品掉落
DECLARE_SQLMESSAGE(CS2DBSaveItemDropControl )
DECLARE_SQLMESSAGE(CS2DBItemDropControlReq  )
DECLARE_SQLMESSAGE(DB2CSItemDropControl     )

// 物品添加
DECLARE_SQLMESSAGE( MsgPFAddItemReq  )
DECLARE_SQLMESSAGE( MsgPFAddItemAck  )

// 邮件
DECLARE_SQLMESSAGE( GS2CSMailListReq         )
DECLARE_SQLMESSAGE( CS2GSMailListAck         )
DECLARE_SQLMESSAGE( GS2CSQueryMailCanSendReq )
DECLARE_SQLMESSAGE( CS2GSQueryMailCanSendAck )
DECLARE_SQLMESSAGE( GS2CSSendMailReq         )
DECLARE_SQLMESSAGE( CS2GSSendMailAck         )
DECLARE_SQLMESSAGE( GS2CSOpMailReq           )
DECLARE_SQLMESSAGE( CS2GSOpMailAck           )

// 国家
DECLARE_SQLMESSAGE( CS2DBRequestCountryDataReq )
DECLARE_SQLMESSAGE( DB2CSRequestCountryDataAck )
DECLARE_SQLMESSAGE( CS2DBCountryDataSaveReq    )
DECLARE_SQLMESSAGE( CS2DBCountryOfficeReq    )
DECLARE_SQLMESSAGE( DB2CSRequestCountryOfficeAck )
DECLARE_SQLMESSAGE( DB2CSRequestCountryInfoAck )
DECLARE_SQLMESSAGE( CS2DBRequestCountryInfoReq )
// 关系
DECLARE_SQLMESSAGE( CS2DBRelationListReq       )
DECLARE_SQLMESSAGE( CS2DBAddRelationReq        )
DECLARE_SQLMESSAGE( CS2DBAddAttributeReq       )
DECLARE_SQLMESSAGE( CS2DBUpdateAttributeReq    )
DECLARE_SQLMESSAGE( DB2CSRelationAttributeList )
DECLARE_SQLMESSAGE( DB2CSRelationDataList      )
DECLARE_SQLMESSAGE( GS2CSQueryAttributeReq     )
DECLARE_SQLMESSAGE( DB2CSQueryAttributeAck     )
DECLARE_SQLMESSAGE( CS2DBUpdateRelationGroup   )
DECLARE_SQLMESSAGE( CS2DBUpdateRelationDataReq )

// 帮派
DECLARE_SQLMESSAGE( CS2DBGuildDataLoadReq     )
DECLARE_SQLMESSAGE( DB2CSGuildDataList        )
DECLARE_SQLMESSAGE( DB2CSGuildMemberList      )
DECLARE_SQLMESSAGE( CS2DBGuildDataUpdateReq   )
DECLARE_SQLMESSAGE( CS2DBGuildMemberUpdateReq )
DECLARE_SQLMESSAGE( CS2DBGuildDisbandReq      )
DECLARE_SQLMESSAGE( CS2DBGuildMemberLeaveReq  )

// 家族
DECLARE_SQLMESSAGE( CS2DBFamilyDataLoadReq		)
DECLARE_SQLMESSAGE( CS2DBFamilyDataUpdateReq	)
DECLARE_SQLMESSAGE( CS2DBFamilyMemberUpdateReq	)
DECLARE_SQLMESSAGE( CS2DBFamilyMemberLeaveReq	)
DECLARE_SQLMESSAGE( CS2DBFamilyDisbandReq		)
DECLARE_SQLMESSAGE( DB2CSFamilyDataList			)
DECLARE_SQLMESSAGE( DB2CSFamilyMemberList		)

// 寄售
DECLARE_SQLMESSAGE( CS2DBLoadConsignmentDataReq     )
DECLARE_SQLMESSAGE( CS2DBOperateMoneyReq            )
DECLARE_SQLMESSAGE( DB2CSOperateMoneyAck            )
DECLARE_SQLMESSAGE( CS2DBConsignmentMoneyReq        )
DECLARE_SQLMESSAGE( CS2DBConsignmentmoneyOperateReq )
DECLARE_SQLMESSAGE( DB2CSConsignmentmoneyOperateAck )
DECLARE_SQLMESSAGE( DB2CSLoadConsignmentAccount     )
DECLARE_SQLMESSAGE( DB2CSLoadConsignmentMoneyList   )
DECLARE_SQLMESSAGE( DB2CSLoadConsignmentHistroy     )

// 保存系统变量
DECLARE_SQLMESSAGE( CS2DBSaveSystemVarReq  )
DECLARE_SQLMESSAGE( CS2DBLoadSystemVarReq  )
DECLARE_SQLMESSAGE( DB2CSLoadSysVarSuccess )
DECLARE_SQLMESSAGE( DB2CSLoadSystemVarAck  )

// 平台
//DECLARE_SQLMESSAGE( P2CSAddPayReq  )
//DECLARE_SQLMESSAGE( CS2PAddPayAck  )

// 个人资料
DECLARE_SQLMESSAGE( CS2DBUpdatePersonalInfoReq )
DECLARE_SQLMESSAGE( GS2CSFindPersonReq )

// 防沉迷
DECLARE_SQLMESSAGE( GS2CSUpdateAntiaddictionInfoReq )
DECLARE_SQLMESSAGE( CS2GSUpdateAntiaddictionInfoAck )

//等级封印
DECLARE_SQLMESSAGE( MsgReqMYSQLData )
DECLARE_SQLMESSAGE( MsgAckMySQLData )
DECLARE_SQLMESSAGE( MsgAddLevelLimit )
DECLARE_SQLMESSAGE( MsgUpdateLevelLimit )

//全局变量
DECLARE_SQLMESSAGE(GS2CSLoadGlobalDBReq)
DECLARE_SQLMESSAGE(GS2CSSaveGlobalDBReq)
DECLARE_SQLMESSAGE(GS2CSLoadGlobalDBAck)

//xuda 
//皇帝
/*DECLARE_SQLMESSAGE(CS2DBRequestEmperorDataReq)

//通缉令
DECLARE_SQLMESSAGE( CS2DBRequestWantedDataReq)
DECLARE_SQLMESSAGE( DBS2CSRequestWantedDataAck)

DECLARE_SQLMESSAGE( CS2DBWantedInsertReq)
DECLARE_SQLMESSAGE( CS2DBWantedDeleteReq)
DECLARE_SQLMESSAGE( CS2DBWantedDataSaveReq)*/

//任务委托
DECLARE_SQLMESSAGE( CS2DBRequestQuestEntrustDataReq)
DECLARE_SQLMESSAGE( CS2DBAddQuestEntrustDataAck)
DECLARE_SQLMESSAGE( CS2DBQuestEntrustDeleteReq)
DECLARE_SQLMESSAGE( CS2DBQuestEntrustDataSaveReq)
DECLARE_SQLMESSAGE( DBS2CSRequestQuestEntrustDataAck)
//战场数据
DECLARE_SQLMESSAGE(CS2DBLoadCampBattleData)
DECLARE_SQLMESSAGE(DB2CSLoadCampBattleData)
DECLARE_SQLMESSAGE(CS2DBAddCampBattleData)
DECLARE_SQLMESSAGE(CS2DBDelCampBattleData)

//////////////////////////////////////////////////////////////////////////
#define theSqlMessageManager SqlMessageManager::GetInstance()

class SqlMessageManager
{
public:    
    static SqlMessageManager& GetInstance();
    BaseSqlMessage* Get3PartySqlMessageByDbMsg( Msg* pMsg );   // 生成对应的SqlMessage
	BaseSqlMessage* GetSqlMessageByDbMsg( Msg* pMsg );                   // 生成对应的SqlMessage
    bool            FreeSqlMessage      ( BaseSqlMessage* pSqlMessage ); // 释放SqlMessage
};

#pragma pack ( pop )

#endif // __CENTERSERVER_SQLMESSAGES_H__
