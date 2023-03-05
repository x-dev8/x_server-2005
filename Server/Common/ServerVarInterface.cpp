#include "BaseCharacter.h"
#include "MessageDefine.h"
#include "GameWorld.h"
#include "ShareData.h"
#include "ServerVarinterface.h"
#include "ScriptKeyword.h"
#include "ScriptCompiler.h"
#include "DataBuffer.h"
#include "GlobalDef.h"
#include "GamePlayer.h"
#include "ScriptFunctionDefine.h"
#include "NpcBaseEx.h"
#include "MonsterBaseEx.h"
#include "QuestManager.h"
#include "ShopMgr.h"
#include "ErrorLog.h"
#include "GameWorldTimer.h"
#include "DatabaseConnectors.h"
#include "DBChunk.h"
#include "FuncPerformanceLog.h"
#include "XmlStringLanguage.h"
#include "ResourcePath.h"
#include "TeamManager.h"
#include "NpcInfo.h"
#include "Configure.h"
#include "BattleManager.h"
#include "MountManager.h"
#include "ExpStage.h"
#include "MonsterCreater.h"
#include "NpcCreater.h"
#include "XinFaConfig.h"
#include "GlobalDBManager.h"
#include "GameTimeHandleManager.h"
#include "WorldBattleManager.h"
#include "LogEventService.h"
#include "QuestEntrust.h"
#pragma warning( push )
#pragma warning( disable : 4293 )

// 服务器的全局系统变量
IScriptInterface* gs_pScript = NULL; 
IScriptInterface* GetScriptInterface()
{ return gs_pScript; }

CServerVarInterface g_svi;

CServerVarInterface::CServerVarInterface()
{
    m_recordCurCharId = -1;
    m_recordDstId     = -1;
    m_nCurCharId      = -1;
    m_nDstId          = -1;
    gs_pScript = this;
}

void CServerVarInterface::SetTeamVar( int nVarId, int nOp, void* pParams, int nParamCount )
{
    BaseCharacter* pChar = theRunTimeData.GetCharacterByID( m_nCurCharId );
    if( !pChar || !pChar->IsPlayer() )
    { return; }

    MapConfig::MapData* pMapData = theMapConfig.GetMapDataById( EctypeId2MapId( pChar->GetMapID() ) );
    if ( pMapData == NULL )
    { return; }

    GameTeam* pTeam = theGameTeamManager.GetTeam( pChar->GetTeamID() );
    if ( pTeam != NULL )
    {
        GameObjectId nSelfId = m_nCurCharId;
        for (int n = 0; n < pTeam->TeamMemberCount(); ++n)
        {
            unsigned long dwPlayerID = pTeam->GetMemberIDByIndex( n );
            GamePlayer* pPlayer = theRunTimeData.GetGamePlayerByDBID( dwPlayerID );

            if (pMapData->IsEctypeMap())
            {// 副本地图全图生效
                if ( pPlayer != NULL && ( pChar->GetMapID() == pPlayer->GetMapID() ) )
                {
                    m_nCurCharId = pPlayer->GetID();
                    SetVar( nVarId, nOp, pParams, nParamCount );
                }   
            }
            else
            {// 普通地图两屏幕
                if ( pPlayer != NULL && pPlayer->IsInMapArea( pChar->GetMapID(), pChar->GetFloatX(), pChar->GetFloatY(), TEAM_EXP_DIS ) )
                {
                    m_nCurCharId = pPlayer->GetID();
                    SetVar( nVarId, nOp, pParams, nParamCount );
                }   
            }         
        }
        m_nCurCharId = nSelfId;
    }
    else
    {
        SetVar( nVarId, nOp, pParams, nParamCount );
    }
}


void CServerVarInterface::SetAreaVar( int nVarId, int nValue, int nRadius, int nType )
{
    BaseCharacter* pChar = theRunTimeData.GetCharacterByID(m_nCurCharId);
    if ( pChar == NULL || !pChar->IsPlayer() )
    { return;}

    GamePlayer* pPlayer = (GamePlayer*)pChar;
    if (pPlayer == NULL)
    { return;}

    GameStage* pStage = theGameWorld.GetStageById( pPlayer->GetMapID() );
    if (pStage == NULL)
    { return;}

    pStage->SetVarInTaskArea( pPlayer, nVarId, nValue, nRadius, nType );
}

bool CServerVarInterface::IsTeamVarAllLess( int nVarId, int nValue )
{
    BaseCharacter* pChar = theRunTimeData.GetCharacterByID( m_nCurCharId );
    if( !pChar || !pChar->IsPlayer() )
    {
        GetErrorLog()->logString( "CServerVarInterface::IsTeamVarAllLess error" );
        return false;
    }

    char szName[dr_MaxPlayerName] = { 0 };
    GameTeam* pTeam = theGameTeamManager.GetTeam( pChar->GetTeamID() );
    if ( pTeam != NULL )
    {
        for ( int n = 0; n < pTeam->TeamMemberCount(); ++n )
        {
            unsigned long dwPlayerID = pTeam->GetMemberIDByIndex( n );
            GamePlayer* pPlayer = theRunTimeData.GetGamePlayerByDBID( dwPlayerID );
            if ( pPlayer == NULL )
            { return false; }

            if ( GetVar( nVarId, pPlayer->GetID() ) >= nValue )
            {
                strncpy_s( szName, sizeof( szName ), pPlayer->GetCharName(), sizeof( szName ) - 1 );
                break; 
            }
        }
    }
    else
    {
        if ( GetVar( nVarId ) >= nValue )
        { 
            strncpy_s( szName, sizeof( szName ), pChar->GetCharName(), sizeof( szName ) - 1 );
        }
    }

    if ( szName[0] != 0 )
    {
        GamePlayer* pTeamHeader = NULL;
        if ( pTeam == NULL )
        {
            pTeamHeader = (GamePlayer*)pChar;
        }
        else
        {
            pTeamHeader = theRunTimeData.GetGamePlayerByDBID( pTeam->GetTeamHeaderID() );
        }
        if ( pTeamHeader != NULL )
        {
            pTeamHeader->TellClient( theXmlString.GetString(eClient_FlyMapGreaterThanMax), szName, nValue );
        }
    }

    return szName[0] == 0;
}

bool CServerVarInterface::IsTeamVarAllGreater( int nVarId, int nValue )
{
    BaseCharacter* pChar = theRunTimeData.GetCharacterByID( m_nCurCharId );
    if( !pChar || !pChar->IsPlayer() )
    {
        GetErrorLog()->logString( "CServerVarInterface::IsTeamVarAllGreater error" );
        return false;
    }

    char szName[dr_MaxPlayerName] = { 0 };
    GameTeam* pTeam = theGameTeamManager.GetTeam( pChar->GetTeamID() );
    if ( pTeam != NULL )
    {
        for ( int n = 0; n < pTeam->TeamMemberCount(); ++n )
        {
            unsigned long dwPlayerID = pTeam->GetMemberIDByIndex( n );
            GamePlayer* pPlayer = theRunTimeData.GetGamePlayerByDBID( dwPlayerID );
            if ( pPlayer == NULL )
            { return false; }

            if ( GetVar( nVarId, pPlayer->GetID() ) <= nValue )
            {
                strncpy_s( szName, sizeof( szName ), pPlayer->GetCharName(), sizeof( szName ) - 1 );
                break; 
            }
        }
    }
    else
    {
        if ( GetVar( nVarId ) <= nValue )
        { 
            strncpy_s( szName, sizeof( szName ), pChar->GetCharName(), sizeof( szName ) - 1 );
        }
    }

    //if ( szName[0] != 0 )
    //{
    //    GamePlayer* pTeamHeader = NULL;
    //    if ( pTeam == NULL )
    //    {
    //        pTeamHeader = (GamePlayer*)pChar;
    //    }
    //    else
    //    {
    //        pTeamHeader = (GamePlayer*) theRunTimeData.GetGamePlayerByDBID( pTeam->GetTeamHeaderID() );
    //    }
    //    if ( pTeamHeader != NULL )
    //    {
    //        pTeamHeader->TellClient( theXmlString.GetString(eClient_FlyMapGreaterThanMax), szName, nValue );
    //    }
    //}

    return szName[0] == 0;
}


void CServerVarInterface::SetVar( int nVarId,  int nOp, void* pvParams, int nParamCount )
{
    if( pvParams == NULL )
    { return; }

    CScriptCmd__SetVar::Param* pParams = (CScriptCmd__SetVar::Param*)pvParams;
    
    BaseCharacter* pChar = theRunTimeData.GetCharacterByID( m_nCurCharId );
    if( pChar == NULL || !pChar->IsPlayer() )
    { return; }

    GamePlayer* pPlayer = static_cast< GamePlayer* >( pChar );
    switch( nVarId )
    {
    case SKW_POS:
        if ( nParamCount != 3 )
        { return; }
        break;
    default:
        if ( nParamCount != 1 )
        { return; }
        break;
    }

    uint8 uchOperateType = GetOperateType( nOp );

    switch( nVarId )
    {
    case SKW_LEVEL:
        pPlayer->SetLevel( pParams[0].GetNumber() );
        break;
    case SKW_POS:
        pPlayer->SetFloatXF( float(pParams[0].GetNumber()) );
        pPlayer->SetFloatYF( float(pParams[1].GetNumber()) );
        pPlayer->SetDir( pParams[2].GetNumber() );
        break;
    case SKW_NAME:
        pPlayer->SetCharName( pParams[0].GetString() );
        break;
    case SKW_MAP:
        pPlayer->SetMapID( pParams[0].GetNumber() );
        break;
    case SKW_MODEL:
        pPlayer->SetModelId( pParams[0].GetNumber() );
        break;
    case SKW_PROFESSION:
        pPlayer->Script_SetProfession( pParams[0].GetNumber() );
        break;
    case SKW_SEX:
        pPlayer->Script_SetSex( pParams[0].GetNumber() );
        break;
    case SKW_SILVER:
        pPlayer->OperateJinDing( uchOperateType, pParams[0].GetNumber(), __FUNCTION__, __LINE__ ,ePlayerMoneySourceType_Scprit);
        break;
    case SKW_MONEY:
        pPlayer->OperateMoney( uchOperateType, pParams[0].GetNumber(), true, __FUNCTION__, __LINE__ ,ePlayerMoneySourceType_Scprit);
        break;
    case SKW_JIAOZI:
        pPlayer->OperateJiaoZi( uchOperateType, pParams[0].GetNumber(), true, __FUNCTION__, __LINE__ ,ePlayerMoneySourceType_Scprit);
        break;
    case SKW_JIAOZI_MONEY:
        pPlayer->OperateJiaoZi( uchOperateType, pParams[0].GetNumber(), true, __FUNCTION__, __LINE__,ePlayerMoneySourceType_Scprit );
        break;
    case SKW_EXP:
        pPlayer->Script_SetExp( pParams[0].GetNumber(), nOp, __FUNCTION__, __LINE__ );
        break;
    case SKW_SKILLEXP:
        pPlayer->Script_SetSkillExp( pParams[0].GetNumber(), nOp );
        break;
    case SKW_STAMINA:
        pPlayer->Script_SetCon( pParams[0].GetNumber(), nOp );
        break;
    case SKW_STRENGTH:
        pPlayer->Script_SetStr( pParams[0].GetNumber(), nOp );
        break;
    case SKW_AGILITY:
        pPlayer->Script_SetDex( pParams[0].GetNumber(), nOp );
        break;
    case SKW_INTELLIGENCE:
        pPlayer->Script_SetInt( pParams[0].GetNumber(), nOp );
        break;
    case SKW_SPIRIT:
        pPlayer->Script_SetMgc( pParams[0].GetNumber(), nOp );
        break;
    case SKW_LUCKY:
        pPlayer->Script_SetLky( pParams[0].GetNumber(), nOp );
        break;
    case SKW_HP:
        pPlayer->Script_SetHp( pParams[0].GetNumber(), nOp );
        break;
    case SKW_MP:
        pPlayer->Script_SetMp( pParams[0].GetNumber(), nOp );
        break;
    case SKW_SKILL:
        pPlayer->Script_Skill( pParams[0].GetNumber(), nOp );
        break;
    case SKW_REPUTATION:
        pPlayer->OperateReputation(uchOperateType, pParams[0].GetNumber(), __FUNCTION__, __LINE__ ,ePlayerMoneySourceType_Scprit);
        break;
    case SKW_EXPLOIT:
        pPlayer->OperateExploit( uchOperateType, pParams[0].GetNumber(), __FUNCTION__, __LINE__ ,ePlayerMoneySourceType_Scprit);
        break;
    case SKW_ENERGY:
        pPlayer->Script_SetEnergy( pParams[0].GetNumber(), nOp );
        break;
    case SKW_VIGOR:
        pPlayer->Script_SetVigor( pParams[0].GetNumber(), nOp );
        break;
    case SKW_VIGORMAX:
        pPlayer->Script_SetVigorMax( pParams[0].GetNumber(), nOp );
        break;
    default:
        pPlayer->SetVar( nVarId, pParams[0].GetNumber(), nOp );
        break;
    }
}

const char* CServerVarInterface::GetStringFormVar( int nVarId )
{
    BaseCharacter* pChar = theRunTimeData.GetCharacterByID( m_nCurCharId );
    if( pChar == NULL || !pChar->IsPlayer() )
    { return ""; }

    GamePlayer* pPlayer = static_cast< GamePlayer* >( pChar );

    switch( nVarId )
    {
    case SKW_NAME:
        {
            return pPlayer->GetCharName();
        }
        break;
    case SKW_HEADERNAME:
        {
            GameTeam* pTeam = theGameTeamManager.GetTeam( pPlayer->GetTeamID() );
            if ( pTeam == NULL )
            { return ""; }

            GamePlayer* pHeader = theRunTimeData.GetGamePlayerByDBID( pTeam->GetTeamHeaderID() );
            if ( pHeader == NULL )
            { return ""; }

            return pHeader->GetCharName();
        }
        break;
    case SKW_DSTPLAYERNAME:
        {
            BaseCharacter* pHeader = theRunTimeData.GetCharacterByID( pPlayer->GetDstPlayerId() );
            if ( pHeader == NULL )
            { return ""; }

            return pHeader->GetCharName();
        }
        break;
    case SKW_GUILDNAME:
        {
            GameGuild* pGuild = pPlayer->GetGuild();
            if ( pGuild == NULL )
            { return ""; }
            
            return pGuild->GetName();
        }
        break;
    case  SKW_MARRIAGENAME:
        {
            return pPlayer->GetMarriageName();
        }
        break;
	case SKW_GetGuildName:
		{
			GameGuild* pGuild = pPlayer->GetGuild();
			if( pGuild == NULL )
			{ return " "; }
			return pGuild->GetName();
		}
		break;
    default:
        break;
    }

    static char szVar[32];
    itoa( GetVar(nVarId), szVar, 10 );
    return szVar;
}

int CServerVarInterface::GetVar( int nVarId, GameObjectId nPlayerId )
{
    if ( nPlayerId == -1 )
    { nPlayerId = m_nCurCharId; }

    BaseCharacter* pChar = theRunTimeData.GetCharacterByID( nPlayerId );
    if( pChar == NULL || !pChar->IsPlayer() )
    { return 0; }
    GamePlayer* pPlayer = static_cast< GamePlayer* >( pChar );

    switch( nVarId )
    {
    case SKW_SILVER:
        return pPlayer->GetJinDing(); 
        break;
    case SKW_MONEY:
        return pPlayer->GetMoney();
        break;
    case SKW_JIAOZI:
        return pPlayer->GetJiaoZi();
        break;
    case SKW_JIAOZI_MONEY:
        return pPlayer->GetJiaoZiMoney(); 
        break;
    case SKW_MAP:
        return pPlayer->GetMapID();
        break;
    case SKW_POSX:
        return pPlayer->GetTileX();
        break;
    case SKW_POSY:
        return pPlayer->GetTileY();
        break;
    case SKW_LEVEL:
        return pPlayer->GetLevel();
        break;
    case SKW_PROFESSION:
        return pPlayer->GetProfession();
        break;
    case SKW_SEX:
        return pPlayer->GetSex();
        break;
    case SKW_EXP:
        return pPlayer->Script_GetExp();
        break;
    case SKW_SKILLEXP:
        return pPlayer->Script_GetSkillExp();
        break;
    case SKW_STAMINA:
        return pPlayer->Script_GetCon();
        break;
    case SKW_STRENGTH:
        return pPlayer->Script_GetStr();
        break;
    case SKW_AGILITY:
        return pPlayer->Script_GetDex();
        break;
    case SKW_INTELLIGENCE:
        return pPlayer->Script_GetInt();
        break;
    case SKW_SPIRIT:
        return pPlayer->Script_GetMgc();
        break;
    case SKW_LUCKY:
        return pPlayer->Script_GetLky();
        break;
    case SKW_HP:
        return pPlayer->Script_GetHp();
        break;
    case SKW_MP:
        return pPlayer->Script_GetMp();
        break;
    case SKW_REPUTATION:
        return pPlayer->GetReputation();
        break;
    case SKW_EXPLOIT:
        return pPlayer->GetExploit();
        break;
    case SKW_ENERGY:
        return pPlayer->gCharInfoServer.baseinfo.liveinfo.activity;
        break;
    case SKW_ENERGYMAX:
        return pPlayer->gCharInfoServer.baseinfo.liveinfo.activityMax;
        break;
    case SKW_VIGOR:
        return pPlayer->gCharInfoServer.baseinfo.liveinfo.vigor;
        break;
    case SKW_VIGORMAX:
        return pPlayer->gCharInfoServer.baseinfo.liveinfo.vigorMax;
        break;
    default:
        break;
    }

    return pPlayer->GetVar( nVarId );
}

void CServerVarInterface::Dlg( const char* pszText, int iButtonFLag ,int iValue)
{
    BaseCharacter* pChar = theRunTimeData.GetCharacterByID( m_nCurCharId );
    if( pChar == NULL || !pChar->IsPlayer() )
    { return; }

    MsgAckScript msg;
    msg.byType = MsgAckScript::eNpcDialog;
    msg.stNpcId = m_nDstId;
    msg.SetString( pszText );
    msg.dlgType = iButtonFLag;
    msg.iValue    = iValue;
    GettheServer().SendMsgToSingle( &msg, pChar );
}

void CServerVarInterface::NpcMainDlg( const char* pszText, int iButtonFLag ,int iValue)
{
    BaseCharacter* pChar = theRunTimeData.GetCharacterByID( m_nCurCharId );
    if( pChar == NULL || !pChar->IsPlayer() )
    { return; }

    MsgAckScript msg;
    msg.byType = MsgAckScript::eNpcMainDialog;
    msg.stNpcId = m_nDstId;
    msg.SetString( pszText );
    msg.dlgType = iButtonFLag;
    msg.iValue    = iValue;
    GettheServer().SendMsgToSingle( &msg, pChar );
}

void CServerVarInterface::Ask( short stVarId, const char* pszText )
{
    if( m_nCurCharId == InvalidGameObjectId )
    { return;}

    if ( m_nDstId != InvalidGameObjectId )
    {
        BaseCharacter* pChar = theRunTimeData.GetCharacterByID( m_nDstId );
        if ( pChar == NULL )
        { return; }

        if ( pChar->IsNpc() )
        {
            NpcBaseEx* pNpc = static_cast< NpcBaseEx* >( pChar );
            if ( !pNpc->GetShow() )
            { return; }
        }
        else if ( pChar->IsMonster() )
        {
            MonsterBaseEx* pMonster = static_cast< MonsterBaseEx* >( pChar );
            if ( !pMonster->CanQueryScriptTypeStatus() )
            { return; }
        }
    }

    BaseCharacter* pChar = theRunTimeData.GetCharacterByID( m_nCurCharId );
    if( !pChar || !pChar->IsPlayer() )
    { return; }

    GamePlayer* pGamePlayer = (GamePlayer*)pChar;
    if( !pGamePlayer->RegisterVar( stVarId ) )
    { return; }
    pGamePlayer->SetScriptNpc( m_nDstId );

    MsgAckScript msg;
    msg.byType  = MsgAckScript::eAskQuestion;
    msg.stNpcId = m_nDstId;
    msg.SetString( pszText );
    GettheServer().SendMsgToSingle( &msg, pChar );
}

//私聊
void CServerVarInterface::Tell( const char *pszText )
{
    BaseCharacter *pChar = theRunTimeData.GetCharacterByID( m_nCurCharId );
    if( !pChar )
    {
        return;
    }
    pChar->TellClient( pszText );
}

//说话
void CServerVarInterface::Talk( int type, const char *pszText )
{
    if ( !pszText || strlen(pszText) <= 0 )
    { return; }

    MsgShowText msg;
    msg.bTile = false;
    msg.byAlign = MsgShowText::eAlignMiddle;
    msg.nShowInfoType = type;
    strncpy_s( msg.szText, MsgShowText::STRING_LEGTH, pszText, MsgShowText::STRING_LEGTH-1 );
    BaseCharacter* pChar = theRunTimeData.GetCharacterByID( m_nCurCharId );
    if( !pChar || !pChar->IsPlayer() )
    { return; }
    GettheServer().SendMsgToSingle( &msg, pChar );
}

//说话
void CServerVarInterface::TalkToAll( int type, const char *pszText )
{
    if ( !pszText || strlen(pszText) <= 0 )
        return;
    MsgShowText msg;
    msg.bTile = false;
    msg.byAlign = MsgShowText::eAlignMiddle;
    msg.nShowInfoType = type;
    strncpy_s( msg.szText, MsgShowText::STRING_LEGTH, pszText, MsgShowText::STRING_LEGTH-1 );
    GettheServer().SendMsgToWorld( &msg, true );
}

void CServerVarInterface::TalkToCountry( int country_id, int type, const char *pszText )
{
	BaseCharacter* pChar = theRunTimeData.GetCharacterByID( m_nCurCharId );
	if( !pChar || !pChar->IsPlayer() )
	{
		GetErrorLog()->logString( "CServerVarInterface::TalkToMap error" );
		return;
	}

	if ( pszText == NULL || *pszText == 0 )
		return;

	uint32 realcountry = country_id;
	if (realcountry < 0)
	{
		realcountry = pChar->GetCountry();
	}

	MsgShowText msg;
	msg.bTile = false;
	msg.byAlign = MsgShowText::eAlignMiddle;
	msg.nShowInfoType = type;
	strncpy_s( msg.szText, MsgShowText::STRING_LEGTH, pszText, MsgShowText::STRING_LEGTH-1 );
	GettheServer().SendMsgToCountry(&msg,realcountry,true);
}

void CServerVarInterface::TalkToMap( int map_id, int type, const char *pszText )
{
	BaseCharacter* pChar = theRunTimeData.GetCharacterByID( m_nCurCharId );
	if( !pChar || !pChar->IsPlayer() )
	{
		GetErrorLog()->logString( "CServerVarInterface::TalkToMap error" );
		return;
	}

	if ( pszText == NULL || *pszText == 0 )
		return;

	uint32 realmap = map_id;
	if (map_id < 0)
	{
		realmap = pChar->GetMapID();
	}

	MsgShowText msg;
	msg.bTile = false;
	msg.byAlign = MsgShowText::eAlignMiddle;
	msg.nShowInfoType = type;
	strncpy_s( msg.szText, MsgShowText::STRING_LEGTH, pszText, MsgShowText::STRING_LEGTH-1 );
	GettheServer().SendMsgToStage(&msg,realmap);
}

//说话
void CServerVarInterface::TalkToTeam( int type, const char *pszText )
{
    BaseCharacter* pChar = theRunTimeData.GetCharacterByID( m_nCurCharId );
    if( !pChar || !pChar->IsPlayer() )
    {
        GetErrorLog()->logString( "CServerVarInterface::TalkToTeam error" );
        return;
    }
    if ( pszText == NULL || *pszText == 0 )
        return;
    MsgShowText msg;
    msg.bTile = false;
    msg.byAlign = MsgShowText::eAlignMiddle;
    msg.nShowInfoType = type;
    strncpy_s( msg.szText, MsgShowText::STRING_LEGTH, pszText, MsgShowText::STRING_LEGTH-1 );
    GameTeam* pTeam = theGameTeamManager.GetTeam(pChar->GetTeamID());
    if (pTeam != NULL)
    {
        for (int i = 0; i < pTeam->TeamMemberCount(); ++i)
        {
            DWORD dwPlayerID = pTeam->GetMemberIDByIndex( i );
            BaseCharacter* pTeamPlayer = theRunTimeData.GetGamePlayerByDBID(dwPlayerID);
            if( pTeamPlayer != NULL )
            {
                GettheServer().SendMsgToSingle( &msg, pTeamPlayer );
            }
        }
    }
    else
    {
        GettheServer().SendMsgToSingle( &msg, pChar );
    }
}


//说话
void CServerVarInterface::TalkToArea( int nMapId, int nX, int nY, int type, const char *pszText )
{
    if ( !pszText || strlen(pszText) <= 0 )
        return;

    DWORD dwMapId = 0;
    if ( nMapId == -1 || nX == -1 || nY == -1 )
    {
        BaseCharacter* pChar = NULL;
        pChar = theRunTimeData.GetCharacterByID( GetCurCharId() );
        if ( pChar == NULL )
        {
            pChar = theRunTimeData.GetCharacterByID( GetDstId() );
        }
        if ( pChar == NULL )
        {
            return;
        }
        dwMapId = pChar->GetMapID();
        nX      = pChar->GetTileX();
        nY      = pChar->GetTileY();
    }

    MsgShowText msg;
    msg.bTile   = false;
    msg.byAlign = MsgShowText::eAlignMiddle;
    msg.nShowInfoType = type;
    strncpy_s( msg.szText, MsgShowText::STRING_LEGTH, pszText, MsgShowText::STRING_LEGTH - 1 );
    GettheServer().SendMsgToArea( &msg, dwMapId, nX, nY );
}

//广播
void CServerVarInterface::Broadcast( int nType, const char *pszText )
{
    BaseCharacter *pChar = theRunTimeData.GetCharacterByID( m_nCurCharId );
    if( pChar == NULL )
    { return; }

    MsgChat Msg( MsgChat::CHAT_TYPE_PROGRAM_SYSTEM );
	if ( nType == 3 || nType == 4 )
	{
		Msg.chatHeader.stType = MsgChat::CHAT_TYPE_BULL;
	}
    Msg.header.stID = m_nCurCharId;
    Msg.SetString( pszText );
    if ( nType == 2 )       // 全国广播
    {
        GettheServer().SendMsgToCountry( &Msg , pChar->GetCountry(), true );  
    }
    else
    {
		if ( nType == 3 )
			nType = 0;
		if ( nType == 4 )
			nType = 1;
        GettheServer().SendMsgToWorld( &Msg , nType );  
    }
}

