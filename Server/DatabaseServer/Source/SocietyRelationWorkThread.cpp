#include "SocietyRelationWorkThread.h"
#include "DatabaseServerApp.h"
#include "zlib/zlib.h"
#include "RoleDataCache.h"
#include "FileDatabase.h"
#include "CharChunkWR.h"
#include "MySqlCommunication.h"

SocietyRelationWorkThread::SocietyRelationWorkThread( MySqlCommunication* pOwn ) : MySqlWorkThread(pOwn)
{
}


uint32 SocietyRelationWorkThread::Update()
{
    // 保存基本的 Sql连接 和 Update
    if ( MySqlWorkThread::Update() == ER_SqlNotConnected )
    { return ER_Success; }

    DECLARE_TIME_TEST
    BEGIN_TIME_TEST( "SocietyRelationWorkThread::Update" );
    BaseSqlMessage* pMessage = _dbMsgQueue.PopQuery();
    while ( pMessage != NULL)
    {
        MessageType msgType = pMessage->type;
        DATABASE_MESSAGE_MAPPING_BEGIN
            DATABASE_MESSAGE_HANDLE( DBMSG_ACCOUNTWALLOWINFO_REQ,  OnQueryDBAccountWallowInfoReq   )
            DATABASE_MESSAGE_HANDLE( DBMSG_ACCOUNTWALLOWINFO_SAVE, OnQueryDBAccountWallowInfoSave  )
            DATABASE_MESSAGE_HANDLE( DBMSG_JIFENGSHOPITEMSLISTREQ, OnDBMsgJiFengShopItemsListReq   )
            DATABASE_MESSAGE_HANDLE( DBMSG_JIFENGSHOPITEMSGAINREQ, OnDBMsgJiFengShopItemsGainReq   )
            
            // DATABASE_MESSAGE_HANDLE( DBMSG_SAVE_BATTLE_ATTACKER, ? )
            // DATABASE_MESSAGE_HANDLE( DBMSG_REQ_BATTLE_LOADDATA, ? )
            // DATABASE_MESSAGE_HANDLE( DBMSG_REQLOADGUILDSTAKEDATA, ? )
            // DATABASE_MESSAGE_HANDLE( DBMSG_SAVEGUILDSTAKEDATA, ? )
            // DATABASE_MESSAGE_HANDLE( DBMSG_SAVE_BATTLE_MASTER, ? )
            default:
                LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_WARNING, "SocietyRelationWorkThread::Update() MessageId[%d] 没有处理函数", pMessage->type );
                break;
        DATABASE_MESSAGE_MAPPING_END


        theSqlMessageManager.FreeSqlMessage( pMessage );
        pMessage = _dbMsgQueue.PopQuery();
    }

    _CheckState();

    END_TIME_TEST_1( "SocietyRelationWorkThread::Update", 2000 );
    return ER_Success;
}

void SocietyRelationWorkThread::OnQueryDBAccountWallowInfoReq ( BaseSqlMessage* pSqlMessage )
{
    DBAccountWallowInfoReq* pMessage = static_cast<DBAccountWallowInfoReq*>( pSqlMessage->GetMessageAddress() );

    char szSql[ 1024 ] = {0};
    memset( szSql, 0, sizeof(szSql));
    sprintf_s( szSql, sizeof( szSql ) - 1, "select * from account_wallow where accoun_id=%ld;", pMessage->accountId );
    uint32 result = ER_Success;

    DBAccountWallowInfoAck ack;
    ack.bOpenAntiAddiction = 0;//= GetDatabaseServerApp()->_bOpenantiAddiction;
    //ack.antiAddictionTime  = GetDatabaseServerApp()->_antiAddiction;
	ack.header.stID        = pMessage->header.stID;

    //玩家是小孩，并且防沉迷系统已经打开
    if ( pMessage->IsChild() && ack.bOpenAntiAddiction )
    {
        TRYBEGIN
            mysqlpp::Query mysqlQuery = _pMysqlConnect->query(szSql);
        mysqlpp::StoreQueryResult res = mysqlQuery.store();

        if ( res && !res.empty())
        {
            ack.accountId                 = res[0]["accoun_id"                ];
            ack.onlineMinuteTimeForWallow = res[0]["accumulative_online_time" ];
            ack.offMinuteTimeForWallow    = res[0]["accumulative_offline_time"];
            ack.lastOfflineTime           = res[0]["offline_time"             ];            
        }
        TRYEND

    }
        
    theMysqlCommunication.PushAckMessage( &ack, pSqlMessage->nClientId );

    CHECK_SQL_RESULT( result ); // 执行检测
}

