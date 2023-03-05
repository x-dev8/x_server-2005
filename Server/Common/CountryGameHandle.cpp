#include "CountryManager.h"
#include "CenterServerNetEvent.h"
#include "GamePlayer.h"
#include "ShareData.h"
#include "CountryConfig.h"
#include "RunStatus.h"
#include "CountryReward.h"
#include "GamePlayer.h"
#include "ItemBag.h"

long CenterServerNetEvent::OnProcessCountryMessage(TcpServer* pTcpServer, NetClient* pNetClient,unsigned long msgType, Msg* pMessage )
{
    MESSAGE_MAPPING_BEGIN
        MESSAGE_HANDLE( CS2GS_COUNTRYNOTICECHANGEACK, CS2GSCountryNoticeChangeAck, _OnCS2GSCountryNoticeChangeAck );
        MESSAGE_HANDLE( CS2GS_COUNTRYQUESTSTATUSCHANGEACK, CS2GSCountryQuestStatusChangeAck, _OnCS2GSCountryQuestStatusChangeAck );
        MESSAGE_HANDLE( CS2GS_COUNTRYDATECHANGEED, CS2GSCountryDateChangeed, _OnCS2GSCountryDateChangeed );
        MESSAGE_HANDLE( CS2GS_COUNTRYQUESTSTATUSSTOP, CS2GSCountryQuestStatusStop, _OnCS2GSCountryQuestStatusStop );
        MESSAGE_HANDLE( CS2GS_COUNTRYDATALIST, CS2GSCountryDataList, _OnCS2GSCountryDataList );
        MESSAGE_HANDLE( CS2GS_COUNTRYBATTLERESULT, CS2GSCountryBattleResult, _OnCS2GSCountryBattleResult );
        MESSAGE_HANDLE( CS2GS_COUNTRYREQUESTRAISEACK, CS2GSCountryRequestRaiseAck, _OnCS2GSCountryRequestRaiseAck );
        MESSAGE_HANDLE( CS2GS_COUNTRYBORDERSFIHGT, CS2GSCountryBordersFight, _OnCS2GSCountryBordersFight );
        MESSAGE_HANDLE( CS2GS_COUNTRYOPERATETOPLAYERREQ, CS2GSCountryOperateToPlayerReq, _OnCS2GSCountryOperateToPlayerReq );
        MESSAGE_HANDLE( CS2GS_COUNTRYOPERATETOPLAYERACK, CS2GSCountryOperateToPlayerAck, _OnCS2GSCountryOperateToPlayerAck );
        MESSAGE_HANDLE( CS2GS_COUNTRYCONVENEREQ, CS2GSCountryConveneReq, _OnCS2GSCountryConveneReq );
        MESSAGE_HANDLE( CS2GS_COUNTRYSETOFFICIAL, CS2GSCountrySetOfficial, _OnCS2GSCountrySetOfficial );
        MESSAGE_HANDLE( CS2GS_COUNTRYDATAUPDATE, CS2GSCountryDataUpdate, _OnCS2GSCountryDataUpdate );
        MESSAGE_HANDLE( CS2GS_COUNTRYOFFICIALCHANGE, CS2GSCountryOfficialChange, _OnCS2GSCountryOfficialChange );
        MESSAGE_HANDLE( CS2GS_TELLWEAKCOUNTRY, CS2GSTellWeakCountry, _OnCS2GSTellWeakCountry );
        MESSAGE_HANDLE( CS2GS_COUNTRYNAMECHANGE, CS2GSCountryNameChange, _OnCS2GSCountryNameChange );
        MESSAGE_HANDLE( CS2GS_COUNTRYWARSTATUS, CS2GSCountryWarStatus, _OnCS2GSCountryWarStatus );
        MESSAGE_HANDLE( CS2GS_COUNTRYWARKILLPLAYER, CS2GSCountryWarKillPlayer, _OnCS2GSCountryWarKillPlayer );
	    MESSAGE_HANDLE( CS2GS_TELLSTRONGCOUNTRY, CS2GSTellStrongCountry, _OnCS2GSTellStrongCountry );
		MESSAGE_HANDLE( CS2GS_COUNTRYWEAKSTRONGTH, CS2GSCountryWeakStrongthChange, _OnCS2GSCountryWeakStrong);
		MESSAGE_HANDLE( CS2GS_ADDCOUNTRYOFFICIAL, CS2GSAddCountryOfficial, _OnCS2GSAddCountryOfficial);
        MESSAGE_HANDLE( CS2GS_COUNTRYOFFICIALREWARD, CS2GSCountryOfficialReward, _OnCS2GSCountryOfficialReward);
		MESSAGE_HANDLE( CS2GS_ADDCOUNTRYINFOACK, CS2GSAddCountryInfoAck, _OnCS2GSAddCountryInfoAck );

		MESSAGE_HANDLE( CS2GS_REQUESTCOUNTRYINFOACK, CS2GSRequestCountryInfoAck, _OnCS2GSRequestCountryInfoAck );
		
    MESSAGE_MAPPING_END

    return ER_Success;
}

