#include "GameGuildGeneralBattleManager.h"
#include "GameGuildGeneralBattleConfig.h"
#include "GuildManager.h"
#include "GameGuildGeneralBattle.h"
#include <algorithm>
#include <functional>
#include "GameWorld.h"
#include "GamePlayer.h"
#include "GameBattleMessage.h"
#include "ShareData.h"
#include "Configure.h"
#include "GameBattleDefine.h"
#include "GuildDefine.h"
#include "GameBattleMessage.h"
GameGuildGeneralBattleManager::GameGuildGeneralBattleManager():m_BattleValue(0),m_BattleValueIsOpen(false)
{
    SetGameBattleType( GameBattleDefine::GameBattle_Type_GuildGeneral );
	m_BattleValue = GuildDefine::GameBattleGuildGeneral;//���ֵ����ǰ��ս������ͳһ����
	m_BattleValueIsOpen = theGameGuildManager.GetCampBattleConfig()->m_GuildSetting.IsOpen;
}
GameGuildGeneralBattleManager::~GameGuildGeneralBattleManager()
{
    Destroy();
}
void GameGuildGeneralBattleManager::Init()
{

}
void GameGuildGeneralBattleManager::Destroy()
{
	for ( GameBattleMapIter iter = m_mapGameBattle.begin(); iter != m_mapGameBattle.end(); ++iter )
    {
        iter->second->Destroy();
    }
	m_mapGameBattle.clear();
}
void GameGuildGeneralBattleManager::AddGameGuildGeneralBattleOnceInfo(unsigned int ID,unsigned int MapID,unsigned int SrcGuildID,unsigned int DestGuildID,__int64 BeginTime,unsigned int MoneySum,unsigned int GuildMoney,unsigned int GuildMission)
{
	//��������������µ�ս������
	if(MapID != GetGameBattleMapID())
		return;
	if(m_pInfoList.count(ID) !=0)
		return;
	GameGuildGeneralBattleOnceInfo info;
	info.SetData(ID,SrcGuildID,DestGuildID,BeginTime,MapID,MoneySum,GuildMoney,GuildMission);
	m_pInfoList.insert(std::map<unsigned int,GameGuildGeneralBattleOnceInfo>::value_type(ID,info));

	//�µ����������Ϻ� ������Ҫ����������ս���ĵ�ǰ״̬
	HandleGameGuildGeneralBattleStates(ID);
}
void GameGuildGeneralBattleManager::HandleGameGuildGeneralBattleStates(unsigned int ID)
{
	if(m_pInfoList.count(ID) != 1)
		return;
	//����������ǰս����״̬
	time_t nowtime;
	time(&nowtime);
	__int64 NowTime = nowtime;
	switch ( m_pInfoList[ID].GetBattleStatus())
	{
	case GameBattleDefine::StatusInit:        
		// ս����ʼ״̬
		ProcessBattleInitStatus( ID,NowTime);
	case GameBattleDefine::StatusEnter:
		// ս������״̬
		ProcessBattleEnterStatus( ID,NowTime);
	case GameBattleDefine::StatusFight:
		// ս��ս��״̬
		ProcessBattleFightStatus(ID,NowTime);
	case GameBattleDefine::StatusEnd:
		// ս������״̬
		ProcessBattleEndStatus(ID,NowTime);
	}
	if(m_pInfoList[ID].GetBattleStatus() == GameBattleDefine::StatusEnd)
	{
		GS2CSDelCampBattleData msg;
		msg.ID = ID;
		GettheServer().SendMsgToCenterServer( &msg );
		m_pInfoList.erase(ID);
	}
}
void GameGuildGeneralBattleManager::RunUpdate( unsigned int nCurrentTime )
{
	//���º��� ������Ҫ����
	time_t nowtime;
	time(&nowtime);
	__int64 NowTime = nowtime;
	std::map<unsigned int,GameGuildGeneralBattleOnceInfo>::iterator Iter = m_pInfoList.begin();
	for(;Iter != m_pInfoList.end();++Iter)
	{
		switch ( Iter->second.GetBattleStatus())
		{
		 case GameBattleDefine::StatusInit:        
			// ս����ʼ״̬
			ProcessBattleInitStatus( Iter->first,NowTime);
			break;
		case GameBattleDefine::StatusEnter:
			// ս������״̬
			ProcessBattleEnterStatus( Iter->first,NowTime);
			break;
		case GameBattleDefine::StatusFight:
			// ս��ս��״̬
			ProcessBattleFightStatus( Iter->first,NowTime);
			break;
		case GameBattleDefine::StatusEnd:
			// ս������״̬
			ProcessBattleEndStatus(Iter->first,NowTime);
			break;
		default:
			Iter->second.SetBattleStatus( GameBattleDefine::StatusInit );
			break;
		}
		// ����״̬ʣ��ʱ��
		ProcessBattleLeftTime(Iter->first, nCurrentTime );
	}
	Iter = m_pInfoList.begin();
	for(;Iter != m_pInfoList.end();)
	{
		switch ( Iter->second.GetBattleStatus())
		{
		case GameBattleDefine::StatusEnd:
		case GameBattleDefine::StatusRelease:
			{
				//��ǰս���Ѿ������� ������Ҫɾ�����ݿ��������
				GS2CSDelCampBattleData msg;
				msg.ID = Iter->first;
				GettheServer().SendMsgToCenterServer( &msg );
				Iter = m_pInfoList.erase(Iter);
			}
			break;
		default:
			++Iter;
			break;
		}
	}
    // ս������
    for ( GameBattleMapIter iter = m_mapGameBattle.begin(); iter != m_mapGameBattle.end(); )
    {
        switch ( iter->second->RunUpdate( nCurrentTime ) )
        {
        case GameBattleDefine::StatusRelease:
            {
                iter->second->Destroy();
                iter = m_mapGameBattle.erase( iter );
            }
            break;
        default:
            ++iter;
            break;
        }
    }
}