enum PlayerFlyType      // 飞地图的类型
{
    Fly_Individual = 0,         // 个人
    Fly_Team,                   // 队伍
    Fly_Guild,                  // 公会
	Fly_TeamFollow,				// 队伍跟随
};

bool CServerVarInterface::FlyToMap( FlyMapParam& xFlyMapParam )
{
    if( m_nCurCharId == -1 )
    { return false; }

    GamePlayer* pPlayer = (GamePlayer*)theRunTimeData.GetCharacterByID( m_nCurCharId );
    if( pPlayer == NULL || !pPlayer->IsPlayer() )
    { return false; }

    if ( xFlyMapParam.nMapId == -1 )
        xFlyMapParam.nMapId = pPlayer->GetMapID();




    switch ( xFlyMapParam.chFlyType )
    {
    case Fly_Individual:        // 个人进入
		{

			// 队长跳转时,将队伍跟随的队友也跳转
			GameTeam *pTeam = theGameTeamManager.GetTeam( pPlayer->GetTeamID() );
			if ( pTeam && pTeam->IsTeamHeader( pPlayer->GetDBCharacterID() ) ) //队长
			{
				if(pTeam->TeamMemberCount() > 1) //有队员
					for ( int i = 0; i < pTeam->TeamMemberCount(); ++i )
					{
						GameTeamMember* pMember = pTeam->GetTeamMemberByIndex(i);
						if ( pMember && pMember->GetTeamFollowMemberID() > 0 )
						{
							//lyh++ 如果是单人传地图的话就 队长取消队伍跟随
							MsgHeaderCancelTeamFollow msgReq;
							pPlayer->OnHeaderCancelTeamFollow( &msgReq );
							//xFlyMapParam.chFlyType = Fly_TeamFollow;
							break;
						}
					}
			}

			if(pTeam && !pTeam->IsTeamHeader( pPlayer->GetDBCharacterID() )) //队员
			{
				MsgCancelTeamFollow msg;
				pPlayer->OnCancelTeamFollow(&msg);
				

			}

        return pPlayer->FlyToMapReq( xFlyMapParam.nMapId, xFlyMapParam.x, xFlyMapParam.y, xFlyMapParam.fDir );
		}
        break;
    case Fly_Team:  // 组队进入
        {
            GameTeam* pTeam = theGameTeamManager.GetTeam( pPlayer->GetTeamID() );
            if ( pTeam == NULL )
            { return false; }

            // 判断副本地图是否已经开启
            MapConfig::MapData* pMapData = theMapConfig.GetMapDataById( EctypeId2MapId(xFlyMapParam.nMapId) );
            if ( pMapData == NULL )
            { return false; }

            DWORD dwMapId = theGameWorld.MakeEctypeStageID( pMapData, pPlayer );      // 队伍可能已经在里面了
            GameStage* pStage = theGameWorld.GetStageById( dwMapId );  // 查找是否已有此副本
            if ( pStage != NULL )   //已经存在了, 直接让他飞进去
            {
				//这儿原来只把自己传送过去，现在改为队伍模式飞地图时把队伍中所有人传送过去  liaojie
				/*GameTeam *pTeam = theGameTeamManager.GetTeam( pPlayer->GetTeamID() );
				bool bFlyResult = true;
				if ( pTeam && pTeam->IsTeamHeader( pPlayer->GetDBCharacterID() ) )
				{
					for ( int i = 0; i < pTeam->TeamMemberCount(); ++i )
					{
						GameTeamMember* pMember = pTeam->GetTeamMemberByIndex(i);
						if (!pMember)
						{
							continue;
						}
						GamePlayer* pMemberPlayer = theRunTimeData.GetGamePlayerByDBID( pMember->GetID() );
						if ( pMemberPlayer )
						{
							pMemberPlayer->FlyToMapReq( xFlyMapParam.nMapId, xFlyMapParam.x, xFlyMapParam.y, xFlyMapParam.fDir );
						}
					}
				}
				else
				{
					bFlyResult = false;
				}
				return bFlyResult;*/
                return pPlayer->FlyToMapReq( xFlyMapParam.nMapId, xFlyMapParam.x, xFlyMapParam.y, xFlyMapParam.fDir );
            }
            else
            {
                if ( xFlyMapParam.bCheckHeader && !pTeam->IsTeamHeader(pPlayer->GetDBCharacterID()) )
                {
                    pPlayer->TellClient(theXmlString.GetString(eTellClient_FlyOnlyTeamHeader));            // 队长未进入副本，无法传送
                    return false;           
                }

                unsigned int nInAreaCount = pTeam->GetTeamMemberCountInMap( pPlayer->GetMapID(), pPlayer->GetFloatX(), pPlayer->GetFloatY() );
                if ( nInAreaCount != pTeam->TeamMemberCount() )
                {
                    pPlayer->TellClient(theXmlString.GetString(eTellClient_TeamMemberMustArlound));            // 只有所有队员在有效范围内才能进入
                    return false;
                }

                if ( !pTeam->IsAllTeamMemberGreaterLevel(pMapData->MinPlayerLevel) )
                {
                    pPlayer->TellClient( theXmlString.GetString(eTellClient_TeamMemberMustGreaterMapLevel), pMapData->MinPlayerLevel );      // 所有队员都需要%d级才能进入此副本
                    return false;
                }

                //判断是否都接了这个任务,已经做了不行
                if ( xFlyMapParam.m_nQuestID != -1 )
                {
                    unsigned long dwNotHaveQuestPlayerID = pTeam->GetTeamMemberNotHaveQuest( xFlyMapParam.m_nQuestID );
                    if ( dwNotHaveQuestPlayerID != TeamDefine::ErrorID )
                    {
                        MsgAckResult xAck;
                        xAck.result = ER_TeamMemberMustHaveQuest;       // 所有队员都必须接任务才能进入此副本
                        xAck.value = dwNotHaveQuestPlayerID;
                        GettheServer().SendMsgToSingle( &xAck, pPlayer );
                        return false;
                    }
                }

                pPlayer->SetChangeStageType( GamePlayer::TeamChangeStage );
                return pPlayer->FlyToMapReq( xFlyMapParam.nMapId, xFlyMapParam.x, xFlyMapParam.y, xFlyMapParam.fDir );
            }
        }
        break;
    case Fly_Guild: // 公会进入
        {
            if ( pPlayer->GetGuild() == NULL )
            { return false; }

            return pPlayer->FlyToMapReq( xFlyMapParam.nMapId, xFlyMapParam.x, xFlyMapParam.y, xFlyMapParam.fDir );
        }
        break;
	case Fly_TeamFollow:
		{
			if ( pPlayer->FlyToMapReq( xFlyMapParam.nMapId, xFlyMapParam.x, xFlyMapParam.y, xFlyMapParam.fDir ) )
			{
				// 队长跳转时,将队伍跟随的队友也跳转
				GameTeam *pTeam = theGameTeamManager.GetTeam( pPlayer->GetTeamID() );
				if ( pTeam && pTeam->IsTeamHeader( pPlayer->GetDBCharacterID() ) )
				{
					for ( int i = 0; i < pTeam->TeamMemberCount(); ++i )
					{
						GameTeamMember* pMember = pTeam->GetTeamMemberByIndex(i);
						if ( pMember && pMember->GetTeamFollowMemberID() > 0 )
						{
							GamePlayer* pMemberPlayer = theRunTimeData.GetGamePlayerByDBID( pMember->GetID() );
							if ( pMemberPlayer )
							{
								pMemberPlayer->FlyToMapReq( xFlyMapParam.nMapId, xFlyMapParam.x, xFlyMapParam.y, xFlyMapParam.fDir );
							}
						}
					}
				}
				return true;
			}
		}
		break;
    default:
        break;
    }

    return false;
}

bool CServerVarInterface::CallAllTeamPlayerFlyToMap(int nMapId, int x, int y, float fDir /* = 0.0f */)
{
    GamePlayer* pPlayer = (GamePlayer*)theRunTimeData.GetCharacterByID( m_nCurCharId );
    if( pPlayer == NULL || !pPlayer->IsPlayer() )
        return false;

    if ( nMapId == -1 )
        nMapId = pPlayer->GetMapID();

    GameTeam* pTeam = theGameTeamManager.GetTeam( pPlayer->GetTeamID() );
    if ( pTeam == NULL )
    { return false; }

    //if ( !pTeam->IsTeamHeader(pPlayer->GetDBCharacterID()) )
    //{
    //    pPlayer->TellClient("");            // 只有队长才能带队员飞入副本地图
    //    return;
    //}

    unsigned int nInAreaCount = pTeam->GetTeamMemberCountInMap( pPlayer->GetMapID(), pPlayer->GetFloatX(), pPlayer->GetFloatY() );
    if ( nInAreaCount != pTeam->TeamMemberCount() )
    {
        pPlayer->TellClient(theXmlString.GetString(eTellClient_TeamMemberMustArlound));            // 只有所有队员在有效范围内才能进入
        return false;
    }

    return pTeam->CallAllTeamPlayerFlyToMapReq( nMapId, x, y, fDir );
}

bool CServerVarInterface::InitShop(int nShopId, int nRefreshRate, int nType, bool bIsBound, SShopItem pItems[], int nCount)
{
    ItemDefine::SItemCommon *pItemDetail = NULL;
    for ( int n=0; n<nCount; n++ )
    {
        if ( pItems[n].nBasePrice > 0 )
            continue;
        pItemDetail = GettheItemDetail().GetItemByID( pItems[n].nId );
        if ( !pItemDetail )
        {
            LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_ERROR, "Error:InitShop Can`t find Item[%d]",pItems[n].nId  );
            return false;
        }
        pItems[n].nBasePrice = pItemDetail->dwCost;
        pItems[n].costType   = pItemDetail->costType;
        pItems[n].costItemID  = pItemDetail->costItemID;
    }
    //
    CShopMgr::SShop *pShop = GetShopMgr()->GetShopById( nShopId );
    if ( pShop )
    {
        pShop->dwRefreshRate = nRefreshRate;
        pShop->byType = nType;
        pShop->bIsBound = bIsBound;
        // 移除老的没有的Item
        for ( int n=0; n<pShop->nItemCount && n < CShopMgr::SShop::eShopItemMax; )
        {
            bool bFind = false;
            for ( int m=0; m<nCount; m++ )
            {
                if ( pShop->stItem[n].nId == pItems[m].nId )
                {
                    bFind = true;
                    break;
                }
            }
            if ( bFind == true )
            {
                n++;
            }
            else
            {
                int nBack = pShop->nItemCount-1;
                if ( n < nBack )
                {
                    pShop->stItem[n] = pShop->stItem[nBack];
                }
                pShop->nItemCount--;
            }
        }
        // 添加/更新
        for ( int n=0; n<nCount; n++ )
        {
            SShopItem* pItem = pShop->GetItemById( pItems[n].nId );
            if ( pItem == NULL  )
            {
                pShop->AddItem(&pItems[n]);
            }
            else
            {
                pItem->nBasePrice = pItems[n].nBasePrice;
                //pItem->nMinCount = pItems[n].nMinCount;
                pItem->nMaxCount = pItems[n].nMaxCount;
                pItem->nPerCount = pItems[n].nPerCount;
                //pItem->nX = pItems[n].nX;
            }
        }
        pShop->RefreshCount();
    }
    else
    {
        CShopMgr::SShop stShop;
        stShop.nShopId = nShopId;
        stShop.dwRefreshRate = nRefreshRate;
        stShop.byType = nType;
        stShop.bIsBound = bIsBound;
        for ( int n=0; n<nCount; n++ )
        {
            if ( stShop.AddItem(&pItems[n]) == false )
            {
                GetErrorLog()->logString("Error:Can`t add item, the item is max(32)");
            }
        }
        stShop.RefreshCount();
        if( GetShopMgr()->AddShop( &stShop ) == false )
        {
            GetErrorLog()->logString( "Error:InitShop,can`t add shop,the shop is max" );
        }
    }
    return true;
}

void CServerVarInterface::Shop( int nShopId, GameObjectId nDstPlayerId, int nNpcId )
{
    GamePlayer* pChar = (GamePlayer*)theRunTimeData.GetCharacterByID( nDstPlayerId );
    if( !pChar || !pChar->IsPlayer() )
    {
        return;
    }
    // 记录下商店物品的副本,防止玩家跨NPC买物品
    CShopMgr::SShop *pShop = NULL;
    pShop = GetShopMgr()->GetShopById( nShopId );
    if ( !pShop )
        return;
    if ( nNpcId != -1 )
    {
        pShop->nShopNpcId = nNpcId;
    }
    else
    {
        pShop->nShopNpcId = m_nDstId;
    }
    pShop->RefreshPrice();
    pChar->SetShop( pShop );
    //
    MsgAckGetShop msg;
    msg.header.stID = pShop->nShopNpcId;    // 把 NPC id 用这个传回去
    msg.byType      = pShop->byType;
    msg.bIsBound    = pShop->bIsBound;
    msg.nCount      = pShop->nItemCount;
    if ( msg.nCount > MsgAckGetShop::eMaxItem )
    {
        msg.nCount = MsgAckGetShop::eMaxItem;
    }
    SShopItem *pItem = NULL;
    for( int i = 0; i < msg.nCount; i++ )
    {
        pItem = &pShop->stItem[i];
        msg.nIds[i] = pItem->nId;
        if ( pItem->nCurCount <= 0 || pItem->nPerCount <= 0 )
        {
            msg.nCounts[i] = 0;
        }
        else
        {
            int nLess = pItem->nCurCount % pItem->nPerCount;
            if ( nLess <= 0 )
            {
                nLess = pItem->nPerCount;
            }
            msg.nCounts[i] = nLess < pItem->nCurCount ? nLess : pItem->nCurCount;
        }
        msg.dwSellPrices[i] = pItem->dwSellPrice;
        msg.dwBuyPrices[i] = pItem->dwBuyPrice;
        msg.nBuyCounts[i] = pItem->nPerCount;
    }
    GettheServer().SendMsgToSingle( &msg, pChar );
}

void CServerVarInterface::DoCommand( const char* command )
{
    return;
    if( !command )
        return;
    if( strlen( command ) > 64 )
        return;
    if( m_nCurCharId == InvalidGameObjectId )
        return;

    BaseCharacter* pChar = theRunTimeData.GetCharacterByID( m_nCurCharId );
    if( !pChar || !pChar->IsPlayer() )
        return;

    MsgChat msg;
    char s[1024];
    WordParser words;
    words.Parse( command );
    if( stricmp( words.GetWord( 0 ), "onlineplayercount" ) == 0 )
    {
        sprintf_s(s, sizeof(s)-1, theXmlString.GetString(eClient_AddInfo_2slk_136), theRunTimeData.GetOnlinePlayer() );
        msg.SetString( s );
    }
    else if( stricmp( words.GetWord( 0 ), "whereis" ) == 0 )
    {
        GameObjectId objectId = InvalidGameObjectId;
        for ( int currentIndex = 0; (objectId = theGameWorld.GetNextObjectBId( 0 == currentIndex )) != InvalidGameObjectId; ++currentIndex )
        {
            BaseCharacter* pChar = (BaseCharacter*)theRunTimeData.GetCharacterByID( objectId );
            if ( pChar == NULL || !pChar->IsPlayer())
            { continue; }

            if( stricmp( pChar->GetCharName(), words.GetWord( 1 ) ) == 0 )
            {
                sprintf_s( s, sizeof(s)-1, "%s at map %ld pos %ld %ld", pChar->GetCharName(), pChar->GetMapID(), pChar->GetTileX(), pChar->GetTileY() );
                msg.SetString( s );
                break;
            }
        }

    }
    GettheServer().SendMsgToSingle( &msg, pChar );
}

void CServerVarInterface::Printf( const char* string, ... )
{
    if( !string )
        return;

    va_list    va;
    static char data[1024];
    va_start( va, string );
    wvsprintf( (char*)data, string, va );
    va_end( va );
    MessageBox( NULL, data, "script warning", MB_OK );
}

void CServerVarInterface::DBGPrint( const char* string )
{
    BaseCharacter *pActChar = theRunTimeData.GetCharacterByID( m_nCurCharId );
    if( !pActChar )
    { return; }

    if( !string )
    { return; }
        
    pActChar->Say( 0, string );
}

void CServerVarInterface::Show( short stImageId, int x, int y, DWORD dwLife, DWORD dwFlag, DWORD dwFlagTime )
{
    BaseCharacter *pActChar = theRunTimeData.GetCharacterByID( m_nCurCharId );
    if( !pActChar || !pActChar->IsPlayer() )
    {
        return;
    }
    MsgScriptShow msg;
    msg.stImageId = stImageId;
    msg.x = x;
    msg.y = y;
    msg.byFlag = (BYTE)dwFlag;
    msg.stLife = dwLife;
    msg.stFadeTime = dwFlagTime;
    GettheServer().SendMsgToSingle( &msg, pActChar );
}

void CServerVarInterface::RemoveAllEquip( )
{
    if( m_nCurCharId == -1 )
        return;

    BaseCharacter* pChar = theRunTimeData.GetCharacterByID( m_nCurCharId );
    if( !pChar || !pChar->IsPlayer() )
        return;

    GamePlayer* pGamePlayer = (GamePlayer*)pChar;
    if (!pGamePlayer)
        return;

    pGamePlayer->RemoveAllEquip();
}

void CServerVarInterface::SetBornPoint( DWORD dwMapID, int iPosX, int iPosY )
{
    BaseCharacter* pChar = theRunTimeData.GetCharacterByID( m_nCurCharId );
    if( pChar == NULL || !pChar->IsPlayer() )
    { return; }

    GamePlayer* pPlayer = (GamePlayer*)pChar;

    pPlayer->Script_SetBornPoint( dwMapID, iPosX, iPosY );
}

int CServerVarInterface::HaveThisItem( char *pItemName )
{
    BaseCharacter* pChar = theRunTimeData.GetCharacterByID( m_nCurCharId );
    if ( pChar == NULL || !pChar->IsPlayer() )
    { return 0; }

    GamePlayer* pGamePlayer = (GamePlayer*)pChar;

    ItemDefine::SItemCommon* pItem = GettheItemDetail().GetItemByName( pItemName );
    if( pItem == NULL  )
    { return 0; }

    return pGamePlayer->GetItemCount( pItem->ustItemID );
}

void CServerVarInterface::RemoveThisItem( char *pItemName, int iNumber )
{
    BaseCharacter* pChar = theRunTimeData.GetCharacterByID( GetCurCharId() );
    if ( pChar == NULL || !pChar->IsPlayer() )
    { return; }

    ItemDefine::SItemCommon *pItem = GettheItemDetail().GetItemByName( pItemName );
    if( pItem == NULL )
    { return; }

    GamePlayer* pPlayer = static_cast< GamePlayer* >( pChar );


	//LYH日志添加
	SCharItem *_item = pPlayer->GetBagItemByGuid(pPlayer->GetItemGUIDByItemID(pItem->ustItemID));
	if (_item)
	{
		theLogEventService.LogItemConsume(pPlayer->GetAccountID(),pPlayer->GetDBCharacterID(),pItem->ustItemID,iNumber,pPlayer->GetItemGUIDByItemID(pItem->ustItemID),
			_item->GetItemCount()-iNumber >= 0 ? _item->GetItemCount()-iNumber : 0,eItemLogInfo_ItemConsume_Script,
			pPlayer->GetCharName(),pItem->GetItemName());
	}
	

    if ( !pPlayer->RemoveItem( pItem->ustItemID, iNumber ) )
    {
        pPlayer->CancelCurScript( __FILE__, __FUNCTION__ );
    }
}

bool CServerVarInterface::IsThisItemEquipped( char *pItemName )
{
    BaseCharacter* pChar = theRunTimeData.GetCharacterByID( GetCurCharId() );
    if ( pChar == NULL || !pChar->IsPlayer() )
    { return false;}

    ItemDefine::SItemCommon *pItem = GettheItemDetail().GetItemByName( pItemName );
    if( pItem == NULL )
    { return false; }

    GamePlayer* pPlayer = static_cast< GamePlayer* >( pChar );
    return pPlayer->Script_IsThisItemEquipped( pItem->ustItemID );
}

bool CServerVarInterface::IsThisSkillActived( unsigned short ustSkillItemID,unsigned short ustSkillLevel )
{
    BaseCharacter* pChar = theRunTimeData.GetCharacterByID( GetCurCharId() );
    if ( !pChar || !pChar->IsPlayer() )
    { return false; }

    ItemDefine::SItemSkill *pSkill = GettheItemDetail().GetSkillByID( ustSkillItemID, ustSkillLevel );
    if( pSkill == NULL )
    { return false; }
    
    GamePlayer* pPlayer = static_cast< GamePlayer* >( pChar );

    return pPlayer->Script_IsThisSkillActived( ustSkillItemID,ustSkillLevel );
}
int	CServerVarInterface::GetWeekKillNum()
{
	BaseCharacter* pChar = theRunTimeData.GetCharacterByID( GetCurCharId() );
    if ( !pChar || !pChar->IsPlayer() )
    { return -1; }
	GamePlayer* pPlayer = static_cast< GamePlayer* >( pChar );
	return pPlayer->Script_GetWeekKillNum();
}
int	CServerVarInterface::GetAllKillNum()
{
	BaseCharacter* pChar = theRunTimeData.GetCharacterByID( GetCurCharId() );
    if ( !pChar || !pChar->IsPlayer() )
    { return -1; }
	GamePlayer* pPlayer = static_cast< GamePlayer* >( pChar );
	return pPlayer->Script_GetAllKillNum();
}
int	CServerVarInterface::GetSeriesKillNum()
{
	BaseCharacter* pChar = theRunTimeData.GetCharacterByID( GetCurCharId() );
    if ( !pChar || !pChar->IsPlayer() )
    { return -1; }
	GamePlayer* pPlayer = static_cast< GamePlayer* >( pChar );
	return pPlayer->Script_GetSeriesKillNum();
}
int    CServerVarInterface::GetMapIdByName( const char* pszMapName )
{
    MapConfig::MapData* pMapData = theMapConfig.GetMapDataByName( pszMapName );
    if( !pMapData )
        return -1;

    return pMapData->Id;
}
void CServerVarInterface::ProcTimeStep(int StringID,int TimeStep)
{
	BaseCharacter* pChar = theRunTimeData.GetCharacterByID( GetCurCharId() );
    if ( !pChar || !pChar->IsPlayer() )
    { return; }
	GamePlayer* pPlayer = static_cast< GamePlayer* >( pChar );
	pPlayer->Script_ProcTimeStep(StringID,TimeStep);
}
void CServerVarInterface::TeashSkill( std::vector<int>&vectorSkill )
{
    GamePlayer* pPlayer = (GamePlayer*)theRunTimeData.GetCharacterByID( GetCurCharId() );
    if ( !pPlayer || !pPlayer->IsPlayer() )
        return;
    MsgTeachSkill msg;
    msg.nNum = vectorSkill.size();
    for ( int n=0; n<MsgTeachSkill::MAXSKILL && n<msg.nNum ; n++ )
    {
        msg.nId[n] = vectorSkill[n];
    }
    GettheServer().SendMsgToSingle( &msg, pPlayer );
}

void CServerVarInterface::AddSkill( int nSkillId, int level, bool bMessageDialog  )
{
    GamePlayer* pPlayer = (GamePlayer*)theRunTimeData.GetCharacterByID( GetCurCharId() );
    if ( pPlayer == NULL || !pPlayer->IsPlayer() )
    { return; }

    if ( level > 0)
    {
        if( !pPlayer->LearnSkill( nSkillId, level, false ,bMessageDialog ) )
        {
            pPlayer->Log( theXmlString.GetString(eLog_info_2slk_7), nSkillId );
        }
        else
        {
            pPlayer->Log( theXmlString.GetString(eLog_info_2slk_8), nSkillId );
        }
    }
    else
    {
        pPlayer->ForgetSkill( nSkillId );
    }
}

void CServerVarInterface::AddXinFa( int nXinFaId, int level, bool bCheck, bool bMessageDialog  )
{
    GamePlayer* pPlayer = (GamePlayer*)theRunTimeData.GetCharacterByID( GetCurCharId() );
    if ( pPlayer == NULL || !pPlayer->IsPlayer() )
    { return; }

    if ( level > 0)
    {
        if( !pPlayer->LearnXinFa( nXinFaId, level, bCheck ,bMessageDialog ) )
        {
            pPlayer->Log( theXmlString.GetString(eLog_info_2slk_7), nXinFaId );
        }
        else
        {
            pPlayer->Log( theXmlString.GetString(eLog_info_2slk_8), nXinFaId );
        }
    }
    else
    {
        pPlayer->ForgetXinFa( nXinFaId );
    }
}

void CServerVarInterface::GMAddXinFa( int iWhichXinFa, int nLevel )
{
    GamePlayer* pPlayer = (GamePlayer*)theRunTimeData.GetCharacterByID( GetCurCharId() );
    if ( pPlayer == NULL || !pPlayer->IsPlayer() )
    { return; }


    XinFaConfig::STalentXinFa* pTalentXinFa = theXinFaConfig.GetXinFaByID( iWhichXinFa, nLevel );
    if( pTalentXinFa == NULL )
    { return ; }

    if ( !pTalentXinFa->arrayProfessionReq[pPlayer->GetProfession()] )
    { 
        pPlayer->SendErrorToClient(ER_ProfessionToLearnXinFa);
        return ; 
    }

    SCharXinFa* pCurCharXinFa = pPlayer->_XinFaManager.GetXinFaByID( iWhichXinFa );

    bool bAddSuccess = false;
    if ( pCurCharXinFa == NULL )
    { bAddSuccess =  pPlayer->_XinFaManager.AddXinFa(iWhichXinFa, nLevel); }
    else
    {
        pCurCharXinFa->nXinFaLevel = nLevel;
        bAddSuccess = true;
    }

    if ( bAddSuccess )
    {
        SCharXinFa* pCharXinFa = pPlayer->_XinFaManager.GetXinFaByID( iWhichXinFa );
        if( pCharXinFa == NULL )
        {
            pPlayer->SendErrorToClient(ER_LearnXinFa);
            return ; 
        }

        MsgChangeXinFa msg;
        msg.xinfa       = *pCharXinFa;
        msg.nUnUsedExp  = pPlayer->GetSkillExpUnUsed();

        if ( pCurCharXinFa == NULL )
        { msg.op = MsgChangeXinFa::OT_Add; }
        else
        { msg.op = MsgChangeXinFa::OT_Update; }

        GettheServer().SendMsgToSingle( &msg, pPlayer );

        for (int i = 0;i < XinFaConfig::EXCD_SkillMaxCount; ++i)
        {
            XinFaConfig::SXinFaSkill* pXinFaSkill = pTalentXinFa->GetXinFaSkill(i);
            if (pXinFaSkill == NULL)
            { continue; }

            if (pXinFaSkill->nLevel != 0)
            {
                pPlayer->LearnSkill( pXinFaSkill->nId, pXinFaSkill->nLevel, false, true );
            }
        }

        pPlayer->ApplyTalentXinFaToChar  ();
        pPlayer->UpdateCharAllAttibute   ();
        pPlayer->SendCharAttibuteToClient();

        return ;
    }
}