void CenterServerNetEvent::_OnCS2GSCountryDataUpdate( NetClient* pNetClient, CS2GSCountryDataUpdate* pMessage )
{
    GameCountry* pCountry = theGameCountryManager.GetCountry( pMessage->uchCountryID );
    if ( pCountry == NULL )
    { return; }

    pCountry->UpdateCountryData( pMessage->uchUpdateType, pMessage->n64Value );
}
void CenterServerNetEvent::_OnCS2GSAddCountryInfoAck( NetClient* pNetClient, CS2GSAddCountryInfoAck* pMessage )
{
	GameCountry* pCountry = theGameCountryManager.GetCountry( pMessage->uchCountryID );
    if ( pCountry == NULL )
    { return; }
	pCountry->AddCountryInfo(pMessage->szNotice,pMessage->Time,pMessage->Value);
}
void CenterServerNetEvent::_OnCS2GSRequestCountryInfoAck( NetClient* pNetClient, CS2GSRequestCountryInfoAck* pMessage )
{
	//���շ������˷����������й�����Ϣ
	for(int i =CountryDefine::Country_Init;i<CountryDefine::Country_Max;++i)
	{
		GameCountry* pCountry = theGameCountryManager.GetCountry(i);
		if(!pCountry) continue;
		for(int j = 0;j<pMessage->Sum;++j)
		{
			if(pMessage->CountryID[j] != i)
				continue;
			pCountry->SetCountryInfo(pMessage->Info[j],pMessage->Time[j],pMessage->values[j]);
		}
	}
}
void CenterServerNetEvent::_OnCS2GSCountryNoticeChangeAck( NetClient* pNetClient, CS2GSCountryNoticeChangeAck* pMessage )
{
    GameCountry* pCountry = theGameCountryManager.GetCountry( pMessage->uchCountryID );
    if ( pCountry == NULL )
    { return; }

    pCountry->ProcessNoticeChange( pMessage->nPlayerID, pMessage->szNotice );
}

