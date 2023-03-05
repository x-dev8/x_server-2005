#include "CountryMessage.h"
#include "CountryManager.h"
#include "NetEvent.h"
#include "GameServerManager.h"
#include "RelationManager.h"
#include "CountryConfig.h"
#include "ClientPeerManager.h"
#include "GuildManager.h"
#include "CountryReward.h"
#include "XmlStringLanguage.h"
#include "MailManagerMain.h"
long NetEvent::OnProcessCountryMessage(TcpServer* pTcpServer, NetClient* pNetClient,unsigned long msgType, Msg* pMessage )
{
    MESSAGE_MAPPING_BEGIN
        MESSAGE_HANDLE( GS2CS_COUNTRYNOTICECHANGEREQ, GS2CSCountryNoticeChangeReq, _OnGS2CSCountryNoticeChangeReq );
        MESSAGE_HANDLE( GS2CS_COUNTRYQUESTSTATUSCHANGEREQ, GS2CSCountryQuestStatusChangeReq, _OnGS2CSCountryQuestStatusChangeReq );
        MESSAGE_HANDLE( GS2CS_COUNTRYOFFICIALAPPOINTREQ, GS2CSCountryOfficialAppointReq, _OnGS2CSCountryOfficialAppointReq );
        MESSAGE_HANDLE( GS2CS_COUNTRYOFFICIALRECALLREQ, GS2CSCountryOfficialRecallReq, _OnGS2CSCountryOfficialRecallReq );
        MESSAGE_HANDLE( GS2CS_COUNTRYBATTLERESULT, GS2CSCountryBattleResult, _OnGS2CSCountryBattleResult );
		MESSAGE_HANDLE( CS2CS_GS2CSCountryBattleReward,GS2CSCountryBattleReward,_OnGS2CSCountryBattleReward);
        MESSAGE_HANDLE( GS2CS_COUNTRYREQUESTRAISEREQ, GS2CSCountryRequestRaiseReq, _OnGS2CSCountryRequestRaiseReq );
        MESSAGE_HANDLE( GS2CS_COUNTRYMONEYRAISEED, GS2CSCountryMoneyRaiseed, _OnGS2CSCountryMoneyRaiseed );
        MESSAGE_HANDLE( GS2CS_COUNTRYBORDERSFIHGT, GS2CSCountryBordersFight, _OnGS2CSCountryBordersFight );
        MESSAGE_HANDLE( GS2CS_COUNTRYOPERATETOPLAYERREQ, GS2CSCountryOperateToPlayerReq, _OnGS2CSCountryOperateToPlayerReq );
        MESSAGE_HANDLE( GS2CS_COUNTRYOPERATETOPLAYERACK, GS2CSCountryOperateToPlayerAck, _OnGS2CSCountryOperateToPlayerAck );
        MESSAGE_HANDLE( GS2CS_COUNTRYCONVENEREQ, GS2CSCountryConveneReq, _OnGS2CSCountryConveneReq );
        MESSAGE_HANDLE( GS2CS_COUNTRYSETOFFICIAL, GS2CSCountrySetOfficial, _OnGS2CSCountrySetOfficial );
        MESSAGE_HANDLE( GS2CS_COUNTRYCHANGERESULT, GS2CSCountryChangeResult, _OnGS2CSCountryChangeResult );
        MESSAGE_HANDLE( GS2CS_COUNTRYDATACHANGEREQ, GS2CSCountryDateChangeReq, _OnGS2CSCountryDateChangeReq );
        MESSAGE_HANDLE( GS2CS_CHANGECOUNTRYNAMEREQ, GS2CSChangeCountryNameReq, _OnGS2CSChangeCountryNameReq );
        MESSAGE_HANDLE( GS2CS_COUNTRYWARKILLPLAYER, GS2CSCountryWarKillPlayer, _OnGS2CSCountryWarKillPlayer );
        MESSAGE_HANDLE( GS2CS_COUNTRYWARSTATUSCHANGE, GS2CSCountryWarStatusChange, _OnGS2CSCountryWarStatusChange );
		MESSAGE_HANDLE( GS2CS_COUNTRYPLAYERCHANGE, GS2CSCountryPlayerChange, _OnGS2CSCountryPlayerChange );
        MESSAGE_HANDLE( GS2CS_ADDCOUNTRYOFFICIAL, GS2CSAddCountryOfficial, _OnGS2CSAddCountryOfficial );
        MESSAGE_HANDLE( GS2CS_RAISECOUNTRYPLAYERITEM, GS2CSRaiseCountryPlayerItem, _OnGS2CSRaiseCountryPlayerItem );

		MESSAGE_HANDLE( GS2CS_DELCOUNTRYOFFICIALREQ, GS2CSDelCountryOfficialReq, _OnGS2CSDelCountryOfficialReq );

		MESSAGE_HANDLE( GS2CS_ADDCOUNTRYINFOREQ, GS2CSAddCountryInfoReq, _OnGS2CSAddCountryInfoReq );
		
    MESSAGE_MAPPING_END

    return ER_Success;
}

