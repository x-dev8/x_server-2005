#include "ConsignmentManager.h"
#include "MySqlCommunication.h"
#include "ConsignmentMessage.h"
#include "GameServerManager.h"
#include "RunStatus.h"


ConsignmentManager::ConsignmentManager() : m_bLoadAccount( false ), m_bLoadSellRMB( false ), m_bLoadBuyRMB( false ), m_bLoadSellItem( false ), m_bLoadBuyItem( false ), m_LoadRMBHistory( false ), 
                                        m_LoadItemHistory( false ), m_bIsStartLoad( false ), m_bLoadSuccess( false )
{
    m_mapAccount.clear();
    m_mapSellRMB.clear();
    m_mapBuyRMB.clear();
    m_mapSellItem.clear();
    m_mapBuyItem.clear();
    m_mapRMBHistroy.clear();
    m_mapItemHistroy.clear();

    m_xUpdateTimer.StartTimer( 1, ConsignmentDefine::UpdateSpaceTime );
}

ConsignmentManager::~ConsignmentManager()
{
    for ( MapAccountIter iter = m_mapAccount.begin(); iter != m_mapAccount.end(); ++iter )
    {
        iter->second->Release();
    }
    m_mapAccount.clear();

    for ( SellRMBMapIter iter = m_mapSellRMB.begin(); iter != m_mapSellRMB.end(); ++iter )
    {
        iter->second->Release();
    }
    m_mapSellRMB.clear();

    for ( BuyRMBMapIter iter = m_mapBuyRMB.begin(); iter != m_mapBuyRMB.end(); ++iter )
    {
        iter->second->Release();
    }
    m_mapBuyRMB.clear();

    for ( SellItemMapIter iter = m_mapSellItem.begin(); iter != m_mapSellItem.end(); ++iter )
    {
        iter->second->Release();
    }
    m_mapSellItem.clear();

    for ( BuyItemMapIter iter = m_mapBuyItem.begin(); iter != m_mapBuyItem.end(); ++iter )
    {
        iter->second->Release();
    }
    m_mapBuyItem.clear();

    for ( RMBHistroyMapIter iter = m_mapRMBHistroy.begin(); iter != m_mapRMBHistroy.end(); ++iter )
    {
        for ( RMBHistroyVectorIter viter = iter->second.begin(); viter != iter->second.end(); ++viter )
        {
            ( *viter )->Release();
        }
    }
    m_mapRMBHistroy.clear();

    for ( ItemHistroyMapIter iter = m_mapItemHistroy.begin(); iter != m_mapItemHistroy.end(); ++iter )
    {
        for ( VectorItemHistroyIter viter = iter->second.begin(); viter != iter->second.end(); ++viter )
        {
            ( *viter )->Release();
        }
    }
    m_mapItemHistroy.clear();
}

void ConsignmentManager::RunUpdate( unsigned long nCurrentTime )
{
    if ( !m_xUpdateTimer.DoneTimer( nCurrentTime ) )
    { return; }

    // 处理加载数据
    ProcessLoadConsignmentData( nCurrentTime );

    // 处理过期的寄售单
    ProcessSellRMBTimeOut();
    ProcessBuyRMBTimeOut();
}

void ConsignmentManager::StartLoadTimer( unsigned int nCurrentTime )
{
    if ( m_bIsStartLoad )
    { return; }

    m_bIsStartLoad = true;
    m_xLoadTimer.StartTimer( 1, ConsignmentDefine::LoadSpaceTime );
}
void ConsignmentManager::SetLoadSuccess( bool bValue ) 
{
	m_bLoadSuccess = bValue;
	if (bValue)
	{
		theRunStatus.SetLoadSuccess(RunStatusDefine::LoadConsignmentSuccess);
	}
}
void ConsignmentManager::ProcessLoadConsignmentData( unsigned int nCurrentTime )
{
    StartLoadTimer( nCurrentTime );
    if ( !m_xLoadTimer.DoneTimer( nCurrentTime ) )
    { return; }

    // 请求数据库加载
    CS2DBLoadConsignmentDataReq xReq;
    theMysqlCommunication.PushReqMessage( &xReq, 0 );
}

void ConsignmentManager::InitConsignmentAccount( const ConsignmentAccount* pAccountArray, int nCount )
{
    if ( pAccountArray == NULL || nCount == 0 )
    { return; }

    for ( int i = 0; i < nCount; ++i, ++pAccountArray )
    {
        if ( pAccountArray->IsErrorAccount() )
        { break; }

        Account* pAccount = NEW_POOL(Account);
        if ( pAccount == NULL )
        { continue; }

        pAccount->Initialize( pAccountArray );
        m_mapAccount[ pAccount->GetPlayerID() ] = pAccount;
    }
}

ConsignmentManager::Account* ConsignmentManager::GetConsignmentAccount( unsigned long dwPlayerID )
{
    if ( !m_bLoadAccount )
    { return NULL; }

    MapAccountIter iter = m_mapAccount.find( dwPlayerID );
    if ( iter == m_mapAccount.end() )
    {
        Account* pAccount = NEW_POOL(Account);
        pAccount->SetPlayerID( dwPlayerID );

        iter = m_mapAccount.insert( std::make_pair( dwPlayerID, pAccount ) ).first;
        if ( iter == m_mapAccount.end() )
        { return NULL; }
    }

    return iter->second;
}

void ConsignmentManager::InitConsignmentMoneyList( const ConsignmentBase* pConsignment, int nCount )
{
    if ( pConsignment == NULL || nCount == 0 )
    { return; }

    for ( int i = 0; i < nCount; ++i, ++pConsignment )
    {
        AddConsignment( pConsignment );
    }
}

void ConsignmentManager::InitConsignmentItemList( const ConsignmentData* pConsignment, int nCount )
{
    if ( pConsignment == NULL || nCount == 0 )
    { return; }

    for ( int i = 0; i < nCount; ++i, ++pConsignment )
    {
        AddConsignment( pConsignment );
    }
}

void ConsignmentManager::InitConsignmentHistoryList( const ConsignmentHistroy* pHistroy, int nCount )
{
    if ( pHistroy == NULL || nCount == 0 )
    { return; }

    for ( int i = 0; i < nCount; ++i, ++pHistroy )
    {
        switch ( pHistroy->GetType() )
        {
        case ConsignmentDefine::Consignment_SellRMB:
        case ConsignmentDefine::Consignment_BuyRMB:
            {
                AddRMBHistroy( pHistroy );
            }
            break;
        case ConsignmentDefine::Consignment_SellItem:
        case ConsignmentDefine::Consignment_SellMount:
        case ConsignmentDefine::Consignment_SellPet:
        case ConsignmentDefine::Consignment_BuyItem:
        case ConsignmentDefine::Consignment_BuyMount:
        case ConsignmentDefine::Consignment_BuyPet:
            {
                AddItemHistroy( pHistroy );
            }
            break;
        default:
            break;
        }
    }
}

