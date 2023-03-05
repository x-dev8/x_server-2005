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

    // �����������
    ProcessLoadConsignmentData( nCurrentTime );

    // ������ڵļ��۵�
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

    // �������ݿ����
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
    case ConsignmentDefine::Sort_Count:     // ָ������
        std::for_each( m_mapSellRMB.begin(), m_mapSellRMB.end(), CopyConsignmentMoneyListCount< SellRMBPair, SellRMBVector >( m_vecSellRMB, nValue ) );
        std::sort( m_vecSellRMB.begin(), m_vecSellRMB.end(), SortByLessPrice< SellRMB >() );
        break;
    case ConsignmentDefine::Sort_ForMe:     // ָ������
        std::for_each( m_mapSellRMB.begin(), m_mapSellRMB.end(), CopyConsignmentMoneyListForMe< SellRMBPair, SellRMBVector >( m_vecSellRMB, nValue ) );
        break;
    case ConsignmentDefine::Sort_MySelf:    // ���Լ�������
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
            case ConsignmentDefine::Sort_Date:  // ����������
                std::sort( m_vecSellRMB.begin(), m_vecSellRMB.end(), SortByDate< SellRMB >() );
                break;
            case ConsignmentDefine::Sort_LessPrice: // ��Ǯ��С��������
                std::sort( m_vecSellRMB.begin(), m_vecSellRMB.end(), SortByLessPrice< SellRMB >() );
                break;
            case ConsignmentDefine::Sort_GreaterPrice:  // ��Ǯ�Ӵ�С
                std::sort( m_vecSellRMB.begin(), m_vecSellRMB.end(), SortByGreaterPrice< SellRMB >() );
                break;
            case ConsignmentDefine::Sort_LessCount: // ������С����
                std::sort( m_vecSellRMB.begin(), m_vecSellRMB.end(), SortByLessCount< SellRMB >() );
                break;
            case ConsignmentDefine::Sort_GreaterCount:  // �����Ӵ�С
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
    case ConsignmentDefine::Sort_Count:     // ָ������
        std::for_each( m_mapBuyRMB.begin(), m_mapBuyRMB.end(), CopyConsignmentMoneyListCount< BuyRMBPair, BuyRMBVector >( m_vecBuyRMB, nValue ) );
        std::sort( m_vecBuyRMB.begin(), m_vecBuyRMB.end(), SortByLessPrice< BuyRMB >() );
        break;
    case ConsignmentDefine::Sort_ForMe:     // ָ������
        std::for_each( m_mapBuyRMB.begin(), m_mapBuyRMB.end(), CopyConsignmentMoneyListForMe< BuyRMBPair, BuyRMBVector >( m_vecBuyRMB, nValue ) );
        break;
    case ConsignmentDefine::Sort_MySelf:    // ���Լ�������
        std::for_each( m_mapBuyRMB.begin(), m_mapBuyRMB.end(), CopyConsignmentMoneyListSelf< BuyRMBPair, BuyRMBVector >( m_vecBuyRMB, nValue ) );
        break;
    default:
        {
            std::for_each( m_mapBuyRMB.begin(), m_mapBuyRMB.end(), CopyConsignmentMoneyList< BuyRMBPair, BuyRMBVector >( m_vecBuyRMB ) );

            switch( uchSortType )
            {
            case ConsignmentDefine::Sort_Normal:  // Ĭ��
                std::sort( m_vecBuyRMB.begin(), m_vecBuyRMB.end(), SortByGreaterPrice< BuyRMB >() );
                break;
            case ConsignmentDefine::Sort_Date:  // ����������
                std::sort( m_vecBuyRMB.begin(), m_vecBuyRMB.end(), SortByDate< BuyRMB >() );
                break;
            case ConsignmentDefine::Sort_LessPrice:     // ��Ǯ��С��������
                std::sort( m_vecBuyRMB.begin(), m_vecBuyRMB.end(), SortByLessPrice< BuyRMB >() );
                break;
            case ConsignmentDefine::Sort_GreaterPrice:  // ��Ǯ�Ӵ�С
                std::sort( m_vecBuyRMB.begin(), m_vecBuyRMB.end(), SortByGreaterPrice< BuyRMB >() );
                break;
            case ConsignmentDefine::Sort_LessCount:     // ������С����
                std::sort( m_vecBuyRMB.begin(), m_vecBuyRMB.end(), SortByLessCount< BuyRMB >() );
                break;
            case ConsignmentDefine::Sort_GreaterCount:  // �����Ӵ�С
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

    // �ȴ�������
    switch ( uchConsignmentType )
    {
    case ConsignmentDefine::Consignment_SellRMB:    // ���۽𶧼��۵�
        {
            int nCount = 0;
            for ( SellRMBVectorIter iter = m_vecSellRMB.begin(); iter != m_vecSellRMB.end() && nCount < ConsignmentDefine::MaxConsignmentCount; ++iter, ++nCount )
            {
                xList.AddConsignmentMoney( *iter );
            }
            xList.uchShowType = MsgShowConsignmentMoneyList::Show_SellRMB;
        }
        break;
    case ConsignmentDefine::Consignment_BuyRMB:     // ����𶧼��۵�
        {
            int nCount = 0;
            for ( BuyRMBVectorIter iter = m_vecBuyRMB.begin(); iter != m_vecBuyRMB.end() && nCount < ConsignmentDefine::MaxConsignmentCount; ++iter, ++nCount )
            {
                xList.AddConsignmentMoney( *iter );
            }
            xList.uchShowType = MsgShowConsignmentMoneyList::Show_BuyRMB;
        }
        break;
    default:    // Ĭ����������ʾ
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

            pAccount->SetWaitPorcess( true );       // �������ڵȴ�DB����
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
        // ����Ҫ������ֱ�ӷ��͸�GameServer
        CS2GSOperateMoneyAck xAck;
        xAck.xAccount.Initialize( pAccount );
        xAck.uchOperate = uchOperate;
        xAck.nRMBMoney  = nRMBMoney;
        xAck.nGameMoney = nGameMoney;
        SendMessageToPlayer( nPlayerID, &xAck, false );
    }

    theMysqlCommunication.PushReqMessage( &xOperate, 0 );

    LOG_MESSAGE( AUCTIONOBJECT, LOG_PRIORITY_INFO, "���[%u]��ȡǮ[%d]�����ɹ� ��[%u]��Ϸ��[%u], �˻���[%u]���[%u] ���͸�DB����", 
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

    LOG_MESSAGE( AUCTIONOBJECT, LOG_PRIORITY_INFO, "���[%u]��ȡǮ���ݿ⴦��ɹ� �˻���[%u]���[%u]", 
        xAccount.GetPlayerID(), xAccount.GetRMBMoney(), xAccount.GetGameMoney() );
}

__int64 ConsignmentManager::CreateConsigmentID( unsigned int nPlayerID, __int64 n64Time )
{
    // ���ID������ǰ��, ʱ����ں�32λ��
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

        LOG_MESSAGE( AUCTIONOBJECT, LOG_PRIORITY_INFO, "���[%u][%d]���۶���[%I64u]ʧ��, ����[%u]����[%u], �ʺ����ڵȴ�DB��������, �����ܼ��۶���", 
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

    // ���һ������Ψһ��ID, �������ͬ��, �ͷ���,���´β���
    __int64 n64NowTime = TimeEx::GetCurrentTime().GetTime();
    xConsignment.SetStartTime( n64NowTime );

    // �������۵�ID
    __int64 n64ConsignmentID = CreateConsigmentID( nPlayerID, n64NowTime );
    xConsignment.SetID( n64ConsignmentID );

    // ��������б���
    if ( !AddConsignment( &xConsignment ) )
    {
        MsgConsignmentMoneyAck xAck;
        xAck.uchResult = MsgConsignmentMoneyAck::ECD_SystemBusy;
        SendMessageToPlayer( nPlayerID, &xAck, true );

        SendOperateMessage( nPlayerID, false );

        LOG_MESSAGE( AUCTIONOBJECT, LOG_PRIORITY_INFO, "���[%u][%d]���۶���[%I64u]ʧ��, ����[%u]����[%u], ������ͬʱ��ӵ���������, ���ܷ���ID", 
            nPlayerID, xConsignment.GetType(), xConsignment.GetID(), xConsignment.GetPrice(), xConsignment.GetCount() );
        return;
    }

    switch ( xConsignment.GetType() )
    {
    case ConsignmentDefine::Consignment_SellRMB:
        {
            pAccount->SetRMBMoney( pAccount->GetRMBMoney() - nValue );  // �۽�
        }
        break;
    case ConsignmentDefine::Consignment_BuyRMB:
        {
            pAccount->SetGameMoney( pAccount->GetGameMoney() - nValue );    // ����Ϸ��
        }
        break;
    default:
        return;
    }

    // ������ʷ��¼��
    ConsignmentHistroy xHistroy;
    xHistroy.Initialize( &xConsignment );
    xHistroy.SetOperateID( nPlayerID );
    xHistroy.SetStatus( ConsignmentDefine::Status_Running );
    AddRMBHistroy( &xHistroy );
    
    // ͬ���ʺŸ�GameServer
    SendAccountMessage( nPlayerID );

    // �����б���ͻ���
    SendConsignmentMoneyListMessage( nPlayerID, xConsignment.GetType(), ConsignmentDefine::Sort_Normal );

    // ����㲥
    SendConsignmentMoneyToWorld( xConsignment );

    // ���浽Database
    CS2DBConsignmentMoneyReq xReq;
    xReq.xAccount.Initialize( pAccount );
    xReq.xConsignment = xHistroy;
    theMysqlCommunication.PushReqMessage( &xReq, 0 );

    // ��¼Log
    LOG_MESSAGE( AUCTIONOBJECT, LOG_PRIORITY_INFO, "���[%u][%d]���۶���[%I64u]���ݿ⴦��ɹ�, ָ�����[%u], ����[%u]����[%u], �˻���[%u]���[%u]", 
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

		LOG_MESSAGE( AUCTIONOBJECT, LOG_PRIORITY_INFO, "���[%u][%d]���۶���[%I64u]ʧ��, ����[%u]����[%u], �ʺ����ڵȴ�DB��������, �����ܼ��۶���", 
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

	// ���һ������Ψһ��ID, �������ͬ��, �ͷ���,���´β���
	__int64 n64NowTime = TimeEx::GetCurrentTime().GetTime();
	xConsignment.SetStartTime( n64NowTime );

	// �������۵�ID
	__int64 n64ConsignmentID = CreateConsigmentID( nPlayerID, n64NowTime );
	xConsignment.SetID( n64ConsignmentID );

	// ��������б���
	if ( !AddConsignment( &xConsignment ) )
	{
		MsgConsignmentItemAck xAck;
		xAck.uchResult = MsgConsignmentItemAck::ECD_SystemBusy;
		SendMessageToPlayer( nPlayerID, &xAck, true );

		SendOperateMessage( nPlayerID, false );

		LOG_MESSAGE( AUCTIONOBJECT, LOG_PRIORITY_INFO, "���[%u][%d]���۶���[%I64u]ʧ��, ����[%u]����[%u], ������ͬʱ��ӵ���������, ���ܷ���ID", 
			nPlayerID, xConsignment.GetType(), xConsignment.GetID(), xConsignment.GetPrice(), xConsignment.GetCount() );
		return;
	}

	//�����ô����gameplayer�еĳ�Ա
	switch ( xConsignment.GetType() )
	{
	case ConsignmentDefine::Consignment_SellItem:
		{
			//ɾ�����ﱳ���м��۵���Ʒ
			//pAccount->SetRMBMoney( pAccount->GetRMBMoney() - nValue );  // �۽�
		}
		break;
	case ConsignmentDefine::Consignment_BuyItem:
		{
			pAccount->SetGameMoney( pAccount->GetGameMoney() - nValue );    // ����Ϸ��
		}
		break;
	default:
		return;
	}

	// ������ʷ��¼��
	ConsignmentHistroy xHistroy;
	xHistroy.Initialize( &xConsignment );
	xHistroy.SetOperateID( nPlayerID );
	xHistroy.SetStatus( ConsignmentDefine::Status_Running );
	AddRMBHistroy( &xHistroy );

	// ͬ���ʺŸ�GameServer
	SendAccountMessage( nPlayerID );

	// �����б���ͻ���
	SendConsignmentMoneyListMessage( nPlayerID, xConsignment.GetType(), ConsignmentDefine::Sort_Normal );

	// ����㲥
	SendConsignmentMoneyToWorld( xConsignment );

	// ���浽Database
	CS2DBConsignmentMoneyReq xReq;
	xReq.xAccount.Initialize( pAccount );
	xReq.xConsignment = xHistroy;
	theMysqlCommunication.PushReqMessage( &xReq, 0 );

	// ��¼Log
	LOG_MESSAGE( AUCTIONOBJECT, LOG_PRIORITY_INFO, "���[%u][%d]���۶���[%I64u]���ݿ⴦��ɹ�, ָ�����[%u], ����[%u]����[%u], �˻���[%u]���[%u]", 
		nPlayerID, xConsignment.GetType(), xConsignment.GetID(), xConsignment.GetBuyPlayerID(), xConsignment.GetPrice(), xConsignment.GetCount(), pAccount->GetRMBMoney(), pAccount->GetGameMoney() );
}

// ȫ����㲥ĳ�˹ҵ�
void ConsignmentManager::SendConsignmentMoneyToWorld( const ConsignmentBase& xConsignment )
{
    MsgTellConsignmentMoney xTell;
    xTell.uchConsignmentType = xConsignment.GetType();
    xTell.nPrice             = xConsignment.GetPrice();
    xTell.nCount             = xConsignment.GetCount();
    theGameServerManager.SendMsgToWorldUser( &xTell );
}

// ��ѯ��ʷ��¼
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

// ����𶧼��۵�����
void ConsignmentManager::ProcessConsignmentMoneyOperate( unsigned int nPlayerID, __int64 nConsignmentID, unsigned char uchConsignmentType, unsigned char uchOperate )
{
    MsgConsignmentOperateAck xAck;

    __int64 n64NowTime = TimeEx::GetCurrentTime().GetTime();

    // �������ݿ�����
    CS2DBConsignmentmoneyOperateReq xReq;
    xReq.nConsignmentID = nConsignmentID;
    xReq.n64EndTime = n64NowTime;

    // ���۵�
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
    
    // �������ʺ�
    Account* pOperateAccount = GetConsignmentAccount( nPlayerID );
    if ( pOperateAccount == NULL || pOperateAccount->IsWaitProcess() )
    {
        xAck.uchResult = MsgConsignmentOperateAck::ECD_SystemBusy;
        SendMessageToPlayer( nPlayerID, &xAck, true );
        SendOperateMessage( nPlayerID, false );
        return;
    }

    // ���۵����ʺ�
    Account* pSellerAccount = GetConsignmentAccount( pConsignment->GetSellPlayerID() );
    if ( pSellerAccount == NULL || pSellerAccount->IsWaitProcess() )
    {
        xAck.uchResult = MsgConsignmentOperateAck::ECD_SystemBusy;
        SendMessageToPlayer( nPlayerID, &xAck, true );
        SendOperateMessage( nPlayerID, false );
        return;
    }

    // �����˲����¼
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

            // ����򷽿�Ǯ�ӽ�
            xReq.xOperaterAccount.SetRMBMoney( xReq.xOperaterAccount.GetRMBMoney() + pConsignment->GetCount() );
            xReq.xOperaterAccount.SetGameMoney( xReq.xOperaterAccount.GetGameMoney() - nValue );

            pOperateAccount->SetWaitPorcess( true );

            // ������Ǯ
            xReq.xSellerAccount.Initialize( pSellerAccount );
            xReq.xSellerAccount.SetGameMoney( xReq.xSellerAccount.GetGameMoney() + nValue );

            // �������ڴ�����
            pSellerAccount->SetWaitPorcess( true );
            SendOperateMessage( pSellerAccount->GetPlayerID(), true );  

            // �޸���ʷ��¼
            xReq.uchEndStatus = ConsignmentDefine::Status_Selled;

            // ��������ʷ��¼
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
            // ���۷��۽𶧼�Ǯ
            unsigned int nValue = pConsignment->GetPrice() * pConsignment->GetCount();
            xReq.xOperaterAccount.SetRMBMoney( xReq.xOperaterAccount.GetRMBMoney() - pConsignment->GetCount() );
            xReq.xOperaterAccount.SetGameMoney( pOperateAccount->GetGameMoney() + nValue );

            pOperateAccount->SetWaitPorcess( true );
            
            // ���򷽼ӽ�
            xReq.xSellerAccount.Initialize( pSellerAccount );
            xReq.xSellerAccount.SetRMBMoney( xReq.xSellerAccount.GetRMBMoney() + pConsignment->GetCount() );

            pSellerAccount->SetWaitPorcess( true );
            SendOperateMessage( pSellerAccount->GetPlayerID(), true );  

            // �޸���ʷ��¼
            xReq.uchEndStatus = ConsignmentDefine::Status_Buyed;

            // �����������ʷ��¼
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

            // Ǯ����
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

    // ���ö����ڴ�����
    pConsignment->SetWaitPorcess( true );
    theMysqlCommunication.PushReqMessage( &xReq, 0 );

    LOG_MESSAGE( AUCTIONOBJECT, LOG_PRIORITY_INFO, "���[%u]����[%d]���۶���[%I64u]�ɹ�, ����[%u]����[%u], �ȴ����ݿ⴦�����",
        nPlayerID, uchOperate, pConsignment->GetID(), pConsignment->GetPrice(), pConsignment->GetCount() );
}

void ConsignmentManager::ProcessDBConsignmentmoneyOperate( const ConsignmentAccount& xOperateAccount, const ConsignmentAccount& xSellerAccount, __int64 nConsignmentID, 
                                                          unsigned char uchEndStatus, __int64 n64EndTime, const ConsignmentHistroy& xNewHistroy )
{
    // �������ʺ�
    Account* pOperateAccount = GetConsignmentAccount( xOperateAccount.GetPlayerID() );
    if ( pOperateAccount != NULL )
    { 
        pOperateAccount->Initialize( &xOperateAccount );
        pOperateAccount->SetWaitPorcess( false );

        SendAccountMessage( pOperateAccount );
    }

    // �ҵ����ʺ�
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

    // ɾ��һ�����۵�
    RemoveConsignment( nConsignmentID, xNewHistroy.GetType() );
    // ֪ͨ�ͻ��˳ɹ�, ɾ�������б�
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

    // �޸���ʷ��¼
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

    // ����һ���µ���ʷ��¼
    if ( xNewHistroy.GetOperateID() != ConsignmentDefine::NoneID )
    {
        AddRMBHistroy( &xNewHistroy );
    }

    LOG_MESSAGE( AUCTIONOBJECT, LOG_PRIORITY_INFO, "���۶���[%I64u]���ݿ⴦��ɹ�, ���[%u]�ʻ���[%u]���[%u], ���[%u]�ʻ���[%u]���[%u]", 
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