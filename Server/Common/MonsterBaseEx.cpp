#include "MonsterBaseEx.h"
#include "ShareData.h"
#include "GamePlayer.h"
#include "MonsterStatusConfig.h"
#include "ScriptMgr.h"
#include "GameWorld.h"
#include "RouteManager.h"
#include "DropItemManager.h"
#include "CampBattleControl.h"
#include "CampBattle.h"
#include "NpcFightEx.h"
#include "GameGuildGeneralBattleManager.h"
#include "GameBattleControl.h"
MonsterBaseEx::MonsterBaseEx() : AiCharacter()
{
    m_nProduceIndex    = -1;
    SetMonsterStatus( MonsterDefine::StatusNormal );
    m_nNextMosntrStatus = MonsterDefine::StatusNormal;
    SetForce( ForceDefine::NormalMonsterForce );
	m_dwLastBeLongTime = 0;
}

MonsterBaseEx::~MonsterBaseEx()
{
    // 释放lua资源
    ReleaseLuaScript();
}

void MonsterBaseEx::Initialize( ItemDefine::SMonster* pConfig, MonsterCreateData& xCreateData, GamePlayer* pPlayer )
{
	if(pConfig->stMonsterId == 100386||
		pConfig->stMonsterId == 100387||
		pConfig->stMonsterId == 100388)
	{
		int n =0;
		n++;
	}
    m_pMonsterConfig = pConfig;

    SetProduceIndex( xCreateData.GetMonsterIndex() ); 

    SetMapID( xCreateData.GetMapID() );
    SetFloatXF( xCreateData.GetPostionX() );
    SetFloatYF( xCreateData.GetPostionY() );
    //SetDir( 0 );
    //SetDirX( xCreateData.GetDirX() );
    //SetDirY( xCreateData.GetDirY() );
    SetDirectiron( xCreateData.GetDirection() );
    SetBornPoint( xCreateData.GetPostionX(), xCreateData.GetPostionY(), 0 );
    SetPassivity( !m_pMonsterConfig->nIsInitiative );

    const RECT& xMoveZone = xCreateData.GetCanMoveZone();
    if ( xMoveZone.left == 0 && xMoveZone.right == 0 )
    {
        RECT xMoveZone;
        xMoveZone.left   = FloatToTile( xCreateData.GetPostionX() ) - AiDefine::MonsterMoveRadius;
        xMoveZone.right  = FloatToTile( xCreateData.GetPostionX() ) + AiDefine::MonsterMoveRadius;
        xMoveZone.top    = FloatToTile( xCreateData.GetPostionY() ) - AiDefine::MonsterMoveRadius;
        xMoveZone.bottom = FloatToTile( xCreateData.GetPostionY() ) + AiDefine::MonsterMoveRadius;
        FIX_NORMAL_ZERO( xMoveZone.left );
        FIX_NORMAL_ZERO( xMoveZone.top  );
        xCreateData.SetCanMoveZone( xMoveZone );
    }

    SetCanMoveZone( xCreateData.GetCanMoveZone() );

    SetCharName( m_pMonsterConfig->GetName() );
    SetMonsterType( m_pMonsterConfig->stMonsterType );
    
    float fBodySize = m_pMonsterConfig->fBodyLengthSize;
    if ( xCreateData.GetBodySize() > 0.f )
    { fBodySize = xCreateData.GetBodySize(); }
    SetBodySize( fBodySize );

    SetLevel( m_pMonsterConfig->stLevel );
    SetHPMax( m_pMonsterConfig->nHPMax );
    SetMPMax( m_pMonsterConfig->stMPMax );

    GetCharFightAttr()->hpRestore    .base = m_pMonsterConfig->stHPRestore ;
    GetCharFightAttr()->mpRestore    .base = m_pMonsterConfig->stMPRestore ;
    GetCharFightAttr()->exact        .base = m_pMonsterConfig->stExact     ;
    GetCharFightAttr()->dodge        .base = m_pMonsterConfig->stDodge     ;
    GetCharFightAttr()->attackPhysics.base = m_pMonsterConfig->fPhysicAtt  ;
    GetCharFightAttr()->attackMagic  .base = m_pMonsterConfig->fMagicAtt   ;
    GetCharFightAttr()->defendPhysics.base = m_pMonsterConfig->fPhysicDef  ;
    GetCharFightAttr()->defendMagic  .base = m_pMonsterConfig->fMagicDef   ;
    GetCharFightAttr()->critical     .base = m_pMonsterConfig->critical    ;
    GetCharFightAttr()->tenacity     .base = m_pMonsterConfig->tenacity    ;
    GetCharFightAttr()->criticalIntensity   .base = m_pMonsterConfig->criticalIntensity ;
    GetCharFightAttr()->backStrike          .base = m_pMonsterConfig->backStrike        ;
    GetCharFightAttr()->backStrikeResist    .base = m_pMonsterConfig->backStrikeResist  ;
    GetCharFightAttr()->breakStrike         .base = m_pMonsterConfig->breakStrike       ;
    GetCharFightAttr()->stabStrike          .base = m_pMonsterConfig->stabStrike        ;
    GetCharFightAttr()->elementStrike       .base = m_pMonsterConfig->elementStrike     ;
    GetCharFightAttr()->toxinStrike         .base = m_pMonsterConfig->toxinStrike       ;
    GetCharFightAttr()->spiritStrike        .base = m_pMonsterConfig->spiritStrike      ;
    GetCharFightAttr()->breakResist         .base = m_pMonsterConfig->breakResist       ;
    GetCharFightAttr()->stabResist          .base = m_pMonsterConfig->stabResist        ;
    GetCharFightAttr()->elementResist       .base = m_pMonsterConfig->elementResist     ;
    GetCharFightAttr()->toxinResist         .base = m_pMonsterConfig->toxinResist       ;
    GetCharFightAttr()->spiritResist        .base = m_pMonsterConfig->spiritResist      ;
    GetCharFightAttr()->attackSpeed         .base = m_pMonsterConfig->stAttackRate      ;
    GetCharFightAttr()->moveSpeed           .base = m_pMonsterConfig->fMoveSpeed        ;

    // 移动速度
    if( m_pMonsterConfig->fIdleMoveSpeed > 1.5f )
    { GetCharFightAttr()->moveSpeed.base = 1.5f; }
    else
    { GetCharFightAttr()->moveSpeed.base = m_pMonsterConfig->fIdleMoveSpeed; }

    UpdateCharAllAttibute();

    SetHP( m_pMonsterConfig->nHPMax  );
    SetMP( m_pMonsterConfig->stMPMax );

    for ( int i = 0; i < ItemDefine::SMonster::MONSTER_SKILL_COUNT; ++i )
    {
        AiSkill xAiSkill;
        xAiSkill.SetID( m_pMonsterConfig->iSkillID[i] );
        xAiSkill.SetLevel( m_pMonsterConfig->stSkillLevel[i] );
        
        xAiSkill.SetUseRate( m_pMonsterConfig->stSkillRate[i] );
        m_nUseSkillTotalRate += xAiSkill.GetUseRate();
        
        ItemDefine::SItemSkill* pSkill = GettheItemDetail().GetSkillByID( xAiSkill.GetID(), xAiSkill.GetLevel() );
        if ( pSkill != NULL )
        {
            xAiSkill.SetCostHP( pSkill->ustCostHP + pSkill->ustCostHPPer * GetCharFightAttr()->hpMax.final + 1 );
            xAiSkill.SetCostMP( pSkill->ustCostMP + pSkill->ustCostMPPer * GetCharFightAttr()->mpMax.final );       
            xAiSkill.SetAttackDistance( pSkill->fRangeCanCast );       
            xAiSkill.SetColdDownTime( pSkill->dwSkillCoolDownTime );
        }

        AddAiSkill( i, xAiSkill );
    }

    if ( xCreateData.GetCountry() != CountryDefine::Country_Init )
    { SetCountry ( xCreateData.GetCountry() ); }
    
    if ( xCreateData.GetFightCamp() !=  CampDefine::NoneCamp )
    { SetFightCamp( xCreateData.GetFightCamp() ); }
    
    if ( xCreateData.GetForce() != ForceDefine::NoneForce )
    { SetForce ( xCreateData.GetForce() ); }
    
    SetThinkingTime( xCreateData.GetThinkingTime() );
    SetViewSight( GetIdleViewSight() );

    // 自动消失定时器
    if ( m_pMonsterConfig->bIsDisappear )
    { m_xTimer[ AiDefine::AiTimer_Disappear ].StartTimer( HQ_TimeGetTime(), m_pMonsterConfig->dwDisappearTime ); }

    // 初始化脚本
    const char* szScriptName = pConfig->GetDeadScript();
    if( szScriptName != NULL && szScriptName[ 0 ] != 0 )
    { m_nDeathScriptVMID = GetScriptMgr()->CreateVM( ST_MONSTER, szScriptName, GetMonsterID() );  }

    // 判断是否是特殊类型怪
    const MonsterStatusConfig::StatusData* pStatusData = theMonsterStatusConfig.GetStatusData( GetMonsterID() );
    if ( pStatusData != NULL )
    {
        // 设置初始类型状态
        SetMonsterStatus( pStatusData->GetInitStatus() );

        // 当前状态属性
        const MonsterStatusConfig::StatusSetting* pNowSetting = pStatusData->GetStatusSetting( GetMonsterStatus() );
        if ( pNowSetting == NULL )
        { return; }

        m_nNextMosntrStatus = pNowSetting->GetNextStatus();
        m_xTimer[ AiDefine::AiTimer_StatusChange ].StartTimer( HQ_TimeGetTime(), pNowSetting->GetSpaceTime() );
    }
    else
    {
        // 如果有出生动作, 设置定时器( 出生状态不能被攻击 )
        if ( m_pMonsterConfig->dwBornProtectTime != 0  )
        {
            SetMonsterStatus( MonsterDefine::StatusMonsterBorn );
            m_xTimer[ AiDefine::AiTimer_StatusChange ].StartTimer( HQ_TimeGetTime(), m_pMonsterConfig->dwBornProtectTime );
            m_nNextMosntrStatus = MonsterDefine::StatusNormal;
        }
    }

    // 路点信息
    InitRoute( xCreateData.GetMapID(), xCreateData.GetRouteID() );
    
    // 初始化Lua脚本信息
    InitLuaScript();

	// 初始化寻路
	InitFindParth( GetID(), pConfig->blIsFindParth, pConfig->blIsDynamicBlock );
}

