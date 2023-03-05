#include "NormalLogicWorkThread.h"
#include "MySqlCommunication.h"
#include "ConsignmentMessage.h"

// ��ȡ������Ϣ
void NormalLogicWorkThread::OnLoadConsignmentData( BaseSqlMessage* pSqlMessage )
{
    if ( !LoadConsignmentAccount() )
    {
        LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_ERROR, "���ؼ����ʺų���" );
        return;
    }

    if ( !LoadConsignmentMoneyList() )
    {
        LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_ERROR, "���ؼ��۵��ӳ���" );
        return;
    }

    if ( !LoadConsignmentHistroy() )
    {
        LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_ERROR, "���ؼ�����ʷ��¼����" );

        return;
    }
}

bool NormalLogicWorkThread::LoadConsignmentAccount()
{
    static char szSql[ 1024 ] = { 0 };
    memset( szSql, 0, sizeof(szSql) );
    uint32 result = ER_Success;

    TRYBEGIN
    {
        sprintf_s( szSql, sizeof( szSql ) - 1, "select * from consignmentaccount;" );
        mysqlpp::Query mysqlQuery = _pMysqlConnect->query( szSql );
        mysqlpp::StoreQueryResult res = mysqlQuery.store();      

        DB2CSLoadConsignmentAccount xAccount;
        if ( res && !res.empty() )
        { 
            for ( int i = 0; i < res.num_rows(); ++i )
            {
                unsigned long nPlayerID  = res[i]["playerid"];
                unsigned long nRMBMoney  = res[i]["jinding"]; 
                unsigned long nGameMoney = res[i]["gamemoney"];

                xAccount.AddConsignmentAccount( nPlayerID, nRMBMoney, nGameMoney );
                if ( xAccount.IsFull() )
                {
                    theMysqlCommunication.PushAckMessage( &xAccount, 0 );
                    xAccount.Reset();
                }
            }
        }

        theMysqlCommunication.PushAckMessage( &xAccount, 0 );
        mysqlQuery.reset();
    }
    TRYEND

        return RESULT_SUCCESS( result );
}

bool NormalLogicWorkThread::LoadConsignmentMoneyList()
{
    static char szSql[ 1024 ] = { 0 };
    memset( szSql, 0, sizeof( szSql ) );
    uint32 result = ER_Success;

    TRYBEGIN
    {
        sprintf_s( szSql, sizeof( szSql ), "select * from consignmentlist;");
        mysqlpp::Query mysqlQuery = _pMysqlConnect->query( szSql );
        mysqlpp::StoreQueryResult res = mysqlQuery.store();  

        DB2CSLoadConsignmentMoneyList xList;

        if ( res && !res.empty() )
        { 
            ConsignmentBase xBase;
            for ( int i = 0; i < res.num_rows(); ++i )
            {
                xBase.SetID( res[i]["id"] );
                xBase.SetType( res[i]["type"] );
                xBase.SetStartTime( res[i]["starttime"] );
                xBase.SetSellPlayerID( res[i]["seller"] );
                xBase.SetBuyPlayerID( res[i]["buyer"] );
                xBase.SetPrice( res[i]["price"] );
                xBase.SetCount( res[i]["count"] );
                xBase.SetItemID( res[i]["itemid"] );

                xList.AddConsignmentMoney( &xBase );
                if ( xList.IsFull() )
                {
                    theMysqlCommunication.PushAckMessage( &xList, 0 );
                    xList.Reset();
                }
            }
        }

        theMysqlCommunication.PushAckMessage( &xList, 0 );
        mysqlQuery.reset();
    }
    TRYEND

        return RESULT_SUCCESS( result );
}

