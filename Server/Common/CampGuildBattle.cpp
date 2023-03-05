#include "CampGuildBattle.h"
#include "GuildManager.h"
#include "CampBattleMessage.h"
#include "MapConfig.h"
#include "CampGuildBattleConfig.h"
#include "GamePlayer.h"
#include "CampBattleManager.h"
#include "GameWorld.h"
#include "MonsterCreater.h"
#include "CampGuildUnionBattleConfig.h"
#include "LogEventService.h"
#include "XmlStringLanguage.h"
#include "ShareData.h"
typedef pair<unsigned int, BattlePlayer> PAIR;    
int cmp(const PAIR& x, const PAIR& y)    
{    
	return x.second.GetTotalKillCount() > y.second.GetTotalKillCount();
}

CampGuildBattle::CampGuildBattle() : CampBattle()
{
    m_xRefreshTimer.StartTimer( 1, 3000 );
	m_BlueBarracksDeadSum = 0;
	m_RedBarracksDeadSum = 0;
	m_RedBoss = NULL;
	m_BlueBoss = NULL;

	m_xNormalTimer.clear();
}	
void CampGuildBattle::SetGuildCampBattleTimeMap()
{
	if(!m_pBattleManager)
		return;
	const CampGuildBattleConfig* pBattleConfig = static_cast< const CampGuildBattleConfig* >( m_pBattleManager->GetBattleConfig() );
	if(pBattleConfig)
	{
		map<int,CampGuildBattleConfig::NormalMonster> mapList;
		pBattleConfig->GetNormalMonster(mapList);
		map<int,CampGuildBattleConfig::NormalMonster>::iterator Iter = mapList.begin();
		for(;Iter !=mapList.end();++Iter)
		{
			GameTimerEx ex;
			m_xNormalTimer.insert(std::map<int,GameTimerEx>::value_type(Iter->first,ex));
		}
	}
}
void CampGuildBattle::Release()
{
    ReleaseBattle< CampGuildBattle >( this );
}

void CampGuildBattle::SendEnterCampBattleMessage()
{
    // ��õ�ͼID
    MapConfig::MapData* pMapData = theMapConfig.GetMapDataById( m_pBattleManager->GetMapID() );
    if ( pMapData == NULL )
    { return; }

    // ��ý����NPC�ص�
    MapConfig::RelivePosition* pRelive = pMapData->GetRelivePositionByState( false );
    if ( pRelive == NULL )
    { return; }

    MsgFlyToCampBattleReq xReq;
    xReq.uchBattleType = m_pBattleManager->GetBattleType();
    xReq.nMapID        = m_pBattleManager->GetMapID();
	xReq.nKingdomID = m_pBattleManager->GetKingdomMapID();
	xReq.nKingdomX = m_pBattleManager->GetKingdomMapX();
	xReq.nKingdomY = m_pBattleManager->GetKingdomMapY();
	xReq.RedID = GetRedID();
	xReq.BlueID = GetBlueID();

    // �췽����
    GameGuild* pRedGuild = theGameGuildManager.GetGuild( m_nRedID );
    if ( pRedGuild != NULL )
    {
        pRedGuild->SendMessageToGuild( &xReq, GuildDefine::InitID, pMapData->MinPlayerLevel, true );
    }

    // ��������
    GameGuild* pBlueGuild = theGameGuildManager.GetGuild( m_nBlueID );
    if ( pBlueGuild != NULL )
    { 
        pBlueGuild->SendMessageToGuild( &xReq, GuildDefine::InitID, pMapData->MinPlayerLevel, true );
    }
}