bool ConsignmentManager::AddConsignment( const ConsignmentBase* pConsignment )
{
    if ( pConsignment == NULL )
    { return false; }

    switch( pConsignment->GetType() )
    {
    case ConsignmentDefine::Consignment_SellRMB:
        {
            SellRMB* pSellRMB = MES_NEW(SellRMB);
            if ( pSellRMB == NULL )
            { return false; }

            pSellRMB->Initialize( pConsignment );
            return m_mapSellRMB.insert( std::make_pair( pSellRMB->GetID(), pSellRMB ) ).second;
        }
        break;
    case ConsignmentDefine::Consignment_BuyRMB:
        {
            BuyRMB* pBuyRMB = MES_NEW(BuyRMB);
            if ( pBuyRMB == NULL )
            { return false; }

            pBuyRMB->Initialize( pConsignment );
            return m_mapBuyRMB.insert( std::make_pair( pBuyRMB->GetID(), pBuyRMB ) ).second;
        }
        break;
    case ConsignmentDefine::Consignment_SellItem:
    case ConsignmentDefine::Consignment_SellMount:
    case ConsignmentDefine::Consignment_SellPet:
        {
            SellItem* pSellItem = MES_NEW(SellItem);
            if ( pSellItem == NULL )
            { return false; }
            
            pSellItem->Initialize( static_cast< const ConsignmentData* >( pConsignment ) );
            return m_mapSellItem.insert( std::make_pair( pSellItem->GetID(), pSellItem ) ).second;
        }
        break;
    case ConsignmentDefine::Consignment_BuyItem:
    case ConsignmentDefine::Consignment_BuyMount:
    case ConsignmentDefine::Consignment_BuyPet:
        {
            BuyItem* pBuyItem = MES_NEW(BuyItem);
            if ( pBuyItem == NULL )
            { return false; }

            pBuyItem->Initialize( pConsignment );
            return m_mapBuyItem.insert( std::make_pair( pBuyItem->GetID(), pBuyItem ) ).second;
        }
        break;
    default:
        break;
    }

    return false;
}

void ConsignmentManager::RemoveConsignment( __int64 n64ID, unsigned char uchType )
{
    switch( uchType )
    {
    case ConsignmentDefine::Consignment_SellRMB:
        {
            SellRMBMapIter iter = m_mapSellRMB.find( n64ID );
            if ( iter != m_mapSellRMB.end() )
            {
                iter->second->Release();
                m_mapSellRMB.erase( iter );
            }
        }
        break;
    case ConsignmentDefine::Consignment_BuyRMB:
        {
            BuyRMBMapIter iter = m_mapBuyRMB.find( n64ID );
            if ( iter != m_mapBuyRMB.end() )
            {
                iter->second->Release();
                m_mapBuyRMB.erase( iter );
            }
        }
        break;
    case ConsignmentDefine::Consignment_SellItem:
    case ConsignmentDefine::Consignment_SellMount:
    case ConsignmentDefine::Consignment_SellPet:
        {
            SellItemMapIter iter = m_mapSellItem.find( n64ID );
            if ( iter != m_mapSellItem.end() )
            {
                iter->second->Release();
                m_mapSellItem.erase( iter );
            }
        }
        break;
    case ConsignmentDefine::Consignment_BuyItem:
    case ConsignmentDefine::Consignment_BuyMount:
    case ConsignmentDefine::Consignment_BuyPet:
        {
            BuyItemMapIter iter = m_mapBuyItem.find( n64ID );
            if ( iter != m_mapBuyItem.end() )
            {
                iter->second->Release();
                m_mapBuyItem.erase( iter );
            }
        }
        break;
    default:
        break;
    }
}

ConsignmentManager::Consignment* ConsignmentManager::GetConsignmentMoney( __int64 n64ID, unsigned char uchType )
{
    switch( uchType )
    {
    case ConsignmentDefine::Consignment_SellRMB:
        {
            SellRMBMapIter iter = m_mapSellRMB.find( n64ID );
            if ( iter != m_mapSellRMB.end() )
            {
                return iter->second;
            }
        }
        break;
    case ConsignmentDefine::Consignment_BuyRMB:
        {
            BuyRMBMapIter iter = m_mapBuyRMB.find( n64ID );
            if ( iter != m_mapBuyRMB.end() )
            {
                return iter->second;
            }
        }
        break;
    default:
        break;
    }

    return NULL;
}

void ConsignmentManager::AddRMBHistroy( const ConsignmentHistroy* pHistroy )
{
    if ( pHistroy == NULL )
    { return; }

    RMBHistroy* pRMBHistroy = MES_NEW(RMBHistroy);
    if ( pRMBHistroy == NULL )
    { return; }

    pRMBHistroy->Initialize( pHistroy );

    RMBHistroyMapIter iter = m_mapRMBHistroy.find( pRMBHistroy->GetOperateID() );
    if ( iter != m_mapRMBHistroy.end() )
    {
        iter->second.push_back( pRMBHistroy );
    }
    else
    {
        RMBHistroyVector vecHistroy;
        vecHistroy.push_back( pRMBHistroy );
        m_mapRMBHistroy.insert( std::make_pair( pRMBHistroy->GetOperateID(), vecHistroy ) );
    }
}

void ConsignmentManager::AddItemHistroy( const ConsignmentHistroy* pHistroy )
{
    if ( pHistroy == NULL )
    { return; }

    ItemHistroy* pItemHistroy = MES_NEW(ItemHistroy);
    if ( pItemHistroy == NULL )
    { return; }

    pItemHistroy->Initialize( pHistroy );

    ItemHistroyMapIter iter = m_mapItemHistroy.find( pItemHistroy->GetOperateID() );
    if ( iter != m_mapItemHistroy.end() )
    {
        iter->second.push_back( pItemHistroy );
    }
    else
    {
        VectorItemHistroy vecHistroy;
        vecHistroy.push_back( pItemHistroy );
        m_mapItemHistroy.insert( std::make_pair( pItemHistroy->GetOperateID(), vecHistroy ) );
    }
}