void CenterServerNetEvent::_OnCS2GSCountryQuestStatusChangeAck( NetClient* pNetClient, CS2GSCountryQuestStatusChangeAck* pMessage )
{
    GameCountry* pCountry = theGameCountryManager.GetCountry( pMessage->uchCountryID );
    if ( pCountry == NULL )
    { return; }

    OperateTime* pOperateTime = pCountry->GetQuestOperate( pMessage->uchQuestType );
    if ( pOperateTime == NULL )
    { return; }

    const CountryConfig::QuestSetting* pSetting = theCountryConfig.GetQuestSetting( pMessage->uchQuestType );
    if ( pSetting == NULL )
    { return; }

    pOperateTime->SetCount( pOperateTime->GetCount() + 1 );
    pOperateTime->SetStartTime( TimeEx::GetCurrentTime().GetTime() );

    GamePlayer* pPlayer = theRunTimeData.GetGamePlayerByDBID( pMessage->nPlayerID );
    if ( pPlayer != NULL )      // ֪ͨ�ͻ����޸ĳɹ�
    {
        MsgCountryQuestStatusChangeAck xAck;
        xAck.uchQuestType = pMessage->uchQuestType;
        pPlayer->SendMessageToClient( &xAck );
    }

    // ȫ���㲥, ֪ͨ�����������
    MsgTellCountryQuestStatus xTell;
    MsgTellCountryQuestStatus::QuestStatus xStatus;
    xStatus.uchType      = pMessage->uchQuestType;
    xStatus.n64StartTime = pOperateTime->GetStartTime();
    xStatus.bNeedNotice  = true;
    xTell.AddQuestStatus( xStatus );
    GettheServer().SendMsgToCountry( &xTell, pMessage->uchCountryID, false );
	
	//�������������� ��������Ŀ�
	MsgCountryFlyMap msg;
	msg.uchType = pMessage->uchQuestType;
	GettheServer().SendMsgToCountry( &msg, pMessage->uchCountryID, false );
}

void CenterServerNetEvent::_OnCS2GSCountryDateChangeed( NetClient* pNetClient, CS2GSCountryDateChangeed* pMessage )
{
    GameCountry* pCountry = theGameCountryManager.GetCountry( pMessage->uchCountryID );
    if ( pCountry == NULL )
    { return; }

    pCountry->ClearAllOperateTime();
}

void CenterServerNetEvent::_OnCS2GSCountryQuestStatusStop( NetClient* pNetClient, CS2GSCountryQuestStatusStop* pMessage )
{
    GameCountry* pCountry = theGameCountryManager.GetCountry( pMessage->uchCountryID );
    if ( pCountry == NULL )
    { return; }

    OperateTime* pOperateTime = pCountry->GetQuestOperate( pMessage->uchQuestType );
    if ( pOperateTime == NULL )
    { return; }

    pOperateTime->SetStartTime( 0 );

    // ֪ͨȫ�����
    MsgCountryQuestStatusStop xStop;
    xStop.uchQuestType = pMessage->uchQuestType;
    GettheServer().SendMsgToCountry( &xStop, pMessage->uchCountryID, false );
}

void CenterServerNetEvent::_OnCS2GSCountryDataList( NetClient* pNetClient, CS2GSCountryDataList* pMessage )
{
	//InitCountry�����Ѿ����ù�����:SetLoadSuccess( true ); + theRunStatus.SetLoadSuccess( RunStatusDefine::LoadContrySuccess );
    theGameCountryManager.InitCountry( pMessage->xData );
    theGameCountryManager.SetWeakCountry( pMessage->uchWeakCountryID );
	theGameCountryManager.SetStrongCountry( pMessage->uchStrongCountryID );
}

