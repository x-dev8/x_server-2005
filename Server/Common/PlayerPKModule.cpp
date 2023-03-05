#include "GamePlayer.h"
#include "MapConfig.h"
#include "DuelHandler.h"
#include "TeamManager.h"
#include "ShareData.h"
#include "GameTime.h"
#include "GameWorld.h"
#include "PKConfig.h"
#include "SevenDays.h"
#include "XmlStringLanguage.h"
#include "GlobalDBManager.h"

void GamePlayer::SetPKValue( int nValue, char chOp /* = Op_Add */, unsigned char chSendMessage /* = 1 */ )
{
    if ( chOp == PKValueOp_Set )
    {
        m_nPKValue = nValue;
        if ( m_nPKValue > /*MaxPKValue*/thePKConfig.GetMaxPKValue() )
        { 
            m_nPKValue = /*MaxPKValue*/thePKConfig.GetMaxPKValue();
        }
        if ( m_nPKValue < /*MinPKValue*/ thePKConfig.GetMinPKValue())
        {
            m_nPKValue = /*MinPKValue*/thePKConfig.GetMinPKValue();
        }
    }
    else if ( chOp == PKValueOp_Add && nValue > 0 )
    {
        int nTempPkValue = m_nPKValue;
        m_nPKValue += nValue;
        if ( m_nPKValue > /*MaxPKValue*/thePKConfig.GetMaxPKValue() )
        { 
            m_nPKValue = /*MaxPKValue*/thePKConfig.GetMaxPKValue();
        }
        else if ( nTempPkValue < 0 )        
        {
            if ( m_nPKValue > 0 )       // 使用道具洗点时, 只能洗到白名
            {
                m_nPKValue = 0;         
            }
        }
    }
    else if ( chOp == PKValueOp_Reduce && nValue > 0 )
    {
        int nTempPkValue = m_nPKValue;
        m_nPKValue -= nValue;
        if ( m_nPKValue < /*MinPKValue*/thePKConfig.GetMinPKValue() )
        {
            m_nPKValue = /*MinPKValue*/thePKConfig.GetMinPKValue();
        }
        else if ( nTempPkValue > 0 )
        {
            if ( m_nPKValue < 0 )
            {
                m_nPKValue = 0;
            }
        }
    }
    else
    {
        return; 
    }

    if ( chSendMessage == BV_SendMessage )
    {
        TellClientPKValue();
    }
}

