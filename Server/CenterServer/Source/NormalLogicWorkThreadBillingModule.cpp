#include "NormalLogicWorkThread.h"
#include "zlib/zlib.h"
#include "tstring.h"
#include "MySqlCommunication.h"

//void NormalLogicWorkThread::OnP2CSAddPayReq( BaseSqlMessage* pSqlMessage )
//{
//    P2CSAddPayReq* pMessage = static_cast< P2CSAddPayReq* >( pSqlMessage->GetMessageAddress() );
//
//    char szSql[1024] = {0};
//    uint32 result = ER_Success;
//    memset( szSql, 0, sizeof(szSql));
//    sprintf_s( szSql, sizeof( szSql ) - 1,"call account_point_op( %u, %d, %d );", pMessage->payInfo.guid, pMessage->payInfo.addpoint, EAPOT_Sub );
//    uint32 point = 0;
//
//    TRYBEGIN
//    {
//        mysqlpp::Query mysqlQuery = _pMysqlConnect->query();        
//        mysqlpp::StoreQueryResult res = mysqlQuery.store( szSql, sizeof(szSql) );
//        FREESTOREPROCEDURE_TRY;
//    }
//    TRYEND
//
//    // ִ��ʧ��
//    if ( RESULT_FAILED( result ) )
//    { 
//        LOG_MESSAGE( BILLINGOBJECT, LOG_PRIORITY_INFO, "��ֵ����Ϸ���ݿ� ʧ�� typeId[%d] guid[%u] pid[%d] gssid[%d] addpoint[%d]",
//            pMessage->payInfo.typeId,pMessage->payInfo.guid, pMessage->payInfo.pid, pMessage->payInfo.gssid, pMessage->payInfo.addpoint );
//        return; 
//    }
//
//    LOG_MESSAGE( BILLINGOBJECT, LOG_PRIORITY_INFO, "��ֵ����Ϸ���ݿ� �ɹ� typeId[%d] guid[%u] pid[%d] gssid[%d] addpoint[%d]",
//        pMessage->payInfo.typeId,pMessage->payInfo.guid, pMessage->payInfo.pid, pMessage->payInfo.gssid, pMessage->payInfo.addpoint );
//
//    // ֪ͨ�����ƽ̨���ݿ�
//    CS2PAddPayAck ack;
//    ack.result = ER_Success;
//    ack.guid   = pMessage->payInfo.guid;
//    ack.typeId = pMessage->payInfo.typeId;
//    theMysqlCommunication.PushReqMessage( &ack, 0 );
//}