void CampGuildBattle::ProcessCampBattleEnterStatus()
{
    if ( !m_xRefreshTimer.DoneTimer( HQ_TimeGetTime() ) )
    { return; }

    GameStage* pStage = theGameWorld.GetStageById( GetBattleMapID() );
    if ( pStage == NULL )
    { return; }

    // ��ֹͣ��ʱ��
    m_xRefreshTimer.StopTimer();

    m_mapRefreshIndex.clear();

    MonsterCreateData xCreateData;
    xCreateData.SetMapID( pStage->GetStageID() );

    // ˢ��˫����Ӫ
    const CampGuildBattleConfig* pBattleConfig = static_cast< const CampGuildBattleConfig* >( m_pBattleManager->GetBattleConfig() );
    for ( int i = 0; i < pBattleConfig->GetGetRefreshSettingCount(); ++i )
    {
        const CampGuildBattleConfig::RefreshSetting* pSetting = pBattleConfig->GetRefreshSettingByIndex( i );
        if ( pSetting == NULL )
        { continue; }

        const CampGuildBattleConfig::RefreshSetting::BarracksSetting& xRedSetting = pSetting->GetRedBarracksSetting();

        xCreateData.SetMonsterID( /*pSetting->GetBarracksID()*/ xRedSetting.GetMonsterID());
        xCreateData.SetPostionX( xRedSetting.GetPosX() );
        xCreateData.SetPostionY( xRedSetting.GetPosY() );
       // xCreateData.SetDirX( xRedSetting.GetDirX() );
       // xCreateData.SetDirY( xRedSetting.GetDirY() );
		xCreateData.SetDirection(xRedSetting.GetAngle());

        xCreateData.SetFightCamp( CampDefine::GuildCampRed );
		xCreateData.SetMapID(m_nEctypeMapID);	
		MonsterBaseEx*  pMonst = MonsterCreater::CreateBuildMonster( xCreateData );
		if(pMonst)
			m_RedBarracks.push_back(pMonst->GetID());

        const CampGuildBattleConfig::RefreshSetting::BarracksSetting& xBlueSetting = pSetting->GetBlueBarracksSetting();

        xCreateData.SetMonsterID( /*pSetting->GetBarracksID()*/ xBlueSetting.GetMonsterID());
        xCreateData.SetPostionX( xBlueSetting.GetPosX() );
        xCreateData.SetPostionY( xBlueSetting.GetPosY() );
       // xCreateData.SetDirX( xBlueSetting.GetDirX() );
        //xCreateData.SetDirY( xBlueSetting.GetDirY() );
		xCreateData.SetDirection(xBlueSetting.GetAngle());
        xCreateData.SetFightCamp( CampDefine::GuildCampBlue );
		xCreateData.SetMapID(m_nEctypeMapID);
		pMonst = MonsterCreater::CreateBuildMonster( xCreateData );
		if(pMonst)
			m_BlueBarracks.push_back(pMonst->GetID());

        // ����ˢ����Ϣ
        RefreshIndex xRefreshIndex;
        xRefreshIndex.SetRedIndex( 0 );
        xRefreshIndex.SetMaxRedIndex( xRedSetting.GetMonsterCount() - 1 );
        xRefreshIndex.SetBlueIndex( 0 );
        xRefreshIndex.SetMaxBlueIndex( xBlueSetting.GetMonsterCount() - 1 );
        m_mapRefreshIndex.insert( std::make_pair( pSetting->GetBarracksID(), xRefreshIndex ) );
    }

    // ˢ��������Ӫ��
    for ( int i = 0; i < pBattleConfig->GetRedCampMonsterCount(); ++i )
    {
        const CampGuildBattleConfig::CampMonster* pMonster = pBattleConfig->GetRedCampMonster( i );
        if ( pMonster == NULL )
        { continue; }

        xCreateData.SetMonsterID( pMonster->GetID() );
        xCreateData.SetPostionX( pMonster->GetPosX() );
        xCreateData.SetPostionY( pMonster->GetPosY() );
       /* xCreateData.SetDirX( pMonster->GetDirX() );
        xCreateData.SetDirY( pMonster->GetDirY() );*/
		xCreateData.SetDirection(pMonster->GetAngle());


        xCreateData.SetFightCamp( CampDefine::GuildCampRed );
		xCreateData.SetMapID(m_nEctypeMapID);

        MonsterCreater::CreateNormalMonster( xCreateData );
    }

    for ( int i = 0; i < pBattleConfig->GetBlueCampMonsterCount(); ++i )
    {
        const CampGuildBattleConfig::CampMonster* pMonster = pBattleConfig->GetBlueCampMonster( i );
        if ( pMonster == NULL )
        { continue; }

        xCreateData.SetMonsterID( pMonster->GetID() );
        xCreateData.SetPostionX( pMonster->GetPosX() );
        xCreateData.SetPostionY( pMonster->GetPosY() );
        //xCreateData.SetDirX( pMonster->GetDirX() );
        //xCreateData.SetDirY( pMonster->GetDirY() );
		xCreateData.SetDirection(pMonster->GetAngle());


        xCreateData.SetFightCamp( CampDefine::GuildCampBlue );
		xCreateData.SetMapID(m_nEctypeMapID);

        MonsterCreater::CreateNormalMonster( xCreateData );
    }
}

void CampGuildBattle::SendCampBattleResourceMessage()
{
    // 5��ͬ��һ����Դ��
    MsgTellCampBattleResource xTell;
	xTell.nRedGuildID = m_nRedID;
	xTell.nBlueGuildID = m_nBlueID;
    xTell.nRedResource  = m_nRedResource;
    xTell.nBlueResource = m_nBlueResource;
	xTell.nBlueTotleKillSum = m_BlueTotleKillSum;
	xTell.nRedTotleKillSum = m_RedTotleKillSum;
	//��˫����Ӫ��Ѫ��������¼����
	const CampGuildBattleConfig* pBattleConfig = static_cast< const CampGuildBattleConfig* >( m_pBattleManager->GetBattleConfig() );
	if(pBattleConfig->GetGetRefreshSettingCount() != 3)
		return;
    for ( int i = 0; i < pBattleConfig->GetGetRefreshSettingCount(); ++i )
    {
        const CampGuildBattleConfig::RefreshSetting* pSetting = pBattleConfig->GetRefreshSettingByIndex( i );
        if ( pSetting == NULL )
        { continue; }	
		MonsterBaseEx * pCreate = (MonsterBaseEx *)theRunTimeData.GetCharacterByID( m_RedBarracks[i]);
		if(pCreate == NULL || pCreate->GetHPMax()==0/*|| pCreate->GetMonsterID() !=pSetting->GetBarracksID()*/)
		{
			 xTell.nRedAtterHp[i] = 0;
			 m_RedBarracks[i] = NULL;
		}
		else
		{
			 xTell.nRedAtterHp[i] = (pCreate->GetHP() * 1.0)/pCreate->GetHPMax();
		}
		
		pCreate = (MonsterBaseEx *)theRunTimeData.GetCharacterByID( m_BlueBarracks[i]);
		if(pCreate == NULL || pCreate->GetHPMax() == 0/*|| pCreate->GetMonsterID() !=pSetting->GetBarracksID()*/)
		{
			 xTell.nBlueAtterHp[i] = 0;
			 m_BlueBarracks[i] = NULL;
		}
		else
		{
			 xTell.nBlueAtterHp[i] = (pCreate->GetHP() * 1.0)/pCreate->GetHPMax();
		}
	}
	if(m_RedBoss && m_RedBoss->GetHPMax() != 0)
	{
		 xTell.nRedAtterHp[3] = (m_RedBoss->GetHP() * 1.0)/m_RedBoss->GetHPMax();
	}
	else
	{
		if(m_RedBarracksDeadSum == pBattleConfig->GetGetRefreshSettingCount() || m_RedBarracksDeadSum == -1)
		{
			xTell.nRedAtterHp[3] = 0;
		}
		else
		{
			xTell.nRedAtterHp[3] = 100;
		}
	}
	if(m_BlueBoss && m_BlueBoss->GetHPMax() != 0)
	{
		 xTell.nBlueAtterHp[3] = (m_BlueBoss->GetHP() * 1.0)/m_BlueBoss->GetHPMax();
	}
	else
	{
		if(m_BlueBarracksDeadSum == pBattleConfig->GetGetRefreshSettingCount() || m_BlueBarracksDeadSum == -1)
		{
			xTell.nBlueAtterHp[3] = 0;
		}
		else
		{
			xTell.nBlueAtterHp[3] = 100;
		}
	}
    GettheServer().SendMsgToStage( &xTell, GetBattleMapID() );
}

