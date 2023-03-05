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

    // ״̬����
    switch ( GetBattleStatus() )
    {
    case CampDefine::StatusInit:        
        // ս����ʼ״̬
        ProcessBattleInitStatus( nCurrentTime, xSystemTime.wDayOfWeek, xSystemTime.wHour, xSystemTime.wMinute );
        break;
    case CampDefine::StatusSignUp:
        // ս������״̬
        ProcessBattleSignUpStatus( nCurrentTime, xSystemTime.wDayOfWeek, xSystemTime.wHour, xSystemTime.wMinute );
        break;
    case CampDefine::StatusPrepare:
        // ս��׼��״̬
        ProcessBattlePrepareStatus( nCurrentTime, xSystemTime.wDayOfWeek, xSystemTime.wHour, xSystemTime.wMinute );
        break;
    case CampDefine::StatusEnter:
        // ս������״̬
        ProcessBattleEnterStatus( nCurrentTime, xSystemTime.wDayOfWeek, xSystemTime.wHour, xSystemTime.wMinute );
        break;
    case CampDefine::StatusFight:
        // ս��ս��״̬
        ProcessBattleFightStatus( nCurrentTime, xSystemTime.wDayOfWeek, xSystemTime.wHour, xSystemTime.wMinute );
        break;
    case CampDefine::StatusEnd:
        // ս������״̬
        ProcessBattleEndStatus();
        break;
    default:
        SetBattleStatus( CampDefine::StatusInit );
        break;
    }

    // ����״̬ʣ��ʱ��
    ProcessBattleLeftTime( nCurrentTime );

    // ս������
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
    // �ж��Ƿ���ս��׼��ʱ��
    if ( !CheckBattleSignUpTime( nCurrentTime, nDayOfWeek, nHour, nMinute ) )
    { return; }

    // ����ս���ı䵽׼��״̬
    ProcessChangeStatus( CampDefine::StatusSignUp );
}

void CampBattleManager::ProcessBattleSignUpStatus( unsigned int nCurrentTime, int nDayOfWeek, int nHour, int nMinute )
{
    if ( !CheckBattlePrepareTime( nCurrentTime, nDayOfWeek, nHour, nMinute ) )
    { return; }

    // ����ս���ı䵽����״̬
    ProcessChangeStatus( CampDefine::StatusPrepare );
}

void CampBattleManager::ProcessBattlePrepareStatus( unsigned int nCurrentTime, int nDayOfWeek, int nHour, int nMinute )
{
    if ( !CheckBattleEnterTime( nCurrentTime, nDayOfWeek, nHour, nMinute ) )
    { return; }

    // ����ս���ı䵽����״̬
    ProcessChangeStatus( CampDefine::StatusEnter );
}

void CampBattleManager::ProcessBattleEnterStatus( unsigned int nCurrentTime, int nDayOfWeek, int nHour, int nMinute )
{
    if ( !CheckBattleFightTime( nCurrentTime, nDayOfWeek, nHour, nMinute ) )
    { return; }

    // ����ս���ı䵽ս��״̬
    ProcessChangeStatus( CampDefine::StatusFight );
}

void CampBattleManager::ProcessBattleFightStatus( unsigned int nCurrentTime, int nDayOfWeek, int nHour, int nMinute )
{
    if ( !CheckBattleEndTime( nCurrentTime, nDayOfWeek, nHour, nMinute ) )
    { return; }

    // ����ս���ı䵽������״̬
    ProcessChangeStatus( CampDefine::StatusEnd );
}

void CampBattleManager::ProcessBattleEndStatus()
{
    SetBattleStatus( CampDefine::StatusInit );
}