void CenterServerNetEvent::_OnCS2GSCountryBattleResult( NetClient* pNetClient, CS2GSCountryBattleResult* pMessage )
{
	//1 �Ǻ� 2 ���� ��ɫ�Ƿ��ط�����ɫ�ǽ�����
	//if (pMessage->nCampBattle == 1) //zhuxincong ��������ɹ�
	//{
	//	return;
	//}

    GameCountry* pCountry = theGameCountryManager.GetCountry( pMessage->uchCountryID );
    if ( pCountry == NULL )
    { return; }

    pCountry->ProcessCountryBattleResult( pMessage->uchBattleType, pMessage->uchWinType, pMessage->nGuildID ); 

	//���͹���ս֮��Ľ�����ɾ����Ʒ,�߼������� by vvx 2013.3.27
	//zhuxincong ��ս����
	//GameGuild* pReplaceGuild = theGameGuildManager.GetGuild( pMessage->nGuildID );
	//GameGuild* pReplaceLoseGuild = theGameGuildManager.GetGuild( pMessage->nLoseGuildID );
	//if ( pReplaceGuild == NULL  || pReplaceLoseGuild ==NULL)
	//{ return; }

	//GuildMember* pMember = pReplaceGuild->GetMember( pReplaceGuild->GetMasterID() );
	//GuildMember* pMemberLose = pReplaceLoseGuild->GetMember( pReplaceLoseGuild->GetMasterID() );
	//if ( pMember == NULL || pMemberLose == NULL)
	//{ return; }

	//GamePlayer* pWinPlayer = theRunTimeData.GetGamePlayerByDBID( pMember->GetID() );
	//if (pWinPlayer)
	//{
	//	int nItemId = theCountryReward.GetItemID(pMember->GetLevel(),CountryDefine::Position_King);
	//	ItemDefine::SItemCommon* pItemCommon = GettheItemDetail().GetItemByID( nItemId);
	//	if (!pItemCommon)
	//	{
	//		return;
	//	}
	//	//zhuxincong �����Ǹ�����ƷID ������Ʒ
	//	SCharItem item;
	//	if( !theRunTimeData.CreateItem( NULL, nItemId, 1, HelperFunc::CreateID(), item ) )
	//	{
	//		return;
	//	}
	//	GS2CSCountryBattleReward xResult;
	//	memcpy(&xResult.CItem,&item,sizeof(SCharItem));
	//	xResult.nLevel = pMember->GetLevel();
	//	xResult.nPlayerID = pMember->GetID();
	//	xResult.nGuidID = pMessage->nGuildID;
	//	xResult.oldID = pMemberLose->GetID()/*xResult.newID*/;
	//	xResult.newID = pMember->GetID();
	//	xResult.nCampBattle = pMessage->nCampBattle;

	//	GettheServer().SendMsgToCenterServer( &xResult );
	//}
	//////zhuxincong ɾ���Ϲ�������Ʒ
	//if (xResult.oldID != xResult.newID)
	//{
	//	
	//	GamePlayer* pPlayer = theRunTimeData.GetGamePlayerByDBID( xResult.oldID );
	//	if (pPlayer == NULL)
	//	{
	//		return;
	//	}	
	//	if ( pMember == NULL )
	//	{ return; }
	//	int nOldItemId = theCountryReward.GetSubItemID(pPlayer->GetLevel(),CountryDefine::Position_King);
	//	int nOldMountID = theCountryReward.GetSubMountID(pPlayer->GetLevel(),CountryDefine::Position_King);
	//	ItemDefine::SItemCommon* pOldItemCommon = GettheItemDetail().GetItemByID( nOldItemId);
	//	if (!pOldItemCommon)
	//	{
	//		return;
	//	}
	//	//ɾ��Item
	//	MsgRemoveItem msg;
	//	msg.ucItemBagType = 0;
	//	msg.ustItemID     = nOldItemId;
	//	msg.ustCount      = 1;
	//	GettheServer().SendMsgToSingle( &msg, pPlayer );
	//	pPlayer->RemoveMountByGuid(nOldMountID);
	////	//_NormalItemBag.RemoveItemByID(nOldItemId,1);

	//}

}

void CenterServerNetEvent::_OnCS2GSCountryRequestRaiseAck( NetClient* pNetClient, CS2GSCountryRequestRaiseAck* pMessage )
{
    GameCountry* pCountry = theGameCountryManager.GetCountry( pMessage->uchCountryID );
    if ( pCountry == NULL )
    { return; }

    pCountry->SetRaiseCount( pCountry->GetRaiseCount() + 1 );
    pCountry->StartRaiseTimer( HQ_TimeGetTime(), theCountryConfig.GetRaiseKeepTime() * OneMinuteMicroSecond + 2000 );        // ����ļ����ʱ��

    GamePlayer* pPlayer = theRunTimeData.GetGamePlayerByDBID( pMessage->nPlayerID );
    if ( pPlayer != NULL )
    {
        MsgCountryRequestRaiseAck xAck;
        pPlayer->SendMessageToClient( &xAck );
    }

    // ����ļ��
    MsgCountryRaiseToPlayerReq xReq;
    GettheServer().SendMsgToCountry( &xReq, pMessage->uchCountryID, false, theCountryConfig.GetMinRaiseLevel() );
}

