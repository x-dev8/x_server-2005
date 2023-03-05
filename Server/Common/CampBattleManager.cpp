#include "CampBattleManager.h"
#include "CampBattle.h"
#include "CampBattleMessage.h"
#include "GameServer.h"
#include "GamePlayer.h"
#include "CampBattleConfig.h"
#include "Configure.h"
#include "GameWorld.h"
#include "ShareData.h"
//#include "TeamManager.h"
CampBattleManager::CampBattleManager() : m_uchBattleStatus( CampDefine::StatusInit ), m_uchCountryID( 0 ), m_uchBattleType( 0 ), m_nLeftTime( 0 ),m_BattleValue(0),m_BattleValueIsOpen(false)
{
    m_vecSignUp.clear();
    m_mapCampBattle.clear();

    m_pBattleConfig = NULL;

	m_nConfigMapID = 0xffffffff;
}

CampBattleManager::~CampBattleManager()
{
    for ( CampBattleMapIter iter = m_mapCampBattle.begin(); iter != m_mapCampBattle.end(); ++iter )
    {
        iter->second->Release();
    }
    m_mapCampBattle.clear();
}

void CampBattleManager::RunUpdate( unsigned int nCurrentTime )
{
    static SYSTEMTIME xSystemTime;
    ::GetLocalTime( &xSystemTime );

    // 状态更新
    switch ( GetBattleStatus() )
    {
    case CampDefine::StatusInit:        
        // 战场初始状态
        ProcessBattleInitStatus( nCurrentTime, xSystemTime.wDayOfWeek, xSystemTime.wHour, xSystemTime.wMinute );
        break;
    case CampDefine::StatusSignUp:
        // 战场报名状态
        ProcessBattleSignUpStatus( nCurrentTime, xSystemTime.wDayOfWeek, xSystemTime.wHour, xSystemTime.wMinute );
        break;
    case CampDefine::StatusPrepare:
        // 战场准备状态
        ProcessBattlePrepareStatus( nCurrentTime, xSystemTime.wDayOfWeek, xSystemTime.wHour, xSystemTime.wMinute );
        break;
    case CampDefine::StatusEnter:
        // 战场进入状态
        ProcessBattleEnterStatus( nCurrentTime, xSystemTime.wDayOfWeek, xSystemTime.wHour, xSystemTime.wMinute );
        break;
    case CampDefine::StatusFight:
        // 战场战斗状态
        ProcessBattleFightStatus( nCurrentTime, xSystemTime.wDayOfWeek, xSystemTime.wHour, xSystemTime.wMinute );
        break;
    case CampDefine::StatusEnd:
        // 战场结束状态
        ProcessBattleEndStatus();
        break;
    default:
        SetBattleStatus( CampDefine::StatusInit );
        break;
    }

    // 处理状态剩余时间
    ProcessBattleLeftTime( nCurrentTime );

    // 战场更新
    for ( CampBattleMapIter iter = m_mapCampBattle.begin(); iter != m_mapCampBattle.end(); )
    {
        switch ( iter->second->RunUpdate( nCurrentTime ) )
        {
        case CampDefine::StatusRelease:
            {
                iter->second->Release();
                iter = m_mapCampBattle.erase( iter );
            }
            break;
        default:
            ++iter;
            break;
        }
    }
}

void CampBattleManager::ProcessBattleInitStatus( unsigned int nCurrentTime, int nDayOfWeek, int nHour, int nMinute )
{
    // 判断是否到了战场准备时间
    if ( !CheckBattleSignUpTime( nCurrentTime, nDayOfWeek, nHour, nMinute ) )
    { return; }

    // 处理战场改变到准备状态
    ProcessChangeStatus( CampDefine::StatusSignUp );
}

void CampBattleManager::ProcessBattleSignUpStatus( unsigned int nCurrentTime, int nDayOfWeek, int nHour, int nMinute )
{
    if ( !CheckBattlePrepareTime( nCurrentTime, nDayOfWeek, nHour, nMinute ) )
    { return; }

    // 处理战场改变到进入状态
    ProcessChangeStatus( CampDefine::StatusPrepare );
}