void NetEvent::_OnGS2CSCountryNoticeChangeReq( NetClient* pNetClient, GS2CSCountryNoticeChangeReq* pMessage )
{
    CenterCountry* pCountry = theCenterCountryManager.GetCountry( pMessage->uchCountryID );
    if ( pCountry == NULL )
    { return; }

    if ( !pCountry->IsHaveRight( CountryDefine::Right_Placard, pMessage->nPlayerID ) )
    { return; }

    if ( pCountry->GetPlacardCount() >= theCountryConfig.GetPlacardCount() )
    { return; }

    if ( pCountry->GetMoney() < theCountryConfig.GetPlacardCost() )
    { return; }

    // 扣钱
    pCountry->OperateCountryMoney( CountryDefine::OperateSub, theCountryConfig.GetPlacardCost() );
    // 改变国家公告
    pCountry->ProcessNoticeChange( pMessage->nPlayerID, pMessage->szNotice );
	//更新国家的实力
	theCenterCountryManager.HandleAllCountryStrength();//更新国家实力 如果变化会发生命令
}
void NetEvent::_OnGS2CSAddCountryInfoReq( NetClient* pNetClient, GS2CSAddCountryInfoReq* pMessage )
{
	CenterCountry* pCountry = theCenterCountryManager.GetCountry( pMessage->uchCountryID );
    if ( pCountry == NULL )
    { return; }
	if(pMessage->Time == 0)
	{
		time_t now;
		time(&now);
		pMessage->Time = now;
	}
	pCountry->AddCountryInfo(pMessage->szNotice,pMessage->Time,pMessage->Value);
}
void NetEvent::_OnGS2CSCountryQuestStatusChangeReq( NetClient* pNetClient, GS2CSCountryQuestStatusChangeReq* pMessage )
{
    CenterCountry* pCountry = theCenterCountryManager.GetCountry( pMessage->uchCountryID );
    if ( pCountry == NULL )
    { return; }

    unsigned int nRight = CountryDefine::GetQuestRightByType( pMessage->uchQuestType );
    if ( nRight == CountryDefine::Right_None )
    { return; }

    if ( !pCountry->IsHaveRight( nRight, pMessage->nPlayerID ) )
    { return; }

    OperateTime* pOperateTime = pCountry->GetQuestOperate( pMessage->uchQuestType );
    if ( pOperateTime == NULL )
    { return; }

    const CountryConfig::QuestSetting* pSetting = theCountryConfig.GetQuestSetting( pMessage->uchQuestType );
    if ( pSetting == NULL )
    { return; }

    if ( pOperateTime->GetCount() >= pSetting->GetCount() )
    { return; }

    if ( pCountry->GetMoney() < pSetting->GetCostMoney() )
    { return; }

    pCountry->OperateCountryMoney( CountryDefine::OperateSub, pSetting->GetCostMoney() );

    pOperateTime->SetCount( pOperateTime->GetCount() + 1 );
    pOperateTime->SetStartTime( TimeEx::GetCurrentTime().GetTime() );

    // 更新国家实力
    const CountryConfig::StrengthSetting& xSetting = theCountryConfig.GetStrengthSetting();
    switch ( pMessage->uchQuestType )
    {
    case CountryDefine::QuestType_General:
		//国力增加 但是不发生命令 下面一起发送
		pCountry->SetNowStrength(pCountry->GetNowStrength() +  xSetting.GetReleaseModulus());
        //pCountry->OperateCountryStrength( CountryDefine::OperateAdd, xSetting.GetReleaseModulus() );
        break;
    default:
        break;
    }

	//记录国家发布的任务总次数
	pCountry->SetAddQuestCount(pMessage->uchQuestType);//添加任务执行的次数
	//重新计算所有国家的实力 如果有变化发布到客户端去
	theCenterCountryManager.HandleAllCountryStrength();

    // 消息同步给所有服务器
    CS2GSCountryQuestStatusChangeAck xAck;
    xAck.uchCountryID = pMessage->uchCountryID;
    xAck.uchQuestType = pMessage->uchQuestType;
    xAck.nPlayerID    = pMessage->nPlayerID;
    theGameServerManager.SendMessageToGameServers( &xAck );
}