void SocietyRelationWorkThread::OnQueryDBAccountWallowInfoSave( BaseSqlMessage* pSqlMessage )
{
    SqlMessageDBAccountWallowInfoSave* pDetailSqlMessage = (SqlMessageDBAccountWallowInfoSave* )pSqlMessage;
    DBAccountWallowInfoSave* pMessage = &pDetailSqlMessage->msg;

    char szSql[ 1024 ] = {0};
    memset( szSql, 0,sizeof(szSql));
    uint32 result = ER_Success;
    sprintf_s( szSql, sizeof( szSql ) - 1, "select * from account_wallow where accoun_id=%ld;", pMessage->accountId );

    bool bExist = false;
    TRYBEGIN
        mysqlpp::Query mysqlQuery = _pMysqlConnect->query( szSql );        
        mysqlpp::StoreQueryResult res = mysqlQuery.store();
        if ( res && !res.empty())
        { 
            bExist = true;
        }
        mysqlQuery.reset();
    TRYEND

    CHECK_SQL_RESULT( result ) // 执行检测

    if( !bExist )
    { // 不存在
        TRYBEGIN
            mysqlpp::Query mysqlQuery = _pMysqlConnect->query();
            strncpy_s( szSql, sizeof( szSql ), "insert into account_wallow(accoun_id,accumulative_online_time,accumulative_offline_time,offline_time) values(%0,%1,%2,%3);", sizeof( szSql ) - 1 );
            mysqlQuery << szSql;
            mysqlQuery.parse();
            mysqlQuery.execute( mysqlpp::sql_int_unsigned(pMessage->accountId), mysqlpp::sql_int_unsigned(pMessage->onlineMinuteTimeForWallow), mysqlpp::sql_int_unsigned(pMessage->offMinuteTimeForWallow),
                                 mysqlpp::sql_bigint(pMessage->lastOfflineTime));
            mysqlQuery.reset();
        TRYEND

        CHECK_SQL_RESULT( result ) // 执行检测
    }
    else
    { // 存在
        TRYBEGIN
            mysqlpp::Query mysqlQuery = _pMysqlConnect->query();
            strncpy_s( szSql, sizeof( szSql ), "update account_wallow set accumulative_online_time=%1,accumulative_offline_time=%2,offline_time=%3 where accoun_id=%0;", sizeof( szSql ) - 1 );
            mysqlQuery << szSql;
            mysqlQuery.parse();
            mysqlQuery.execute( mysqlpp::sql_int_unsigned(pMessage->accountId), mysqlpp::sql_int_unsigned(pMessage->onlineMinuteTimeForWallow), mysqlpp::sql_int_unsigned(pMessage->offMinuteTimeForWallow),
                                mysqlpp::sql_bigint(pMessage->lastOfflineTime));
            mysqlQuery.reset();
        TRYEND

        CHECK_SQL_RESULT( result ) // 执行检测
    }
}