void CenterServerNetEvent::_OnCS2GSCountryBordersFight( NetClient* pNetClient, CS2GSCountryBordersFight* pMessage )
{
    GameCountry* pCountry = theGameCountryManager.GetCountry( pMessage->uchCountryID );
    if ( pCountry == NULL )
    { return; }

    pCountry->AddBordersFight( pMessage->ustMapID, pMessage->nPosX, pMessage->nPosY );

    // ���͸�ȫ��
    MsgTellCountryBordersFight xFight;
    xFight.ustMapID = pMessage->ustMapID;
    xFight.ustPosX  = pMessage->nPosX;
    xFight.ustPosY  = pMessage->nPosY;
    GettheServer().SendMsgToCountry( &xFight, pMessage->uchCountryID, false );
}

void CenterServerNetEvent::_OnCS2GSCountryOperateToPlayerReq( NetClient* pNetClient, CS2GSCountryOperateToPlayerReq* pMessage )
{
    GameCountry* pCountry = theGameCountryManager.GetCountry( pMessage->uchCountryID );
    if ( pCountry == NULL )
    { return; }

    GamePlayer* pPlayer = theRunTimeData.GetGamePlayerByDBID( pMessage->nPlayerID );
    if ( pPlayer == NULL )
    { return; }

    if ( pPlayer->GetCountry() != pMessage->uchCountryID )
    {
        MsgCountryOperateToPlayerAck xAck;
        xAck.uchOperate = pMessage->uchOperate;
        xAck.uchResult  = MsgCountryOperateToPlayerAck::ECD_NotSameCountry;
        GettheServer().SendMsgToSingleRemote( CountryDefine::ErrorID, &xAck, pMessage->nOfficialID, "" );
        return;
    }

    switch ( pMessage->uchOperate )
    {
    case MsgCountryOperateToPlayerReq::Operate_BanSpeak:
        {
            // ���ý���
            pPlayer->SetBanSpeakTime( theCountryConfig.GetBanSpeakTime() * OneMinuteMicroSecond, true );     
        }
        break;
    case MsgCountryOperateToPlayerReq::Operate_Chain:
        {
            // �������״̬
            if ( pPlayer->ApplyBufferStatus( theCountryConfig.GetChainStatus(), 1, pPlayer->GetID(), SCharBuff::StatusEventType_Other, 0 ) != GLR_Success )
            { return; }

            pPlayer->OnBuffStatusChanged( true );
        }
        break;
    case MsgCountryOperateToPlayerReq::Operate_Remit:
        {
            // û�б�����, ��û������״̬
            if ( !pPlayer->IsBanSpeak() && !pPlayer->_buffManager.IsHaveStatus( theCountryConfig.GetChainStatus() ) )
            { 
                MsgCountryOperateToPlayerAck xAck;
                xAck.uchOperate = pMessage->uchOperate;
                xAck.uchResult  = MsgCountryOperateToPlayerAck::ECD_NeedNotRemit;
                GettheServer().SendMsgToSingleRemote( CountryDefine::ErrorID, &xAck, pMessage->nOfficialID, "" );
                return;
            } 

            if ( pPlayer->IsBanSpeak() )
            {
                pPlayer->SetBanSpeakTime( 0, true );
            }

            if ( pPlayer->_buffManager.ClearBuffByBuffIdLevel( theCountryConfig.GetChainStatus(), 1 ) )
            { pPlayer->OnBuffStatusChanged( true ); }
        }
        break;
    default:
        return;
    }

    MsgCountryTellOperateToPlayer xTellPlayer;
    xTellPlayer.uchOperate = pMessage->uchOperate;
    pPlayer->SendMessageToClient( &xTellPlayer );

    MsgTellOperateToCountry xTellCountry;
    xTellCountry.uchOperate = pMessage->uchOperate;
    HelperFunc::SafeNCpy( xTellCountry.szName, pPlayer->GetCharName(), sizeof( xTellCountry.szName ) );
    GettheServer().SendMsgToCountry( &xTellCountry,  pCountry->GetID(), true );

    // ֪ͨ��CenterServer
    GS2CSCountryOperateToPlayerAck xAck;
    xAck.uchCountryID = pMessage->uchCountryID;
    xAck.uchOperate   = pMessage->uchOperate;
    xAck.nOfficialID  = pMessage->nOfficialID;
    GettheServer().SendMsgToCenterServer( &xAck );
}