void CampBattleManager::ProcessChangeStatus( unsigned char uchStatus )
{
    // ����״̬
    SetBattleStatus( uchStatus );

    switch( GetBattleStatus() )
    {
		//����״̬
    case CampDefine::StatusSignUp:
        ProcessChangeToSignUpStatus();
        break;
		//׼��״̬
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

    // ����ս��״̬�ı���Ϣ(���ս�����ڴ�GAME SERVER�����÷���) by vvx 2013.3.28
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
            // ��3��״̬���͸�ȫ��
			MsgTellCampBattleStatus xTell;
			xTell.uchCampBattleType   = GetBattleType();
			xTell.uchCampBattleStatus = uchStatus;
			xTell.nLeftTime           = GetLeftTime() / 1000;
			if(GetCountryID() == 0)
			{
				GettheServer().SendMsgToWorld(&xTell,true);//�޹��һ��� ����ȫ�����
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
            // ��2��״̬������ս����ͼ
            for ( CampBattleMapIter iter = m_mapCampBattle.begin(); iter != m_mapCampBattle.end(); ++iter )
            {
                // ����״̬
                iter->second->ProcessStatusChange( uchStatus );
            }
        }
        break;
    default:
        break;
    }
}

// �ж��Ƿ���ս������ʱ��
bool CampBattleManager::CheckBattleSignUpTime( unsigned int nCurrentTime, int nDayOfWeek, int nHour, int nMinute )
{
    const CampBattleConfig::TimeSetting* pSetting = m_pBattleConfig->CheckSignUpTimeSetting( nDayOfWeek, nHour, nMinute );
    if ( pSetting == NULL )
    { return false; }

    SetLeftTime( pSetting->GetKeepTime() * OneMinuteMicroSecond );
    m_nLastUpdateTime = nCurrentTime;

    return true;
}

// �ж��Ƿ���ս��׼��ʱ��
bool CampBattleManager::CheckBattlePrepareTime( unsigned int nCurrentTime, int nDayOfWeek, int nHour, int nMinute )
{
    const CampBattleConfig::TimeSetting* pSetting = m_pBattleConfig->CheckPrepareTimeSetting( nDayOfWeek, nHour, nMinute );
    if ( pSetting == NULL )
    { return false; }

    SetLeftTime( pSetting->GetKeepTime() * OneMinuteMicroSecond );
    m_nLastUpdateTime = nCurrentTime;

    return true;
}

// �ж��Ƿ���ս������ʱ��
bool CampBattleManager::CheckBattleEnterTime( unsigned int nCurrentTime, int nDayOfWeek, int nHour, int nMinute )
{
    const CampBattleConfig::TimeSetting* pSetting = m_pBattleConfig->CheckEnterTimeSetting( nDayOfWeek, nHour, nMinute );
    if ( pSetting == NULL )
    { return false; }

    SetLeftTime( pSetting->GetKeepTime() * OneMinuteMicroSecond );
    m_nLastUpdateTime = nCurrentTime;

    return true;
}

// �ж��Ƿ���ս��ս��ʱ��
bool CampBattleManager::CheckBattleFightTime( unsigned int nCurrentTime, int nDayOfWeek, int nHour, int nMinute )
{
    const CampBattleConfig::TimeSetting* pSetting = m_pBattleConfig->CheckFightTimeSetting( nDayOfWeek, nHour, nMinute );
    if ( pSetting == NULL )
    { return false; }

    SetLeftTime( pSetting->GetKeepTime() * OneMinuteMicroSecond );
    m_nLastUpdateTime = nCurrentTime;

    return true;
}

// �ж��Ƿ���ս������ʱ��
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
    // ��ù��˶���ʱ��
    unsigned int nPassTime = GameTime::GetPassTime( nCurrentTime, m_nLastUpdateTime );
    SubLeftTime( nPassTime );   // ����ʣ��ʱ��

    m_nLastUpdateTime = nCurrentTime;
}