void CampBattleManager::ProcessBattlePrepareStatus( unsigned int nCurrentTime, int nDayOfWeek, int nHour, int nMinute )
{
    if ( !CheckBattleEnterTime( nCurrentTime, nDayOfWeek, nHour, nMinute ) )
    { return; }

    // 处理战场改变到进入状态
    ProcessChangeStatus( CampDefine::StatusEnter );
}

void CampBattleManager::ProcessBattleEnterStatus( unsigned int nCurrentTime, int nDayOfWeek, int nHour, int nMinute )
{
    if ( !CheckBattleFightTime( nCurrentTime, nDayOfWeek, nHour, nMinute ) )
    { return; }

    // 处理战场改变到战斗状态
    ProcessChangeStatus( CampDefine::StatusFight );
}

void CampBattleManager::ProcessBattleFightStatus( unsigned int nCurrentTime, int nDayOfWeek, int nHour, int nMinute )
{
    if ( !CheckBattleEndTime( nCurrentTime, nDayOfWeek, nHour, nMinute ) )
    { return; }

    // 处理战场改变到处理结果状态
    ProcessChangeStatus( CampDefine::StatusEnd );
}

void CampBattleManager::ProcessBattleEndStatus()
{
    SetBattleStatus( CampDefine::StatusInit );
}

void CampBattleManager::ProcessChangeStatus( unsigned char uchStatus )
{
    // 设置状态
    SetBattleStatus( uchStatus );

    switch( GetBattleStatus() )
    {
		//报名状态
    case CampDefine::StatusSignUp:
        ProcessChangeToSignUpStatus();
        break;
		//准备状态
    case CampDefine::StatusPrepare:
        ProcessChangeToPrepareStatus();
        break;
    case CampDefine::StatusEnter:
        ProcessChangeToEnterStatus();
        break;
    case CampDefine::StatusFight:
        ProcessChangeToFightStatus();
        break;
	case CampDefine::StatusEnd:
		ProcessChangeToEndStatus();
		break;
    default:
        break;
    }

    // 发送战场状态改变消息(如果战场不在此GAME SERVER上则不用发送) by vvx 2013.3.28
	if (0xffffffff != m_nConfigMapID)
	{
		SendBattleStatusMessage( GetBattleStatus() );
	}
}

void CampBattleManager::SendBattleStatusMessage( unsigned char uchStatus )
{
    switch ( uchStatus )
    {
    case CampDefine::StatusSignUp:
    case CampDefine::StatusPrepare:
    case CampDefine::StatusEnter:
        {
            // 这3个状态发送给全国
			MsgTellCampBattleStatus xTell;
			xTell.uchCampBattleType   = GetBattleType();
			xTell.uchCampBattleStatus = uchStatus;
			xTell.nLeftTime           = GetLeftTime() / 1000;
			if(GetCountryID() == 0)
			{
				GettheServer().SendMsgToWorld(&xTell,true);//无国家划分 发送全部玩家
			}
			else
			{
				GettheServer().SendMsgToCountry( &xTell, GetCountryID(), true );
			}
        }
        break;
    case CampDefine::StatusFight:
    case CampDefine::StatusEnd:
        {
            // 这2个状态发功给战场地图
            for ( CampBattleMapIter iter = m_mapCampBattle.begin(); iter != m_mapCampBattle.end(); ++iter )
            {
                // 设置状态
                iter->second->ProcessStatusChange( uchStatus );
            }
        }
        break;
    default:
        break;
    }
}

// 判断是否到了战场报名时间
bool CampBattleManager::CheckBattleSignUpTime( unsigned int nCurrentTime, int nDayOfWeek, int nHour, int nMinute )
{
    const CampBattleConfig::TimeSetting* pSetting = m_pBattleConfig->CheckSignUpTimeSetting( nDayOfWeek, nHour, nMinute );
    if ( pSetting == NULL )
    { return false; }

    SetLeftTime( pSetting->GetKeepTime() * OneMinuteMicroSecond );
    m_nLastUpdateTime = nCurrentTime;

    return true;
}