void NetEvent::_OnGS2CSCountryOfficialAppointReq( NetClient* pNetClient, GS2CSCountryOfficialAppointReq* pMessage )
{
    CenterCountry* pCountry = theCenterCountryManager.GetCountry( pMessage->uchCountryID );
    if ( pCountry == NULL )
    { return; }

    unsigned int nRight = CountryDefine::GetAppointRightByPosition( pMessage->uchPosition );
    if ( nRight == CountryDefine::Right_None )
    { return; }

    if ( !pCountry->IsHaveRight( nRight, pMessage->nOfficialID ) )
    { return; }

    uint8 uchPositon = pCountry->GetPosition( pMessage->nPlayerID );
    if ( uchPositon != CountryDefine::Position_None )
    { return; }

	CenterRelation * pTargetRelation = theCenterRelationManager.GetPlayerRelation( pMessage->nPlayerID );
	if ( pTargetRelation == NULL || !pTargetRelation->GetOnLine() )
	{ return; }

    // 不能重复任命
    OfficialInfo* pOfficial = pCountry->GetOfficial( pMessage->uchPosition );
    if ( pOfficial == NULL || pOfficial->GetID() == pMessage->nPlayerID )
    { return; }

    // 处理国家职位改变
    pCountry->ProcessCountryOfficialChange( pMessage->uchPosition, pMessage->nPlayerID, pTargetRelation->GetName(),pMessage->sexID,pMessage->faceID,pMessage->headerID,pMessage->professionID);

    // 通知操作者
    MsgCountryOfficialAppointAck xAck;
    xAck.uchResult   = MsgCountryOfficialAppointAck::ECD_Success;
    xAck.uchPosition = pMessage->uchPosition;
    xAck.nPlayerID   = pMessage->nPlayerID;
    theGameServerManager.SendMsgToSingleRemote( InvalidLogicNumber, &xAck, pMessage->nOfficialID );
}

void NetEvent::_OnGS2CSCountryOfficialRecallReq( NetClient* pNetClient, GS2CSCountryOfficialRecallReq* pMessage )
{
    CenterCountry* pCountry = theCenterCountryManager.GetCountry( pMessage->uchCountryID );
    if ( pCountry == NULL )
    { return; }

    unsigned int nRight = CountryDefine::GetAppointRightByPosition( pMessage->uchPosition );
    if ( nRight == CountryDefine::Right_None )
    { return; }

    if ( !pCountry->IsHaveRight( nRight, pMessage->nOfficialID ) )
    { return; }

    OfficialInfo* pOfficial = pCountry->GetOfficial( pMessage->uchPosition );
    if ( pOfficial == NULL || pOfficial->GetID() == CountryDefine::NoneID )
    { return; }

    // 处理国家职位改变
    pCountry->ProcessCountryOfficialChange( pMessage->uchPosition, CountryDefine::NoneID, "",0,0,0 ,0);

    // 通知操作者
    MsgCountryOfficialRecallAck xAck;
    xAck.uchResult   = MsgCountryOfficialRecallAck::ECD_Success;
    xAck.uchPosition = pMessage->uchPosition;
    theGameServerManager.SendMsgToSingleRemote( InvalidLogicNumber, &xAck, pMessage->nOfficialID );
}

