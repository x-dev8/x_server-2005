#include "GamePlayer.h"
#include "BargainingMessage.h"
#include "ShareData.h"
#include "XmlStringLanguage.h"
#include "DuelHandler.h"
#include "LogEventService.h"
bool GamePlayer::ProcessBargainingMsg( Msg* pMsg )
{
    DWORD dwType = pMsg->GetType();

    GAMESERVER_MESSAGE_MAPPING_BEGIN
        GAMESERVER_MESSAGE_HANDLE( MSG_BARGAININGREQ, OnMsgBargainingReq );
        GAMESERVER_MESSAGE_HANDLE( MSG_BARGAININGREQUESTACK, OnMsgBargainingRequestAck );
        GAMESERVER_MESSAGE_HANDLE( MSG_BARGAININGDATAREQ, OnMsgBargainingDataReq );
        GAMESERVER_MESSAGE_HANDLE( MSG_BARGAININGLOCKREQ, OnMsgBargainingLockReq );
        GAMESERVER_MESSAGE_HANDLE( MSG_BARGAININGFIXREQ, OnMsgBargainingFixReq );
        GAMESERVER_MESSAGE_HANDLE( MSG_BARGAININGCANCELREQ, OnMsgBargainingCancelReq );
        GAMESERVER_MESSAGE_HANDLE( MSG_REMOVEBARGAININGDATAREQ, OnMsgRemoveBargainingDataReq );
    GAMESERVER_MESSAGE_MAPPING_END
    return false;
}

// 请求交易
void GamePlayer::OnMsgBargainingReq( Msg* pMsg )
{
    MsgBargainingReq* pReq = static_cast< MsgBargainingReq* >( pMsg );
    if ( pReq == NULL ) 
    { return; }

    if ( !ProcessSecondPasswordOperate( PasswordDefine::EProtect_Bargaining, PasswordDefine::OP_InitAction ) )
    { return;}  // 财产保护下无法进行交易

    BaseCharacter* pTargetChar = theRunTimeData.GetCharacterByID( pReq->ustPlayerID );
    if ( pTargetChar == NULL || !pTargetChar->IsPlayer() )
    {
        SendBargainingAckMessage( BargainingDefine::FailedNotInArea );
        return;
    }   
    GamePlayer* pPlayer = static_cast< GamePlayer* >( pTargetChar );

    if ( theBargainingManager.GetBargainingInvite( pPlayer->GetDBCharacterID() ) != BargainingDefine::NoneID )
    {
        SendBargainingAckMessage( BargainingDefine::FailedTargetBargaining );
        return;
    }

    unsigned char uchResult = CheckCanBargaining( pPlayer );
    SendBargainingAckMessage( uchResult );

    // 不能交易, 直接返回
    if ( uchResult != BargainingDefine::FailedSuccess )
    { return; }

    // 发送申请给对方
    MsgBargainingRequestReq xReq;
    xReq.ustPlayerID = GetID();
    pPlayer->SendMessageToClient( &xReq );

    // 加入交易申请记录
    theBargainingManager.AddBargainingInvite( GetDBCharacterID(), pPlayer->GetDBCharacterID() );
}

void GamePlayer::OnMsgBargainingRequestAck( Msg* pMsg )
{
    MsgBargainingRequestAck* pAck = static_cast< MsgBargainingRequestAck* >( pMsg );
    if ( pAck == NULL )
    { return; }

    // 先清除掉交易申请信息
    unsigned int nPlayerID = theBargainingManager.GetBargainingInvite( GetDBCharacterID() );
    theBargainingManager.RemoveBargainingInvite( GetDBCharacterID() );

    GamePlayer* pPlayer = theRunTimeData.GetGamePlayerByDBID( nPlayerID );
    if ( pPlayer == NULL )
    {
        SendBargainingAckMessage( BargainingDefine::FailedNotInArea );
        return;
    }   

    // 不同意交易
    if ( !pAck->bBargainintAgree )
    {
        pPlayer->SendBargainingAckMessage( BargainingDefine::FailedRefuse );
        return;
    }

    if ( !ProcessSecondPasswordOperate( PasswordDefine::EProtect_Bargaining, PasswordDefine::OP_InitAction ) )
    { return;}  // 财产保护下无法进行交易

    // 判断是否能交易
    unsigned char uchResult = CheckCanBargaining( pPlayer );
    if ( uchResult != BargainingDefine::FailedSuccess )
    {
        SendBargainingAckMessage( uchResult );
        return;
    }

    // 添加一个交易房间
    BargainingInfo* pBargainingInfo = theBargainingManager.CreateBargaining();
    if ( pBargainingInfo == NULL )
    { return; }

    // 设置交易房间ID
    pPlayer->SetBargainingID( pBargainingInfo->GetID() );
    SetBargainingID( pBargainingInfo->GetID() );

    // 申请的玩家
    PlayerBargaining& xBarginingA = pBargainingInfo->GetPlayerBargainingA();
    xBarginingA.SetID( pPlayer->GetDBCharacterID() );
    xBarginingA.SetStatus( BargainingDefine::StatusStart );

    // 同意的玩家
    PlayerBargaining& xBarginingB = pBargainingInfo->GetPlayerBargainingB();
    xBarginingB.SetID( GetDBCharacterID() );
    xBarginingB.SetStatus( BargainingDefine::StatusStart );


    pPlayer->Log(theXmlString.GetString(eServerLog_JiaoYiBegin),GetCharName(), GetDBCharacterID());
	Log(theXmlString.GetString(eServerLog_JiaoYiBegin), pPlayer->GetCharName(), pPlayer->GetDBCharacterID());

	//pPlayer->Log("交易-与玩家[name:%s, dbid:%u] 开始交易", GetCharName(), GetDBCharacterID());
	//Log("交易-与玩家[name:%s, dbid:%u] 开始交易", pPlayer->GetCharName(), pPlayer->GetDBCharacterID());

	
	// 开启定时器
    pBargainingInfo->StartTimer( HQ_TimeGetTime(), BargainingDefine::BargainingTime );

    // 发送消息给双方
    SendBargainingStartMessage( pPlayer->GetID() );
    pPlayer->SendBargainingStartMessage( GetID() );
}

