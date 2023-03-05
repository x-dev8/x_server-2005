#include "GamePlayer.h"
#include "MonsterBaseEx.h"
#include "ShareData.h"
#include "NpcFightEx.h"

void GamePlayer::ProcessRefreshEnmity( uint32 nCurrentTime )
{
    // 定时器
    if ( !m_xRefeshEnmityTimer.DoneTimer( nCurrentTime ) )
    { return; }

    // 别人对我的仇恨, 衰减
    for ( TargetEnmityMapIter iter = m_mapTargetEnmity.begin(); iter != m_mapTargetEnmity.end(); ++iter )
    {
        // 仇恨衰减
        BaseCharacter* pChar = theRunTimeData.GetCharacterByID( iter->first );
        if ( pChar == NULL )
        { continue; }

        // 仇恨衰减
        iter->second.DecEnmity( iter->second.GetReduction() );
    }

    // 判断我打过的人, 如果对方没有我的仇恨了, 则删除之
    for ( AttackTargetSetIter iter = m_setAttackTarget.begin(); iter != m_setAttackTarget.end(); )
    {
        BaseCharacter* pChar = theRunTimeData.GetCharacterByID( *iter );
        if ( pChar == NULL || pChar->GetMapID() != GetMapID() )
        { 
            iter = m_setAttackTarget.erase( iter );
            continue; 
        }

        // 已经无仇恨了
        EnmityData* pEnmityData = pChar->GetEnmity( GetID() );
        if ( pEnmityData == NULL || !pEnmityData->HaveEnmity() )
        {
            iter = m_setAttackTarget.erase( iter );
            continue;
        }

        ++iter;
    }

    TryChangeFightState( HaveEnmity(), eFighting );
}

void GamePlayer::CalcEnmity( BaseCharacter* pTarget, const ItemDefine::SItemSkill* pSkillConfig, int nDamage )
{
    BaseCharacter::CalcEnmity( pTarget, pSkillConfig, nDamage );

    if ( pSkillConfig->stEnmity == 0 )
    { return; }

    // 如果是自己, 则不需要加仇恨
    if ( pTarget->GetID() == GetID() )
    { return; }

    // 资源怪不加仇恨
    if ( pTarget->IsResourceMonster() )
    { return; }

	//如果对方是怪物或者战斗NPC，他们在回去的过程中不加仇恨
	if ( pTarget->IsMonster() )
	{
		MonsterBaseEx* pMonster = static_cast< MonsterBaseEx* >( pTarget );
		if ( pMonster->GetAiStatus() == AiDefine::ThinkingMoveToBorn )
			return;
	}

	if ( pTarget->IsFightNpc() )
	{
		NpcFightEx* pFightNpc = static_cast< NpcFightEx* >( pTarget );
		if ( pFightNpc->GetAiStatus() == AiDefine::ThinkingMoveToBorn )
			return;
	}

    // 添加自己的攻击目标
    // 普通攻击
    if ( IsNormalAttack( pSkillConfig->ustItemID ) )
    { AddAttackTarget( pTarget->GetID() ); }

    unsigned int nEnmity = nDamage + pSkillConfig->stEnmity;

    if ( nEnmity < MIN_ENMINYVALUE )
    { nEnmity = MIN_ENMINYVALUE; }

    ItemDefine::SItemStatus* pItemStatus = GettheItemDetail().GetStatusBySkill( pSkillConfig );
    if ( pItemStatus == NULL || !pItemStatus->bAvail )
    {
        pTarget->AddEnmity( GetID(), nEnmity, nDamage, pTarget->GetEnmityRate() );
		//TellClient("Name:%s Enmity:%d Damage:%d,total:%d", pTarget->GetCharName(), nEnmity,nDamage,enmt);
    }
    else
    {
        // 有利的, 给对方的攻击目标加一个仇恨
        BaseCharacter* pLockTarget = theRunTimeData.GetCharacterByID( pTarget->GetLockID() );
        if ( pLockTarget != NULL && CheckCanAttackTarget( pLockTarget ) )
        {
            pLockTarget->AddEnmity( GetID(), nEnmity, nDamage, pLockTarget->GetEnmityRate() );
        }
    }
}