void NetEvent::_OnGS2CSCountryBattleResult( NetClient* pNetClient, GS2CSCountryBattleResult* pMessage )
{
    CenterCountry* pCountry = theCenterCountryManager.GetCountry( pMessage->uchCountryID );
    if ( pCountry == NULL )
    { return; }

    pCountry->ProcessCountryBattleResult( pMessage->uchBattleType, pMessage->uchWinType, pMessage->nGuildID,pMessage->nLoseGuildID ,NULL,pMessage->nCampBattle);

}

void NetEvent::_OnGS2CSCountryBattleReward( NetClient* pNetClient, GS2CSCountryBattleReward* pMessage )
{
	if (pMessage == NULL)
	{
		return;
	}

	if (pMessage->nCampBattle == 1) //zhuxincong 国王帮卫冕
	{
		return;
	}
	
	theCountryReward.SendCountryReward(pMessage->szName,pMessage->nPlayerID,pMessage->nLevel,pMessage->nPosition,pMessage->CItem);
}


void NetEvent::_OnGS2CSCountryRequestRaiseReq( NetClient* pNetClient, GS2CSCountryRequestRaiseReq* pMessage )
{
    CenterCountry* pCountry = theCenterCountryManager.GetCountry( pMessage->uchCountryID );
    if ( pCountry == NULL )
    { return; }

    if ( !pCountry->IsHaveRight( CountryDefine::Right_Raise, pMessage->nPlayerID ) )
    { return; }

    if ( pCountry->GetRaiseCount() >= theCountryConfig.GetRaiseCount() )
    { return; }

    pCountry->SetRaiseCount( pCountry->GetRaiseCount() + 1 );
    pCountry->StartSaveTimer( HQ_TimeGetTime() );

    CS2GSCountryRequestRaiseAck xAck;
    xAck.uchCountryID = pMessage->uchCountryID;
    xAck.nPlayerID    = pMessage->nPlayerID;
    theGameServerManager.SendMessageToGameServers( &xAck );
}

void NetEvent::_OnGS2CSCountryMoneyRaiseed( NetClient* pNetClient, GS2CSCountryMoneyRaiseed* pMessage )
{
    CenterCountry* pCountry = theCenterCountryManager.GetCountry( pMessage->uchCountryID );
    if ( pCountry == NULL )
    { return; }

	if (pMessage->nType == 0)
	{
		/*int nCanAddMoney = theCountryConfig.GetMaxMoney() - pCountry->GetMoney();
		if ( pMessage->nMoney > nCanAddMoney )
		{ pMessage->nMoney = nCanAddMoney; }*/
		if ( pMessage->nMoney == 0 )
		{ return; }

		pCountry->OperateCountryMoney( CountryDefine::OperateAdd, pMessage->nMoney );

		theCenterCountryManager.HandleAllCountryStrength();//更新国家实力 如果变化会发生命令
	}
	else if (pMessage->nType == 1)
	{
		if (pMessage->OperateType == 3)
		{
			if (pMessage->nMoney > theCountryConfig.GetMaxTribute())
			{
				pMessage->nMoney = theCountryConfig.GetMaxTribute();
			}
			if (pMessage->nMoney < theCountryConfig.GetMinTribute())
			{
				pMessage->nMoney = theCountryConfig.GetMinTribute();
			}
			pCountry->OperateCountryTribute( CountryDefine::OperateSet, pMessage->nMoney );

			theCenterCountryManager.HandleAllCountryStrength();//更新国家实力 如果变化会发生命令
		}
		else
		{
			int nCanaddTribute = theCountryConfig.GetMaxTribute() - pCountry->GetTribute();
			if (pMessage->nMoney > nCanaddTribute)
			{
				pMessage->nMoney = nCanaddTribute;
			}
			if (pMessage->nMoney == theCountryConfig.GetMinTribute())
			{
				return;
			}
			pCountry->OperateCountryTribute( CountryDefine::OperateAdd, pMessage->nMoney );

			theCenterCountryManager.HandleAllCountryStrength();//更新国家实力 如果变化会发生命令
		}
	}   
}