bool GamePlayer::GMSetPKMode( uint8 nMode )
{
    if ( nMode >= PKMode_MaxValue )
    { return false; }
		
    this->m_nPKMode = nMode;

    //进入狂暴模式处理
    if ( GetPKMode() == PKMode_Critical)
    { EnterCriticalMode(); }

    m_gtUpdatePKModeTimer.StopTimer();

    TellClientPKValue();
    return true;
}
bool GamePlayer::SetPKMode( uint8 nMode, uint8 chSendMessage )
{
    if ( nMode >= PKMode_MaxValue )
    { return false; }

    if ( GetPKMode() == nMode )
    { return false; }

    if ( GetLevel() < g_Cfg.m_nPKProtectLevel )
    {
        if ( chSendMessage == BV_SendMessage )
        {
            MsgAckResult xResult;     
            xResult.result = ER_InProtectLevel;
            xResult.value = g_Cfg.m_nPKProtectLevel;
            GettheServer().SendMsgToSingle( &xResult, this );
            return false;
        } 
    }

    if ( nMode != PKMode_Critical )
    {
        switch(m_nPKMode)
        {
        case PKMode_Normal:
			{
				if (nMode != PKMode_AttackFight && nMode != PKMode_AttackGuild && m_gtUpdatePKModeTimer.IsStart() )
                {
                    if ( chSendMessage == BV_SendMessage )
                    {
                        MsgAckResult xResult;     
                        xResult.result = ER_ChangePKModeOften;
                        xResult.value = m_nPKValue;
                        GettheServer().SendMsgToSingle( &xResult, this );
                    }
                    return false;
                }
			}
			break;
		case PKMode_Guild:
			{
				if( nMode == PKMode_Normal && m_gtUpdatePKModeTimer.IsStart())
				{
					if ( chSendMessage == BV_SendMessage )
                    {
                        MsgAckResult xResult;     
                        xResult.result = ER_ChangePKModeOften;
                        xResult.value = m_nPKValue;
                        GettheServer().SendMsgToSingle( &xResult, this );
                    }
                    return false;
				}
				else if(nMode ==PKMode_AttackFight)
					return false;
			}
			break;
		case PKMode_Fight:
			{ 
				if( nMode == PKMode_Normal && m_gtUpdatePKModeTimer.IsStart())
				{
					if ( chSendMessage == BV_SendMessage )
                    {
                        MsgAckResult xResult;     
                        xResult.result = ER_ChangePKModeOften;
                        xResult.value = m_nPKValue;
                        GettheServer().SendMsgToSingle( &xResult, this );
                    }
                    return false;
				}
				else if(nMode == PKMode_AttackGuild)
					return false;
			}
			break;
        case PKMode_Critical:
            {// 如果 PK值大于 1 不能改变狂暴模式
				if ( m_nPKValue >= /*0*/ thePKConfig.GetEnterCriticalPK() )
                {
                    if ( chSendMessage == BV_SendMessage )
                    {
                        MsgAckResult xResult;     
                        xResult.result = ER_CannotChangePKMode;
                        xResult.value = m_nPKValue;
                        GettheServer().SendMsgToSingle( &xResult, this );
                    }
                    return false;
                }
				if(nMode == PKMode_AttackFight || nMode == PKMode_AttackGuild)
					return false;
                // 30分钟时间还未到
                if ( m_gtUpdateCriticalModeTimer.IsStart() )
                {
                    if ( chSendMessage == BV_SendMessage )
                    {
                        MsgAckResult xResult;     
                        xResult.result = ER_PKModeCriticalNoTimer;
                        xResult.value = m_nPKValue;
                        GettheServer().SendMsgToSingle( &xResult, this );
                    }
                    return false;
                }
            }
            break;
		case PKMode_AttackFight:
		case PKMode_AttackGuild:
			{
				//反击模式 判断是时间到了切换 还是 客户端手动切换的 		
				if (!m_IsUpdateLevelPKAttMode && chSendMessage == BV_SendMessage )
                {
                    MsgAckResult xResult;     
                    xResult.result = ER_ChangePKModeAttact;
                    xResult.value = m_nPKValue;
                    GettheServer().SendMsgToSingle( &xResult, this );
					return false;//在反击模式是不可以手动切换的
                }
			}
			break;
        }
    }

    //设置PK模式
	if((m_nPKMode == PKMode_Normal && (nMode == PKMode_Guild || nMode == PKMode_Fight)) ||
	(nMode == PKMode_Normal && (m_nPKMode == PKMode_Guild || nMode == PKMode_Fight)))
		 m_gtUpdatePKModeTimer.StartTimer( HQ_TimeGetTime(), PKModeChangeDelayed );

	if((m_nPKMode == PKMode_AttackFight || m_nPKMode== PKMode_AttackFight) && m_AttertUpdateTime.IsStart())
		m_AttertUpdateTime.StopTimer(); 
    this->m_nPKMode = nMode;

    //进入狂暴模式处理
    if ( GetPKMode() == PKMode_Critical)
    { EnterCriticalMode(); }

    if ( chSendMessage == BV_SendMessage )
    {
        TellClientPKValue();
    }

    return true;
}
bool GamePlayer::CheckCanAttackPlayer( GamePlayer* pTarget )
{
    if ( this == NULL || pTarget == NULL || this == pTarget )
    { return false; }

    if( theDuelHandler()->IsDuelFight( GetID(), pTarget->GetID() ) )
    { return true; }    //都是玩家，如果是决斗或者处于PK区域，可以攻击

    if ( GetLevel() < g_Cfg.m_nPKProtectLevel || pTarget->GetLevel() < g_Cfg.m_nPKProtectLevel )
    { return false; }   // 小于PK保护等级

    if ( IsOpenStall() || pTarget->IsOpenStall() )
    { return false; }   // 摆摊中无法攻击

    if ( pTarget->GetProtectTime() > 0 )
    { return false; }   // 判断对方是否在保护时间内

    if ( pTarget->_buffManager.IsInvincible() )
    { return false; }   // 无敌状态不能攻击

    if ( GetMapID() != pTarget->GetMapID() )
    { return false; }   // 不在同一地图

	//同一队伍无法PK
	GameTeam * pTeam = theGameTeamManager.GetTeam(pTarget->GetTeamID());
	if(pTeam && GetTeamID() == pTarget->GetTeamID())
	{
		return false;
	}

    //判断是否是pk地图
    MapConfig::MapData* pTargetMapData = pTarget->GetMapData();
    if ( pTargetMapData == NULL )
    { return false; }

    // 游戏没有开PK模式
    if( !g_Cfg.bPKOpen /*|| IsInPKDisableZone() || pTarget->IsInPKDisableZone() */)
    { return false; }    

    //地图PK模式
    int nMapPKMode  = pTargetMapData->CanPk ;
    //自己的PK模式

	// 不再是检查当前地图能否PK, 精确到刷怪区域(如果当前Zone的PK模式是有效的)
    GameStage *pStage = theGameWorld.GetStageById( pTarget->GetMapID() );
    if ( pStage == NULL )
    { return false; }

    GameZone *pZone =  pStage->GetZone( pTarget->GetCurZoneID() );
	if ( pZone != NULL && pZone->GetZonePKMode() != MapConfig::MapData::EPKM_None_PK )
    {
		// 区域PK模式大于地图PK模式
		nMapPKMode = pZone->GetZonePKMode();
	}
	//新加军团PK模式 需要添加判断
	//if(IsInOneGuild(pTarget) && GetPKMode() == PKMode_Guild) //如果我处于军团模式 且和目标同一军团
    switch ( nMapPKMode )
    {
    case MapConfig::MapData::EPKM_UnAllow_PK:
        { return false; }
        break;
    case MapConfig::MapData::EPKM_Critical_PK:
        {
            // 判断 自己 和 被攻击者的队伍 ( 最低保护级别  同组的一定不能打 )
            if ( GetTeamID() != TeamDefine::NoneSessionID && pTarget->GetTeamID() != TeamDefine::NoneSessionID )
            {
                if ( GetTeamID() == pTarget->GetTeamID() )
                { return false; }
            }

            if ( GetPKMode() != PKMode_Critical )
            { return false; }
        }
        break;
    case MapConfig::MapData::EPKM_Allow_PK:
        {
            // 判断 自己 和 被攻击者的队伍 ( 最低保护级别  同组的一定不能打 )
            if ( GetTeamID() != TeamDefine::NoneSessionID && pTarget->GetTeamID() != TeamDefine::NoneSessionID )
            {
                if ( GetTeamID() == pTarget->GetTeamID() )
                { return false; }
            }

            // 判断自己的模式
            switch ( GetPKMode() )   
            {
            case PKMode_Normal:     // 普通模式玩家遇见狂暴模式玩家可以进行攻击
                {
                    if (pTarget->GetPKMode() != PKMode_Critical)
                    { return false; }
                }
                break;
			case PKMode_Guild:
				{
					if(IsInOneGuild(pTarget))
						return false;
				}
				break;
            case PKMode_Fight:      // 对于开启PK模式的玩家和狂暴状态的玩家都可以进行攻击
                {
                     /*if (pTarget->GetPKMode() == PKMode_Normal)
                    { return false; }*/
					return true;
                }
                break;
			case PKMode_AttackFight:
				{
					return true;
				}
				break;
			case PKMode_AttackGuild:
				{
					if(IsInOneGuild(pTarget))
						return false;
				}
				break;
            case PKMode_Critical:   // 狂暴模式
                { return true; }
                break;
            }
        }
        break;
    case MapConfig::MapData::EPKM_Normal_PK:
        {
            // 判断 自己 和 被攻击者的队伍 ( 最低保护级别  同组的一定不能打 )
            if ( GetTeamID() != TeamDefine::NoneSessionID && pTarget->GetTeamID() != TeamDefine::NoneSessionID )
            {
                if ( GetTeamID() == pTarget->GetTeamID() )
                { return false; }
            }

            if ( GetCountry() != pTarget->GetCountry() )
            { return true; }    // 不是同一国家的可以攻击

            // 判断自己的模式
            switch ( GetPKMode() )   
            {
            case PKMode_Normal:     // 普通模式玩家遇见狂暴模式玩家可以进行攻击
                {
                    if (pTarget->GetPKMode() != PKMode_Critical)
                    { return false; }
                }
                break;
			case PKMode_Guild:
				{
					if(IsInOneGuild(pTarget))
						return false;
				}
				break;
            case PKMode_Fight:      // 对于开启PK模式的玩家和狂暴状态的玩家都可以进行攻击
                {
                   /* if (pTarget->GetPKMode() == PKMode_Normal)
                    { return false; }*/
					return true;
                }
                break;
			case PKMode_AttackFight:
				{
					return true;
				}
				break;
			case PKMode_AttackGuild:
				{
					if(IsInOneGuild(pTarget))
						return false;
				}
				break;
            case PKMode_Critical:   // 狂暴模式
                { return true; }
                break;
            }
        }
        break;
    case MapConfig::MapData::EPKM_Group_PK:         // 阵营战场
        { return GetFightCamp() != pTarget->GetFightCamp() ; }
        break;
    case MapConfig::MapData::EPKM_Guild_PK:         // 帮派战场
        {	
            if ( GetGuildID() == GuildDefine::InitID || pTarget->GetGuildID() == GuildDefine::InitID )
            { return false; }

            return GetGuildID() != pTarget->GetGuildID();
        }
        break;
	case MapConfig::MapData::EPKM_WorldBattle_PK:
		{
			//野外国家战场攻击模式
			uint32 CountryID = theGameGlobalDBManager.GetMapCountryID();
			if(CountryID == CountryDefine::Country_Init)
			{
				//所有国家都是友好的
				return false;
			}
			else
			{
				if(GetCountryId() == CountryID)
				{
					if(pTarget->GetCountryId() != CountryID)
						return true;
					else
						return false;
				}
				else
				{
					if(pTarget->GetCountryId() == CountryID)
						return true;
					else
						return false;
				}
			}
		}
		break;
    case MapConfig::MapData::EPKM_Free_PK:
        { return true; }
        break;
    case MapConfig::MapData::EPKM_Team_PK:          // 队伍战场
        { return GetTeamID() != pTarget->GetTeamID(); }
        break;
    case MapConfig::MapData::EPKM_Challenge_PK:     // 个人擂台
        { return true; }
        break;
    case MapConfig::MapData::EPKM_Contend_PK:
        {
            // 判断 自己 和 被攻击者的队伍 ( 最低保护级别  同组的一定不能打 )
            if ( GetTeamID() != TeamDefine::NoneSessionID && pTarget->GetTeamID() != TeamDefine::NoneSessionID )
            {
                if ( GetTeamID() == pTarget->GetTeamID() )
                { return false; }
            }
        }
        break;
    }

    return true;
}


