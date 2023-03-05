#include "CampGuildUnionBattleManager.h"
#include "GlobalDBManager.h"
#include "Guild.h"
#include "GuildManager.h"
#include "GamePlayer.h"
#include "CampBattleMessage.h"
#include "CampGuildUnionBattleConfig.h"
#include "GameWorld.h"
#include "CampBattle.h"
#include "CampGuildUnionBattle.h"
CampGuildUnionBattleManager::CampGuildUnionBattleManager()
{
	SetBattleType( CampDefine::BattleTypeGuildUnion );//设置公会战场类型
	m_BattleValue = GuildDefine::CampBattleGuildUnion;
	m_BattleValueIsOpen = theGameGuildManager.GetCampBattleConfig()->m_GuildUnionSetting.IsOpen;
}
bool CampGuildUnionBattleManager::SignUpCampBattle( GamePlayer* pPlayer )//处理指定玩家报名
{
	if(theGameGlobalDBManager.GetBattleSum() == 0)
	{
		GameGuild* pGuild = pPlayer->GetGuild();
		if ( pGuild == NULL || !pGuild->IsMaster( pPlayer->GetDBCharacterID() ) )
		{
			// 报名的不是帮主
			pPlayer->SendOperateAckToClient< MsgCampBattleSignUpAck >( CampDefine::SignUp_MustGuildMaster );
			return false;
		}
		if ( !CampBattleManager::SignUpCampBattle( pPlayer, pGuild->GetID()) )
		{ return false; }
		
		//判断报名是否已满
		int MaxSum = 2<<theCampGuildUnionBattleConfig.GetBattleSum();
		if(m_vecSignUp.size() >= MaxSum)
		{
			pPlayer->SendOperateAckToClient< MsgCampBattleSignUpAck >( CampDefine::SignUp_GuildBattleFull );//报名已经满了不可以再报名了
			return false;
		}

		AddSignUpUnit( pGuild->GetID() );
		// 报名成功
		pPlayer->SendOperateAckToClient< MsgCampBattleSignUpAck >( CampDefine::SignUp_Success );
		return true;
	}
	else
	{	
		GameGuild * pGuild = theGameGuildManager.GetGuild(pPlayer->GetGuildID());
		if(pGuild && pGuild->GetBattleSum() == theGameGlobalDBManager.GetBattleSum())
			pPlayer->SendOperateAckToClient< MsgCampBattleSignUpAck >( CampDefine::SignUp_GuildUnionBattleNone );
		else
			pPlayer->SendOperateAckToClient< MsgCampBattleSignUpAck >( CampDefine::SignUp_GuildUnionBattleSumError );
        return false;
	}
}
void CampGuildUnionBattleManager::ProcessChangeToPrepareStatus()// 对已经报名的公会进行配对处理
{
	if(theGameGlobalDBManager.GetBattleSum() != 0)
	{
		//已经是以后的轮数了
		//获取全部的公会 我们开始处理 判断公会BattleSum为当前值的公会的全部ID 这些公会会被动的处理
		map< unsigned int, GameGuild* >& pMap = theGameGuildManager.GetAllGuild();
		if(pMap.empty())
		{
			//公会为空 
			m_vecSignUp.clear();
			return;
		}
		map< unsigned int, GameGuild* >::iterator Iter = pMap.begin();
		for(;Iter != pMap.end();++Iter)
		{
			if(Iter->second->GetBattleSum() == theGameGlobalDBManager.GetBattleSum())
			{
				m_vecSignUp.push_back(Iter->second->GetID());//加入到报名列表
			}
			else if(Iter->second->GetBattleSum() != 0)
			{
				Iter->second->SetBattleSum(0);

				CS2GSGuildBattleSum msg;
				msg.nGuildID = Iter->second->GetID();
				msg.battleSum = 0;
				GettheServer().SendMsgToCenterServer( &msg );
			}
		}
	}
	m_mapMatchUnit.clear();
	if ( m_vecSignUp.empty())
		return; 
		
	//对集合的公会进行配对 多余的直接晋级 给予奖励
	if(m_vecSignUp.size()% 2 == 1)
	{
		//随机选择一个公会 让他直接晋级
		int RandSum = theRand.rand32() % m_vecSignUp.size();
		//设置指定公会直接晋级
		uint32 GuildID = m_vecSignUp[RandSum];
		m_vecSignUp[RandSum] = 0;//设置标记为0
		GameGuild * pGameGuild = theGameGuildManager.GetGuild(GuildID);
		if(pGameGuild)
		{	
			//1.给予指定的奖励 设置公会的轮数
			uint32 Num = pGameGuild->GetBattleSum();
			uint32 Sum = theCampGuildUnionBattleConfig.GetBattleSum();
			++Num;
			if(Num>=Sum)
				Num = 0;
			pGameGuild->SetBattleSum(Num);

			CS2GSGuildBattleSum msg;
			msg.nGuildID = GuildID;
			msg.battleSum = Num;
			GettheServer().SendMsgToCenterServer( &msg );
		}
	}
	int Sum = m_vecSignUp.size() /2;
	for(int i =0;i<Sum;++i)
	{
		//进行配对处理
		int RandOne=0;
		do
		{
			RandOne = theRand.rand32() % m_vecSignUp.size();
		}while(m_vecSignUp[RandOne] == 0);

		int RandTwo=0;
		do
		{
			RandTwo = theRand.rand32() % m_vecSignUp.size();
		}while(RandTwo == RandOne || m_vecSignUp[RandTwo] == 0);

		m_mapMatchUnit[ m_vecSignUp[RandOne] ] = m_vecSignUp[RandTwo];
		
		m_vecSignUp[RandOne]  = 0;
		m_vecSignUp[RandTwo]  = 0;
	}
	m_vecSignUp.clear();
}
void CampGuildUnionBattleManager::ProcessChangeToEnterStatus()
{
    // 创建副本场景, 
    for ( MatchUnitMapIter iter = m_mapMatchUnit.begin(); iter != m_mapMatchUnit.end(); ++iter )
    {
        // 创建副本
        unsigned int nBattleMapID = theGameWorld.GetEctypeMapID( GetMapID(), true );
        theGameWorld.MultiCreateStage( GetMapID(), nBattleMapID );

        // 创建战场
        CampBattle* pCampBattle = CampBattle::CreateBattle< CampGuildUnionBattle >();
        pCampBattle->SetBattleManager( this );
        pCampBattle->SetBattleMapID( nBattleMapID );
        pCampBattle->SetRedID( iter->first );
        pCampBattle->SetBlueID( iter->second );
        pCampBattle->SetWinResource( m_pBattleConfig->GetResourceSetting().GetMaxResource() );
       
        // 发送是否进入战场消息
        pCampBattle->SendEnterCampBattleMessage();

        // 添加到战场列表中
        AddCampBattle( pCampBattle );
    }
    m_mapMatchUnit.clear();
}
void CampGuildUnionBattleManager::ProcessChangeToSignUpStatus()
{
	//当战场管理器的状态有Init转换到报名状态的时候 我们需要设置一下战场的基本数据
	//1.根据当前进行的轮数 设置好配置文件引用
	SetBattleConfig(&theCampGuildUnionBattleConfig.GetGuildBattleSumConfig(theGameGlobalDBManager.GetBattleSum()));
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
void CampGuildUnionBattleManager::ProcessChangeToEndStatus()
{
	//当战场设置结束的时候 我们需要处理一下管理器的状态
	uint32 Num = theGameGlobalDBManager.GetBattleSum();
	uint32 Sum = theCampGuildUnionBattleConfig.GetBattleSum();
	++Num;
	if(Num>=Sum)
		Num = 0;
	theGameGlobalDBManager.SetBattleSum(Num);//记录下次战场的轮数 并且保存到数据库去
}
bool CampGuildUnionBattleManager::ShowCampBattleEnter( GamePlayer* pPlayer )
{
    GameGuild* pGuild = pPlayer->GetGuild();
	if ( pGuild == NULL || pGuild->GetBattleSum() != theGameGlobalDBManager.GetBattleSum())
    { return false; }

    return CampBattleManager::ShowCampBattleEnter( pPlayer, pGuild->GetID() );
}

bool CampGuildUnionBattleManager::EnterCampBattle( GamePlayer* pPlayer )
{
    GameGuild* pGuild = pPlayer->GetGuild();
    if ( pGuild == NULL )
    { 
        pPlayer->SendOperateAckToClient< MsgEnterCampBattleAck >( CampDefine::Enter_MustSignUpGuild );
        return false;
    }
	else if(pGuild->GetBattleSum() != theGameGlobalDBManager.GetBattleSum())
	{
		pPlayer->SendOperateAckToClient< MsgEnterCampBattleAck >( CampDefine::Enter_BattleSumError );
        return false;
	}

    return CampBattleManager::EnterCampBattle( pPlayer, pGuild->GetID() );   
}
void CampGuildUnionBattleManager::ProcessBattleInitStatus( unsigned int nCurrentTime, int nDayOfWeek, int nHour, int nMinute )
{
	if(!m_pBattleConfig)//因为center的全局数据还没发来 所以暂时先别判断 等待数据处理
		return;
	// 判断是否到了战场准备时间
    if ( !CheckBattleSignUpTime( nCurrentTime, nDayOfWeek, nHour, nMinute ) )
    { return; }

    // 处理战场改变到准备状态
    ProcessChangeStatus( CampDefine::StatusSignUp );
}