void CenterServerNetEvent::_OnCS2GSCountryOperateToPlayerAck( NetClient* pNetClient, CS2GSCountryOperateToPlayerAck* pMessage )
{
    GameCountry* pCountry = theGameCountryManager.GetCountry( pMessage->uchCountryID );
    if ( pCountry == NULL )
    { return; }

    switch ( pMessage->uchOperate )
    {
    case MsgCountryOperateToPlayerReq::Operate_BanSpeak:
        {
            pCountry->SetBanSpeakCount( pCountry->GetBanSpeakCount() + 1 );
        }
        break;
    case MsgCountryOperateToPlayerReq::Operate_Chain:
        {
            pCountry->SetChainCount( pCountry->GetChainCount() + 1 );
        }
        break;
    case MsgCountryOperateToPlayerReq::Operate_Remit:
        {
            pCountry->SetRemitCount( pCountry->GetRemitCount() + 1 );
        }
        break;
    default:
        break;
    }

    GamePlayer* pPlayer = theRunTimeData.GetGamePlayerByDBID( pMessage->nOfficialID );
    if ( pPlayer != NULL )
    {
        MsgCountryOperateToPlayerAck xAck;
        xAck.uchOperate = pMessage->uchOperate;
        pPlayer->SendMessageToClient( &xAck );
    }
}

void CenterServerNetEvent::_OnCS2GSCountryConveneReq( NetClient* pNetClient, CS2GSCountryConveneReq* pMessage )
{
    GameCountry* pCountry = theGameCountryManager.GetCountry( pMessage->uchCountryID );
    if ( pCountry == NULL )
    { return; }

    pCountry->SetConveneCount( pCountry->GetConveneCount() + 1 );

    // ��������
    pCountry->StartConveneTimer( HQ_TimeGetTime(), theCountryConfig.GetConveneTime() * OneMinuteMicroSecond );
    pCountry->SetConvenePlace( pMessage->nMapID, pMessage->fX, pMessage->fY );

    GamePlayer* pPlayer = theRunTimeData.GetGamePlayerByDBID( pMessage->nOfficialID );
    if ( pPlayer != NULL )
    {
        MsgCountryConveneResult xResult;
        pPlayer->SendMessageToClient( &xResult );
    }

    uint16 ustExceptID = ( pPlayer != NULL ? pPlayer->GetID() : InvalidGameObjectId );
    // ���͸�ȫ��
    MsgCountryConveneReq xReq;
    xReq.nOfficialID = pMessage->nOfficialID;
    GettheServer().SendMsgToCountry( &xReq, pMessage->uchCountryID, false, pMessage->ustLevel, ustExceptID );
}