void GamePlayer::OnMsgBargainingDataReq( Msg* pMsg )
{
    MsgBargainingDataReq* pReq = static_cast< MsgBargainingDataReq* >( pMsg );
    if ( pReq == NULL )
    { return; }

    // 查找自己 和对方的交易信息
    GamePlayer* pTarget = NULL;
    PlayerBargaining* pTargetPlayerBargaining = NULL;
    PlayerBargaining* pPlayerBargaining = GetPlayerBargaining( pTarget, pTargetPlayerBargaining );  
    if ( pPlayerBargaining == NULL || pTarget == NULL || pTargetPlayerBargaining == NULL )
    { return; }

    if ( pPlayerBargaining->GetStatus() != BargainingDefine::StatusStart )
    { return; } // 锁定以后不能放入物品
    //////////////////////////////////////////////////////////////////////////////////////////////
    // 判断交易过来的物品
    switch ( pReq->uchBargainintType )
    {
    case BargainingDefine::BargainingMoney:     // 请求交易金钱
        ProcessBargainingMoneyReq( pReq->nBargainingValue, pPlayerBargaining, pTarget );
        break;
    case BargainingDefine::BargainingRMB:       // 请求交易金锭
        // ProcessBargainingRMBReq( pReq->nBargainingValue, pPlayerBargaining, pTarget );
        break;
    case BargainingDefine::BargainingItem:      // 请求交易物品
        ProcessBargainingItemReq( pReq->uchBargainingIndex, pReq->uchBagType, pReq->uchIndex, pReq->n64Guid, pPlayerBargaining, pTarget );
        break;
    case BargainingDefine::BargainingMount:     // 请求交易坐骑
		{
			return; //先不让交易 lrt
			ProcessBargainingMountReq( pReq->uchBargainingIndex, pReq->uchBagType, pReq->uchIndex, pReq->n64Guid, pPlayerBargaining, pTarget );
		}
        break;
    case BargainingDefine::BargainingPet:
		ProcessBargainingPetReq( pReq->uchBargainingIndex, pReq->uchBagType, pReq->uchIndex, pReq->n64Guid, pPlayerBargaining, pTarget );
        break;
    default:
        return;
    }
}

void GamePlayer::OnMsgBargainingLockReq( Msg* pMsg )
{
    MsgBargainingLockReq* pReq = static_cast< MsgBargainingLockReq* >( pMsg );
    if ( pReq == NULL )
    { return; }

    // 查找自己 和对方的交易信息
    GamePlayer* pTarget = NULL;
    PlayerBargaining* pTargetPlayerBargaining = NULL;
    PlayerBargaining* pPlayerBargaining = GetPlayerBargaining( pTarget, pTargetPlayerBargaining );  
    if ( pPlayerBargaining == NULL || pTarget == NULL || pTargetPlayerBargaining == NULL )
    { return; }

    /////////////////////////////////////////////////////////////////////////////////////////////////////
    if ( pPlayerBargaining->GetStatus() != BargainingDefine::StatusStart )
    { return; }

    pPlayerBargaining->SetStatus( BargainingDefine::StatusLock );

    // 发送消息通知客户端
    SendBargainingStatusMessage( GetID(), pPlayerBargaining->GetStatus() );
    pTarget->SendBargainingStatusMessage( GetID(), pPlayerBargaining->GetStatus() );
}

void GamePlayer::OnMsgBargainingCancelReq( Msg* pMsg )
{
    MsgBargainingCancelReq* pReq = static_cast< MsgBargainingCancelReq* >( pMsg );
    if ( pReq == NULL )
    { return; }

    theBargainingManager.RemoveBargaining( GetBargainingID(), BargainingDefine::FinishCancel );
}

void GamePlayer::OnMsgRemoveBargainingDataReq( Msg* pMsg )
{
    MsgRemoveBargainingDataReq* pReq = static_cast< MsgRemoveBargainingDataReq* >( pMsg );
    if ( pReq == NULL )
    { return; }

    // 查找自己 和对方的交易信息
    GamePlayer* pTarget = NULL;
    PlayerBargaining* pTargetPlayerBargaining = NULL;
    PlayerBargaining* pPlayerBargaining = GetPlayerBargaining( pTarget, pTargetPlayerBargaining );  
    if ( pPlayerBargaining == NULL || pTarget == NULL || pTargetPlayerBargaining == NULL )
    { return; }

    if ( pPlayerBargaining->GetStatus() != BargainingDefine::StatusStart )
    { return; } // 锁定以后不能取消交易物品
    //////////////////////////////////////////////////////////////////////////////////////////
    pPlayerBargaining->ClearBargainingData( pReq->uchBargainingIndex );

    // 发送消息给客户端
    SendRemoveBargainingDataMessage( GetID(), pReq->uchBargainingIndex );
    pTarget->SendRemoveBargainingDataMessage( GetID(), pReq->uchBargainingIndex );
}

