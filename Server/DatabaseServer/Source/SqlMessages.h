#ifndef __DATABASE_SQLQUERYS_H__
#define __DATABASE_SQLQUERYS_H__

#pragma once

#include "Mutex.h"
#include "DBMessageDefine.h"
#include "CenterDataBaseMessage.h"
#include "Memory_Pool.h"

#pragma pack ( push, 1 )

enum EItemBagPos 
{
    e_CharBag     = 0,
    e_StroageBag  = 1,
    e_VisualBag   = 2,
    e_MaterialBag = 3,
    e_TaskBag     = 4,
    e_NpcBag      = 5,
    e_Max
};

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

struct GMINFO
{
    uint32 nLevel;
    int8   szIP[20];
};

extern int G_PrinfInfo;
#define  NOPRINT 0
#define  PRINTFQUEUESIZE 1
#define  PRINTFSAVEROLETIME 2
#define  DEBUGPRINTQUEUESIZE 100

void DebugLogMsg(const char* szText);               // 日志输出函数
const char*   BigInt2String( __int64 nInt);
const __int64 String2BigInt( const char* szBigInt);

// 编码函数（用于二进制人物数据编码成可视字符串方便数据库存储）
// pDec : 存放编码过后的字串地址 pSrc : 需要进行编码的二进制数值地址
// 返回值: 编码过后的pDec字串长度
int EnCodeToString(const unsigned char *pszSrc, char *pszDest, size_t nSrcLen, size_t nDestLen);

// 解码函数（用于从数据库中载入可视字符串还原成二进制人物数据）
// pDec : 存放解码过后的二进制数值地址 pSrc : 需要进行解码的字符串地址
// 返回值: 解码过后的pDec二进制数值长度
int    DeCodeFromString(const uint8* pszSrc, char* pszDest,  size_t nDestLen);
uint32 DeCodeToBuffer  (const int8* pszSrc,  uint8* pszDest, size_t nDestLen);

#define TRYBEGIN  try {