void CenterServerNetEvent::_OnCS2GSCountrySetOfficial( NetClient* pNetClient, CS2GSCountrySetOfficial* pMessage )
{
    GameCountry* pCountry = theGameCountryManager.GetCountry( pMessage->uchCountryID );
    if ( pCountry == NULL )
    { return; }

    pCountry->SetKingGuild( pMessage->nGuildID );
    GamePlayer* pPlayer = theRunTimeData.GetGamePlayerByDBID( pMessage->nPlayerID );
    if ( pPlayer != NULL )
    {
        // ���óƺ�
		pCountry->AppointOfficial( pMessage->uchPosition, pMessage->nPlayerID, pMessage->szName
			,pPlayer->GetCharInfo().baseinfo.aptotic.ucSex,
			pPlayer->GetCharInfo().visual.faceId
		,pPlayer->GetCharInfo().visual.hairId,pPlayer->GetCharInfo().baseinfo.aptotic.usProfession);
        uint8 uchCountryTitle = CountryDefine::GetCountryTitleByPosition( pMessage->uchPosition );
        pPlayer->SetCountryTitle( uchCountryTitle, true );
    }
	else
		pCountry->AppointOfficial( pMessage->uchPosition, pMessage->nPlayerID, pMessage->szName,pMessage->sexID,pMessage->faceID,pMessage->headerID,pMessage->professionID);
}

void CenterServerNetEvent::_OnCS2GSCountryOfficialChange( NetClient* pNetClient, CS2GSCountryOfficialChange* pMessage )
{
    GameCountry* pCountry = theGameCountryManager.GetCountry( pMessage->uchCountryID );
    if ( pCountry == NULL )
    { return; }

	//GamePlayer* pPlayer = theRunTimeData.GetGamePlayerByName( pMessage->szName );
	//int nLevel = (pPlayer->GetLevel()/10)*10;//int nMountLevel = (nLevel/10)*10;
	//int nItemID = theCountryReward.GetItemID(nLevel,pMessage->uchPosition);
	//ItemDefine::SItemCommon* pItemCommon = GettheItemDetail().GetItemByID( nItemID );
    pCountry->ProcessCountryOfficialChange( pMessage->uchPosition, pMessage->nPlayerID, pMessage->szName,pMessage->sexID,pMessage->faceID,pMessage->headerID,pMessage->professionID /*,(SCharItem*)pItemCommon*/);

}
void CenterServerNetEvent::_OnCS2GSTellStrongCountry( NetClient* pNetClient, CS2GSTellStrongCountry* pMessage )
{
	theRunTimeData.SetStrongCountry( pMessage->uchCountryID );
}
void CenterServerNetEvent::_OnCS2GSTellWeakCountry( NetClient* pNetClient, CS2GSTellWeakCountry* pMessage )
{
    theRunTimeData.SetWeakCountry( pMessage->uchCountryID );
}

void CenterServerNetEvent::_OnCS2GSCountryNameChange( NetClient* pNetClient, CS2GSCountryNameChange* pMessage )
{
    GameCountry* pCountry = theGameCountryManager.GetCountry( pMessage->uchCountryID );
    if ( pCountry == NULL )
    { return; }

    pCountry->SetName( pMessage->szName );
    pCountry->SetChangeName( true );
    
    // ֪ͨ�������
    MsgTellCountryNameChange xChange;
    xChange.uchCountryID = pMessage->uchCountryID;
    HelperFunc::SafeNCpy( xChange.szPlayer, pMessage->szPlayer, sizeof( xChange.szPlayer ) );
    HelperFunc::SafeNCpy( xChange.szName, pMessage->szName, sizeof( xChange.szName ) );
    GettheServer().SendMsgToWorld( &xChange, false );

    // ֪ͨ�����޸ĳɹ�
    GamePlayer* pPlayer = theRunTimeData.GetGamePlayerByDBID( pMessage->nPlayerID );
    if ( pPlayer != NULL )
    {
        MsgChangeCountryNameAck xAck;
        pPlayer->SendMessageToClient( &xAck );
    }
}

void CenterServerNetEvent::_OnCS2GSCountryWarStatus( NetClient* pNetClient, CS2GSCountryWarStatus* pMessage )
{
    theGameCountryManager.ProcessWarStatusChange( pMessage->uchStatus );
}

