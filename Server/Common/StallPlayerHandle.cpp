#include "GamePlayer.h"
#include "BargainingManager.h"
#include "Configure.h"
#include "ShareData.h"
#include "StallInfoQuery.h"
#include "chatcheck.h"
#include "XmlStringLanguage.h"
#include "GameWorld.h"
#include "LogEventService.h"

bool GamePlayer::ProcessStallMsg( Msg* pMsg )
{
    DWORD dwType = pMsg->GetType();

    GAMESERVER_MESSAGE_MAPPING_BEGIN
        GAMESERVER_MESSAGE_HANDLE( MSG_STARTSTALLREQ, OnMsgStartStallReq );
        GAMESERVER_MESSAGE_HANDLE( MSG_CLOSESTALLREQ, OnMsgCloseStallReq );
        GAMESERVER_MESSAGE_HANDLE( MSG_OPENSTALLREQ, OnMsgOpenStallReq );
        GAMESERVER_MESSAGE_HANDLE( MSG_BUYSTALLREQ, OnMsgBuyStallReq );
        GAMESERVER_MESSAGE_HANDLE( MSG_SELLSTALLREQ, OnMsgSellStallReq );
        GAMESERVER_MESSAGE_HANDLE( MSG_ADDSELLDATAREQ, OnMsgAddSellDataReq );
        GAMESERVER_MESSAGE_HANDLE( MSG_ADDBUYDATAREQ, OnMsgAddBuyDataReq );
        GAMESERVER_MESSAGE_HANDLE( MSG_MOVESELLDATAREQ, OnMsgMoveStallDataReq );
        GAMESERVER_MESSAGE_HANDLE( MSG_REMOVESELLDATAREQ, OnMsgRemoveStallDataReq );
        GAMESERVER_MESSAGE_HANDLE( MSG_CHANGESTALLTITLEREQ, OnMsgChangeStallTitleReq );
        GAMESERVER_MESSAGE_HANDLE( MSG_CHANGESTALLPRICEREQ, OnMsgChangeStallPriceReq );
		GAMESERVER_MESSAGE_HANDLE( MSG_STALLQUERY, OnMsgStallQuery );
        
    GAMESERVER_MESSAGE_MAPPING_END
    return false;
}

void GamePlayer::OnMsgAddSellDataReq( Msg* pMsg )
{
    MsgAddSellDataReq* pReq = static_cast< MsgAddSellDataReq* >( pMsg );
    if ( pReq == NULL )
    { return; }

    if ( pReq->uchStallIndex >= StallDefine::MaxSellCount )
    {
        return SendOperateAckToClient< MsgAddSellDataAck >( MsgAddSellDataAck::ECD_ErrorStallIndex );
    }

    // �ж��Ƿ��Ѿ��г��۵���
    StallData* pStallData = m_xStall.GetStallData( pReq->uchStallIndex );
    if ( pStallData == NULL )
    {
        return SendOperateAckToClient< MsgAddSellDataAck >( MsgAddSellDataAck::ECD_ErrorStallIndex );
    }

    if ( !pStallData->IsEmpty() )
    {
        return SendOperateAckToClient< MsgAddSellDataAck >( MsgAddSellDataAck::ECD_AlreadyHaveData );
    }

    if ( !m_xStall.CheckStallDataValid( pReq->uchBagType, pReq->n64Guid ) )
    {
        return SendOperateAckToClient< MsgAddSellDataAck >( MsgAddSellDataAck::ECD_AlreadySellItem );
    }

    switch ( pReq->uchBagType )
    {
    case BT_MaterialBag:    // ���ϱ���
    case BT_NormalItemBag:  // ��ͨ����
        {
            ItemBag* pItemBag = GetItemBagByBagType( pReq->uchBagType );
            SCharItem* pCharItem = pItemBag->GetItemByIndex( pReq->uchBagIndex );

            if ( pCharItem == NULL || pCharItem->GetItemGuid() != pReq->n64Guid )
            {
                return SendOperateAckToClient< MsgAddSellDataAck >( MsgAddSellDataAck::ECD_ErrorItem );
            }

            if ( pCharItem->GetItemCount() < pReq->uchCount )
            {
                return SendOperateAckToClient< MsgAddSellDataAck >( MsgAddSellDataAck::ECD_ErrorCount );
            }

            if ( !CheckStallItemValid( pCharItem, pReq->uchStallIndex, NULL ) )
            {
                return SendOperateAckToClient< MsgAddSellDataAck >( MsgAddSellDataAck::ECD_BoundItem );
            }
        }
        break;
    case BT_MountBag:   // ���ﱳ��
        {
			return; //�Ȳ��ý��� lrt
            SMountItem* pMount = _mountManager.GetMountByIndex( pReq->uchBagIndex );
            if ( pMount == NULL || pMount->GetMountGuid() != pReq->n64Guid )
            {
                return SendOperateAckToClient< MsgAddSellDataAck >( MsgAddSellDataAck::ECD_ErrorItem );
            }

            pReq->uchCount = 1;     // ��������Ϊ1

            if ( !CheckStallMountValid( pMount, pReq->uchStallIndex, NULL ) )
            {
                return SendOperateAckToClient< MsgAddSellDataAck >( MsgAddSellDataAck::ECD_BoundItem );
            }
        }
        break;
    case BT_PetBag:
        {
            SPetItem* pPet = _petManager.GetPetByIndex( pReq->uchBagIndex );
            if ( pPet == NULL || pPet->GetPetGuid() != pReq->n64Guid )
            {
                return SendOperateAckToClient< MsgAddSellDataAck >( MsgAddSellDataAck::ECD_ErrorItem );
            }

			if(pPet->baseInfo.IsExitesEquip())
				return;

            pReq->uchCount = 1;     // ��������Ϊ1

            if ( !CheckStallPetValid( pPet, pReq->uchStallIndex, NULL ) )
            {
                return SendOperateAckToClient< MsgAddSellDataAck >( MsgAddSellDataAck::ECD_BoundItem );
            }
        }
        break;
    default:
        {
            return SendOperateAckToClient< MsgAddSellDataAck >( MsgAddSellDataAck::ECD_ErrorBagType );
        }
        break;
    }

    StallData xStallData;
    xStallData.SetStallType( StallDefine::StallSell );
    xStallData.SetBagType( pReq->uchBagType );
    xStallData.SetGuid( pReq->n64Guid );
    xStallData.SetGameMoneyPrice( pReq->nGameMoneyPrice );
    xStallData.SetRMBMoneyPrice( pReq->nRMBMoneyPrice );
    xStallData.SetCount( pReq->uchCount );

    m_xStall.AddStallData( pReq->uchStallIndex, xStallData );

    SendUpdateStallDataMessage( pReq->uchStallIndex, xStallData );
}

void GamePlayer::OnMsgAddBuyDataReq( Msg* pMsg )
{
    MsgAddBuyDataReq* pReq = static_cast< MsgAddBuyDataReq* >( pMsg );
    if ( pReq == NULL )
    { return; }

    if ( pReq->uchStallIndex < StallDefine::MaxSellCount || pReq->uchStallIndex >= StallDefine::MaxStallCount )
    {
        return SendOperateAckToClient< MsgAddBuyDataAck >( MsgAddBuyDataAck::ECD_ErrorStallIndex );
    }

    // �ж��Ƿ��е��ߵ���
    StallData* pStallData = m_xStall.GetStallData( pReq->uchStallIndex );
    if ( pStallData == NULL )
    {
        return SendOperateAckToClient< MsgAddBuyDataAck >( MsgAddBuyDataAck::ECD_ErrorStallIndex );
    }

    if ( !pStallData->IsEmpty() )
    {
        return SendOperateAckToClient< MsgAddBuyDataAck >( MsgAddBuyDataAck::ECD_AlreadyHaveData );
    }

    switch ( pReq->uchBagType )
    {
    case BT_NormalItemBag:
    case BT_MaterialBag:
    case BT_MountBag:
    case BT_PetBag:
        break;
    default:
        {
            return SendOperateAckToClient< MsgAddBuyDataAck >( MsgAddBuyDataAck::ECD_ErrorBagType );
        }
        break;
    }

    ItemDefine::SItemCommon* pItemCommon = GettheItemDetail().GetItemByID( pReq->ustItemID );
    if ( pItemCommon == NULL || !pItemCommon->bIsCanTrade ) // ���ܽ��׵���Ʒ�����չ�
    {
        return SendOperateAckToClient< MsgAddBuyDataAck >( MsgAddBuyDataAck::ECD_ErrorItem );
    }

    StallData xStallData;
    xStallData.SetStallType( StallDefine::StallBuy );
    xStallData.SetBagType( pReq->uchBagType );
    xStallData.SetItemID( pReq->ustItemID );
    xStallData.SetGameMoneyPrice( pReq->nGameMoneyPrice );
    xStallData.SetRMBMoneyPrice( pReq->nRMBMoneyPrice );
    xStallData.SetCount( pReq->uchCount );

    m_xStall.AddStallData( pReq->uchStallIndex, xStallData );

    SendUpdateStallDataMessage( pReq->uchStallIndex, xStallData );
}