void GameGuildGeneralBattleManager::ProcessBattleInitStatus(unsigned int ID,__int64 NowTime)
{
    // �ж��Ƿ���ս��׼��ʱ��
    if(m_pInfoList.count(ID) != 1)
		return;
	if(m_pInfoList[ID].GetBattleStatus() != GameBattleDefine::StatusInit)
		return;
	//�ж� �������Ƿ���ͬ
	__int64 BeginTime = m_pInfoList[ID].BeginTime;
	//int MaxKeepTime = m_pConfig.GetEnterTimeKeepTime()*60+m_pConfig.GetFightTimeKeepTime()*60;
	if(NowTime >= BeginTime /*&& NowTime< BeginTime + MaxKeepTime*/)
	{
		m_pInfoList[ID].SetLeftTime( m_pConfig.GetEnterTimeKeepTime() * OneMinuteMicroSecond );
		m_pInfoList[ID].m_nLastUpdateTime = HQ_TimeGetTime();
		ProcessChangeStatus(ID, GameBattleDefine::StatusEnter );
	} 
}
void GameGuildGeneralBattleManager::ProcessBattleEnterStatus(unsigned int ID,__int64 NowTime)
{
   if(m_pInfoList.count(ID) != 1)
		return;
   if(m_pInfoList[ID].GetBattleStatus() != GameBattleDefine::StatusEnter)
		return;
    __int64 BeginTime = m_pInfoList[ID].BeginTime + m_pConfig.GetEnterTimeKeepTime()*60;
	/*int MaxKeepTime = m_pConfig.GetSignUpKeepTime()*60 + m_pConfig.GetPrepareTimeKeepTime()*60 + m_pConfig.GetEnterTimeKeepTime()*60
		+m_pConfig.GetFightTimeKeepTime()*60;*/
	if(NowTime >= BeginTime /*&& NowTime< BeginTime + MaxKeepTime*/)
	{
		/*if(m_pInfoList[ID].GetBattleStatus() == GameBattleDefine::StatusInit)
			ProcessChangeStatus(ID, GameBattleDefine::StatusEnter );*/
		// ����ս���ı䵽ս��״̬
		m_pInfoList[ID].SetLeftTime( m_pConfig.GetFightTimeKeepTime() * OneMinuteMicroSecond );
		m_pInfoList[ID].m_nLastUpdateTime = HQ_TimeGetTime();
		ProcessChangeStatus(ID, GameBattleDefine::StatusFight );	
	}
}