void ConsignmentManager::ProcessSortSellRMB( unsigned char uchSortType, int nValue /* = 0 */)
{
    m_vecSellRMB.clear();
    m_vecSellRMB.reserve( m_mapSellRMB.size() );

    if ( !m_bLoadSellRMB )
    { return; }

    switch ( uchSortType )
    {
    case ConsignmentDefine::Sort_Count:     // 指定数量
        std::for_each( m_mapSellRMB.begin(), m_mapSellRMB.end(), CopyConsignmentMoneyListCount< SellRMBPair, SellRMBVector >( m_vecSellRMB, nValue ) );
        std::sort( m_vecSellRMB.begin(), m_vecSellRMB.end(), SortByLessPrice< SellRMB >() );
        break;
    case ConsignmentDefine::Sort_ForMe:     // 指定给我
        std::for_each( m_mapSellRMB.begin(), m_mapSellRMB.end(), CopyConsignmentMoneyListForMe< SellRMBPair, SellRMBVector >( m_vecSellRMB, nValue ) );
        break;
    case ConsignmentDefine::Sort_MySelf:    // 我自己发布的
        std::for_each( m_mapSellRMB.begin(), m_mapSellRMB.end(), CopyConsignmentMoneyListSelf< SellRMBPair, SellRMBVector >( m_vecSellRMB, nValue ) );
        break;
    default:
        {
            std::for_each( m_mapSellRMB.begin(), m_mapSellRMB.end(), CopyConsignmentMoneyList< SellRMBPair, SellRMBVector >( m_vecSellRMB ) );

            switch( uchSortType )
            {
            case ConsignmentDefine::Sort_Normal:
                std::sort( m_vecSellRMB.begin(), m_vecSellRMB.end(), SortByLessPrice< SellRMB >() );
                break;
            case ConsignmentDefine::Sort_Date:  // 按日期排序
                std::sort( m_vecSellRMB.begin(), m_vecSellRMB.end(), SortByDate< SellRMB >() );
                break;
            case ConsignmentDefine::Sort_LessPrice: // 价钱从小到大排序
                std::sort( m_vecSellRMB.begin(), m_vecSellRMB.end(), SortByLessPrice< SellRMB >() );
                break;
            case ConsignmentDefine::Sort_GreaterPrice:  // 价钱从大到小
                std::sort( m_vecSellRMB.begin(), m_vecSellRMB.end(), SortByGreaterPrice< SellRMB >() );
                break;
            case ConsignmentDefine::Sort_LessCount: // 数量从小到大
                std::sort( m_vecSellRMB.begin(), m_vecSellRMB.end(), SortByLessCount< SellRMB >() );
                break;
            case ConsignmentDefine::Sort_GreaterCount:  // 数量从大到小
                std::sort( m_vecSellRMB.begin(), m_vecSellRMB.end(), SortByGreaterCount< SellRMB >() );
                break;
            default:
                break;
            }
        }
        break;
    }
}

void ConsignmentManager::ProcessSortBuyRMB( unsigned char uchSortType, int nValue /* = 0 */)
{
    m_vecBuyRMB.clear();
    m_vecBuyRMB.reserve( m_mapBuyRMB.size() );

    if ( !m_bLoadBuyRMB )
    { return; }

    switch ( uchSortType )
    {
    case ConsignmentDefine::Sort_Count:     // 指定数量
        std::for_each( m_mapBuyRMB.begin(), m_mapBuyRMB.end(), CopyConsignmentMoneyListCount< BuyRMBPair, BuyRMBVector >( m_vecBuyRMB, nValue ) );
        std::sort( m_vecBuyRMB.begin(), m_vecBuyRMB.end(), SortByLessPrice< BuyRMB >() );
        break;
    case ConsignmentDefine::Sort_ForMe:     // 指定给我
        std::for_each( m_mapBuyRMB.begin(), m_mapBuyRMB.end(), CopyConsignmentMoneyListForMe< BuyRMBPair, BuyRMBVector >( m_vecBuyRMB, nValue ) );
        break;
    case ConsignmentDefine::Sort_MySelf:    // 我自己发布的
        std::for_each( m_mapBuyRMB.begin(), m_mapBuyRMB.end(), CopyConsignmentMoneyListSelf< BuyRMBPair, BuyRMBVector >( m_vecBuyRMB, nValue ) );
        break;
    default:
        {
            std::for_each( m_mapBuyRMB.begin(), m_mapBuyRMB.end(), CopyConsignmentMoneyList< BuyRMBPair, BuyRMBVector >( m_vecBuyRMB ) );

            switch( uchSortType )
            {
            case ConsignmentDefine::Sort_Normal:  // 默认
                std::sort( m_vecBuyRMB.begin(), m_vecBuyRMB.end(), SortByGreaterPrice< BuyRMB >() );
                break;
            case ConsignmentDefine::Sort_Date:  // 按日期排序
                std::sort( m_vecBuyRMB.begin(), m_vecBuyRMB.end(), SortByDate< BuyRMB >() );
                break;
            case ConsignmentDefine::Sort_LessPrice:     // 价钱从小到大排序
                std::sort( m_vecBuyRMB.begin(), m_vecBuyRMB.end(), SortByLessPrice< BuyRMB >() );
                break;
            case ConsignmentDefine::Sort_GreaterPrice:  // 价钱从大到小
                std::sort( m_vecBuyRMB.begin(), m_vecBuyRMB.end(), SortByGreaterPrice< BuyRMB >() );
                break;
            case ConsignmentDefine::Sort_LessCount:     // 数量从小到大
                std::sort( m_vecBuyRMB.begin(), m_vecBuyRMB.end(), SortByLessCount< BuyRMB >() );
                break;
            case ConsignmentDefine::Sort_GreaterCount:  // 数量从大到小
                std::sort( m_vecBuyRMB.begin(), m_vecBuyRMB.end(), SortByGreaterCount< BuyRMB >() );
                break;
            default:
                break;
            }
        }
        break;
    }
}

void ConsignmentManager::SendMessageToPlayer( unsigned int nPlayerID, Msg* pMessage, bool bDirect )
{
    theGameServerManager.SendMsgToSingleRemote( ConsignmentDefine::ErrorID, pMessage, nPlayerID, "", bDirect );
}

void ConsignmentManager::SendAccountMessage( unsigned int nPlayerID )
{
    Account* pAccount = GetConsignmentAccount( nPlayerID );
    if ( pAccount == NULL )
    { return; }

    SendAccountMessage( pAccount );
}

void ConsignmentManager::SendAccountMessage( const Account* pAccount )
{
    if ( pAccount == NULL )
    { return; }

    CS2GSConsignmentAccount xTell;
    xTell.bProcess = pAccount->IsWaitProcess();
    xTell.xAcount.Initialize( pAccount );
    SendMessageToPlayer( pAccount->GetPlayerID(), &xTell, false );
}