bool NormalLogicWorkThread::LoadConsignmentHistroy()
{
    static char szSql[ 1024 ] = { 0 };
    memset( szSql, 0, sizeof( szSql ) );
    uint32 result = ER_Success;

    TRYBEGIN
    {
        sprintf_s( szSql, sizeof( szSql ), "select * from consignmenthistroy where starttime > %I64u order by endtime DESC", TimeEx::GetCurrentTime().GetTime() - ConsignmentDefine::MaxConsignmentTime );
        mysqlpp::Query mysqlQuery = _pMysqlConnect->query( szSql );
        mysqlpp::StoreQueryResult res = mysqlQuery.store();       

        DB2CSLoadConsignmentHistroy xList;
        if ( res && !res.empty() )
        { 
            ConsignmentHistroy xHistroy;
            for ( int i = 0; i < res.num_rows(); ++i )
            {
                xHistroy.SetID( res[i]["id"] );
                xHistroy.SetType( res[i]["type"] );
                xHistroy.SetStartTime( res[i]["starttime"] );
                xHistroy.SetSellPlayerID( res[i]["seller"] );
                xHistroy.SetBuyPlayerID( res[i]["buyer"] );
                xHistroy.SetPrice( res[i]["price"] );
                xHistroy.SetCount( res[i]["count"] );
                xHistroy.SetItemID( res[i]["itemid"] );
                xHistroy.SetOperateID( res[i]["operateid"] );
                xHistroy.SetStatus( res[i]["status"] );
                xHistroy.SetEndTime( res[i]["endtime"] );

                xList.AddConsignmentHistroy( &xHistroy );
                if ( xList.IsFull() )
                {
                    theMysqlCommunication.PushAckMessage( &xList, 0 );
                    xList.Reset();
                }
            }
        }

        theMysqlCommunication.PushAckMessage( &xList, 0 );
        mysqlQuery.reset();

    }
    TRYEND


        return RESULT_SUCCESS( result );
}

void NormalLogicWorkThread::OnConsignmnetAccountReq( BaseSqlMessage* pSqlmessage )
{
    CS2DBOperateMoneyReq* pOperate = static_cast< CS2DBOperateMoneyReq* >( pSqlmessage->GetMessageAddress() );
    if ( pOperate == NULL )
    { return; }

    if ( !ConsignmnetAccountReq( pOperate->xAccount ) )
    {
        LOG_MESSAGE( AUCTIONOBJECT, LOG_PRIORITY_ERROR, "[%s]�����ʺŲ���[%d]ʧ�ܣ���[%u],��Ϸ��[%u]", pOperate->xAccount.GetPlayerID(), pOperate->uchOperate, pOperate->xAccount.GetRMBMoney(), pOperate->xAccount.GetGameMoney() );
        return;
    }

    if ( pOperate->bNeedDBAck )
    {
        DB2CSOperateMoneyAck xAck;
        xAck.xAccount   = pOperate->xAccount;
        xAck.uchOperate = pOperate->uchOperate;
        xAck.nRMBMoney  = pOperate->nRMBMoney;
        xAck.nGameMoney = pOperate->nGameMoney;
        theMysqlCommunication.PushAckMessage( &xAck, 0 );
    }

    LOG_MESSAGE( AUCTIONOBJECT, LOG_PRIORITY_INFO, "���[%u]��ȡǮ[%d]�����ɹ� ��[%u]��Ϸ��[%u], DB����ɹ�", pOperate->xAccount.GetPlayerID(), pOperate->uchOperate, pOperate->nRMBMoney, pOperate->nGameMoney );
}

bool NormalLogicWorkThread::ConsignmnetAccountReq( const ConsignmentAccount& xAccount )
{
    static char szSql[ 1024 ] = { 0 };
    memset( szSql, 0, sizeof( szSql ) );
    uint32 result = ER_Success;

    TRYBEGIN
    {
        bool bExist = false;
        sprintf_s( szSql, sizeof( szSql ), "select jinding from consignmentaccount where playerid=%u;",  xAccount.GetPlayerID() );
        mysqlpp::Query mysqlQuery = _pMysqlConnect->query( szSql );
        mysqlpp::StoreQueryResult res = mysqlQuery.store();        
        if ( res && !res.empty() )
        { bExist = true;  }
        mysqlQuery.reset();

        if ( bExist )
        {
            UpdateConsignmentAccount( mysqlQuery, xAccount );   // ����
        }
        else
        {
            InsertConsignmentAccount( mysqlQuery, xAccount );  //����
        }
    }
    TRYEND

        return RESULT_SUCCESS( result );
}