void GamePlayer::AttackChar( BaseCharacter* pChar )
{
    if( pChar == NULL || pChar->GetID() == GetID() )
        return;

    if( pChar->IsPlayer() )
    {
        AttackPlayer( (GamePlayer*)pChar );
    }
    else if( pChar->IsMonster() )
    {
        MonsterBaseEx* pAIChar = static_cast< MonsterBaseEx*>( pChar );
        GamePlayer* pMaster = pAIChar->GetMasterPlayer();
        if ( pMaster != NULL )
        { AttackPlayer( pMaster, true ); }
    }
}
void GamePlayer::AttactOrAssistChar(BaseCharacter* pChar)
{
	if( pChar == NULL || pChar->GetID() == GetID() )
        return;
    if( pChar->IsPlayer() )
    {
        OnAttactOrAssistPlayer( (GamePlayer*)pChar);
    }
    else if( pChar->IsMonster() )
    {
        MonsterBaseEx* pAIChar = static_cast< MonsterBaseEx*>( pChar );
        GamePlayer* pMaster = pAIChar->GetMasterPlayer();
        if ( pMaster != NULL )
        { OnAttactOrAssistPlayer( pMaster);}
    }
}
void GamePlayer::AttackPlayer ( GamePlayer* pTarget, bool bSummonPet /*= false */)
{
    //if ( !IsCanAttackPlayer(pTarget) )
    //{ return; }
	//当玩家对指定玩家发动攻击的时候
	//OnAttactOrAssistPlayer(pTarget);
}

