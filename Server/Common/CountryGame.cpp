#include "CountryManager.h"
#include "CountryConfig.h"
#include "CampBattleMessage.h"
#include "GameServer.h"
#include "ShareData.h"
#include "GamePlayer.h"
#include "PlayerMessageHandle.h"

template<>
void GameCountry::InitCountryInfo()
{
    // do nothing...
    // 初始化边境战斗记录
    int nSize = theCountryConfig.GetBordersFightCount();
    if ( nSize <= 0 )
    { nSize = CountryDefine::MaxBordersFightCount; }

    vecBordersFight.resize( nSize );
}


template<>
void GameCountry::SendBordersFightMessage( unsigned short ustMapID, int nPosX, int nPosY )
{
    // 全国公告
    GS2CSCountryBordersFight xFight;
    xFight.uchCountryID = GetID();
    xFight.ustMapID     = ustMapID;
    xFight.nPosX        = nPosX;
    xFight.nPosY        = nPosY;
    GettheServer().SendMsgToCenterServer( &xFight );
}


template<>
void GameCountry::SendUpdateCountryDataMessage( unsigned char uchType, __int64 n64Value )
{
    switch ( uchType )
    {
    case CountryDefine::CancelKingGuild:    // 清除国王帮
        {
            for ( int i = CountryDefine::Position_None + 1; i < CountryDefine::Position_Max; ++i )
            {
                ProcessCountryOfficialChange( i, CountryDefine::NoneID, "" ,0,0,0,0);
            }

            GameGuild* pGuild = theGameGuildManager.GetGuild( GetKingGuild() );
            if ( pGuild != NULL )
            {
                pGuild->ClearCountryTitle();
            }

            SetKingGuild( n64Value );
        }
        break;
    case CountryDefine::UpdateKingGuild:    // 更新国王帮
        {
            GameGuild* pGuild = theGameGuildManager.GetGuild( GetKingGuild() );
            if ( pGuild != NULL )
            {
                pGuild->SetCountryTitle( CountryDefine::Title_KingGuard, CountryDefine::Title_King );
            }
        }
        break;
    case CountryDefine::CancelDragonGuild:  // 清除青龙帮
        {
            GameGuild* pGuild = theGameGuildManager.GetGuild( GetDragonGuild() );
            if ( pGuild != NULL )
            {
                // 清除国家称号
                pGuild->ClearCountryTitle();

                GamePlayer* pPlayer = theRunTimeData.GetGamePlayerByDBID( pGuild->GetMasterID() );
                if ( pPlayer != NULL )
                {
                    SMountItem* pMount = pPlayer->GetCountryMount();
                    if ( pMount != NULL )
                    {
                        pPlayer->RemoveMountByGuid( pMount->GetMountGuid() );
                    }
                }
            }

            SetDragonGuild( n64Value );
        }
        break;
    case CountryDefine::UpdateDragonGuild:  // 更新青龙帮
        {
            GameGuild* pGuild = theGameGuildManager.GetGuild( GetDragonGuild() );
            if ( pGuild != NULL )
            {
                // 加上国家称号
                pGuild->SetCountryTitle( CountryDefine::Title_DragonGuard, CountryDefine::Title_Dragon );
            }
        }
        break;
    case CountryDefine::CancelRosefinchGuild:  // 清除朱雀帮
        {
            GameGuild* pGuild = theGameGuildManager.GetGuild( GetRosefinchGuild() );
            if ( pGuild != NULL )
            {
                // 清除国家称号
                pGuild->ClearCountryTitle();

                GamePlayer* pPlayer = GameGuild::GetPlayer( pGuild->GetMasterID() );
                if ( pPlayer != NULL )
                {
                    SMountItem* pMount = pPlayer->GetCountryMount();
                    if ( pMount != NULL )
                    {
                        pPlayer->RemoveMountByGuid( pMount->GetMountGuid() );
                    }
                }
            }

            SetRosefinchGuild( n64Value );
        }
        break;
    case CountryDefine::UpdateRosefinchGuild:   // 更新朱雀帮
        {
            GameGuild* pGuild = theGameGuildManager.GetGuild( GetDragonGuild() );
            if ( pGuild != NULL )
            {
                // 加上国家称号
                pGuild->SetCountryTitle( CountryDefine::Title_RosefinchGuard, CountryDefine::Title_Rosefinch );
            }
        }
        break;

	case CountryDefine::UpdateTribute:
		SetTribute(n64Value);
		break;

	case CountryDefine::UpdateMoney:
		SetMoney(n64Value);
		break;
		}

	MsgUpdateCountryDate msg;
	msg.nValue = n64Value;
	msg.chType = uchType;
	GettheServer().SendMsgToCountry( &msg, GetID(), false );
}