uint32 SocietyRelationWorkThread::OnDBMsgJiFengShopItemsListReq ( BaseSqlMessage* pSqlMessage )
{
    SqlMessageDBMsgJiFengShopItemsListReq * pDetailSqlMessage = (SqlMessageDBMsgJiFengShopItemsListReq * )pSqlMessage;
    DBMsgJiFengShopItemsListReq* pMessage = &pDetailSqlMessage->msg;

    char szSql[ 1024 ] = {0};
    memset( szSql, 0,sizeof(szSql));
    uint32 result = ER_Success;
    sprintf_s( szSql, sizeof( szSql ) - 1, "select * from platform_objects where account_id=%u and status=%d;", pMessage->accountId, EJFIS_Have );
    
    DBMsgJiFengShopItemsListAck ack;
    ack.header.stID = pMessage->header.stID;

    TRYBEGIN
        mysqlpp::Query mysqlQuery = _pMysqlConnect->query( szSql );        
        mysqlpp::StoreQueryResult res = mysqlQuery.store();
        if ( res && !res.empty())
        {
            SJiFengItemRecordServer record;
            for (int i = 0; i < res.num_rows(); ++i )
            {
                memset( &record, 0, sizeof(record));
                
                record.id             = res[i]["id"];
                strncpy_s( record.info.sn, sizeof(record.info.sn), res[i]["sn"].c_str(), sizeof(record.info.sn)-1 );
                record.info.itemType  = res[i]["object_type"];
                record.info.itemId    = res[i]["object_id"];
                record.info.itemCount = res[i]["object_count"];
                
                for ( int y=0; y<gJiFengItemValueMaxCount; ++y)
                {
                    char szName[64] = {0};
                    sprintf_s( szName,"value_%d",y+1);
                    record.info.value[y] = res[i][szName];
                }

                ack.AddItem( record );
                if ( ack.IsFull() )
                {
                    theMysqlCommunication.PushAckMessage( &ack, pSqlMessage->nClientId );
                    ack.isNew = 0;
                    ack.Reset();
                }
            }
            
        }
        mysqlQuery.reset();

        theMysqlCommunication.PushAckMessage( &ack, pSqlMessage->nClientId );
        
    TRYEND
    
    CHECK_SQL_RESULT_RETURN( result ) // 执行检测

    return result;
}

uint32 SocietyRelationWorkThread::OnDBMsgJiFengShopItemsGainReq( BaseSqlMessage* pSqlMessage )
{
    SqlMessageDBMsgJiFengShopItemsGainReq* pDetailSqlMessage = (SqlMessageDBMsgJiFengShopItemsGainReq*)pSqlMessage;
    DBMsgJiFengShopItemsGainReq* pMessage = &pDetailSqlMessage->msg;

    char szSql[ 1024 ] = {0};
    memset( szSql, 0,sizeof(szSql));
    uint32 result = ER_Success;
    sprintf_s( szSql, sizeof( szSql ) - 1, "select * from platform_objects where account_id=%u and status=%d;", pMessage->accountId, EJFIS_Have );    

    DBMsgJiFengShopItemsGainAck ack;
    ack.header.stID = pMessage->header.stID;

    JiFengItemServerContainer records;
    TRYBEGIN
        mysqlpp::Query mysqlQuery = _pMysqlConnect->query( szSql );        
        mysqlpp::StoreQueryResult res = mysqlQuery.store();
        if ( res && !res.empty())
        {
            SJiFengItemRecordServer record;
            for (int i = 0; i < res.num_rows(); ++i )
            {
                memset( &record, 0, sizeof(record));

                record.id             = res[i]["id"];
                strncpy_s( record.info.sn, sizeof(record.info.sn), res[i]["sn"].c_str(), sizeof(record.info.sn)-1 );
                record.info.itemType  = res[i]["object_type"];
                record.info.itemId    = res[i]["object_id"];
                record.info.itemCount = res[i]["object_count"];
                for ( int y=0; y<gJiFengItemValueMaxCount; ++y)
                {
                    char szName[64] = {0};
                    sprintf_s( szName,"value_%d",y+1);
                    record.info.value[y] = res[i][szName];
                }
                records.push_back( record );
            }

        }
        mysqlQuery.reset();
        
        ItrJiFengItemServerContainer it = records.begin();
        for ( ; it != records.end(); )
        {
            SJiFengItemRecordServer& record = *it;

            // 判断是否在获取队列中
            if ( !pMessage->IsInIds(record.id) )
            {
                it = records.erase( it ); // 不在删除
                continue;
            }
            ++it;
        }
        
        // 领取逻辑
        it = records.begin();
        for ( ; it != records.end(); ++it)
        {
            SJiFengItemRecordServer& record = *it;
            sprintf_s(szSql, sizeof( szSql ) - 1, "update platform_objects set status=%d where account_id=%u and id=%u", EJFIS_Delete, pMessage->accountId, record.id );
            mysqlQuery.execute(szSql);
            mysqlQuery.reset();

            ack.AddItem( record );
            if ( ack.IsFull() )
            { 
                theMysqlCommunication.PushAckMessage( &ack, pSqlMessage->nClientId ); 
                ack.Reset();
            }
        }

        theMysqlCommunication.PushAckMessage( &ack, pSqlMessage->nClientId );

    TRYEND

    CHECK_SQL_RESULT_RETURN( result ) // 执行检测

    return result;
}