void ConsignmentManager::SendConsignmentMoneyListMessage( unsigned int nPlayerID, unsigned char uchConsignmentType )
{
    MsgShowConsignmentMoneyList xList;

    // 先处理排序
    switch ( uchConsignmentType )
    {
    case ConsignmentDefine::Consignment_SellRMB:    // 出售金锭寄售单
        {
            int nCount = 0;
            for ( SellRMBVectorIter iter = m_vecSellRMB.begin(); iter != m_vecSellRMB.end() && nCount < ConsignmentDefine::MaxConsignmentCount; ++iter, ++nCount )
            {
                xList.AddConsignmentMoney( *iter );
            }
            xList.uchShowType = MsgShowConsignmentMoneyList::Show_SellRMB;
        }
        break;
    case ConsignmentDefine::Consignment_BuyRMB:     // 购买金锭寄售单
        {
            int nCount = 0;
            for ( BuyRMBVectorIter iter = m_vecBuyRMB.begin(); iter != m_vecBuyRMB.end() && nCount < ConsignmentDefine::MaxConsignmentCount; ++iter, ++nCount )
            {
                xList.AddConsignmentMoney( *iter );
            }
            xList.uchShowType = MsgShowConsignmentMoneyList::Show_BuyRMB;
        }
        break;
    default:    // 默认两个都显示
        {
            int nCount = 0;
            for ( SellRMBVectorIter iter = m_vecSellRMB.begin(); iter != m_vecSellRMB.end() && nCount < ConsignmentDefine::MaxConsignmentCount; ++iter, ++nCount )
            {
                xList.AddConsignmentMoney( *iter );
            }
            
            nCount = 0;
            for ( BuyRMBVectorIter iter = m_vecBuyRMB.begin(); iter != m_vecBuyRMB.end() && nCount < ConsignmentDefine::MaxConsignmentCount; ++iter, ++nCount )
            {
                xList.AddConsignmentMoney( *iter );
            }
        }
        break;
    }
    
    SendMessageToPlayer( nPlayerID, &xList, true );
}

void ConsignmentManager::SendConsignmentMoneyListMessage( unsigned int nPlayerID, unsigned char uchConsignmentType, unsigned char uchSortType, int nValue /* = 0 */ )
{
    switch ( uchSortType )
    {
    case ConsignmentDefine::Sort_MySelf:
    case ConsignmentDefine::Sort_ForMe:
        nValue = nPlayerID;
        break;
    default:
        break;
    }

    switch ( uchConsignmentType )
    {
    case ConsignmentDefine::Consignment_SellRMB:
        ProcessSortSellRMB( uchSortType, nValue );
        break;
    case ConsignmentDefine::Consignment_BuyRMB:
        ProcessSortBuyRMB( uchSortType, nValue );
        break;
    default:
        ProcessSortSellRMB( uchSortType, nValue );
        ProcessSortBuyRMB( uchSortType, nValue );
        break;
    }

    SendConsignmentMoneyListMessage( nPlayerID, uchConsignmentType );
}

void ConsignmentManager::SendOperateMessage( unsigned int nPlayerID, bool bProcess )
{
    CS2GSConsignmentOperate xProcess;
    xProcess.bProcess = bProcess;
    SendMessageToPlayer( nPlayerID, &xProcess, false );
}

void ConsignmentManager::ProcessGameAccountOperate( unsigned int nPlayerID, unsigned char uchOperate, unsigned int nRMBMoney, unsigned int nGameMoney )
{
    Account* pAccount = GetConsignmentAccount( nPlayerID );
    if ( pAccount == NULL || pAccount->IsWaitProcess() )
    {
        // ToLog;
        return;
    }

    CS2DBOperateMoneyReq xOperate;
    xOperate.xAccount.SetPlayerID( nPlayerID );
    xOperate.uchOperate = uchOperate;
    xOperate.nRMBMoney  = nRMBMoney;
    xOperate.nGameMoney = nGameMoney;

    switch( uchOperate )
    {
    case ConsignmentDefine::Operate_Save:
        {
            xOperate.bNeedDBAck = true;
            xOperate.xAccount.Initialize( pAccount );

            if ( nGameMoney != 0 )
            {
                if ( pAccount->GetGameMoney() + nGameMoney > ConsignmentDefine::MaxAccountGameMoney )
                {
                    // ToLog
                    return;
                }

                xOperate.xAccount.SetGameMoney( pAccount->GetGameMoney() + nGameMoney );
            }
            
            if ( nRMBMoney != 0 )
            {
                if ( nRMBMoney + pAccount->GetRMBMoney() > ConsignmentDefine::MaxAccountRMB )
                {
                    // ToLog
                    return;
                }

                xOperate.xAccount.SetRMBMoney( pAccount->GetRMBMoney() + nRMBMoney );
            }

            pAccount->SetWaitPorcess( true );       // 设置正在等待DB处理
        }
        break;
    case ConsignmentDefine::Operate_TakeOut:
        {
            xOperate.bNeedDBAck = false;

            if ( nGameMoney != 0 )
            {
                if ( nGameMoney > pAccount->GetGameMoney()  )
                {
                    // ToLog
                    return;
                }
                pAccount->SetGameMoney( pAccount->GetGameMoney() - nGameMoney );
            }

            if ( nRMBMoney != 0 )
            {
                if ( nRMBMoney > pAccount->GetRMBMoney() )
                {
                    // ToLog
                    return;
                }
                pAccount->SetRMBMoney( pAccount->GetRMBMoney() - nRMBMoney );
            }

            xOperate.xAccount.Initialize( pAccount );
        }
        break;
    default:
        return;
    }

    if ( !xOperate.bNeedDBAck )
    {
        // 不需要回馈的直接发送给GameServer
        CS2GSOperateMoneyAck xAck;
        xAck.xAccount.Initialize( pAccount );
        xAck.uchOperate = uchOperate;
        xAck.nRMBMoney  = nRMBMoney;
        xAck.nGameMoney = nGameMoney;
        SendMessageToPlayer( nPlayerID, &xAck, false );
    }

    theMysqlCommunication.PushReqMessage( &xOperate, 0 );

    LOG_MESSAGE( AUCTIONOBJECT, LOG_PRIORITY_INFO, "玩家[%u]存取钱[%d]操作成功 金锭[%u]游戏币[%u], 账户金锭[%u]金币[%u] 发送给DB处理", 
        nPlayerID, uchOperate, nRMBMoney, nGameMoney, pAccount->GetRMBMoney(), pAccount->GetGameMoney() );
}

void ConsignmentManager::ProcessDBAccountOperate( const ConsignmentAccount& xAccount, unsigned char uchOperate, unsigned int nRMBMoney, unsigned int nGameMoney )
{
    Account* pAccount = GetConsignmentAccount( xAccount.GetPlayerID() );
    if ( pAccount == NULL )
    { return; }

    pAccount->Initialize( &xAccount );
    pAccount->SetWaitPorcess( false );

    CS2GSOperateMoneyAck xAck;
    xAck.xAccount.Initialize( pAccount );
    xAck.uchOperate = uchOperate;
    xAck.nRMBMoney  = nRMBMoney;
    xAck.nGameMoney = nGameMoney;
    SendMessageToPlayer( pAccount->GetPlayerID(), &xAck, false );

    LOG_MESSAGE( AUCTIONOBJECT, LOG_PRIORITY_INFO, "玩家[%u]存取钱数据库处理成功 账户金锭[%u]金币[%u]", 
        xAccount.GetPlayerID(), xAccount.GetRMBMoney(), xAccount.GetGameMoney() );
}