void MonsterBaseEx::Run( uint32 nCostTime )
{
    // 处理怪物状态改变
    ProcessMonsterStatusChange();

    // 处理基类
    AiCharacter::Run( nCostTime );
}

// 获得脚本入口点
int MonsterBaseEx::GetMonsterStatusScriptEnter()
{
    const MonsterStatusConfig::StatusData* pStatusData = theMonsterStatusConfig.GetStatusData( GetMonsterID() );
    if ( pStatusData == NULL )
    { return AiDefine::MonsterDefaultScriptEnter; }

    const MonsterStatusConfig::StatusSetting* pNowSetting = pStatusData->GetStatusSetting( GetMonsterStatus() );
    if ( pNowSetting == NULL )
    { return AiDefine::MonsterDefaultScriptEnter; }

    return pNowSetting->GetScriptEnter();
}

void MonsterBaseEx::ProcessMonsterStatusChange( )
{
    if ( !m_xTimer[ AiDefine::AiTimer_StatusChange ].DoneTimer() )
    { return; }

    // 怪物状态改变
    SetMonsterStatus( m_nNextMosntrStatus );
    m_nNextMosntrStatus = MonsterDefine::StatusNormal;

    // 改变模型
    const MonsterStatusConfig::StatusData* pStatusData = theMonsterStatusConfig.GetStatusData( GetMonsterID() );
    if ( pStatusData != NULL )
    {
        const MonsterStatusConfig::StatusSetting* pChangeStatusSetting = pStatusData->GetStatusSetting( GetMonsterStatus() );
        if ( pChangeStatusSetting != NULL )
        {
            SetModelId( pChangeStatusSetting->GetModelID() );
        }
    }

    MsgMonsterTypeStatusChange xChange;
    xChange.nMonsterID  = GetID();
    xChange.nTypeStatus = GetMonsterStatus();
    GettheServer().SendMsgToView( &xChange, GetID(), true );
}