void GamePlayer::OnMsgBargainingFixReq( Msg* pMsg )
{
    MsgBargainingFixReq* pReq = static_cast< MsgBargainingFixReq* >( pMsg );
    if ( pReq == NULL )
    { return; }

    // 查找自己 和对方的交易信息
    GamePlayer* pTarget = NULL;
    PlayerBargaining* pTargetPlayerBargaining = NULL;
    PlayerBargaining* pPlayerBargaining = GetPlayerBargaining( pTarget, pTargetPlayerBargaining );  
    if ( pPlayerBargaining == NULL || pTarget == NULL || pTargetPlayerBargaining == NULL )
    { return; }

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////
    if ( pTargetPlayerBargaining->GetStatus() == BargainingDefine::StatusStart )
    { return; } // 对方还没有锁定状态, 强制不让确定交易

    if ( pPlayerBargaining->GetStatus() == BargainingDefine::StatusFix )
    { return; } // 自己已经是锁定状态

    pPlayerBargaining->SetStatus( BargainingDefine::StatusFix );

    // 发送消息通知客户端
    SendBargainingStatusMessage( GetID(), pPlayerBargaining->GetStatus() );
    pTarget->SendBargainingStatusMessage( GetID(), pPlayerBargaining->GetStatus() );

    // 双方都确定了
    if ( pTargetPlayerBargaining->GetStatus() == BargainingDefine::StatusFix )
    {
        ProcessBargainingChangeData( pPlayerBargaining, pTarget, pTargetPlayerBargaining );
    }
}

PlayerBargaining* GamePlayer::GetPlayerBargaining( GamePlayer*& pTargetPlayer, PlayerBargaining*& pTargetPlayerBargaining )
{
    pTargetPlayer = NULL;
    pTargetPlayerBargaining = NULL;
    // 查找自己的交易信息
    BargainingInfo* pBargaining = theBargainingManager.GetBargaining( GetBargainingID() );
    if ( pBargaining == NULL )
    { return NULL; }

    PlayerBargaining* pPlayerBargaining = pBargaining->GetPlayerBargaining( GetDBCharacterID() );
    if ( pPlayerBargaining == NULL )
    { return NULL; }

    // 判断交易对方
    pTargetPlayerBargaining = pBargaining->GetTargetPlayerBargaining( GetDBCharacterID() );
    if ( pTargetPlayerBargaining == NULL )
    { return NULL; }

    pTargetPlayer = theRunTimeData.GetGamePlayerByDBID( pTargetPlayerBargaining->GetID() );
    if ( pTargetPlayer == NULL )
    { return NULL; }

    return pPlayerBargaining;
}

unsigned char GamePlayer::CheckCanBargaining( GamePlayer* pTarget )
{
    if ( pTarget == NULL || !pTarget->IsInMapArea( GetMapID(), GetFloatX(), GetFloatY(), 16.f ) )
    { return BargainingDefine::FailedNotInArea; }

    if ( HaveBargaining() )
    { return BargainingDefine::FailedBargaining; }

    if ( IsOpenStall() )
    { return BargainingDefine::FailedStall; }

    if ( pTarget->HaveBargaining() )
    { return BargainingDefine::FailedTargetBargaining; }

    if ( pTarget->IsOpenStall() )
    { return BargainingDefine::FailedTargetStall; }

    if ( theDuelHandler()->IsInDuel( GetID() ) || HaveFighteFlag( eFighting ) )
    { return BargainingDefine::FailedFighting; }

    if ( theDuelHandler()->IsInDuel( pTarget->GetID() ) ||  pTarget->HaveFighteFlag( eFighting ) )
    { return BargainingDefine::FailedTargetFighting; }

    return BargainingDefine::FailedSuccess;
}

void GamePlayer::ProcessBargainingMoneyReq( unsigned int nGameMoney, PlayerBargaining* pPlayerBargaining, GamePlayer* pTarget )
{
    if ( pPlayerBargaining == NULL || pTarget == NULL )
    { return; }

    if ( GetMoney() < nGameMoney )
    {
        SendBargainingDataErrorMessage( GetID(), BargainingDefine::LessMoney );
        return;
    }

    if ( GetLevel() < BargainingDefine::BargainingMoneyLevel )
    {
        SendBargainingDataErrorMessage( GetID(), BargainingDefine::MoneyLevelLimit );
        return;
    }

    if ( pTarget->GetLevel() < BargainingDefine::BargainingMoneyLevel )
    {
        SendBargainingDataErrorMessage( pTarget->GetID(), BargainingDefine::MoneyLevelLimit );
        return;
    }

    if (nGameMoney > 0 && !pTarget->CheckCanAddMoney( nGameMoney ) )
    {
        SendBargainingDataErrorMessage( pTarget->GetID(), BargainingDefine::MaxMoney );
        return;
    }

    // 加入到交易列表中
    pPlayerBargaining->SetGameMoney( nGameMoney );
	

Log(theXmlString.GetString(eServerLog_JiaoYiByMoney),pTarget->GetCharName(), pTarget->GetDBCharacterID(),nGameMoney );

	
		
	//Log("交易-与玩家[name:%s, dbid:%u] 交易。 交易金钱。交易额: %d", pTarget->GetCharName(), pTarget->GetDBCharacterID(),
	//	nGameMoney );
    // 通知自己
    SendBargainingDataAckMessage( BargainingDefine::BargainingMoney, nGameMoney, 0, 0, 0, 0 );

    // 通知对方
    pTarget->SendShowBargainingDataMessage( BargainingDefine::BargainingMoney, nGameMoney, 0, NULL, 0 );
}