void GamePlayer::OnMsgMoveStallDataReq( Msg* pMsg )
{
    MsgMoveStallDataReq* pReq = static_cast< MsgMoveStallDataReq* >( pMsg );
    if ( pReq == NULL )
    { return; }

    m_xStall.MoveStallData( pReq->uchSrcIndex, pReq->uchDestIndex );

    StallData* pStallData = m_xStall.GetStallData( pReq->uchSrcIndex );
    if ( pStallData != NULL )
    { SendUpdateStallDataMessage( pReq->uchSrcIndex, *pStallData ); }

    pStallData = m_xStall.GetStallData( pReq->uchDestIndex );
    if ( pStallData != NULL )
    { SendUpdateStallDataMessage( pReq->uchDestIndex, *pStallData ); }
}

void GamePlayer::OnMsgRemoveStallDataReq( Msg* pMsg )
{
    MsgRemoveStallDataReq* pReq = static_cast< MsgRemoveStallDataReq* >( pMsg );
    if ( pReq == NULL )
    { return; }

    StallData* pStallData = m_xStall.GetStallData( pReq->uchIndex );
    if ( pStallData == NULL )
    { return; }

    m_xStall.RemoveStallData( pStallData );

    SendUpdateStallDataMessage( pReq->uchIndex, *pStallData );
}

void GamePlayer::OnMsgStartStallReq( Msg* pMsg )
{
    MsgStartStallReq* pReq = static_cast< MsgStartStallReq* >( pMsg );
    if ( pReq == NULL )
    { return; }

    HelperFunc::CheckStringValid( pReq->szTitle, sizeof( pReq->szTitle ) );

    switch ( pReq->uchOpenType )
    {
    case MsgStartStallReq::TypeOpenWindow:
        ProcessOpenStallWindow();
        break;
    case MsgStartStallReq::TypeStartStall:
        ProcessStartStall( pReq->szTitle );
        break;
	case MsgStartStallReq::TypeStartOfflineStall:
		ProcessStartStall( pReq->szTitle, true );
		break;
    default:
        break;
    } 
}

void GamePlayer::OnMsgCloseStallReq( Msg* pMsg )
{
    CloseStall();
}

void GamePlayer::OnMsgOpenStallReq( Msg* pMsg )
{
    MsgOpenStallReq* pReq = static_cast< MsgOpenStallReq* >( pMsg );
    if ( pReq == NULL )
    { return; }

    BaseCharacter* pChar = theRunTimeData.GetCharacterByID( pReq->nPlayerID );
    if ( pChar == NULL || !pChar->IsPlayer() )
    { return; }

    GamePlayer* pPlayer = static_cast< GamePlayer* >( pChar );
    if ( pPlayer == NULL || !pPlayer->IsOpenStall() )
    { return; }

    pPlayer->ShowStallDataToPlayer( this );
}

void GamePlayer::OnMsgBuyStallReq( Msg* pMsg )
{
    MsgBuyStallReq* pReq = static_cast< MsgBuyStallReq* >( pMsg );
    if ( pReq == NULL )
    { return; }

    BaseCharacter* pChar = theRunTimeData.GetCharacterByID( pReq->nPlayerID );
    if ( pChar == NULL || !pChar->IsPlayer() )
    { 
        return SendOperateAckToClient< MsgBuyOrSellStallAck >( MsgBuyOrSellStallAck::ECD_PlayerOutLine );
    }

    GamePlayer* pPlayer = static_cast< GamePlayer* >( pChar );
    if ( pPlayer == NULL || !pPlayer->IsOpenStall() )
    { 
        return SendOperateAckToClient< MsgBuyOrSellStallAck >( MsgBuyOrSellStallAck::ECD_StallNotStart );
    }

    if ( IsWantSwitchGameWaitSaveInfoOk() || pPlayer->IsWantSwitchGameWaitSaveInfoOk() )
    {
        return SendOperateAckToClient< MsgBuyOrSellStallAck >( MsgBuyOrSellStallAck::ECD_SystemBusy );
    }

    // ����
    pPlayer->ProcessStallSell( this, pReq->uchIndex, pReq->nGameMoneyPrice, pReq->nRMBMoneyPrice, pReq->uchCount, pReq->n64Guid );
}

void GamePlayer::OnMsgSellStallReq( Msg* pMsg )
{
    MsgSellStallReq* pReq = static_cast< MsgSellStallReq* >( pMsg );
    if ( pReq == NULL )
    { return; }

    BaseCharacter* pChar = theRunTimeData.GetCharacterByID( pReq->nPlayerID );
    if ( pChar == NULL || !pChar->IsPlayer() )
    { 
        return SendOperateAckToClient< MsgBuyOrSellStallAck >( MsgBuyOrSellStallAck::ECD_PlayerOutLine );
    }

    GamePlayer* pPlayer = static_cast< GamePlayer* >( pChar );
    if ( pPlayer == NULL || !pPlayer->IsOpenStall() )
    { 
        return SendOperateAckToClient< MsgBuyOrSellStallAck >( MsgBuyOrSellStallAck::ECD_StallNotStart );
    }

    if ( IsWantSwitchGameWaitSaveInfoOk() || pPlayer->IsWantSwitchGameWaitSaveInfoOk() )
    {
        return SendOperateAckToClient< MsgBuyOrSellStallAck >( MsgBuyOrSellStallAck::ECD_SystemBusy );
    }

    // �Ʋ��������޷����г���
    if ( !ProcessSecondPasswordOperate( PasswordDefine::EProtect_Bargaining, PasswordDefine::OP_InitAction ) )
    { return;} 

    // ����
    pPlayer->ProcessStallBuy( this, pReq->uchStallIndex, pReq->nGameMoneyPrice, pReq->nRMBMoneyPrice, pReq->uchCount, pReq->uchBagType, pReq->uchBagIndex, pReq->n64Guid );
}

void GamePlayer::OnMsgChangeStallTitleReq( Msg* pMsg )
{
    MsgChangeStallTitleReq* pReq = static_cast< MsgChangeStallTitleReq* >( pMsg );
    if ( pReq == NULL )
    { return; }

    HelperFunc::CheckStringValid( pReq->szTitle, sizeof( pReq->szTitle ) );
    if ( !theChatCheck->CheckStringInLow( pReq->szTitle ) )
    { return; }

    SetStallTitle( pReq->szTitle );

    // ֪ͨ��Χ���
    MsgTellStallTitleToView xTell;
    xTell.ustPlayerID = GetID();
    HelperFunc::SafeNCpy( xTell.szTitle, pReq->szTitle, sizeof( xTell.szTitle ) );
    GettheServer().SendMsgToView( &xTell, GetID(), false );
}

