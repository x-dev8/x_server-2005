#include "PlatformRPCLogicWorkThread.h"
#include "zlib/zlib.h"
#include "tstring.h"
#include "MySqlCommunication.h"
#include "GlobalFunction.h"
#include "Config.h"

PlatformRPCLogicWorkThread::PlatformRPCLogicWorkThread( MySqlCommunication* pOwn ) : MySqlWorkThread(pOwn)
{
}

uint32 PlatformRPCLogicWorkThread::Update()
{
    // 保存基本的 Sql连接 和 Update
    if ( MySqlWorkThread::Update() == ER_SqlNotConnected )
    { return ER_Success; }

    BaseSqlMessage* pSqlMessage = _dbMsgQueue.PopQuery();
    while ( pSqlMessage != NULL)
    {
        switch( pSqlMessage->type )
        {
		case GS2CS_UPDATEANTIADDICTIONINFOREQ:
            { OnGS2CSUpdateAntiaddictionInfoReq( pSqlMessage ); }
            break;
        //case CS2P_NEWCARDREQ:
        //    OnCS2PNewCardReq( pSqlMessage );
        //    break;
        default:
            LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_WARNING, "PlatformRPCLogicWorkThread::Update() MessageId[%d] 没有处理函数", pSqlMessage->type );
            break;
        }

        theSqlMessageManager.FreeSqlMessage( pSqlMessage );
        pSqlMessage = _dbMsgQueue.PopQuery();
    }

    _TryGetGmTaskRecord();

    _CheckState( false );
    return ER_Success;
}

//void PlatformRPCLogicWorkThread::OnCS2PNewCardReq( BaseSqlMessage* pSqlMessage )
//{
//    CS2PNewCardReq* pMessage = static_cast<CS2PNewCardReq*>( pSqlMessage->GetMessageAddress() );
//
//    uint32 result = ER_Success;
//    char szSql[1024] = {0};
//    memset( szSql, 0, sizeof(szSql));
//    TRYBEGIN
//    {
//        uint16 callResult = 0;
//        mysqlpp::Query mysqlQuery = _pMysqlConnect->query();
//        strncpy_s( szSql, sizeof( szSql ) - 1,"call get_newcard(%0,%1q,%2);", sizeof( szSql ) - 1 );
//        mysqlQuery << szSql;
//        mysqlQuery.parse();
//        mysqlpp::StoreQueryResult res = mysqlQuery.store( pMessage->gssid, pMessage->passport, pMessage->types );
//
//        if ( res && !res.empty() )
//        {
//            for ( int i = 0; i < res.num_rows(); ++i )
//            {
//                callResult = res[i]["result"];
//                break;
//            }
//            res.clear();
//        }
//
//        FREESTOREPROCEDURE_TRY;
//
//        mysqlQuery.reset();
//    }
//    TRYEND
//
//    // 执行失败
//    if ( RESULT_FAILED( result ) )
//    { return; }
//}