void GamePlayer::ProcessBargainingRMBReq( unsigned int nRMBMoney, PlayerBargaining* pPlayerBargaining, GamePlayer* pTarget )
{
    if ( pPlayerBargaining == NULL || pTarget == NULL )
    { return; }

    if ( GetJinDing() < nRMBMoney )
    {
        SendBargainingDataErrorMessage( GetID(), BargainingDefine::LessRMB );
        return;
    }

    // 加入到交易列表中
    pPlayerBargaining->SetRMBMoney( nRMBMoney );
	Log(theXmlString.GetString(eServerLog_JiaoYiByJingDing), pTarget->GetCharName(), pTarget->GetDBCharacterID(),nRMBMoney);
			
	//Log("交易-与玩家[name:%s, dbid:%u] 交易。 交易金锭。交易额: %d", pTarget->GetCharName(), pTarget->GetDBCharacterID(),
	//	nRMBMoney );
    // 通知自己
    SendBargainingDataAckMessage( BargainingDefine::BargainingRMB, nRMBMoney, 0, 0, 0, 0 );

    // 通知对方
    pTarget->SendShowBargainingDataMessage( BargainingDefine::BargainingRMB, nRMBMoney, 0, NULL, 0 );
}

void GamePlayer::ProcessBargainingItemReq( unsigned char uchBargainingIndex, unsigned char uchBagType, unsigned char uchBagIndex, __int64 n64Guid, PlayerBargaining* pPlayerBargaining, GamePlayer* pTarget )
{
    if ( pPlayerBargaining == NULL || pTarget == NULL )
    { return; }

    ItemBag* pItemBag = GetItemBagByBagType( uchBagType );
    SCharItem* pCharItem = pItemBag->GetItemByIndex( uchBagIndex );
    if ( pCharItem == NULL || pCharItem->GetItemGuid() != n64Guid )
    {
        SendBargainingDataErrorMessage( GetID(), BargainingDefine::DataError );
        return;
    }

    ItemDefine::SItemCommon* pItemCommon = GettheItemDetail().GetItemByID( pCharItem->GetItemID() );
    if ( pItemCommon == NULL || !pItemCommon->bIsCanTrade )
    { 
        SendBargainingDataErrorMessage( GetID(), BargainingDefine::CanNotTrade );
        return;
    }

    // 锁定 或者 绑定的不能交易
    if ( pCharItem->IsLock() || pCharItem->IsBounded() )
    {
        SendBargainingDataErrorMessage( GetID(), BargainingDefine::DataLocked );
        return;
    }

    // 过期的物品不能交易
    if ( pCharItem->IsOverdue() )
    {
        SendBargainingDataErrorMessage( GetID(), BargainingDefine::DataOverdue );
        return;
    }

    // 检查交易栏道具
    if ( !CheckPlayerBargainingData( pPlayerBargaining, uchBargainingIndex, uchBagType, n64Guid ) )
    { return; }

    // 加入交易列表
    BargainingData xBargainingData;
    xBargainingData.SetItemBag( uchBagType );
    xBargainingData.SetItemIndex( uchBagIndex );
    xBargainingData.SetItemCount( pCharItem->GetItemCount() );
    xBargainingData.SetItemGuid( pCharItem->GetItemGuid() );
    xBargainingData.SetItemValue1( pCharItem->itembaseinfo.value1 );
    xBargainingData.SetItemValue2( pCharItem->itembaseinfo.value2 );
    pPlayerBargaining->AddBargainingData( uchBargainingIndex, xBargainingData );


	  Log(theXmlString.GetString(eServerLog_JiaoYiByItem), pTarget->GetCharName(), pTarget->GetDBCharacterID(),uchBargainingIndex, uchBagType, uchBagIndex, n64Guid);

	//Log("交易-与玩家[name:%s, dbid:%u] 交易。 交易道具。失去物品: %s, 物品id: %d, 堆叠数: %d,  物品guid: %s ", pTarget->GetCharName(), pTarget->GetDBCharacterID(),
	//	uchBargainingIndex, uchBagType, uchBagIndex, n64Guid );


    // 发送给自己
    SendBargainingDataAckMessage( BargainingDefine::BargainingItem, 0, uchBargainingIndex, uchBagType, uchBagIndex, n64Guid );

    // 发送给对方
    pTarget->SendShowBargainingDataMessage( BargainingDefine::BargainingItem, 0, uchBargainingIndex, pCharItem, sizeof( SCharItem ) );
}

void GamePlayer::ProcessBargainingMountReq( unsigned char uchBargainingIndex, unsigned char uchBagType, unsigned char uchBagIndex, __int64 n64Guid, PlayerBargaining* pPlayerBargaining, GamePlayer* pTarget )
{
    if ( pPlayerBargaining == NULL || pTarget == NULL )
    { return; }

    SMountItem* pMount = _mountManager.GetMountByIndex( uchBagIndex );
    if ( pMount == NULL || pMount->GetMountGuid() != n64Guid )
    {
        SendBargainingDataErrorMessage( GetID(), BargainingDefine::DataError );
        return;
    }

    if ( pMount->IsLock() )
    {
        SendBargainingDataErrorMessage( GetID(), BargainingDefine::DataLocked );
        return;
    }

    if ( uchBagIndex == GetActiveMountIndex() )
    {
        SendBargainingDataErrorMessage( GetID(), BargainingDefine::MountActive );
        return;
    }

    if ( pMount->baseInfo.level - pTarget->GetLevel() > BargainingDefine::BargainingMountLevel )
    {
        SendBargainingDataErrorMessage( pTarget->GetID(), BargainingDefine::MountLevelLimit );
        return;
    }

    // 检查交易栏道具
    if ( !CheckPlayerBargainingData( pPlayerBargaining, uchBargainingIndex, uchBagType, n64Guid ) )
    { return; }

    // 加入交易列表
    BargainingData xBargainingData;
    xBargainingData.SetItemBag( uchBagType );
    xBargainingData.SetItemIndex( uchBagIndex );
    xBargainingData.SetItemCount( 1 );
    xBargainingData.SetItemGuid( pMount->GetMountGuid() );
    pPlayerBargaining->AddBargainingData( uchBargainingIndex, xBargainingData );

	
        Log(theXmlString.GetString(eServerLog_JiaoYiByMount),pTarget->GetCharName(), pTarget->GetDBCharacterID(),pMount->GetMountName());
	
	
		
	//Log("交易-与玩家[name:%s, dbid:%u] 交易。 交易坐骑。 %s", pTarget->GetCharName(), pTarget->GetDBCharacterID(),
	//	pMount->GetMountName());

    // 发送给自己
    SendBargainingDataAckMessage( BargainingDefine::BargainingMount, 0, uchBargainingIndex, uchBagType, uchBagIndex, n64Guid );

    // 发送给对方
    pTarget->SendShowBargainingDataMessage( BargainingDefine::BargainingMount, 0, uchBargainingIndex, pMount, sizeof( SMountItem ) );
}