int CServerVarInterface::GetSkillLevel( int nSkillId )
{
    GameObjectId iCharID = GetCurCharId();
    GamePlayer* pPlayer = (GamePlayer*)theRunTimeData.GetCharacterByID( iCharID );
    if ( !pPlayer || !pPlayer->IsPlayer() )
        return -1;

    SCharSkill* pCharSkill = pPlayer->_SkillBag.GetSkillByID(nSkillId);
    if ( !pCharSkill)
        return -1;

    return pCharSkill->stSkillLevel; 
}

int CServerVarInterface::GetXinFaLevel( int nXinFaId )
{
    GameObjectId iCharID = GetCurCharId();
    GamePlayer* pPlayer = (GamePlayer*)theRunTimeData.GetCharacterByID( iCharID );
    if ( !pPlayer || !pPlayer->IsPlayer() )
        return -1;

    SCharXinFa* pCharXinFa = pPlayer->_XinFaManager.GetXinFaByID( nXinFaId );
    if ( !pCharXinFa)
        return -1;

    return pCharXinFa->nXinFaLevel; 
}

int CServerVarInterface::GetXinFaMaxLevel( )
{
    GameObjectId iCharID = GetCurCharId();
    GamePlayer* pPlayer = (GamePlayer*)theRunTimeData.GetCharacterByID( iCharID );
    if ( !pPlayer || !pPlayer->IsPlayer() )
        return -1;

    int nMaxLevel = 0;
    for ( int i=0; i<pPlayer->_XinFaManager.GetXinFaNum(); ++i )
    {
        SCharXinFa* pCharXinFa = pPlayer->_XinFaManager.GetXinFaByIndex( i );
        if ( pCharXinFa != NULL && pCharXinFa->nXinFaLevel > nMaxLevel )
        { nMaxLevel = pCharXinFa->nXinFaLevel; }
    }

    return nMaxLevel; 
}

//任务物品,只要是队伍中的人,有这个任务,并且没有满,就要给这个东西,
void CServerVarInterface::AddItem( const char* pszItemName, int nItemCount ,bool isChangeUnBindSum ,unsigned short UnBindeSum, int sysType, int typeID )
{
    GamePlayer* pPlayer = (GamePlayer*)theRunTimeData.GetCharacterByID( GetCurCharId() );
    if( pPlayer == NULL && !pPlayer->IsPlayer() )
    { return; }

    ItemDefine::SItemCommon* pItem = GettheItemDetail().GetItemByName( pszItemName );
    if( pItem == NULL )
    { return; }

    pPlayer->AddItem( pItem->ustItemID, nItemCount, EIGS_Script ,true,NULL,isChangeUnBindSum,UnBindeSum, sysType, typeID );
}

void CServerVarInterface::AddRecipe( unsigned short ustRecipeID )
{
    GamePlayer* pPlayer = (GamePlayer*)theRunTimeData.GetCharacterByID( GetCurCharId() );
    if( pPlayer == NULL || !pPlayer->IsPlayer() )
    { return; }

    pPlayer->Script_AddRecipe( ustRecipeID );
}

bool CServerVarInterface::HaveRecipe( unsigned short ustRecipeID )
{
    GamePlayer* pPlayer = (GamePlayer*)theRunTimeData.GetCharacterByID( GetCurCharId() );
    if( pPlayer == NULL || !pPlayer->IsPlayer() )
    { return false; }

    return pPlayer->_recipeManager.IsExistRecipe( ustRecipeID );
}

void CServerVarInterface::AddItemByItemid( const unsigned short ustItemid, int nItemCount, bool bIsBound ,bool isChangeUnBindSum,unsigned short UnBindeSum, int sysType, int typeID )
{
    GamePlayer* pPlayer = (GamePlayer*)theRunTimeData.GetCharacterByID( GetCurCharId() );
    if( pPlayer == NULL || !pPlayer->IsPlayer() )
    { return; }

    pPlayer->AddItem( ustItemid, nItemCount, EIGS_Script,bIsBound ,NULL,isChangeUnBindSum,UnBindeSum, sysType, typeID );
}

void CServerVarInterface::AddEquipByItemId( const unsigned short ustItemid, bool bStarRandom, int16 nStarLevel, bool bIsBound ,bool isChangeUnBindSum ,unsigned short UnBindeSum, int sysType, int typeID )
{
    GamePlayer* pPlayer = (GamePlayer*)theRunTimeData.GetCharacterByID( GetCurCharId() );
    if( pPlayer == NULL || !pPlayer->IsPlayer() )
    { return; }

    pPlayer->AddEquipItem( ustItemid, NUMERIC_ONE, EIGS_Script, bIsBound, NULL, bStarRandom, nStarLevel ,isChangeUnBindSum,UnBindeSum, sysType, typeID );
}

void CServerVarInterface::AddEquipRandAttrItem( unsigned short ustItemid, bool bIsBound,int nRandId1, int nRandId2, int nRandId3, int nRandId4, int nRandId5, int nRandId6, int nRandId7, int sysType, int typeID )
{
	GamePlayer* pPlayer = (GamePlayer*)theRunTimeData.GetCharacterByID( GetCurCharId() );
	if( pPlayer == NULL || !pPlayer->IsPlayer() )
	{ return; }

	pPlayer->AddEquipRandAttrItem(ustItemid, NUMERIC_ONE, EIGS_Script, bIsBound, NULL, nRandId1, nRandId2, nRandId3, nRandId4, nRandId5, nRandId6, nRandId7, sysType, typeID );
}

void CServerVarInterface::AddItemInWorld( unsigned short ustItemid, int nItemCount,bool isChangeUnBindSum ,unsigned short UnBindeSum, int sysType, int typeID )
{
    GamePlayer* pPlayer = (GamePlayer*)theRunTimeData.GetCharacterByID( GetCurCharId() );
    if ( pPlayer == NULL || !pPlayer->IsPlayer())
    { return; }

    ItemDefine::SItemCommon* pItemCommon = GettheItemDetail().GetItemByID( ustItemid );
    if ( pItemCommon == NULL )
    { return; }

    SCharItem item;
    theRunTimeData.CreateItem( NULL, pItemCommon->ustItemID, nItemCount, HelperFunc::CreateID(), item ,isChangeUnBindSum,UnBindeSum);

    //需要改成怪物死亡时候的坐标
    theGameWorld.CreateItemNpc( pItemCommon->GetItemName(),pPlayer->GetMapID(),pPlayer->GetFloatX(),pPlayer->GetFloatY(), 0, item, -1, 0, false);
}


void CServerVarInterface::AddTitle(unsigned short nstTitleID)
{
    BaseCharacter* pChar = theRunTimeData.GetCharacterByID( GetCurCharId() );
    if( pChar == NULL || !pChar->IsPlayer() )
    { return; }

    GamePlayer* pPlayer = static_cast< GamePlayer* >( pChar );
    pPlayer->AddTitle(nstTitleID);
}

void CServerVarInterface::RemoveTitle(unsigned short nstTitleID)
{
    BaseCharacter* pChar = theRunTimeData.GetCharacterByID( GetCurCharId() );
    if ( pChar == NULL || !pChar->IsPlayer() )
    { return; }

    GamePlayer* pPlayer = static_cast< GamePlayer* >( pChar );
    pPlayer->RemoveTitle(nstTitleID);
}

int CServerVarInterface::HaveThisTitle(unsigned short nTitleID)
{
    BaseCharacter* pChar = theRunTimeData.GetCharacterByID( GetCurCharId() );
    if ( pChar == NULL || !pChar->IsPlayer() )
    { return 0; }

    GamePlayer* pPlayer = static_cast< GamePlayer* >( pChar );

    return pPlayer->IsHaveTitle(nTitleID);
}

void CServerVarInterface::Quest_CancelQuest( int nQuestID )
{
    BaseCharacter* pChar = theRunTimeData.GetCharacterByID( GetCurCharId() );
    if( pChar == NULL || !pChar->IsPlayer() )
    { return; }

    GamePlayer* pPlayer = static_cast< GamePlayer* >( pChar );
    pPlayer->Script_CancelQuest( nQuestID );
}

bool CServerVarInterface::Quest_DoneQuest( int nQuestID )
{
    BaseCharacter* pChar = theRunTimeData.GetCharacterByID( GetCurCharId() );
    if ( pChar == NULL || !pChar->IsPlayer() )
    { return false; }

    GamePlayer* pPlayer = static_cast< GamePlayer* >( pChar );
    return pPlayer->Script_DoneQuest( nQuestID );
}

bool CServerVarInterface::Quest_SetQuestState( int nQuestID, int nState )
{
    if( nQuestID < dr_MinQuestId || nQuestID > dr_MaxQuestId )
        return false;

    BaseCharacter* pChar = theRunTimeData.GetCharacterByID( GetCurCharId() );
    if ( pChar == NULL || !pChar->IsPlayer() )
    { return false; }

    GamePlayer* pPlayer = static_cast< GamePlayer* >( pChar );
    return pPlayer->SetQuestState( nQuestID, nState );
}

void CServerVarInterface::Quest_GetQuestState( int nQuestID, int nVarID )
{
    BaseCharacter* pChar = theRunTimeData.GetCharacterByID( GetCurCharId() );
    if( pChar == NULL || !pChar->IsPlayer() )
    { return; }

    GamePlayer* pPlayer = static_cast< GamePlayer* >( pChar );
    pPlayer->Script_GetQuestState( nQuestID, nVarID );
}

void CServerVarInterface::Quest_RelateQuest( int nQuestID, int nState, int nEnter )
{
    BaseCharacter* pChar = theRunTimeData.GetCharacterByID( GetCurCharId() );
    if( pChar == NULL || !pChar->IsNpc() )
    { return; }

    NpcBaseEx* pNpc = static_cast< NpcBaseEx* >( pChar );
    QuestScript info;
    info.stQuestId = nQuestID;
    info.chState = nState;
    info.stEnter = nEnter;
    pNpc->AddQuestScript( info );
}

bool CServerVarInterface::Quest_CanGetNewQuest( int nVarID )
{
    BaseCharacter* pChar = theRunTimeData.GetCharacterByID( GetCurCharId() );
    if( pChar == NULL || !pChar->IsPlayer() )
    { return false; }

    GamePlayer* pPlayer = (GamePlayer*)pChar;
    return pPlayer->Script_CanGetNewQuest( nVarID );
}

void CServerVarInterface::RefreshMonster( int nMapId, int x, int y, const char* szArea )
{    
    BaseCharacter* pChar = theRunTimeData.GetCharacterByID( GetCurCharId() );

    GameStage* pStage = NULL;
    if ( nMapId == -1 )
    {
        if ( !pChar )
            return;
        pStage = theGameWorld.GetStageById( pChar->GetMapID() );
    }
    else
    {
        MapConfig::MapData* pMapData = theMapConfig.GetMapDataById( nMapId );
        if ( !pMapData )
            return;

        DWORD dwMapId = 0;
        if ( pChar )
            dwMapId = theGameWorld.MakeEctypeStageID( pMapData, pChar );
        else
            dwMapId = nMapId;

        pStage = theGameWorld.GetStageById( dwMapId );
    }

    if ( pStage )
        pStage->RefreshHideMonster( x, y, szArea );
}

void CServerVarInterface::PlayerMusic( const char *szFileName, short stParameter )
{
    BaseCharacter* pChar = theRunTimeData.GetCharacterByID( m_nCurCharId );
    if( pChar == NULL || !pChar->IsPlayer() )
    { return; }

    MsgScriptPlayerMusic msg;
    msg.header.stID = pChar->GetID();
    msg.stParameter = stParameter;
    msg.SetFileName( szFileName );
    GettheServer().SendMsgToSingle( &msg, pChar );
}

void CServerVarInterface::MakeItem(BYTE byCreatNewOrOld,/* int nMakeType, */int nRate,/* BYTE byEquipType, BYTE byItemType,
                                                                                      float fX1,float fX2,float fX3,float fX4, float fY, float fA,float fX,*/
                                                                                      int nIdBegin[], int nIdEnd[], int nCount/*,
                                                                                                                              float fw*/)
{
    GamePlayer* pChar = (GamePlayer*)theRunTimeData.GetCharacterByID( m_nCurCharId );
    if( !pChar || !pChar->IsPlayer() )
    { return; }

    pChar->SetScriptNpc( m_nDstId );
    MsgScriptMakeItem msg;
    GettheServer().SendMsgToSingle( &msg, pChar );
}

void CServerVarInterface::ShowQuestDlg( int nVarid, const char* szInfo )
{
    GamePlayer* pChar = (GamePlayer*)theRunTimeData.GetCharacterByID( m_nCurCharId );
    if( pChar == NULL || !pChar->IsPlayer() )
    { return; }

    pChar->SetScriptNpc( m_nDstId );

    MsgScriptReqShowQuestDlg msg;
    msg.header.stID = pChar->GetID();
    msg.stNpcId     = m_nDstId;
    HelperFunc::SafeNCpy( msg.szInfo, szInfo, MsgScriptReqShowQuestDlg::eInfoLengthMax );
    GettheServer().SendMsgToSingle( &msg, pChar );

    pChar->RegisterVar( nVarid );
}

void CServerVarInterface::ShowPubQuestDlg( int nVarid, int nType, const char* szInfo )
{
    GamePlayer* pChar = (GamePlayer*)theRunTimeData.GetCharacterByID( m_nCurCharId );
    if( pChar == NULL || !pChar->IsPlayer() )
    { return; }

    pChar->SetScriptNpc( m_nDstId );
    pChar->ShowPubQuestDlg( m_nDstId, nType, szInfo );

    pChar->RegisterVar( nVarid );
}

void CServerVarInterface::UseSkill( int nSkillId, int nSkillLevel )
{
    BaseCharacter* pDst = theRunTimeData.GetCharacterByID( m_nCurCharId );
    if ( pDst == NULL )
    { return; }

    ItemDefine::SItemSkill* pSkill = GettheItemDetail().GetSkillByID( nSkillId, nSkillLevel );
    if ( pSkill == NULL )
    { return; }

    SAttackTarget target;
    target.bIsCharTarget = true;
    target.nCharID = pDst->GetID();
    pDst->TryAttack(&target, pSkill, nSkillId, nSkillLevel );
}

void CServerVarInterface::SetStatusByScript( int nStatusID, int nStatusLevel )
{
    ItemDefine::SItemStatus* pItemStatus = GettheItemDetail().GetStatus(nStatusID,nStatusLevel);
    if ( NULL == pItemStatus )
    { return; }

    DWORD dwTime = HQ_TimeGetTime();
    BaseCharacter* pDst = theRunTimeData.GetCharacterByID( m_nCurCharId );
    if ( NULL == pDst || !pDst->IsPlayer())
    { return;  }

    GamePlayer* pGamePlayer = (GamePlayer*)pDst;

    bool bStop = false;
    if ( pItemStatus->actionMapConfigId != InvalidLogicNumber && pItemStatus->actionMapConfigId != EctypeId2MapId( pGamePlayer->GetMapID()) )
    { bStop = true; }

    bool bHaveChange = pGamePlayer->_buffManager.ApplyBuff( bStop, nStatusID,nStatusLevel,pGamePlayer->GetID(), dwTime, true, 0, pGamePlayer->GetDBCharacterID(), SCharBuff::StatusEventType_Other, 0);
    if ( bHaveChange )
    { pGamePlayer->OnBuffStatusChanged(true); }
}

void CServerVarInterface::AddStatusByScript(int nStatusID, int nStatusLevel)
{
    // Todo 现在已经修改成为跨服的，需要请求到center去同步  

}
void CServerVarInterface::PopNpcList()
{
    BaseCharacter * pDst = theRunTimeData.GetCharacterByID( m_nCurCharId );
    if ( !pDst )
    { return; }
    MsgPopMapNpcList pop;
    GettheServer().SendMsgToSingle( &pop, pDst );
}

int CServerVarInterface::GetWorldTime( const char *pszTimeType, bool bRealTime )
{
    if ( !pszTimeType )
    {
        return 0;
    }
    int nTime = 0;
    if ( bRealTime )
    {
        if ( stricmp(pszTimeType,"Year") == 0 )
        {
            nTime = GetGameWorldTimer()->GetRealTime( CGameWorldTimer::eYear );
        }
        else if ( stricmp(pszTimeType,"Month") == 0 )
        {
            nTime = GetGameWorldTimer()->GetRealTime( CGameWorldTimer::eMonth );
        }
        else if ( stricmp(pszTimeType,"Week") == 0 )
        {
            nTime = GetGameWorldTimer()->GetRealTime( CGameWorldTimer::eWeek );
        }
        else if ( stricmp(pszTimeType,"Day") == 0 )
        {
            nTime = GetGameWorldTimer()->GetRealTime( CGameWorldTimer::eDay );
        }
        else if ( stricmp(pszTimeType,"Hour") == 0 )
        {
            nTime = GetGameWorldTimer()->GetRealTime( CGameWorldTimer::eHour );
        }
        else if ( stricmp(pszTimeType,"Minute") == 0 )
        {
            nTime = GetGameWorldTimer()->GetRealTime( CGameWorldTimer::eMinute );
        }
    }
    else
    {
        if ( stricmp(pszTimeType,"Year") == 0 )
        {
            nTime = GetGameWorldTimer()->GetGameTime( CGameWorldTimer::eYear );
        }
        else if ( stricmp(pszTimeType,"Month") == 0 )
        {
            nTime = GetGameWorldTimer()->GetGameTime( CGameWorldTimer::eMonth );
        }
        //else if ( stricmp(pszTimeType,"Week") == 0 )
        //{
        //    nTime = GetGameWorldTimer()->GetGameTime( CGameWorldTimer::eWeek );
        //}
        else if ( stricmp(pszTimeType,"Day") == 0 )
        {
            nTime = GetGameWorldTimer()->GetGameTime( CGameWorldTimer::eDay );
        }
        else if ( stricmp(pszTimeType,"Hour") == 0 )
        {
            nTime = GetGameWorldTimer()->GetGameTime( CGameWorldTimer::eHour );
        }
        else if ( stricmp(pszTimeType,"Minute") == 0 )
        {
            nTime = GetGameWorldTimer()->GetGameTime( CGameWorldTimer::eMinute );
        }
    }
    return nTime;
}

int CServerVarInterface::GetBirthday( int nTimeType )
{
    GamePlayer* pChar = NULL;
    pChar = (GamePlayer*)theRunTimeData.GetCharacterByID( m_nCurCharId );
    if( !pChar || !pChar->IsPlayer() )
    { return 0; }

    int nTime = 0;
    switch( nTimeType ) 
    {
    case 0:
        pChar->GetBirthday( &nTime, NULL, NULL );
        break;
    case 1:
        pChar->GetBirthday( NULL, &nTime, NULL );
        break;
    case 2:
        pChar->GetBirthday( NULL, NULL, &nTime );
        break;
    default:
        break;
    }
    return nTime;
}

void CServerVarInterface::ShowBank()
{
    GamePlayer* pChar = (GamePlayer*)theRunTimeData.GetCharacterByID( m_nCurCharId );
    if( pChar == NULL || !pChar->IsPlayer() )
    { return; }

    //CBankMgr::SBank *pBank;
    //pBank = GetBankMgr()->GetBank( pChar );
    //if ( !pBank )
    //    return;
    //MsgUpdateBank msg;
    //msg.dwCurMoney = pBank->dwCurMoney;
    //msg.dwMaxMoney = pBank->dwMaxMoney;
    //msg.dwPlayerMoney = pChar->GetMoney();
    //GetBankMgr()->UpgradeNeedMoney( pChar, msg.dwUpgrade );
    //GettheServer().SendMsgToSingle( &msg, pChar );
}

BOOL CServerVarInterface::SetStorage()
{
    GamePlayer* pChar = (GamePlayer*)theRunTimeData.GetCharacterByID( m_nCurCharId );
    if( pChar == NULL || !pChar->IsPlayer() )
    { return false;}

    pChar->SetScriptNpc( m_nDstId );
    GamePlayer* pPlayer = static_cast< GamePlayer* >( pChar );

    NpcBaseEx* pNpcChar = (NpcBaseEx*)theRunTimeData.GetCharacterByID( m_nDstId );
    if( pNpcChar == NULL || !pNpcChar->IsNpc())
    { return false;}

    return !pPlayer->ProcessSecondPasswordOperate( PasswordDefine::EProtect_OpenStorage, PasswordDefine::OP_OpenStorage );
}

BOOL CServerVarInterface::SetMountStorage()
{
    GamePlayer* pChar = (GamePlayer*)theRunTimeData.GetCharacterByID( m_nCurCharId );
    if( pChar == NULL || !pChar->IsPlayer() )
    { return false;}

    pChar->SetScriptNpc( m_nDstId );
    GamePlayer* pPlayer = static_cast< GamePlayer* >( pChar );

    NpcBaseEx* pNpcChar = (NpcBaseEx*)theRunTimeData.GetCharacterByID( m_nDstId );
    if( pNpcChar == NULL || !pNpcChar->IsNpc())
    { return false;}

    return !pPlayer->ProcessSecondPasswordOperate( PasswordDefine::EProtect_OpenMountStorage, PasswordDefine::OP_OpenMountStorage );
}

void CServerVarInterface::ShowMail()
{
}

void CServerVarInterface::NpcMoveNext()
{
    GameObjectId iCharID = GetDstId();
    BaseCharacter* pChar = theRunTimeData.GetCharacterByID( iCharID );
    if( pChar && pChar->IsNpc() )
    {
        NpcBaseEx* pNpc = (NpcBaseEx*)pChar;
        //pNpc->MoveNext();
    }
}

void CServerVarInterface::NpcStopMove()
{
    GameObjectId iCharID = GetDstId();
    BaseCharacter* pChar = theRunTimeData.GetCharacterByID( iCharID );
    if( pChar && pChar->IsNpc() )
    {
        NpcBaseEx* pNpc = (NpcBaseEx*)pChar;
        pNpc->StartTalk();
    }
}

void CServerVarInterface::NpcStartMove()
{
    GameObjectId iCharID = GetDstId();
    BaseCharacter* pChar = theRunTimeData.GetCharacterByID( iCharID );
    if( pChar && pChar->IsNpc() )
    {
        NpcBaseEx* pNpc = (NpcBaseEx*)pChar;
        pNpc->EndTalk();
    }
}

void CServerVarInterface::NpcPlayAnim( const char* szName, int nTimes, const char* szEndName,
                                      bool bForView, int nNpcId )
{
    BaseCharacter* pChar = theRunTimeData.GetCharacterByID( m_nCurCharId );
    if( !pChar || !pChar->IsPlayer() )
    { return; }

    GameObjectId nNpcWorldId = -1;
    if ( nNpcId == -1 )
    {
        nNpcWorldId = GetDstId();
    }
    else
    {
        GameStage* pGameStage = NULL;
        DWORD dwMapID = pChar->GetMapID();
        pGameStage = theGameWorld.GetStageById( dwMapID );
        if ( !pGameStage )
        {
            GetErrorLog()->logString( "CServerVarInterface::NpcPlayAnim error" );
            return;
        }
        bool bFound = false;
        for( int n=0; n<pGameStage->GetCharacterCount(); n++)
        {
            GameObjectId cPID = pGameStage->GetCharacterID(n);
            BaseCharacter* pChar = theRunTimeData.GetCharacterByID(cPID);
            if ( !pChar || !pChar->IsNpc() )
            {
                continue;
            }
            NpcBaseEx *pNpc = (NpcBaseEx*)pChar;
            if ( pNpc->GetNpcID() == nNpcId )
            {
                nNpcWorldId = pNpc->GetID();
                bFound = true;
                break;
            }
        }
        if ( bFound == false )
        { return; }
    }

    NpcBaseEx* pNpc = (NpcBaseEx*)theRunTimeData.GetCharacterByID( nNpcWorldId );
    if ( !pNpc || !pNpc->IsNpc() )
    { return; }

    MsgNpcPlayAnim msg;
    msg.header.stID = pChar->GetID();
    msg.nNpcId = nNpcWorldId;
    HelperFunc::SafeNCpy( msg.szActionName, szName, MsgNpcPlayAnim::eActionNameLength );
    HelperFunc::SafeNCpy( msg.szEndActionName, szEndName, MsgNpcPlayAnim::eActionNameLength );
    msg.nLoopTimes = nTimes;
    if ( bForView == true )
    {
        GettheServer().SendMsgToView( &msg, pChar->GetID(), false );
        pNpc->SetLastAnimName( msg.szEndActionName );
    }
    else
    {
        GettheServer().SendMsgToSingle( &msg, pChar );
    }    
}

void CServerVarInterface::ScenePlay( int nSceneID, bool bView )
{
    BaseCharacter* pChar = theRunTimeData.GetCharacterByID( m_nCurCharId );
    if( !pChar || !pChar->IsPlayer() )
    { return; }
    
    MsgScenePlay  msgScene;
    msgScene.header.stID = pChar->GetID();
    msgScene.stSceneId   = nSceneID;
    if ( bView )
    { GettheServer().SendMsgToView  ( &msgScene, pChar->GetID() ); }
    else
    { GettheServer().SendMsgToSingle( &msgScene, pChar ); }    
}