void NetEvent::_OnGS2CSCountryBordersFight( NetClient* pNetClient, GS2CSCountryBordersFight* pMessage )
{
    CenterCountry* pCountry = theCenterCountryManager.GetCountry( pMessage->uchCountryID );
    if ( pCountry == NULL )
    { return; }

    pCountry->AddBordersFight( pMessage->ustMapID, pMessage->nPosX, pMessage->nPosY );

    // 通知给服务器
    CS2GSCountryBordersFight xFight;
    xFight.uchCountryID = pMessage->uchCountryID;
    xFight.ustMapID     = pMessage->ustMapID;
    xFight.nPosX        = pMessage->nPosX;
    xFight.nPosY        = pMessage->nPosY;
    theGameServerManager.SendMessageToGameServers( &xFight );
}

void NetEvent::_OnGS2CSCountryOperateToPlayerReq( NetClient* pNetClient, GS2CSCountryOperateToPlayerReq* pMessage )
{
    CenterCountry* pCountry = theCenterCountryManager.GetCountry( pMessage->uchCountryID );
    if ( pCountry == NULL )
    { return; }

    unsigned int nRight = CountryDefine::Right_None;
    int nCostMoney = 0;

    switch ( pMessage->uchOperate )
    {
    case MsgCountryOperateToPlayerReq::Operate_BanSpeak:
        {
            if ( pCountry->GetBanSpeakCount() >= theCountryConfig.GetBanSpeakCount() )
            { return; }

            nRight = CountryDefine::Right_BanSpeak;
            nCostMoney = theCountryConfig.GetBanSpeakCost();
        }
        break;
    case MsgCountryOperateToPlayerReq::Operate_Chain:
        {
            if ( pCountry->GetChainCount() >= theCountryConfig.GetChainCount() )
            { return; }

            nRight = CountryDefine::Right_Chain;
            nCostMoney = theCountryConfig.GetChainCost();
        }
        break;
    case MsgCountryOperateToPlayerReq::Operate_Remit:
        {
            if ( pCountry->GetRemitCount() >= theCountryConfig.GetRemitCount() )
            { return; }

            nRight = CountryDefine::Right_Remit;
            nCostMoney = theCountryConfig.GetRemitCost();
        }
        break;
    default:
        return;
    }

    if ( !pCountry->IsHaveRight( nRight, pMessage->nPlayerID ) )
    { return; }

    if ( pCountry->GetMoney() < nCostMoney )
    { return; }

    ClientPeer* pClient = theClientPeerManager.GetClientPeerByName( pMessage->szName );
    if ( pClient == NULL )
    {
        MsgCountryOperateToPlayerAck xAck;
        xAck.uchOperate = pMessage->uchOperate;
        xAck.uchResult  = MsgCountryOperateToPlayerAck::ECD_NotOnLine;
        theGameServerManager.SendMsgToSingleRemote( CountryDefine::ErrorID, &xAck, pMessage->nPlayerID );
        return;
    }

    GameServerPeer* pGameServer = theGameServerManager.GetGameServerPeer( pClient->GetServerInfo().nServerId );
    if( pGameServer == NULL )
    { return; }

    CS2GSCountryOperateToPlayerReq xReq;
    xReq.uchCountryID = pMessage->uchCountryID;
    xReq.uchOperate   = pMessage->uchOperate;
    xReq.nOfficialID  = pMessage->nPlayerID;
    xReq.nPlayerID    = pClient->GetCharDbId();
    pGameServer->Send( &xReq );
}

