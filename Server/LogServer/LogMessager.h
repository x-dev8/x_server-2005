#ifndef __LogMessager_H__
#define __LogMessager_H__
#pragma once

#include "LogServerMessageDefine.h"
#include "Memory_Pool.h"
#include "GlobalDef.h"

#pragma pack( push, 1 )

extern int G_PrinfInfo;
#define  NOPRINT 0
#define  PRINTFQUEUESIZE 1
#define  PRINTFSAVEROLETIME 2


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

/////////////////////////////////////////////////////////////////////////
class BaseLogMessage
{
public:
	BaseLogMessage(): serverid( -1 ), _type( ErrorUnsignedShortID ){}
public:
	int32			serverid;//发过来的服务器ID
	MessageType		_type;
	virtual void	Release()		   {}
	virtual void*	GetMessageAddress(){ return NULL;}
	virtual uint32	GetMessageSize()   { return 0;   }
};

#define LOGMSGCLASS(xLogMsg) LogMessage##xLogMsg



#define DECLARE_LOGMESSAGE_BEGIN(xLogMsg) \
class LogMessage##xLogMsg : public BaseLogMessage, INHERIT_POOL_PARAM(LogMessage##xLogMsg, 50) \
{ \
public: \
	static  BaseLogMessage* CreateInstance()    { return MES_NEW(LogMessage##xLogMsg); } \
	virtual void            Release()           { MES_DELETE(LogMessage##xLogMsg); } \
	virtual void*           GetMessageAddress() { return &msg;        } \
	virtual uint32          GetMessageSize()    { return sizeof(msg); } \
public: \
	xLogMsg msg;

#define DECLARE_LOGMESSAGE_END(xLogMsg) \
};

#define DECLARE_LOGMESSAGE(xLogMsg)   \
	DECLARE_LOGMESSAGE_BEGIN(xLogMsg) \
	DECLARE_LOGMESSAGE_END(xLogMsg)   \

DECLARE_LOGMESSAGE(TestLogMessage)
DECLARE_LOGMESSAGE(CS2LOnlineInfo)
DECLARE_LOGMESSAGE(GS2LPlayerInOutLog)
DECLARE_LOGMESSAGE(GS2LItemGain)
DECLARE_LOGMESSAGE(GS2LItemTrade)
DECLARE_LOGMESSAGE(GS2LItemConsume)
DECLARE_LOGMESSAGE(GS2LItemUpgrade)
DECLARE_LOGMESSAGE(GS2LQuestLog)
DECLARE_LOGMESSAGE(GS2LCurrencyLog)
DECLARE_LOGMESSAGE(GS2LExpLog)
DECLARE_LOGMESSAGE(GS2LLevelChange)
DECLARE_LOGMESSAGE(S2LMailLog)
DECLARE_LOGMESSAGE(S2LGuildDetailLog)
DECLARE_LOGMESSAGE(S2LGuildLog)
DECLARE_LOGMESSAGE(GS2LGMCommand)
DECLARE_LOGMESSAGE(GS2LChatInfo)

/////////////////////////////////////////////////////////////////////////
#define theLogMessageManager LogMessageManager::GetInstance()

class LogMessageManager
{
public:    
	static LogMessageManager& GetInstance();	
	BaseLogMessage* GetLogMessageByLogMsg( Msg* pMsg );                   // 生成对应的SqlMessage
	bool            FreeLogMessage      ( BaseLogMessage* pSqlMessage ); // 释放SqlMessage
};


#pragma pack( pop ) 

#endif