void GamePlayer::KillChar( BaseCharacter* pChar )
{
    if ( pChar == NULL || !pChar->IsPlayer() )
    { return; }

    GamePlayer* pPlayer = static_cast< GamePlayer* >( pChar ); 
    KillPlayer( pPlayer );
}

void GamePlayer::KillPlayer( GamePlayer* pTarget ) 
{
    if ( this == NULL || pTarget == NULL )
    { return; }

	//theGameWantedManager.OnPlayerDead(pTarget->GetDBCharacterID(),GetDBCharacterID());

    if (GetCountry() != pTarget->GetCountry())
    {// 不同国家的人增加荣誉值
		//判断是否在战场里面
		pTarget->OnPkDead();
		gCharInfoServer.otherdata.AddKIllPlayer(pTarget->GetDBCharacterID());
		if(!IsInBattleMap())
		{
			bool IsGetHonour = (!GetBuffManager() || GetBuffManager()->GetIsCanGetHonour()) && (!pTarget->GetBuffManager() || pTarget->GetBuffManager()->GetIsCanBeGetHonour());
			if(/*m_KillPlayerMap.OnKillPlayer(this,pTarget) &&*/ IsGetHonour && gCharInfoServer.otherdata.GetKillSum(pTarget->GetDBCharacterID()) <= g_Cfg.OncePlayerKillSum )
			{
				_ProcessHonour ( pTarget );	
			}

			//给军团添加使命点 判断使命点每天最大的上限
			uint16 KillSum = gCharInfoServer.otherdata.GetAllKillSum();
			if(KillSum * g_Cfg.KillPlayerMission < g_Cfg.MaxMissionSum)	
			{
				OperateGuildMission( GuildDefine::OperateAdd,min(g_Cfg.KillPlayerMission,g_Cfg.MaxMissionSum - KillSum * g_Cfg.KillPlayerMission));
			}
		}
		
		OnAddKillPlayerSum(pTarget);//计算杀人数

		TriggerSpecialQuest(ESTT_KillPlayer);
		switch (pTarget->GetCountry())
		{
		case CountryDefine::Country_LouLan:
			TriggerSpecialQuest(ESTT_KillWei);
			break;
		case CountryDefine::Country_KunLun:
			TriggerSpecialQuest(ESTT_KillShu);
			break;
		case CountryDefine::Country_DunHuang:
			TriggerSpecialQuest(ESTT_KillWu);
			break;
		}
		//玩家杀死敌对阵营的玩家 我们调用脚本处理
		GetScriptMgr()->StartupVM( ST_CHAR_KILLCHAR, 0, this );//杀死敌对阵营的玩家

    }
    else
    {// 同一个国家的人刷新PK值
        _ProcessPKValue( pTarget );
    }
}