__int64 ConsignmentManager::CreateConsigmentID( unsigned int nPlayerID, __int64 n64Time )
{
    // 玩家ID放在最前面, 时间放在后32位中
    __int64 n64ConsignmentID = nPlayerID;
    n64ConsignmentID = n64ConsignmentID << 33;
    n64ConsignmentID |= n64Time;

    return n64ConsignmentID;
}

void ConsignmentManager::ProcessGameConsignmentMoney( unsigned int nPlayerID, ConsignmentBase& xConsignment, unsigned int nCostValue )
{
    Account* pAccount = GetConsignmentAccount( nPlayerID );
    if ( pAccount == NULL || pAccount->IsWaitProcess() )
    {
        MsgConsignmentMoneyAck xAck;
        xAck.uchResult = MsgConsignmentMoneyAck::ECD_SystemBusy;
        SendMessageToPlayer( nPlayerID, &xAck, true );

        SendOperateMessage( nPlayerID, false );

        LOG_MESSAGE( AUCTIONOBJECT, LOG_PRIORITY_INFO, "玩家[%u][%d]寄售订单[%I64u]失败, 单价[%u]数量[%u], 帐号正在等待DB回馈处理, 不接受寄售订单", 
            nPlayerID, xConsignment.GetType(), xConsignment.GetID(), xConsignment.GetPrice(), xConsignment.GetCount() );
        return;
    }

    unsigned int nValue = 0;
    switch ( xConsignment.GetType() )
    {
    case ConsignmentDefine::Consignment_SellRMB:
        {
            nValue = xConsignment.GetCount() + nCostValue;
            if ( nValue > pAccount->GetRMBMoney() )
            { return; }
        }
        break;
    case ConsignmentDefine::Consignment_BuyRMB:
        {
            nValue = xConsignment.GetCount() * xConsignment.GetPrice() + nCostValue;
            if ( nValue > pAccount->GetGameMoney() )
            { return; }
        }
        break;
    default:
        return;
    }

    // 算出一个世界唯一的ID, 如果有相同的, 就返回,等下次操作
    __int64 n64NowTime = TimeEx::GetCurrentTime().GetTime();
    xConsignment.SetStartTime( n64NowTime );

    // 创建寄售单ID
    __int64 n64ConsignmentID = CreateConsigmentID( nPlayerID, n64NowTime );
    xConsignment.SetID( n64ConsignmentID );

    // 加入寄售列表中
    if ( !AddConsignment( &xConsignment ) )
    {
        MsgConsignmentMoneyAck xAck;
        xAck.uchResult = MsgConsignmentMoneyAck::ECD_SystemBusy;
        SendMessageToPlayer( nPlayerID, &xAck, true );

        SendOperateMessage( nPlayerID, false );

        LOG_MESSAGE( AUCTIONOBJECT, LOG_PRIORITY_INFO, "玩家[%u][%d]寄售订单[%I64u]失败, 单价[%u]数量[%u], 服务器同时间接到两个请求, 不能分配ID", 
            nPlayerID, xConsignment.GetType(), xConsignment.GetID(), xConsignment.GetPrice(), xConsignment.GetCount() );
        return;
    }

    switch ( xConsignment.GetType() )
    {
    case ConsignmentDefine::Consignment_SellRMB:
        {
            pAccount->SetRMBMoney( pAccount->GetRMBMoney() - nValue );  // 扣金锭
        }
        break;
    case ConsignmentDefine::Consignment_BuyRMB:
        {
            pAccount->SetGameMoney( pAccount->GetGameMoney() - nValue );    // 扣游戏币
        }
        break;
    default:
        return;
    }

    // 加入历史记录中
    ConsignmentHistroy xHistroy;
    xHistroy.Initialize( &xConsignment );
    xHistroy.SetOperateID( nPlayerID );
    xHistroy.SetStatus( ConsignmentDefine::Status_Running );
    AddRMBHistroy( &xHistroy );
    
    // 同步帐号给GameServer
    SendAccountMessage( nPlayerID );

    // 发送列表给客户端
    SendConsignmentMoneyListMessage( nPlayerID, xConsignment.GetType(), ConsignmentDefine::Sort_Normal );

    // 世界广播
    SendConsignmentMoneyToWorld( xConsignment );

    // 保存到Database
    CS2DBConsignmentMoneyReq xReq;
    xReq.xAccount.Initialize( pAccount );
    xReq.xConsignment = xHistroy;
    theMysqlCommunication.PushReqMessage( &xReq, 0 );

    // 记录Log
    LOG_MESSAGE( AUCTIONOBJECT, LOG_PRIORITY_INFO, "玩家[%u][%d]寄售订单[%I64u]数据库处理成功, 指定玩家[%u], 单价[%u]数量[%u], 账户金锭[%u]金币[%u]", 
        nPlayerID, xConsignment.GetType(), xConsignment.GetID(), xConsignment.GetBuyPlayerID(), xConsignment.GetPrice(), xConsignment.GetCount(), pAccount->GetRMBMoney(), pAccount->GetGameMoney() );
}