void NetEvent::_OnGS2CSCountryOperateToPlayerAck( NetClient* pNetClient, GS2CSCountryOperateToPlayerAck* pMessage )
{
    CenterCountry* pCountry = theCenterCountryManager.GetCountry( pMessage->uchCountryID );
    if ( pCountry == NULL )
    { return; }

    switch ( pMessage->uchOperate )
    {
    case MsgCountryOperateToPlayerReq::Operate_BanSpeak:
        {
            pCountry->SetBanSpeakCount( pCountry->GetBanSpeakCount() + 1 );
            pCountry->OperateCountryMoney( CountryDefine::OperateSub, theCountryConfig.GetBanSpeakCost() );
        }
        break;
    case MsgCountryOperateToPlayerReq::Operate_Chain:
        {
            pCountry->SetChainCount( pCountry->GetChainCount() + 1 );
            pCountry->OperateCountryMoney( CountryDefine::OperateSub, theCountryConfig.GetChainCost() );
        }
        break;
    case MsgCountryOperateToPlayerReq::Operate_Remit:
        {
            pCountry->SetRemitCount( pCountry->GetRemitCount() + 1 );
            pCountry->OperateCountryMoney( CountryDefine::OperateSub, theCountryConfig.GetRemitCost() );
        }
        break;
    default:
        return;
    }

	theCenterCountryManager.HandleAllCountryStrength();//更新国家实力 如果变化会发生命令

    // 同步给所有服务器
    CS2GSCountryOperateToPlayerAck xAck;
    xAck.uchCountryID = pMessage->uchCountryID;
    xAck.uchOperate   = pMessage->uchOperate;
    xAck.nOfficialID  = pMessage->nOfficialID;
    theGameServerManager.SendMessageToGameServers( &xAck );
}

void NetEvent::_OnGS2CSCountryConveneReq( NetClient* pNetClient, GS2CSCountryConveneReq* pMessage )
{
    CenterCountry* pCountry = theCenterCountryManager.GetCountry( pMessage->uchCountryID );
    if ( pCountry == NULL )
    { return; }

    if ( !pCountry->IsHaveRight( CountryDefine::Right_Convene, pMessage->nOfficialID ) )
    { return; }

    if ( pCountry->GetConveneCount() >= theCountryConfig.GetConveneCount() )
    { return; }

    if ( pCountry->GetMoney() < theCountryConfig.GetConveneCost() )
    { return; }

    pCountry->OperateCountryMoney( CountryDefine::OperateSub, theCountryConfig.GetConveneCost() );
    pCountry->SetConveneCount( pCountry->GetConveneCount() + 1 );

	theCenterCountryManager.HandleAllCountryStrength();//更新国家实力 如果变化会发生命令

    CS2GSCountryConveneReq xReq;
    xReq.uchCountryID = pMessage->uchCountryID;
    xReq.nOfficialID  = pMessage->nOfficialID;
    xReq.ustLevel     = pMessage->ustLevel;
    xReq.nMapID       = pMessage->nMapID;
    xReq.fX           = pMessage->fX;
    xReq.fY           = pMessage->fY;
    theGameServerManager.SendMessageToGameServers( &xReq );
}

void NetEvent::_OnGS2CSCountrySetOfficial( NetClient* pNetClient, GS2CSCountrySetOfficial* pMessage )
{
    CenterCountry* pCountry = theCenterCountryManager.GetCountry( pMessage->uchCountryID );
    if ( pCountry == NULL )
    { return; }

    if ( pMessage->uchPosition >= CountryDefine::Position_Max )
    { return; }

	//获取指定名称的玩家

    pCountry->AppointOfficial( pMessage->uchPosition, pMessage->nPlayerID, pMessage->szName,pMessage->sexID,pMessage->faceID,pMessage->headerID,pMessage->professionID);

    pCountry->SetKingGuild( pMessage->nGuildID );
    
    CS2GSCountrySetOfficial xSet;
    xSet.uchCountryID = pMessage->uchCountryID;
    xSet.uchPosition  = pMessage->uchPosition;
    xSet.nGuildID     = pMessage->nGuildID;
    xSet.nPlayerID    = pMessage->nPlayerID;

	xSet.sexID = pMessage->sexID;
	xSet.faceID = pMessage->faceID;
	xSet.headerID = pMessage->headerID;
	xSet.professionID = pMessage->professionID;

    strncpy_s( xSet.szName, sizeof( xSet.szName ), pMessage->szName, sizeof( xSet.szName ) - 1 );
    theGameServerManager.SendMessageToGameServers( &xSet );
}