void GameGuildGeneralBattleManager::ProcessBattleFightStatus(unsigned int ID,__int64 NowTime)
{
     if(m_pInfoList.count(ID) != 1)
		return;
	 if(m_pInfoList[ID].GetBattleStatus() != GameBattleDefine::StatusFight)
		return;
    __int64 BeginTime = m_pInfoList[ID].BeginTime + m_pConfig.GetEnterTimeKeepTime()*60 +m_pConfig.GetFightTimeKeepTime()*60;
	/*int MaxKeepTime = m_pConfig.GetSignUpKeepTime()*60 + m_pConfig.GetPrepareTimeKeepTime()*60 + m_pConfig.GetEnterTimeKeepTime()*60
		+m_pConfig.GetFightTimeKeepTime()*60;*/
	if(NowTime >= BeginTime /*&& NowTime< BeginTime + MaxKeepTime*/)
	{
		/*if(m_pInfoList[ID].GetBattleStatus() == GameBattleDefine::StatusInit)
			ProcessChangeStatus(ID, GameBattleDefine::StatusEnter );
		if(m_pInfoList[ID].GetBattleStatus() == GameBattleDefine::StatusEnter)
			ProcessChangeStatus(ID, GameBattleDefine::StatusFight );*/
		m_pInfoList[ID].SetLeftTime( m_pConfig.GetEndTimeKeepTime() * OneMinuteMicroSecond );
		m_pInfoList[ID].m_nLastUpdateTime = HQ_TimeGetTime();
		ProcessChangeStatus(ID, GameBattleDefine::StatusEnd );
	}
}

void GameGuildGeneralBattleManager::ProcessBattleEndStatus(unsigned int ID,__int64 NowTime)
{

}