void CampGuildBattle::ProcessCampBattleFightStatus()
{
    SendCampBattleResourceMessage();

    // ��ʱˢ��
    ProcessRefreshCampMonster();

    // ������( Roshan )ˢ��
    ProcessRefreshNormalMonster();
}

void CampGuildBattle::ProcessChangeToEndStatus()
{
    // ͬ��һ��ս������
    SendCampBattleResourceMessage();

    CampBattle::ProcessChangeToEndStatus();
}

void CampGuildBattle::ProcessCampBattleResult( unsigned char uchFightCamp )
{
    // ����ս������
	unsigned int nWinGuildID  = GuildDefine::InitID;
	unsigned int nLoseGuildID = GuildDefine::InitID;
	switch ( uchFightCamp )
	{
	case CampDefine::BaseCampRed:
		nWinGuildID  = m_nRedID;
		nLoseGuildID = m_nBlueID;
		break;
	case CampDefine::BaseCampBlue:
		nWinGuildID  = m_nBlueID;
		nLoseGuildID = m_nRedID;
		break;
	default:
		return;
		break;
	}

	// ����ս������
	GameGuild* pWinGuild = theGameGuildManager.GetGuild( nWinGuildID );
	GameGuild* pLoseGuild = theGameGuildManager.GetGuild( nLoseGuildID );
	if ( pWinGuild == NULL || pLoseGuild == NULL )
	{ return; }

	MsgCampGuildBattleResult xResult;
	xResult.nWinGuildID  = nWinGuildID;
	xResult.nLoseGuildID = nLoseGuildID;
	pWinGuild->SendMessageToGuild(&xResult);
	pLoseGuild->SendMessageToGuild(&xResult);

	const CampBattleConfig* pCampBattleConfig = m_pBattleManager->GetBattleConfig();
	for ( int i = 0; i < pCampBattleConfig->GetRewardSettingCount(); ++i )
	{
		const CampBattleConfig::RewardSetting* pSetting = pCampBattleConfig->GetRewardSetting( i );
		if ( pSetting == NULL )
		{ continue; }

		switch ( pSetting->GetType() )
		{
		case CampBattleConfig::RewardSetting::RewardGuildExp:   // �������ɾ���
			{
				pWinGuild->SendGuildDataChangeReqMessage( GuildDefine::UpdateGuildExp, GuildDefine::OperateAdd, pSetting->GetWinValue() );

				//LYH��־���
				theLogEventService.LogGuildDetail(0,0,pWinGuild->GetID(),0,pSetting->GetWinValue(),0,"NULL");

					
				pLoseGuild->SendGuildDataChangeReqMessage( GuildDefine::UpdateGuildExp, GuildDefine::OperateAdd, pSetting->GetLoseValue() );

				//LYH��־���
				theLogEventService.LogGuildDetail(0,0,pLoseGuild->GetID(),0,pSetting->GetLoseValue(),0,"NULL");
			}
			break;
		case CampBattleConfig::RewardSetting::RewardGuildMission:   // ��������ʹ����
			{
				pWinGuild->SendGuildDataChangeReqMessage( GuildDefine::UpdateGuildMission, GuildDefine::OperateAdd, pSetting->GetWinValue() );
				pLoseGuild->SendGuildDataChangeReqMessage( GuildDefine::UpdateGuildMission, GuildDefine::OperateAdd, pSetting->GetLoseValue() );
			}
			break;
		case CampBattleConfig::RewardSetting::RewardGuildSalary:    // �������ɽ���
			{
				pWinGuild->SendGuildDataChangeReqMessage( GuildDefine::UpdateGuildSalary, GuildDefine::OperateAdd, pSetting->GetWinValue() );
				pLoseGuild->SendGuildDataChangeReqMessage( GuildDefine::UpdateGuildSalary, GuildDefine::OperateAdd, pSetting->GetLoseValue() );
			}
			break;
		case CampBattleConfig::RewardSetting::RewardPlayerExp:  // �������˾���
			{   // ֻ�Բμӵ����
				for ( BattlePlayerMapIter iter = m_mapBattlePlayer.begin(); iter != m_mapBattlePlayer.end(); ++iter )
				{
					GamePlayer* pPlayer = GameGuild::GetPlayer( iter->first );
					if ( pPlayer == NULL )
					{ continue; }

					unsigned int nRewardValue = ( iter->second.GetFightCamp() == uchFightCamp ? pSetting->GetWinValue() : pSetting->GetLoseValue() );
					unsigned int nRewardExp = nRewardValue * pPlayer->GetLevel();
					pPlayer->IncreaseExp( nRewardExp, 0, NULL );

				}
			}
			break;
		case CampBattleConfig::RewardSetting::RewardPlayerGuildOffer:   // �����ﹱ
			{
				for ( BattlePlayerMapIter iter = m_mapBattlePlayer.begin(); iter != m_mapBattlePlayer.end(); ++iter )
				{
					GamePlayer* pPlayer = GameGuild::GetPlayer( iter->first );
					if ( pPlayer == NULL )
					{ continue; }

					unsigned int nRewardValue = ( iter->second.GetFightCamp() == uchFightCamp ? pSetting->GetWinValue() : pSetting->GetLoseValue() );
					pPlayer->OperateGuildOffer( GuildDefine::OperateAdd, nRewardValue );
				}
			}
			break;
		default:
			break;
		}
	}
	//����ս������������
	const CampGuildBattleConfig* pGuildBattleConfig = static_cast<const CampGuildBattleConfig*>(pCampBattleConfig);
	int WinItemID = pGuildBattleConfig->GetOtherReward().GetWinItemID();
	int LoseItemID = pGuildBattleConfig->GetOtherReward().GetLoseItemID();
	int OtherSum = pGuildBattleConfig->GetOtherReward().GetOtherSum();
	int OtherItemID = pGuildBattleConfig->GetOtherReward().GetOtherItemID();
	//ʤ���Ĺ������Ѫսɳ���Ļ���
	//�����������������
	GS2CSUpdateGuildCampBattlePoint msgWin;
	msgWin.GuildID = nWinGuildID;
	msgWin.Point = pWinGuild->GetGuildCampBattlePoint() + pGuildBattleConfig->GetOtherReward().GetWinPoint();
	GettheServer().SendCenterServerMsg( &msgWin );
	GS2CSUpdateGuildCampBattlePoint msgLose;
	msgLose.GuildID = nLoseGuildID;
	msgLose.Point = pLoseGuild->GetGuildCampBattlePoint() + pGuildBattleConfig->GetOtherReward().GetLosePoint();
	GettheServer().SendCenterServerMsg( &msgLose );
	//1.�����ʼ������в�ս����� ���������͹�ȥ  
	vector<PAIR> vec;    
	for(BattlePlayerMapIter curr = m_mapBattlePlayer.begin(); curr !=m_mapBattlePlayer.end(); ++curr)    
	{    
		vec.push_back(make_pair(curr->first, curr->second));    
	}    
	sort(vec.begin(), vec.end(), cmp); 
	//�Ѿ��������
	vector<PAIR>::iterator Iter = vec.begin();
	int WinSum = 0;
	int LoseSum = 0;
	vector<int> vecWin;
	vector<int> vecLose;
 	for(;Iter != vec.end();++Iter)
	{
		int PlayerID = Iter->first;
		GamePlayer* pPlayer = GameGuild::GetPlayer( PlayerID );
		if ( pPlayer == NULL )
			continue;
		int TotleKillSum = Iter->second.GetTotalKillCount();
		int FighCamp = Iter->second.GetFightCamp();
		int ItemID = 0;
		bool IsNeedOtherReward = false;	
		if(CampDefine::GetBaseFightCamp( FighCamp )== CampDefine::GetBaseFightCamp( uchFightCamp ))
		{ 
			ItemID = WinItemID;
			if(WinSum < OtherSum)
			{
				IsNeedOtherReward = true;
				++WinSum;
				vecWin.push_back(PlayerID);
			}
		}
		else
		{
			ItemID = LoseItemID;
			if(LoseSum < OtherSum)
			{
				IsNeedOtherReward = true;
				++LoseSum;
				vecLose.push_back(PlayerID);
			}
		}
		//������Ϻ� ���ǿ�ʼ�����ʼ�
		GS2CSSendMailReq xReq;
		xReq.charDbId = RelationDefine::InitID;
		xReq.mail.type  = SMail::EMT_System;
		xReq.mail.state = SMail::EMS_NotOpen;
		xReq.mail.sendTime = TimeEx::GetNowTime();        
		// ������
		xReq.mail.owners[EM_FromIndex].charDbId = 0;
		sprintf_s( xReq.mail.owners[EM_FromIndex].addressName, sizeof( xReq.mail.owners[EM_FromIndex] ) - 1, theXmlString.GetString( eText_MailSystemName ) );
		// �ռ���
		xReq.mail.owners[EM_ToIndex].charDbId = PlayerID;	
		HelperFunc::SafeNCpy( xReq.mail.owners[EM_ToIndex].addressName, pPlayer->GetCharInfo().baseinfo.aptotic.szCharacterName, sizeof( xReq.mail.owners[EM_ToIndex].addressName ) );
		//����
		sprintf_s( xReq.mail.content, sizeof( xReq.mail.content ) - 1,theXmlString.GetString( eText_MailFamilyDisbanded ) );
		//����
		sprintf_s( xReq.mail.title, sizeof( xReq.mail.title ) - 1, theXmlString.GetString( eText_MailSystemTitle ) );
		//��Ʒ
		xReq.mail.accessory.type = SMail::EAT_Item;
		{
			SCharItem item;
			theRunTimeData.CreateItem(ItemID, 1,HelperFunc::CreateID(),item);
			memcpy( &xReq.mail.accessory.content, &item, sizeof(SCharItem)); 
			GettheServer().SendCenterServerMsg( &xReq );
		}
		if(IsNeedOtherReward)
		{
			SCharItem item;
			theRunTimeData.CreateItem(OtherItemID, 1, HelperFunc::CreateID(),item);
			memcpy( &xReq.mail.accessory.content, &item, sizeof(SCharItem) ); 
			GettheServer().SendCenterServerMsg( &xReq );
		}
	}

	//2.����������ͻ��� �䳤������
	if(OtherSum >= vecWin.size() && vecLose.size() <= OtherSum && OtherSum<=10)
	{
		int WinSum = min( vecWin.size(),OtherSum);
		MsgCampGuildBattleRewardInfo msgWin;
		msgWin.nWinGuildID = nWinGuildID;
		msgWin.nLoseGuildID = nLoseGuildID;
		msgWin.WinItemID = WinItemID;
		msgWin.LoseItemID = LoseItemID;
		msgWin.OtherItemID = OtherItemID;
		msgWin.OtherSum = WinSum;
		{
			for(int i =0;i<WinSum;++i)
			{
				BattlePlayer* pBattlePlayer = &m_mapBattlePlayer.find(vecWin[i])->second;
				if(pBattlePlayer)
				{
					msgWin.PlayerID[i] = vecWin[i];
					strcpy_s(msgWin.Name[i],GuildDefine::MaxNameLength,pBattlePlayer->GetName());
					msgWin.Point[i] = pBattlePlayer->GetTotalKillCount();
				}
			}
		}

		int LoseSum = min( vecLose.size(),OtherSum);
		MsgCampGuildBattleRewardInfo msgLose; 
		msgLose.nLoseGuildID = nLoseGuildID;
		msgLose.WinItemID = WinItemID;
		msgLose.LoseItemID = LoseItemID;
		msgLose.OtherItemID = OtherItemID;
		msgLose.OtherSum = LoseSum;
		{
			for(int i =0;i<LoseSum;++i)
			{
				BattlePlayer* pBattlePlayer = &m_mapBattlePlayer.find(vecLose[i])->second;
				if(pBattlePlayer)
				{
					msgLose.PlayerID[i] = vecLose[i];
					strcpy_s(msgLose.Name[i],GuildDefine::MaxNameLength,pBattlePlayer->GetName());
					msgLose.Point[i] = pBattlePlayer->GetTotalKillCount();
				}
			}
		}

		//�������ú��˺� ���͸����ʵ����
		for(BattlePlayerMapIter curr = m_mapBattlePlayer.begin(); curr !=m_mapBattlePlayer.end(); ++curr)    
		{    
			if(CampDefine::GetBaseFightCamp(curr->second.GetFightCamp()) == CampDefine::GetBaseFightCamp(uchFightCamp))
			{
				//ʤ����
				msgWin.KissSum = curr->second.GetTotalKillCount();
				GamePlayer * pPlayer = theRunTimeData.GetGamePlayerByDBID( curr->first );
				if(pPlayer)
					pPlayer->SendMessageToClient(&msgWin);
				//SendMessageToPlayer(curr->first, msgWin, false ); 
			}
			else
			{
				//ʧ�ܷ�
				msgLose.KissSum = curr->second.GetTotalKillCount();
				GamePlayer * pPlayer = theRunTimeData.GetGamePlayerByDBID( curr->first );
				if(pPlayer)
					pPlayer->SendMessageToClient(&msgLose);
				//SendMessageToPlayer(curr->first, msgLose, false ); 
			}
		}  

	}
}

