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

// ������
void GamePlayer::OnMsgBargainingReq( Msg* pMsg )
{
    MsgBargainingReq* pReq = static_cast< MsgBargainingReq* >( pMsg );
    if ( pReq == NULL ) 
    { return; }

    if ( !ProcessSecondPasswordOperate( PasswordDefine::EProtect_Bargaining, PasswordDefine::OP_InitAction ) )
    { return;}  // �Ʋ��������޷����н���

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

    // ���ܽ���, ֱ�ӷ���
    if ( uchResult != BargainingDefine::FailedSuccess )
    { return; }

    // ����������Է�
    MsgBargainingRequestReq xReq;
    xReq.ustPlayerID = GetID();
    pPlayer->SendMessageToClient( &xReq );

    // ���뽻�������¼
    theBargainingManager.AddBargainingInvite( GetDBCharacterID(), pPlayer->GetDBCharacterID() );
}

void GamePlayer::OnMsgBargainingRequestAck( Msg* pMsg )
{
    MsgBargainingRequestAck* pAck = static_cast< MsgBargainingRequestAck* >( pMsg );
    if ( pAck == NULL )
    { return; }

    // �����������������Ϣ
    unsigned int nPlayerID = theBargainingManager.GetBargainingInvite( GetDBCharacterID() );
    theBargainingManager.RemoveBargainingInvite( GetDBCharacterID() );

    GamePlayer* pPlayer = theRunTimeData.GetGamePlayerByDBID( nPlayerID );
    if ( pPlayer == NULL )
    {
        SendBargainingAckMessage( BargainingDefine::FailedNotInArea );
        return;
    }   

    // ��ͬ�⽻��
    if ( !pAck->bBargainintAgree )
    {
        pPlayer->SendBargainingAckMessage( BargainingDefine::FailedRefuse );
        return;
    }

    if ( !ProcessSecondPasswordOperate( PasswordDefine::EProtect_Bargaining, PasswordDefine::OP_InitAction ) )
    { return;}  // �Ʋ��������޷����н���

    // �ж��Ƿ��ܽ���
    unsigned char uchResult = CheckCanBargaining( pPlayer );
    if ( uchResult != BargainingDefine::FailedSuccess )
    {
        SendBargainingAckMessage( uchResult );
        return;
    }

    // ���һ�����׷���
    BargainingInfo* pBargainingInfo = theBargainingManager.CreateBargaining();
    if ( pBargainingInfo == NULL )
    { return; }

    // ���ý��׷���ID
    pPlayer->SetBargainingID( pBargainingInfo->GetID() );
    SetBargainingID( pBargainingInfo->GetID() );

    // ��������
    PlayerBargaining& xBarginingA = pBargainingInfo->GetPlayerBargainingA();
    xBarginingA.SetID( pPlayer->GetDBCharacterID() );
    xBarginingA.SetStatus( BargainingDefine::StatusStart );

    // ͬ������
    PlayerBargaining& xBarginingB = pBargainingInfo->GetPlayerBargainingB();
    xBarginingB.SetID( GetDBCharacterID() );
    xBarginingB.SetStatus( BargainingDefine::StatusStart );


    pPlayer->Log(theXmlString.GetString(eServerLog_JiaoYiBegin),GetCharName(), GetDBCharacterID());
	Log(theXmlString.GetString(eServerLog_JiaoYiBegin), pPlayer->GetCharName(), pPlayer->GetDBCharacterID());

	//pPlayer->Log("����-�����[name:%s, dbid:%u] ��ʼ����", GetCharName(), GetDBCharacterID());
	//Log("����-�����[name:%s, dbid:%u] ��ʼ����", pPlayer->GetCharName(), pPlayer->GetDBCharacterID());

	
	// ������ʱ��
    pBargainingInfo->StartTimer( HQ_TimeGetTime(), BargainingDefine::BargainingTime );

    // ������Ϣ��˫��
    SendBargainingStartMessage( pPlayer->GetID() );
    pPlayer->SendBargainingStartMessage( GetID() );
}