void CServerVarInterface::BlackScreen( int nTime, bool bView )
{
    BaseCharacter* pChar = theRunTimeData.GetCharacterByID( m_nCurCharId );
    if( !pChar || !pChar->IsPlayer() )
    { return; }

    MsgBlackScreen  msg;
    msg.header.stID = pChar->GetID();
    msg.dwTime      = nTime;
    if ( bView )
    { GettheServer().SendMsgToView  ( &msg, pChar->GetID() ); }
    else
    { GettheServer().SendMsgToSingle( &msg, pChar ); }    
}

void CServerVarInterface::NpcScenePlay( int nNpcID, int nSceneID, bool bView )
{
    BaseCharacter* pChar = theRunTimeData.GetCharacterByID( m_nCurCharId );
    if( !pChar || !pChar->IsPlayer() )
    { return; }

    GameObjectId nNpcWorldId = -1;
    if ( nNpcID == -1 )
    {
        nNpcWorldId = GetDstId();
    }
    else
    {
        GameStage* pGameStage = NULL;
        DWORD dwMapID = pChar->GetMapID();
        pGameStage = theGameWorld.GetStageById( dwMapID );
        if ( !pGameStage )
        {
            GetErrorLog()->logString( "CServerVarInterface::NpcScenePlay error" );
            return;
        }
        bool bFound = false;
        for( int n=0; n<pGameStage->GetCharacterCount(); n++)
        {
            GameObjectId cPID = pGameStage->GetCharacterID(n);
            BaseCharacter* pChar = theRunTimeData.GetCharacterByID(cPID);
            if ( !pChar || !pChar->IsNpc() )
            { continue; }

            NpcBaseEx *pNpc = (NpcBaseEx*)pChar;
            if ( pNpc->GetNpcID() == nNpcID )
            {
                nNpcWorldId = pNpc->GetID();
                bFound = true;
                break;
            }
        }
        if ( bFound == false )
        { return; }
    }

    NpcBaseEx* pNpc = (NpcBaseEx*)theRunTimeData.GetCharacterByID( nNpcWorldId );
    if ( !pNpc || !pNpc->IsNpc() )
    { return; }

    MsgScenePlay  msgScene;
    msgScene.header.stID = nNpcWorldId;
    msgScene.stSceneId   = nSceneID;
    if ( bView )
    { GettheServer().SendMsgToView  ( &msgScene, pChar->GetID() ); }
    else
    { GettheServer().SendMsgToSingle( &msgScene, pChar ); }    
}

BOOL CServerVarInterface::IsNpcPlayAnim( int nNpcId, const char* szName )
{
    BaseCharacter* pChar = theRunTimeData.GetCharacterByID( m_nCurCharId );
    if( !pChar || !pChar->IsPlayer() )
    {
        GetErrorLog()->logString( "CServerVarInterface::IsNpcPlayAnim error" );
        return FALSE;
    }
    GameObjectId nNpcWorldId = -1;
    if ( nNpcId == -1 )
    {
        nNpcWorldId = GetDstId();
    }
    else
    {
        GameStage* pGameStage = NULL;
        DWORD dwMapID = pChar->GetMapID();
        pGameStage = theGameWorld.GetStageById( dwMapID );
        if ( !pGameStage )
        {
            GetErrorLog()->logString( "CServerVarInterface::NpcPlayAnim error" );
            return FALSE;
        }
        bool bFound = false;
        for( int n=0; n<pGameStage->GetCharacterCount(); n++)
        {
            GameObjectId cPID = pGameStage->GetCharacterID(n);
            BaseCharacter* pChar = theRunTimeData.GetCharacterByID(cPID);
            if ( !pChar || !pChar->IsNpc() )
            {
                continue;
            }
            NpcBaseEx *pNpc = (NpcBaseEx*)pChar;
            if ( pNpc->GetNpcID() == nNpcId )
            {
                nNpcWorldId = pNpc->GetID();
                bFound = true;
                break;
            }
        }
        if ( bFound == false )
        {
            GetErrorLog()->logString( "CServerVarInterface::IsNpcPlayAnim failed" );
            return FALSE;
        }
    }
    //
    NpcBaseEx* pNpc = (NpcBaseEx*)theRunTimeData.GetCharacterByID( nNpcWorldId );
    if ( !pNpc || !pNpc->IsNpc() )
    {
        return FALSE;
    }
    return strcmp( pNpc->GetLastAnimName(), szName ) == 0;
}

BOOL CServerVarInterface::CanLearnSkill( int nSkillId, int nSkillLevel )
{
    GamePlayer* pChar = (GamePlayer*)theRunTimeData.GetCharacterByID( m_nCurCharId );
    if( !pChar || !pChar->IsPlayer() )
    {
        GetErrorLog()->logString( "CServerVarInterface::CanLearnSkill error" );
        return FALSE;
    }
    return pChar->CanLearnSkill( nSkillId, nSkillLevel  );
}

bool CServerVarInterface::IsCanPet( void )
{
	GamePlayer* pChar = (GamePlayer*)theRunTimeData.GetCharacterByID( m_nCurCharId );
	if( !pChar || !pChar->IsPlayer() )
	{
		GetErrorLog()->logString( "CServerVarInterface::IsCanPet error" );
		return false;
	}

	return pChar->IsCanPet();
}
bool CServerVarInterface::DoPet(int nIndex)
{
	GamePlayer* pChar = (GamePlayer*)theRunTimeData.GetCharacterByID( m_nCurCharId );
	if( !pChar || !pChar->IsPlayer() )
		return false;

	pChar->DebugLog("Script DoPet nId:%d ", nIndex);
	return pChar->DoPet( nIndex );
}

bool CServerVarInterface::IsCanRide( void )
{
    GamePlayer* pChar = (GamePlayer*)theRunTimeData.GetCharacterByID( m_nCurCharId );
    if( !pChar || !pChar->IsPlayer() )
    {
        GetErrorLog()->logString( "CServerVarInterface::IsCanRide error" );
        return false;
    }

    return pChar->IsCanRide();
}

void CServerVarInterface::DoRide( int nId )
{
    GamePlayer* pChar = (GamePlayer*)theRunTimeData.GetCharacterByID( m_nCurCharId );
    if( !pChar || !pChar->IsPlayer() )
        return;

    pChar->DebugLog("Script DoRide nId:%d ", nId);
    pChar->DoRide( nId );
}

void CServerVarInterface::DoRideFristMount()
{
    GamePlayer* pChar = (GamePlayer*)theRunTimeData.GetCharacterByID( m_nCurCharId );
    if( !pChar || !pChar->IsPlayer() )
        return;

    pChar->DoRideFristMount();
}

void CServerVarInterface::AddSkillToFristMount( uint16 skillId, uint8 level )
{
    GamePlayer* pChar = (GamePlayer*)theRunTimeData.GetCharacterByID( m_nCurCharId );
    if( !pChar || !pChar->IsPlayer() )
        return;

    pChar->AddSkillToFristMount( skillId, level );
}

void CServerVarInterface::DoHitch( int nID, bool bBack )
{
    BaseCharacter* pChar = theRunTimeData.GetCharacterByID( m_nCurCharId );

    if( !pChar || !pChar->IsPlayer() )
    { return; }

    GamePlayer* pPlayer = (GamePlayer*)pChar;

    pPlayer->DoHitch( nID, bBack );
}
void CServerVarInterface::DoHitchByTeam(int nID,int TeamnID,bool bBack)
{
	BaseCharacter* pChar = theRunTimeData.GetCharacterByID( m_nCurCharId );
    if( !pChar || !pChar->IsPlayer() )
    { return; }

    GamePlayer* pPlayer = (GamePlayer*)pChar;
	GameTeam * pTeam = theGameTeamManager.GetTeam(pPlayer->GetTeamID());
	if(!pTeam)
		return;
	for( int i = 0; i < pTeam->TeamMemberCount(); ++i )
    {
        GamePlayer* pPlayerTeam = pTeam->GetMemberPlayer( pTeam->GetMemberIDByIndex( i ) );
        if ( pPlayerTeam == NULL || pPlayerTeam->IsDead() ) 
        { continue; }

        if( !pPlayerTeam->IsPlayer() || !pPlayer->IsInMapArea(pPlayerTeam->GetMapID(), pPlayerTeam->GetFloatX(), pPlayerTeam->GetFloatY(),TEAM_EXP_DIS) )
        { continue; }

		if(pTeam->IsTeamHeader(pPlayerTeam->GetDBCharacterID()))
			pPlayerTeam->DoHitch( nID, bBack );
		else
		{
			if(TeamnID == -1 || TeamnID == 0)
				TeamnID = nID;
			pPlayerTeam->DoHitch( TeamnID, bBack );
		}
	}
}
short CServerVarInterface::GetRideId()
{
    GamePlayer* pChar = (GamePlayer*)theRunTimeData.GetCharacterByID( m_nCurCharId );
    if( !pChar || !pChar->IsPlayer() )
    {
        return -1;
    }
    return pChar->GetRideId();
}

uint16 CServerVarInterface::GetRideLevel()
{
	GamePlayer* pChar = (GamePlayer*)theRunTimeData.GetCharacterByID( m_nCurCharId );
	if( !pChar || !pChar->IsPlayer() )
	{
		return -1;
	}
	return pChar->GetRideLevel();
}

void CServerVarInterface::SetDialogName( const char* szName )
{
    BaseCharacter* pChar = theRunTimeData.GetCharacterByID( m_nCurCharId );
    if( !pChar || !pChar->IsPlayer() )
    {
        GetErrorLog()->logString( "CServerVarInterface::SetDialogName error" );
        return;
    }
    if ( strlen(szName) <= 0 )
        return;
    MsgSetDialogName msg;
    strncpy( msg.szName, szName, MsgSetDialogName::NAME_MAXLENGTH-1 );
    GettheServer().SendMsgToSingle( &msg, pChar );
}

void CServerVarInterface::SetHotkey( int nIndex, int nID )
{
    BaseCharacter* pChar = theRunTimeData.GetCharacterByID( m_nCurCharId );
    if( !pChar || !pChar->IsPlayer() )
        return;

    if ( nIndex >= More_iHotkey )
        return;
    ItemDefine::SItemCommon* pItemCommon = GettheItemDetail().GetItemByID( nID );;
    if ( !pItemCommon )
        return;

    GamePlayer* pGamePlayer = (GamePlayer*)pChar;
    if ( !pGamePlayer )
        return;

    SHotKey* pHotkey = &pGamePlayer->gCharInfoServer.otherdata.hotkeys.itemHotKey[nIndex];

    switch( pItemCommon->ucItemType )
    {
    case ItemDefine::ITEMTYPE_RESTORE:
        {
            pHotkey->ShortCut.BagType = BagTypePack;
            pHotkey->ShortCut.BagIndex = nID;
        }
        break;
    case ItemDefine::ITEMTYPE_ACTION:
        {
            pHotkey->ShortCut.BagType = BagTypeActionUI;
            pHotkey->ShortCut.BagIndex = nID;
        }
        break;
    case ItemDefine::ITEMTYPE_SKILL:
        {
            int nSkillIndex = pGamePlayer->_SkillBag.GetSkillIndexById(nID);
            if ( nSkillIndex == -1 )
			{
				nSkillIndex = pGamePlayer->_HeroSkillBag.GetSkillIndexById( nID );
				if (nSkillIndex == -1 )
				{
					return;
				}
				pHotkey->ShortCut.BagType = BagTypeHeroSkill;
			}
			else
			{
				pHotkey->ShortCut.BagType  = BagTypeSkill;
			}
            
            pHotkey->ShortCut.BagIndex = nSkillIndex;
        }
        break;
    default:
        return;
    }

    MsgScriptSetHotkey msg;
    msg.ustIndex = nIndex;
    msg.nID = nID;
    GettheServer().SendMsgToSingle( &msg, pChar );
}

BOOL CServerVarInterface::LogInfoToDB( const char* szInfo )
{
    BaseCharacter* pChar = theRunTimeData.GetCharacterByID( m_nCurCharId );
    if( !pChar || !pChar->IsPlayer() )
        return FALSE;
    //if (g_dbchunk.SaveUserInfo(pChar->GetCharName(), szInfo))
    //    return TRUE;
    //else
    //    return FALSE;
    return TRUE;
} 

int CServerVarInterface::GetTeamPlayerCount()
{
    BaseCharacter* pChar = theRunTimeData.GetCharacterByID( m_nCurCharId );
    if( !pChar || !pChar->IsPlayer() )
    {
        GetErrorLog()->logString( "CServerVarInterface::GetTeamPlayerCount error" );
        return 1;
    }
    GameTeam* pTeam = theGameTeamManager.GetTeam( pChar->GetTeamID() );

    int nCount = 1;
    if ( pTeam != NULL )
    {
        nCount = pTeam->TeamMemberCount();
    }

    return nCount;
}

int CServerVarInterface::GetTeamID()
{
    BaseCharacter* pChar = theRunTimeData.GetCharacterByID( m_nCurCharId );
    if( !pChar || !pChar->IsPlayer() )
    {
        GetErrorLog()->logString( "CServerVarInterface::GetTeamID error" );
        return -1;
    }
    return pChar->GetTeamID();
}

int CServerVarInterface::GetTeamPlayerLevel( int nType )
{
    BaseCharacter* pChar = theRunTimeData.GetCharacterByID( m_nCurCharId );
    if( !pChar || !pChar->IsPlayer() )
    {
        GetErrorLog()->logString( "CServerVarInterface::GetTeamPlayerCount error" );
        return 0;
    }
    int nLevel = pChar->GetLevel();
    GameTeam* pTeam = theGameTeamManager.GetTeam( pChar->GetTeamID() );
    if (pTeam != NULL)
    {
        for (int i = 0; i < pTeam->TeamMemberCount(); ++i)
        {
            DWORD dwPlayerID = pTeam->GetMemberIDByIndex( i );
            GamePlayer* pTeamPlayer = theRunTimeData.GetGamePlayerByDBID(dwPlayerID);
            if( !pTeamPlayer )
                continue;
            switch( nType ) 
            {
            case 0:
                {
                    if ( pTeamPlayer->GetLevel() < nLevel )
                    {
                        nLevel = pTeamPlayer->GetLevel();
                    }
                }
                break;
            case 1:
                {
                    if ( pTeamPlayer->GetLevel() > nLevel )
                    {
                        nLevel = pTeamPlayer->GetLevel();
                    }
                }
                break;
            default:
                break;
            }
        }
    }
    return nLevel;
}

int CServerVarInterface::GetTeamAverageLevel()
{
    BaseCharacter* pChar = theRunTimeData.GetCharacterByID( m_nCurCharId );
    if( !pChar || !pChar->IsPlayer() )
    { return 0; }

    GamePlayer* pPlayer = ( GamePlayer* ) pChar;

    return pPlayer->GetPlayerEctypeMapLevel( pPlayer->GetMapID(), pPlayer->GetFloatX(), pPlayer->GetFloatY(), true );
}

int CServerVarInterface::GetTeamPlayerID( unsigned int nIndex )
{
    BaseCharacter* pChar = theRunTimeData.GetCharacterByID( m_nCurCharId );
    if( !pChar || !pChar->IsPlayer() )
    {
        GetErrorLog()->logString( "CServerVarInterface::GetTeamPlayerID error" );
        return -1;
    }
    GameTeam* pTeam = theGameTeamManager.GetTeam(pChar->GetTeamID());
    if ( pTeam != NULL )
    {
        if (nIndex < pTeam->TeamMemberCount())
        {
            return pTeam->GetMemberIDByIndex( nIndex );
        }
    }
    return -1;
}


bool CServerVarInterface::IsTeamHeader()
{
    GamePlayer* pChar = (GamePlayer*) theRunTimeData.GetCharacterByID( m_nCurCharId );
    if( pChar == NULL || !pChar->IsPlayer() )
    {
        GetErrorLog()->logString( "CServerVarInterface::IsTeamHeader error" );
        return -1;
    }

    GameTeam* pTeam = theGameTeamManager.GetTeam(pChar->GetTeamID());
    if (pTeam != NULL)
    {
        return pTeam->IsTeamHeader( pChar->GetDBCharacterID() );
    }

    return false;
}

int CServerVarInterface::AddTeamFriendly(int nValue)
{
    GamePlayer* pChar = (GamePlayer*) theRunTimeData.GetCharacterByID( m_nCurCharId );
    if( pChar == NULL || !pChar->IsPlayer() )
    {
        GetErrorLog()->logString( "CServerVarInterface::AddTeamFriendly error" );
        return -1;
    }

    GameTeam* pTeam = theGameTeamManager.GetTeam(pChar->GetTeamID());
    if (pTeam == NULL)
    {
        GetErrorLog()->logString( "CServerVarInterface::AddTeamFriendly error" );
        return -1;
    }

    pTeam->UpdateTeamFriendly( pChar, nValue );

    return 0;
}


void CServerVarInterface::SetDstPlayer( int nId )
{
    GamePlayer* pChar = (GamePlayer*)theRunTimeData.GetCharacterByID( m_nCurCharId );
    if( !pChar || !pChar->IsPlayer() )
    {
        GetErrorLog()->logString( "CServerVarInterface::SetDstPlayer error" );
        return;
    }
    pChar->SetDstPlayerId( nId );
}

void CServerVarInterface::CreateMonster( int nMapId, float fPosX, float fPosY,
                                        float fRadius, float fBodySize,
                                        int nMonsterIndex, int nMonsterNum )
{
    BaseCharacter* pChar = theRunTimeData.GetCharacterByID( GetCurCharId() );
    if ( pChar == NULL )
    {
        LOG_MESSAGE( LOGICSYSTEMOBJECT, LOG_PRIORITY_ERROR, "CServerVarInterface::CreateMonster pChar = NULL" );
        return;
    }

    MonsterCreateData xCreateData;
    xCreateData.SetMonsterID( nMonsterIndex );
    xCreateData.SetCount( nMonsterNum );
    xCreateData.SetRadius( fRadius );
    xCreateData.SetBodySize( fBodySize );
    xCreateData.SetPostionX( fPosX );
    xCreateData.SetPostionY( fPosY );
    xCreateData.SetDirX( 1.0f );
    xCreateData.SetDirY( 1.0f );
    if ( nMapId == -1 )
    {
        xCreateData.SetMapID( pChar->GetMapID() );
        if ( fPosX == -1 && fPosY == -1 )
        {
            xCreateData.SetPostionX( pChar->GetFloatX() );
            xCreateData.SetPostionY( pChar->GetFloatY() );
        }
    }
    else
    {
        MapConfig::MapData* pMapData = theMapConfig.GetMapDataById( nMapId );
        if ( pMapData == NULL )
        {
            LogMessage::LogLogicError( "CServerVarInterface::CreateMonster pMapData[0x%x] == NULL", nMapId );
            return;
        }

        if( !g_Cfg.IsMapRun( EctypeId2MapId( nMapId ) ) )
        { return; }

        if ( pMapData->IsEctypeMap() )
        { xCreateData.SetMapID( pChar->GetMapID() ); }
        else
        { xCreateData.SetMapID( nMapId ); }
    }

    MonsterCreater::ProcessCreateNormalMonster( xCreateData );
}

void CServerVarInterface::CreateSpecialMonster( int nMapId, float fPosX, float fPosY,
                                               float fRadius, float fBodySize,
                                               int nMonsterIndex, int nMonsterNum )
{    
    BaseCharacter* pChar = theRunTimeData.GetCharacterByID( GetCurCharId() );
    if ( pChar== NULL || !pChar->IsPlayer()  )
    { return; }

    GamePlayer* pPlayer = static_cast< GamePlayer* >( pChar );
    if ( fPosX == -1 && fPosY == -1 )
    {
        fPosX = pChar->GetFloatX(); 
        fPosY = pChar->GetFloatY();
    }

    MonsterCreateData xCreateData;
    xCreateData.SetMonsterID( nMonsterIndex );
    xCreateData.SetCount( nMonsterNum );
    xCreateData.SetRadius( fRadius );
    xCreateData.SetBodySize( fBodySize );
    xCreateData.SetMapID( pPlayer->GetMapID() );
    xCreateData.SetPostionX( fPosX );
    xCreateData.SetPostionY( fPosY );
    xCreateData.SetSpecialType( MonsterDefine::SpecialPlayerVar );
    xCreateData.SetSpecialValue( pPlayer->GetDBCharacterID() );
    MonsterCreater::ProcessCreateSpecialMonster( xCreateData );
}

void CServerVarInterface::CreateRouteMonster( int nMapId, float fPosX, float fPosY, float fRadius, int nMonsterIndex, int nRouteID )
{
    BaseCharacter* pChar = theRunTimeData.GetCharacterByID( GetCurCharId() );
    if ( pChar == NULL )
    {
        LOG_MESSAGE( LOGICSYSTEMOBJECT, LOG_PRIORITY_ERROR, "CServerVarInterface::CreateMonster pChar = NULL" );
        return;
    }

    MonsterCreateData xCreateData;
    xCreateData.SetMonsterID( nMonsterIndex );
    xCreateData.SetCount( 1 );
    xCreateData.SetRadius( fRadius );
    xCreateData.SetPostionX( fPosX );
    xCreateData.SetPostionY( fPosY );
    xCreateData.SetDirX( 1.0f );
    xCreateData.SetDirY( 1.0f );
    xCreateData.SetRouteID( nRouteID );

    if ( nMapId == -1 )
    {
        xCreateData.SetMapID( pChar->GetMapID() );
        if ( fPosX == -1 && fPosY == -1 )
        {
            xCreateData.SetPostionX( pChar->GetFloatX() );
            xCreateData.SetPostionY( pChar->GetFloatY() );
        }
    }
    else
    {
        MapConfig::MapData* pMapData = theMapConfig.GetMapDataById( nMapId );
        if ( pMapData == NULL )
        {
            LogMessage::LogLogicError( "CServerVarInterface::CreateMonster pMapData[0x%x] == NULL", nMapId );
            return;
        }

        if( !g_Cfg.IsMapRun( EctypeId2MapId( nMapId ) ) )
        { return; }

        if ( pMapData->IsEctypeMap() )
        { xCreateData.SetMapID( pChar->GetMapID() ); }
        else
        { xCreateData.SetMapID( nMapId ); }
    }

    MonsterCreater::ProcessCreateNormalMonster( xCreateData );
}

void CServerVarInterface::CreateMonsterEx( int nMapId, float fPosX, float fPosY, float fRadius, 
                                          int nMonsterIndex, int nFightCamp, int nForce, int nRouteID, int nCountry )
{
    BaseCharacter* pChar = theRunTimeData.GetCharacterByID( GetCurCharId() );
    if ( pChar == NULL )
    {
        LOG_MESSAGE( LOGICSYSTEMOBJECT, LOG_PRIORITY_ERROR, "CServerVarInterface::CreateMonster pChar = NULL" );
        return;
    }

    MonsterCreateData xCreateData;
    xCreateData.SetMonsterID( nMonsterIndex );
    xCreateData.SetRadius( fRadius );
    xCreateData.SetPostionX( fPosX );
    xCreateData.SetPostionY( fPosY );
    xCreateData.SetDirX( 1.0f );
    xCreateData.SetDirY( 1.0f );
    xCreateData.SetFightCamp( nFightCamp );
    xCreateData.SetForce( nForce );
    xCreateData.SetRouteID( nRouteID );
	xCreateData.SetCountry( nCountry );

    if ( nMapId == -1 )
    {
        xCreateData.SetMapID( pChar->GetMapID() );
        if ( fPosX == -1 && fPosY == -1 )
        {
            xCreateData.SetPostionX( pChar->GetFloatX() );
            xCreateData.SetPostionY( pChar->GetFloatY() );
        }
    }
    else
    {
        MapConfig::MapData* pMapData = theMapConfig.GetMapDataById( nMapId );
        if ( pMapData == NULL )
        {
            LogMessage::LogLogicError( "CServerVarInterface::CreateMonster pMapData[0x%x] == NULL", nMapId );
            return;
        }

        if( !g_Cfg.IsMapRun( EctypeId2MapId( nMapId ) ) )
        { return; }

        if ( pMapData->IsEctypeMap() )
        { xCreateData.SetMapID( pChar->GetMapID() ); }
        else
        { xCreateData.SetMapID( nMapId ); }
    }

    MonsterCreater::ProcessCreateNormalMonster( xCreateData );
}

void CServerVarInterface::CreateSpecialMonsterEx( int nMapId, float fPosX, float fPosY, float fRadius, 
                                                 int nMonsterIndex, int nFightCamp, int nForce, int nRouteID )
{    
    BaseCharacter* pChar = theRunTimeData.GetCharacterByID( GetCurCharId() );
    if ( pChar== NULL || !pChar->IsPlayer()  )
    { return; }

    GamePlayer* pPlayer = static_cast< GamePlayer* >( pChar );
    if ( fPosX == -1 && fPosY == -1 )
    {
        fPosX = pChar->GetFloatX();
        fPosY = pChar->GetFloatY();
    }

    MonsterCreateData xCreateData;
    xCreateData.SetMonsterID( nMonsterIndex );
    xCreateData.SetRadius( fRadius );
    xCreateData.SetMapID( pPlayer->GetMapID() );
    xCreateData.SetPostionX( fPosX );
    xCreateData.SetPostionY( fPosY );
    xCreateData.SetFightCamp( nFightCamp );
    xCreateData.SetForce( nForce );
    xCreateData.SetRouteID( nRouteID );
    xCreateData.SetSpecialType( MonsterDefine::SpecialPlayerVar );
    xCreateData.SetSpecialValue( pPlayer->GetDBCharacterID() );
    MonsterCreater::ProcessCreateSpecialMonster( xCreateData );
}

int CServerVarInterface::GetNullItemCount( unsigned short usItemBagItem )
{
    GamePlayer* pChar = (GamePlayer*)theRunTimeData.GetCharacterByID( m_nCurCharId );
    if ( !pChar || !pChar->IsPlayer() )
    {    
        return 0;
    }
    return pChar->GetNullItemCount( usItemBagItem );
}

void CServerVarInterface::Sleep( DWORD dwTime )
{
    GamePlayer* pPlayer = NULL;
    pPlayer = (GamePlayer*)theRunTimeData.GetCharacterByID( GetCurCharId() );
    if ( !pPlayer || !pPlayer->IsPlayer() )
    {
        return;
    }
    pPlayer->SetScriptSleepTime( dwTime );
}