// nMonsterStatus != 0时, 直接改变到该状态
void MonsterBaseEx::ProcessMonsterStatusChange( int nMonsterStatus )
{
    const MonsterStatusConfig::StatusData* pStatusData = theMonsterStatusConfig.GetStatusData( GetMonsterID() );
    if ( pStatusData == NULL )
    { return; }

    // 当前状态属性
    const MonsterStatusConfig::StatusSetting* pNowSetting = pStatusData->GetStatusSetting( GetMonsterStatus() );
    if ( pNowSetting == NULL )
    { return; }

    m_xTimer[ AiDefine::AiTimer_StatusChange ].StartTimer( HQ_TimeGetTime(), pNowSetting->GetSpaceTime() );
    if ( nMonsterStatus == MonsterDefine::StatusNormal )
    { m_nNextMosntrStatus = pNowSetting->GetNextStatus(); }
    else
    { m_nNextMosntrStatus = nMonsterStatus; }
}

Msg* MonsterBaseEx::FirstSightOnMe( char* szMsgBuffer, unsigned int nBuffSize )
{
    BaseCharacter::FirstSightOnMe( szMsgBuffer, nBuffSize );

    MsgNPCEnterMySight* pEnter = reinterpret_cast< MsgNPCEnterMySight* >( szMsgBuffer );

    pEnter->stCharType      = Object_Monster;
    pEnter->stMonsterType   = GetMonsterType();
    pEnter->nSubMonsterType = GetObjType();         // 怪物详细类型
    pEnter->stId            = GetMonsterID();
    pEnter->nTypeStatus     = GetMonsterStatus();   // 怪物的状态类型
	pEnter->BelongID			= GetKiller()?GetKiller()->GetID():0;
    
    //if( IsSummonMonster() )
    //{
    //    pEnter->stMasterId = GetSummonMasterID();
    //    BaseCharacter* pMaster = theRunTimeData.GetCharacterByID( GetSummonMasterID() );
    //    if ( pMaster != NULL && pMaster->IsPlayer() )
    //    { strncpy_s( pEnter->szDisplayName, pMaster->GetCharName(), sizeof( pEnter->szDisplayName ) - 1); }
    //}

    return pEnter;
}