void GamePlayer::_ProcessHonour ( GamePlayer* pTarget )
{
    if ( this == NULL || pTarget == NULL )
    { return; }

    if (GetCountry() == pTarget->GetCountry())
    { return; }

    MapConfig::MapData* pMapData = GetMapData();
    if ( pMapData == NULL )
    { return; }

    if ( RecordTime::CheckRecordTime( GetHonourRecordTime() ) )
    {
        ClearHonourRecord();
        RecordTime::SaveRecordTime( gCharInfoServer.otherdata.nRecordHonourTime );
    }

    if (GetHonourRecord() > GetHonourTopLimit())
    {
        MsgAckResult msg;
        msg.result = ER_HonourTopLimit;
        GettheServer().SendMsgToSingle(&msg, this);
        return;
    }

    int16 nHonour = 0;
	if(GetLevel() - pTarget->GetLevel() >= g_Cfg.LevelLimit)
	{
		nHonour = 0;
	}
	else if (pMapData->CountryID == GetCountry())
    { 
		//nHonour = PKHonour_SelfCountry;
		nHonour = g_Cfg.CountryKillPlayerHonour;
	}
	else
	{
		nHonour = g_Cfg.KillPlayerHonour;
	}
    
    /*else
    { nHonour = PKHonour_ForeignCountry; }*/

    // 玩家的组队情况
    GameTeam* pTeam = theGameTeamManager.GetTeam( GetTeamID() );
    if ( pTeam == NULL )
    {
		/*
		 *	Author 2012-11-28 zhuxincong
		 *	DESC: 策划需求
		 同级以及10级等级差内PK 获得15点
		 高于自己10级获得20点
		 高于自己20级获得30点
		 低于自己10级获得5点
		 低于自己20级无荣誉

		 */
		/*if (GetLevel() >= pTarget->GetLevel())
		{
			if (GetLevel() - pTarget->GetLevel() <= 10)
			{
				//nHonour = PKHoniur15;
				nHonour = PKHoniur6;
			}
			else if (GetLevel() - pTarget->GetLevel() >=20)
			{
				nHonour = 0;
			}
			else if (GetLevel() - pTarget->GetLevel() >= 10)
			{
				nHonour = PKHoniur6;
			}
		}
		else
		{
			if (abs(GetLevel() - pTarget->GetLevel()) <= 10)
			{
				//nHonour = PKHoniur15;
				nHonour = PKHoniur6;
			}
			else if (abs(GetLevel() - pTarget->GetLevel()) >=20)
			{
				//nHonour = PKHonour_ForeignCountry;
				nHonour = PKHoniur6;
			}
			else if (abs(GetLevel() - pTarget->GetLevel()) >= 10)
			{
				//nHonour = PKHoniur20;
				nHonour = PKHoniur6;
			}
		}*/
		/*if(!pTarget->IsInNormalMap())
			nHonour = PKHoniur6;
		else if(GetLevel() - pTarget->GetLevel() >= 20)
			nHonour = 0;
		else
			nHonour = PKHoniur6;*/
		
        //if (GetLevel() - pTarget->GetLevel() < 20)
        //{
        OperateHonour( EOT_Add, nHonour, __FUNCTION__, __LINE__ ,ePlayerMoneySourceType_KillPerson);
        //}
		//触发7天乐
		//_sevenDayManager.TriggerSevenDaysVar( (int)SevenDaysConfig::TD_ThirdDay, nHonour );
    }
    else
    {
        //获得有效队员数量
        unsigned int nAreaCount = pTeam->GetTeamMemberCountInMap( pTarget->GetMapID(), pTarget->GetFloatX(), pTarget->GetFloatY() );
        if ( nAreaCount == 0 ) 
        { nAreaCount = 1;}

        for( int i = 0; i < pTeam->TeamMemberCount(); ++i )
        {
            GamePlayer* pPlayer = pTeam->GetMemberPlayer( pTeam->GetMemberIDByIndex( i ) );
            if ( pPlayer == NULL || pPlayer->IsDead() ) 
            { continue; }

            if( !pPlayer->IsPlayer() || !pPlayer->IsInMapArea(pTarget->GetMapID(), pTarget->GetFloatX(), pTarget->GetFloatY(),g_Cfg.TeamHonourDis /*TEAM_EXP_DIS*/) )
            { continue; }

			/*if (pPlayer->GetLevel() >= pTarget->GetLevel())
			{
				if (pPlayer->GetLevel() - pTarget->GetLevel() <= 10)
				{
					nHonour = PKHoniur6;
					//nHonour = PKHoniur15;
				}
				else if (pPlayer->GetLevel() - pTarget->GetLevel() >=20)
				{
					nHonour = 0;
				}
				else if (pPlayer->GetLevel() - pTarget->GetLevel() >= 10)
				{
					nHonour = PKHoniur6;
				}
			}
			else
			{
				if (abs(pPlayer->GetLevel() - pTarget->GetLevel()) <= 10)
				{
					nHonour = PKHoniur6;
					//nHonour = PKHoniur15;
				}
				else if (abs(pPlayer->GetLevel() - pTarget->GetLevel()) >=20)
				{
					nHonour = PKHoniur6;
					//nHonour = PKHonour_ForeignCountry;
				}
				else if (abs(pPlayer->GetLevel() - pTarget->GetLevel()) >= 10)
				{
					nHonour = PKHoniur6;
					//nHonour = PKHoniur20;
				}
			}*/
			/*if(!pTarget->IsInNormalMap())
				nHonour = PKHoniur6;
			else if(GetLevel() - pTarget->GetLevel() >= 20)
				nHonour = 0;
			else
				nHonour = PKHoniur6;*/
			int16 nAvgHonour = nHonour;
			if(pPlayer == this)
				nAvgHonour = nHonour - g_Cfg.TeamDelHonour;
			else
				nAvgHonour = g_Cfg.TeamOtherPlayerHonour;			
			pPlayer->OperateHonour( EOT_Add, nAvgHonour, __FUNCTION__, __LINE__ ,ePlayerMoneySourceType_KillPerson);

			//触发7天乐
			//pPlayer->_sevenDayManager.TriggerSevenDaysVar( (int)SevenDaysConfig::TD_ThirdDay, nAvgHonour );

            /*if (pPlayer->GetLevel() - pTarget->GetLevel() < 20 )
            {
                pPlayer->OperateHonour( EOT_Add, nAvgHonour, __FUNCTION__, __LINE__ );
            }*/
        }
    }

}