void CServerVarInterface::CallScript( const char* szFileName, int nEnterId, GameObjectId nPlayerId, bool bDbId )
{ // CallScript Data\Script\Quest\Quest4982.script 1 -1 注意
    if ( !szFileName )
    { return; }

    GameObjectId  nId = -1;
    if ( nPlayerId == -1 )
    { 
        nId   = GetCurCharId();
        bDbId = false;
    }
    else
    {
        nId = nPlayerId;
    }

    GamePlayer* pGamePlayer = NULL;

    if ( bDbId )
    { pGamePlayer = theRunTimeData.GetGamePlayerByDBID( nId );}
    else
    { pGamePlayer = (GamePlayer*)theRunTimeData.GetCharacterByID( nId );   }

    if ( !pGamePlayer || !pGamePlayer->IsPlayer() )
    { return; }

    std::string strScriptPath = SCRIPT_ROOTDIRECTORY;
    strScriptPath += szFileName;

    int nVMId = GetScriptMgr()->CreateVM( ST_NPC, strScriptPath.c_str(), -1 );
    if ( nVMId == -1 )
    {
        LOG_MESSAGE(SYSTEMOBJECT, LOG_PRIORITY_ERROR,"Error:CServerVarInterface::CallScript(%s)", szFileName );
        return;
    }
    GetScriptMgr()->StartupVM( ST_NPC, nVMId, pGamePlayer, false, nEnterId, GetDstId() );
}

void CServerVarInterface::CloseDlg()
{
    BaseCharacter* pChar = NULL;
    pChar = theRunTimeData.GetCharacterByID( GetCurCharId() );
    if ( !pChar || !pChar->IsPlayer() )
    {
        return;
    }
    MsgAckScript msg;
    msg.byType = MsgAckScript::eCloseDlg;
    msg.stNpcId = m_nDstId;
    msg.SetString( "" );
    GettheServer().SendMsgToSingle( &msg, pChar );
}

int CServerVarInterface::GetMapId()
{
    BaseCharacter* pChar = NULL;
    pChar = theRunTimeData.GetCharacterByID( GetCurCharId() );
    if ( !pChar || !pChar->IsPlayer() )
    {
        return -1;
    }
    return EctypeId2MapId( pChar->GetMapID() );
}

bool CServerVarInterface::IsInZone( const char* pszName )
{
    if ( !pszName )
    {
        return false;
    }
    BaseCharacter* pChar = NULL;
    pChar = theRunTimeData.GetCharacterByID( GetCurCharId() );
    if ( !pChar || !pChar->IsPlayer() )
    {
        return false;
    }
    GamePlayer* pPlayer = (GamePlayer*)pChar;
    int nZoneID = pPlayer->GetCurZoneID();
    if ( nZoneID == -1 )
    {
        return false;
    }
    GameStage *pStage = NULL;
    pStage = theGameWorld.GetStageById( pPlayer->GetMapID() );
    if ( !pStage )
    {
        return false;
    }
    GameZone *pZone = NULL;
    pZone = pStage->GetZone( nZoneID );
    if ( !pZone )
    {
        return false;
    }
    return stricmp( pszName, pZone->GetZoneName() ) == 0;
}

void CServerVarInterface::PlayEffect( const char* pszName, float fX, float fY, float fZ, bool bIsCast )
{
    if ( pszName == NULL || pszName[0] == 0 )
    { return; }

    MsgPlayEffect msg;
    msg.nPlayerId = -1;
    HelperFunc::SafeNCpy( msg.szFileName, pszName, MsgPlayEffect::eMaxFileName );

    msg.fX = fX;
    msg.fY = fY;
    msg.fZ = fZ;

    BaseCharacter* pBaseChar = theRunTimeData.GetCharacterByID( GetCurCharId() );   // 得到当前的玩家
    if ( pBaseChar == NULL )
    { return; }

    if ( fX == 0.0f && fY == 0.0f && fZ == 0.0f )     // 如果使用自己的坐标
    {
        msg.fX = pBaseChar->GetFloatX();
        msg.fY = pBaseChar->GetFloatY();
        msg.fZ = pBaseChar->GetFloatZ();
        msg.nPlayerId = GetCurCharId();         // 以角色为主
    }

    if (bIsCast)
    {
        GettheServer().SendMsgToView( &msg, GetCurCharId(), false );   // 广播给所有
    }
    else
    {
        GettheServer().SendMsgToSingle(&msg, pBaseChar);    // 广播给某个玩家
    }    
}

void CServerVarInterface::ShowIntonateBar( DWORD dwTime, int nStringID, int nActionID, int nType, int nID )
{
    BaseCharacter* pChar = NULL;
    pChar = theRunTimeData.GetCharacterByID( GetCurCharId() );
    if ( !pChar || !pChar->IsPlayer() )
    {
        return;
    }
    GamePlayer* pPlayer = (GamePlayer*)pChar;
	if(pPlayer->GetStatus() == CS_INTONATE)
	{
		//当前有吟唱技能 我们打断吟唱
		pPlayer->IntonateInterrupt( ItemDefine::EIT_Normal, __FUNCTION__ );
	}
    pPlayer->SetScriptSleepTime( dwTime );
    MsgShowIntonateBar msg;
    msg.header.stID = pPlayer->GetID();
    msg.dwTime      = dwTime;
    msg.nStringID   = nStringID;
    msg.nActionID   = nActionID;
    msg.nType       = nType;
    msg.nID         = nID;
    GettheServer().SendMsgToView( &msg, pPlayer->GetID(), false );

    pPlayer->SetCurActionId( nActionID );
    pPlayer->SetCurActionPlayTime( dwTime );

	pPlayer->SetScriptStatesID(GamePlayer::EScriptStates_OnDead);//设置死亡打断
}

void CServerVarInterface::AddPkValue(int nValue,bool dailypkvale)
{
    BaseCharacter* pChar = NULL;
    pChar = theRunTimeData.GetCharacterByID( GetCurCharId() );
    if ( !pChar || !pChar->IsPlayer() )
    {
        return;
    }
    GamePlayer* pPlayer = (GamePlayer*)pChar;

    //if (nValue > 0 && pPlayer->m_cFightStatus.IsCalcDailyPkValue())
    //{
    //    if (dailypkvale)
    //    {
    //        nValue = pPlayer->CheckPlayerPkValueDaily(nValue);
    //    }        
    //}

    pPlayer->SetPKValue( nValue, PKValueOp_Add );
}

void CServerVarInterface::DecPkValue(int nValue)
{
    BaseCharacter* pChar = NULL;
    pChar = theRunTimeData.GetCharacterByID( GetCurCharId() );
    if ( !pChar || !pChar->IsPlayer() )
    {
        return;
    }
    GamePlayer* pPlayer = (GamePlayer*)pChar;

    //if (nValue < 0 && pPlayer->m_cFightStatus.IsCalcDailyPkValue())
    //{
    //    nValue = pPlayer->CheckPlayerPkValueDaily(nValue);
    //}

    pPlayer->SetPKValue( nValue, PKValueOp_Reduce );
}

void CServerVarInterface::SetPkValue(int nValue)
{    
    BaseCharacter* pChar = NULL;
    pChar = theRunTimeData.GetCharacterByID( GetCurCharId() );
    if ( !pChar || !pChar->IsPlayer() )
    {
        return;
    }
    GamePlayer* pPlayer = (GamePlayer*)pChar;
    pPlayer->SetPKValue( nValue, PKValueOp_Set );
}

int CServerVarInterface::GetPkValue()
{
    BaseCharacter* pChar = NULL;
    pChar = theRunTimeData.GetCharacterByID( GetCurCharId() );
    if ( !pChar || !pChar->IsPlayer() )
    {
        return 0;
    }
    GamePlayer* pPlayer = (GamePlayer*)pChar;
    return pPlayer->GetPKValue();
}

int CServerVarInterface::GetPkState()
{
    BaseCharacter* pChar = NULL;
    pChar = theRunTimeData.GetCharacterByID( GetCurCharId() );
    if ( !pChar || !pChar->IsPlayer() )
    {
        return 0;
    }
    GamePlayer* pPlayer = (GamePlayer*)pChar;
    return pPlayer->GetPKValue();
}

int CServerVarInterface::GetPkMode()
{
    BaseCharacter* pChar = NULL;
    pChar = theRunTimeData.GetCharacterByID( GetCurCharId() );
    if ( !pChar || !pChar->IsPlayer() )
    {
        return 0;
    }
    GamePlayer* pPlayer = (GamePlayer*)pChar;
    return pPlayer->GetPKMode();
}

bool CServerVarInterface::SetPkMode(int nMode)
{
    BaseCharacter* pChar = NULL;
    pChar = theRunTimeData.GetCharacterByID( GetCurCharId() );
    if ( !pChar || !pChar->IsPlayer() )
    {
        return 0;
    }
    GamePlayer* pPlayer = (GamePlayer*)pChar;
    return pPlayer->GMSetPKMode(nMode);
}

//void    CServerVarInterface::OpenStoryBook( int nValue )
//{
//    BaseCharacter* pChar = NULL;
//    pChar = theRunTimeData.GetCharacterByID( GetCurCharId() );
//    if ( !pChar || !pChar->IsPlayer() )
//    {
//        return;
//    }
//    MsgOpenStoryBook _MsgOpenStoryBook;
//    _MsgOpenStoryBook.isOpenIt = nValue;
//    GettheServer().SendMsgToSingle( &_MsgOpenStoryBook, pChar );
//}
//
//void    CServerVarInterface::OpenTgaIconDlg( int nValue)
//{
//    BaseCharacter* pChar = NULL;
//    pChar = theRunTimeData.GetCharacterByID( GetCurCharId() );
//    if ( !pChar || !pChar->IsPlayer() )
//    {
//        return;
//    }
//    MsgOpenTgaIconDlg _MsgOpenTgaIconDlg;
//    _MsgOpenTgaIconDlg.isOpenIt = (BOOL)nValue;
//    GettheServer().SendMsgToSingle( &_MsgOpenTgaIconDlg, pChar );
//}


// 结婚
void    CServerVarInterface::NotarizationSuccess( int nMember1,int nMember2,int nValue)
{
    //BaseCharacter* pChar1 = NULL;
    //BaseCharacter* pChar2 = NULL;
    //pChar1 = theRunTimeData.GetCharacterByID( nMember1 );
    //if( NULL == pChar1 )
    //    return;
    //if( !pChar1->IsPlayer() )
    //    return;
    //GamePlayer* pPlayer1 = (GamePlayer*)pChar1;
    //pChar2 = theRunTimeData.GetCharacterByID( nMember2 );
    //if ( !pChar2 || !pChar2->IsPlayer() )
    //{
    //    return;
    //}
    //GamePlayer* pPlayer2 = (GamePlayer*)pChar2;
    //if ( nMember1 == nMember2)
    //{
    //    return;
    //}
    //if (nValue == eSTP_Marriage && pPlayer1->GetSex() == pPlayer2->GetSex())
    //{
    //    return;
    //}
    //MsgReqAddFriend _AddFriend;
    //_AddFriend.eSType = (eSocialityType)nValue;
    //strncpy(_AddFriend.szName, pPlayer2->GetCharName(), sizeof(_AddFriend.szName)-1);
    //pPlayer1->OnAddFriend(&_AddFriend);
}

void    CServerVarInterface::NoticeNotarizationResult(GameObjectId iPlayer1,const char *pszAnd,GameObjectId iPlayer2,const char *pszText,int nMapId, int nX, int nY,DWORD time, DWORD color)
{
    BaseCharacter* pChar1 = NULL;
    BaseCharacter* pChar2 = NULL;
    pChar1 = theRunTimeData.GetCharacterByID( iPlayer1 );
    if ( !pChar1 || !pChar1->IsPlayer() )
    {
        return;
    }
    GamePlayer* pPlayer1 = (GamePlayer*)pChar1;
    pChar2 = theRunTimeData.GetCharacterByID( iPlayer2 );
    if ( !pChar2 || !pChar2->IsPlayer() )
    {
        return;
    }
    GamePlayer* pPlayer2 = (GamePlayer*)pChar2;
    if ( iPlayer1 == iPlayer2/* || pPlayer1->GetSex() == pPlayer2->GetSex()*/)
    {
        return;
    }
    std::string    strBuff;
    strBuff = pPlayer1->GetCharName();
    strBuff += pszAnd;
    strBuff += pPlayer2->GetCharName();
    strBuff += pszText;
    //TalkToArea( nMapId,nX,nY,time,color, strBuff.c_str() );
    TalkToAll(/*time,*/color, strBuff.c_str());
}


void CServerVarInterface::OpenClientUI(int UIFlag, int openType/* = 0*/, int64 openParam /*= 0 */)
{
    BaseCharacter* pChar = NULL;
    pChar = theRunTimeData.GetCharacterByID( GetCurCharId() );
    if ( !pChar || !pChar->IsPlayer() )
    { return; }

    MsgOpenUI _MsgOpenUI;
    _MsgOpenUI.UIFlag    = UIFlag;
    _MsgOpenUI.openType  = openType;
    _MsgOpenUI.openParam = openParam;
    GettheServer().SendMsgToSingle( &_MsgOpenUI, pChar );
}

bool    CServerVarInterface::IsEverybodyAllReady(GameObjectId iPlayerId,int nValue)
{
    bool    bIsPlayerTeam = false;
    iPlayerId = GetCurCharId();
    BaseCharacter* pChar = theRunTimeData.GetCharacterByID( iPlayerId );
    if( !pChar || !pChar->IsPlayer() )
    {
        GetErrorLog()->logString( "CServerVarInterface::IsEverybody error" );
        return false;
    }
    GamePlayer* pPlayer = (GamePlayer*)pChar;
    //Team * pTeam = NULL;
    //pTeam = GetTeamManager().GetTeam( pGamePlayer->GetTeamID() );
    //TeamEx* pTeam = theTeamManager.GetTeam(pGamePlayer->GetTeamID());
    //if (pTeam != NULL)
    //{
    //    //int iTeamNumber = pTeam->GetTeamNumber();
    //    int nCount = pTeam->TeamMemberCount();
    //    vector<std::string> VTeamName;
    //    vector<GamePlayer*> VPlayerChar;
    //    //for (unsigned int i = 0; i < iTeamNumber; i++)
    //    for (int i = 0; i < nCount; ++i)
    //    {
    //        //short id = pTeam->GetTeamMemberID(i);
    //        //BaseCharacter* pChar1 = theRunTimeData.GetCharacterByID( id );
    //        DWORD dwPlayerID = pTeam->GetTeamMemberDataBaseIdByIndex(i);
    //        BaseCharacter* pChar1 = theRunTimeData.GetGamePlayerByDBID(dwPlayerID);
    //        if( !pChar1 || !pChar1->IsPlayer() )
    //        {
    //            return false;
    //        }
    //        GamePlayer* pPlayer1 = (GamePlayer*)pChar1;
    //        if (pPlayer1)
    //        {
    //            //std::string name = pPlayer1->GetCharName();
    //            //VTeamName.push_back(name);
    //            VPlayerChar.push_back(pPlayer1);
    //        }
    //    }
    //    for (int x = 0; x < VPlayerChar.size(); x++)
    //    {
    //        for (int y = 0; y < VPlayerChar.size(); y++)
    //        {
    //            if (VPlayerChar[x] != VPlayerChar[y])
    //            {
    //                SSocietyRelation* ptj = NULL;
    //                ptj = VPlayerChar[x]->GetFriendInfoByName(VPlayerChar[y]->GetCharName());
    //                if (ptj)
    //                {
    //                    if (nValue)
    //                    {
    //                        if (nValue == 1)
    //                        {
    //                            if (ptj->Stype & BinaryFlag(nValue))
    //                            {
    //                                bIsPlayerTeam = true;
    //                            }else{
    //                                return false;
    //                            }
    //                        }
    //                        if (nValue == 2)
    //                        {
    //                            if (ptj->Stype & BinaryFlag(nValue))
    //                            {
    //                                return    false;
    //                            }else{
    //                                bIsPlayerTeam = true;
    //                            }
    //                        }
    //                    }else{
    //                        bIsPlayerTeam = true;
    //                    }
    //                }else{
    //                    return false;
    //                }
    //            }
    //        }
    //    }
    //}
    //return bIsPlayerTeam;
    return false;
}

bool CServerVarInterface::IsEverybodyAllHere()
{
    BaseCharacter* pNpcChar = theRunTimeData.GetCharacterByID( GetDstId() );
    if ( pNpcChar == NULL || !pNpcChar->IsNpc() )
    { return false; }

    BaseCharacter* pChar = theRunTimeData.GetCharacterByID(GetCurCharId());
    if ( pChar == NULL || !pChar->IsPlayer() )
    { return false; }

    GameTeam* pTeam = theGameTeamManager.GetTeam( pChar->GetTeamID() );
    if ( pTeam == NULL )
    { return false; }

    for ( int i = 0; i < pTeam->TeamMemberCount(); ++i )
    {
        GamePlayer* pTeamPlayer = theRunTimeData.GetGamePlayerByDBID( pTeam->GetMemberIDByIndex( i ) );
        if ( pTeamPlayer == NULL )
        { return false; }

        if ( !pTeamPlayer->IsInMapArea( pNpcChar->GetMapID(), pNpcChar->GetFloatX(), pNpcChar->GetFloatY(), 10.f ) )
        { return false; }
    }

    return true;
}

int CServerVarInterface::GetBagSize( int bagType )
{
    BaseCharacter* pChar = theRunTimeData.GetCharacterByID( GetCurCharId() );
    if ( !pChar || !pChar->IsPlayer() )
    { return 0;}

    GamePlayer* pGamePlayer = (GamePlayer*)pChar;

    int nCount = 0;
    switch ( bagType )
    {
    case BT_NormalItemBag:
        nCount = pGamePlayer->GetNormalBagSize();
        break;
    case BT_MaterialBag:
        nCount = pGamePlayer->GetMaterialBagSize();
        break;
    case BT_TaskBag:
        nCount = pGamePlayer->GetTaskBagSize();
        break;
    }

    return nCount;
}

void CServerVarInterface::AddBagSize( int bagType, int nSize )
{
    BaseCharacter* pChar = theRunTimeData.GetCharacterByID( GetCurCharId() );
    if ( !pChar || !pChar->IsPlayer() )
    { return; }
    GamePlayer* pPlayer = (GamePlayer*)pChar;
    switch ( bagType )
    {
    case BT_NormalItemBag:
        pPlayer->AddNormalBagNowSize( nSize );
        break;
    case BT_MaterialBag:
        pPlayer->AddMaterialBagNowSize( nSize );
        break;
    default:
        return;
        break;
    }
}



BOOL CServerVarInterface::IsMapActive( int nMapId )
{
    BaseCharacter* pChar = theRunTimeData.GetCharacterByID( GetCurCharId() );

    if ( pChar == NULL || !pChar->IsPlayer() )
        return FALSE;

    MapConfig::MapData* pMapData = theMapConfig.GetMapDataById( EctypeId2MapId(nMapId) );
    if ( !pMapData )
        return FALSE;

    DWORD dwMapId = theGameWorld.MakeEctypeStageID( pMapData, pChar );

    // 查找是否已有此副本
    GameStage* pStage = theGameWorld.GetStageById( dwMapId );

    return ( pStage != NULL );
}

int CServerVarInterface::GetMapCount( DWORD dwId )
{
    return theGameWorld.GetMapCount( dwId );
}

void CServerVarInterface::GetOfflineHookExp(uint8 nHookLevel)
{
    BaseCharacter* pChar = theRunTimeData.GetCharacterByID( GetCurCharId() );
    if ( !pChar || !pChar->IsPlayer() )
    { return; }

    static_cast<GamePlayer*>(pChar)->GetOfflineHookExp(nHookLevel);
}

bool CServerVarInterface::IsOfflinePassOneWeek()
{
    BaseCharacter* pChar = theRunTimeData.GetCharacterByID( GetCurCharId() );
    if ( !pChar || !pChar->IsPlayer() )
    { return false; }
    
    GamePlayer* pPlayer = static_cast<GamePlayer*>(pChar);
    
    return pPlayer->IsPassSunday( pPlayer->GetTimeVar( ECT_ExploitTime ) );
}

bool CServerVarInterface::AddSysDoubleExpTime( int nValue )
{
    BaseCharacter* pChar = theRunTimeData.GetCharacterByID( GetCurCharId() );
    if ( !pChar || !pChar->IsPlayer() )
    { return false; }

    return static_cast<GamePlayer*>(pChar)->AddSysDoubleExpTime( nValue );
}

bool CServerVarInterface::AddItemDoubleExpTime( int nValue )
{
    BaseCharacter* pChar = theRunTimeData.GetCharacterByID( GetCurCharId() );
    if ( !pChar || !pChar->IsPlayer() )
    { return false; }

    return static_cast<GamePlayer*>(pChar)->AddItemDoubleExpTime( nValue );
}

// 创建保护对象
void CServerVarInterface::CreateProtectChar( int monsterId, int varId, bool isCanRide )
{
    BaseCharacter* pChar = theRunTimeData.GetCharacterByID( GetCurCharId() );
    if ( !pChar || !pChar->IsPlayer() )
    { return; }

    GamePlayer* pPlayer = (GamePlayer*)pChar;

    pPlayer->CreateProtectMonster( monsterId, varId, isCanRide );
}

// 创建保护对象
void CServerVarInterface::LostProtectChar()
{
    BaseCharacter* pChar = NULL;
    pChar = theRunTimeData.GetCharacterByID( GetCurCharId() );
    if ( !pChar || !pChar->IsPlayer() )
    {
        return;
    }
    GamePlayer* pPlayer = (GamePlayer*)pChar;
    pPlayer->KillProtectChar();
}

// 获得保护对象的怪物索引
int CServerVarInterface::GetProtectCharMonsterIndex()
{
    BaseCharacter* pChar = NULL;
    pChar = theRunTimeData.GetCharacterByID( GetCurCharId() );
    if ( !pChar || !pChar->IsPlayer() )
    {
        return -1;
    }
    GamePlayer* pPlayer = (GamePlayer*)pChar;
    return pPlayer->GetProtectCharMonsterId();
}

int CServerVarInterface::GetRankLevel(int index)
{
    GameObjectId iplayerid = GetCurCharId();
    BaseCharacter* pChar = theRunTimeData.GetCharacterByID(iplayerid);
    if(!pChar)
        return 0;
    GamePlayer* pPlayer = (GamePlayer*)pChar;
    if (pPlayer)
    {
        //return pPlayer->gCharInfoServer.baseinfo.liveinfo.sRankMgr.Read(index-1);
    }
    return 0;
}

bool CServerVarInterface::IsHaveStatus( short shStatusID )
{
    BaseCharacter* pChar = theRunTimeData.GetCharacterByID( GetCurCharId() );
    if ( !pChar || !pChar->IsPlayer() )
    { return 0; }

    return pChar->_buffManager.IsHaveStatus(shStatusID);
}

void CServerVarInterface::AddPlayerIntegralMax( int nSize )
{
    //BaseCharacter* pChar = NULL;
    //pChar = theRunTimeData.GetCharacterByID( GetCurCharId() );
    //if ( !pChar || !pChar->IsPlayer() )
    //    return;

    //GamePlayer* pPlayer = (GamePlayer*)pChar;
    //pPlayer->UpdateEnergyMax( pPlayer->GetLevel(),nSize );
}

bool CServerVarInterface::IsThisItemEquipped_Byid(unsigned short ustItemId)
{
    BaseCharacter* pChar = theRunTimeData.GetCharacterByID( m_nCurCharId );
    if ( !pChar || !pChar->IsPlayer() )
    {
        return false;
    }
    ItemDefine::SItemCommon *pItem = NULL;
    pItem = GettheItemDetail().GetItemByID(ustItemId);
    if( !pItem )
        return false;
    return ((GamePlayer*)pChar)->Script_IsThisItemEquipped( pItem->ustItemID);
}

int CServerVarInterface::HaveThisItem_Byid( unsigned short ustItemId)
{
    BaseCharacter* pChar = theRunTimeData.GetCharacterByID( m_nCurCharId );
    if ( !pChar || !pChar->IsPlayer() )
    { return 0; }

    GamePlayer* pGamePlayer = (GamePlayer*) pChar;
    if ( !pGamePlayer)
    { return 0; }

    int nItemCount = pGamePlayer->GetItemCount( ustItemId );
    /*if ( nItemCount == 0 )
    { nItemCount = pGamePlayer->IsHaveEquipItem(ustItemId); }*/
 
    return nItemCount;
}

void CServerVarInterface::RemoveThisItem_Byid( unsigned short ustItemid, int iNumber )
{
    BaseCharacter* pChar = theRunTimeData.GetCharacterByID( m_nCurCharId );
    if ( pChar == NULL || !pChar->IsPlayer() )
    { return; }

    GamePlayer* pPlayer = static_cast< GamePlayer* >( pChar );

    // iNumber -1 时候 会在RemoveItem的第二个参数做无符号强转,做全删除逻辑
	//LYH日志添加

	ItemDefine::SItemCommon* _pitem = GettheItemDetail().GetItemByID(ustItemid);
	SCharItem *_item = pPlayer->GetBagItemByGuid(pPlayer->GetItemGUIDByItemID(ustItemid));
	if(_pitem && _item)
	theLogEventService.LogItemConsume(pPlayer->GetAccountID(),pPlayer->GetDBCharacterID(),ustItemid,(unsigned short)iNumber,pPlayer->GetItemGUIDByItemID(ustItemid),
	_item->GetItemCount()-(unsigned short)iNumber >= 0 ? _item->GetItemCount()-(unsigned short)iNumber : 0,eItemLogInfo_ItemConsume_Script,
	                                  pPlayer->GetCharName(),_pitem->GetItemName());

    if ( !pPlayer->RemoveItem( ustItemid, iNumber ) ) 
		//if (!pPlayer->RemoveItem(pPlayer->GetUseItemInfo().uchItemBagType,pPlayer->GetUseItemInfo().stIndex,iNumber,pPlayer->GetUseItemInfo().nGuid))
    {
        // 移除失败,终止脚本
        pPlayer->CancelCurScript( __FILE__, __FUNCTION__ ); // 不能终止脚本, 后面可能还有需要执行
	}
}

void CServerVarInterface::GetPlayerCountVar( int nQuestID, int nVarID )
{
    GameObjectId iCharID = GetCurCharId();
    BaseCharacter* pChar = theRunTimeData.GetCharacterByID( iCharID );

    if( pChar && pChar->IsPlayer() )
    {
        GamePlayer* pPlayer = (GamePlayer*)pChar;
        //pPlayer->SetVar( nVarId, pPlayer->Script_GetQuestState( nQuestId ) );
        pPlayer->Script_GetPlayerCountVar( nQuestID, nVarID );
    }
}