//
void ConsignmentManager::ProcessGameConsignmentItem( unsigned int nPlayerID, ConsignmentData& xConsignment, unsigned int nCostValue )
{
	Account* pAccount = GetConsignmentAccount( nPlayerID );
	if ( pAccount == NULL || pAccount->IsWaitProcess() )
	{
		MsgConsignmentItemAck xAck;
		xAck.uchResult = MsgConsignmentItemAck::ECD_SystemBusy;
		SendMessageToPlayer( nPlayerID, &xAck, true );

		SendOperateMessage( nPlayerID, false );

		LOG_MESSAGE( AUCTIONOBJECT, LOG_PRIORITY_INFO, "玩家[%u][%d]寄售订单[%I64u]失败, 单价[%u]数量[%u], 帐号正在等待DB回馈处理, 不接受寄售订单", 
			nPlayerID, xConsignment.GetType(), xConsignment.GetID(), xConsignment.GetPrice(), xConsignment.GetCount() );
		return;
	}

	unsigned int nValue = 0;
	switch ( xConsignment.GetType() )
	{
	case ConsignmentDefine::Consignment_SellItem:
		{
			////////////////////////
			nValue = xConsignment.GetCount();
		}
		break;
	case ConsignmentDefine::Consignment_BuyItem:
		{
			nValue = xConsignment.GetCount() * xConsignment.GetPrice() + nCostValue;
			if ( nValue > pAccount->GetGameMoney() )
			{ return; }
		}
		break;
	default:
		return;
	}

	// 算出一个世界唯一的ID, 如果有相同的, 就返回,等下次操作
	__int64 n64NowTime = TimeEx::GetCurrentTime().GetTime();
	xConsignment.SetStartTime( n64NowTime );

	// 创建寄售单ID
	__int64 n64ConsignmentID = CreateConsigmentID( nPlayerID, n64NowTime );
	xConsignment.SetID( n64ConsignmentID );

	// 加入寄售列表中
	if ( !AddConsignment( &xConsignment ) )
	{
		MsgConsignmentItemAck xAck;
		xAck.uchResult = MsgConsignmentItemAck::ECD_SystemBusy;
		SendMessageToPlayer( nPlayerID, &xAck, true );

		SendOperateMessage( nPlayerID, false );

		LOG_MESSAGE( AUCTIONOBJECT, LOG_PRIORITY_INFO, "玩家[%u][%d]寄售订单[%I64u]失败, 单价[%u]数量[%u], 服务器同时间接到两个请求, 不能分配ID", 
			nPlayerID, xConsignment.GetType(), xConsignment.GetID(), xConsignment.GetPrice(), xConsignment.GetCount() );
		return;
	}

	//这儿怎么操作gameplayer中的成员
	switch ( xConsignment.GetType() )
	{
	case ConsignmentDefine::Consignment_SellItem:
		{
			//删除人物背包中寄售的物品
			//pAccount->SetRMBMoney( pAccount->GetRMBMoney() - nValue );  // 扣金锭
		}
		break;
	case ConsignmentDefine::Consignment_BuyItem:
		{
			pAccount->SetGameMoney( pAccount->GetGameMoney() - nValue );    // 扣游戏币
		}
		break;
	default:
		return;
	}

	// 加入历史记录中
	ConsignmentHistroy xHistroy;
	xHistroy.Initialize( &xConsignment );
	xHistroy.SetOperateID( nPlayerID );
	xHistroy.SetStatus( ConsignmentDefine::Status_Running );
	AddRMBHistroy( &xHistroy );

	// 同步帐号给GameServer
	SendAccountMessage( nPlayerID );

	// 发送列表给客户端
	SendConsignmentMoneyListMessage( nPlayerID, xConsignment.GetType(), ConsignmentDefine::Sort_Normal );

	// 世界广播
	SendConsignmentMoneyToWorld( xConsignment );

	// 保存到Database
	CS2DBConsignmentMoneyReq xReq;
	xReq.xAccount.Initialize( pAccount );
	xReq.xConsignment = xHistroy;
	theMysqlCommunication.PushReqMessage( &xReq, 0 );

	// 记录Log
	LOG_MESSAGE( AUCTIONOBJECT, LOG_PRIORITY_INFO, "玩家[%u][%d]寄售订单[%I64u]数据库处理成功, 指定玩家[%u], 单价[%u]数量[%u], 账户金锭[%u]金币[%u]", 
		nPlayerID, xConsignment.GetType(), xConsignment.GetID(), xConsignment.GetBuyPlayerID(), xConsignment.GetPrice(), xConsignment.GetCount(), pAccount->GetRMBMoney(), pAccount->GetGameMoney() );
}

// 全世界广播某人挂单
void ConsignmentManager::SendConsignmentMoneyToWorld( const ConsignmentBase& xConsignment )
{
    MsgTellConsignmentMoney xTell;
    xTell.uchConsignmentType = xConsignment.GetType();
    xTell.nPrice             = xConsignment.GetPrice();
    xTell.nCount             = xConsignment.GetCount();
    theGameServerManager.SendMsgToWorldUser( &xTell );
}

// 查询历史记录
void ConsignmentManager::ProcessQueryMoneyHistroy( unsigned int nPlayerID )
{
    const RMBHistroyVector* vecHistroy = GetRMBHistroy( nPlayerID );
    MsgShowConsignmentHistroy xHistroy;
    if ( vecHistroy != NULL )
    {
        for ( RMBHistroyVectorConstIter iter = vecHistroy->begin(); iter != vecHistroy->end(); ++iter )
        {
            xHistroy.AddConsignmentHistroy( *iter );
        }
    }

    SendMessageToPlayer( nPlayerID, &xHistroy, true );
    SendOperateMessage( nPlayerID, false );
}

const ConsignmentManager::RMBHistroyVector* ConsignmentManager::GetRMBHistroy( unsigned int nPlayerID )
{
    RMBHistroyMapIter iter = m_mapRMBHistroy.find( nPlayerID );
    if ( iter == m_mapRMBHistroy.end() )
    { return NULL; }

    return &( iter->second );
}

ConsignmentManager::RMBHistroy* ConsignmentManager::GetRMBHistory( unsigned int nPlayerID, __int64 nConsignmentID )
{
    RMBHistroyMapIter iter = m_mapRMBHistroy.find( nPlayerID );
    if ( iter == m_mapRMBHistroy.end() )
    { return NULL; }

    RMBHistroyVectorIter viter = std::find_if( iter->second.begin(), iter->second.end(), EqualHistroy< RMBHistroy >( nConsignmentID ) );
    if ( viter == iter->second.end() )
    { return NULL; }

    return *viter;
}

void ConsignmentManager::ProcessConsignmentOperate( unsigned int nPlayerID, __int64 nConsignmentID, unsigned char uchConsignmentType, unsigned char uchOperate )
{
    switch ( uchConsignmentType )
    {
    case ConsignmentDefine::Consignment_BuyRMB:
    case ConsignmentDefine::Consignment_SellRMB:
        {
            ProcessConsignmentMoneyOperate( nPlayerID, nConsignmentID, uchConsignmentType, uchOperate );
        }
        break;
    default:
        break;
    }
}