// 判断是否到了战场准备时间
bool CampBattleManager::CheckBattlePrepareTime( unsigned int nCurrentTime, int nDayOfWeek, int nHour, int nMinute )
{
    const CampBattleConfig::TimeSetting* pSetting = m_pBattleConfig->CheckPrepareTimeSetting( nDayOfWeek, nHour, nMinute );
    if ( pSetting == NULL )
    { return false; }

    SetLeftTime( pSetting->GetKeepTime() * OneMinuteMicroSecond );
    m_nLastUpdateTime = nCurrentTime;

    return true;
}

// 判断是否到了战场进入时间
bool CampBattleManager::CheckBattleEnterTime( unsigned int nCurrentTime, int nDayOfWeek, int nHour, int nMinute )
{
    const CampBattleConfig::TimeSetting* pSetting = m_pBattleConfig->CheckEnterTimeSetting( nDayOfWeek, nHour, nMinute );
    if ( pSetting == NULL )
    { return false; }

    SetLeftTime( pSetting->GetKeepTime() * OneMinuteMicroSecond );
    m_nLastUpdateTime = nCurrentTime;

    return true;
}

// 判断是否到了战场战斗时间
bool CampBattleManager::CheckBattleFightTime( unsigned int nCurrentTime, int nDayOfWeek, int nHour, int nMinute )
{
    const CampBattleConfig::TimeSetting* pSetting = m_pBattleConfig->CheckFightTimeSetting( nDayOfWeek, nHour, nMinute );
    if ( pSetting == NULL )
    { return false; }

    SetLeftTime( pSetting->GetKeepTime() * OneMinuteMicroSecond );
    m_nLastUpdateTime = nCurrentTime;

    return true;
}

// 判断是否到了战场结束时间
bool CampBattleManager::CheckBattleEndTime( unsigned int nCurrentTime, int nDayOfWeek, int nHour, int nMinute )
{
    const CampBattleConfig::TimeSetting* pSetting = m_pBattleConfig->CheckEndTimeSetting( nDayOfWeek, nHour, nMinute );
    if ( pSetting == NULL )
    { return false; }

    SetLeftTime( 0 );
    m_nLastUpdateTime = nCurrentTime;

    return true;
}

void CampBattleManager::ProcessBattleLeftTime( unsigned int nCurrentTime )
{
    // 获得过了多少时间
    unsigned int nPassTime = GameTime::GetPassTime( nCurrentTime, m_nLastUpdateTime );
    SubLeftTime( nPassTime );   // 设置剩余时间

    m_nLastUpdateTime = nCurrentTime;
}

// 处理转换到报名状态逻辑
void CampBattleManager::ProcessChangeToSignUpStatus()
{
    m_vecSignUp.clear();

    // 设置战场国家, 和战场MapConfig ID
    for ( int i = 0; i < m_pBattleConfig->GetMapSettingCount(); ++i )
    {
        const CampBattleConfig::MapSetting* pSetting = m_pBattleConfig->GetMapSetting( i );
        if ( pSetting == NULL )
        { continue; }

        if ( !g_Cfg.IsMapRun( pSetting->GetMapID() ) )
        { continue; }       // 没有开地图

        SetMapID( pSetting->GetMapID() );
        SetCountryID( pSetting->GetCountryID() );

		const CampBattleConfig::CKingdomMap &xKingdomMap = m_pBattleConfig->GetKingdomMap();

		SetkingdomMapInfo(xKingdomMap.GetMapID(),
						  xKingdomMap.GetMapX(),
						  xKingdomMap.GetMapY());
    }
}
void CampBattleManager::ProcessChangeToFightStatus()
{
	//战场正式开始战斗 去除地图内全部玩家的BUFF
	
}
// 添加一个报名的ID
void CampBattleManager::AddSignUpUnit( unsigned int nUnitID )
{
    SignUpVectorIter iter = std::find( m_vecSignUp.begin(), m_vecSignUp.end(), nUnitID );
    if ( iter != m_vecSignUp.end() )
    { return; }

    m_vecSignUp.push_back( nUnitID );
}

// 判断是否已经报名了
bool CampBattleManager::IsSignUpUnit( unsigned int nUnitID )
{
    return std::find( m_vecSignUp.begin(), m_vecSignUp.end(), nUnitID ) != m_vecSignUp.end();
}