int CServerVarInterface::GetStorageItemGrid ()
{
    BaseCharacter* pChar = theRunTimeData.GetCharacterByID( GetCurCharId() );
    if( pChar && pChar->IsPlayer() )
    {
        GamePlayer* pPlayer = (GamePlayer*)pChar;
        return pPlayer->gCharInfoServer.baseinfo.liveinfo.nStorageItemGrid;
    }
    return 0;
}

int CServerVarInterface::GetStorageMountGrid()
{
    BaseCharacter* pChar = theRunTimeData.GetCharacterByID( GetCurCharId() );
    if( pChar && pChar->IsPlayer() )
    {
        GamePlayer* pPlayer = (GamePlayer*)pChar;
        return pPlayer->gCharInfoServer.baseinfo.liveinfo.nStorageMountGrid;
    }
    return 0;
}

bool CServerVarInterface::AddStorageItemGrid(unsigned char nValue)
{
    BaseCharacter* pChar = theRunTimeData.GetCharacterByID( GetCurCharId() );
    if( pChar && pChar->IsPlayer() )
    {
        GamePlayer* pPlayer = (GamePlayer*)pChar;
        return pPlayer->AddStorageItemGrid( nValue);
    }
    return false;
}

bool CServerVarInterface::AddStorageMountGrid(unsigned char nValue)
{
    BaseCharacter* pChar = theRunTimeData.GetCharacterByID( GetCurCharId() );
    if( pChar && pChar->IsPlayer() )
    {
        GamePlayer* pPlayer = (GamePlayer*)pChar;
        return pPlayer->AddStorageMountGrid( nValue);
    }
    return false;
}

void CServerVarInterface::UpdatePkValueMaxDaily(int offset)
{
    BaseCharacter* pChar = theRunTimeData.GetCharacterByID( GetCurCharId() );
    if( pChar && pChar->IsPlayer() )
    {
        GamePlayer* pPlayer = (GamePlayer*)pChar;
    }
}

void CServerVarInterface::InsertDelayScript(int delaytime,int scriptindex,bool forplayer)
{
    uint32 dwnowtime = HQ_TimeGetTime();
    uint32 dwdelaytime = delaytime*1000;

    CScriptMgr::SDelayTimeScript delayTimeScript;
    delayTimeScript.delaytime    = dwdelaytime;
    delayTimeScript.starttime    = dwnowtime;
    delayTimeScript.script_index = scriptindex;

    if ( forplayer )
    {
        BaseCharacter* pChar = theRunTimeData.GetCharacterByID( GetCurCharId() );
        if ( NULL == pChar )
        { return; }

        GamePlayer* pPlayer = NULL;
        if ( pChar->IsPlayer() )
        { pPlayer = (GamePlayer*)pChar; }
        else
        { return; }

        delayTimeScript.playerdbid = pPlayer->GetDBCharacterID();
    }
    else
    { delayTimeScript.playerdbid = 0; }

    GetScriptMgr()->InsertDelayTime( delayTimeScript );
}

void CServerVarInterface::ScriptLog(const char* pszKeyWord,const char* pszContent)
{
    BaseCharacter* pChar = theRunTimeData.GetCharacterByID( GetCurCharId() );
    if ( !pChar )
        return;

    GamePlayer* pPlayer = NULL;
    if ( pChar->IsPlayer() )
    {
        pPlayer = (GamePlayer*)pChar;
        pPlayer->Log("%s %s", pszKeyWord, pszContent);
    }
}

void CServerVarInterface::RemoveDelayScript(int scriptindex,bool forplayer)
{
    DWORD playerdbid = 0;
    if (forplayer)
    {
        BaseCharacter* pChar = NULL;
        pChar = theRunTimeData.GetCharacterByID( GetCurCharId() );
        if ( !pChar )
            return;

        GamePlayer* pPlayer = NULL;
        if ( pChar->IsPlayer() )
        {
            pPlayer = (GamePlayer*)pChar;
        }

        playerdbid = pPlayer->GetDBCharacterID();
    }
    else
    {
        playerdbid = 0;
    }
    GetScriptMgr()->RemoveDelayScript(scriptindex,playerdbid);
}

void CServerVarInterface::ShowTimeTop(DWORD showtime)
{
    {
        if (showtime == 0)
        {
            return;
        }

        BaseCharacter* pChar = NULL;
        pChar = theRunTimeData.GetCharacterByID( GetCurCharId() );
        if ( !pChar )
            return;

        GamePlayer* pPlayer = NULL;
        if ( pChar->IsPlayer() )
        {
            pPlayer = (GamePlayer*)pChar;
            if (pPlayer)
            {
                MsgShowTimeTop msg;
                msg.header.stID = pPlayer->GetID();
                msg.showtime = showtime;
                GettheServer().SendMsgToSingle(&msg,pChar);
            }
        }
    }
}

void CServerVarInterface::ShutDownTimeTop()
{
    {
        BaseCharacter* pChar = NULL;
        pChar = theRunTimeData.GetCharacterByID( GetCurCharId() );
        if ( !pChar )
            return;

        GamePlayer* pPlayer = NULL;
        if ( pChar->IsPlayer() )
        {
            pPlayer = (GamePlayer*)pChar;
            if (pPlayer)
            {
                MsgShutDownTimeTop msg;
                msg.header.stID = pPlayer->GetID();                
                GettheServer().SendMsgToSingle(&msg,pChar);
            }
        }
    }
}

void CServerVarInterface::BeckonPlayer( GameObjectId nPlayerId )
{
    BaseCharacter* pSelfChar = theRunTimeData.GetCharacterByID( GetCurCharId() );
    if ( !pSelfChar || !pSelfChar->IsPlayer() )
    { return; }

    BaseCharacter* pOtherChar = theRunTimeData.GetCharacterByID( nPlayerId );
    if ( pOtherChar== NULL || !pOtherChar->IsPlayer())
    { return; }

    GamePlayer* pPlayer = static_cast< GamePlayer* >( pOtherChar );
    pPlayer->FlyToMapReq( pSelfChar->GetMapID(), pSelfChar->GetFloatX(), pSelfChar->GetFloatY(), 0.0f );
}

void CServerVarInterface::CallScriptTeam( const char* szFileName, int nEnterId )
{
    BaseCharacter* pChar = theRunTimeData.GetCharacterByID( GetCurCharId() );
    if( !pChar || !pChar->IsPlayer() )
        return;

    GameTeam* pTeam = theGameTeamManager.GetTeam(pChar->GetTeamID());
    if (pTeam != NULL)
    {   
        for ( int i = 0; i < pTeam->TeamMemberCount(); ++i )
        {
            GameTeamMember* pMember = pTeam->GetTeamMemberByIndex( i );
            if (pMember == NULL) 
            { continue; }
            CallScript( szFileName, nEnterId, pMember->GetID(), true );
            //CallScript( szFileName, nEnterId, nCharId );
        }
    }
}

bool CServerVarInterface::IsMountFull()
{
	BaseCharacter* pChar = theRunTimeData.GetCharacterByID( GetCurCharId() );
	if( !pChar || !pChar->IsPlayer() )
	{ return false; }

	GamePlayer* pPlayer = (GamePlayer*)pChar;
	if ( !pPlayer )
	{ return false; }

	return pPlayer->IsMountFull();
}

int CServerVarInterface::AddMount( unsigned short usMountId )
{
    BaseCharacter* pChar = theRunTimeData.GetCharacterByID( GetCurCharId() );
    if( !pChar || !pChar->IsPlayer() )
    { return 0; }

    GamePlayer* pPlayer = (GamePlayer*)pChar;
    if ( !pPlayer )
    { return 0; }

    return pPlayer->AddMount( usMountId );
}

bool CServerVarInterface::IsPetFull()
{
    BaseCharacter* pChar = theRunTimeData.GetCharacterByID( GetCurCharId() );
    if( !pChar || !pChar->IsPlayer() )
    { return ER_Failed; }

    GamePlayer* pPlayer = (GamePlayer*)pChar;
    if ( !pPlayer )
    { return ER_Failed; }

    return pPlayer->_petManager.IsPetFull();
}

int CServerVarInterface::GetPetNumber()
{
    BaseCharacter* pChar = theRunTimeData.GetCharacterByID( GetCurCharId() );
    if( !pChar || !pChar->IsPlayer() )
    { return 0; }

    GamePlayer* pPlayer = (GamePlayer*)pChar;
    if ( !pPlayer )
    { return 0; }

    return pPlayer->_petManager.GetPetNumber();
}

int CServerVarInterface::AddPet( int monsterId, int quality, int sex )
{
    BaseCharacter* pChar = theRunTimeData.GetCharacterByID( GetCurCharId() );
    if( !pChar || !pChar->IsPlayer() )
    { return ER_Failed; }

    GamePlayer* pPlayer = (GamePlayer*)pChar;
    if ( !pPlayer )
    { return ER_Failed; }

    return pPlayer->AddPet( monsterId, quality, sex );
}

bool CServerVarInterface::AddPetIdentify ( uint16 petType )
{
    BaseCharacter* pChar = theRunTimeData.GetCharacterByID( GetCurCharId() );
    if( !pChar || !pChar->IsPlayer() )
    { return false; }

    GamePlayer* pPlayer = (GamePlayer*)pChar;
    if ( !pPlayer )
    { return false; }

    return pPlayer->AddPetIdentify( petType );
}

bool CServerVarInterface::HaveBreedPet()
{
    BaseCharacter* pChar = theRunTimeData.GetCharacterByID( GetCurCharId() );
    if( !pChar || !pChar->IsPlayer() )
    { return false; }

    GamePlayer* pPlayer = (GamePlayer*)pChar;
    if ( !pPlayer )
    { return false; }

    SPetItem* pPet = pPlayer->_petManager.GetBreedPet();

    return pPet != NULL;
}

void CServerVarInterface::PetBreedAcquire()
{
    BaseCharacter* pChar = theRunTimeData.GetCharacterByID( GetCurCharId() );
    if( !pChar || !pChar->IsPlayer() )
    { return ; }

    GamePlayer* pPlayer = (GamePlayer*)pChar;
    if ( !pPlayer )
    { return ; }

    return pPlayer->PetBreedAcquire();
}

int CServerVarInterface::GetPetMaxLevel( )
{
    BaseCharacter* pChar = theRunTimeData.GetCharacterByID( GetCurCharId() );
    if( !pChar || !pChar->IsPlayer() )
    { return 0; }

    GamePlayer* pPlayer = (GamePlayer*)pChar;
    if ( !pPlayer )
    { return 0; }

    return pPlayer->_petManager.GetPetMaxLevel();
}

int CServerVarInterface::GetActivePetIndex( )
{
    BaseCharacter* pChar = theRunTimeData.GetCharacterByID( GetCurCharId() );
    if( !pChar || !pChar->IsPlayer() )
    { return 0; }

    GamePlayer* pPlayer = (GamePlayer*)pChar;
    if ( !pPlayer )
    { return 0; }

    return pPlayer->_petManager.GetActivePetIndex();
}

int CServerVarInterface::GetDaoxing()
{
    BaseCharacter* pChar = theRunTimeData.GetCharacterByID( GetCurCharId() );
    if( !pChar || !pChar->IsPlayer() )
    { return 0; }

    GamePlayer* pPlayer = (GamePlayer*)pChar;
    if ( !pPlayer )
    { return 0; }

    return pPlayer->GetDaoxing();
}

void CServerVarInterface::AddDaoxing( int nValue )
{
    BaseCharacter* pChar = theRunTimeData.GetCharacterByID( GetCurCharId() );
    if( !pChar || !pChar->IsPlayer() )
    { return ; }

    GamePlayer* pPlayer = (GamePlayer*)pChar;
    if ( !pPlayer )
    { return ; }

    pPlayer->OperateDaoxing(EOT_Add, nValue, __FUNCTION__, __LINE__ );
}

bool CServerVarInterface::HasMount( unsigned short usMountId )
{
    BaseCharacter* pChar = theRunTimeData.GetCharacterByID( GetCurCharId() );
    if( !pChar || !pChar->IsPlayer() )
        return -1;

    GamePlayer* pPlayer = (GamePlayer*)pChar;
    if ( !pPlayer )
        return -1;

    return pPlayer->_mountManager.HasMount( usMountId );
}

int CServerVarInterface::RestoreMountEnjoyment()
{
    BaseCharacter* pChar = theRunTimeData.GetCharacterByID( GetCurCharId() );
    if( !pChar || !pChar->IsPlayer() )
        return -1;

    GamePlayer* pPlayer = (GamePlayer*)pChar;
    if ( !pPlayer )
        return -1;

    return pPlayer->_mountManager.RestoreMountHP();
}

void CServerVarInterface::AddLevel(int level)
{
    BaseCharacter* pChar = theRunTimeData.GetCharacterByID( GetCurCharId() );
    if( !pChar || !pChar->IsPlayer() )
        return;

    GamePlayer* pGamePlayer = (GamePlayer*)pChar;
    if ( !pGamePlayer )
        return;

    int nTargetLevel = pGamePlayer->GetLevel() + level;

    pGamePlayer->ChangeExp( theExpStage.GetLevelupExp( nTargetLevel ) );
}

bool CServerVarInterface::IsInArea(int Lx,int Ly,int Rx,int Ry)
{
    GameObjectId iCharID = GetCurCharId();
    BaseCharacter* pChar = theRunTimeData.GetCharacterByID( iCharID );

    if( pChar && pChar->IsPlayer() )
    {
        GamePlayer* pPlayer = (GamePlayer*)pChar;
        return pPlayer->Script_IsInArea(Lx,Ly,Rx,Ry);
    }
    return false;
}

int CServerVarInterface::SelfPosX()
{
    GameObjectId iCharID = GetCurCharId();
    BaseCharacter* pChar = theRunTimeData.GetCharacterByID( iCharID );

    if( pChar && pChar->IsPlayer() )
    {
        GamePlayer* pPlayer = (GamePlayer*)pChar;
        return pPlayer->Script_SelfPosX();
    }
    return -1;
}

int CServerVarInterface::SelfPosY()
{
    GameObjectId iCharID = GetCurCharId();
    BaseCharacter* pChar = theRunTimeData.GetCharacterByID( iCharID );

    if( pChar && pChar->IsPlayer() )
    {
        GamePlayer* pPlayer = (GamePlayer*)pChar;
        return pPlayer->Script_SelfPosY();
    }
    return -1;
}
void CServerVarInterface::DropItem(int ItemId,int ItemNum,bool nobelong)
{
    GameObjectId iCharID = GetCurCharId();
    BaseCharacter* pChar = theRunTimeData.GetCharacterByID( iCharID );

    if( pChar && pChar->IsPlayer() )
    {
        GamePlayer* pPlayer = (GamePlayer*)pChar;
        pPlayer->Script_DropItemOnMonsterDead(ItemId,ItemNum,nobelong);
        return;
    }
    return;
}
bool CServerVarInterface::CreateScriptNpc(int NpcId,int mapId,int PosX,int PosY,unsigned int unOnTime)
{
    //检查当前服务器有没有开启需要创建的地图
    GameStage* pGameStage = theGameWorld.GetStageById(mapId);
    if ( pGameStage == NULL || pGameStage->IsEctypeStage() )
    { return false; }

    //检查有没有对应的Npc
    NpcInfo::Npc* pNpcInfo = theNpcInfo.GetNpc( NpcId, mapId );
    if (!pNpcInfo || pNpcInfo->type != eNT_ScriptNpc)     //没有指定的NPC Info
    {
        LogMessage::LogScriptError( "Create Npc Error! Npc %d Info Error", NpcId );
        return false;
    }

    NpcInfo::Npc* pNewNpcInfo = new NpcInfo::Npc;
    if ( pNpcInfo == NULL )
    { return false; }

    *pNewNpcInfo = *pNpcInfo;
    pNewNpcInfo->mapId = mapId;
    pNewNpcInfo->x     = PosX;
    pNewNpcInfo->y     = PosY;
    pNewNpcInfo->z     = WORLD_HEIGHT;    
    NpcCreater::CreateNpc( pGameStage, pNewNpcInfo, true, unOnTime ); 

    return true;
}

bool CServerVarInterface::RecordTime( int nVarId )
{
    GameObjectId iCharID = GetCurCharId();
    GamePlayer* pPlayer = (GamePlayer*) theRunTimeData.GetCharacterByID( iCharID );
    if ( pPlayer == NULL || !pPlayer->IsPlayer())
        return false;

    return pPlayer->RecordTimeVar( nVarId );
}

bool CServerVarInterface::IsExpired( int nVarId, int keyHour, int keyMinute, int minDuration  )
{
    GameObjectId iCharID = GetCurCharId();
    GamePlayer* pPlayer = (GamePlayer*) theRunTimeData.GetCharacterByID( iCharID );
    if ( pPlayer == NULL || !pPlayer->IsPlayer())
        return false;

    return pPlayer->IsExpired( nVarId, keyHour, keyMinute, minDuration );
}

bool CServerVarInterface::RecordTeamTime( int nVarId )
{
    GameObjectId iCharID = GetCurCharId();
    GamePlayer* pPlayer = (GamePlayer*) theRunTimeData.GetCharacterByID( iCharID );
    if ( pPlayer == NULL || !pPlayer->IsPlayer())
        return false;

    GameTeam* pTeam = theGameTeamManager.GetTeam( pPlayer->GetTeamID() );
    if ( pTeam == NULL )
    { return false; }

    return pTeam->RecordTeamTime( nVarId );
}


bool CServerVarInterface::IsTeamExpired( int nVarId, int keyHour, int keyMinute, int minDuration  )
{
    GameObjectId iCharID = GetCurCharId();
    GamePlayer* pPlayer = (GamePlayer*) theRunTimeData.GetCharacterByID( iCharID );
    if ( pPlayer == NULL || !pPlayer->IsPlayer())
        return false;

    GameTeam* pTeam = theGameTeamManager.GetTeam( pPlayer->GetTeamID() );
    if ( pTeam == NULL )
    { return false; }

    unsigned int nInAreaCount = pTeam->GetTeamMemberCountInMap( pPlayer->GetMapID(), pPlayer->GetFloatX(), pPlayer->GetFloatY() );
    if ( nInAreaCount != pTeam->TeamMemberCount() )
    {
        pPlayer->TellClient(theXmlString.GetString(eTellClient_TeamMemberMustArlound));            // 只有所有队员在有效范围内才能进入
        return false;
    }

    unsigned long dwID = pTeam->IsTeamExpired( nVarId, keyHour, keyMinute, minDuration );
    if ( dwID != InvalidLogicNumber )
    {
        MsgAckResult xAck;
        xAck.result = ER_TeamMemberAlreadyEntryMap;       // 某某某已经进入过地图了
        xAck.value = dwID;
        GettheServer().SendMsgToSingle( &xAck, pPlayer );
    }

    return ( dwID == InvalidLogicNumber );
}

void CServerVarInterface::ClearTeamExpiredVar( int nVarId, int keyHour, int keyMinute, int minDuration, int nClearVarId )
{
    GameObjectId iCharID = GetCurCharId();
    GamePlayer* pPlayer = (GamePlayer*) theRunTimeData.GetCharacterByID( iCharID );
    if ( pPlayer == NULL || !pPlayer->IsPlayer())
        return;

    GameTeam* pTeam = theGameTeamManager.GetTeam( pPlayer->GetTeamID() );
    if ( pTeam == NULL )
    {
        if ( pPlayer->IsExpired( nVarId, keyHour, keyMinute, minDuration ) )
        {
            pPlayer->SetVar( nClearVarId, 0 );
        }
    }
    else
    {
        pTeam->ClearTeamExpiredVar( nVarId, keyHour, keyMinute, minDuration, nClearVarId );
    }
}

void CServerVarInterface::RecordExploitTime()
{
    GameObjectId iCharID = GetCurCharId();
    GamePlayer* pPlayer = (GamePlayer*) theRunTimeData.GetCharacterByID( iCharID );
    if ( pPlayer == NULL || !pPlayer->IsPlayer())
        return;

    pPlayer->SetTimeVar( ECT_ExploitTime, TimeEx::GetNowTime() );
}

void CServerVarInterface::RecordTimeVar( int nVarID )
{
    BaseCharacter* pChar = theRunTimeData.GetCharacterByID( GetCurCharId() );
    if ( pChar == NULL || !pChar->IsPlayer() )
    { return; }

    GamePlayer* pPlayer = static_cast< GamePlayer* >( pChar );

    pPlayer->RecordNowTimeVar( nVarID );
}

bool CServerVarInterface::IsTimeVarPassOneDay( int nVarID )
{
    BaseCharacter* pChar = theRunTimeData.GetCharacterByID( GetCurCharId() );
    if ( pChar == NULL || !pChar->IsPlayer() )
    { return false; }

    GamePlayer* pPlayer = static_cast< GamePlayer* >( pChar );
    return pPlayer->IsTimeVarPassOneDay( nVarID );
}

void CServerVarInterface::RecordTeamTimeVar( int nVarID )
{
    BaseCharacter* pChar = theRunTimeData.GetCharacterByID( GetCurCharId() );
    if ( pChar == NULL || !pChar->IsPlayer() )
    { return; }

    GamePlayer* pPlayer = static_cast< GamePlayer* >( pChar );

    GameTeam* pTeam = theGameTeamManager.GetTeam( pPlayer->GetTeamID() );
    if ( pTeam == NULL )
    { pPlayer->RecordNowTimeVar( nVarID ); }
    else
    { pTeam->RecordNowTeamTimeVar( nVarID ); }
}

bool CServerVarInterface::IsTeamTimeVarPassOneDay( int nVarID )
{
    BaseCharacter* pChar = theRunTimeData.GetCharacterByID( GetCurCharId() );
    if ( pChar == NULL || !pChar->IsPlayer() )
    { return false; }
    GamePlayer* pPlayer = static_cast< GamePlayer* >( pChar );

    GameTeam* pTeam = theGameTeamManager.GetTeam( pPlayer->GetTeamID() );
    if ( pTeam == NULL )
    { return false; }

    unsigned int nInAreaCount = pTeam->GetTeamMemberCountInMap( pPlayer->GetMapID(), pPlayer->GetFloatX(), pPlayer->GetFloatY() );
    if ( nInAreaCount != pTeam->TeamMemberCount() )
    {
        pPlayer->TellClient( theXmlString.GetString( eTellClient_TeamMemberMustArlound ) );            // 只有所有队员在有效范围内
        return false;
    }

    unsigned long dwID = pTeam->IsTeamTimeVarPassOneDay( nVarID );
    if ( dwID != TeamDefine::ErrorID )
    { pPlayer->SendErrorToClient( ER_TeamMemberAlreadyEntryMap, dwID ); }

    return ( dwID == TeamDefine::ErrorID );
}


void CServerVarInterface::ClearTeamTimeVar( int nVarID, int nClearVarID )
{
    BaseCharacter* pChar = theRunTimeData.GetCharacterByID( GetCurCharId() );
    if ( pChar == NULL || !pChar->IsPlayer() )
    { return; }
    GamePlayer* pPlayer = static_cast< GamePlayer* >( pChar );

    GameTeam* pTeam = theGameTeamManager.GetTeam( pPlayer->GetTeamID() );
    if ( pTeam == NULL )
    {
        if ( pPlayer->IsTimeVarPassOneDay( nVarID ) )
        {
            pPlayer->SetVar( nClearVarID, 0 );
        }
    }
    else
    {
        pTeam->ClearTeamTimeVar( nVarID, nClearVarID );
    }
}

// bool CServerVarInterface::DeleteScriptNpc(int NpcBeginId ,int NpcEndId)
// {
//     int BeginNpcId = NpcBeginId;
//     for(; BeginNpcId != NpcEndId;++BeginNpcId)
//     {
// //         BaseCharacter* pChar = theRunTimeData.GetCharacterByNpcID(BeginNpcId);
// //         if (pChar && pChar->IsNpc() && pChar->GetObjType() == eNT_ScriptNpc)
//         {
//             theGameWorld.OnDelNpc(BeginNpcId);
//         }
//     }
//     if (NpcBeginId == NpcBeginId)
//     {
// //         BaseCharacter* pChar = theRunTimeData.GetCharacterByNpcID(BeginNpcId);
// //         if (pChar && pChar->IsNpc() && pChar->GetObjType() == eNT_ScriptNpc)
//         {
//             theGameWorld.OnDelNpc(BeginNpcId);
//         }
//     }
//     return true;
// }


bool CServerVarInterface::ScriptCreateStage( const DWORD dwMapID, int nMapCount, bool bUsePlayerLevel, unsigned short ustMapLevel )
{
    MapConfig::MapData* pMapData = theMapConfig.GetMapDataById( EctypeId2MapId( dwMapID ) );
    if ( pMapData == NULL || !pMapData->IsEctypeMap() || !pMapData->IsSystemCreateMap() )
    { 
        LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_ERROR, "ScriptCreateStage MapData Error! dwMapID = [%u]", dwMapID );
        return false; 
    }

    if( !g_Cfg.IsMapRun( pMapData->Id ) )
    { return false; }   // 服务器上没有开这个地图

    if ( bUsePlayerLevel )
    {
        BaseCharacter* pChar = theRunTimeData.GetCharacterByID( GetCurCharId() );
        if ( pChar == NULL || !pChar->IsPlayer() )
        { return false; }

        GamePlayer* pPlayer = static_cast< GamePlayer* >( pChar );
        ustMapLevel = pPlayer->GetPlayerEctypeMapLevel( pPlayer->GetMapID(), pPlayer->GetFloatX(), pPlayer->GetFloatY(), pMapData->GetMapType() ); 
    }

    if ( nMapCount <= 0 )
        nMapCount = 1;
    if ( nMapCount > 20 )
        nMapCount = 20;

    if ( pMapData->IsMapCountLimitMap() )
    {
        int nCount = pMapData->Count - theGameWorld.GetMapCount( dwMapID );
        if ( nMapCount > nCount )
        {
            nMapCount = nCount;
        }
    }

    if ( nMapCount == 0 )           // 创建满了
    {
        LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_ERROR, "ScriptCreateStage[MapID = %u] nMapCount == 0, max = %d exist = %d", dwMapID, pMapData->IsMapCountLimitMap(), theGameWorld.GetMapCount( dwMapID ) );
        return false;
    }

    for ( int i = 0; i < nMapCount; ++i )
    {

        DWORD dwEctypeMapId = theGameWorld.GetEctypeMapID( dwMapID, true );
        if ( dwEctypeMapId == 0 )
        { return false;  }

        GameStage* pStage = theGameWorld.GetStageById( dwEctypeMapId );
        if ( pStage == NULL )
        {
            theGameWorld.MultiCreateStage( dwMapID, dwEctypeMapId, ustMapLevel );
        }
    }

	//printf("createstage:%d,count:%d,all stage count:%d\n",dwMapID,nMapCount,theGameWorld.GetStageCount());

    return true;
}