void GameGuildGeneralBattleManager::ProcessChangeStatus(unsigned int ID, unsigned char uchStatus )
{
    // ����״̬
	if(m_pInfoList.count(ID) != 1)
		return;
    m_pInfoList[ID].SetBattleStatus( uchStatus );

    switch(  m_pInfoList[ID].GetBattleStatus() )
    {
		//����״̬
    case GameBattleDefine::StatusSignUp:
        ProcessChangeToSignUpStatus(ID);
        break;
		//׼��״̬
    case GameBattleDefine::StatusPrepare:
        ProcessChangeToPrepareStatus(ID);
        break;
    case GameBattleDefine::StatusEnter:
        ProcessChangeToEnterStatus(ID);
        break;
    case GameBattleDefine::StatusFight:
        ProcessChangeToFightStatus(ID);
        break;
	case GameBattleDefine::StatusEnd:
		ProcessChangeToEndStatus(ID);
		break;
    default:
        break;
    }
	if (0xffffffff != m_pInfoList[ID].GetMapID())
	{
		SendBattleStatusMessage(ID,  m_pInfoList[ID].GetBattleStatus() );
	}
}
void GameGuildGeneralBattleManager::SendBattleStatusMessage(unsigned int ID, unsigned char uchStatus )
{
	if(m_pInfoList.count(ID) != 1)
		return;
	GameGuild* pSrcGuild = theGameGuildManager.GetGuild(m_pInfoList[ID].RedGuildID);
	GameGuild* pDestGuild = theGameGuildManager.GetGuild(m_pInfoList[ID].BlueGuildID);
    switch ( uchStatus )
    {
    case GameBattleDefine::StatusSignUp:
    case GameBattleDefine::StatusPrepare:
    case GameBattleDefine::StatusEnter:
        {
			MsgTellGameBattleStatus xTell;
			xTell.uchCampBattleType   = GetGameBattleType();
			xTell.uchCampBattleStatus = uchStatus;
			xTell.nLeftTime           = m_pInfoList[ID].GetLeftTime() / 1000;
			if(pSrcGuild)
				pSrcGuild->SendMessageToGuild(&xTell,GuildDefine::InitID,0,true);
			if(pDestGuild)
				pDestGuild->SendMessageToGuild(&xTell,GuildDefine::InitID,0,true);
        }
        break;
    case GameBattleDefine::StatusFight:
    case GameBattleDefine::StatusEnd:
        {
            // ��2��״̬������ս����ͼ
            for ( GameBattleMapIter iter = m_mapGameBattle.begin(); iter != m_mapGameBattle.end(); ++iter )
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
void GameGuildGeneralBattleManager::ProcessBattleLeftTime(unsigned int ID, unsigned int nCurrentTime )
{
    // ��ù��˶���ʱ��
	if(m_pInfoList.count(ID) != 1)
		return;
    unsigned int nPassTime = GameTime::GetPassTime( nCurrentTime, m_pInfoList[ID].m_nLastUpdateTime );
    m_pInfoList[ID].SubLeftTime( nPassTime );   // ����ʣ��ʱ��
    m_pInfoList[ID].m_nLastUpdateTime = nCurrentTime;
}

// ����ת��������״̬�߼�
void GameGuildGeneralBattleManager::ProcessChangeToSignUpStatus(unsigned int ID)
{
	if(m_pInfoList.count(ID) != 1)
		return;
    const GameGuildGeneralBattleConfig::MapSetting* pSetting = m_pConfig.GetMapSetting();
    if ( pSetting == NULL )
		return;
    if ( !g_Cfg.IsMapRun( pSetting->GetMapID() ) )
		return;
	m_pInfoList[ID].SetMapID( pSetting->GetMapID() );

	const GameGuildGeneralBattleConfig::CKingdomMap &xKingdomMap = m_pConfig.GetKingdomMap();
	SetkingdomMapInfo(xKingdomMap.GetMapID(),
					  xKingdomMap.GetMapX(),
					  xKingdomMap.GetMapY());

}
void GameGuildGeneralBattleManager::ProcessChangeToFightStatus(unsigned int ID)
{
	//ս����ʽ��ʼս�� ȥ����ͼ��ȫ����ҵ�BUFF
	
}
void GameGuildGeneralBattleManager::AddGameBattle( GameGuildGeneralBattle* pGameBattle )
{
    if ( pGameBattle == NULL )
    { return; }

    m_mapGameBattle[ pGameBattle->GetBattleMapID() ] = pGameBattle;
}

GameGuildGeneralBattle* GameGuildGeneralBattleManager::GetGameBattleByPlayerID( unsigned int nPlayerID )
{
    for ( GameBattleMapIter iter = m_mapGameBattle.begin(); iter != m_mapGameBattle.end(); ++iter )
    {
		GameBattleDefine::BattlePlayer* pBattlePlayer = iter->second->GetBattlePlayer( nPlayerID );
        if ( pBattlePlayer != NULL )
        { return iter->second; }
    }

    return NULL;
}

GameGuildGeneralBattle* GameGuildGeneralBattleManager::GetGameBattleByUnitID( unsigned int nUnitID )
{
    for ( GameBattleMapIter iter = m_mapGameBattle.begin(); iter != m_mapGameBattle.end(); ++iter )
    {
        if ( iter->second->GetRedID() == nUnitID || iter->second->GetBlueID() == nUnitID )
        { return iter->second; }
    }

    return NULL;
}
GameGuildGeneralBattle* GameGuildGeneralBattleManager::GetGameBattleByID(unsigned int ID)
{
	for ( GameBattleMapIter iter = m_mapGameBattle.begin(); iter != m_mapGameBattle.end(); ++iter )
    {
        if(iter->second->GetBattleIndexID() == ID)
			return iter->second;
    }
	return NULL;
}
GameGuildGeneralBattle* GameGuildGeneralBattleManager::GetGameBattleByOnlyMapID(unsigned int MapID)
{
	for ( GameBattleMapIter iter = m_mapGameBattle.begin(); iter != m_mapGameBattle.end(); ++iter )
    {
        if(iter->second->GetBattleMapID() == MapID)
			return iter->second;
    }
	return NULL;
}
void GameGuildGeneralBattleManager::SetkingdomMapInfo(int map_id,float map_x,float map_y)
{
	m_KingdomMapID = map_id;
	m_X = map_x;
	m_Y = map_y;
}

// ����ת����׼��״̬�߼�
void GameGuildGeneralBattleManager::ProcessChangeToPrepareStatus(unsigned int ID)
{	
}
// ����ת��������״̬�߼�
void GameGuildGeneralBattleManager::ProcessChangeToEnterStatus(unsigned int ID)
{
    // ������������
	if(m_pInfoList.count(ID) != 1)
		return;
	#ifdef _DEBUG
    #else
	GameGuild * pRedGuild = theGameGuildManager.GetGuild(m_pInfoList[ID].RedGuildID);
	GameGuild * pBlueGuild = theGameGuildManager.GetGuild(m_pInfoList[ID].BlueGuildID);
	if(!pRedGuild || !pBlueGuild)
		return;
	#endif
    // ��������
    unsigned int nBattleMapID = theGameWorld.GetEctypeMapID(m_pInfoList[ID].GetMapID(), true );
    theGameWorld.MultiCreateStage( m_pInfoList[ID].GetMapID(), nBattleMapID );

    // ����ս��
    GameGuildGeneralBattle* pGameBattle = GameGuildGeneralBattle::CreateGameGuildGeneralBattle< GameGuildGeneralBattle >();
	pGameBattle->SetGameBattleManager( this );
	pGameBattle->SetBattleMapID( nBattleMapID );
	pGameBattle->SetRedID( m_pInfoList[ID].RedGuildID );
	pGameBattle->SetBlueID( m_pInfoList[ID].BlueGuildID );
	pGameBattle->SetWinResource( m_pConfig.GetResourceSetting().GetMaxResource() );
	pGameBattle->SetData(ID,m_pInfoList[ID].MoneySum,m_pInfoList[ID].GuildMoneySum,m_pInfoList[ID].GuildMissionSum);

	// �����Ƿ����ս����Ϣ
	pGameBattle->SendEnterGameBattleMessage();

	// ��ӵ�ս���б���
	AddGameBattle( pGameBattle );
	pGameBattle->SetGuildGameBattleTimeMap();
}
bool GameGuildGeneralBattleManager::ShowGameBattleEnter( GamePlayer* pPlayer )
{
    if ( pPlayer == NULL )
    { return false; }

    GameGuild* pGuild = pPlayer->GetGuild();
    if ( pGuild == NULL )
    { return false; }

	//�ж���ҵ�Ȩ��
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

	GameGuildGeneralBattle* pGameBattle = GetGameBattleByUnitID( pGuild->GetID() );
    if ( pGameBattle == NULL )
    { return false; }

	if(m_pInfoList.count(pGameBattle->GetBattleIndexID()) != 1)
		return false;

	if ( m_pInfoList[pGameBattle->GetBattleIndexID()].GetBattleStatus() != GameBattleDefine::StatusEnter )
    { return false; }

    MsgShowGameGuildBattleEnter xShow;
    xShow.uchBattleType = GetGameBattleType();
    xShow.nRedGuildID   = pGameBattle->GetRedID();
    xShow.nBlueGuildID  = pGameBattle->GetBlueID();
    pPlayer->SendMessageToClient( &xShow );

    return true;
}

bool GameGuildGeneralBattleManager::EnterGameBattle(GamePlayer* pPlayer )
{
    if ( pPlayer == NULL )
    { return false; }

    GameGuild* pGuild = pPlayer->GetGuild();
    if ( pGuild == NULL )
    { 
        pPlayer->SendOperateAckToClient< MsgEnterGameBattleAck >( CampDefine::Enter_MustSignUpGuild );
        return false;
    }

	if(m_BattleValue !=0 && m_BattleValueIsOpen)
	{
		GuildMember * pMember = pGuild->GetMember(pPlayer->GetDBCharacterID()) ;
		if(!pMember)
			return false;
		if(!(pMember->GetCampBattleValue() & m_BattleValue))
			return false;
	}

	// ����ս��
	GameGuildGeneralBattle* pGameBattle = GetGameBattleByUnitID( pGuild->GetID() );
    if ( pGameBattle == NULL )
    { 
        pPlayer->SendOperateAckToClient< MsgEnterGameBattleAck >( CampDefine::Enter_MustSignUpGuild );
        return false;
    }
	if(m_pInfoList.count(pGameBattle->GetBattleIndexID()) != 1)
		return false;
	if ( m_pInfoList[pGameBattle->GetBattleIndexID()].GetBattleStatus() != GameBattleDefine::StatusEnter  &&  m_pInfoList[pGameBattle->GetBattleIndexID()].GetBattleStatus() != GameBattleDefine::StatusFight)
	{ 
		pPlayer->SendOperateAckToClient< MsgEnterGameBattleAck >( CampDefine::Enter_NotEnterStatus );
		return false; 
	}

    const GameGuildGeneralBattleConfig::EnterSetting &xSetting = m_pConfig.GetEnterSetting();
    if ( pPlayer->GetLevel() < xSetting.GetMinLevel() )
    {
        pPlayer->SendOperateAckToClient< MsgEnterGameBattleAck >( CampDefine::Enter_NotEnterStatus );
        return false; 
    }

	GameBattleDefine::BattlePlayer* pBattlePlayer = pGameBattle->GetBattlePlayer( pPlayer->GetDBCharacterID() );
    if ( pBattlePlayer == NULL )
    {
        // �ж���Ӫ
        unsigned char uchFightGame = pGameBattle->GetGameBattleFight( pGuild->GetID() );
     
        // �жϽ�������, ���˾Ͳ����ڽ�����
        if ( pGameBattle->GetBattlePlayerCount( uchFightGame ) >= xSetting.GetMaxCount() )
        {
            pPlayer->SendOperateAckToClient< MsgEnterGameBattleAck >( CampDefine::Enter_MaxCount );
            return false;
        }

        // ������Ӫ, ֻ����, ������Ϣ, ��MsgMapLoad�����д�����Ϣ���͸��ͻ���
        pPlayer->SetFightGame( uchFightGame );

        // ����ս�����
		GameBattleDefine::BattlePlayer xBattlePlayer;
        xBattlePlayer.SetName( pPlayer->GetCharName() );
        xBattlePlayer.SetLevel( pPlayer->GetLevel() );
        xBattlePlayer.SetProfession( pPlayer->GetProfession() );
        xBattlePlayer.SetFight( pPlayer->GetFightCamp() );
        pGameBattle->AddBattlePlayer( pPlayer->GetDBCharacterID(), xBattlePlayer );
    }

    // ����ս��
    MapConfig::MapData* pMapData = theMapConfig.GetMapDataById( m_pInfoList[pGameBattle->GetBattleIndexID()].GetMapID() );
    if ( pMapData == NULL )
    { return false; }

    MapConfig::RelivePosition* pRelive = pMapData->GetRelivePositionByIndex( pGameBattle->GetReliveIndex( pPlayer ) );
    if ( pRelive == NULL )
    { return false; }


	int BuffID = m_pConfig.GetEnterBuff().GetBuffID();
	int Level = m_pConfig.GetEnterBuff().GetLevel();
	if(BuffID != 0 && Level != 0 && m_pInfoList[pGameBattle->GetBattleIndexID()].GetBattleStatus() == GameBattleDefine::StatusEnter)  //��Ҹս����ʱ�����һ��BUFF
	{
		long nResult = GLR_Success;
		nResult = pPlayer->ApplyBufferStatus(BuffID,Level, pPlayer->GetID(), SCharBuff::StatusEventType_Other, 0);
		if ( nResult == GLR_Success  )
		{
			pPlayer->OnBuffStatusChanged( true );
		}
	}

	pGameBattle->SendBattleStatusMessage(pPlayer);
	return pPlayer->FlyToMapReq(pGameBattle->GetBattleMapID(),pRelive->PositionX, pRelive->PositionY,pRelive->Direction );
}
void GameGuildGeneralBattleManager::KillGameBattleMonster( unsigned char uchFight, unsigned int nPlayerID, int nMonsterID ,unsigned int MapID)
{
	//nPlayerID �п���Ϊ 0  ������Ҫ�������Ĵ��� 
	GameGuildGeneralBattle* pBattle = GetGameBattleByOnlyMapID(MapID);
	if(!pBattle)
		return;
	pBattle->KillGameBattleMonster(uchFight,nPlayerID,nMonsterID);
}