void GamePlayer::OnMsgChangeStallPriceReq( Msg* pMsg )
{
    MsgChangeStallPriceReq* pReq = static_cast< MsgChangeStallPriceReq* >( pMsg );
    if ( pReq == NULL )
    { return; }

    // ��̯�в����޸ļ۸�
    if ( IsOpenStall() )
    { return; }

    // ������Ҫ����Ʒ
    StallData* pStallData = m_xStall.GetStallData( pReq->uchStallIndex );
    if ( pStallData == NULL || pStallData->IsEmpty() )
    { return; }

    // �޸ļ۸�
    pStallData->SetGameMoneyPrice( pReq->nGameMoneyPrice );
    pStallData->SetRMBMoneyPrice( pReq->nRMBMoneyPrice );

    // ֪ͨ�ͻ���
    MsgTellStallPrice xTell;
    xTell.uchStallIndex   = pReq->uchStallIndex;
    xTell.nGameMoneyPrice = pReq->nGameMoneyPrice;
    xTell.nRMBMoneyPrice  = pReq->nRMBMoneyPrice;
    SendMessageToClient( &xTell );
}

/////////////////////////////////////////////////////////////////////////////////
void GamePlayer::InitStall()
{
    m_nStallState = SS_None;
    memset( m_szStallTitle, 0, sizeof( m_szStallTitle ) );
	m_nOfflineStallEndTime = 0;
	m_nSetmealID = 0;

    m_xStall.InitStall( this );
}

unsigned int GamePlayer::GetStallModelID( bool blIsOffline )
{
    switch ( GetSex() )
    {
    case Sex_Male:
		return blIsOffline ? StallDefine::OfflineStallMaleModel : StallDefine::StallMaleModel;
        break;
    case Sex_Female:
        return blIsOffline ? StallDefine::OfflineStallFemaleModel : StallDefine::StallFemaleModel;
        break;
    default:
        break;
    }

    return StallDefine::StallMaleModel;
}

bool GamePlayer::CheckStallDataValid( unsigned char uchIndex, StallData* pData )
{
    if ( pData == NULL )
    { return false; }

    switch ( pData->GetBagType() )
    {
    case BT_NormalItemBag:
        {
            SCharItem* pCharItem = _NormalItemBag.GetItemByOnlyBigId( pData->GetGuid() );
            return CheckStallItemValid( pCharItem, uchIndex, pData );
        }
        break;
    case BT_MaterialBag:
        {
            SCharItem* pCharItem = _MaterialItemBag.GetItemByOnlyBigId( pData->GetGuid() );
            return CheckStallItemValid( pCharItem, uchIndex, pData );
        }
        break;
    case BT_MountBag:
        {
            SMountItem* pMount = _mountManager.GetMountByGuid( pData->GetGuid() );
            return CheckStallMountValid( pMount, uchIndex, pData );
        }
        break;
    case BT_PetBag:
        {
            SPetItem* pPet = _petManager.GetPetByGuid( pData->GetGuid() );
            return CheckStallPetValid( pPet, uchIndex, pData );
        }
        break;
    default:
        break;
    }

    return false;
}

void GamePlayer::ProcessOpenStallWindow()
{
    MsgTellTotalStallData xTell;
    HelperFunc::SafeNCpy( xTell.szStallTitle, GetStallTitle(), sizeof( xTell.szStallTitle ) );

    for ( int i = 0; i < StallDefine::MaxStallCount; ++i )
    {
        StallData* pStallData = m_xStall.GetStallData( i );
        if ( pStallData == NULL || pStallData->IsEmpty() )
        { continue; }

        if ( !m_xStall.CheckStallDataValid( i, pStallData ) )
        { continue; }

        xTell.AddData( i, *pStallData );
    }

    SendMessageToClient( &xTell );
}

void GamePlayer::ProcessStartStall( const char* szTitle, bool blIsOfflineStall /*= false */ )
{
	//����Ƿ�λ�ڿɰ�̯����
	GameStage* pStage = theGameWorld.GetStageById( GetMapID() );
	if ( NULL == pStage )
		return;
	GameZone* pZone = pStage->GetZone( GetCurZoneID() );
	if ( NULL == pZone || ! pZone->IsPrivateShopEnable() )
	{
		return SendOperateAckToClient< MsgStartStallAck >( MsgStartStallAck::ECD_NotInStallZone );
	}

    if ( IsDead() )
    {
        return SendOperateAckToClient< MsgStartStallAck >( MsgStartStallAck::ECD_Death ); 
    }

    // ��ģʽ�²��ܰ�̯
    if ( GetPKMode() == PKMode_Critical )
    {
        return SendOperateAckToClient< MsgStartStallAck >( MsgStartStallAck::ECD_PKModeCritical );
    }

    if ( HaveFighteFlag( eFighting ) )
    {
        return SendOperateAckToClient< MsgStartStallAck >( MsgStartStallAck::ECD_InFighting );
    }

    // �Ʋ��������޷����а�̯
    if ( !ProcessSecondPasswordOperate( PasswordDefine::EProtect_Stall, PasswordDefine::OP_InitAction ) )
    { 
        return SendOperateAckToClient< MsgStartStallAck >( MsgStartStallAck::ECD_InProtectLockTime );
    } 

    // ӵ�б���״̬���ܰ�̯
    if ( _buffManager.HaveChangeChangeMonsterIDBuff() )
    {
        return SendOperateAckToClient< MsgStartStallAck >( MsgStartStallAck::ECD_ChangeMosterBuffer );
    }

    // �����в��ܰ�̯
    if ( HaveBargaining() )   
    {
        return SendOperateAckToClient< MsgStartStallAck >( MsgStartStallAck::ECD_IsBargainingNow );
    }

    // С�ڰ�̯�ȼ�
    if ( GetLevel() < g_Cfg.m_nPrivateShopLevel )           
    {
        return SendOperateAckToClient< MsgStartStallAck >( MsgStartStallAck::ECD_LessPrivateShopLevel );
    }

    if ( GetRideId() > InvalidLogicNumber )
    {
        return SendOperateAckToClient< MsgStartStallAck >( MsgStartStallAck::ECD_OnRide );
    }
	
	/*
	 *	Author 2012-11-23 zhuxincong
	 *	DESC: �߻�Ҫ��ȡ����̯�������
	 */
    //unsigned int nTotalSellMoney = m_xStall.GetStallDataTotalSellMoney();
    //if ( !CheckCanAddMoney( nTotalSellMoney ) )  // ��֤��Ǯ�ܶ�����
    //{ 
    //    return SendOperateAckToClient< MsgStartStallAck >( MsgStartStallAck::ECD_SelfMaxMoneyLimit );
    //}

    unsigned int nTotalBuyMoney = m_xStall.GetStallDataTotalBuyMoney();
    if ( GetMoney() < nTotalBuyMoney )  // û���㹻�Ľ�Ǯ�չ�, ��̯ʧ��
    { 
        return SendOperateAckToClient< MsgStartStallAck >( MsgStartStallAck::ECD_NotEnoughMoneyBuy );
    }

    // �������ռ��ǹ��㹻
    if ( !m_xStall.CheckStallBuyBagCount( _NormalItemBag.GetNullItemCount(), _MaterialItemBag.GetNullItemCount(), _mountManager.GetMountEmptyCount(), _petManager.GetPetEmptyCount() ) )
    {
        return SendOperateAckToClient< MsgStartStallAck >( MsgStartStallAck::ECD_NotEnoughEmptyBagCount );
    }

    if ( !theChatCheck->CheckStringInLow( szTitle ) )
    {
        return SendOperateAckToClient< MsgStartStallAck >( MsgStartStallAck::ECD_ErrorStallTitle );
    }

    if ( !m_xStall.CheckStallDataValid() )
    {
        return SendOperateAckToClient< MsgStartStallAck >( MsgStartStallAck::ECD_EmptyStall );
    }

	// �������
	if ( !CheckStallDist( pStage, 3 ) )
	{
		return SendOperateAckToClient< MsgStartStallAck >( MsgStartStallAck::ECD_StallDistance );
	}

	// �ɷ�
	StallConfig::CostSetmeal* pCostSetmeal = NULL;
	bool blCanOffline = false;
	if ( blIsOfflineStall )
	{// ���߰�̯
		int nSetmealCount = GetStallConfig().GetOfflineCostSetmealCount();
		for ( int i = 0; i < nSetmealCount; ++i )
		{
			pCostSetmeal = GetStallConfig().GetOfflineCostSetmeal(i);
			if ( pCostSetmeal && IsSatisfyCost( pCostSetmeal ) && RemoveStallCost( pCostSetmeal ) )
			{
				blCanOffline = true;
				m_nSetmealID = pCostSetmeal->nID;
				break;
			}
		}
	}
	else
	{
		int nSetmealCount = GetStallConfig().GetOnlineCostSetmealCount();
		for ( int i = 0; i < nSetmealCount; ++i )
		{
			pCostSetmeal = GetStallConfig().GetOnlineCostSetmeal(i);
			if ( pCostSetmeal && IsSatisfyCost( pCostSetmeal ) && RemoveStallCost( pCostSetmeal ) )
			{
				blCanOffline = true;
				m_nSetmealID = pCostSetmeal->nID;
				break;
			}
		}
	}

	if ( !blCanOffline )
	{
		return SendOperateAckToClient< MsgStartStallAck >( MsgStartStallAck::ECD_LackOfStallFee );
	}

    SendOperateAckToClient< MsgStartStallAck >( MsgStartStallAck::ECD_Success );

    // ������Ϣ
    SetStallTitle( szTitle );
    if ( blIsOfflineStall )
    {
		SetStallOpenOffline( true );
		SetOfflineStallEndTime( HQ_TimeGetTime() + pCostSetmeal->nTime * 1000 );
    }
    else
    {
    	SetStallOpen( true );
    }

	theStallInfoQuery.AddStallInfo( GetMapID(), GetTileX(), GetTileY(), szTitle, GetCharName(), GetDBCharacterID() );

    // ֪ͨ�������
    MsgTellStartStall xTell;
    xTell.nPlayerID = GetID();
    xTell.nModelID  = GetStallModelID( false );	// ����ʱ�ٸı�ģ��
	xTell.blIsOffline = blIsOfflineStall;
    HelperFunc::SafeNCpy( xTell.szTitle, GetStallTitle(), sizeof( xTell.szTitle ) );
    GettheServer().SendMsgToView( &xTell, GetID(), false );
}