void CampGuildBattle::KillCampBattleMonster( unsigned char uchFightCamp, unsigned int nPlayerID, int nMonsterID )
{
    CampBattle::KillCampBattleMonster( uchFightCamp, nPlayerID, nMonsterID );

    // �����������, ������10���Ӻ���ˢһ������
    const CampGuildBattleConfig* pBattleConfig = static_cast< const CampGuildBattleConfig* >( m_pBattleManager->GetBattleConfig() );
	map<int,CampGuildBattleConfig::NormalMonster> mapList;
	pBattleConfig->GetNormalMonster(mapList);
	if(mapList.count(nMonsterID) == 1 && m_xNormalTimer.count(nMonsterID) == 1)
	{
		m_xNormalTimer[nMonsterID].StartTimer( HQ_TimeGetTime(), mapList[nMonsterID].GetTimeSpace() * OneMinuteMicroSecond );
	}

    // �ж��Ƿ��Ǳ�Ӫ
    /*RefreshIndexMapIter iter = m_mapRefreshIndex.find( nMonsterID );
    if ( iter == m_mapRefreshIndex.end() )
    { return; }*/
	for ( int i = 0; i < pBattleConfig->GetGetRefreshSettingCount(); ++i )
    {
        const CampGuildBattleConfig::RefreshSetting* pSetting = pBattleConfig->GetRefreshSettingByIndex( i );
        if ( pSetting == NULL )
        { continue; }

        const CampGuildBattleConfig::RefreshSetting::BarracksSetting& xRedSetting = pSetting->GetRedBarracksSetting();
		const CampGuildBattleConfig::RefreshSetting::BarracksSetting& xBlueSetting = pSetting->GetBlueBarracksSetting();
		RefreshIndexMapIter iter = m_mapRefreshIndex.find( pSetting->GetBarracksID() );
		if ( iter == m_mapRefreshIndex.end() )
			continue;
		if(xRedSetting.GetMonsterID() == nMonsterID)
		{
			if(iter->second.GetBlueIndex() != -1)
				iter->second.SetBlueIndex( iter->second.GetMaxBlueIndex() );
			iter->second.SetRedIndex( -1 );
			m_RedBarracksDeadSum++;	
			ProcessBoss();
		}
		else if(xBlueSetting.GetMonsterID() == nMonsterID)
		{
			if(iter->second.GetRedIndex() != -1)
				iter->second.SetRedIndex( iter->second.GetMaxRedIndex() );
			iter->second.SetBlueIndex( -1 );
			m_BlueBarracksDeadSum++;
			ProcessBoss();
		}
		else
			continue;
	}

    // ��ɱһ������ˢ����, �Լ���ˢһ·���
  //  switch ( CampDefine::GetBaseFightCamp( uchFightCamp ) )//��Ӫ �ж� Ҫ������  ��ˢ�췢BOSS
  //  {
  //  case CampDefine::BaseCampRed:
		//iter->second.SetBlueIndex( iter->second.GetMaxBlueIndex() );
  //      iter->second.SetRedIndex( -1 );
		//m_BlueBarracksDeadSum++;
		//ProcessBoss();
  //      break;
  //  case CampDefine::BaseCampBlue:
		//iter->second.SetRedIndex( iter->second.GetMaxRedIndex() );
  //      iter->second.SetBlueIndex( -1 );
		//m_RedBarracksDeadSum++;	
		//ProcessBoss();
  //      break;
  //  default:
  //      return;
  //      break;
  //  }
	//�ж��Ƿ�Ϊ����BOSS �ǵĻ�����ս�� �ֳ�ʤ��
	if(pBattleConfig->GetRedBoss().GetID() == nMonsterID)
	{
		m_RedBoss = NULL;
		//���ú췽ʧ��
		//m_nBlueResource += 1000;
		//m_nRedResource = 0;
		ProcessStatusChange( CampDefine::StatusEnd );
	}
	else if(pBattleConfig->GetBlueBoss().GetID() == nMonsterID)
	{
		m_BlueBoss = NULL;
		//��������ʧ��
		//m_nBlueResource = 0;
		//m_nRedResource += 1000;
		ProcessStatusChange( CampDefine::StatusEnd );
	}
}
void CampGuildBattle::ProcessBoss()
{
	const CampGuildBattleConfig* pBattleConfig = static_cast< const CampGuildBattleConfig* >( m_pBattleManager->GetBattleConfig() );
    int Sum = pBattleConfig->GetGetRefreshSettingCount();
	 MonsterCreateData xCreateData;
	if(m_RedBarracksDeadSum == Sum)
	{
		//ˢ��BOSS
		const CampGuildBattleConfig::BossMonster& pMonster = pBattleConfig->GetRedBoss();
        xCreateData.SetMonsterID( pMonster.GetID() );
        xCreateData.SetPostionX( pMonster.GetPosX() );
        xCreateData.SetPostionY( pMonster.GetPosY() );
        //xCreateData.SetDirX( pMonster.GetDirX() );
       // xCreateData.SetDirY( pMonster.GetDirY() );

		xCreateData.SetDirection(pMonster.GetAngle());

        xCreateData.SetFightCamp( CampDefine::GuildCampRed );
		xCreateData.SetRouteID( pMonster.GetRouteID() );
		xCreateData.SetMapID(m_nEctypeMapID);
        m_RedBoss = MonsterCreater::CreateNormalMonster( xCreateData );

		m_RedBarracksDeadSum = -1;//�����Ӫ�Ѿ�ɱ����
	}
	else if(Sum == m_BlueBarracksDeadSum)
	{
		//ˢ��BOSS
		const CampGuildBattleConfig::BossMonster& pMonster = pBattleConfig->GetBlueBoss();
        xCreateData.SetMonsterID( pMonster.GetID() );
        xCreateData.SetPostionX( pMonster.GetPosX() );
        xCreateData.SetPostionY( pMonster.GetPosY() );
       // xCreateData.SetDirX( pMonster.GetDirX() );
       // xCreateData.SetDirY( pMonster.GetDirY() );

		xCreateData.SetDirection(pMonster.GetAngle());

		xCreateData.SetFightCamp( CampDefine::GuildCampBlue );
		xCreateData.SetRouteID( pMonster.GetRouteID() );
		xCreateData.SetMapID(m_nEctypeMapID);
        m_BlueBoss = MonsterCreater::CreateNormalMonster( xCreateData );

		m_BlueBarracksDeadSum = -1;
	}
}
void CampGuildBattle::ProcessChangeToFightStatus()
{
    CampBattle::ProcessChangeToFightStatus();

    if ( GetStatus() == CampDefine::StatusEnd )
    { return; } // �����˾Ͳ�ˢ����

    // ����ˢ�ֶ�ʱ��
    m_xRefreshTimer.StartTimer( 1, CampGuildBattleConfig::RefreshSetting::GetTimeSpace() * 1000 );

    const CampGuildBattleConfig* pBattleConfig = static_cast< const CampGuildBattleConfig* >( m_pBattleManager->GetBattleConfig() );
    //const CampGuildBattleConfig::NormalMonster& xNormalMonster = pBattleConfig->GetNormalMonster();

	map<int,CampGuildBattleConfig::NormalMonster> mapList;
	pBattleConfig->GetNormalMonster(mapList);
	map<int,CampGuildBattleConfig::NormalMonster>::iterator Iter = mapList.begin();
	for(;Iter !=mapList.end();++Iter)
	{
		if(m_xNormalTimer.count(Iter->first) != 1)
			continue;
		m_xNormalTimer[Iter->first].StartTimer( HQ_TimeGetTime(), Iter->second.GetTimeSpace() * OneMinuteMicroSecond );
	}
    //m_xNormalTimer.StartTimer( HQ_TimeGetTime(), xNormalMonster.GetTimeSpace() * OneMinuteMicroSecond );
}