void MonsterBaseEx::OnDeath()
{
    // 死亡掉落
    ProcessDeathDromItem();

    // 阵营怪物死亡
    ProcessCampMonsterDeath();

	ProcessGameBattleMonsterDeath();

    AiCharacter::OnDeath();
}

void MonsterBaseEx::ProcessDeathDromItem()
{
    if ( m_pBelongKiller == NULL || !m_pBelongKiller->IsPlayer() )
    { return; }

    GetDropItemManager().MonsterDeath( this, m_pBelongKiller );
}


void MonsterBaseEx::ProcessDeathCallScript()
{
    if ( !CheckDeathCallScript() )
    { return; }

    GamePlayer* pKillerPlayer = static_cast< GamePlayer* >( m_pBelongKiller );
    GetScriptMgr()->StartupVM( ST_MONSTER, GetMonsterID(), pKillerPlayer, false, AiDefine::MonsterDeathScriptEnter, GetID() );
}
void MonsterBaseEx::ProcessGameBattleMonsterDeath()
{
	GameGuildGeneralBattleManager* pManager = static_cast<GameGuildGeneralBattleManager*>(theGameBattleControl.GetGameBattleManager(GameBattleDefine::GameBattle_Type_GuildGeneral));
	if(!pManager)
		return;
    unsigned int nPlayerID = 0;
    if (m_pBelongKiller && m_pBelongKiller->IsPlayer() )
    {
        GamePlayer* pPlayer = static_cast< GamePlayer* >( m_pBelongKiller );
        nPlayerID = pPlayer->GetDBCharacterID();
    }
	unsigned int OnlyMapID = GetMapID();
	if(m_pBelongKiller)
		pManager->KillGameBattleMonster( m_pBelongKiller->GetFightCamp(), nPlayerID, GetMonsterID(),OnlyMapID);
	else
	{
		if(GetFightCamp() == GameBattleDefine::GameBattle_Blue)
			pManager->KillGameBattleMonster( GameBattleDefine::GameBattle_Red, nPlayerID, GetMonsterID(),OnlyMapID);
		else
			pManager->KillGameBattleMonster( GameBattleDefine::GameBattle_Blue, nPlayerID, GetMonsterID(),OnlyMapID);
	}
}
void MonsterBaseEx::ProcessCampMonsterDeath()
{
    CampBattle* pCampBattle = theCampBattleControl.GetCampBattle( GetFightCamp(), GetMapID(),m_pMonsterConfig->nMonsterSide);
    if ( pCampBattle == NULL || pCampBattle->GetStatus() != CampDefine::StatusFight )
    { return; }

	unsigned int nPlayerID = 0;
    if (m_pBelongKiller && m_pBelongKiller->IsPlayer() )
    {
        GamePlayer* pPlayer = static_cast< GamePlayer* >( m_pBelongKiller );
        nPlayerID = pPlayer->GetDBCharacterID();
    }
	if(m_pBelongKiller)
		pCampBattle->KillCampBattleMonster( m_pBelongKiller->GetFightCamp(), nPlayerID, GetMonsterID());
	else
	{
		uint8 NowFight = GetFightCamp();
		if(NowFight == 0)
			return;
		//取相反的阵营
		uint8 OtherFight = 0;
		if(NowFight % 2 == 0)
			OtherFight = NowFight -1;
		else
			OtherFight = NowFight +1;
		pCampBattle->KillCampBattleMonster(OtherFight, nPlayerID, GetMonsterID());
	}
}