void GamePlayer::ProcessBargainingPetReq( unsigned char uchBargainingIndex, unsigned char uchBagType, unsigned char uchBagIndex, __int64 n64Guid, PlayerBargaining* pPlayerBargaining, GamePlayer* pTarget )
{
	if ( pPlayerBargaining == NULL || pTarget == NULL )
	{ return; }

	SPetItem* pPet = _petManager.GetPetByIndex( uchBagIndex );
	if ( pPet == NULL || pPet->GetPetGuid() != n64Guid )
	{
		SendBargainingDataErrorMessage( GetID(), BargainingDefine::DataError );
		return;
	}

	if ( pPet->IsLock() )
	{
		SendBargainingDataErrorMessage( GetID(), BargainingDefine::DataLocked );
		return;
	}

	if ( uchBagIndex == _petManager.GetActivePetIndex() )
	{
		SendBargainingDataErrorMessage( GetID(), BargainingDefine::PetActive );
		return;
	}

	if(pPet->baseInfo.IsExitesEquip())
		return;
	// 检查交易栏道具
	if ( !CheckPlayerBargainingData( pPlayerBargaining, uchBargainingIndex, uchBagType, n64Guid ) )
	{ return; }

	// 加入交易列表
	BargainingData xBargainingData;
	xBargainingData.SetItemBag( uchBagType );
	xBargainingData.SetItemIndex( uchBagIndex );
	xBargainingData.SetItemCount( 1 );
	xBargainingData.SetItemGuid( pPet->GetPetGuid() );
	pPlayerBargaining->AddBargainingData( uchBargainingIndex, xBargainingData );


   
		Log(theXmlString.GetString(eServerLog_JiaoYiByPet),pTarget->GetCharName(), pTarget->GetDBCharacterID(),
			uchBargainingIndex, uchBagType, uchBagIndex, n64Guid);


	//Log("交易-与玩家[name:%s, dbid:%u] 交易。 交易宠物。失去物品: %s, 物品id: %d, 堆叠数: %d,  物品guid: %s ", pTarget->GetCharName(), pTarget->GetDBCharacterID(),
	//	uchBargainingIndex, uchBagType, uchBagIndex, n64Guid);

	// 发送给自己
	SendBargainingDataAckMessage( BargainingDefine::BargainingPet, 0, uchBargainingIndex, uchBagType, uchBagIndex, n64Guid );

	// 发送给对方
	pTarget->SendShowBargainingDataMessage( BargainingDefine::BargainingPet, 0, uchBargainingIndex, pPet, sizeof( SPetItem ) );
}

void GamePlayer::ProcessBargainingChangeData( PlayerBargaining* pPlayerBargaining, GamePlayer* pTarget, PlayerBargaining* pTargetPlayerBargaining )
{
    if ( pPlayerBargaining == NULL || pTarget == NULL || pTargetPlayerBargaining == NULL )
    { return; }

    if ( IsWantSwitchGameWaitSaveInfoOk() || pTarget->IsWantSwitchGameWaitSaveInfoOk() )
    { return; } // 有一方等待数据入库回应时, 不让交易

    // 不能交易, 让他们回到初始状态
    if ( !CheckCanBargainingChangeData( pPlayerBargaining, pTarget, pTargetPlayerBargaining ) || 
        !pTarget->CheckCanBargainingChangeData( pTargetPlayerBargaining, this, pPlayerBargaining ) )
    {
        pPlayerBargaining->SetStatus( BargainingDefine::StatusStart );
        SendBargainingStatusMessage( GetID(), pPlayerBargaining->GetStatus() );
        pTarget->SendBargainingStatusMessage( GetID(), pPlayerBargaining->GetStatus() );

        pTargetPlayerBargaining->SetStatus( BargainingDefine::StatusStart );
        SendBargainingStatusMessage( pTarget->GetID(), pTargetPlayerBargaining->GetStatus() );
        pTarget->SendBargainingStatusMessage( pTarget->GetID(), pTargetPlayerBargaining->GetStatus() );

        return;
    }

    // 交换物品
    ProcessBargainingChangeData( pTarget, pTargetPlayerBargaining );
    pTarget->ProcessBargainingChangeData( this, pPlayerBargaining );
	
	Log(theXmlString.GetString(eServerLog_JiaoYiEnd),pTarget->GetCharName(), pTarget->GetDBCharacterID());
	//Log("交易-与玩家[name:%s, dbid:%u] 结束交易", pTarget->GetCharName(), pTarget->GetDBCharacterID());
    // 交易成功, 删除管理
    theBargainingManager.RemoveBargaining( GetBargainingID(), BargainingDefine::FinishSuccess );
}