void GamePlayer::OnMsgBargainingDataReq( Msg* pMsg )
{
    MsgBargainingDataReq* pReq = static_cast< MsgBargainingDataReq* >( pMsg );
    if ( pReq == NULL )
    { return; }

    // �����Լ� �ͶԷ��Ľ�����Ϣ
    GamePlayer* pTarget = NULL;
    PlayerBargaining* pTargetPlayerBargaining = NULL;
    PlayerBargaining* pPlayerBargaining = GetPlayerBargaining( pTarget, pTargetPlayerBargaining );  
    if ( pPlayerBargaining == NULL || pTarget == NULL || pTargetPlayerBargaining == NULL )
    { return; }

    if ( pPlayerBargaining->GetStatus() != BargainingDefine::StatusStart )
    { return; } // �����Ժ��ܷ�����Ʒ
    //////////////////////////////////////////////////////////////////////////////////////////////
    // �жϽ��׹�������Ʒ
    switch ( pReq->uchBargainintType )
    {
    case BargainingDefine::BargainingMoney:     // �����׽�Ǯ
        ProcessBargainingMoneyReq( pReq->nBargainingValue, pPlayerBargaining, pTarget );
        break;
    case BargainingDefine::BargainingRMB:       // �����׽�
        // ProcessBargainingRMBReq( pReq->nBargainingValue, pPlayerBargaining, pTarget );
        break;
    case BargainingDefine::BargainingItem:      // ��������Ʒ
        ProcessBargainingItemReq( pReq->uchBargainingIndex, pReq->uchBagType, pReq->uchIndex, pReq->n64Guid, pPlayerBargaining, pTarget );
        break;
    case BargainingDefine::BargainingMount:     // ����������
		{
			return; //�Ȳ��ý��� lrt
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

    // �����Լ� �ͶԷ��Ľ�����Ϣ
    GamePlayer* pTarget = NULL;
    PlayerBargaining* pTargetPlayerBargaining = NULL;
    PlayerBargaining* pPlayerBargaining = GetPlayerBargaining( pTarget, pTargetPlayerBargaining );  
    if ( pPlayerBargaining == NULL || pTarget == NULL || pTargetPlayerBargaining == NULL )
    { return; }

    /////////////////////////////////////////////////////////////////////////////////////////////////////
    if ( pPlayerBargaining->GetStatus() != BargainingDefine::StatusStart )
    { return; }

    pPlayerBargaining->SetStatus( BargainingDefine::StatusLock );

    // ������Ϣ֪ͨ�ͻ���
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

    // �����Լ� �ͶԷ��Ľ�����Ϣ
    GamePlayer* pTarget = NULL;
    PlayerBargaining* pTargetPlayerBargaining = NULL;
    PlayerBargaining* pPlayerBargaining = GetPlayerBargaining( pTarget, pTargetPlayerBargaining );  
    if ( pPlayerBargaining == NULL || pTarget == NULL || pTargetPlayerBargaining == NULL )
    { return; }

    if ( pPlayerBargaining->GetStatus() != BargainingDefine::StatusStart )
    { return; } // �����Ժ���ȡ��������Ʒ
    //////////////////////////////////////////////////////////////////////////////////////////
    pPlayerBargaining->ClearBargainingData( pReq->uchBargainingIndex );

    // ������Ϣ���ͻ���
    SendRemoveBargainingDataMessage( GetID(), pReq->uchBargainingIndex );
    pTarget->SendRemoveBargainingDataMessage( GetID(), pReq->uchBargainingIndex );
}

void GamePlayer::OnMsgBargainingFixReq( Msg* pMsg )
{
    MsgBargainingFixReq* pReq = static_cast< MsgBargainingFixReq* >( pMsg );
    if ( pReq == NULL )
    { return; }

    // �����Լ� �ͶԷ��Ľ�����Ϣ
    GamePlayer* pTarget = NULL;
    PlayerBargaining* pTargetPlayerBargaining = NULL;
    PlayerBargaining* pPlayerBargaining = GetPlayerBargaining( pTarget, pTargetPlayerBargaining );  
    if ( pPlayerBargaining == NULL || pTarget == NULL || pTargetPlayerBargaining == NULL )
    { return; }

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////
    if ( pTargetPlayerBargaining->GetStatus() == BargainingDefine::StatusStart )
    { return; } // �Է���û������״̬, ǿ�Ʋ���ȷ������

    if ( pPlayerBargaining->GetStatus() == BargainingDefine::StatusFix )
    { return; } // �Լ��Ѿ�������״̬

    pPlayerBargaining->SetStatus( BargainingDefine::StatusFix );

    // ������Ϣ֪ͨ�ͻ���
    SendBargainingStatusMessage( GetID(), pPlayerBargaining->GetStatus() );
    pTarget->SendBargainingStatusMessage( GetID(), pPlayerBargaining->GetStatus() );

    // ˫����ȷ����
    if ( pTargetPlayerBargaining->GetStatus() == BargainingDefine::StatusFix )
    {
        ProcessBargainingChangeData( pPlayerBargaining, pTarget, pTargetPlayerBargaining );
    }
}

PlayerBargaining* GamePlayer::GetPlayerBargaining( GamePlayer*& pTargetPlayer, PlayerBargaining*& pTargetPlayerBargaining )
{
    pTargetPlayer = NULL;
    pTargetPlayerBargaining = NULL;
    // �����Լ��Ľ�����Ϣ
    BargainingInfo* pBargaining = theBargainingManager.GetBargaining( GetBargainingID() );
    if ( pBargaining == NULL )
    { return NULL; }

    PlayerBargaining* pPlayerBargaining = pBargaining->GetPlayerBargaining( GetDBCharacterID() );
    if ( pPlayerBargaining == NULL )
    { return NULL; }

    // �жϽ��׶Է�
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

    // ���뵽�����б���
    pPlayerBargaining->SetGameMoney( nGameMoney );
	

Log(theXmlString.GetString(eServerLog_JiaoYiByMoney),pTarget->GetCharName(), pTarget->GetDBCharacterID(),nGameMoney );

	
		
	//Log("����-�����[name:%s, dbid:%u] ���ס� ���׽�Ǯ�����׶�: %d", pTarget->GetCharName(), pTarget->GetDBCharacterID(),
	//	nGameMoney );
    // ֪ͨ�Լ�
    SendBargainingDataAckMessage( BargainingDefine::BargainingMoney, nGameMoney, 0, 0, 0, 0 );

    // ֪ͨ�Է�
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

    // ���뵽�����б���
    pPlayerBargaining->SetRMBMoney( nRMBMoney );
	Log(theXmlString.GetString(eServerLog_JiaoYiByJingDing), pTarget->GetCharName(), pTarget->GetDBCharacterID(),nRMBMoney);
			
	//Log("����-�����[name:%s, dbid:%u] ���ס� ���׽𶧡����׶�: %d", pTarget->GetCharName(), pTarget->GetDBCharacterID(),
	//	nRMBMoney );
    // ֪ͨ�Լ�
    SendBargainingDataAckMessage( BargainingDefine::BargainingRMB, nRMBMoney, 0, 0, 0, 0 );

    // ֪ͨ�Է�
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

    // ���� ���� �󶨵Ĳ��ܽ���
    if ( pCharItem->IsLock() || pCharItem->IsBounded() )
    {
        SendBargainingDataErrorMessage( GetID(), BargainingDefine::DataLocked );
        return;
    }

    // ���ڵ���Ʒ���ܽ���
    if ( pCharItem->IsOverdue() )
    {
        SendBargainingDataErrorMessage( GetID(), BargainingDefine::DataOverdue );
        return;
    }

    // ��齻��������
    if ( !CheckPlayerBargainingData( pPlayerBargaining, uchBargainingIndex, uchBagType, n64Guid ) )
    { return; }

    // ���뽻���б�
    BargainingData xBargainingData;
    xBargainingData.SetItemBag( uchBagType );
    xBargainingData.SetItemIndex( uchBagIndex );
    xBargainingData.SetItemCount( pCharItem->GetItemCount() );
    xBargainingData.SetItemGuid( pCharItem->GetItemGuid() );
    xBargainingData.SetItemValue1( pCharItem->itembaseinfo.value1 );
    xBargainingData.SetItemValue2( pCharItem->itembaseinfo.value2 );
    pPlayerBargaining->AddBargainingData( uchBargainingIndex, xBargainingData );


	  Log(theXmlString.GetString(eServerLog_JiaoYiByItem), pTarget->GetCharName(), pTarget->GetDBCharacterID(),uchBargainingIndex, uchBagType, uchBagIndex, n64Guid);

	//Log("����-�����[name:%s, dbid:%u] ���ס� ���׵��ߡ�ʧȥ��Ʒ: %s, ��Ʒid: %d, �ѵ���: %d,  ��Ʒguid: %s ", pTarget->GetCharName(), pTarget->GetDBCharacterID(),
	//	uchBargainingIndex, uchBagType, uchBagIndex, n64Guid );


    // ���͸��Լ�
    SendBargainingDataAckMessage( BargainingDefine::BargainingItem, 0, uchBargainingIndex, uchBagType, uchBagIndex, n64Guid );

    // ���͸��Է�
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

    // ��齻��������
    if ( !CheckPlayerBargainingData( pPlayerBargaining, uchBargainingIndex, uchBagType, n64Guid ) )
    { return; }

    // ���뽻���б�
    BargainingData xBargainingData;
    xBargainingData.SetItemBag( uchBagType );
    xBargainingData.SetItemIndex( uchBagIndex );
    xBargainingData.SetItemCount( 1 );
    xBargainingData.SetItemGuid( pMount->GetMountGuid() );
    pPlayerBargaining->AddBargainingData( uchBargainingIndex, xBargainingData );

	
        Log(theXmlString.GetString(eServerLog_JiaoYiByMount),pTarget->GetCharName(), pTarget->GetDBCharacterID(),pMount->GetMountName());
	
	
		
	//Log("����-�����[name:%s, dbid:%u] ���ס� ������� %s", pTarget->GetCharName(), pTarget->GetDBCharacterID(),
	//	pMount->GetMountName());

    // ���͸��Լ�
    SendBargainingDataAckMessage( BargainingDefine::BargainingMount, 0, uchBargainingIndex, uchBagType, uchBagIndex, n64Guid );

    // ���͸��Է�
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
	// ��齻��������
	if ( !CheckPlayerBargainingData( pPlayerBargaining, uchBargainingIndex, uchBagType, n64Guid ) )
	{ return; }

	// ���뽻���б�
	BargainingData xBargainingData;
	xBargainingData.SetItemBag( uchBagType );
	xBargainingData.SetItemIndex( uchBagIndex );
	xBargainingData.SetItemCount( 1 );
	xBargainingData.SetItemGuid( pPet->GetPetGuid() );
	pPlayerBargaining->AddBargainingData( uchBargainingIndex, xBargainingData );


   
		Log(theXmlString.GetString(eServerLog_JiaoYiByPet),pTarget->GetCharName(), pTarget->GetDBCharacterID(),
			uchBargainingIndex, uchBagType, uchBagIndex, n64Guid);


	//Log("����-�����[name:%s, dbid:%u] ���ס� ���׳��ʧȥ��Ʒ: %s, ��Ʒid: %d, �ѵ���: %d,  ��Ʒguid: %s ", pTarget->GetCharName(), pTarget->GetDBCharacterID(),
	//	uchBargainingIndex, uchBagType, uchBagIndex, n64Guid);

	// ���͸��Լ�
	SendBargainingDataAckMessage( BargainingDefine::BargainingPet, 0, uchBargainingIndex, uchBagType, uchBagIndex, n64Guid );

	// ���͸��Է�
	pTarget->SendShowBargainingDataMessage( BargainingDefine::BargainingPet, 0, uchBargainingIndex, pPet, sizeof( SPetItem ) );
}

void GamePlayer::ProcessBargainingChangeData( PlayerBargaining* pPlayerBargaining, GamePlayer* pTarget, PlayerBargaining* pTargetPlayerBargaining )
{
    if ( pPlayerBargaining == NULL || pTarget == NULL || pTargetPlayerBargaining == NULL )
    { return; }

    if ( IsWantSwitchGameWaitSaveInfoOk() || pTarget->IsWantSwitchGameWaitSaveInfoOk() )
    { return; } // ��һ���ȴ���������Ӧʱ, ���ý���

    // ���ܽ���, �����ǻص���ʼ״̬
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

    // ������Ʒ
    ProcessBargainingChangeData( pTarget, pTargetPlayerBargaining );
    pTarget->ProcessBargainingChangeData( this, pPlayerBargaining );
	
	Log(theXmlString.GetString(eServerLog_JiaoYiEnd),pTarget->GetCharName(), pTarget->GetDBCharacterID());
	//Log("����-�����[name:%s, dbid:%u] ��������", pTarget->GetCharName(), pTarget->GetDBCharacterID());
    // ���׳ɹ�, ɾ������
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

    // �ж���Ʒ����
    int nNormalCount   = 0;     // ��ͨ��Ʒ����
    int nMaterialCount = 0;     // ������Ʒ����
    int nMountCount    = 0;     // ��������
    int nPetCount      = 0;     // ��������

    // �ٴ�У�齻����Ʒ, �жϽ��׵���Ʒ��Ч�Ժ�����
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

    // ��ͨ����
    if ( nNormalCount > pTarget->GetNullItemCount( BT_NormalItemBag ) )
    {
        SendBargainingDataErrorMessage( pTarget->GetID(), BargainingDefine::NormalFull );
        pTarget->SendBargainingDataErrorMessage( pTarget->GetID(), BargainingDefine::NormalFull );
        return false;
    }

    // ���ϱ���
    if ( nMaterialCount > pTarget->GetNullItemCount( BT_MaterialBag ) )
    {
        SendBargainingDataErrorMessage( pTarget->GetID(), BargainingDefine::MaterialFull );
        pTarget->SendBargainingDataErrorMessage( pTarget->GetID(), BargainingDefine::MaterialFull );
        return false;
    }

    // ���ﱳ��
    if ( nMountCount > pTarget->GetNullItemCount( BT_MountBag ) )
    {
        SendBargainingDataErrorMessage( pTarget->GetID(), BargainingDefine::MountFull );
        pTarget->SendBargainingDataErrorMessage( pTarget->GetID(), BargainingDefine::MountFull );
        return false;
    }

    // ���ﱳ��
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
    // ����λ�ô���
    const BargainingData* pBargainingData = pPlayerBargaining->GetBargainingData( uchBargainingIndex );
    if ( pBargainingData == NULL )
    {
        SendBargainingDataErrorMessage( GetID(), BargainingDefine::IndexError );
        return false;
    }

    // ��λ�����Ѿ�����Ʒ��
    if ( pBargainingData->GetItemGuid() != 0 && pBargainingData->GetItemGuid() != n64Guid )
    {
        SendBargainingDataErrorMessage( GetID(), BargainingDefine::IndexAlready );
        return false;
    }

    // �жϸõ���û���ڽ�������
    if ( !pPlayerBargaining->CheckBargainingData( uchBargainingIndex, uchBagType, n64Guid ) )
    {
        SendBargainingDataErrorMessage( GetID(), BargainingDefine::DataAlready );
        return false;
    }

    return true;
}

void GamePlayer::ProcessBargainingChangeData( GamePlayer* pTarget, PlayerBargaining* pTargetPlayerBargaining )
{
     // ���뵽�˺���, ������return, һ��Ҫ�������߼���ִ�����.

	
    Log( theXmlString.GetString( eLog_info_2slk_9 ), GetCharName(), pTarget->GetCharName() );

    // ��Ϸ��
	//LYH��־��� ���ף���Ǯ�� ��ȷ��
	if(pTargetPlayerBargaining->GetGameMoney() > 0)
		theLogEventService.LogItemTrade(GetAccountID(),GetDBCharacterID(),pTarget->GetAccountID(),pTarget->GetDBCharacterID(),0,0,0,pTargetPlayerBargaining->GetGameMoney(),eItemTrade_Bargain,
		                                GetCharName(),pTarget->GetCharName(),"Money");

    OperateMoney( EOT_Add, pTargetPlayerBargaining->GetGameMoney(), true, __FUNCTION__, __LINE__ ,ePlayerMoneySourceType_Bargain);
    pTarget->OperateMoney( EOT_Sub, pTargetPlayerBargaining->GetGameMoney(), true, __FUNCTION__, __LINE__,ePlayerMoneySourceType_Bargain );

    // ��
    OperateJinDing( EOT_Add, pTargetPlayerBargaining->GetRMBMoney(), __FUNCTION__, __LINE__ ,ePlayerMoneySourceType_Bargain);
    pTarget->OperateJinDing( EOT_Sub, pTargetPlayerBargaining->GetRMBMoney(), __FUNCTION__, __LINE__,ePlayerMoneySourceType_Bargain );

    // �ȼ���Ʒ
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

                // ��ӵ���
                unsigned short ustCount = pCharItem->GetItemCount();
                AddItemToBag( *pCharItem, ustCount, EIGS_Bargaining );
				//LYH��־��� ������Ʒ ��ȷ��

				 ItemDefine::SItemCommon* pItemCommon = GettheItemDetail().GetItemByID( pCharItem->GetItemID() );

				 if ( pItemCommon != NULL )
				 {
				
					 theLogEventService.LogItemTrade(GetAccountID(),GetDBCharacterID(),pTarget->GetAccountID(),pTarget->GetDBCharacterID(),
												pCharItem->GetItemID(),ustCount,pCharItem->GetItemGuid(),0,eItemTrade_Bargain,
												GetCharName(),pTarget->GetCharName(),pItemCommon->GetItemName());   
               
                    char szID[ 60 ] = { 0 };
                    pTarget->Log( theXmlString.GetString( eLog_info_2slk_11 ), pItemCommon->GetItemName(), BigInt2String( pCharItem->GetItemGuid(), szID ), pCharItem->GetItemCount() );
               

				//LYH��־���
				theLogEventService.LogItemConsume(pTarget->GetAccountID(),pTarget->GetDBCharacterID(),pCharItem->GetItemID(),
												pCharItem->GetItemCount(),pCharItem->GetItemGuid(),
												0,eItemLogInfo_ItemConsume_Bargain,
												pTarget->GetCharName(),pItemCommon->GetItemName());
                 }
                // ɾ������
				 bool result = false;
                result = pTarget->RemoveItem( pData->GetItemBag(), pData->GetItemIndex(), pCharItem->GetItemCount(), pCharItem->GetItemGuid() );
				if (!result)
				{
					LOG_MESSAGE(LOGICSYSTEMOBJECT, LOG_PRIORITY_ERROR,"%d-%d ����ʱɾ����Ʒʧ��,���ܳ���װ������.",pTarget->GetDBCharacterID(), pCharItem->GetItemID());
				}
				
            }
            break;
        case BT_MountBag:
            {
                // ����ֻ����guid������, ��Ϊ����ɾ����һ��, ���������Ѿ��ı���
                SMountItem* pMount = pTarget->GetMountByGuid( pData->GetItemGuid() );
                if ( pMount == NULL )
                { continue; }

                // �������
                AddMount( *pMount );

                char szID[ 60 ] = { 0 };
                Log( theXmlString.GetString( eLog_info_2slk_14 ), pMount->GetMountName(), BigInt2String( pMount->GetMountGuid(), szID ), 1 );
                pTarget->Log( theXmlString.GetString( eLog_info_2slk_11 ), pMount->GetMountName(), BigInt2String( pMount->GetMountGuid(), szID ), 1 );

                // ɾ������
                pTarget->RemoveMountByGuid( pData->GetItemGuid() );

				//LYH��־��� ������Ʒ ��ȷ��
				theLogEventService.LogItemTrade(GetAccountID(),GetDBCharacterID(),pTarget->GetAccountID(),pTarget->GetDBCharacterID(),pMount->GetMountID(),
												1,pMount->GetMountGuid(),0,eItemTrade_Bargain,GetCharName(),pTarget->GetCharName(),pMount->GetMountName());

            }
            break;
        case BT_PetBag:
            {
                // ����ֻ����guid������, ��Ϊ����ɾ����һ��, ���������Ѿ��ı���
                SPetItem* pPet = pTarget->_petManager.GetPetByGuid( pData->GetItemGuid() );
                if ( pPet == NULL )
                { continue; }

                // ��ӳ���
                AddPet( *pPet );

                char szID[ 60 ] = { 0 };
                Log( theXmlString.GetString( eLog_info_2slk_14 ), pPet->GetPetName(), BigInt2String( pPet->GetPetGuid(), szID ), 1 );
                pTarget->Log( theXmlString.GetString( eLog_info_2slk_11 ), pPet->GetPetName(), BigInt2String( pPet->GetPetGuid(), szID ), 1 );

                // ɾ������
                pTarget->RemovePetByGuid( pData->GetItemGuid(), EDS_Stall );

				//LYH��־��� ������Ʒ ��ȷ��
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