void MonsterBaseEx::ProcessDeathChangeStatus()
{
    switch ( GetMonsterStatus() )
    {
    case MonsterDefine::StatusMonster:
        {
            // 获得当前状态, 如果下一个状态是
            const MonsterStatusConfig::StatusData* pStatusData = theMonsterStatusConfig.GetStatusData( GetMonsterID() );
            if ( pStatusData != NULL )
            {
                const MonsterStatusConfig::StatusSetting* pNowSetting = pStatusData->GetStatusSetting( GetMonsterStatus() );
                if ( pNowSetting != NULL && pNowSetting->GetNextStatus() == MonsterDefine::StatusMonsterDeath )
                { 
                    // 确保怪物会清除, 防止策划忘记exit
                    m_xTimer[ AiDefine::AiTimer_Disappear ].StartTimer( HQ_TimeGetTime(), 1800000 );
                    return;
                }
            }
        }
        break;
    default:
        break;
    }

    AiCharacter::ProcessDeathChangeStatus();
}

uint8 MonsterBaseEx::CheckCanAttackResult( BaseCharacter* pTarget )
{
    uint8 nAttackResult = AiCharacter::CheckCanAttackResult( pTarget );
    if ( nAttackResult != CheckAttack::AttackUnknow )
    { return nAttackResult; }

    // 有主人的怪物, 并且不是自己的主人
    if ( pTarget->IsMonster() )
    {
        if ( !HaveMaster() && pTarget->HaveMaster() )
        { return CheckAttack::EnmityForce; }
    }

    return CheckAttack::AttackUnknow;
}

bool MonsterBaseEx::CheckCanBeAttack()
{
    if ( !CanAttackMonsterStatus() )
    { return false; }

    switch ( GetAiStatus() )
    {
    case AiDefine::ThinkingWaitRelive:
        return false;
        break;
    }

    return BaseCharacter::CheckCanBeAttack();
}