void GamePlayer::_ProcessPKValue( GamePlayer* pTarget )
{
    if ( this == NULL || pTarget == NULL )
    { return; }

    if (GetCountry() != pTarget->GetCountry())
    { return; }

    // 比武切磋
    if( theDuelHandler()->IsDuelFight( GetID(), pTarget->GetID() ) )
    { return; }

    // 判断是否是pk地图
    MapConfig::MapData* pTargetMapData = GetMapData();
    if ( pTargetMapData == NULL )
    { return; }

    switch ( pTargetMapData->CanPk )
    {
    case MapConfig::MapData::EPKM_UnAllow_PK:
    case MapConfig::MapData::EPKM_Critical_PK:
    case MapConfig::MapData::EPKM_Allow_PK:
    case MapConfig::MapData::EPKM_Normal_PK:
        {
            if ( pTarget->GetProtectTime() > 0 )
            { return; }     // 保护时间内不能算PK值

            if ( pTarget->GetPKMode() == PKMode_Critical || pTarget->GetPKValue() >= thePKConfig.GetEnterCriticalPK()/*0*/ )
            { return; }     // 任何玩家杀死狂暴模式玩家都不改变PK值 

            //同是PK模式不改变PK值
            if (/* (GetPKMode() == PKMode_Fight || GetPKMode() == PKMode_Guild ) && */(pTarget->GetPKMode() == PKMode_Fight || pTarget->GetPKMode() == PKMode_Guild))
            { return; } 
	
			if(pTarget->GetPKMode() == PKMode_AttackFight || pTarget->GetPKMode() == PKMode_AttackGuild)//特殊模式下被杀不计算PK值
				return;
			//拥有特殊权利的玩家杀人不加Pk值
			GameCountry * pCountry = theGameCountryManager.GetCountry(GetCountryId());
			if(pCountry && pCountry->IsHaveRight(CountryDefine::Right_PK,GetDBCharacterID()))
				return;
            //加PK值
            SetPKValue( /*PKKillValue*/thePKConfig.GetPKKillValue(), PKValueOp_Add, BV_SendMessage );
            ProcessPKPunish();
        }
        break;
    default:
        break;
    }
}

bool GamePlayer::IsEffectKill( unsigned int dwPlayerDBID )
{
    if ( dwPlayerDBID == InvalidLogicNumber )
    { return false; }

    return true;
}

void GamePlayer::EnterCriticalMode()
{
    m_gtUpdateCriticalModeTimer.StartTimer( HQ_TimeGetTime(), PKCriticalTime );
}

void GamePlayer::TellClientPKValue( bool bSendToView /* = true */ )
{      
    if ( this == NULL )
    { return; }

    MsgPKStateChange change;
    change.shCharID       = GetID();
    change.nPKMode        = GetPKMode();
    change.nPKValue       = GetPKValue();

    if ( bSendToView )
    {
        GettheServer().SendMsgToView( &change, GetID(), false );
    }
    else
    {
        GettheServer().SendMsgToSingle( &change, this );
    }
}

void GamePlayer::PKProcessRun( unsigned int dwCostTime )
{
    //更新PK值
	if ( GetPKValue() >= 0 /*thePKConfig.GetEnterCriticalPK()*/)
    {
        if ( GetPKMode() != PKMode_Critical  && GetPKValue() >= thePKConfig.GetEnterCriticalPK())
        {
            SetPKMode( PKMode_Critical );
        }
		if(!m_gtUpdatePKValueTimer.IsStart() && gTransferRuntimeInfo.PkValueTimeLog == 0)
			gTransferRuntimeInfo.PkValueTimeLog = HQ_TimeGetTime();
		m_gtUpdatePKValueTimer.StartTimer(gTransferRuntimeInfo.PkValueTimeLog, /*PKValueUpdateTime*/thePKConfig.GetPKValueUpdateTime() );
        if ( m_gtUpdatePKValueTimer.DoneTimer() )
        {
            SetPKValue( 1, PKValueOp_Reduce );
			if ( GetPKValue() >=0/* thePKConfig.GetEnterCriticalPK()*//*0*/ )
			{
				gTransferRuntimeInfo.PkValueTimeLog = HQ_TimeGetTime();
				m_gtUpdatePKValueTimer.StartTimer(gTransferRuntimeInfo.PkValueTimeLog, /*PKValueUpdateTime*/thePKConfig.GetPKValueUpdateTime() );
			}
			else
				gTransferRuntimeInfo.PkValueTimeLog = 0;
        }
    }

    //更新狂暴状态
    if ( GetPKMode() == PKMode_Critical )
    {
        if ( m_gtUpdateCriticalModeTimer.DoneTimer() )
        {
            if ( GetPKValue() < /*0*/ thePKConfig.GetEnterCriticalPK())
            { SetPKMode( PKMode_Normal ); }
        }
    }

    m_gtUpdatePKModeTimer.DoneTimer();

    if ( GetPKValue() < 0 )
    { SetPKValue( 0 , PKValueOp_Set ); }

	m_KillPlayerMap.Update();//更新玩家的杀人列表记录
	OnUpdateClearKillPlayerWeekSum();//更新每周杀人数量
	OnPlayerLeaveAttack();
	OnLevelAttackMode();//离开特殊模式
}