void CampGuildBattle::ProcessRefreshCampMonster()
{
    if ( !m_xRefreshTimer.DoneTimer( HQ_TimeGetTime() ) )
    { return; }

    GameStage* pStage = theGameWorld.GetStageById( GetBattleMapID() );
    if ( pStage == NULL )
    { return; }

    MonsterCreateData xCreateData;
    xCreateData.SetMapID( pStage->GetStageID() );
    xCreateData.SetCreateType( 0 );
    xCreateData.SetCount( CampGuildBattleConfig::RefreshSetting::GetCount() );
    xCreateData.SetRadius( CampGuildBattleConfig::RefreshSetting::GetRadius() );
    xCreateData.SetFightCamp( CampGuildBattleConfig::RefreshSetting::GetType() );

    const CampGuildBattleConfig* pBattleConfig = static_cast< const CampGuildBattleConfig* >( m_pBattleManager->GetBattleConfig() );
    for ( RefreshIndexMapIter iter = m_mapRefreshIndex.begin(); iter != m_mapRefreshIndex.end(); ++iter )
    {
        const CampGuildBattleConfig::RefreshSetting* pSetting = pBattleConfig->GetRefreshSetting( iter->first );
        if ( pSetting == NULL )
        { continue; }

        // �췽��Ӫˢ��
        const CampGuildBattleConfig::RefreshSetting::BarracksSetting& xRedBarrackSetting = pSetting->GetRedBarracksSetting();
        const CampGuildBattleConfig::RefreshSetting::MonsterDataList* pRedMonsterDataList = xRedBarrackSetting.GetMonster( iter->second.GetRedIndex() );
		if(pRedMonsterDataList != NULL)
		{
			//ˢ��һ����
			vector<CampGuildBattleConfig::RefreshSetting::MonsterData> vec;
			pRedMonsterDataList->GetAllMonster(vec);
			vector<CampGuildBattleConfig::RefreshSetting::MonsterData>::iterator Iter = vec.begin();
			for(;Iter !=vec.end();++Iter)
			{
				//��������ˢ��
				MonsterCreateData xCreateDataRed;
				xCreateDataRed.SetMapID( pStage->GetStageID() );
				xCreateDataRed.SetCount( 1 );
				xCreateDataRed.SetRouteID( Iter->GetRouteID());
				xCreateDataRed.SetPostionX(Iter->GetPosX());
				xCreateDataRed.SetPostionY(Iter->GetPosY());
				xCreateDataRed.SetMonsterID(Iter->GetMonsterID());
				xCreateDataRed.SetDirection(Iter->GetAngle());
				xCreateDataRed.SetFightCamp( CampDefine::GuildCampRed );
				MonsterCreater::ProcessCreateNormalMonster( xCreateDataRed );
			}
		}	

   //     if ( pRedMonsterData != NULL )
   //     {
   //         xCreateData.SetMonsterID( pRedMonsterData->GetMonsterID() );
   //         xCreateData.SetPostionX( xRedBarrackSetting.GetPosX() );
   //         xCreateData.SetPostionY( xRedBarrackSetting.GetPosY() );
   //         //xCreateData.SetDirX( xRedBarrackSetting.GetDirX() );
   //         //xCreateData.SetDirY( xRedBarrackSetting.GetDirY() );

			//xCreateData.SetDirection(xRedBarrackSetting.GetAngle());

   //         xCreateData.SetFightCamp( CampDefine::GuildCampRed );
   //         xCreateData.SetRouteID( pRedMonsterData->GetRouteID() );
			//xCreateData.SetMapID(m_nEctypeMapID);
   //         MonsterCreater::ProcessCreateNormalMonster( xCreateData );
   //     }

        // ������Ӫˢ��
        const CampGuildBattleConfig::RefreshSetting::BarracksSetting& xBlueBarrackSetting = pSetting->GetBlueBarracksSetting();
       
   //     if ( pBlueMonsterData != NULL )
   //     {
   //         xCreateData.SetMonsterID( pBlueMonsterData->GetMonsterID() );
   //         xCreateData.SetPostionX( xBlueBarrackSetting.GetPosX() );
   //         xCreateData.SetPostionY( xBlueBarrackSetting.GetPosY() );
   //         //xCreateData.SetDirX( xBlueBarrackSetting.GetDirX() );
   //         //xCreateData.SetDirY( xBlueBarrackSetting.GetDirY() );

			//xCreateData.SetDirection(xBlueBarrackSetting.GetAngle());

   //         xCreateData.SetFightCamp( CampDefine::GuildCampBlue );
   //         xCreateData.SetRouteID( pBlueMonsterData->GetRouteID() );
			//xCreateData.SetMapID(m_nEctypeMapID);
   //         MonsterCreater::ProcessCreateNormalMonster( xCreateData );
   //     }
		const CampGuildBattleConfig::RefreshSetting::MonsterDataList* pBlueMonsterDataList = xBlueBarrackSetting.GetMonster( iter->second.GetBlueIndex() );
		if(pBlueMonsterDataList != NULL)
		{
			//ˢ��һ����
			vector<CampGuildBattleConfig::RefreshSetting::MonsterData> vec;
			pBlueMonsterDataList->GetAllMonster(vec);
			vector<CampGuildBattleConfig::RefreshSetting::MonsterData>::iterator Iter = vec.begin();
			for(;Iter !=vec.end();++Iter)
			{
				//��������ˢ��
				MonsterCreateData xCreateDataBlue;
				xCreateDataBlue.SetMapID( pStage->GetStageID() );
				xCreateDataBlue.SetCount( 1 );
				xCreateDataBlue.SetRouteID( Iter->GetRouteID());
				xCreateDataBlue.SetPostionX(Iter->GetPosX());
				xCreateDataBlue.SetPostionY(Iter->GetPosY());
				xCreateDataBlue.SetMonsterID(Iter->GetMonsterID());
				xCreateDataBlue.SetDirection(Iter->GetAngle());
				xCreateDataBlue.SetFightCamp( CampDefine::GuildCampBlue );
				MonsterCreater::ProcessCreateNormalMonster( xCreateDataBlue );
			}
		}	
    }
}