bool GamePlayer::IsSatisfyCost( StallConfig::CostSetmeal* pCostSetmeal )
{
	if ( NULL == pCostSetmeal )
	{ return false; }

	// ռ��˰
	if ( GetJiaoZiMoney() < pCostSetmeal->nStallRevenue )
	{ return false; }

	StallConfig::ItrCostList itr = pCostSetmeal->costList.begin();
	StallConfig::ItrCostList endItr = pCostSetmeal->costList.end();
	for ( ; itr != endItr; ++itr )
	{
		switch ( itr->nType )
		{
		case ItemDefine::CT_Money :
			{
				if ( GetJiaoZiMoney() < itr->nValue + pCostSetmeal->nStallRevenue )
				{ return false;	}
			}
			break;
		case ItemDefine::CT_Item :
			{
				if ( _NormalItemBag.GetItemCount(itr->nSubType) < itr->nValue )
				{ return false;	}
			}
			break;
		}
	}
	return true;
}

bool GamePlayer::RemoveStallCost( StallConfig::CostSetmeal* pCostSetmeal )
{
	if ( NULL == pCostSetmeal )
	{ return false; }

	// ռ��˰
	if (/* GetMoney() */ GetJiaoZiMoney()< pCostSetmeal->nStallRevenue )
	{ return false; }
	OperateJiaoZi( EOT_Sub, pCostSetmeal->nStallRevenue, true, __FUNCTION__, __LINE__,ePlayerMoneySourceType_StallRevenue);

	StallConfig::ItrCostList itr = pCostSetmeal->costList.begin();
	StallConfig::ItrCostList endItr = pCostSetmeal->costList.end();
	for ( ; itr != endItr; ++itr )
	{
		switch ( itr->nType )
		{
		case ItemDefine::CT_Money :
			{
				if ( GetJiaoZiMoney() < itr->nValue )
				{ return false;	}
				OperateMoney( EOT_Sub, itr->nValue, true, __FUNCTION__, __LINE__ ,ePlayerMoneySourceType_StallSetmeal);
			}
			break;
		case ItemDefine::CT_Item :
			{
				if ( _NormalItemBag.GetItemCount(itr->nSubType) < itr->nValue )
				{ return false;	}
				RemoveItem( itr->nSubType, itr->nValue );
			}
			break;
		}
	}
	return true;
}

void GamePlayer::SendUpdateStallDataMessage( unsigned char uchIndex, StallData& xData )
{
    MsgUpdateStallData xUpdate;
    xUpdate.uchIndex  = uchIndex;
    xUpdate.xData     = xData;
    SendMessageToClient( &xUpdate );
}

bool GamePlayer::CheckStallItemValid( SCharItem* pCharItem, unsigned char uchIndex, StallData* pData )
{
    // ��, ����, ���ڵĶ����ܽ���
    if ( pCharItem == NULL || pCharItem->IsBounded() || pCharItem->IsLock() || pCharItem->IsOverdue() )
    { 
        if ( pData != NULL )
        {
            pData->ClearStall();
            SendUpdateStallDataMessage( uchIndex, *pData );
        }
        return false;
    }

    if ( pData != NULL && pCharItem->GetItemCount() < pData->GetCount() )
    { 
        if ( pData != NULL )
        {
            pData->ClearStall();
            SendUpdateStallDataMessage( uchIndex, *pData );
        }
        return false;
    }


    // �ж��Ƿ��ܽ���
    ItemDefine::SItemCommon* pItemCommon = GettheItemDetail().GetItemByID( pCharItem->GetItemID() );
    if ( pItemCommon == NULL || !pItemCommon->bIsCanTrade )
    { 
        if ( pData != NULL )
        {
            pData->ClearStall();
            SendUpdateStallDataMessage( uchIndex, *pData );
        }
        return false;
    }

    return true;
}

bool GamePlayer::CheckStallMountValid( SMountItem* pMount,unsigned char uchStallIndex,  StallData* pData )
{
    // ���������ﲻ�ܰ�̯
    if ( pMount == NULL || pMount->IsLock() )
    {
        if ( pData != NULL )
        {
            pData->ClearStall();
            SendUpdateStallDataMessage( uchStallIndex, *pData );
        }
        return false;
    }

    // ��ս�����ܰ�̯����
    SMountItem* pActiveMount = _mountManager.GetActiveMount();
    if ( pActiveMount != NULL && pActiveMount->GetMountGuid() == pMount->GetMountGuid() )
    {
        if ( pData != NULL )
        {
            pData->ClearStall();
            SendUpdateStallDataMessage( uchStallIndex, *pData );
        }
        return false;
    }

    return true;
}

bool GamePlayer::CheckStallPetValid( SPetItem* pPet,unsigned char uchStallIndex,  StallData* pData )
{
    // ���������ﲻ�ܰ�̯
    if ( pPet == NULL || pPet->IsLock() )
    {
        if ( pData != NULL )
        {
            pData->ClearStall();
            SendUpdateStallDataMessage( uchStallIndex, *pData );
        }
        return false;
    }

    // ��ս�����ܰ�̯����
    SPetItem* pActivepPet = _petManager.GetActivePet();
    if ( pActivepPet != NULL && pActivepPet->GetPetGuid() == pPet->GetPetGuid() )
    {
        if ( pData != NULL )
        {
            pData->ClearStall();
            SendUpdateStallDataMessage( uchStallIndex, *pData );
        }
        return false;
    }

    return true;
}

void GamePlayer::ShowStallDataToPlayer( GamePlayer* pPlayer )
{
    if ( pPlayer == NULL )
    { return; }

    m_xStall.ShowStallDataToPlayer( pPlayer );
}

void GamePlayer::CloseStall()
{
    SetStallOpen( false );

	theStallInfoQuery.RemoveStallInfo( GetDBCharacterID() );

    // ֪ͨ�������
    MsgTellCloseStall xTell;
    xTell.nPlayerID = GetID();
    GettheServer().SendMsgToView( &xTell, GetID(), false );
}

