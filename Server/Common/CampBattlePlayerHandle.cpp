#include "GamePlayer.h"
#include "CampBattle.h"
#include "CampBattleControl.h"
#include "CampBattleMessage.h"
#include "CampBattleConfig.h"
#include "GlobalDBManager.h"

bool GamePlayer::ProcessCampBattleMsg( Msg* pMsg )
{
    DWORD dwType = pMsg->GetType();

    GAMESERVER_MESSAGE_MAPPING_BEGIN
        GAMESERVER_MESSAGE_HANDLE( MSG_CAMPBATTLEPLAYERREQ, OnMsgCampBattlePlayerReq );
        GAMESERVER_MESSAGE_HANDLE( MSG_LEAVECAMPBATTLEREQ, OnMsgLeaveCampBattleReq );
        GAMESERVER_MESSAGE_HANDLE( MSG_FLYTOCAMPBATTLEACK, OnMsgEnterCampBattleAck );
        GAMESERVER_MESSAGE_HANDLE( MSG_CAMPBATTLESIGNUPREQ, OnMsgCampBattleSignUpReq );
        GAMESERVER_MESSAGE_HANDLE( MSG_ENTERCAMPBATTLEREQ, OnMsgEnterCampBattleReq );
		 GAMESERVER_MESSAGE_HANDLE( MSG_GETGLOBALDBBATTLESUMREQ, OnMsgGetGlobalDBBattleSumReq );
    GAMESERVER_MESSAGE_MAPPING_END
    return false;
}

void GamePlayer::OnMsgCampBattlePlayerReq( Msg* pMsg )
{
    MsgCampBattlePlayerReq* pReq = static_cast< MsgCampBattlePlayerReq* >( pMsg );
    if ( pReq == NULL )
    { return; }

    CampBattle* pCampBattle = theCampBattleControl.GetCampBattle( GetFightCamp(), GetMapID() ,GetCountryId());
    if ( pCampBattle == NULL )
    { return; }

    unsigned char uchFightCamp = CampDefine::GetBaseFightCamp( GetFightCamp() );
    switch( pReq->uchReqType )
    {
    case MsgCampBattlePlayerReq::TypeSelfCamp:
        uchFightCamp = uchFightCamp;
        break;
    case MsgCampBattlePlayerReq::TypeTargetCamp:
        uchFightCamp = ( uchFightCamp == CampDefine::BaseCampRed ? CampDefine::BaseCampBlue : CampDefine::BaseCampRed );
        break;
    default:
        uchFightCamp = CampDefine::NoneCamp;
        break;
    }

    pCampBattle->SendBattlePlayerMessage( this, uchFightCamp );
}

void GamePlayer::OnMsgLeaveCampBattleReq( Msg* pMsg )
{
    MsgLeaveCampBattleReq* pReq = static_cast< MsgLeaveCampBattleReq* >( pMsg );
    if ( pReq == NULL )
    { return; }

    CampBattle* pCampBattle = theCampBattleControl.GetCampBattle( GetFightCamp(), GetMapID(),GetCountryId());
    if ( pCampBattle == NULL )
    { return; }

    MapConfig::MapData* pMapData = GetMapData();
    if ( pMapData == NULL )
    { return; }

    MapConfig::RelivePosition* pRelive = pMapData->GetRelivePositionByState( false );
    if ( pRelive == NULL )
    { return; }

	FlyToMapReq(pRelive->MapId,  pRelive->PositionX , pRelive->PositionY, pRelive->Direction);
	//FlyToMapAction( pRelive->MapId, FloatToTile( pRelive->PositionX ), FloatToTile( pRelive->PositionY ), pRelive->Direction );
}