template<>
void GameCountry::SendNoticeChangeMessage( unsigned int nPlayerID )
{
    GamePlayer* pPlayer = theRunTimeData.GetGamePlayerByDBID( nPlayerID );
    if ( pPlayer != NULL )      // 通知客户端修改成功
    {
        MsgCountryNoticeChangeAck xAck;
        pPlayer->SendMessageToClient( &xAck );
    }
}
template<>
void GameCountry::SendCountryInfoChangeMessage(const char * szInfo,__int64 Time,int Value)
{
	MsgAddCountryInfoReq msg;
	msg.Time = Time;
	msg.Value = Value;
	strncpy_s( msg.szNotice, sizeof( msg.szNotice )-1, szInfo, sizeof( msg.szNotice ) - 1 ); 
	//发送给国家所有人
	GettheServer().SendMsgToCountry( &msg, GetID(), false );
}
template<>
void GameCountry::ProcessCountryOfficialChange( unsigned char uchPosition, unsigned int nPlayerID, const char* szName,uint8 sexID,uint16 faceID,uint16 headerID,uint16 professionID ,SCharItem* pItem)
{
    OfficialInfo* pOfficial = GetOfficial( uchPosition );
    if ( pOfficial == NULL )
    { return; }
    int nRecallPlayerID = pOfficial->GetID();

    GamePlayer* pRecallPlayer = theRunTimeData.GetGamePlayerByDBID( nRecallPlayerID );
	GamePlayer* pAppointPlayer = theRunTimeData.GetGamePlayerByDBID( nPlayerID );

	if(pAppointPlayer)
		AppointOfficial( uchPosition, nPlayerID, szName,pAppointPlayer->GetCharInfo().baseinfo.aptotic.ucSex,pAppointPlayer->GetCharInfo().visual.faceId
		,pAppointPlayer->GetCharInfo().visual.hairId,pAppointPlayer->GetCharInfo().baseinfo.aptotic.usProfession);// 设置职位
	else
		AppointOfficial(uchPosition, nPlayerID, szName,sexID,faceID,headerID,professionID);

    
    if ( pRecallPlayer != NULL && nRecallPlayerID != nPlayerID)
    {
        MsgCountryTellAppoint xTell;
        xTell.uchType = MsgCountryTellAppoint::ECD_Recall;
        xTell.uchPosition = uchPosition;
        pRecallPlayer->SendMessageToClient( &xTell );

        // 设置国家称号
        pRecallPlayer->InitCountryTitle( true );

		pRecallPlayer->SetPlayerCountryPosition(CountryDefine::Position_None);
		theCountryReward.BSubItemAndMount(uchPosition,nRecallPlayerID);		

        // 如果有国家坐骑, 删除其坐骑
        SMountItem* pMount = pRecallPlayer->GetCountryMount();
        if ( pMount != NULL )
        {
            pRecallPlayer->RemoveMountByGuid( pMount->GetMountGuid() );
        }
    }

    
    if ( pAppointPlayer != NULL)
    {
        MsgCountryTellAppoint xTell;
        xTell.uchType = MsgCountryTellAppoint::ECD_Appoint;
        xTell.uchPosition = uchPosition;
        pAppointPlayer->SendMessageToClient( &xTell );

        // 设置国家称号
        pAppointPlayer->InitCountryTitle( true );

		pAppointPlayer->SetPlayerCountryPosition(uchPosition);
		//设置获得奖励
		//theCountryReward.SendCountryReward(pAppointPlayer->GetCharName(),pAppointPlayer->GetID(),pAppointPlayer->GetLevel(),uchPosition);
    }
}

template<>  
void GameCountry::ProcessCountryBattleResult( unsigned char uchBattleType, unsigned char uchWinType, unsigned int nGuildID,unsigned int nLoseGuildID,SCharItem* pItem,unsigned int nCampBattle  )
{
    MsgTellCountryBattleResult xResult;
    xResult.uchBattleType = uchBattleType;
    xResult.uchWinType    = uchWinType;
    xResult.nGuildID      = nGuildID;
    //GettheServer().SendMsgToCountry( &xResult, GetID(), false );
	GettheServer().SendMsgToWorld(&xResult,false);
}

template<>
void GameCountry::SendCountryDataChangeReq( unsigned char uchChangeType, unsigned char uchOperateType, unsigned int nValue )
{
    GS2CSCountryDateChangeReq xReq;
    xReq.uchCountryID   = GetID();
    xReq.uchChangeType  = uchChangeType;
    xReq.uchOperateType = uchOperateType;
    xReq.nValue         = nValue;
    GettheServer().SendMsgToCenterServer( &xReq );
}