void GamePlayer::GetSellDataToClient( StallData& xStallData, SellDataToClient& xSellDataToClient )
{
    switch( xStallData.GetBagType() )
    {
    case BT_MaterialBag:
        {
            SCharItem* pCharItem = _MaterialItemBag.GetItemByOnlyBigId( xStallData.GetGuid() );
            if ( pCharItem == NULL )
            { return; }

            if ( pCharItem->GetItemCount() < xStallData.GetCount() )
            { xStallData.SetCount( pCharItem->GetItemCount() ); }

            xSellDataToClient.SetData( pCharItem, sizeof( SCharItem ) );
        }
        break;
    case BT_NormalItemBag:
        {
            SCharItem* pCharItem = _NormalItemBag.GetItemByOnlyBigId( xStallData.GetGuid() );
            if ( pCharItem == NULL )
            { return; }

            if ( pCharItem->GetItemCount() < xStallData.GetCount() )
            { xStallData.SetCount( pCharItem->GetItemCount() ); }

            xSellDataToClient.SetData( pCharItem, sizeof( SCharItem ) );
        }
        break;
    case BT_MountBag:
        {
            SMountItem* pMount = _mountManager.GetMountByGuid( xStallData.GetGuid() );
            if ( pMount == NULL )
            { return; }

            xSellDataToClient.SetData( pMount, sizeof( SMountItem ) );
        }
    case BT_PetBag:
        {
            SPetItem* pPet = _petManager.GetPetByGuid( xStallData.GetGuid() );
            if ( pPet == NULL )
            { return; }

            xSellDataToClient.SetData( pPet, sizeof( SPetItem ) );
        }
        break;
    default:
        break;
    }
}

void GamePlayer::ProcessStallSell( GamePlayer* pPlayer, unsigned char uchStallIndex, unsigned int nGameMoneyPrice, unsigned int nRMBMoneyPrice, unsigned char uchCount, __int64 n64Guid )
{
    StallData* pStallData = m_xStall.GetStallData( uchStallIndex );
    if ( pStallData == NULL || pStallData->GetStallType() != StallDefine::StallSell )
    {
        return pPlayer->SendOperateAckToClient< MsgBuyOrSellStallAck >( MsgBuyOrSellStallAck::ECD_StallDataError );
    }

    if ( uchCount > pStallData->GetCount() || pStallData->GetGuid() != n64Guid )    // �����µ�ǰ��Ϣ
    { 
        pPlayer->SendTellStallDataCountMessage( uchStallIndex, pStallData->GetCount() );
        return pPlayer->SendOperateAckToClient< MsgBuyOrSellStallAck >( MsgBuyOrSellStallAck::ECD_StallCountError );
    }

    // �ж���Ϸ��
    if ( nGameMoneyPrice != pStallData->GetGameMoneyPrice() )
    {
        return pPlayer->SendOperateAckToClient< MsgBuyOrSellStallAck >( MsgBuyOrSellStallAck::ECD_StallPriceError );
    }

    unsigned int nCostGameMoneyMoney = uchCount * pStallData->GetGameMoneyPrice();
    if ( nCostGameMoneyMoney > pPlayer->GetMoney() )
    {
        return pPlayer->SendOperateAckToClient< MsgBuyOrSellStallAck >( MsgBuyOrSellStallAck::ECD_NotEnoughMoney );
    }

    //// �жϽ�
    //if ( nRMBMoneyPrice != pStallData->GetRMBMoneyPrice() )
    //{ return MsgBuyOrSellStallAck::ECD_StallPriceError; }

    unsigned int nCostRMBMoneyMoney = uchCount * pStallData->GetRMBMoneyPrice();
    //if ( nCostRMBMoneyMoney > pPlayer->GetJinDing() )
    //{ return MsgBuyOrSellStallAck::ECD_NotEnoughRMB; }

    std::string strItemName = "";
    switch( pStallData->GetBagType() )
    {
    case BT_MaterialBag:
    case BT_NormalItemBag:  // ������Ʒ
        if ( !ProcessStallSellItem( pPlayer, uchStallIndex, uchCount, pStallData, strItemName ) )
        { return; }
        break;
    case BT_MountBag:       // ��������
        uchCount = 1;
        if ( !ProcessStallSellMount( pPlayer, uchStallIndex, pStallData, strItemName ) )
        { return; }
        break;
    case BT_PetBag:         // ���۳���
        uchCount = 1;
        if ( !ProcessStallSellPet( pPlayer, uchStallIndex, pStallData, strItemName ) )
        { return; }
        break;
    default:
        break;
    }

    // ��ҿ�Ǯ
    pPlayer->OperateMoney( EOT_Sub, nCostGameMoneyMoney, true, __FUNCTION__, __LINE__ ,ePlayerMoneySourceType_Stall);
    // pPlayer->OperateJinDing( EOT_Sub, nCostRMBMoneyMoney );

    // ���Ҽ�Ǯ
    __int64 n64AddMoney = nCostGameMoneyMoney;           // ��unsigned int �����
    //if ( _buffManager.GetReduceTax() == 0 )     // ������˰, �۵�һЩ˰
	int nTradeRevenue = StallDefine::StallRevenue;
	StallConfig::CostSetmeal* pSetmeal = GetStallOpenOffline() ? GetStallConfig().GetOfflineCostSetmealByID( m_nSetmealID ) : GetStallConfig().GetOnlineCostSetmealByID( m_nSetmealID );
	if ( pSetmeal )
	{ nTradeRevenue = pSetmeal->nTradeRevenue; }
    nCostGameMoneyMoney = n64AddMoney * ( 100 - nTradeRevenue ) / 100 ;
    OperateMoney( EOT_Add, nCostGameMoneyMoney, true, __FUNCTION__, __LINE__,ePlayerMoneySourceType_Stall );
    // OperateJinDing( EOT_Add, nCostRMBMoneyMoney );

    // ����̯λ��Ϣ��̯��
    if ( uchCount < pStallData->GetCount() )
    { pStallData->SetCount( pStallData->GetCount() - uchCount ); }
    else
    { m_xStall.RemoveStallData( pStallData ); }
    SendUpdateStallDataMessage( uchStallIndex, *pStallData );

    // ֪ͨ���, ̯λ�����̯λ������
    pPlayer->SendTellStallDataCountMessage( uchStallIndex, pStallData->GetCount() );

    // ֪̯ͨ��ĳ���������Ķ���
    SendTellBuyOrSellStallDataMessage( pPlayer, StallDefine::StallSell, strItemName.c_str(), uchCount, nCostGameMoneyMoney, nCostRMBMoneyMoney );

    // û�ж�����, �ر�̯λ
    if ( m_xStall.GetStallDataCount() == 0 )
    { 
		CloseStall();
		//�ж��Ƿ�Ϊ���߰�̯ �ǵĻ� �ж�����Ƿ��뿪�ͻ��� �ǵĻ� ���������
		if(m_nOfflineTime !=0 && m_nOfflineTime == GetOfflineStallEndTime())
		{
			SetOffline();
            SetOfflineType( ET_ExitGame );
		}
	}
}