void NetEvent::_OnGS2CSCountryChangeResult( NetClient* pNetClient, GS2CSCountryChangeResult* pMessage )
{
    // 更新关系列表
    CenterRelation* pRelation = theCenterRelationManager.GetPlayerRelation( pMessage->nPlayerID );
    if ( pRelation != NULL )
    {
        pRelation->UpdateRelationAttribute( RelationDefine::UpdateCountry, pMessage->uchCountryID );
    }

    ClientPeer* pClientPeer = theClientPeerManager.GetClientPeerByDBId( pMessage->nPlayerID );
    if ( pClientPeer != NULL )
    { 
        pClientPeer->SetCountry( pMessage->uchCountryID );
    }
}

void NetEvent::_OnGS2CSCountryDateChangeReq( NetClient* pNetClient, GS2CSCountryDateChangeReq* pMessage )
{
    CenterCountry* pCountry = theCenterCountryManager.GetCountry( pMessage->uchCountryID );
    if ( pCountry == NULL )
    { return; }

    switch ( pMessage->uchChangeType )
    {
    case CountryDefine::UpdateNowStrength:
		//完成出国任务 添加国家实力
		pCountry->SetAddDoneQuestStrength(pMessage->nValue);
		theCenterCountryManager.HandleAllCountryStrength();
        //pCountry->OperateCountryStrength( pMessage->uchOperateType, pMessage->nValue );
        break;
    case CountryDefine::UpdateChangeName:
        pCountry->UpdateCountryData( CountryDefine::UpdateChangeName, 0 );
        break;
    default:
        break;
    }

}

void NetEvent::_OnGS2CSChangeCountryNameReq( NetClient* pNetClient, GS2CSChangeCountryNameReq* pMessage )
{
    CenterCountry* pCountry = theCenterCountryManager.GetCountry( pMessage->uchCountryID );
    if ( pCountry == NULL )
    { return; }

    if ( !pCountry->IsHaveRight( CountryDefine::Right_ChangeName, pMessage->nPlayerID ) )
    { return; }

    if ( pCountry->GetChangeName() )
    { return; }

    pCountry->SetName( pMessage->szName );
    pCountry->SetChangeName( true );

    // 通知GameServer
    CS2GSCountryNameChange xChange;
    xChange.uchCountryID = pMessage->uchCountryID;
    xChange.nPlayerID    = pMessage->nPlayerID;
    HelperFunc::SafeNCpy( xChange.szPlayer, pMessage->szPlayer, sizeof( xChange.szPlayer ) );
    HelperFunc::SafeNCpy( xChange.szName, pMessage->szName, sizeof( xChange.szName ) );
    theGameServerManager.SendMessageToGameServers( &xChange );
}


void NetEvent::_OnGS2CSCountryWarKillPlayer( NetClient* pNetClient, GS2CSCountryWarKillPlayer* pMessage )
{
    theCenterCountryManager.ProcessWarKillPlayer( pMessage->uchKillCountryID, 1, pMessage->uchDeathCountryID, 1 );
}