// 删除一个报名的ID
void CampBattleManager::RemoveSignUpUnit( unsigned int nUnitID )
{
    SignUpVectorIter iter = std::find( m_vecSignUp.begin(), m_vecSignUp.end(), nUnitID );
    if ( iter == m_vecSignUp.end() )
    { return; }

    m_vecSignUp.erase( iter );
}


void CampBattleManager::AddCampBattle( CampBattle* pCampBattle )
{
    if ( pCampBattle == NULL )
    { return; }

    m_mapCampBattle[ pCampBattle->GetBattleMapID() ] = pCampBattle;
}

CampBattle* CampBattleManager::GetCampBattleByMapID( unsigned int nMapID )
{
    CampBattleMapIter iter = m_mapCampBattle.find( nMapID );
    if ( iter == m_mapCampBattle.end() )
    { return NULL; }

    return iter->second;
}

CampBattle* CampBattleManager::GetCampBattleByPlayerID( unsigned int nPlayerID )
{
    for ( CampBattleMapIter iter = m_mapCampBattle.begin(); iter != m_mapCampBattle.end(); ++iter )
    {
        BattlePlayer* pBattlePlayer = iter->second->GetBattlePlayer( nPlayerID );
        if ( pBattlePlayer != NULL )
        { return iter->second; }
    }

    return NULL;
}

CampBattle* CampBattleManager::GetCampBattleByUnitID( unsigned int nUnitID )
{
    for ( CampBattleMapIter iter = m_mapCampBattle.begin(); iter != m_mapCampBattle.end(); ++iter )
    {
        if ( iter->second->GetRedID() == nUnitID || iter->second->GetBlueID() == nUnitID )
        { return iter->second; }
    }

    return NULL;
}


bool CampBattleManager::ShowCampBattleSignUp( GamePlayer* pPlayer )
{
    if ( pPlayer == NULL )
    { return false; }

    if ( GetBattleStatus() != CampDefine::StatusSignUp )
    { return false; }

    return true;
}

bool CampBattleManager::SignUpCampBattle( GamePlayer* pPlayer, unsigned int nUnitID)
{
    if ( pPlayer == NULL )
    { return false; }

    if ( GetBattleStatus() != CampDefine::StatusSignUp )
    {
        pPlayer->SendOperateAckToClient< MsgCampBattleSignUpAck >( CampDefine::SignUp_NotSignUpStatus );
        return false;
    }

	if(GetCountryID() != 0 && GetCountryID() != pPlayer->GetCountry())
		return false;

    if ( IsSignUpUnit( nUnitID ) )
    {
        pPlayer->SendOperateAckToClient< MsgCampBattleSignUpAck >( CampDefine::SignUp_AlreadySignUp );
        return false;
    }

    return true;
}

bool CampBattleManager::ShowCampBattleEnter( GamePlayer* pPlayer, unsigned int nUnitID )
{
    if ( pPlayer == NULL )
    { return false; }

	//判断玩家的权限
	/*unsigned int Value = 0;
	bool IsOpen = true;
	switch(m_uchBattleType)
	{
	case CampDefine::BattleTypeKing:
		{
			Value = GuildDefine::CampBattleCountry;
			IsOpen = theGameGuildManager.GetCampBattleConfig()->m_CountrySetting.IsOpen;
		}
		break;
	case CampDefine::BattleTypeGuild:
		{
			Value = GuildDefine::CampBattleGuild;
			IsOpen = theGameGuildManager.GetCampBattleConfig()->m_CountrySetting.IsOpen;
		}
		break;
	case CampDefine::BattleTypeGuildUnion:
		{
			Value = GuildDefine::CampBattleGuildUnion;
			IsOpen = theGameGuildManager.GetCampBattleConfig()->m_GuildUnionSetting.IsOpen;
		}
		break;
	}
	if(Value != 0 && IsOpen)
	{
		GameGuild * pGuild = theGameGuildManager.GetGuild(pPlayer->GetGuildID());
		if(!pGuild)
			return false;
		GuildMember * pMember = pGuild->GetMember(pPlayer->GetDBCharacterID()) ;
		if(!pMember)
			return false;
		if(!(pMember->GetCampBattleValue() & Value))
			return false;
	}*/
	if(m_BattleValue !=0 && m_BattleValueIsOpen)
	{
		GameGuild * pGuild = theGameGuildManager.GetGuild(pPlayer->GetGuildID());
		if(!pGuild)
			return false;
		GuildMember * pMember = pGuild->GetMember(pPlayer->GetDBCharacterID()) ;
		if(!pMember)
			return false;
		if(!(pMember->GetCampBattleValue() & m_BattleValue))
			return false;
	}


	if ( GetBattleStatus() != CampDefine::StatusEnter )
    { return false; }

    CampBattle* pCampBattle = GetCampBattleByUnitID( nUnitID );
    if ( pCampBattle == NULL )
    { return false; }

    MsgShowCampGuildBattleEnter xShow;
    xShow.uchBattleType = GetBattleType();
    xShow.nRedGuildID   = pCampBattle->GetRedID();
    xShow.nBlueGuildID  = pCampBattle->GetBlueID();
    pPlayer->SendMessageToClient( &xShow );

    return true;
}

