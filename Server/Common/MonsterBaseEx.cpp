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
    // �ͷ�lua��Դ
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

    // �ƶ��ٶ�
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

    // �Զ���ʧ��ʱ��
    if ( m_pMonsterConfig->bIsDisappear )
    { m_xTimer[ AiDefine::AiTimer_Disappear ].StartTimer( HQ_TimeGetTime(), m_pMonsterConfig->dwDisappearTime ); }

    // ��ʼ���ű�
    const char* szScriptName = pConfig->GetDeadScript();
    if( szScriptName != NULL && szScriptName[ 0 ] != 0 )
    { m_nDeathScriptVMID = GetScriptMgr()->CreateVM( ST_MONSTER, szScriptName, GetMonsterID() );  }

    // �ж��Ƿ����������͹�
    const MonsterStatusConfig::StatusData* pStatusData = theMonsterStatusConfig.GetStatusData( GetMonsterID() );
    if ( pStatusData != NULL )
    {
        // ���ó�ʼ����״̬
        SetMonsterStatus( pStatusData->GetInitStatus() );

        // ��ǰ״̬����
        const MonsterStatusConfig::StatusSetting* pNowSetting = pStatusData->GetStatusSetting( GetMonsterStatus() );
        if ( pNowSetting == NULL )
        { return; }

        m_nNextMosntrStatus = pNowSetting->GetNextStatus();
        m_xTimer[ AiDefine::AiTimer_StatusChange ].StartTimer( HQ_TimeGetTime(), pNowSetting->GetSpaceTime() );
    }
    else
    {
        // ����г�������, ���ö�ʱ��( ����״̬���ܱ����� )
        if ( m_pMonsterConfig->dwBornProtectTime != 0  )
        {
            SetMonsterStatus( MonsterDefine::StatusMonsterBorn );
            m_xTimer[ AiDefine::AiTimer_StatusChange ].StartTimer( HQ_TimeGetTime(), m_pMonsterConfig->dwBornProtectTime );
            m_nNextMosntrStatus = MonsterDefine::StatusNormal;
        }
    }

    // ·����Ϣ
    InitRoute( xCreateData.GetMapID(), xCreateData.GetRouteID() );
    
    // ��ʼ��Lua�ű���Ϣ
    InitLuaScript();

	// ��ʼ��Ѱ·
	InitFindParth( GetID(), pConfig->blIsFindParth, pConfig->blIsDynamicBlock );
}

void MonsterBaseEx::Run( uint32 nCostTime )
{
    // �������״̬�ı�
    ProcessMonsterStatusChange();

    // �������
    AiCharacter::Run( nCostTime );
}

// ��ýű���ڵ�
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

    // ����״̬�ı�
    SetMonsterStatus( m_nNextMosntrStatus );
    m_nNextMosntrStatus = MonsterDefine::StatusNormal;

    // �ı�ģ��
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

// nMonsterStatus != 0ʱ, ֱ�Ӹı䵽��״̬
void MonsterBaseEx::ProcessMonsterStatusChange( int nMonsterStatus )
{
    const MonsterStatusConfig::StatusData* pStatusData = theMonsterStatusConfig.GetStatusData( GetMonsterID() );
    if ( pStatusData == NULL )
    { return; }

    // ��ǰ״̬����
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
    pEnter->nSubMonsterType = GetObjType();         // ������ϸ����
    pEnter->stId            = GetMonsterID();
    pEnter->nTypeStatus     = GetMonsterStatus();   // �����״̬����
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
    // ��������
    ProcessDeathDromItem();

    // ��Ӫ��������
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
		//ȡ�෴����Ӫ
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
            // ��õ�ǰ״̬, �����һ��״̬��
            const MonsterStatusConfig::StatusData* pStatusData = theMonsterStatusConfig.GetStatusData( GetMonsterID() );
            if ( pStatusData != NULL )
            {
                const MonsterStatusConfig::StatusSetting* pNowSetting = pStatusData->GetStatusSetting( GetMonsterStatus() );
                if ( pNowSetting != NULL && pNowSetting->GetNextStatus() == MonsterDefine::StatusMonsterDeath )
                { 
                    // ȷ����������, ��ֹ�߻�����exit
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

    // �����˵Ĺ���, ���Ҳ����Լ�������
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
        // ��������Լ�������Ŀ��,���Ҳ��ǹ���Ŀ��, ����Ҫ���ֳ��
        if ( GetLockID() != pChar->GetID() && !IsAttackTarget( pChar->GetID() ) )
        { return false; }

        // ���ٳ�޷�Χ��
        if ( !CheckInBaseEnmityRange() )
        { return false; }
    }

    return AiCharacter::CheckAddViewEnmity( xEnmityData, pChar );
}

void MonsterBaseEx::ProcessEnterSightEnmity( BaseCharacter* pTarget )
{
    // �ܹ����Ļ��������б�
    if ( !IsPassivity() )
    {
        // �ж���Ӫ, �ܹ����Ļ��������б�
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
    // ����ս��Ѱ·
    if ( m_pMonsterConfig != NULL && g_Cfg.bAIFindParth )
    { OnFindParthConfigChanged( m_pMonsterConfig->blIsFindParth, m_pMonsterConfig->blIsDynamicBlock ); }
    else
    { OnFindParthConfigChanged( false, false ); }

}

void MonsterBaseEx::OnOutFightState()
{
	// ����ս��,���Ѱ·
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

    UpdateMonsterBeLong(pKiller);//����󲹵��ĵ�λ������ȥ����

    OnDeath();
}
// ������ҽ��й�����ʱ����� ����ÿ�ζ�����Ч��̫���� 
void MonsterBaseEx::UpdateMonsterBeLong( BaseCharacter* pKiller )
{
	if (HQ_TimeGetTime() - m_dwLastBeLongTime < AiDefine::MonsterUpdateBeLongTime && !pKiller)
	{
		return;
	}
	m_dwLastBeLongTime = HQ_TimeGetTime();

	// ��ʱ�䲻������������
	CheckClearAttackerScore();
	uint16 Type = m_pMonsterConfig ? m_pMonsterConfig->nDropType : ItemDefine::SMDT_First;
	BaseCharacter* pRealKiller = NULL;
	switch(Type)
	{
	case ItemDefine::SMDT_DPS:
		{
			//����˺�
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
	// ȷʵû���ҵ���Ч��killer�� ��������ɱ���Ǹ���
	if(!pRealKiller)
	{
		OnSetMonsterBelong(pKiller);
	}
	else if(m_pBelongKiller != pRealKiller)
	{
		OnSetMonsterBelong(pRealKiller);
	}
}