void GamePlayer::ProcessPKPunish()
{
	//当玩家的PK值大于配置的进入监狱的PK值的时候 我们让玩家进入监狱 
	//当PK值大于进入监狱的值的时候 让用户名称显示红色的名称

	if(GetMapData() &&  GetMapData()->IsEctypeMap())
		return;
    if ( GetPKValue() < /*PKHellPunishValue*/thePKConfig.GetEnterJianYu() )
    { return; }

    const CountryConfig::SpecialMapSetting* pPrisonMap = theCountryConfig.GetPrisonMapSetting( GetCountry() );
    if( pPrisonMap == NULL )
    { return; }

    // 3秒才飞走
    SetWaitChangeStage( GamePlayer::LeaveStage, pPrisonMap->GetMapID(), pPrisonMap->GetPosX(), pPrisonMap->GetPosY(), pPrisonMap->GetDir(),3, false );

	//发送公告
	char Info[256];
	sprintf_s(Info,127,theXmlString.GetString(thePKConfig.GetCommonID()),GetCharInfo().baseinfo.aptotic.szCharacterName);
	//将这个字符串发送到全服务器
	MsgChat xChat( MsgChat::CHAT_TYPE_BULL );
	xChat.SetString( Info );
	GettheServer().SendMsgToWorld( &xChat, true );  
}