void NormalLogicWorkThread::OnConsignmnetMoneyReq( BaseSqlMessage* pSqlmessage )
{
    CS2DBConsignmentMoneyReq* pReq = static_cast< CS2DBConsignmentMoneyReq* >( pSqlmessage->GetMessageAddress() );
    if ( pReq == NULL )
    { return; }

    static char szSql[ 1024 ] = { 0 };
    memset( szSql, 0, sizeof( szSql ) );
    uint32 result = ER_Success;

    TRYBEGIN
    {
        mysqlpp::Transaction trans( *_pMysqlConnect ); // ��ʼ������
        mysqlpp::Query mysqlQuery = _pMysqlConnect->query();

        // �����ʺ�
        UpdateConsignmentAccount( mysqlQuery, pReq->xAccount );

        // ������۱�
        strncpy_s( szSql, sizeof( szSql ), "insert into consignmentlist(id,type,starttime,seller,buyer,price,count,itemid) values(%0,%1,%2,%3,%4,%5,%6,%7);", sizeof( szSql ) - 1 );
        mysqlQuery << szSql;
        mysqlQuery.parse();
        mysqlQuery.execute( mysqlpp::sql_bigint_unsigned( pReq->xConsignment.GetID() ), pReq->xConsignment.GetType(), mysqlpp::sql_bigint_unsigned( pReq->xConsignment.GetStartTime() ),
            mysqlpp::sql_int_unsigned( pReq->xConsignment.GetSellPlayerID() ), mysqlpp::sql_int_unsigned( pReq->xConsignment.GetBuyPlayerID() ),
            mysqlpp::sql_int_unsigned( pReq->xConsignment.GetPrice() ), mysqlpp::sql_int_unsigned( pReq->xConsignment.GetCount() ), pReq->xConsignment.GetItemID() );
        mysqlQuery.reset();

        //���뽻�׼�¼
        InsertConsignmentHistroy( mysqlQuery, pReq->xConsignment );

        trans.commit();
    }
    TRYEND
        // ִ��ʧ��
        if ( RESULT_FAILED( result ) )
        {
            LOG_MESSAGE( AUCTIONOBJECT, LOG_PRIORITY_INFO, "���[%u][%d]���۶���[%I64u]����ʧ��, ����[%u]����[%u]", pReq->xAccount.GetPlayerID(), pReq->xConsignment.GetType(), pReq->xConsignment.GetID(), pReq->xConsignment.GetPrice(), pReq->xConsignment.GetCount() );
            return;
        }
}

void NormalLogicWorkThread::OnConsignmnetMoneyOperateReq( BaseSqlMessage* pSqlmessage )
{
    CS2DBConsignmentmoneyOperateReq* pReq = static_cast< CS2DBConsignmentmoneyOperateReq* >( pSqlmessage->GetMessageAddress() );
    if ( pReq == NULL )
    { return; }

    static char szSql[ 1024 ] = { 0 };
    memset( szSql, 0, sizeof( szSql ) );
    uint32 result = ER_Success;

    TRYBEGIN
    {
        mysqlpp::Transaction trans( *_pMysqlConnect ); // ��ʼ������
        mysqlpp::Query mysqlQuery = _pMysqlConnect->query();

        // �����˵��˺�
        UpdateConsignmentAccount( mysqlQuery, pReq->xOperaterAccount );

        // �������ʺ�
        if ( !pReq->xSellerAccount.IsErrorAccount() )
        {    
            UpdateConsignmentAccount( mysqlQuery, pReq->xSellerAccount );
        }

        // ɾ�����۱�
        sprintf_s( szSql, sizeof( szSql ), "delete from consignmentlist where id=%I64u;", pReq->nConsignmentID );
        mysqlQuery.execute(szSql);
        mysqlQuery.reset();

        // ������ʷ��¼
        strncpy_s( szSql, sizeof( szSql ), "update consignmenthistroy set status=%1, endtime=%2 where id=%0;", sizeof( szSql ) - 1 );
        mysqlQuery << szSql;
        mysqlQuery.parse();
        mysqlQuery.execute( mysqlpp::sql_bigint_unsigned( pReq->nConsignmentID ), pReq->uchEndStatus, mysqlpp::sql_bigint_unsigned( pReq->n64EndTime ) );
        mysqlQuery.reset();

        //���뽻�׼�¼
        if ( pReq->xNewHistroy.GetOperateID() != ConsignmentDefine::NoneID )
        {
            InsertConsignmentHistroy( mysqlQuery, pReq->xNewHistroy );
        }

        trans.commit();
    }
    TRYEND

        if ( RESULT_FAILED( result ) )
        {
            LOG_MESSAGE( AUCTIONOBJECT, LOG_PRIORITY_INFO, "���ݿ⴦����۶���[%I64u]ʧ��, [%u]��[%u]���˺Ž�����",
                pReq->nConsignmentID, pReq->xOperaterAccount.GetPlayerID(), pReq->xSellerAccount.GetPlayerID() );

            return;
        }

        // ��Ϣ����
        DB2CSConsignmentmoneyOperateAck xAck;
        xAck.xOperaterAccount = pReq->xOperaterAccount;
        xAck.xSellerAccount   = pReq->xSellerAccount;
        xAck.nConsignmentID   = pReq->nConsignmentID;
        xAck.uchEndStatus     = pReq->uchEndStatus;
        xAck.n64EndTime       = pReq->n64EndTime;
        xAck.xNewHistroy      = pReq->xNewHistroy;
        theMysqlCommunication.PushAckMessage( &xAck, 0 );
}