void CampGuildBattle::ProcessRefreshNormalMonster()
{
	map<int,CampGuildBattleConfig::NormalMonster> mapList;
	const CampGuildBattleConfig* pBattleConfig = static_cast< const CampGuildBattleConfig* >( m_pBattleManager->GetBattleConfig() );
	pBattleConfig->GetNormalMonster(mapList);
	map<int,CampGuildBattleConfig::NormalMonster>::iterator Iter = mapList.begin();
	for(;Iter !=mapList.end();++Iter)
	{
		if(m_xNormalTimer.count(Iter->first) != 1)
			continue;
		if(!m_xNormalTimer[Iter->first].DoneTimer())
			continue;
		MonsterCreateData xCreateData;
		xCreateData.SetMapID( GetBattleMapID() );
		xCreateData.SetPostionX( Iter->second.GetPosX() );
		xCreateData.SetPostionY( Iter->second.GetPosY() );
		xCreateData.SetDirection(Iter->second.GetAngle());
		xCreateData.SetMonsterID( Iter->second.GetID() );
		xCreateData.SetCount( 1 );
		xCreateData.SetRadius( 2 );
		xCreateData.SetBodySize( Iter->second.GetBodySize() );
		MonsterCreater::CreateNormalMonster( xCreateData );
		// ֪ͨս�����������
		MsgTellCampGuildBattleRefreshMonster xTell;
		xTell.nMonsterID = Iter->second.GetID();
		xTell.nStringID  = Iter->second.GetString();
		GettheServer().SendMsgToStage( &xTell, GetBattleMapID() );
	}

 //   if ( !m_xNormalTimer.DoneTimer() )
 //   { return; }

 //   const CampGuildBattleConfig* pBattleConfig = static_cast< const CampGuildBattleConfig* >( m_pBattleManager->GetBattleConfig() );
 //   const CampGuildBattleConfig::NormalMonster& xNormalMonster = pBattleConfig->GetNormalMonster();

 //   // ��Roshan ˢ����
 //   MonsterCreateData xCreateData;
 //   xCreateData.SetMapID( GetBattleMapID() );
 //   xCreateData.SetPostionX( xNormalMonster.GetPosX() );
 //   xCreateData.SetPostionY( xNormalMonster.GetPosY() );
 //   //xCreateData.SetDirX( xNormalMonster.GetDirX() );
 //  //xCreateData.SetDirY( xNormalMonster.GetDirY() );

	//xCreateData.SetDirection(xNormalMonster.GetAngle());

 //   xCreateData.SetMonsterID( xNormalMonster.GetID() );
 //   xCreateData.SetCount( 1 );
 //   xCreateData.SetRadius( 2 );
 //   xCreateData.SetBodySize( xNormalMonster.GetBodySize() );
 //   MonsterCreater::CreateNormalMonster( xCreateData );

 //   // ֪ͨս�����������
 //   MsgTellCampGuildBattleRefreshMonster xTell;
 //   xTell.nMonsterID = xNormalMonster.GetID();
 //   xTell.nStringID  = xNormalMonster.GetString();
 //   GettheServer().SendMsgToStage( &xTell, GetBattleMapID() );
}