bool GamePlayer::CheckCanBargainingChangeData( PlayerBargaining* pPlayerBargaining, GamePlayer* pTarget, PlayerBargaining* pTargetPlayerBargaining )
{
    if ( pPlayerBargaining == NULL || pTarget == NULL || pTargetPlayerBargaining == NULL )
    { return false; }

    if ( GetMoney() < pPlayerBargaining->GetGameMoney() )
    {
        SendBargainingDataErrorMessage( GetID(), BargainingDefine::LessMoney );
        pTarget->SendBargainingDataErrorMessage( GetID(), BargainingDefine::LessMoney );
        return false;
    }

    if ( GetJinDing() < pPlayerBargaining->GetRMBMoney() )
    {
        SendBargainingDataErrorMessage( GetID(), BargainingDefine::LessMoney );
        pTarget->SendBargainingDataErrorMessage( GetID(), BargainingDefine::LessMoney );
        return false;
    }

    if (pTargetPlayerBargaining->GetGameMoney() > 0 && !CheckCanAddMoney( pTargetPlayerBargaining->GetGameMoney() ) )
    {
        SendBargainingDataErrorMessage( GetID(), BargainingDefine::MaxMoney );
        pTarget->SendBargainingDataErrorMessage( GetID(), BargainingDefine::MaxMoney );
        return false;
    }

    // 判断物品数量
    int nNormalCount   = 0;     // 普通物品数量
    int nMaterialCount = 0;     // 材料物品数量
    int nMountCount    = 0;     // 坐骑数量
    int nPetCount      = 0;     // 宠物数量

    // 再次校验交易物品, 判断交易的物品有效性和数量
    for ( int i = 0; i < BargainingDefine::MaxItemCount; ++i )
    {
        const BargainingData* pData = pPlayerBargaining->GetBargainingData( i );
        if ( pData == NULL || pData->GetItemGuid() == 0 )
        { continue; }

        switch ( pData->GetItemBag() )
        {
        case BT_MaterialBag:
        case BT_NormalItemBag:
            {
                if ( pData->GetItemBag() == BT_MaterialBag )
                { ++nMaterialCount; }
                else
                { ++nNormalCount; }

                ItemBag* pItemBag = GetItemBagByBagType( pData->GetItemBag() );
                SCharItem* pCharItem = pItemBag->GetItemByIndex( pData->GetItemIndex() );
                if ( pCharItem == NULL || pCharItem->GetItemGuid() != pData->GetItemGuid() || pCharItem->GetItemCount() != pData->GetItemCount() ||
                    pCharItem->IsLock() || pCharItem->IsBounded() || pCharItem->itembaseinfo.value1 != pData->GetItemValue1() || pCharItem->itembaseinfo.value2 != pData->GetItemValue2() )
                {
                    SendBargainingDataErrorMessage( GetID(), BargainingDefine::DataChange );
                    pTarget->SendBargainingDataErrorMessage( GetID(), BargainingDefine::DataChange );
                    return false;
                }
            }
            break;
        case BT_MountBag:
            {
                ++nMountCount;

                SMountItem* pMount = _mountManager.GetMountByIndex( pData->GetItemIndex() );
                if ( pMount == NULL || pMount->GetMountGuid() != pData->GetItemGuid() || pMount->IsLock() || pData->GetItemIndex() == GetActiveMountIndex() )
                {
                    SendBargainingDataErrorMessage( GetID(), BargainingDefine::DataChange );
                    pTarget->SendBargainingDataErrorMessage( GetID(), BargainingDefine::DataChange );
                    return false;
                }
            }
            break;
        case BT_PetBag:
            {
                ++nPetCount;

                SPetItem* pPet = _petManager.GetPetByIndex( pData->GetItemIndex() );
                if ( pPet == NULL || pPet->GetPetGuid() != pData->GetItemGuid() || pPet->IsLock() || pData->GetItemIndex() == _petManager.GetActivePetIndex() )
                {
                    SendBargainingDataErrorMessage( GetID(), BargainingDefine::DataChange );
                    pTarget->SendBargainingDataErrorMessage( GetID(), BargainingDefine::DataChange );
                    return false;
                }
            }
            break;
        default:
            break;
        }
    }

    // 普通背包
    if ( nNormalCount > pTarget->GetNullItemCount( BT_NormalItemBag ) )
    {
        SendBargainingDataErrorMessage( pTarget->GetID(), BargainingDefine::NormalFull );
        pTarget->SendBargainingDataErrorMessage( pTarget->GetID(), BargainingDefine::NormalFull );
        return false;
    }

    // 材料背包
    if ( nMaterialCount > pTarget->GetNullItemCount( BT_MaterialBag ) )
    {
        SendBargainingDataErrorMessage( pTarget->GetID(), BargainingDefine::MaterialFull );
        pTarget->SendBargainingDataErrorMessage( pTarget->GetID(), BargainingDefine::MaterialFull );
        return false;
    }

    // 坐骑背包
    if ( nMountCount > pTarget->GetNullItemCount( BT_MountBag ) )
    {
        SendBargainingDataErrorMessage( pTarget->GetID(), BargainingDefine::MountFull );
        pTarget->SendBargainingDataErrorMessage( pTarget->GetID(), BargainingDefine::MountFull );
        return false;
    }

    // 宠物背包
    if ( nPetCount > pTarget->GetNullItemCount( BT_PetBag ) )
    {
        SendBargainingDataErrorMessage( pTarget->GetID(), BargainingDefine::PetFull );
        pTarget->SendBargainingDataErrorMessage( pTarget->GetID(), BargainingDefine::PetFull );
        return false;
    }

    return true;
}