// 处理金锭寄售单操作
void ConsignmentManager::ProcessConsignmentMoneyOperate( unsigned int nPlayerID, __int64 nConsignmentID, unsigned char uchConsignmentType, unsigned char uchOperate )
{
    MsgConsignmentOperateAck xAck;

    __int64 n64NowTime = TimeEx::GetCurrentTime().GetTime();

    // 保存数据库请求
    CS2DBConsignmentmoneyOperateReq xReq;
    xReq.nConsignmentID = nConsignmentID;
    xReq.n64EndTime = n64NowTime;

    // 寄售单
    Consignment* pConsignment = GetConsignmentMoney( nConsignmentID, uchConsignmentType );
    if ( pConsignment == NULL )
    {
        xAck.uchResult = MsgConsignmentOperateAck::ECD_ConsignmentSelled;
        SendMessageToPlayer( nPlayerID, &xAck, true );
        SendOperateMessage( nPlayerID, false );
        return;
    }

    if ( pConsignment->IsWaitProcess() )
    {
        xAck.uchResult = MsgConsignmentOperateAck::ECD_ConsignmentProcess;
        SendMessageToPlayer( nPlayerID, &xAck, true );
        SendOperateMessage( nPlayerID, false );
        return;
    }
    
    // 操作方帐号
    Account* pOperateAccount = GetConsignmentAccount( nPlayerID );
    if ( pOperateAccount == NULL || pOperateAccount->IsWaitProcess() )
    {
        xAck.uchResult = MsgConsignmentOperateAck::ECD_SystemBusy;
        SendMessageToPlayer( nPlayerID, &xAck, true );
        SendOperateMessage( nPlayerID, false );
        return;
    }

    // 寄售单方帐号
    Account* pSellerAccount = GetConsignmentAccount( pConsignment->GetSellPlayerID() );
    if ( pSellerAccount == NULL || pSellerAccount->IsWaitProcess() )
    {
        xAck.uchResult = MsgConsignmentOperateAck::ECD_SystemBusy;
        SendMessageToPlayer( nPlayerID, &xAck, true );
        SendOperateMessage( nPlayerID, false );
        return;
    }

    // 操作人插入记录
    xReq.xNewHistroy.Initialize( pConsignment );
    xReq.xNewHistroy.SetID( CreateConsigmentID( nPlayerID, n64NowTime ) );
    xReq.xNewHistroy.SetStartTime( n64NowTime );
    xReq.xNewHistroy.SetEndTime( n64NowTime );

    switch ( uchOperate )
    {
    case ConsignmentDefine::Operate_Buy:
        {
            if ( pConsignment->GetType() != ConsignmentDefine::Consignment_SellRMB )
            {
                xAck.uchResult = MsgConsignmentOperateAck::ECD_ErrorOperate;
                SendMessageToPlayer( nPlayerID, &xAck, true );
                SendOperateMessage( nPlayerID, false );
                return;
            }

            if ( pConsignment->GetSellPlayerID() == nPlayerID )
            {
                xAck.uchResult = MsgConsignmentOperateAck::ECD_CanNotOperateSelf;
                SendMessageToPlayer( nPlayerID, &xAck, true );
                SendOperateMessage( nPlayerID, false );
                return;
            }

            if ( pConsignment->GetBuyPlayerID() != ConsignmentDefine::NoneID )
            {
                if ( nPlayerID != pConsignment->GetBuyPlayerID() )
                {   
                    xAck.uchResult = MsgConsignmentOperateAck::ECD_NotAppointPlayer;
                    SendMessageToPlayer( nPlayerID, &xAck, true );
                    SendOperateMessage( nPlayerID, false );
                    return;
                }
            }
            
            unsigned int nValue = pConsignment->GetPrice() * pConsignment->GetCount();
            if ( nValue > pOperateAccount->GetGameMoney() )
            {
                xAck.uchResult = MsgConsignmentOperateAck::ECD_NotEnoughMoney;
                SendMessageToPlayer( nPlayerID, &xAck, true );
                SendOperateMessage( nPlayerID, false );
                return;
            }

            xReq.xOperaterAccount.Initialize( pOperateAccount );

            // 算出买方扣钱加金锭
            xReq.xOperaterAccount.SetRMBMoney( xReq.xOperaterAccount.GetRMBMoney() + pConsignment->GetCount() );
            xReq.xOperaterAccount.SetGameMoney( xReq.xOperaterAccount.GetGameMoney() - nValue );

            pOperateAccount->SetWaitPorcess( true );

            // 卖方加钱
            xReq.xSellerAccount.Initialize( pSellerAccount );
            xReq.xSellerAccount.SetGameMoney( xReq.xSellerAccount.GetGameMoney() + nValue );

            // 设置正在处理中
            pSellerAccount->SetWaitPorcess( true );
            SendOperateMessage( pSellerAccount->GetPlayerID(), true );  

            // 修改历史记录
            xReq.uchEndStatus = ConsignmentDefine::Status_Selled;

            // 操作方历史记录
            xReq.xNewHistroy.SetOperateID( nPlayerID );
            xReq.xNewHistroy.SetStatus( ConsignmentDefine::Status_BuySuccess );
        }
        break;
    case ConsignmentDefine::Operate_Sell:
        {
            if ( pConsignment->GetType() != ConsignmentDefine::Consignment_BuyRMB )
            {
                xAck.uchResult = MsgConsignmentOperateAck::ECD_ErrorOperate;
                SendMessageToPlayer( nPlayerID, &xAck, true );
                SendOperateMessage( nPlayerID, false );
                return;
            }

            if ( pConsignment->GetSellPlayerID() == nPlayerID )
            {
                xAck.uchResult = MsgConsignmentOperateAck::ECD_CanNotOperateSelf;
                SendMessageToPlayer( nPlayerID, &xAck, true );
                SendOperateMessage( nPlayerID, false );
                return;
            }

            if ( pConsignment->GetBuyPlayerID() != ConsignmentDefine::NoneID )
            {
                if ( nPlayerID != pConsignment->GetBuyPlayerID() )
                {   
                    xAck.uchResult = MsgConsignmentOperateAck::ECD_NotAppointPlayer;
                    SendMessageToPlayer( nPlayerID, &xAck, true );
                    SendOperateMessage( nPlayerID, false );
                    return;
                }
            }

            if ( pConsignment->GetCount() > pOperateAccount->GetRMBMoney() )
            {
                xAck.uchResult = MsgConsignmentOperateAck::ECD_NotEnoughJinDing;
                SendMessageToPlayer( nPlayerID, &xAck, true );
                SendOperateMessage( nPlayerID, false );
                return;
            }

            xReq.xOperaterAccount.Initialize( pOperateAccount );
            // 出售方扣金锭加钱
            unsigned int nValue = pConsignment->GetPrice() * pConsignment->GetCount();
            xReq.xOperaterAccount.SetRMBMoney( xReq.xOperaterAccount.GetRMBMoney() - pConsignment->GetCount() );
            xReq.xOperaterAccount.SetGameMoney( pOperateAccount->GetGameMoney() + nValue );

            pOperateAccount->SetWaitPorcess( true );
            
            // 购买方加金锭
            xReq.xSellerAccount.Initialize( pSellerAccount );
            xReq.xSellerAccount.SetRMBMoney( xReq.xSellerAccount.GetRMBMoney() + pConsignment->GetCount() );

            pSellerAccount->SetWaitPorcess( true );
            SendOperateMessage( pSellerAccount->GetPlayerID(), true );  

            // 修改历史记录
            xReq.uchEndStatus = ConsignmentDefine::Status_Buyed;

            // 操作方添加历史记录
            xReq.xNewHistroy.SetOperateID( nPlayerID );
            xReq.xNewHistroy.SetStatus( ConsignmentDefine::Status_SellSuccess );
        }
        break;
    case ConsignmentDefine::Operate_Cancel:
    case ConsignmentDefine::Operate_TimeOut:
        {
            if ( pConsignment->GetSellPlayerID() != nPlayerID )
            {
                xAck.uchResult = MsgConsignmentOperateAck::ECD_CanNotCancelOther;
                SendMessageToPlayer( nPlayerID, &xAck, true );
                SendOperateMessage( nPlayerID, false );
                return;
            }

            // 钱返还
            xReq.xOperaterAccount.Initialize( pOperateAccount );
            pOperateAccount->SetWaitPorcess( true );

            switch ( pConsignment->GetType() )
            {
            case ConsignmentDefine::Consignment_BuyRMB:
                {
                    xReq.xOperaterAccount.SetGameMoney( xReq.xOperaterAccount.GetGameMoney() + pConsignment->GetPrice() * pConsignment->GetCount() );
                }
                break;
            case ConsignmentDefine::Consignment_SellRMB:
                {
                    xReq.xOperaterAccount.SetRMBMoney( xReq.xOperaterAccount.GetRMBMoney() + pConsignment->GetCount() );
                }
                break;
            default:
                break;
            }

            if ( uchOperate == ConsignmentDefine::Operate_Cancel )
            {
                xReq.uchEndStatus = ConsignmentDefine::Status_Cancel;
            }
            else
            {
                SendOperateMessage( nPlayerID, true );
                xReq.uchEndStatus = ConsignmentDefine::Status_TimeOut;
            }
        }
        break;
    default:
        return;
    }

    // 设置订单在处理中
    pConsignment->SetWaitPorcess( true );
    theMysqlCommunication.PushReqMessage( &xReq, 0 );

    LOG_MESSAGE( AUCTIONOBJECT, LOG_PRIORITY_INFO, "玩家[%u]操作[%d]寄售订单[%I64u]成功, 单价[%u]数量[%u], 等待数据库处理回馈",
        nPlayerID, uchOperate, pConsignment->GetID(), pConsignment->GetPrice(), pConsignment->GetCount() );
}