bool GamePlayer::ProcessStallSellItem( GamePlayer* pPlayer, unsigned char uchStallIndex, unsigned char uchCount, StallData* pStallData, std::string& strItemName )
{
    // ��ñ����е���Ʒ
    ItemBag* pItemBag = GetItemBagByBagType( pStallData->GetBagType() );
    uint8 uchBagIndex = pItemBag->GetItemIndexByGuid( pStallData->GetGuid() );
    SCharItem* pCharItem = pItemBag->GetItemByIndex( uchBagIndex );
    if( pCharItem == NULL || pCharItem->GetItemGuid() != pStallData->GetGuid() || pCharItem->IsOverdue() || pCharItem->IsBounded() || pCharItem->IsLock() )
    { 
        m_xStall.RemoveStallData( pStallData );
        SendUpdateStallDataMessage( uchStallIndex, *pStallData );
        pPlayer->SendOperateAckToClient< MsgBuyOrSellStallAck >( MsgBuyOrSellStallAck::ECD_StallItemError );
        return false;
    }

    if ( pCharItem->GetItemCount() < uchCount )
    {
        pPlayer->SendOperateAckToClient< MsgBuyOrSellStallAck >( MsgBuyOrSellStallAck::ECD_StallCountError );
        return false;
    }

    SCharItem xCharItem = *pCharItem;

    // �򷽼���Ʒ
    if ( uchCount < xCharItem.GetItemCount() )
    {
        switch( pStallData->GetBagType() )
        {
        case BT_MaterialBag:
            xCharItem.SetItemGuid( _MaterialItemBag.GetNewItemID() );
            break;
        default:
            xCharItem.SetItemGuid( _NormalItemBag.GetNewItemID() );
            break;
        }
    }

    unsigned short ustCount = uchCount;
    xCharItem.SetItemCount( ustCount );
    if ( pPlayer->AddItemToBag( xCharItem, ustCount, EIGS_Stall ) != ierr_Success )
    {
        pPlayer->SendOperateAckToClient< MsgBuyOrSellStallAck >( MsgBuyOrSellStallAck::ECD_ItemPackFull );
        return false;
    }

	
	//LYH��־��� (���ҿ���Ʒ)
	SCharItem * _item =  GetBagItemByGuid(pStallData->GetGuid());
	if (_item)
	{
		ItemDefine::SItemCommon* _pitem = GettheItemDetail().GetItemByID(_item->GetItemID());
		if(_pitem)
		theLogEventService.LogItemConsume(GetAccountID(),GetDBCharacterID(),_item->GetItemID(),uchCount,_item->GetItemGuid(),
		0,eItemLogInfo_ItemConsume_Bargain,
		                                  GetCharName(),_pitem->GetItemName());
          ItemDefine::SItemCommon* pItemCommon = GettheItemDetail().GetItemByID( xCharItem.GetItemID() );
		  if ( pItemCommon != NULL )
		  { 
			  strItemName = pItemCommon->GetItemName();	  
		  }else
		  {
              strItemName = "";
		  }
		  
		//LYH��־��� ����̯��
		if(!theLogEventService.LogItemTrade(pPlayer->GetAccountID(),pPlayer->GetDBCharacterID(),GetAccountID(),GetDBCharacterID(),_item->GetItemID(),uchCount,_item->GetItemGuid(),
			uchCount * pStallData->GetGameMoneyPrice(),eItemTrade_PrivateShop,pPlayer->GetCharName(),GetCharName(),strItemName.c_str()))
		{
			// ��¼LOG
			
			if ( pItemCommon != NULL )
			{ 
				strItemName = pItemCommon->GetItemName();

				char szID[ 50 ] = { 0 };
				Log( theXmlString.GetString( eLog_info_2slk_92 ), pPlayer->GetCharName(), pPlayer->GetDBCharacterID(), strItemName.c_str(), ::BigInt2String( pStallData->GetGuid(), szID ), uchCount );
				pPlayer->Log( theXmlString.GetString( eLog_info_2slk_93 ), GetCharName(), GetDBCharacterID(), strItemName.c_str(), ::BigInt2String( pStallData->GetGuid(), szID ), uchCount );
			}
		}


	}

	// ���ҿ���Ʒ
	RemoveItem( pStallData->GetBagType(), uchBagIndex, uchCount, pStallData->GetGuid() );

 

	

    return true;
}

bool GamePlayer::ProcessStallSellMount( GamePlayer* pPlayer, unsigned char uchStallIndex, StallData* pStallData, std::string& strMountName )
{
    SMountItem* pMount = GetMountByGuid( pStallData->GetGuid() );
    if ( pMount == NULL || !CheckStallMountValid( pMount, uchStallIndex, pStallData ) )
    {
        pPlayer->SendOperateAckToClient< MsgBuyOrSellStallAck >( MsgBuyOrSellStallAck::ECD_StallItemError );
        return false;
    }

    // �򷽼�����
    if ( pPlayer->AddMount( *pMount ) != ER_Success )
    {
        pPlayer->SendOperateAckToClient< MsgBuyOrSellStallAck >( MsgBuyOrSellStallAck::ECD_MountPackFull );
        return false;
    }

    strMountName = pMount->GetMountName();

    // ̯��ɾ������
    RemoveMountByGuid( pStallData->GetGuid() );

    // ��¼LOG

	if(!theLogEventService.LogItemTrade(pPlayer->GetAccountID(),pPlayer->GetDBCharacterID(),GetAccountID(),GetDBCharacterID(),
		pStallData->GetItemID(),1,pStallData->GetGuid(),pStallData->GetGameMoneyPrice(),eItemTrade_PrivateShop,
		pPlayer->GetCharName(),GetCharName(),strMountName.c_str()))
	{
    char szID[ 50 ] = { 0 };
    Log( theXmlString.GetString( eLog_info_2slk_92 ), pPlayer->GetCharName(), pPlayer->GetDBCharacterID(), strMountName.c_str(), ::BigInt2String( pStallData->GetGuid(), szID ), 1 );
    pPlayer->Log( theXmlString.GetString( eLog_info_2slk_93 ), GetCharName(), GetDBCharacterID(), strMountName.c_str(), ::BigInt2String( pStallData->GetGuid(), szID ), 1 );
	}

    return true;
}

bool GamePlayer::ProcessStallSellPet( GamePlayer* pPlayer, unsigned char uchStallIndex, StallData* pStallData, std::string& strPetName )
{
    SPetItem* pPet = _petManager.GetPetByGuid( pStallData->GetGuid() );
    if ( pPet == NULL || !CheckStallPetValid( pPet, uchStallIndex, pStallData ) )
    {
        pPlayer->SendOperateAckToClient< MsgBuyOrSellStallAck >( MsgBuyOrSellStallAck::ECD_StallItemError );
        return false;
    }

    // �򷽼ӳ���
    if ( pPlayer->AddPet( *pPet ) != ER_Success )
    {
        pPlayer->SendOperateAckToClient< MsgBuyOrSellStallAck >( MsgBuyOrSellStallAck::ECD_MountPackFull );
        return false;
    }

    strPetName = pPet->GetPetName();

    // ̯��ɾ������
    int nIndex = _petManager.GetPetIndexByGuid( pPet->GetPetGuid() );
    RemovePetByIndex( nIndex, EDS_Stall );


	//LYH��־���
	if(!theLogEventService.LogItemTrade(pPlayer->GetAccountID(),pPlayer->GetDBCharacterID(),GetAccountID(),GetDBCharacterID(),
		pStallData->GetItemID(),1,pStallData->GetGuid(),pStallData->GetGameMoneyPrice(),eItemTrade_PrivateShop,
		pPlayer->GetCharName(),GetCharName(),strPetName.c_str()))
	{
    // ��¼LOG
    char szID[ 50 ] = { 0 };
    Log( theXmlString.GetString( eLog_info_2slk_92 ), pPlayer->GetCharName(), pPlayer->GetDBCharacterID(), strPetName.c_str(), ::BigInt2String( pStallData->GetGuid(), szID ), 1 );
    pPlayer->Log( theXmlString.GetString( eLog_info_2slk_93 ), GetCharName(), GetDBCharacterID(), strPetName.c_str(), ::BigInt2String( pStallData->GetGuid(), szID ), 1 );
	}
    return true;
}