void GamePlayer::OnMsgEnterCampBattleAck( Msg* pMsg )
{
    MsgFlyToCampBattleAck* pAck = static_cast< MsgFlyToCampBattleAck* >( pMsg );
    if ( pAck == NULL )
    { return; }

    MapConfig::MapData* pMapData = theMapConfig.GetMapDataById( pAck->nMapID );
    if ( pMapData == NULL )
    { return; }

    // 获得重生点, 传送至战场副本门口NPC处
    MapConfig::RelivePosition* pRelive = pMapData->GetRelivePositionByState( false );
    if ( pRelive == NULL )
    { return; }

    MapConfig::MapData* pReliveMapData = theMapConfig.GetMapDataById( pRelive->MapId );
    if ( pReliveMapData == NULL )
    { return; }

	if (pReliveMapData->Type != MapConfig::MT_NormalMap)
	{
		if (pReliveMapData->CountryID != GetCountry())// 不是本国家的不能飞
		{
			return ;
		}
	}    

    FlyToMapReq( pRelive->MapId, pRelive->PositionX, pRelive->PositionY, pRelive->Direction );
}

void GamePlayer::OnMsgCampBattleSignUpReq( Msg* pMsg )
{
    MsgCampBattleSignUpReq* pReq = static_cast< MsgCampBattleSignUpReq* >( pMsg );
    if ( pReq == NULL )
    { return; }

    CampBattleManager* pManager = theCampBattleControl.GetManagerBytypeAndCountry( pReq->uchBattleType,GetCountryId() );
    if ( pManager == NULL )
    { return; }

    pManager->SignUpCampBattle( this );
}

void GamePlayer::OnMsgEnterCampBattleReq( Msg* pMsg )
{
    MsgEnterCampBattleReq* pReq = static_cast< MsgEnterCampBattleReq* >( pMsg );
    if ( pReq == NULL )
    { return; }
		
	CampBattleManager* pManager = NULL;
	if(pReq->uchBattleType == CampDefine::BattleTypeGuild || pReq->uchBattleType == CampDefine::BattleTypeGuildUnion)
		pManager = theCampBattleControl.GetManagerBytypeAndCountry( pReq->uchBattleType,0);
	else
		pManager = theCampBattleControl.GetManagerBytypeAndCountry( pReq->uchBattleType,GetCountryId() );
    if ( pManager == NULL )
    { return; }

    pManager->EnterCampBattle( this );
}

///////////////////////////////////////////////////////////////////////////
void GamePlayer::KillCampBattleMonster( int nMonsterID )
{
    CampBattle* pCampBattle = theCampBattleControl.GetCampBattle( GetFightCamp(), GetMapID() ,GetCountryId());
    if ( pCampBattle == NULL )
    { return; }

    pCampBattle->KillCampBattleMonster( GetFightCamp(), GetDBCharacterID(), nMonsterID );
}

void GamePlayer::QueryCampBattleSignUp( unsigned char uchBattleType )
{
    CampBattleManager* pBattleManager = theCampBattleControl.GetManagerBytypeAndCountry( uchBattleType ,GetCountryId());
    if ( pBattleManager == NULL )
    { return; }

    switch( uchBattleType )
    {
    case CampDefine::BattleTypeKing:
    case CampDefine::BattleTypeDragon:
    case CampDefine::BattleTypeRosefinch:
        {
            CampCountryBattleManager* pCountryBattleManager = static_cast< CampCountryBattleManager* >( pBattleManager );

            MsgQueryCountryBattleSignUpAck xAck;
            xAck.uchBattleType = pCountryBattleManager->GetCountryBattleType();
            if ( pBattleManager->GetBattleStatus() != CampDefine::StatusSignUp )
            { xAck.uchResult = MsgQueryCountryBattleSignUpAck::ECD_NotOpen; }
            else
            { xAck.nGuildID = pCountryBattleManager->GetSignUpGuildID(); }
            SendMessageToClient( &xAck );
        }
        break;
    default:
        return;
    }
}
void GamePlayer::OnMsgGetGlobalDBBattleSumReq( Msg* pMsg )
{
	MsgGetGlobalDBBattleSumAck msg;
	msg.Sum = theGameGlobalDBManager.GetBattleSum();
	SendMessageToClient( &msg );
}