bool GamePlayer::CheckPlayerBargainingData( PlayerBargaining* pPlayerBargaining, unsigned char uchBargainingIndex, unsigned char uchBagType, __int64 n64Guid )
{
    // 交易位置错误
    const BargainingData* pBargainingData = pPlayerBargaining->GetBargainingData( uchBargainingIndex );
    if ( pBargainingData == NULL )
    {
        SendBargainingDataErrorMessage( GetID(), BargainingDefine::IndexError );
        return false;
    }

    // 该位置上已经有物品了
    if ( pBargainingData->GetItemGuid() != 0 && pBargainingData->GetItemGuid() != n64Guid )
    {
        SendBargainingDataErrorMessage( GetID(), BargainingDefine::IndexAlready );
        return false;
    }

    // 判断该道具没有在交易栏中
    if ( !pPlayerBargaining->CheckBargainingData( uchBargainingIndex, uchBagType, n64Guid ) )
    {
        SendBargainingDataErrorMessage( GetID(), BargainingDefine::DataAlready );
        return false;
    }

    return true;
}

void GamePlayer::ProcessBargainingChangeData( GamePlayer* pTarget, PlayerBargaining* pTargetPlayerBargaining )
{
     // 进入到此函数, 不能有return, 一定要把所有逻辑都执行完成.

	
    Log( theXmlString.GetString( eLog_info_2slk_9 ), GetCharName(), pTarget->GetCharName() );

    // 游戏币
	//LYH日志添加 交易（金钱） 正确的
	if(pTargetPlayerBargaining->GetGameMoney() > 0)
		theLogEventService.LogItemTrade(GetAccountID(),GetDBCharacterID(),pTarget->GetAccountID(),pTarget->GetDBCharacterID(),0,0,0,pTargetPlayerBargaining->GetGameMoney(),eItemTrade_Bargain,
		                                GetCharName(),pTarget->GetCharName(),"Money");

    OperateMoney( EOT_Add, pTargetPlayerBargaining->GetGameMoney(), true, __FUNCTION__, __LINE__ ,ePlayerMoneySourceType_Bargain);
    pTarget->OperateMoney( EOT_Sub, pTargetPlayerBargaining->GetGameMoney(), true, __FUNCTION__, __LINE__,ePlayerMoneySourceType_Bargain );

    // 金锭
    OperateJinDing( EOT_Add, pTargetPlayerBargaining->GetRMBMoney(), __FUNCTION__, __LINE__ ,ePlayerMoneySourceType_Bargain);
    pTarget->OperateJinDing( EOT_Sub, pTargetPlayerBargaining->GetRMBMoney(), __FUNCTION__, __LINE__,ePlayerMoneySourceType_Bargain );

    // 先加物品
    for ( int i = 0; i < BargainingDefine::MaxItemCount; ++i )
    {
        const BargainingData* pData = pTargetPlayerBargaining->GetBargainingData( i );
        if ( pData == NULL || pData->GetItemGuid() == 0 )
        { continue; }

        switch ( pData->GetItemBag() )
        {
        case BT_MaterialBag:
        case BT_NormalItemBag:
            {
                ItemBag* pItemBag = pTarget->GetItemBagByBagType( pData->GetItemBag() );
                SCharItem* pCharItem = pItemBag->GetItemByIndex( pData->GetItemIndex() );
                if ( pCharItem == NULL )
                { continue; }

                // 添加道具
                unsigned short ustCount = pCharItem->GetItemCount();
                AddItemToBag( *pCharItem, ustCount, EIGS_Bargaining );
				//LYH日志添加 交易物品 正确的

				 ItemDefine::SItemCommon* pItemCommon = GettheItemDetail().GetItemByID( pCharItem->GetItemID() );

				 if ( pItemCommon != NULL )
				 {
				
					 theLogEventService.LogItemTrade(GetAccountID(),GetDBCharacterID(),pTarget->GetAccountID(),pTarget->GetDBCharacterID(),
												pCharItem->GetItemID(),ustCount,pCharItem->GetItemGuid(),0,eItemTrade_Bargain,
												GetCharName(),pTarget->GetCharName(),pItemCommon->GetItemName());   
               
                    char szID[ 60 ] = { 0 };
                    pTarget->Log( theXmlString.GetString( eLog_info_2slk_11 ), pItemCommon->GetItemName(), BigInt2String( pCharItem->GetItemGuid(), szID ), pCharItem->GetItemCount() );
               

				//LYH日志添加
				theLogEventService.LogItemConsume(pTarget->GetAccountID(),pTarget->GetDBCharacterID(),pCharItem->GetItemID(),
												pCharItem->GetItemCount(),pCharItem->GetItemGuid(),
												0,eItemLogInfo_ItemConsume_Bargain,
												pTarget->GetCharName(),pItemCommon->GetItemName());
                 }
                // 删除道具
				 bool result = false;
                result = pTarget->RemoveItem( pData->GetItemBag(), pData->GetItemIndex(), pCharItem->GetItemCount(), pCharItem->GetItemGuid() );
				if (!result)
				{
					LOG_MESSAGE(LOGICSYSTEMOBJECT, LOG_PRIORITY_ERROR,"%d-%d 交易时删除物品失败,可能出现装备复制.",pTarget->GetDBCharacterID(), pCharItem->GetItemID());
				}
				
            }
            break;
        case BT_MountBag:
            {
                // 这里只能用guid来操作, 因为坐骑删除掉一个, 坐骑索引已经改变了
                SMountItem* pMount = pTarget->GetMountByGuid( pData->GetItemGuid() );
                if ( pMount == NULL )
                { continue; }

                // 添加坐骑
                AddMount( *pMount );

                char szID[ 60 ] = { 0 };
                Log( theXmlString.GetString( eLog_info_2slk_14 ), pMount->GetMountName(), BigInt2String( pMount->GetMountGuid(), szID ), 1 );
                pTarget->Log( theXmlString.GetString( eLog_info_2slk_11 ), pMount->GetMountName(), BigInt2String( pMount->GetMountGuid(), szID ), 1 );

                // 删除坐骑
                pTarget->RemoveMountByGuid( pData->GetItemGuid() );

				//LYH日志添加 交易物品 正确的
				theLogEventService.LogItemTrade(GetAccountID(),GetDBCharacterID(),pTarget->GetAccountID(),pTarget->GetDBCharacterID(),pMount->GetMountID(),
												1,pMount->GetMountGuid(),0,eItemTrade_Bargain,GetCharName(),pTarget->GetCharName(),pMount->GetMountName());

            }
            break;
        case BT_PetBag:
            {
                // 这里只能用guid来操作, 因为宠物删除掉一个, 宠物索引已经改变了
                SPetItem* pPet = pTarget->_petManager.GetPetByGuid( pData->GetItemGuid() );
                if ( pPet == NULL )
                { continue; }

                // 添加宠物
                AddPet( *pPet );

                char szID[ 60 ] = { 0 };
                Log( theXmlString.GetString( eLog_info_2slk_14 ), pPet->GetPetName(), BigInt2String( pPet->GetPetGuid(), szID ), 1 );
                pTarget->Log( theXmlString.GetString( eLog_info_2slk_11 ), pPet->GetPetName(), BigInt2String( pPet->GetPetGuid(), szID ), 1 );

                // 删除宠物
                pTarget->RemovePetByGuid( pData->GetItemGuid(), EDS_Stall );

				//LYH日志添加 交易物品 正确的
				theLogEventService.LogItemTrade(GetAccountID(),GetDBCharacterID(),pTarget->GetAccountID(),pTarget->GetDBCharacterID(),pPet->GetPetID(),
												1,pPet->GetPetGuid(),0,eItemTrade_Bargain,GetCharName(),pTarget->GetCharName(),pPet->GetPetName());
            }
            break;
        default:
            break;
        }
    }

    Log( theXmlString.GetString( eLog_info_2slk_17 ), GetCharName(), pTarget->GetCharName() );
}