bool CServerVarInterface::IsStageExist( const unsigned short dwMapID )
{
    GameObjectId iCharID = GetCurCharId();
    GamePlayer* pPlayer = (GamePlayer*) theRunTimeData.GetCharacterByID( iCharID );
    if ( pPlayer == NULL || !pPlayer->IsPlayer())
    { return false; }

    MapConfig::MapData* pMapData = theMapConfig.GetMapDataById( dwMapID );
    if ( pMapData == NULL )
    { 
        LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_ERROR, "IsStageExist MapData Error! dwMapID = [%u]", dwMapID );
        return false; 
    }

    if ( pPlayer->GetTeamID() == TeamDefine::NoneSessionID )
    { return false; }

    unsigned long dwMapId = theGameWorld.MakeEctypeStageID( pMapData, pPlayer );
    GameStage* pStage = theGameWorld.GetStageById( dwMapId );

    return ( pStage != NULL );
}

bool CServerVarInterface::IsStageWaitRelease( unsigned int nMapID )
{
    GameObjectId iCharID = GetCurCharId();
    GamePlayer* pPlayer = (GamePlayer*) theRunTimeData.GetCharacterByID( iCharID );
    if ( pPlayer == NULL || !pPlayer->IsPlayer())
    { return false; }

    MapConfig::MapData* pMapData = theMapConfig.GetMapDataById( nMapID );
    if ( pMapData == NULL || pMapData->GetMapType() != MapConfig::MT_SingleTeam )
    { 
        LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_ERROR, "IsStageWaitRelease MapData Error! nMapID = [%u]", nMapID );
        return false; 
    }

    if ( pPlayer->GetTeamID() == TeamDefine::NoneSessionID )
    { return false; }

    unsigned long dwMapId = theGameWorld.MakeEctypeStageID( pMapData, pPlayer );
    GameStage* pStage = theGameWorld.GetStageById( dwMapId );
    if ( pStage == NULL )
    { return false; }

    return pStage->IsStageWaitingRelease();
}

bool CServerVarInterface::LeaveStage( unsigned short ustMapID, float fX, float fY, bool bTeamLeave, unsigned short ustTime )
{
    GameObjectId iCharID = GetCurCharId();
    GamePlayer* pPlayer = (GamePlayer*) theRunTimeData.GetCharacterByID( iCharID );
    if ( pPlayer == NULL || !pPlayer->IsPlayer())
    { return false; }

    MapConfig::MapData* pMapData = theMapConfig.GetMapDataById( ustMapID );
    if ( pMapData == NULL )
    { 
        LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_ERROR, "LeaveStage MapData Error! dwMapID = [%u]", ustMapID );
        return false; 
    }

    if ( bTeamLeave )
    {
        GameTeam* pTeam = theGameTeamManager.GetTeam( pPlayer->GetTeamID() );
        if ( pTeam == NULL )
        {
            pPlayer->SetWaitChangeStage( GamePlayer::LeaveStage, ustMapID, fX, fY, 0.f, ustTime, true );
        }
        else
        {
            for ( int i = 0; i < pTeam->TeamMemberCount(); ++i )
            {
                unsigned long dwPlayerID = pTeam->GetMemberIDByIndex( i );
                GamePlayer* pTeamPlayer = theRunTimeData.GetGamePlayerByDBID( dwPlayerID );
                if ( pTeamPlayer != NULL && pTeamPlayer->IsInMapArea( pPlayer->GetMapID(), pPlayer->GetFloatX(), pPlayer->GetFloatY(), TEAM_EXP_DIS ) )
                {
                    pTeamPlayer->SetWaitChangeStage( GamePlayer::LeaveStage, ustMapID, fX, fY, 0.f, ustTime, true );
                }
            }
        }
    }
    else
    {
        pPlayer->SetWaitChangeStage( GamePlayer::LeaveStage, ustMapID, fX, fY, 0.f, ustTime, true );
    }

    return true;
}

// 幸运15关相关
int CServerVarInterface::GetLuckRewardLevel()           // 获得当前第几关
{
    GamePlayer* pPlayer = static_cast< GamePlayer* >( theRunTimeData.GetCharacterByID( GetCurCharId() ) );
    if ( pPlayer == NULL || !pPlayer->IsPlayer() )
    { return 0; }

    return pPlayer->GetLuckRewardLevel( true );
}

void CServerVarInterface::EnterLuckReward()
{
    GamePlayer* pPlayer = static_cast< GamePlayer* >( theRunTimeData.GetCharacterByID( GetCurCharId() ) );
    if ( pPlayer == NULL || !pPlayer->IsPlayer() )
    { return; }

    pPlayer->EnterLuckReward();
}

void CServerVarInterface::UpdateLuckReward( int nType )
{
    GamePlayer* pPlayer = static_cast< GamePlayer* >( theRunTimeData.GetCharacterByID( GetCurCharId() ) );
    if ( pPlayer == NULL || !pPlayer->IsPlayer() )
    { return; }

    pPlayer->UpdateLuckReward( nType );
}

bool CServerVarInterface::IsCanLuckReward()
{
    GamePlayer* pPlayer = static_cast< GamePlayer* >( theRunTimeData.GetCharacterByID( GetCurCharId() ) );
    if ( pPlayer == NULL || !pPlayer->IsPlayer() )
    { return false; }

    return pPlayer->IsCanLuckReward();
}

bool CServerVarInterface::IsCanNextLuckLevel()
{
    GamePlayer* pPlayer = static_cast< GamePlayer* >( theRunTimeData.GetCharacterByID( GetCurCharId() ) );
    if ( pPlayer == NULL || !pPlayer->IsPlayer() )
    { return false; }

    return pPlayer->IsCanNextLuckLevel();
}

bool CServerVarInterface::IsCanAcceptQuest( unsigned char uchLevel )
{
    GamePlayer* pPlayer = static_cast< GamePlayer* >( theRunTimeData.GetCharacterByID( GetCurCharId() ) );
    if ( pPlayer == NULL || !pPlayer->IsPlayer() )
    { return false; }

    return pPlayer->IsCanAcceptQuest( uchLevel );
}



bool CServerVarInterface::IsCanReceiveReward()
{
    GamePlayer* pPlayer = static_cast< GamePlayer* >( theRunTimeData.GetCharacterByID( GetCurCharId() ) );
    if ( pPlayer == NULL || !pPlayer->IsPlayer() )
    { return false; }

    return pPlayer->IsCanReceiveReward();
}

void CServerVarInterface::SetCanLuckReward()
{
    GamePlayer* pPlayer = static_cast< GamePlayer* >( theRunTimeData.GetCharacterByID( GetCurCharId() ) );
    if ( pPlayer == NULL || !pPlayer->IsPlayer() )
    { return; }

    pPlayer->SetCanLuckReward();
}

void CServerVarInterface::SetLuckSummonCount( unsigned short ustCount )
{
    GamePlayer* pPlayer = static_cast< GamePlayer* >( theRunTimeData.GetCharacterByID( GetCurCharId() ) );
    if ( pPlayer == NULL || !pPlayer->IsPlayer() )
    { return; }

    pPlayer->SetLuckSummonCount( ustCount );
}

unsigned short CServerVarInterface::GetLuckSummonCount()
{
    GamePlayer* pPlayer = static_cast< GamePlayer* >( theRunTimeData.GetCharacterByID( GetCurCharId() ) );
    if ( pPlayer == NULL || !pPlayer->IsPlayer() )
    { return 0xFFFF; }

    return pPlayer->GetLuckSummonCount();
}

bool CServerVarInterface::OperateJinDing( bool bOperate, int nValue )
{
    GamePlayer* pGamePlayer = static_cast< GamePlayer* >( theRunTimeData.GetCharacterByID( GetCurCharId() ) );
    if ( pGamePlayer == NULL || !pGamePlayer->IsPlayer() )
    { return false; }

    if ( nValue <= 0 )
    { return false; }

    LOG_MESSAGE( BILLINGOBJECT, LOG_PRIORITY_INFO, "[%u:%u:%s] 兑换获得金锭[%u]", pGamePlayer->GetAccountID(), pGamePlayer->GetDBCharacterID(), pGamePlayer->GetCharName(), nValue );
    uint8 uchOperate = ( bOperate ? EOT_Add : EOT_Sub );
    pGamePlayer->OperateJinDing( uchOperate, nValue, __FUNCTION__, __LINE__,ePlayerMoneySourceType_Scprit );
    return true;
}

bool CServerVarInterface::OperateJinPiao( bool bOperate, int nValue )
{
    GamePlayer* pPlayer = static_cast< GamePlayer* >( theRunTimeData.GetCharacterByID( GetCurCharId() ) );
    if ( pPlayer == NULL || !pPlayer->IsPlayer() )
    { return false; }

    if ( nValue <= 0 )
    { return false; }

    uint8 uchOperate = ( bOperate ? EOT_Add : EOT_Sub );
    pPlayer->OperateJinPiao( uchOperate, nValue, __FUNCTION__, __LINE__,ePlayerMoneySourceType_Scprit );
    return true;
}

bool CServerVarInterface::OperateHonour( bool bOperate, int nValue )
{
    GamePlayer* pPlayer = static_cast< GamePlayer* >( theRunTimeData.GetCharacterByID( GetCurCharId() ) );
    if ( pPlayer == NULL || !pPlayer->IsPlayer() )
    { return false; }

    if ( nValue <= 0 )
    { return false; }

    uint8 uchOperate = ( bOperate ? EOT_Add : EOT_Sub );
    pPlayer->OperateHonour( uchOperate, nValue, __FUNCTION__, __LINE__ ,ePlayerMoneySourceType_Scprit);
    return true;
}

void CServerVarInterface::ShowTreasureBox()
{
    GamePlayer* pPlayer = static_cast< GamePlayer* >( theRunTimeData.GetCharacterByID( GetCurCharId() ) );
    if ( pPlayer == NULL || !pPlayer->IsPlayer() )
    { return; }

    pPlayer->ShowTreasureBox();
}

void CServerVarInterface::DrawFromPlatform( uint16 infoType )
{   
    BaseCharacter* pChar = theRunTimeData.GetCharacterByID( GetCurCharId() );
    if ( pChar == NULL || !pChar->IsPlayer() )
    { return; }

    GamePlayer* pGamePlayer = (GamePlayer*)pChar;

    GS2CSDrawFromPlatformQuery msg;

    switch ( infoType )
    {
    case ECT_XinShouCard:
    case ECT_17173Card:
    case ECT_ZhiZunCardLevel:
    case ECT_ZhiZunVipGift:
    case ECT_HuiGuiGift:
    case ECT_ChongZhiFirstGift:
    case ECT_ChongZhiBackGift:
        break;
    default:
        return;
    }
    msg.drawType   = infoType;
    msg.guid = pGamePlayer->GetAccountID();
    GettheServer().SendCenterServerMsg( &msg );
}

void CServerVarInterface::SetAreaCurrentReputation( int nMapID, int nValue )
{
    BaseCharacter* pChar = theRunTimeData.GetCharacterByID( GetCurCharId() );
    if ( pChar == NULL || !pChar->IsPlayer() )
    { return; }

    GamePlayer* pGamePlayer = (GamePlayer*)pChar;

    pGamePlayer->Script_SetAreaCurrentReputation( nMapID, nValue, SKW_SET );
}

void CServerVarInterface::AddAreaCurrentReputation( int nMapID, int nValue )
{
    BaseCharacter* pChar = theRunTimeData.GetCharacterByID( GetCurCharId() );
    if ( pChar == NULL || !pChar->IsPlayer() )
    { return; }

    GamePlayer* pGamePlayer = (GamePlayer*)pChar;

    pGamePlayer->Script_SetAreaCurrentReputation( nMapID, nValue, SKW_SETADD );
}

void CServerVarInterface::SubAreaCurrentReputation( int nMapID, int nValue )
{
    BaseCharacter* pChar = theRunTimeData.GetCharacterByID( GetCurCharId() );
    if ( pChar == NULL || !pChar->IsPlayer() )
    { return; }

    GamePlayer* pGamePlayer = (GamePlayer*)pChar;

    pGamePlayer->Script_SetAreaCurrentReputation( nMapID, nValue, SKW_SETSUB );
}

int CServerVarInterface::GetAreaCurrentReputation( int nMapID )
{
    BaseCharacter* pChar = theRunTimeData.GetCharacterByID( GetCurCharId() );
    if ( pChar == NULL || !pChar->IsPlayer() )
    { return 0; }

    GamePlayer* pGamePlayer = (GamePlayer*)pChar;

    return pGamePlayer->Script_GetAreaCurrentReputation( nMapID );
}

void CServerVarInterface::SetAreaMaxReputation( int nMapID, int nValue )
{
    BaseCharacter* pChar = theRunTimeData.GetCharacterByID( GetCurCharId() );
    if ( pChar == NULL || !pChar->IsPlayer() )
    { return; }

    GamePlayer* pGamePlayer = (GamePlayer*)pChar;

    pGamePlayer->Script_SetAreaMaxReputation( nMapID, nValue, SKW_SET );
}

void CServerVarInterface::AddAreaMaxReputation( int nMapID, int nValue )
{
    BaseCharacter* pChar = theRunTimeData.GetCharacterByID( GetCurCharId() );
    if ( pChar == NULL || !pChar->IsPlayer() )
    { return; }

    GamePlayer* pGamePlayer = (GamePlayer*)pChar;

    pGamePlayer->Script_SetAreaMaxReputation( nMapID, nValue, SKW_SETADD );
}

void CServerVarInterface::SubAreaMaxReputation( int nMapID, int nValue )
{
    BaseCharacter* pChar = theRunTimeData.GetCharacterByID( GetCurCharId() );
    if ( pChar == NULL || !pChar->IsPlayer() )
    { return; }

    GamePlayer* pGamePlayer = (GamePlayer*)pChar;

    pGamePlayer->Script_SetAreaMaxReputation( nMapID, nValue, SKW_SETSUB );
}

int CServerVarInterface::GetAreaMaxReputation( int nMapID )
{
    BaseCharacter* pChar = theRunTimeData.GetCharacterByID( GetCurCharId() );
    if ( pChar == NULL || !pChar->IsPlayer() )
    { return 0; }

    GamePlayer* pGamePlayer = (GamePlayer*)pChar;

    return pGamePlayer->Script_GetAreaMaxReputation( nMapID );
}

bool CServerVarInterface::SetNextStage( int nNextStage )
{
    BaseCharacter* pChar = theRunTimeData.GetCharacterByID( GetCurCharId() );
    if ( pChar == NULL || !pChar->IsPlayer() )
    { return false; }

    GamePlayer* pGamePlayer = (GamePlayer*)pChar;

    GameStage* pGameStage = theGameWorld.GetStageById( pGamePlayer->GetMapID() );
    if ( pGameStage == NULL || !pGameStage->IsEctypeStage() )
    { return false; }

    EctypeStage* pStage = static_cast< EctypeStage* >( pGameStage );

    pStage->SetNextRefreshStage( nNextStage );
    return true;
}

bool CServerVarInterface::InitBattle( int nMapID, int nType, int nLevel, unsigned char uchTurns, int nSignTime, int nFightTime, int nMaxUnitCount )
{
    switch ( nType )
    {
    case BattleDefine::PlayerType:     // 个人的
        {
            PlayerBattleData* pBattleData = PlayerBattleData::CreateBattleData();
            if ( pBattleData == NULL )
            { return false; }

            pBattleData->SetWaitMapID( nMapID );    // 设置等待地图
            pBattleData->SetMapLevel( nLevel );
            pBattleData->SetRepeatTurns( uchTurns == 0 ? 1 : uchTurns );
            pBattleData->SetSignUpTime( nSignTime * 60000 );
            pBattleData->SetFightTime( nFightTime * 60000 );
            pBattleData->SetMaxUnitCount( nMaxUnitCount );

            MapConfig::MapData* pMapData = theMapConfig.GetMapDataById( nMapID );
            if ( pMapData == NULL )
            { return false; }

            // 获得战斗地图
            MapConfig::TransportPosition* pPosition  = pMapData->GetTransportPositionByIndex( 0 );
            if ( pPosition == NULL )
            { return false; }

            MapConfig::MapData* pFightMapData = theMapConfig.GetMapDataById( pPosition->TargetMapId );
            if ( pFightMapData == NULL )
            { return false; }

            pBattleData->SetFightMapID( pPosition->TargetMapId );       // 设置战场地图

            thePlayerBattleManager.AddBattleData( pBattleData );
        }
        break;
    case BattleDefine::TeamType:     // 队伍
        {
            TeamBattleData* pBattleData = TeamBattleData::CreateBattleData();
            if ( pBattleData == NULL )
            { return false; }

            pBattleData->SetFightMapID( nMapID );
            pBattleData->SetWaitMapID( nMapID );
            pBattleData->SetMapLevel( nLevel );
            pBattleData->SetRepeatTurns( uchTurns == 0 ? 1 : uchTurns );
            pBattleData->SetSignUpTime( nSignTime * 60000 );
            pBattleData->SetFightTime( nFightTime * 60000 );
            pBattleData->SetMaxUnitCount( nMaxUnitCount );
            theTeamBattleManager.AddBattleData( pBattleData );
        }
        break;
    case BattleDefine::GuildType:     // 公会
        break;
    }

    return true;
}

bool CServerVarInterface::ShowBattleSignUpDlg( int nType, const char* szInfo )
{
    BaseCharacter* pChar = theRunTimeData.GetCharacterByID( GetCurCharId() );
    if ( pChar == NULL || !pChar->IsPlayer() )
    { return false; }

    GamePlayer* pGamePlayer = (GamePlayer*)pChar;

    pGamePlayer->SetScriptNpc( m_nDstId );

    pGamePlayer->ShowBattleSignUpDlg( m_nDstId, nType, szInfo );

    return true;
}

void CServerVarInterface::SetChallengeScore( int nValue, int nOp )
{
    BaseCharacter* pChar = theRunTimeData.GetCharacterByID( GetCurCharId() );
    if ( pChar == NULL || !pChar->IsPlayer() )
    { return; }

    GamePlayer* pGamePlayer = (GamePlayer*)pChar;
    pGamePlayer->OperateEctypeScore( GetOperateType( nOp ), nValue );
}

int CServerVarInterface::GetChallengeScore()
{
    BaseCharacter* pChar = theRunTimeData.GetCharacterByID( GetCurCharId() );
    if ( pChar == NULL || !pChar->IsPlayer() )
    { return false; }

    GamePlayer* pGamePlayer = (GamePlayer*)pChar;
    return pGamePlayer->GetEctypeScore();
}

bool CServerVarInterface::checkSecondPassword(int checkop)
{
    BaseCharacter* pChar = theRunTimeData.GetCharacterByID( GetCurCharId() );
    if ( pChar == NULL || !pChar->IsPlayer() )
    { return false;}

    GamePlayer* pGamePlayer = (GamePlayer*)pChar;
    //return pGamePlayer->CheckSecondPasswordOperate(checkop);
    // TODO
    return true;
}

void CServerVarInterface::CallMailList()
{
    BaseCharacter* pChar = theRunTimeData.GetCharacterByID( GetCurCharId() );
    if ( pChar == NULL || !pChar->IsPlayer() )
    { return; }

    GamePlayer* pGamePlayer = (GamePlayer*)pChar;

    GS2CSMailListReq msg;
    msg.accountId = pGamePlayer->GetAccountID();
    msg.charDbId  = pGamePlayer->GetDBCharacterID();
    GettheServer().SendMsgToCenterServer( &msg );
}

bool CServerVarInterface::FlyToPlayer( int nType )
{
    BaseCharacter* pChar = theRunTimeData.GetCharacterByID( GetCurCharId() );
    if ( pChar == NULL || !pChar->IsPlayer() )
    { return false; }

    GamePlayer* pPlayer = static_cast< GamePlayer* >( pChar );
    return pPlayer->FlyToPlayer( nType );
}

void CServerVarInterface::AddTeamBattleIntegral( int nIntegral )
{
    BaseCharacter* pChar = theRunTimeData.GetCharacterByID( GetCurCharId() );
    if ( pChar == NULL || !pChar->IsPlayer() )
    { return; }

    GamePlayer* pPlayer = static_cast< GamePlayer* >( pChar );

    pPlayer->AddTeamBattleIntegral( nIntegral, 0, 0 );
}


void CServerVarInterface::SetNpcShow( GameObjectId ustNpcID, unsigned int nSpaceTime )
{
    BaseCharacter* pChar = NULL;
    BaseCharacter* pPlayer = theRunTimeData.GetCharacterByID( GetCurCharId() ); // 得到当前触发脚本的玩家
    if (pPlayer == NULL)
    { return; }

    if ( ustNpcID != 0 )    // ustNpcID == 0 是指挂在本NPC身上
    {
        pChar = theRunTimeData.GetCharacterByNpcID( ustNpcID, pPlayer->GetMapID() );
    }
    else
    {
        pChar = theRunTimeData.GetCharacterByID( m_nDstId );
    }
    if ( pChar == NULL || !pChar->IsNpc() )
    { return; }

    NpcBaseEx* pNpc = static_cast< NpcBaseEx* >( pChar );

    pNpc->StartShowTimer( HQ_TimeGetTime(), nSpaceTime * 1000 );
}

void CServerVarInterface::SetNpcHide( GameObjectId ustNpcID, unsigned int nSpaceTime )
{
    BaseCharacter* pChar = NULL;
    BaseCharacter* pPlayer = theRunTimeData.GetCharacterByID( GetCurCharId() ); // 得到当前触发脚本的玩家
    if (pPlayer == NULL)
    { return; }

    if ( ustNpcID != 0 )    // ustNpcID == 0 是指挂在本NPC身上
    {
        pChar = theRunTimeData.GetCharacterByNpcID( ustNpcID, pPlayer->GetMapID() );
    }
    else
    {
        pChar = theRunTimeData.GetCharacterByID( m_nDstId );
    }
    if ( pChar == NULL || !pChar->IsNpc() )
    { return; }

    NpcBaseEx* pNpc = static_cast< NpcBaseEx* >( pChar );

    pNpc->StartHideTimer( HQ_TimeGetTime(), nSpaceTime * 1000 );
}

void CServerVarInterface::AddSkillPoint( int nType, int nValue )
{
    BaseCharacter* pChar = RunTimeData::GetInstance().GetCharacterByID( GetCurCharId() );
    if ( pChar == NULL || !pChar->IsPlayer() )
    { return; }

    GamePlayer* pPlayer = static_cast< GamePlayer* >( pChar );
    pPlayer->Script_SetSkillPoint( nType, nValue, SKW_SETADD );
}

void CServerVarInterface::SubSkillPoint( int nType, int nValue )
{
    BaseCharacter* pChar = theRunTimeData.GetCharacterByID( GetCurCharId() );
    if ( pChar == NULL || !pChar->IsPlayer() )
    { return; }

    GamePlayer* pPlayer = static_cast< GamePlayer* >( pChar );
    pPlayer->Script_SetSkillPoint( nType, nValue, SKW_SETSUB );
}

void CServerVarInterface::SetSkillPoint( int nType, int nValue )
{
    BaseCharacter* pChar = theRunTimeData.GetCharacterByID( GetCurCharId() );
    if ( pChar == NULL || !pChar->IsPlayer() )
    { return; }

    GamePlayer* pPlayer = static_cast< GamePlayer* >( pChar );
    pPlayer->Script_SetSkillPoint( nType, nValue, SKW_SET );
}

unsigned short CServerVarInterface::GetSkillPoint( int nType )
{
    BaseCharacter* pChar = theRunTimeData.GetCharacterByID( GetCurCharId() );
    if ( pChar == NULL || !pChar->IsPlayer() )
    { return 0; }

    GamePlayer* pPlayer = static_cast< GamePlayer* >( pChar );
    return pPlayer->GetRecipeSkillPoint( nType );
}

void CServerVarInterface::TriggerAchieveByType( uint16 nValueType, int32 nValue, bool bAddValue )
{
    BaseCharacter* pChar = theRunTimeData.GetCharacterByID( GetCurCharId() );
    if ( pChar == NULL || !pChar->IsPlayer() )
    { return ; }

    GamePlayer* pPlayer = static_cast< GamePlayer* >( pChar );
    pPlayer->_achieveManager.UpdateTriggerByValueType( nValueType, nValue, bAddValue);
}

void CServerVarInterface::TriggerAchieveByID  ( uint16 nId )
{
    BaseCharacter* pChar = theRunTimeData.GetCharacterByID( GetCurCharId() );
    if ( pChar == NULL || !pChar->IsPlayer() )
    { return ; }

    GamePlayer* pPlayer = static_cast< GamePlayer* >( pChar );
    pPlayer->_achieveManager.TriggerFinishAchieve( nId );
}

void CServerVarInterface::TriggerDeathAchieveByType( uint16 nValueType )
{
    BaseCharacter* pChar = theRunTimeData.GetCharacterByID( GetCurCharId() );
    if ( pChar == NULL || !pChar->IsPlayer() )
    { return ; }

    GamePlayer* pPlayer = static_cast< GamePlayer* >( pChar );

    GameStage* pStage = theGameWorld.GetStageById( pPlayer->GetMapID() );
    if ( pStage != NULL && pStage->IsEctypeStage() )
    {
        pPlayer->_achieveManager.UpdateTriggerByValueType( nValueType, pStage->GetPlayerDeathCount( pPlayer ) );
    }
}

int CServerVarInterface::OnNpcShip()
{
    BaseCharacter* pChar = theRunTimeData.GetCharacterByID( GetCurCharId() );
    if ( pChar == NULL || !pChar->IsPlayer() )
    { return 0; }

    GamePlayer* pPlayer = static_cast< GamePlayer* >( pChar );
    return pPlayer->OnNpcShip() ? 1 : 0;
}