int GamePlayer::GetHonourTopLimit()
{
	return g_Cfg.MaxHonour;
    //return 0;// GetLevel() * 10 + _buffManager.GetAddHonourLimit();
}
bool GamePlayer::IsInOneGuild(GamePlayer* pTarget)
{
	if(!pTarget) return false;
	if ( GetGuildID() == GuildDefine::InitID || pTarget->GetGuildID() == GuildDefine::InitID )
		return false;
    return GetGuildID() == pTarget->GetGuildID();
}
void GamePlayer::OnAddKillPlayerSum(GamePlayer* pTarget)
{
	if(!pTarget) return;
	if(GetCountryId() == pTarget->GetCountryId()) return;//同一国家不计算
	//判断地图 只有野外才计算
	if(!pTarget->IsInNormalMap())
		return;
	++gCharInfoServer.baseinfo.liveinfo.dwKillPlayerSum;//总杀人数
	++gCharInfoServer.baseinfo.liveinfo.dwKillPlayerWeekSum;//本周总杀人数
	//RecordTime::SaveRecordTime( gCharInfoServer.otherdata.nRecordKillPlayerTime );//设置好最后杀人的时间
	time_t now;
	time(&now);
	
	gCharInfoServer.otherdata.nRecordKillPlayerTime = now;

	
	MsgKillPlayerNumAck msg;
	msg.nAllKillNum = gCharInfoServer.baseinfo.liveinfo.dwKillPlayerSum;
	msg.nWeekKillNum = gCharInfoServer.baseinfo.liveinfo.dwKillPlayerWeekSum;
	//发送命令给玩家客户端
	SendMessageToClient(&msg);
	//当总杀人数达到
	if(gCharInfoServer.baseinfo.liveinfo.dwKillPlayerSum >=	10000)
	{
		//成就 万夫莫敌
	}	
	else if(gCharInfoServer.baseinfo.liveinfo.dwKillPlayerSum >= 1000)
	{
		//成就 一骑当千
	}
	else if(gCharInfoServer.baseinfo.liveinfo.dwKillPlayerSum >= 100)
	{
		//成就 百人斩
	}
}
void GamePlayer::OnUpdateClearKillPlayerWeekSum()
{
	//判断当前时间为周6 0点 就清空 本周杀人数
	time_t now;		
	struct tm *fmt;	
	time(&now);	
	fmt = localtime(&now);	
	if(fmt->tm_wday== 0 && fmt->tm_hour == 0 && fmt->tm_min == 0 && fmt->tm_sec ==0)
	{
		gCharInfoServer.baseinfo.liveinfo.dwKillPlayerWeekSum = 0;
		//发生命令
		MsgKillPlayerNumAck msg;
		msg.nAllKillNum = gCharInfoServer.baseinfo.liveinfo.dwKillPlayerSum;
		msg.nWeekKillNum = 0;
		SendMessageToClient(&msg);
	}
}
void GamePlayer::OnCheckKillPlayerSum()
{
	//检查玩家上次下线的时间 
	//获取上次检查的时间
	time_t logtime =gCharInfoServer.otherdata.nRecordKillPlayerTime;//获取玩家最后杀人的时间
	//判断当前
	time_t nowtime;
	time(&nowtime);
	
	double SpanTime = difftime(nowtime,logtime);

	struct tm sysLogTime(*localtime(&logtime));	

	struct tm sysNowTime(*localtime(&nowtime));	

	bool states = false;
	if(7*24*60*60 <= SpanTime)
	{
		//差距时间超过一个星期
		states = true;
	}
	else if(sysLogTime.tm_wday == 0 && sysLogTime.tm_hour == 0 && sysLogTime.tm_min ==0 && sysLogTime.tm_sec ==0)
	{
		states = false;
	}
	else if(sysNowTime.tm_mday == sysLogTime.tm_mday && sysNowTime.tm_mon == sysLogTime.tm_mon && sysNowTime.tm_year == sysLogTime.tm_year)
	{
		//同一天
		states = false;
	}
	else
	{
		//不是同一天 且差距小于一个星期
		if(sysNowTime.tm_wday > sysLogTime.tm_wday)
			states = false;
		else
			states = true;
	}
	if(states)
	{
		gCharInfoServer.baseinfo.liveinfo.dwKillPlayerWeekSum = 0;
	}
}
void GamePlayer::OnPkDead()
{
	m_KillPlayerMap.OnDead();
}
bool GamePlayer::IsInNormalMap()
{
	//判断指定玩家是否在普通地图里面
	MapConfig::MapData* pTargetMapData = GetMapData();
	if(!pTargetMapData) return false;
	if(pTargetMapData->IsEctypeMap())
		return false;
	return true;
}
void GamePlayer::OnPlayerLeaveAttack()
{
	//当玩家离开战斗状态的时候
	if(!HaveFighteFlag(eFighting) && (GetPKMode() == PKMode_AttackFight || GetPKMode() == PKMode_AttackGuild) && !m_AttertUpdateTime.IsStart())
	{
		//启动20秒的计时器 20秒后设置玩家离开模式
		m_AttertUpdateTime.StartTimer( HQ_TimeGetTime(), MaxLevelAttack );
	}
}
void GamePlayer::OnLevelAttackMode()
{
	//让玩家离开模式
	if(m_AttertUpdateTime.IsStart() && m_AttertUpdateTime.DoneTimer())
	{
		m_IsUpdateLevelPKAttMode = true;
 		if(GetPKMode() == PKMode_AttackFight )
			SetPKMode(PKMode_Fight,true);
		else if(GetPKMode() == PKMode_AttackGuild)
			SetPKMode(PKMode_Guild,true);	
		m_AttertUpdateTime.StopTimer();
		m_IsUpdateLevelPKAttMode = false;
	}
}
void GamePlayer::OnAttactOrAssistPlayer(GamePlayer* pPlayer)
{
	if(!pPlayer ||  GetPKMode() == PKMode_Critical) return;
	if (GetCountry() != pPlayer->GetCountry()) return;//不同国家无所谓的特殊模式
	if( theDuelHandler()->IsDuelFight( GetID(), pPlayer->GetID() ) ) // 防止在绝斗后变成杀戮模式 lrt
		return;

	if(pPlayer->GetPKMode() == PKMode_AttackFight || pPlayer->GetPKMode() == PKMode_AttackGuild)
	{
		//任何攻击或者辅助 粉名字的玩家 自身会变为粉色
		if(GetPKMode() == PKMode_Fight)
		{
			if(SetPKMode(PKMode_AttackFight,true) && m_AttertUpdateTime.CheckStart())
				m_AttertUpdateTime.StopTimer();
		}
		else if(GetPKMode() == PKMode_Guild)
		{
			if(SetPKMode(PKMode_AttackGuild,true) && m_AttertUpdateTime.CheckStart())
				m_AttertUpdateTime.StopTimer();
		}
		else if(GetPKMode() == PKMode_AttackGuild || GetPKMode() == PKMode_AttackFight)
		{
			//刷新持续时间
			if(m_AttertUpdateTime.CheckStart())
				m_AttertUpdateTime.StopTimer();
		}
		else 
		{
			if(SetPKMode(PKMode_AttackFight,true) && m_AttertUpdateTime.CheckStart())
				m_AttertUpdateTime.StopTimer();
		}
		return;
	}
	else if(CheckCanAttackPlayer(pPlayer))
	{
		//战场里不处理
		//判断是否是pk地图
		MapConfig::MapData* pTargetMapData = pPlayer->GetMapData();
		if ( pTargetMapData != NULL )
		{
			int nMapPKMode  = pTargetMapData->CanPk ;
			GameStage *pStage = theGameWorld.GetStageById( pPlayer->GetMapID() );
			if(pStage)
			{
				GameZone *pZone =  pStage->GetZone( pPlayer->GetCurZoneID() );
				if ( pZone != NULL && pZone->GetZonePKMode() != MapConfig::MapData::EPKM_None_PK )
					nMapPKMode = pZone->GetZonePKMode();
			}
			if(MapConfig::MapData::EPKM_Guild_PK == nMapPKMode || nMapPKMode == MapConfig::MapData::EPKM_WorldBattle_PK)
				return;
		}
		//如果攻击目标 目标为白色名字
		if(pPlayer->GetPKMode() == PKMode_Normal)
		{
			if(GetPKMode() == PKMode_Fight)
			{
				if(SetPKMode(PKMode_AttackFight,true) && m_AttertUpdateTime.CheckStart())
					m_AttertUpdateTime.StopTimer();
			}
			else if(GetPKMode() == PKMode_Guild)
			{
				if(SetPKMode(PKMode_AttackGuild,true) && m_AttertUpdateTime.CheckStart())
					m_AttertUpdateTime.StopTimer();
			}
			else if(GetPKMode() == PKMode_AttackGuild || GetPKMode() == PKMode_AttackFight)
			{
				//刷新持续时间
				if(m_AttertUpdateTime.CheckStart())
					m_AttertUpdateTime.StopTimer();
			}
			else 
			{
				if(SetPKMode(PKMode_AttackFight,true) && m_AttertUpdateTime.CheckStart())
					m_AttertUpdateTime.StopTimer();
			}
			return;
		}
	}
}