void GamePlayer::SendBargainingAckMessage( unsigned char uchResult )
{
    MsgBargainingAck xAck;
    xAck.uchResult = uchResult;
    SendMessageToClient( &xAck );
}

void GamePlayer::SendBargainingStartMessage( GameObjectId ustPlayerID )
{
    MsgBargainingStart xStart;
    xStart.ustPlayerID = ustPlayerID;
    SendMessageToClient( &xStart );
}

void GamePlayer::SendBargainingFinishMessage( unsigned char uchFinishType )
{
    SetBargainingID( BargainingDefine::NoneID );

    MsgBargainingFinish xFinish;
    xFinish.uchFinishType = uchFinishType;
    SendMessageToClient( &xFinish );
}

void GamePlayer::SendBargainingDataErrorMessage( GameObjectId ustPlayerID, unsigned char uchResult )
{
    MsgBargainingDataError xAck;
    xAck.ustPlayerID = ustPlayerID;
    xAck.uchResult   = uchResult;
    SendMessageToClient( &xAck );
}

void GamePlayer::SendBargainingDataAckMessage( unsigned char uchBargainingType, unsigned int nBargainingValue, unsigned char uchBargainingIndex, unsigned char uchBagType, unsigned char uchBagIndex, __int64 n64Guid )
{
    MsgBargainingDataAck xAck;
    xAck.uchBargainintType  = uchBargainingType;
    xAck.nBargainingValue   = nBargainingValue;
    xAck.uchBargainingIndex = uchBargainingIndex;
    xAck.uchBagType         = uchBagType;
    xAck.uchIndex           = uchBagIndex;
    xAck.n64Guid            = n64Guid;
    SendMessageToClient( &xAck );
}

void GamePlayer::SendShowBargainingDataMessage( unsigned char uchBargainingType, unsigned int nBargainingValue, unsigned char uchBargainingIndex, void* pData, int nSize )
{
    MsgShowBargainingData xShow;
    xShow.uchBargainintType  = uchBargainingType;
    xShow.nBargainingValue   = nBargainingValue;
    xShow.uchBargainingIndex = uchBargainingIndex;
    xShow.AddBargainingData( pData, nSize );
    SendMessageToClient( &xShow );
}

void GamePlayer::SendBargainingStatusMessage( GameObjectId ustPlayerID, unsigned char uchStatus )
{
    MsgBargainingStatus xStatus;
    xStatus.ustPlayerID = ustPlayerID;
    xStatus.uchStatus   = uchStatus;
    SendMessageToClient( &xStatus );
}

void GamePlayer::SendRemoveBargainingDataMessage( GameObjectId ustPlayerID, unsigned char uchBargainingIndex )
{
    MsgRemoveBargainingDataAck xRemove;
    xRemove.ustPlayerID        = ustPlayerID;
    xRemove.uchBargainingIndex = uchBargainingIndex;
    SendMessageToClient( &xRemove );
}