#define TRYEND } \
    catch (mysqlpp::BadQuery er) \
    { \
        LOG_MESSAGE( SQLOBJECT, LOG_PRIORITY_ERROR,"BadQuery [%s] Error:%s",szSql, er.what()); \
        result = ER_Failed; \
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

#define CHECK_SQL_RESULT_RETURN( result ) \
    if ( RESULT_FAILED(result)) \
    { return result; }
//////////////////////////////////////////////////////////////////////////
class BaseSqlMessage
{
public:
    BaseSqlMessage(): nClientId( -1 ), type( ErrorUnsignedShortID ), time(0){}

    virtual void   Release()          {             }
    virtual void*  GetMessageAddress(){ return NULL;}
    virtual uint32 GetMessageSize()   { return 0;   }

public:
    int32       nClientId; // 消息发起者
    MessageType type;      // 消息类型
    uint32      time;      // 时间搓
};

#define SQLMSGCLASS( xDbMsg ) SqlMessage##xDbMsg
    
#define DECLARE_SQLMESSAGE_BEGIN(xDbMsg) \
class SQLMSGCLASS( xDbMsg ) : public BaseSqlMessage, INHERIT_POOL_PARAM( SQLMSGCLASS( xDbMsg ), 50 ) \
{ \
public: \
    DECLARE_POOL_FUNC( SQLMSGCLASS( xDbMsg ) ); \
    virtual void*  GetMessageAddress() { return &msg;        } \
    virtual uint32 GetMessageSize()    { return sizeof(msg); } \
public: \
    xDbMsg msg;

#define DECLARE_SQLMESSAGE_END( xDbMsg ) \
};

#define DECLARE_SQLMESSAGE( xDbMsg )   \
    DECLARE_SQLMESSAGE_BEGIN( xDbMsg ) \
    DECLARE_SQLMESSAGE_END( xDbMsg )


DECLARE_SQLMESSAGE(DBMsgSaveCharacter)
DECLARE_SQLMESSAGE(DBMsgEnterWorld)
DECLARE_SQLMESSAGE(DBMsgQueryAccountChar)
DECLARE_SQLMESSAGE(DBMsgOffline2)
DECLARE_SQLMESSAGE(DBMsgCreateHeroChar)
DECLARE_SQLMESSAGE(DBMsgReqCreateCheckName)
DECLARE_SQLMESSAGE(DBMsgDeleteChar2)
DECLARE_SQLMESSAGE(DBMsgCancelDelChar)
DECLARE_SQLMESSAGE(DBMsgReqStorage)


DECLARE_SQLMESSAGE(DBMsgReqAccountBilling)
DECLARE_SQLMESSAGE(DBMsgReqAccountBillingOp)
DECLARE_SQLMESSAGE(CS2DBAccountPoints)
DECLARE_SQLMESSAGE(DBMsgAckAccountBilling)
DECLARE_SQLMESSAGE(DB2CSAccountPoints)

DECLARE_SQLMESSAGE(DBMsgShopping)
DECLARE_SQLMESSAGE(DBMsgOperateAccountMoney)
DECLARE_SQLMESSAGE(DBMsgSetBillingMoney)
DECLARE_SQLMESSAGE(DBMsgOperateAccountConsumeScore) //lyh++
DECLARE_SQLMESSAGE(DBMsgSetConsumeScore)
DECLARE_SQLMESSAGE(DB2DBConsumeScore)
DECLARE_SQLMESSAGE(DB2DBConsumeScoreResult)
DECLARE_SQLMESSAGE(DB2DBCash)
DECLARE_SQLMESSAGE(DB2DBCashResult)
//////////////////////////////////////////////////////////////////////////
DECLARE_SQLMESSAGE(DBMsgAckCreateCheckName)
DECLARE_SQLMESSAGE(DBMsgCreateCharAck)
DECLARE_SQLMESSAGE(DBMsgAckCharInfo)
DECLARE_SQLMESSAGE(DBMsgEndAckChar)
DECLARE_SQLMESSAGE(DBMsgAckEnterWorld)
DECLARE_SQLMESSAGE(MsgAckResult)
DECLARE_SQLMESSAGE(DBAckOperSucc)
DECLARE_SQLMESSAGE(DBMsgAckDeleteChar2)
DECLARE_SQLMESSAGE(DBMsgAckCancelDelChar)

DECLARE_SQLMESSAGE(DBAccountWallowInfoReq)
DECLARE_SQLMESSAGE(DBAccountWallowInfoAck)
DECLARE_SQLMESSAGE(DBAccountWallowInfoSave)

DECLARE_SQLMESSAGE(MsgRegisterServerAck)
DECLARE_SQLMESSAGE(MsgServerStatusAck)

DECLARE_SQLMESSAGE(DBMsgJiFengShopItemsListReq)
DECLARE_SQLMESSAGE(DBMsgJiFengShopItemsListAck)
DECLARE_SQLMESSAGE(DBMsgJiFengShopItemsGainReq)
DECLARE_SQLMESSAGE(DBMsgJiFengShopItemsGainAck)

DECLARE_SQLMESSAGE(DB2DBNotifyFileDBSaveChar)

DECLARE_SQLMESSAGE(DBMsgPetBreedQueryReq)
DECLARE_SQLMESSAGE(DBMsgPetBreedQueryAck)

DECLARE_SQLMESSAGE(DBMsgChangeNameReq)
DECLARE_SQLMESSAGE(DBMsgChangeNameAck)

DECLARE_SQLMESSAGE(GS2DBUpdateYuanBaoData)
DECLARE_SQLMESSAGE(DB2GSUpdateYuanBaoData)

DECLARE_SQLMESSAGE(GS2DBUpdatePlayerPoint)
DECLARE_SQLMESSAGE(DB2GSUpdatePlayerPoint)
//////////////////////////////////////////////////////////////////////////
#define theSqlMessageManager SqlMessageManager::GetInstance()

class SqlMessageManager
{
public:    
    static SqlMessageManager& GetInstance();

    BaseSqlMessage* GetSqlMessageByDbMsg( Msg* pMsg );                   // 生成对应的SqlMessage
    bool            FreeSqlMessage      ( BaseSqlMessage* pSqlMessage ); // 释放SqlMessage
};

#pragma pack ( pop )

#endif // __DATABASE_SQLQUERYS_H__