void NormalLogicWorkThread::InsertConsignmentAccount( mysqlpp::Query& xQuery, const ConsignmentAccount& xAccount )
{
    static char szSql[ 1024 ] = { 0 };
    memset( szSql, 0, sizeof( szSql ) );

    strncpy_s( szSql, sizeof( szSql ), "insert into consignmentaccount(playerid,jinding,gamemoney) values(%0,%1,%2);", sizeof( szSql ) -1 );
    xQuery << szSql;
    xQuery.parse();
    xQuery.execute( mysqlpp::sql_int_unsigned( xAccount.GetPlayerID() ), mysqlpp::sql_int_unsigned( xAccount.GetRMBMoney() ), mysqlpp::sql_int_unsigned( xAccount.GetGameMoney() ) );
    xQuery.reset();
}

void NormalLogicWorkThread::UpdateConsignmentAccount( mysqlpp::Query& xQuery, const ConsignmentAccount& xAccount )
{
    static char szSql[ 1024 ] = { 0 };
    memset( szSql, 0, sizeof( szSql ) );

    strncpy_s( szSql, sizeof( szSql ), "update consignmentaccount set jinding=%1, gamemoney=%2 where playerid=%0;", sizeof( szSql ) - 1 );
    xQuery << szSql;
    xQuery.parse();
    xQuery.execute( mysqlpp::sql_int_unsigned( xAccount.GetPlayerID() ), mysqlpp::sql_int_unsigned( xAccount.GetRMBMoney() ), mysqlpp::sql_int_unsigned( xAccount.GetGameMoney() ) );
    xQuery.reset();
}

void NormalLogicWorkThread::InsertConsignmentHistroy( mysqlpp::Query& xQuery, const ConsignmentHistroy& xHistroy )
{
    static char szSql[ 1024 ] = { 0 };
    memset( szSql, 0, sizeof( szSql ) );

    strncpy_s( szSql, sizeof( szSql ), "insert into consignmenthistroy(id,type,starttime,seller,buyer,price,count,itemid,operateid,status,endtime) values(%0,%1,%2,%3,%4,%5,%6,%7,%8,%9,%10);", sizeof( szSql ) - 1 );
    xQuery << szSql;
    xQuery.parse();
    xQuery.execute( mysqlpp::sql_bigint_unsigned( xHistroy.GetID() ), xHistroy.GetType(), mysqlpp::sql_bigint_unsigned( xHistroy.GetStartTime() ),
        mysqlpp::sql_int_unsigned( xHistroy.GetSellPlayerID() ), mysqlpp::sql_int_unsigned( xHistroy.GetBuyPlayerID() ),
        mysqlpp::sql_int_unsigned( xHistroy.GetPrice() ), mysqlpp::sql_int_unsigned( xHistroy.GetCount() ), xHistroy.GetItemID(), mysqlpp::sql_int_unsigned( xHistroy.GetOperateID() ),
        xHistroy.GetStatus(), mysqlpp::sql_bigint_unsigned( xHistroy.GetEndTime() ) );
    xQuery.reset();
}