bool CampBattleManager::EnterCampBattle( GamePlayer* pPlayer, unsigned int nUnitID )
{
    if ( pPlayer == NULL )
    { return false; }

	//判断玩家的权限
	/*unsigned int Value = 0;
	bool IsOpen = true;
	switch(m_uchBattleType)
	{
	case CampDefine::BattleTypeKing:
		{
			Value = GuildDefine::CampBattleCountry;
			IsOpen = theGameGuildManager.GetCampBattleConfig()->m_CountrySetting.IsOpen;
		}
		break;
	case CampDefine::BattleTypeGuild:
		{
			Value = GuildDefine::CampBattleGuild;
			IsOpen = theGameGuildManager.GetCampBattleConfig()->m_CountrySetting.IsOpen;
		}
		break;
	case CampDefine::BattleTypeGuildUnion:
		{
			Value = GuildDefine::CampBattleGuildUnion;
			IsOpen = theGameGuildManager.GetCampBattleConfig()->m_GuildUnionSetting.IsOpen;
		}
		break;
	}
	if(Value != 0 && IsOpen)
	{
		GameGuild * pGuild = theGameGuildManager.GetGuild(pPlayer->GetGuildID());
		if(!pGuild)
			return false;
		GuildMember * pMember = pGuild->GetMember(pPlayer->GetDBCharacterID()) ;
		if(!pMember)
			return false;
		if(!(pMember->GetCampBattleValue() & Value))
			return false;
	}*/

	if(m_BattleValue !=0 && m_BattleValueIsOpen)
	{
		GameGuild * pGuild = theGameGuildManager.GetGuild(pPlayer->GetGuildID());
		if(!pGuild)
			return false;
		GuildMember * pMember = pGuild->GetMember(pPlayer->GetDBCharacterID()) ;
		if(!pMember)
			return false;
		if(!(pMember->GetCampBattleValue() & m_BattleValue))
			return false;
	}

	/*unsigned int Value = 0;
	switch(m_uchBattleType)
	{
	case CampDefine::BattleTypeKing:
		Value = GuildDefine::CampBattleCountry;
		break;
	case CampDefine::BattleTypeGuild:
		Value = GuildDefine::CampBattleGuild;
		break;
	case CampDefine::BattleTypeGuildUnion:
		Value = GuildDefine::CampBattleGuildUnion;
		break;
	}
	if(Value != 0)
	{
		GameGuild * pGuild = theGameGuildManager.GetGuild(pPlayer->GetGuildID());
		if(!pGuild)
			return false;
		GuildMember * pMember = pGuild->GetMember(pPlayer->GetDBCharacterID()) ;
		if(!pMember)
			return false;
		if(!(pMember->GetCampBattleValue() & Value))
			return false;
	}*/

	if ( GetBattleStatus() != CampDefine::StatusEnter  &&  GetBattleStatus() != CampDefine::StatusFight)
	{ 
		pPlayer->SendOperateAckToClient< MsgEnterCampBattleAck >( CampDefine::Enter_NotEnterStatus );
		return false; 
	}

    const CampBattleConfig::EnterSetting &xSetting = m_pBattleConfig->GetEnterSetting();
    if ( pPlayer->GetLevel() < xSetting.GetMinLevel() )
    {
        pPlayer->SendOperateAckToClient< MsgEnterCampBattleAck >( CampDefine::Enter_NotEnterStatus );
        return false; 
    }

    // 查找战场
    CampBattle* pCampBattle = GetCampBattleByUnitID( nUnitID );
    if ( pCampBattle == NULL )
    { 
        pPlayer->SendOperateAckToClient< MsgEnterCampBattleAck >( CampDefine::Enter_MustSignUpGuild );
        return false;
    }

    BattlePlayer* pBattlePlayer = pCampBattle->GetBattlePlayer( pPlayer->GetDBCharacterID() );
    if ( pBattlePlayer == NULL )
    {
        // 判断阵营
        unsigned char uchFightCamp = pCampBattle->GetBattleFightCamp( nUnitID );
     
        // 判断进入数量, 满了就不能在进入了
        if ( pCampBattle->GetBattlePlayerCount( uchFightCamp ) >= xSetting.GetMaxCount() )
        {
            pPlayer->SendOperateAckToClient< MsgEnterCampBattleAck >( CampDefine::Enter_MaxCount );
            return false;
        }

        // 设置阵营, 只设置, 不发消息, 在MsgMapLoad函数中处理消息发送给客户端
        pPlayer->SetFightCamp( uchFightCamp );

        // 加入战场玩家
        BattlePlayer xBattlePlayer;
        xBattlePlayer.SetName( pPlayer->GetCharName() );
        xBattlePlayer.SetLevel( pPlayer->GetLevel() );
        xBattlePlayer.SetProfession( pPlayer->GetProfession() );
        xBattlePlayer.SetFightCamp( pPlayer->GetFightCamp() );
        pCampBattle->AddBattlePlayer( pPlayer->GetDBCharacterID(), xBattlePlayer );
    }

    // 进入战场
    MapConfig::MapData* pMapData = theMapConfig.GetMapDataById( GetMapID() );
    if ( pMapData == NULL )
    { return false; }

    MapConfig::RelivePosition* pRelive = pMapData->GetRelivePositionByIndex( pCampBattle->GetReliveIndex( pPlayer ) );
    if ( pRelive == NULL )
    { return false; }


	int BuffID = m_pBattleConfig->GetEnterBuff().GetBuffID();
	int Level = m_pBattleConfig->GetEnterBuff().GetLevel();
	if(BuffID != 0 && Level != 0 && GetBattleStatus() == CampDefine::StatusEnter)  //玩家刚进入的时候添加一个BUFF
	{
		long nResult = GLR_Success;
		nResult = pPlayer->ApplyBufferStatus(BuffID,Level, pPlayer->GetID(), SCharBuff::StatusEventType_Other, 0);
		if ( nResult == GLR_Success  )
		{
			pPlayer->OnBuffStatusChanged( true );
		}
	}

	//玩家进入的时候 不可以拥有队伍 自动离开队伍
	/*GameTeam * pTeam = theGameTeamManager.GetTeam(pPlayer->GetTeamID());
	if(pTeam)
	{
		GS2CSPlayerRemoveFromTeamReq xRemove;
		xRemove.dwSessionId  = pPlayer->GetTeamID();
		xRemove.dwDataBaseId = pPlayer->GetDBCharacterID();
		xRemove.bKick        = true;
		GettheServer().SendMsgToCenterServer( &xRemove );
	}*/
	pCampBattle->SendBattleStatusMessage(pPlayer);
	return pPlayer->FlyToMapReq(pCampBattle->GetBattleMapID(),pRelive->PositionX, pRelive->PositionY,pRelive->Direction );
    //return pPlayer->FlyToMapAction( pCampBattle->GetBattleMapID(), FloatToTile( pRelive->PositionX ), FloatToTile( pRelive->PositionY ), pRelive->Direction );
}

void CampBattleManager::SetkingdomMapInfo(int map_id,float map_x,float map_y)
{
	m_KingdomMapID = map_id;
	m_X = map_x;
	m_Y = map_y;
}