void ConsignmentManager::ProcessDBConsignmentmoneyOperate( const ConsignmentAccount& xOperateAccount, const ConsignmentAccount& xSellerAccount, __int64 nConsignmentID, 
                                                          unsigned char uchEndStatus, __int64 n64EndTime, const ConsignmentHistroy& xNewHistroy )
{
    // 操作人帐号
    Account* pOperateAccount = GetConsignmentAccount( xOperateAccount.GetPlayerID() );
    if ( pOperateAccount != NULL )
    { 
        pOperateAccount->Initialize( &xOperateAccount );
        pOperateAccount->SetWaitPorcess( false );

        SendAccountMessage( pOperateAccount );
    }

    // 挂单人帐号
    if ( xSellerAccount.GetPlayerID() != ConsignmentDefine::NoneID )
    {
        Account* pSellerAccount = GetConsignmentAccount( xSellerAccount.GetPlayerID() );
        if ( pSellerAccount != NULL )
        {
            pSellerAccount->Initialize( &xSellerAccount );
            pSellerAccount->SetWaitPorcess( false );

            SendAccountMessage( pSellerAccount );
        }
    }

    // 删除一个寄售单
    RemoveConsignment( nConsignmentID, xNewHistroy.GetType() );
    // 通知客户端成功, 删除寄售列表
    if ( uchEndStatus != ConsignmentDefine::Status_TimeOut )
    {
        MsgConsignmentOperateAck xAck;
        xAck.uchResult          = MsgConsignmentOperateAck::ECD_Success;
        xAck.n64ConsignmentID   = nConsignmentID;
        xAck.uchConsignmentType = xNewHistroy.GetType();
        xAck.n64EndTime         = n64EndTime;
        xAck.uchEndStatus       = uchEndStatus;
        SendMessageToPlayer( xOperateAccount.GetPlayerID(), &xAck, true );
    }

    // 修改历史记录
    RMBHistroy* pHistroy = NULL;
    switch ( uchEndStatus )
    {
    case ConsignmentDefine::Status_Cancel:
    case ConsignmentDefine::Status_TimeOut:
        pHistroy = GetRMBHistory( xOperateAccount.GetPlayerID(), nConsignmentID );
        break;
    default:
        pHistroy = GetRMBHistory( xSellerAccount.GetPlayerID(), nConsignmentID );
        break;
    }

    if ( pHistroy != NULL )
    {
        pHistroy->SetStatus( uchEndStatus );
        pHistroy->SetEndTime( n64EndTime );
    }

    // 出入一个新的历史记录
    if ( xNewHistroy.GetOperateID() != ConsignmentDefine::NoneID )
    {
        AddRMBHistroy( &xNewHistroy );
    }

    LOG_MESSAGE( AUCTIONOBJECT, LOG_PRIORITY_INFO, "寄售订单[%I64u]数据库处理成功, 玩家[%u]帐户金锭[%u]金币[%u], 玩家[%u]帐户金锭[%u]金币[%u]", 
        nConsignmentID, xOperateAccount.GetPlayerID(), xOperateAccount.GetRMBMoney(), xOperateAccount.GetGameMoney(), xSellerAccount.GetPlayerID(), xSellerAccount.GetRMBMoney(), xSellerAccount.GetGameMoney() );
}

void ConsignmentManager::ProcessSellRMBTimeOut()
{
    for ( SellRMBMapIter iter = m_mapSellRMB.begin(); iter != m_mapSellRMB.end(); ++iter )
    {
        SellRMB* pSellRMB = iter->second;
        if ( TimeEx::IsPassCurrentTime( pSellRMB->GetStartTime(), ConsignmentDefine::MaxConsignmentTime ) )
        {
            ProcessConsignmentMoneyOperate( pSellRMB->GetSellPlayerID(), pSellRMB->GetID(), ConsignmentDefine::Consignment_SellRMB, ConsignmentDefine::Operate_TimeOut );
        }
    }
}

void ConsignmentManager::ProcessBuyRMBTimeOut()
{
    for ( BuyRMBMapIter iter = m_mapBuyRMB.begin(); iter != m_mapBuyRMB.end(); ++iter )
    {
        BuyRMB* pBuyRMB = iter->second;
        if ( TimeEx::IsPassCurrentTime( pBuyRMB->GetStartTime(), ConsignmentDefine::MaxConsignmentTime ) )
        {
            ProcessConsignmentMoneyOperate( pBuyRMB->GetSellPlayerID(), pBuyRMB->GetID(), ConsignmentDefine::Consignment_BuyRMB, ConsignmentDefine::Operate_TimeOut );
        }
    }
}