void NetEvent::_OnGS2CSCountryWarStatusChange( NetClient* pNetClient, GS2CSCountryWarStatusChange* pMessage )
{
    theCenterCountryManager.ProcessWarStatusChange( pMessage->uchStatus );
    switch ( pMessage->uchStatus )
    {
    case CountryDefine::BattleStatusEnd:
        theCenterCountryManager.ProcessCountryWarFightSort();
        break;
    }
}
void NetEvent::_OnGS2CSCountryPlayerChange( NetClient* pNetClient, GS2CSCountryPlayerChange* pMessage )
{
	//指定国家人数减少
	CenterCountry * pOldCountry =  theCenterCountryManager.GetCountry(pMessage->oldCountryID);
	if(pOldCountry)
	{
		unsigned int Sum = pOldCountry->GetCountryPlayerSum();
		if(Sum == 0)
			return;
		--Sum;
		pOldCountry->SetCountryPlayerSum(Sum);
	}

	CenterCountry * pNowCountry =  theCenterCountryManager.GetCountry(pMessage->nowCountryID);
	if(pNowCountry)
	{
		unsigned int Sum = pNowCountry->GetCountryPlayerSum();
		if(Sum == 0)
			return;
		++Sum;
		pNowCountry->SetCountryPlayerSum(Sum);
	}

	//人数变化后 我们开始计算国家的实力变化
	theCenterCountryManager.HandleAllCountryStrength();//发生国家实力的改变
}
void NetEvent::_OnGS2CSAddCountryOfficial( NetClient* pNetClient, GS2CSAddCountryOfficial* pMessage )
{
	//通知Center 给指定国家添加官员
	CenterCountry * pNowCountry =  theCenterCountryManager.GetCountry(pMessage->uchCountryID);
	if(pNowCountry)
	{
		pNowCountry->ProcessCountryOfficialChange(pMessage->position,pMessage->nPlayerID,pMessage->szName,pMessage->sexID,pMessage->faceID,pMessage->headerID,pMessage->professionID);
	}
}
void NetEvent::_OnGS2CSRaiseCountryPlayerItem( NetClient* pNetClient, GS2CSRaiseCountryPlayerItem* pMessage )
{
	//玩家接收邮件
	GS2CSSendMailReq xReq;
	xReq.charDbId = RelationDefine::InitID;

	xReq.mail.type  = SMail::EMT_System;
	xReq.mail.state = SMail::EMS_NotOpen;
	xReq.mail.sendTime = TimeEx::GetNowTime();        

	// 发信人
	xReq.mail.owners[EM_FromIndex].charDbId = 0;
	sprintf_s( xReq.mail.owners[EM_FromIndex].addressName, sizeof( xReq.mail.owners[EM_FromIndex] ) - 1, theXmlString.GetString( eText_MailSystemName ) );

	// 收件人	
	xReq.mail.owners[EM_ToIndex].charDbId = pMessage->PlayerID;
	HelperFunc::SafeNCpy( xReq.mail.owners[EM_ToIndex].addressName,pMessage->szName, sizeof( xReq.mail.owners[EM_ToIndex].addressName ) );
	
	//内容
	sprintf_s( xReq.mail.content, sizeof( xReq.mail.content ) - 1,theXmlString.GetString( etext_CountryRaiseContext ) );

	//标题
	sprintf_s( xReq.mail.title, sizeof( xReq.mail.title ) - 1, theXmlString.GetString( eText_CountryRaiseTitle ) );

	xReq.mail.accessory.type = 1;//2是坐骑,1是物品
	
	memcpy( &xReq.mail.accessory.content,  &pMessage->CItem, sizeof(SCharItem) ); 
	
	theMailSystemManager.OnGS2CSSendMailReq( &xReq, 0 );
}
void NetEvent::_OnGS2CSDelCountryOfficialReq( NetClient* pNetClient, GS2CSDelCountryOfficialReq* pMessage )
{
	//玩家辞去官职
	if(!pMessage) return;
	CenterCountry* pCountry = theCenterCountryManager.GetCountry( pMessage->uchCountryID );
    if ( pCountry == NULL )
    { return; }

    OfficialInfo* pOfficial = pCountry->GetOfficial( pMessage->uchPosition );
    if ( pOfficial == NULL || pOfficial->GetID() == CountryDefine::NoneID )
    { return; }

	unsigned int ID = pOfficial->GetID();
    // 处理国家职位改变
    pCountry->ProcessCountryOfficialChange( pMessage->uchPosition, CountryDefine::NoneID, "",0,0,0,0);

    // 通知操作者
    MsgCountryOfficialRecallAck xAck;
    xAck.uchResult   = MsgCountryOfficialRecallAck::ECD_DelSuccess;//辞职成功
    xAck.uchPosition = pMessage->uchPosition;
    theGameServerManager.SendMsgToSingleRemote( InvalidLogicNumber, &xAck, ID);
}