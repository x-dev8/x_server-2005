#include "GamePlayer.h"
#include "MonsterBaseEx.h"
#include "ShareData.h"
#include "NpcFightEx.h"

void GamePlayer::ProcessRefreshEnmity( uint32 nCurrentTime )
{
    // ��ʱ��
    if ( !m_xRefeshEnmityTimer.DoneTimer( nCurrentTime ) )
    { return; }

    // ���˶��ҵĳ��, ˥��
    for ( TargetEnmityMapIter iter = m_mapTargetEnmity.begin(); iter != m_mapTargetEnmity.end(); ++iter )
    {
        // ���˥��
        BaseCharacter* pChar = theRunTimeData.GetCharacterByID( iter->first );
        if ( pChar == NULL )
        { continue; }

        // ���˥��
        iter->second.DecEnmity( iter->second.GetReduction() );
    }

    // �ж��Ҵ������, ����Է�û���ҵĳ����, ��ɾ��֮
    for ( AttackTargetSetIter iter = m_setAttackTarget.begin(); iter != m_setAttackTarget.end(); )
    {
        BaseCharacter* pChar = theRunTimeData.GetCharacterByID( *iter );
        if ( pChar == NULL || pChar->GetMapID() != GetMapID() )
        { 
            iter = m_setAttackTarget.erase( iter );
            continue; 
        }

        // �Ѿ��޳����
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

    // ������Լ�, ����Ҫ�ӳ��
    if ( pTarget->GetID() == GetID() )
    { return; }

    // ��Դ�ֲ��ӳ��
    if ( pTarget->IsResourceMonster() )
    { return; }

	//����Է��ǹ������ս��NPC�������ڻ�ȥ�Ĺ����в��ӳ��
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

    // ����Լ��Ĺ���Ŀ��
    // ��ͨ����
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
        // ������, ���Է��Ĺ���Ŀ���һ�����
        BaseCharacter* pLockTarget = theRunTimeData.GetCharacterByID( pTarget->GetLockID() );
        if ( pLockTarget != NULL && CheckCanAttackTarget( pLockTarget ) )
        {
            pLockTarget->AddEnmity( GetID(), nEnmity, nDamage, pLockTarget->GetEnmityRate() );
        }
    }
}