void GamePlayer::ProcessStallBuy( GamePlayer* pPlayer, unsigned char uchStallIndex, unsigned int nGameMoneyPrice, unsigned int nRMBMoneyPrice, unsigned char uchCount, 
                                          unsigned char uchBagType, unsigned char uchBagIndex, __int64 n64Guid )
{
    StallData* pStallData = m_xStall.GetStallData( uchStallIndex );
    if ( pStallData == NULL || pStallData->GetStallType() != StallDefine::StallBuy )
    {
        return pPlayer->SendOperateAckToClient< MsgBuyOrSellStallAck >( MsgBuyOrSellStallAck::ECD_StallDataError );
    }

    if ( uchCount > pStallData->GetCount() )    // ���¸���
    { 
        pPlayer->SendTellStallDataCountMessage( uchStallIndex, pStallData->GetCount() );
        return pPlayer->SendOperateAckToClient< MsgBuyOrSellStallAck >( MsgBuyOrSellStallAck::ECD_StallCountError );
    }

    // �ж���Ϸ��
    if ( nGameMoneyPrice != pStallData->GetGameMoneyPrice() )
    {
        return pPlayer->SendOperateAckToClient< MsgBuyOrSellStallAck >( MsgBuyOrSellStallAck::ECD_StallPriceError );
    }

    unsigned int nCostGameMoneyMoney = uchCount * pStallData->GetGameMoneyPrice();
    if ( GetMoney() < nCostGameMoneyMoney )
    {
        return pPlayer->SendOperateAckToClient< MsgBuyOrSellStallAck >( MsgBuyOrSellStallAck::ECD_StallerNotMoney );
    }

    //// �жϽ�
    //if ( nRMBMoneyPrice != pStallData->GetRMBMoneyPrice() )
    //{ return MsgBuyOrSellStallAck::ECD_StallPriceError; }

    unsigned int nCostRMBMoneyMoney = uchCount * pStallData->GetRMBMoneyPrice();
    //if ( GetJinDing() < nCostRMBMoneyMoney )
    //{ return MsgBuyOrSellStallAck::ECD_StallerNotRMB; }

    std::string strItemName = "";
    switch ( uchBagType )
    {
    case BT_MaterialBag:
    case BT_NormalItemBag:  // ������Ʒ
        if ( !ProcessStallBuyItem( pPlayer, pStallData, uchCount, uchBagType, uchBagIndex, n64Guid, strItemName ) )
        { return; }
        break;
    case BT_MountBag:   // ��������
        uchCount = 1;
        if ( !ProcessStallBuyMount( pPlayer, pStallData, uchBagIndex, n64Guid, strItemName ) )
        { return; }
        break;
    case BT_PetBag:
        uchCount = 1;
        if ( !ProcessStallBuyPet( pPlayer, pStallData, uchBagIndex, n64Guid, strItemName ) )
        { return; }
        break;
    default:
        break;
    }

    // ̯����Ǯ
    OperateMoney( EOT_Sub, nCostGameMoneyMoney, true, __FUNCTION__, __LINE__ ,ePlayerMoneySourceType_Stall);
    // OperateJinDing( EOT_Sub, nCostRMBMoneyMoney );

    // ���Ҽ�Ǯ
    __int64 n64AddMoney = nCostGameMoneyMoney;           // ��unsigned int �����
    //if ( _buffManager.GetReduceTax() == 0 )     // ������˰, �۵�һЩ˰
	int nTradeRevenue = StallDefine::StallRevenue;
	StallConfig::CostSetmeal* pSetmeal = GetStallOpenOffline() ? GetStallConfig().GetOfflineCostSetmealByID( m_nSetmealID ) : GetStallConfig().GetOnlineCostSetmealByID( m_nSetmealID );
	if ( pSetmeal )
	{ nTradeRevenue = pSetmeal->nTradeRevenue; }
    nCostGameMoneyMoney = n64AddMoney * ( 100 - /*StallDefine::StallRevenue*/nTradeRevenue ) / 100 ;
    pPlayer->OperateMoney( EOT_Add, nCostGameMoneyMoney, true, __FUNCTION__, __LINE__,ePlayerMoneySourceType_Stall );
    // pPlayer->OperateJinDing( EOT_Add, nCostRMBMoneyMoney );

    // ����̯λ��Ϣ��̯��
    if ( pStallData->GetCount() > uchCount )
    { pStallData->SetCount( pStallData->GetCount() - uchCount ); }
    else
    { m_xStall.RemoveStallData( pStallData ); }
    SendUpdateStallDataMessage( uchStallIndex, *pStallData );

    // ֪ͨ���, ̯λ�����̯λ������
    pPlayer->SendTellStallDataCountMessage( uchStallIndex, pStallData->GetCount() );

    // ֪̯ͨ��ĳ��ҳ����˶�������
    SendTellBuyOrSellStallDataMessage( pPlayer, StallDefine::StallBuy, strItemName.c_str(), uchCount, /*nCostGameMoneyMoney*/n64AddMoney, nCostRMBMoneyMoney );

    // û�ж�����, ����û���㹻�İ����ռ��չ���Ʒ �ر�̯λ
    if ( m_xStall.GetStallDataCount() == 0 || !m_xStall.CheckStallBuyBagCount( _NormalItemBag.GetNullItemCount(), _MaterialItemBag.GetNullItemCount(), 
        _mountManager.GetMountEmptyCount() , _petManager.GetPetEmptyCount() ) )
    { CloseStall(); }   
}

bool GamePlayer::ProcessStallBuyItem( GamePlayer* pPlayer, StallData* pStallData, unsigned char uchCount, 
                                              unsigned char uchBagType, unsigned char uchBagIndex, __int64 n64Guid, std::string& strItemName )
{
    ItemBag* pItemBag = pPlayer->GetItemBagByBagType( uchBagType );
    SCharItem* pCharItem = pItemBag->GetItemByIndex( uchBagIndex );
    if ( pCharItem == NULL || pCharItem->GetItemGuid() != n64Guid || pCharItem->GetItemCount() < uchCount || pCharItem->GetItemID() != pStallData->GetItemID() )
    {
        pPlayer->SendOperateAckToClient< MsgBuyOrSellStallAck >( MsgBuyOrSellStallAck::ECD_SellErrorItem );
        return false;
    }

    if ( pCharItem->IsOverdue() || pCharItem->IsBounded() || pCharItem->IsLock() )
    {
        pPlayer->SendOperateAckToClient< MsgBuyOrSellStallAck >( MsgBuyOrSellStallAck::ECD_SellItemBound );
        return false;
    }

    SCharItem xCharItem = *pCharItem;

    // ̯������Ʒ
    if ( uchCount < pCharItem->GetItemCount() )
    {
        switch( uchBagType )
        {
        case BT_MaterialBag:
            xCharItem.SetItemGuid( _MaterialItemBag.GetNewItemID() );
            break;
        default:
            xCharItem.SetItemGuid( _NormalItemBag.GetNewItemID() );
            break;
        }
    }

    unsigned short ustCount = uchCount;
    xCharItem.SetItemCount( ustCount );
    if ( AddItemToBag( xCharItem, ustCount, EIGS_Stall ) != ierr_Success )
    {
        pPlayer->SendOperateAckToClient< MsgBuyOrSellStallAck >( MsgBuyOrSellStallAck::ECD_StallerPackFull );
        return false;
    }

    // ������ҿ���Ʒ
    pPlayer->RemoveItem( uchBagType, uchBagIndex, uchCount, n64Guid );

	SCharItem * _item = pPlayer->GetBagItemByGuid(n64Guid);
	if (_item)
	{
		ItemDefine::SItemCommon* _pitem = GettheItemDetail().GetItemByID(_item->GetItemID());
		if(_pitem)
	   theLogEventService.LogItemConsume(pPlayer->GetAccountID(),pPlayer->GetDBCharacterID(),_item->GetItemID(),uchCount,_item->GetItemGuid(),
	   0,eItemLogInfo_ItemConsume_Bargain,
	                                     pPlayer->GetCharName(),_pitem->GetItemName());
	}


    // ��¼LOG
    ItemDefine::SItemCommon* pItemCommon = GettheItemDetail().GetItemByID( xCharItem.GetItemID() );
    if ( pItemCommon != NULL )
    { 
        strItemName = pItemCommon->GetItemName();

        char szID[ 50 ] = { 0 };
        pPlayer->Log( theXmlString.GetString( eLog_info_2slk_93 ), GetCharName(), GetDBCharacterID(), strItemName.c_str(), ::BigInt2String( n64Guid, szID ), uchCount );
        Log( theXmlString.GetString( eLog_info_2slk_92 ), pPlayer->GetCharName(), pPlayer->GetDBCharacterID(), strItemName.c_str(), ::BigInt2String( xCharItem.GetItemGuid(), szID ), uchCount );
    }

    return true;
}