void PlatformRPCLogicWorkThread::_TryGetGmTaskRecord()
{
    // 一秒取一次纪录
    if ( !_timerGetPay.DoneTimer( HQ_TimeGetTime() ))
    { return; }

    //    static char szSql[ 1024 ] = {0};
    //    memset( szSql, 0, sizeof(szSql) );
    //    uint32 result = ER_Success;
    //
    //    std::vector<SPayInfo> payInfos;
    //    TRYBEGIN
    //    {
    //        sprintf_s( szSql, sizeof( szSql ), "select * from pay where flag=%d;", EPayFlagType_WaitingProcess );
    //        mysqlpp::Query mysqlQuery = _pMysqlConnect->query( szSql );
    //        mysqlpp::StoreQueryResult res = mysqlQuery.store();      
    //
    //        if ( res && !res.empty() )
    //        {
    //            for ( int i = 0; i < res.num_rows(); ++i )
    //            {
    //                SPayInfo payInfo;
    //                payInfo.pid = res[i]["pid"];
    //                payInfo.gssid = res[i]["gssid"];
    //                strncpy_s( payInfo.passport, sizeof( payInfo.passport ), res[i]["passport"].c_str(), sizeof( payInfo.passport ) );
    //                payInfo.guid         = res[i]["guid"];
    //                payInfo.typeId       = res[i]["typeid"];
    //                strncpy_s( payInfo.typesn, sizeof( payInfo.typesn ), res[i]["typesn"].c_str(), sizeof( payInfo.typesn ) );
    //                payInfo.addpoint     = res[i]["addpoint"];
    //                payInfo.discount     = res[i]["discount"];
    //                payInfo.addamount    = res[i]["addamount"];
    //                payInfo.netincome    = res[i]["netincome"];
    //                strncpy_s( payInfo.remark , sizeof( payInfo.remark  ), res[i]["remark"].c_str() , sizeof( payInfo.remark  ) );
    //                strncpy_s( payInfo.userip , sizeof( payInfo.userip  ), res[i]["userip"].c_str() , sizeof( payInfo.userip  ) );
    //                strncpy_s( payInfo.gateway, sizeof( payInfo.gateway ), res[i]["gateway"].c_str(), sizeof( payInfo.gateway ) );
    //                payInfo.channel      = res[i]["channel"];
    //                payInfo.paytime      = res[i]["paytime"];
    //#pragma warning( push )
    //#pragma warning( disable : 4244 )
    //                payInfo.flag         = mysqlpp::sql_smallint(res[i]["flag"]);
    //#pragma warning( pop )
    //                payInfo.ctime        = res[i]["ctime"];
    //
    //                payInfos.push_back( payInfo );
    //            }
    //        }
    //        mysqlQuery.reset();
    //
    //        if ( !payInfos.empty() )
    //        {
    //            mysqlpp::Transaction trans(*_pMysqlConnect);  // 开始事务处理
    //            std::vector<SPayInfo>::iterator it = payInfos.begin();
    //            for ( ; it!=payInfos.end(); ++it )
    //            {
    //                memset( szSql, 0, sizeof( szSql ) );
    //                strncpy_s( szSql, sizeof( szSql ), "update pay set flag=%1,ctime=%2 where typeid=%0;", sizeof( szSql ) - 1 );
    //                mysqlQuery << szSql;
    //                mysqlQuery.parse();
    //                mysqlQuery.execute( it->typeId, EPayFlagType_Processing, GreenwichTime::GetTime() );
    //                mysqlQuery.reset();
    //            }
    //            trans.commit();
    //        }
    //    }
    //    TRYEND
    //
    //    // 执行失败
    //    if ( RESULT_FAILED( result ) )
    //    { return; }
    //
    //    if ( !payInfos.empty() )
    //    {
    //        P2CSAddPayReq xReq;
    //        std::vector<SPayInfo>::iterator it = payInfos.begin();
    //        for ( ; it!=payInfos.end(); ++it )
    //        {
    //            xReq.payInfo = *it;
    //            theMysqlCommunication.PushReqMessage( &xReq, 0 );
    //            LOG_MESSAGE( BILLINGOBJECT, LOG_PRIORITY_INFO, "开始处理充值typeId[%d] guid[%u] pid[%d] gssid[%d] addpoint[%d]", xReq.payInfo.typeId, xReq.payInfo.guid, xReq.payInfo.pid, xReq.payInfo.gssid, xReq.payInfo.addpoint );
    //        }
    //    }
}
void PlatformRPCLogicWorkThread::OnGS2CSUpdateAntiaddictionInfoReq( BaseSqlMessage* pSqlMessage )
{
    GS2CSUpdateAntiaddictionInfoReq* pMessage = static_cast<GS2CSUpdateAntiaddictionInfoReq*>( pSqlMessage->GetMessageAddress() );

    uint32 result = ER_Success;
    char szSql[1024] = {0};
    memset( szSql, 0, sizeof(szSql));

    CS2GSUpdateAntiaddictionInfoAck xAck;
    xAck.nResult = ER_Success;
    xAck.nType      = pMessage->nType;
    xAck.nAccountId = pMessage->nAccountId;
    xAck.nDuration  = pMessage->nDuration;

	/*switch(pMessage->nType)
	{
	case GS2CSUpdateAntiaddictionInfoReq::EUpdateReqType_Init:*/
Begin:
		TRYBEGIN  
		mysqlpp::Query mysqlQuery = _pMysqlConnect->query();  
		strncpy_s( szSql, sizeof( szSql ), "call check_fcm(%0q,%1,%2,%3);", sizeof(szSql)-1 );
		mysqlQuery << szSql;
		mysqlQuery.parse();
		mysqlpp::StoreQueryResult res = mysqlQuery.store( /*theConfig.CenterServerId, */pMessage->passport, 
														mysqlpp::sql_int_unsigned(pMessage->nAccountId),
														mysqlpp::sql_int_unsigned(pMessage->nDuration),
														mysqlpp::sql_int_unsigned(pMessage->nType) );
		if ( res && !res.empty())
		{ xAck.nOnlineTime = res[0][0]; }
		FREESTOREPROCEDURE_TRY;
		TRYEND

			LOG_MESSAGE( LOGICSYSTEMOBJECT, LOG_PRIORITY_INFO,"account[%d][%d] GS2CSUpdateAntiaddictionInfoReq(%d:%s:%u)", pMessage->nAccountId, result, pMessage->nType,pMessage->passport,pMessage->nDuration);

		// 保证执行
		CHECK_RESULT;
		/*break;
	case GS2CSUpdateAntiaddictionInfoReq::EUpdateReqType_Update:
		break;
	default:
		return;
		break;
	}*/


    xAck.nResult = (uint16)result;
    _pOwn->PushAckMessage( &xAck, 0 );    
}