int CServerVarInterface::GetTargetId()
{
    BaseCharacter* pChar = theRunTimeData.GetCharacterByID(GetDstId());
    if (pChar == NULL)
    { return 0;}

    if (pChar->IsNpc())
    {
        NpcBaseEx* pNpc = static_cast<NpcBaseEx*>( pChar );
        return pNpc->GetNpcID();
    }
    else if (pChar->IsMonster())
    {
        MonsterBaseEx* pMonster = static_cast<MonsterBaseEx*>( pChar );
        return pMonster->GetMonsterID();
    }
    //else if (pChar->IsItem())
    //{
    //    ItemCharacter* pItem = static_cast<ItemCharacter*>( pChar );
    //    return pItem->get
    //}

    return 0;
}

int CServerVarInterface::GetMonsterTypeStatus()
{
    BaseCharacter* pChar = theRunTimeData.GetCharacterByID( GetDstId() );
    if ( pChar == NULL || !pChar->IsMonster() )
    { return 0; }

    MonsterBaseEx* pMonster = static_cast< MonsterBaseEx* >( pChar );

    return pMonster->GetMonsterStatus();
}

void CServerVarInterface::ChangeMonsterTypeStatus( int nStatus )
{
    BaseCharacter* pChar = theRunTimeData.GetCharacterByID( GetDstId() );
    if ( pChar == NULL || !pChar->IsMonster() )
    { return; }

    MonsterBaseEx* pMonster = static_cast< MonsterBaseEx* >( pChar );

    pMonster->ProcessMonsterStatusChange( nStatus );
}

void CServerVarInterface::PlayMovie( unsigned int nMovieId, DWORD dwPlayTime )
{
    BaseCharacter* pChar = theRunTimeData.GetCharacterByID( GetCurCharId() );
    if ( pChar == NULL )
    { return; }

    MsgPlayMovieReq msg;
    msg.header.stID = m_nCurCharId; // 当前的动态ID
    msg.nMovieId = nMovieId;
    msg.dwPlayTime = dwPlayTime;
    GettheServer().SendMsgToSingle( &msg, pChar );
}

void CServerVarInterface::StartEventByID( uint16 nEventID, bool bBroadcast )
{
    BaseCharacter* pChar = theRunTimeData.GetCharacterByID( GetCurCharId() );
    if ( pChar == NULL )
    { return; }

    GamePlayer* pPlayer = (GamePlayer*)pChar;
    MsgStartEvent msg;
    msg.header.stID = pPlayer->GetID();
    msg.usEventID = nEventID;

    if ( bBroadcast )	
    { 
        pPlayer->SetCurEventID( nEventID ); 
        msg.ucBroadcast = MsgStartEvent::ENB_Broadcast;
        GettheServer().SendMsgToView( &msg, pPlayer->GetID(), false );		
    }
    else	// 不需要广播的 服务器就不保存了
    {
        msg.ucBroadcast = MsgStartEvent::ENB_NoBroadcast;
        GettheServer().SendMsgToSingle( &msg, pPlayer );
    }
	//为神马客户端没有实现???tell me why 亲!   by vvx 2012.7.30
}

char CServerVarInterface::GetTPHJRank()
{
	BaseCharacter* pChar = theRunTimeData.GetCharacterByID( GetCurCharId() );
	if ( pChar == NULL || !pChar->IsPlayer() )
	{ return 0; }

	GamePlayer* pPlayer = (GamePlayer*)pChar;
	if (!pPlayer)
	{
		return 0;
	}
	return pPlayer->GetTPHJRank();
}

void CServerVarInterface::SetTPHJRank(char value,int operType)
{
	BaseCharacter* pChar = theRunTimeData.GetCharacterByID( m_nCurCharId );
	if( pChar == NULL || !pChar->IsPlayer() )
	{ return; }

	GamePlayer* pPlayer = (GamePlayer*)pChar;

	pPlayer->SetTPHJRank(value,operType);
}

void CServerVarInterface::SetPetUnactive()
{
	/**********************************************************************
	author:liaojie
	date:2012/08/25
	Desc:取消当前副将出战状态
	**********************************************************************/
	BaseCharacter* pChar = theRunTimeData.GetCharacterByID( GetCurCharId() );
	if( !pChar || !pChar->IsPlayer() )
	{ return ; }

	GamePlayer* pPlayer = (GamePlayer*)pChar;
	if ( !pPlayer )
	{ return ; }
	MsgChangePet Msg;
	Msg.ucOpType = MsgChangePet::EOT_UnActive;
	SPetItem* pPetItem = pPlayer->_petManager.GetActivePet();
	if (!pPetItem)
	{
		return;
	}
	Msg.header.stID = pPlayer->GetID();
	Msg.guid = pPetItem->GetPetGuid();
	Msg.nIndex = pPlayer->_petManager.GetActivePetIndex();
	
	//清除当前出战战马状态
	pPlayer->_petManager.LostActivePetMonster();
	//_petManager.ClearPassiveSkillAffect();
	pPlayer->_petManager.GetActiveSkillBag()->SaveSkillColdTime();
	GettheServer().SendMsgToSingle( &Msg, pPlayer );
}

void CServerVarInterface::PlayAnim(const char* chanim,int times,const char* endanim)
{
	BaseCharacter* pChar = theRunTimeData.GetCharacterByID( GetCurCharId() );
	if( !pChar || !pChar->IsPlayer() )
	{ return ; }

	GamePlayer* pPlayer = (GamePlayer*)pChar;
	if ( !pPlayer )
	{ return ; }

	MsgPlayerPlayAnim msg;
	msg.header.stID = pPlayer->GetID();
	HelperFunc::SafeNCpy( msg.szActionName, chanim, MsgPlayerPlayAnim::eActionNameLength );
	HelperFunc::SafeNCpy( msg.szEndActionName, endanim, MsgPlayerPlayAnim::eActionNameLength );
	msg.nLoopTimes = times;
	GettheServer().SendMsgToView(&msg, pPlayer->GetID(),false);
}

void CServerVarInterface::AskPlatformActivity(int _type)
{
	BaseCharacter* pChar = theRunTimeData.GetCharacterByID( GetCurCharId() );
	if( !pChar || !pChar->IsPlayer() )
	{ return ; }

	GamePlayer* pPlayer = (GamePlayer*)pChar;
	if ( !pPlayer )
	{ return ; }

	MsgGS2CsAskForPlatformActivity msg;
	msg.accountid = pPlayer->GetAccountID();
	msg.characterid = pPlayer->GetDBCharacterID();
	msg._type = _type;
	strncpy_s(msg.charactername,sizeof(msg.charactername),pPlayer->GetCharName(),sizeof(msg.charactername) - 1);
	GettheServer().SendMsgToCenterServer(&msg);
}
void CServerVarInterface::ChangeTimeHandleStates(unsigned int Index,int Value)
{
	theGameGlobalDBManager.SetTimeHandleState(Index,Value);//修改指定时间的状态
}
void CServerVarInterface::ResetTimeHandleStates(unsigned int Index)
{
	TimeHandle* th = theGameTimeHandleManager.GetTimeHandleByTimeLogID(Index);
	if(th)
		th->OnScriptReset();
}
void CServerVarInterface::ClearTimeHandle(unsigned int Index)
{
	theGameGlobalDBManager.SetTimeHandleLog(Index,0);
	theGameGlobalDBManager.SetTimeHandleState(Index,0);
}
void CServerVarInterface::SetWorldBattleCountry(int CountryID)
{
	//设置指定国家的数据
	BaseCharacter* pChar = theRunTimeData.GetCharacterByID( GetCurCharId() );
	if ( pChar == NULL || !pChar->IsPlayer() )
		return;
	GamePlayer* pPlayer = (GamePlayer*)pChar;
	if (!pPlayer)
		return;
	if(CountryID == 0)
	{
		theGameGlobalDBManager.SetMapCountryID(CountryDefine::Country_Init);
	}
	else
	{
		theGameGlobalDBManager.SetMapCountryID(pPlayer->GetCountryId());
	}
	theWorldBattleManager.SetWorldBattleIsResult();
}
bool CServerVarInterface::IsOnBiaoChe()
{
	BaseCharacter* pChar = theRunTimeData.GetCharacterByID( GetCurCharId() );
	if ( pChar == NULL || !pChar->IsPlayer() )
	{ return 0; }

	GamePlayer* pPlayer = (GamePlayer*)pChar;
	if (!pPlayer)
	{
		return 0;
	}
	return pPlayer->IsBiaocheState();
}

void CServerVarInterface::ClearStatusByid(int status_id)
{
	if (status_id <= 0)
	{
		return;
	}

	BaseCharacter* pChar = theRunTimeData.GetCharacterByID( GetCurCharId() );
	if ( pChar == NULL || !pChar->IsPlayer() )
	{ return; }

	GamePlayer* pPlayer = (GamePlayer*)pChar;
	if (!pPlayer)
	{
		return;
	}

	if(pPlayer->GetBuffManager()->ClearBuffByBuffId(status_id))
		pPlayer->OnBuffStatusChanged( true );

}
void CServerVarInterface::ChangeGamePlayerDuration(int Count)
{
	BaseCharacter* pChar = theRunTimeData.GetCharacterByID( GetCurCharId() );
	if ( pChar == NULL || !pChar->IsPlayer() )
	{ return; }
	GamePlayer* pPlayer = (GamePlayer*)pChar;
	if (!pPlayer)
	{
		return;
	}

	pPlayer->SetPetDuration(Count);//直接存储到数据库去
}
void CServerVarInterface::ChangePetMode(int ModeID,int Sec)
{
	BaseCharacter* pChar = theRunTimeData.GetCharacterByID( GetCurCharId() );
	if ( pChar == NULL || !pChar->IsPlayer() )
	{ return; }

	GamePlayer* pPlayer = (GamePlayer*)pChar;
	if (!pPlayer)
	{
		return;
	}
	SPetItem * pPet = pPlayer->_petManager.GetActivePet();
	if(!pPet)
		return;
	pPlayer->SetPetMode(pPet->baseInfo.guid,ModeID,Sec);
}
void CServerVarInterface::UseItem(unsigned short ustItemId)
{
	BaseCharacter *pChar = theRunTimeData.GetCharacterByID( m_nCurCharId );
	if( pChar == NULL || !pChar->IsPlayer() )
	{ return; }

	MsgTellUseItem msg;
	msg.ustItemId = ustItemId;
	GettheServer().SendMsgToSingle( &msg, pChar );
}
unsigned short CServerVarInterface::GetPlayerStates()
{
	BaseCharacter* pChar = theRunTimeData.GetCharacterByID( GetCurCharId() );
	if ( pChar == NULL || !pChar->IsPlayer() )
	{ return -1; }

	GamePlayer* pPlayer = (GamePlayer*)pChar;
	if (!pPlayer)
	{
		return -1;
	}
	return pPlayer->GetStatus();
}
void CServerVarInterface::AddCard(short stCardID, short stLevel)
{
	BaseCharacter *pChar = theRunTimeData.GetCharacterByID( m_nCurCharId );
	if( pChar == NULL || !pChar->IsPlayer() )
		return;

	GamePlayer* pPlayer = (GamePlayer*)pChar;
	if ( !pPlayer )
		return;

	pPlayer->AddCard(stCardID, stLevel);
}
int CServerVarInterface::GetGamePlayerDuration()
{
	BaseCharacter *pChar = theRunTimeData.GetCharacterByID( m_nCurCharId );
	if( pChar == NULL || !pChar->IsPlayer() )
		return 0;

	GamePlayer* pPlayer = (GamePlayer*)pChar;
	if ( !pPlayer )
		return 0;
	return pPlayer->GetPetDuration();
}
void CServerVarInterface::TriggerSevenDays()
{
	BaseCharacter *pChar = theRunTimeData.GetCharacterByID( m_nCurCharId );
	if( pChar == NULL || !pChar->IsPlayer() )
		return;

	GamePlayer* pPlayer = (GamePlayer*)pChar;
	if ( !pPlayer )
		return;

	pPlayer->TriggerSevenDays();
}

 int CServerVarInterface::AddFriendPoint(int distance , int FriendlyPoint)
{

	BaseCharacter *pChar = theRunTimeData.GetCharacterByID( m_nCurCharId );
	if( pChar == NULL || !pChar->IsPlayer() )
		return 10;

	GamePlayer* pPlayer = (GamePlayer*)pChar;
	if ( !pPlayer )
		return 10;

	return pPlayer->AddFriendPoint(distance , FriendlyPoint);

}
 int CServerVarInterface::IsInFight()
 {
	BaseCharacter *pChar = theRunTimeData.GetCharacterByID( m_nCurCharId );
	if( pChar == NULL || !pChar->IsPlayer() )
		return 0;

	GamePlayer* pPlayer = (GamePlayer*)pChar;
	if ( !pPlayer )
		return 0;
	if(pPlayer->HaveFighteFlag(eFighting))
		return 1;
	else
		return 0;
 }
 void CServerVarInterface::SetScriptStates(unsigned short StatesID)
 {
	BaseCharacter *pChar = theRunTimeData.GetCharacterByID( m_nCurCharId );
	if( pChar == NULL || !pChar->IsPlayer() )
		return;

	GamePlayer* pPlayer = (GamePlayer*)pChar;
	if ( !pPlayer )
		return;

	pPlayer->SetScriptStatesID(StatesID);
 }
 bool CServerVarInterface::CanFlyToCouple()
 {
	BaseCharacter *pChar = theRunTimeData.GetCharacterByID( m_nCurCharId );
	if( pChar == NULL || !pChar->IsPlayer() )
		return false;
	GamePlayer* pPlayer = (GamePlayer*)pChar;
	if ( !pPlayer )
		return false;
	//1.判断自己所在地图
	uint32 MapID = pPlayer->GetMapID();
	const CountryConfig::SpecialMapSetting* pSetting = theCountryConfig.GetPrisonMapSetting( pPlayer->GetCountry() );
    if (pSetting && pSetting->GetMapID() == EctypeId2MapId( MapID ) )
		return false;
	if(!theMapConfig.GetMapDataById(MapID) || theMapConfig.GetMapDataById(MapID)->IsEctypeMap() || EctypeId2MapId( MapID ) == 67)
		return false;
	//2.获取目标 根据关系的类型 获取目标的的地图ID 需要目标的ID
	//夫妻之间是否可以传送
	if(!pPlayer->GetRelation()->IsHaveMarriage())
		return false;
	GameRelation * pRelation = theGameRelationManager.GetPlayerRelation(pPlayer->GetRelation()->GetMarriageID());
	if(!pRelation || !pRelation->GetOnLine())
		return false;
	MapID = pRelation->GetMapID();
    if (pSetting && pSetting->GetMapID() == EctypeId2MapId( MapID ) )
		return false;
	if(!theMapConfig.GetMapDataById(MapID) || theMapConfig.GetMapDataById(MapID)->IsEctypeMap() || EctypeId2MapId( MapID ) == 67)
		return false;
	else
		return true;
 }
 void CServerVarInterface::DropQuestEntrust()
 {
	//当前玩家放弃委托
	BaseCharacter *pChar = theRunTimeData.GetCharacterByID( m_nCurCharId );
	if( pChar == NULL || !pChar->IsPlayer() )
		return;
	GamePlayer* pPlayer = (GamePlayer*)pChar;
	if ( !pPlayer )
		return;
	unsigned int ID = theGameQuestEntrustManager.IsExitesJoinQuestEntrust(pPlayer->GetDBCharacterID());
	QuestEntrustStates* pInfo= theGameQuestEntrustManager.GetQuestEntrust(ID);
	if(!pInfo)
		return;
	if(pInfo->DestPlayerID != pPlayer->GetDBCharacterID())
		return;
	//2.发送命令
	QuestEntrustStates states = *pInfo;
	states.DestPlayerID = 0;
	states.ReceiveLogTime = 0;
	strcpy_s(states.DestPlayerName,MaxPlayerNameLength,"");
	theGameQuestEntrustManager.CanelQuestEntrust(states);
 }
 void CServerVarInterface::DoneQuestEntrust()
 {
	BaseCharacter *pChar = theRunTimeData.GetCharacterByID( m_nCurCharId );
	if( pChar == NULL || !pChar->IsPlayer() )
		return;
	GamePlayer* pPlayer = (GamePlayer*)pChar;
	if ( !pPlayer )
		return;
	unsigned int ID = theGameQuestEntrustManager.IsExitesJoinQuestEntrust(pPlayer->GetDBCharacterID());
	QuestEntrustStates* pInfo= theGameQuestEntrustManager.GetQuestEntrust(ID);
	if(!pInfo)
		return;
	if(pInfo->DestPlayerID != pPlayer->GetDBCharacterID())
		return;
	//设置完成委托
	unsigned int MoneySum = theGameQuestEntrustManager.GetConfig().GetQuestMoneySum(pInfo->SrcQuestID);
	//1.获得奖励 发送邮件
	GS2CSSendMailReq xReq;
	xReq.charDbId = RelationDefine::InitID;
	xReq.mail.type  = SMail::EMT_System;
	xReq.mail.state = SMail::EMS_NotOpen;
	xReq.mail.sendTime = TimeEx::GetNowTime();        
	// 发信人
	xReq.mail.owners[EM_FromIndex].charDbId = 0;
	sprintf_s( xReq.mail.owners[EM_FromIndex].addressName, sizeof( xReq.mail.owners[EM_FromIndex] ) - 1, theXmlString.GetString( eText_MailSystemName ) );
	// 收件人	
	xReq.mail.owners[EM_ToIndex].charDbId = pInfo->DestPlayerID;
	HelperFunc::SafeNCpy( xReq.mail.owners[EM_ToIndex].addressName,pInfo->DestPlayerName, sizeof( xReq.mail.owners[EM_ToIndex].addressName ) );

	sprintf_s( xReq.mail.content, sizeof( xReq.mail.content ) - 1,theXmlString.GetString( eText_QuestEntrust_SeccContent ) );
	sprintf_s( xReq.mail.title, sizeof( xReq.mail.title ) - 1, theXmlString.GetString( eText_QuestEntrust_SeccTitle ) );

	if(pInfo->ItemInfo.itembaseinfo.nOnlyInt == 0)
	{
		xReq.mail.accessory.type = SMail::EAT_None;
	}
	else
	{
		xReq.mail.accessory.type = SMail::EAT_Item;//2是坐骑,1是物品
		memcpy( &xReq.mail.accessory.content,  &pInfo->ItemInfo, sizeof(SCharItem) ); 
	}
	//设置金钱 或者元宝
	xReq.mail.money = pInfo->EntrustRewardSum + MoneySum;
	GettheServer().SendMsgToCenterServer( &xReq );
	//3.发送命令道Center去
	GS2CSQuestEntrustSeccReq msg;
	msg.ID =ID;
	GettheServer().SendMsgToCenterServer( &msg );
 }
 void CServerVarInterface::CanelQuestEntrust(int nQuestID)
 {
	BaseCharacter *pChar = theRunTimeData.GetCharacterByID( m_nCurCharId );
	 if( pChar == NULL || !pChar->IsPlayer() )
		 return;

	 GamePlayer* pPlayer = (GamePlayer*)pChar;
	 if ( !pPlayer )
		 return;
	vector<unsigned int> vec;
	if(!theGameQuestEntrustManager.IsExitesQuestEntrust(pPlayer->GetDBCharacterID(),nQuestID,vec))
		return;
	vector<unsigned int>::iterator Iter = vec.begin();
	for(;Iter != vec.end();++Iter)
	{
		QuestEntrustStates* pInfo= theGameQuestEntrustManager.GetQuestEntrust(*Iter);
		if(!pInfo)
			return;
		if(pInfo->SrcPlayerID != pPlayer->GetDBCharacterID())
			return;
		theGameQuestEntrustManager.DelQuestEntrust(*Iter);//发送命令
	}
 }
 int CServerVarInterface::GetTodayHuntingCount()
 {
	 BaseCharacter *pChar = theRunTimeData.GetCharacterByID( m_nCurCharId );
	 if( pChar == NULL || !pChar->IsPlayer() )
		 return 0;

	 GamePlayer* pPlayer = (GamePlayer*)pChar;
	 if ( !pPlayer )
		 return 0;

	 return pPlayer->GetTodayHuntingCount();
 }

 void CServerVarInterface::OperateHuntingCount( int nType, int nValue )
 {
	 BaseCharacter *pChar = theRunTimeData.GetCharacterByID( m_nCurCharId );
	 if( pChar == NULL || !pChar->IsPlayer() )
		 return;

	 GamePlayer* pPlayer = (GamePlayer*)pChar;
	 if ( !pPlayer )
		 return;

	 pPlayer->OperateHuntingCount( nType, nValue );
 }

 void CServerVarInterface::DoneHuntingQuest( int nQuestId )
 {
	 BaseCharacter *pChar = theRunTimeData.GetCharacterByID( m_nCurCharId );
	 if( pChar == NULL || !pChar->IsPlayer() )
		 return;

	 GamePlayer* pPlayer = (GamePlayer*)pChar;
	 if ( !pPlayer )
		 return;

	 pPlayer->DoneHuntingQuest( nQuestId );
 }
 int CServerVarInterface::FlytoPosition(int Type)
 {
	 BaseCharacter *pChar = theRunTimeData.GetCharacterByID( m_nCurCharId );
	 if( pChar == NULL || !pChar->IsPlayer() )
		 return 1;

	 GamePlayer* pPlayer = (GamePlayer*)pChar;
	 if ( !pPlayer )
		 return 1;
	//1.将玩家的位置信息和类型 发送到Center服务器去
	MapConfig::MapData* pMapData =  theMapConfig.GetMapDataById(pPlayer->GetMapID());
	if(!pMapData)
		return 3;
	if(pMapData->IsEctypeMap())
		return 4;
	//将指定类型的玩家发送命令
	MsgFlyToPosition msg;
	msg.MapID = pPlayer->GetMapID();
	msg.Pos_X = pPlayer->GetFloatX();
	msg.Pos_Y = pPlayer->GetFloatY();
	msg.Type = Type;
	switch(Type)
	{
	case 1:
		{
			//GUILD
			GameGuild* pGuild = theGameGuildManager.GetGuild(pPlayer->GetGuildID());
			if(!pGuild)
				return 2;
			pGuild->SendMessageToGuild(&msg,pPlayer->GetDBCharacterID(),0,true);
		}
		break;
	case 2:
		{
			 GettheServer().SendMsgToCountry( &msg, pPlayer->GetCountryId(), true ,0,pPlayer->GetDBCharacterID());
		}
		break;
	}
	return 0;
 }
 void CServerVarInterface::AddHonourByTeam(int Num)
 {
	//给指定队伍添加指定数量的荣誉
	BaseCharacter *pChar = theRunTimeData.GetCharacterByID( m_nCurCharId );
	 if( pChar == NULL || !pChar->IsPlayer() )
		 return;
	 GamePlayer* pPlayer = (GamePlayer*)pChar;
	 if ( !pPlayer )
		 return;
	GameTeam* pTeam = theGameTeamManager.GetTeam( pPlayer->GetTeamID() );
	if(pTeam)
	{
		unsigned int nAreaCount = pTeam->GetTeamMemberCountInMap( pPlayer->GetMapID(), pPlayer->GetFloatX(), pPlayer->GetFloatY() );
		if ( nAreaCount == 0 ) 
		{ nAreaCount = 1;}

		for( int i = 0; i < pTeam->TeamMemberCount(); ++i )
		{
			GamePlayer* pTeamPlayer = pTeam->GetMemberPlayer( pTeam->GetMemberIDByIndex( i ) );
			if ( pTeamPlayer == NULL ) 
			{ continue; }

			if( !pTeamPlayer->IsPlayer() || !pTeamPlayer->IsInMapArea(pPlayer->GetMapID(), pPlayer->GetFloatX(), pPlayer->GetFloatY(),g_Cfg.TeamHonourDis) )
			{ continue; }
			
			pTeamPlayer->OperateHonour( EOT_Add, Num, __FUNCTION__, __LINE__ ,ePlayerMoneySourceType_KillPerson);
		}
	}
	else
	{
		pPlayer->OperateHonour( EOT_Add, Num, __FUNCTION__, __LINE__ ,ePlayerMoneySourceType_KillPerson);
	}
 }
int CServerVarInterface::GetStrongCountry()
 {
	//获取强国的ID
	return theGameCountryManager.GetStrongCountry();
 }
int CServerVarInterface::GetWeakCountry()
{
	return theGameCountryManager.GetWeakCountry();
}
void CServerVarInterface::ChangePlayerPoint(int Op,int Value,int States)
{
	//对玩家的点数进行操控
	BaseCharacter *pChar = theRunTimeData.GetCharacterByID( m_nCurCharId );
	if( pChar == NULL || !pChar->IsPlayer() )
		return;
	if(Op != 0 && Op != 1 && Op!=2)
		return;
	GamePlayer* pPlayer = (GamePlayer*)pChar;
	if ( !pPlayer )
		return;
	unsigned int ID = 0;
	switch(States)
	{
	case 0:
		ID = pPlayer->GetDBCharacterID();
		break;
	case 1:
		{
			GameGuild* pGuild = theGameGuildManager.GetGuild(pPlayer->GetGuildID());
			if(!pGuild)
				return;//无公会
			ID = pPlayer->GetGuildID();
		}
		break;
	case 2:
		{
			ID = pPlayer->GetCountry();
			if(ID == CountryDefine::Country_Init)
				return;//无国籍
		}
		break;
	default:
		return;
		break;
	}

	GS2DBUpdatePlayerPoint msg;
	msg.PlayerID = pPlayer->GetDBCharacterID();
	msg.ID = ID;
	msg.Op = Op;
	msg.Value = Value;
	msg.States = States;
	GettheDBCon().SendMsg( &msg,pPlayer->GetLifeCode());
}
void CServerVarInterface::SetMonsterArray(int Index,int Value)
{
	BaseCharacter* pChar = theRunTimeData.GetCharacterByID( GetDstId() );
    if ( pChar == NULL || !pChar->IsMonster() )
    { return; }

    MonsterBaseEx* pMonster = static_cast< MonsterBaseEx* >( pChar );
	if(!pMonster)
		return;
    pMonster->SetParamValue(Index,Value);
}
int	CServerVarInterface::GetMonsterArray(int Index)
{
	BaseCharacter* pChar = theRunTimeData.GetCharacterByID( GetDstId() );
    if ( pChar == NULL || !pChar->IsMonster() )
    { return -1; }

    MonsterBaseEx* pMonster = static_cast< MonsterBaseEx* >( pChar );
	if(!pMonster)
		return -1;
    return pMonster->GetParamValue( Index );
}

#pragma warning( pop )