bool GamePlayer::ProcessStallBuyMount( GamePlayer* pPlayer, StallData* pStallData, unsigned char uchBagIndex, __int64 n64Guid, std::string& strMountName )
{
    SMountItem* pMount = pPlayer->GetMountByIndex( uchBagIndex );
    if ( pMount == NULL || pMount->GetMountGuid() != n64Guid || pMount->GetMountID() != pStallData->GetItemID() )
    {
        pPlayer->SendOperateAckToClient< MsgBuyOrSellStallAck >( MsgBuyOrSellStallAck::ECD_SellErrorItem );
        return false;
    }

    SMountItem* pActiveMount = pPlayer->GetActiveMount();
    if ( pActiveMount != NULL && pMount->GetMountGuid() == pActiveMount->GetMountGuid() )
    {
        pPlayer->SendOperateAckToClient< MsgBuyOrSellStallAck >( MsgBuyOrSellStallAck::ECD_SellMountActive );
        return false;
    }

    if ( pMount->IsLock() )
    {
        pPlayer->SendOperateAckToClient< MsgBuyOrSellStallAck >( MsgBuyOrSellStallAck::ECD_SellItemBound );
        return false;
    }

    // ̯���ȼ�����
    if ( AddMount( *pMount ) != ER_Success )
    {
        pPlayer->SendOperateAckToClient< MsgBuyOrSellStallAck >( MsgBuyOrSellStallAck::ECD_StallerMountFull );
        return false;
    }

    strMountName = pMount->GetMountName();

    // ̯��ɾ����
    pPlayer->RemoveMountByIndex( uchBagIndex );

    // ��¼LOG
    char szID[ 50 ] = { 0 };
    Log( theXmlString.GetString( eLog_info_2slk_92 ), pPlayer->GetCharName(), pPlayer->GetDBCharacterID(), strMountName.c_str(), ::BigInt2String( n64Guid, szID ), 1 );
    pPlayer->Log( theXmlString.GetString( eLog_info_2slk_93 ), GetCharName(), GetDBCharacterID(), strMountName.c_str(), ::BigInt2String( n64Guid, szID ), 1 );

    return true;
}

bool GamePlayer::ProcessStallBuyPet( GamePlayer* pPlayer, StallData* pStallData, unsigned char uchBagIndex, __int64 n64Guid, std::string& strPetName )
{
    SPetItem* pPet = pPlayer->_petManager.GetPetByIndex( uchBagIndex );
    if ( pPet == NULL || pPet->GetPetGuid() != n64Guid || pPet->GetPetID() != pStallData->GetItemID() )
    {
        pPlayer->SendOperateAckToClient< MsgBuyOrSellStallAck >( MsgBuyOrSellStallAck::ECD_SellErrorItem );
        return false;
    }

    SPetItem* pActivePet = pPlayer->_petManager.GetActivePet();
    if ( pActivePet != NULL && pPet->GetPetGuid() == pActivePet->GetPetGuid() )
    {
        pPlayer->SendOperateAckToClient< MsgBuyOrSellStallAck >( MsgBuyOrSellStallAck::ECD_SellPetActive );
        return false;
    }

    if ( pPet->IsLock() )
    {
        pPlayer->SendOperateAckToClient< MsgBuyOrSellStallAck >( MsgBuyOrSellStallAck::ECD_SellItemBound );
        return false;
    }

    // ̯���ȼ�����
    if ( AddPet( *pPet ) != ER_Success )
    {
        pPlayer->SendOperateAckToClient< MsgBuyOrSellStallAck >( MsgBuyOrSellStallAck::ECD_StallerPetFull );
        return false;
    }

    strPetName = pPet->GetPetName();

    // ̯��ɾ����
    pPlayer->RemovePetByIndex( uchBagIndex, EDS_Stall );

    // ��¼LOG
    char szID[ 50 ] = { 0 };
    Log( theXmlString.GetString( eLog_info_2slk_92 ), pPlayer->GetCharName(), pPlayer->GetDBCharacterID(), strPetName.c_str(), ::BigInt2String( n64Guid, szID ), 1 );
    pPlayer->Log( theXmlString.GetString( eLog_info_2slk_93 ), GetCharName(), GetDBCharacterID(), strPetName.c_str(), ::BigInt2String( n64Guid, szID ), 1 );

    return true;
}

void GamePlayer::SendTellBuyOrSellStallDataMessage( GamePlayer* pPlayer, unsigned char uchStallType, const char* szItemName, unsigned char uchCount, unsigned int nGameMoney, unsigned int nRMBMoney )
{
    MsgTellBuyOrSellStallData xTell;
    xTell.uchStallType = uchStallType;
    xTell.uchCount     = uchCount;
    xTell.nGameMoney   = nGameMoney;
    xTell.nRmbMoney    = nRMBMoney;
    HelperFunc::SafeNCpy( xTell.szPlayer, pPlayer->GetCharName(), sizeof( xTell.szPlayer ) );
    HelperFunc::SafeNCpy( xTell.szItemName, szItemName, sizeof( xTell.szItemName ) );
    SendMessageToClient( &xTell );
}

void GamePlayer::SendTellStallDataCountMessage( unsigned char uchStallIndex, unsigned char uchCount )
{
    MsgTellStallDataCount xTell;
    xTell.uchIndex = uchStallIndex;
    xTell.uchCount = uchCount;
    SendMessageToClient( &xTell );
}

void GamePlayer::ShowStallInfo( GamePlayer *pTarget )
{
    MsgTellStartStall xTell;
    xTell.nPlayerID = GetID();
    xTell.nModelID  = GetStallModelID( GetStallOpenOffline() );
    HelperFunc::SafeNCpy( xTell.szTitle, GetStallTitle(), sizeof( xTell.szTitle ) );
    pTarget->SendMessageToClient( &xTell );
}

void GamePlayer::OnMsgStallQuery( Msg* pMsg )
{
	MsgStallQuery* pReq = static_cast< MsgStallQuery * >(pMsg);
	
    std::vector<StallDefine::SStallInfo> vecList;
    theStallInfoQuery.GetStallInfoList( GetMapID(), pReq->nSearchField, pReq->szKeyWord, vecList );

    MsgAckStallQuery xAck;
    StallDefine::SStallInfo xStall;
    for ( std::vector<StallDefine::SStallInfo>::iterator iter = vecList.begin(); iter != vecList.end(); ++iter )
    {
        xStall.dwMapID = iter->dwMapID;
        xStall.nX      = iter->nX;
        xStall.nY      = iter->nY;
        memcpy_s( xStall.szStallTitle, sizeof(xStall.szStallTitle), iter->szStallTitle, sizeof(xStall.szStallTitle) );
        memcpy_s( xStall.szCharacterName, sizeof(xStall.szCharacterName), iter->szCharacterName, sizeof(xStall.szCharacterName) );

        if ( !xAck.AddData(xStall) )
        {
            GettheServer().SendMsgToSingle( &xAck, this );
            xAck.Clear();
            xAck.AddData(xStall);
        }
    }
    xAck.SetTheLast();
    GettheServer().SendMsgToSingle( &xAck, this );
}

void GamePlayer::SetStallOpen( bool bValue )
{
	if ( bValue )
	{ m_nStallState = SS_Normal; }
	else
	{ m_nStallState = SS_None; }
}

void GamePlayer::SetStallOpenOffline( bool bValue )
{
	if ( bValue )
	{ m_nStallState = SS_Offline; }
	else
	{ m_nStallState = SS_None; }
}

bool GamePlayer::CheckStallDist( GameStage* pStage, float fDistance )
{
	if ( NULL == pStage )
	{ return false; }

	std::vector<int32> vecCharID;
	pStage->GetAllCharInCircle( fDistance, GetPos(), vecCharID, 1);

	std::vector<int32>::iterator itr = vecCharID.begin();
	std::vector<int32>::iterator endItr = vecCharID.end();
	for ( ; itr != endItr; ++itr )
	{
		GamePlayer* pPlayer = static_cast< GamePlayer* >( theRunTimeData.GetCharacterByID( *itr ) );
		if ( pPlayer && pPlayer->IsPlayer() )
		{
			if ( pPlayer->IsOpenStall() )
			{ return false;	}
		}
	}

	return true;
}