// ����ת��������״̬�߼�
void CampBattleManager::ProcessChangeToSignUpStatus()
{
    m_vecSignUp.clear();

    // ����ս������, ��ս��MapConfig ID
    for ( int i = 0; i < m_pBattleConfig->GetMapSettingCount(); ++i )
    {
        const CampBattleConfig::MapSetting* pSetting = m_pBattleConfig->GetMapSetting( i );
        if ( pSetting == NULL )
        { continue; }

        if ( !g_Cfg.IsMapRun( pSetting->GetMapID() ) )
        { continue; }       // û�п���ͼ

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
	//ս����ʽ��ʼս�� ȥ����ͼ��ȫ����ҵ�BUFF
	
}
// ���һ��������ID
void CampBattleManager::AddSignUpUnit( unsigned int nUnitID )
{
    SignUpVectorIter iter = std::find( m_vecSignUp.begin(), m_vecSignUp.end(), nUnitID );
    if ( iter != m_vecSignUp.end() )
    { return; }

    m_vecSignUp.push_back( nUnitID );
}

// �ж��Ƿ��Ѿ�������
bool CampBattleManager::IsSignUpUnit( unsigned int nUnitID )
{
    return std::find( m_vecSignUp.begin(), m_vecSignUp.end(), nUnitID ) != m_vecSignUp.end();
}

// ɾ��һ��������ID
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

	//�ж���ҵ�Ȩ��
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

	//�ж���ҵ�Ȩ��
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

    // ����ս��
    CampBattle* pCampBattle = GetCampBattleByUnitID( nUnitID );
    if ( pCampBattle == NULL )
    { 
        pPlayer->SendOperateAckToClient< MsgEnterCampBattleAck >( CampDefine::Enter_MustSignUpGuild );
        return false;
    }

    BattlePlayer* pBattlePlayer = pCampBattle->GetBattlePlayer( pPlayer->GetDBCharacterID() );
    if ( pBattlePlayer == NULL )
    {
        // �ж���Ӫ
        unsigned char uchFightCamp = pCampBattle->GetBattleFightCamp( nUnitID );
     
        // �жϽ�������, ���˾Ͳ����ڽ�����
        if ( pCampBattle->GetBattlePlayerCount( uchFightCamp ) >= xSetting.GetMaxCount() )
        {
            pPlayer->SendOperateAckToClient< MsgEnterCampBattleAck >( CampDefine::Enter_MaxCount );
            return false;
        }

        // ������Ӫ, ֻ����, ������Ϣ, ��MsgMapLoad�����д�����Ϣ���͸��ͻ���
        pPlayer->SetFightCamp( uchFightCamp );

        // ����ս�����
        BattlePlayer xBattlePlayer;
        xBattlePlayer.SetName( pPlayer->GetCharName() );
        xBattlePlayer.SetLevel( pPlayer->GetLevel() );
        xBattlePlayer.SetProfession( pPlayer->GetProfession() );
        xBattlePlayer.SetFightCamp( pPlayer->GetFightCamp() );
        pCampBattle->AddBattlePlayer( pPlayer->GetDBCharacterID(), xBattlePlayer );
    }

    // ����ս��
    MapConfig::MapData* pMapData = theMapConfig.GetMapDataById( GetMapID() );
    if ( pMapData == NULL )
    { return false; }

    MapConfig::RelivePosition* pRelive = pMapData->GetRelivePositionByIndex( pCampBattle->GetReliveIndex( pPlayer ) );
    if ( pRelive == NULL )
    { return false; }


	int BuffID = m_pBattleConfig->GetEnterBuff().GetBuffID();
	int Level = m_pBattleConfig->GetEnterBuff().GetLevel();
	if(BuffID != 0 && Level != 0 && GetBattleStatus() == CampDefine::StatusEnter)  //��Ҹս����ʱ�����һ��BUFF
	{
		long nResult = GLR_Success;
		nResult = pPlayer->ApplyBufferStatus(BuffID,Level, pPlayer->GetID(), SCharBuff::StatusEventType_Other, 0);
		if ( nResult == GLR_Success  )
		{
			pPlayer->OnBuffStatusChanged( true );
		}
	}

	//��ҽ����ʱ�� ������ӵ�ж��� �Զ��뿪����
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