void MonsterBaseEx::ProcessFindAttackTarget()
{
    switch ( GetMonsterStatus() )
    {
    case MonsterDefine::StatusMoveNpc:
    case MonsterDefine::StatusUnMoveNpc:
    case MonsterDefine::StatusMonsterDeath:
    case MonsterDefine::StatusMonsterBorn:
        return;
        break;
    default:
        break;
    }

    AiCharacter::ProcessFindAttackTarget();
}

bool MonsterBaseEx::CheckAddViewEnmity( EnmityData& xEnmityData, BaseCharacter* pChar )
{
    if ( IsPassivity() )
    {
        // 如果不是自己的锁定目标,并且不是攻击目标, 则不需要保持仇恨
        if ( GetLockID() != pChar->GetID() && !IsAttackTarget( pChar->GetID() ) )
        { return false; }

        // 不再仇恨范围内
        if ( !CheckInBaseEnmityRange() )
        { return false; }
    }

    return AiCharacter::CheckAddViewEnmity( xEnmityData, pChar );
}

void MonsterBaseEx::ProcessEnterSightEnmity( BaseCharacter* pTarget )
{
    // 能攻击的话加入仇恨列表
    if ( !IsPassivity() )
    {
        // 敌对阵营, 能攻击的话加入仇恨列表
        if ( ForceDefine::CheckEnmityForce( GetForce(), pTarget->GetForce() ) || CheckCanAttackTarget( pTarget ) )
        {
			if (!pTarget->IsFightNpc())
				AddEnmity( pTarget->GetID(), 0, 0, GetEnmityRate() );
			else
			{
				NpcFightEx* pNpc = (NpcFightEx*)pTarget;
				if (pNpc)
				{
					if ( pNpc->GetFightType() != NpcFightEx::FT_Player )
						AddEnmity( pTarget->GetID(), 0, 0, GetEnmityRate() );
				}
			}
        }
    }
}

void MonsterBaseEx::OnEnterFightState()
{   
    // 怪物战斗寻路
    if ( m_pMonsterConfig != NULL && g_Cfg.bAIFindParth )
    { OnFindParthConfigChanged( m_pMonsterConfig->blIsFindParth, m_pMonsterConfig->blIsDynamicBlock ); }
    else
    { OnFindParthConfigChanged( false, false ); }

}

void MonsterBaseEx::OnOutFightState()
{
	// 脱离战斗,清除寻路
	_charFindParth.ReInitFindParth( false, false );
}
void MonsterBaseEx::WasKilled( BaseCharacter* pKiller )
{
	switch( GetStatus() )    
    {
    case CS_INTONATE:
    case CS_HOLDSKILL:
        CancelSkill();
        break;
    }

    UpdateMonsterBeLong(pKiller);//把最后补刀的单位传给它去更新

    OnDeath();
}
// 当有玩家进行攻击的时候调用 但是每次都调用效率太低了 
void MonsterBaseEx::UpdateMonsterBeLong( BaseCharacter* pKiller )
{
	if (HQ_TimeGetTime() - m_dwLastBeLongTime < AiDefine::MonsterUpdateBeLongTime && !pKiller)
	{
		return;
	}
	m_dwLastBeLongTime = HQ_TimeGetTime();

	// 长时间不输出的人清除他
	CheckClearAttackerScore();
	uint16 Type = m_pMonsterConfig ? m_pMonsterConfig->nDropType : ItemDefine::SMDT_First;
	BaseCharacter* pRealKiller = NULL;
	switch(Type)
	{
	case ItemDefine::SMDT_DPS:
		{
			//最大伤害
			pRealKiller = theRunTimeData.GetCharacterByID( GetBestAttacker() );
		}
		break;
	case ItemDefine::SMDT_First:
	default:
		{
			pRealKiller = theRunTimeData.GetCharacterByID( GetFirstValidAttacker() );
		}
		break;
	}
	// 确实没有找到有效的killer者 就用最后击杀的那个人
	if(!pRealKiller)
	{
		OnSetMonsterBelong(pKiller);
	}
	else if(m_pBelongKiller != pRealKiller)
	{
		OnSetMonsterBelong(pRealKiller);
	}
}