void CenterServerNetEvent::_OnCS2GSCountryWarKillPlayer( NetClient* pNetClient, CS2GSCountryWarKillPlayer* pMessage )
{
    theGameCountryManager.ProcessWarKillPlayer( pMessage->uchKillCountryID, pMessage->nKillCount, pMessage->uchDeathCountryID, pMessage->nDeathCount );
}
void CenterServerNetEvent::_OnCS2GSCountryWeakStrong( NetClient* pNetClient, CS2GSCountryWeakStrongthChange* pMessage )
{
	//����ǿ����
	theGameCountryManager.SetWeakCountry( pMessage->uchWeakCountryID );
	theGameCountryManager.SetStrongCountry( pMessage->uchStrongCountryID );
	//֪ͨ�ͻ��� ǿ�����ı仯 ����������������Ҷ���Ҫ����
	if(pMessage->uchWeakCountryID != CountryDefine::Country_Init)
	{
		MsgCountryTellWeak xTell;
		xTell.uchWeakCountryID = theGameCountryManager.GetWeakCountry(); 
		GettheServer().SendMsgToWorld(&xTell,true);
	}
	if(pMessage->uchStrongCountryID != CountryDefine::Country_Init)
	{
		MsgCountryTellStrong xTell;
		xTell.uchStrongCountryID = theGameCountryManager.GetStrongCountry(); 
		GettheServer().SendMsgToWorld(&xTell,true);
	}
	//֪ͨ������ҷ���BUFF�ı����Ϣ ��ǰGameServer���������
	MsgCountryBuffChange msg;
	GettheServer().SendMsgToWorld(&msg,false);
}
void CenterServerNetEvent::_OnCS2GSAddCountryOfficial( NetClient* pNetClient, CS2GSAddCountryOfficial* pMessage )
{
	//��ӹ�Ա
	GamePlayer * pPlayer = theRunTimeData.GetGamePlayerByDBID(pMessage->nPlayerID);
	if(pPlayer)
	{
		GS2CSAddCountryOfficial msg;
		msg.uchCountryID = pMessage->uchCountryID;
		msg.position = pMessage->uchPosition;
		HelperFunc::SafeNCpy( msg.szName, pPlayer->GetCharName(), sizeof( msg.szName ) );
		msg.nPlayerID = pMessage->nPlayerID;
		msg.sexID = pPlayer->GetCharInfo().baseinfo.aptotic.ucSex;
		msg.faceID = pPlayer->GetCharInfo().visual.faceId;
		msg.headerID = pPlayer->GetCharInfo().visual.hairId;
		msg.professionID = pPlayer->GetCharInfo().baseinfo.aptotic.usProfession;
		GettheServer().SendMsgToCenterServer( &msg );
	}
}
void CenterServerNetEvent::_OnCS2GSCountryOfficialReward( NetClient* pNetClient, CS2GSCountryOfficialReward* pMessage )
{
	//��ȡ�����ļ� ���ҷ��͵�center
	//zhuxincong �������Ϊ��Ա����Ľ���
	int nItemID = theCountryReward.GetItemID(30,pMessage->uchPosition);
	ItemDefine::SItemCommon* pItemCommon = GettheItemDetail().GetItemByID(nItemID);
	if (pItemCommon == NULL)
	{
		return;
	}
	//zhuxincong �����Ǹ�����ƷID ������Ʒ
	SCharItem item;
	if( !theRunTimeData.CreateItem( NULL, nItemID, 1, HelperFunc::CreateID(), item ) )
	{
		return;
	}
	GS2CSCountryBattleReward xResult;
	memcpy(&xResult.CItem,&item,sizeof(SCharItem));
	xResult.nLevel = 30;
	xResult.nPlayerID = pMessage->nPlayerID;
	xResult.nGuidID = 0;
	xResult.oldID = xResult.newID;
	xResult.newID = pMessage->nPlayerID;
	xResult.nPosition = pMessage->uchPosition;
	HelperFunc::SafeNCpy(xResult.szName,pMessage->szName, sizeof( xResult.szName) );
	GettheServer().SendMsgToCenterServer( &xResult );
}