#include "NpcFightEx.h"
#include "CampBattleDefine.h"

NpcFightEx::NpcFightEx()
{
    SetObjType( Object_NpcFight );
    SetForce( ForceDefine::FightNpcForce );
}

void NpcFightEx::Initialize( NpcInfo::Npc* pConfig, GameStage* pStage, bool bAsyn )
{
    NpcBaseEx::Initialize( pConfig, pStage ,bAsyn);

    NpcInfo::FightInfo& xFightData = m_pNpcInfo->fightData[0];

    SetHPMax( xFightData.hpMax );
    SetMPMax( xFightData.mpMax );

    GetCharFightAttr()->hpRestore    .base = xFightData.hpRestore ;
    GetCharFightAttr()->mpRestore    .base = xFightData.mpRestore ;
    GetCharFightAttr()->exact        .base = xFightData.exact     ;
    GetCharFightAttr()->dodge        .base = xFightData.dodge     ;
    GetCharFightAttr()->attackPhysics.base = xFightData.attackPhysics  ;
    GetCharFightAttr()->attackMagic  .base = xFightData.attackMagic    ;
    GetCharFightAttr()->defendPhysics.base = xFightData.defendPhysics  ;
    GetCharFightAttr()->defendMagic  .base = xFightData.defendMagic    ;
    GetCharFightAttr()->critical     .base = xFightData.critical    ;
    GetCharFightAttr()->tenacity     .base = xFightData.tenacity    ;
    GetCharFightAttr()->criticalIntensity  .base = xFightData.criticalIntensity ;
    GetCharFightAttr()->attackSpeed  .base = xFightData.attackSpeed;
    GetCharFightAttr()->moveSpeed.    base = xFightData.moveSpeed  ;

	GetCharFightAttr()->backStrike	 .base = xFightData.backStrike ;
	GetCharFightAttr()->backStrikeResist.base = xFightData.backStrikeResist;
	GetCharFightAttr()->breakStrike	 .base = xFightData.breakStrike;
	GetCharFightAttr()->stabStrike	 .base = xFightData.stabStrike;
	GetCharFightAttr()->elementStrike.base = xFightData.elementStrike;
	GetCharFightAttr()->toxinStrike	 .base = xFightData.toxinStrike;
	GetCharFightAttr()->spiritStrike .base = xFightData.spiritStrike;
	GetCharFightAttr()->breakResist  .base = xFightData.breakResist;
	GetCharFightAttr()->stabResist	 .base = xFightData.stabResist;
	GetCharFightAttr()->elementResist.base = xFightData.elementResist;
	GetCharFightAttr()->toxinResist	 .base = xFightData.toxinResist;
	GetCharFightAttr()->spiritResist .base = xFightData.spiritResist;

    SetBornPoint( pConfig->x/*GetFloatX()*/, pConfig->y/*GetFloatY()*/, /*GetFloatZ()*/0 );
    SetBodySize( xFightData.bodyLength ); // 设置身体大小
    SetViewSight( xFightData.view );
    SetLevel( xFightData.level );

    if ( !xFightData.deadScript.empty() )
    { m_nDeathScriptVMID = GetScriptMgr()->CreateVM( ST_NPC_DEAD, xFightData.deadScript.c_str(), GetNpcID() ); }

    // 移动速度
    if( xFightData.idleMoveSpeed > 1.5f )
    { GetCharFightAttr()->moveSpeed.base = 1.5f; }
    else
    { GetCharFightAttr()->moveSpeed.base = xFightData.idleMoveSpeed; }

    SetLastMovingSpeed( GetMoveSpeed() );

    UpdateCharAllAttibute();

    SetHP( xFightData.hpMax     );
    SetMP( xFightData.mpMax );

    for ( int i = 0; i < NpcInfo::FightInfo::ECD_SkillCount; ++i )
    {
        AiSkill xAiSkill;
        xAiSkill.SetID( xFightData.skills[i].skillId );
        xAiSkill.SetLevel( xFightData.skills[i].skillLevel );

        xAiSkill.SetUseRate( xFightData.skills[i].skillRate );
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

	if ( xFightData.fightCamp !=  CampDefine::NoneCamp )
	{ SetFightCamp( xFightData.fightCamp ); }

    InitRoute( GetMapID(), xFightData.routeId );
}

void NpcFightEx::ProcessRefreshEnmity( uint32 nCurrentTime )
{
    AiCharacter::ProcessRefreshEnmity( nCurrentTime );
}

void NpcFightEx::ProcessFindAttackTarget()
{
    AiCharacter::ProcessFindAttackTarget();
}

bool NpcFightEx::CheckCanBeAttack()
{
    return AiCharacter::CheckCanBeAttack();
}

uint8 NpcFightEx::CheckCanAttackResult( BaseCharacter* pTarget )
{
    return AiCharacter::CheckCanAttackResult( pTarget );
}

void NpcFightEx::ProcessEnterSightEnmity( BaseCharacter* pTarget )
{
    if ( CountryDefine::CheckEnmityCountry( GetCountry(), pTarget->GetCountry() ) || 
         ForceDefine::CheckEnmityForce( GetForce(), pTarget->GetForce() ) || 
         CheckCanAttackTarget( pTarget ) )
    {
		if ( GetFightType() == FT_Player )
		{
			if (!pTarget->IsMonster())
				AddEnmity( pTarget->GetID(), 0 , 0 , GetEnmityRate());
		}
		else if ( GetFightType() == FT_Monster )
		{
			if ( !pTarget->IsPlayer() && CheckMonsterTpye( pTarget->GetMonsterType() ))
				AddEnmity( pTarget->GetID(), 0 , 0 , GetEnmityRate());
		}
		else
		{
			if ( CheckMonsterTpye( pTarget->GetMonsterType() ) )
				AddEnmity( pTarget->GetID(), 0 , 0 , GetEnmityRate());
		}
    }
}

bool NpcFightEx::CheckMonsterTpye(int type)
{
	switch (type)
	{
	case eMT_Trap:
	case eMT_Herb:
	case eMT_Mine:
	case eMT_Wood:
	case eMT_Treasure:
	case eMT_Building:
	case eMT_Collision:
		return false;
		break;
	}

	return true;
} 

//void NpcFightEx::OnDeath()
//{
//	AiCharacter::OnDeath();
//	ClearEnmity( true ); 
//}

bool NpcFightEx::CheckAddViewEnmity( EnmityData& xEnmityData, BaseCharacter* pChar )
{
	/*if (!CheckInMaxAttackRange( pChar->GetMapID(), pChar->GetFloatX(), pChar->GetFloatY(), 0 ))
		return false;*/

	if ( pChar->GetMapID() != GetMapID() )
		return false;
	if ( GetMaxAttackRange() != -1 )
	{
		if ( abs( m_xBornPoint.x - pChar->GetFloatX() ) > GetMaxAttackRange() || abs( m_xBornPoint.y - pChar->GetFloatY() ) > GetMaxAttackRange() || 
			abs( m_xBornPoint.z - 0 ) > GetMaxAttackRange() )
			return false;
	}
	
	return AiCharacter::CheckAddViewEnmity( xEnmityData, pChar );
}

//void NpcFightEx::OnDeath() //加上之后npc不会复活了。。
//{ 
//	// 清除战斗状态
//	if (_HAS_FLAG(m_dwFightFlag, eFighting))
//	{
//		_CLS_FLAG(m_dwFightFlag, eFighting);
//	}
//	 
//}