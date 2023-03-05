#include "AiNormalAttackTask.h"
#include "ShareData.h"
#include "SkillTaskManager.h"
#include "MonsterBaseEx.h"
#include "NpcFightEx.h"

AiNormalAttackTask::AiNormalAttackTask()
{
    strncpy_s(m_szName, "AiNormalAttackTask", sizeof(m_szName)-1);
    _targetObjectId = InvalidGameObjectId;
    m_iLevel   = 0;
    m_iSkillId = 0;
}

AiNormalAttackTask::~AiNormalAttackTask()
{
}

void AiNormalAttackTask::ExecuteTask( BaseCharacter* pOwner )
{
    if (pOwner != NULL)
    { pOwner->_SkillTaskManager.Clear(); }

    if( _targetObjectId == InvalidGameObjectId )
    { return; }

    BaseCharacter* pTarget = (BaseCharacter*)theRunTimeData.GetCharacterByID( _targetObjectId );
    if( NULL == pTarget || !pOwner->CheckCanAttackTarget( pTarget ) )
    { 
        // 无条件返回
        _targetObjectId = InvalidGameObjectId;
        return;
    }

    //if ( pOwner->IsMonster() )
    //{
    //    MonsterBase* pMonsterBase = (MonsterBase*)pOwner;
    //    pMonsterBase->SetCanAttackCharId( _targetObjectId );
    //}
    //else if ( pOwner->GetObjType() == Object_NpcFight )
    //{
    //    NpcFightEx* pNpcFight = (NpcFightEx*)pOwner;
    //    pNpcFight->SetCanAttackCharId( _targetObjectId );
    //}
    //else
    //{ return; }

    SAttackTarget target;
    target.bIsCharTarget = true;
	target.nCharID = pTarget->GetID();
    ItemDefine::SItemSkill* pSkill = GettheItemDetail().GetSkillByID( m_iSkillId, m_iLevel );
    if ( NULL == pSkill)
    { return; }

	bool bCharTarget = true;
	
	if( ItemDefine::casttarget_pos == pSkill->ustCastTarget )
	{ bCharTarget = false; }
	
	GameObjectId stTargetID = pTarget->GetID();
	if( ItemDefine::casttarget_me == pSkill->ustCastTarget )
	{
		stTargetID = pOwner->GetID();
	}
    else if( ItemDefine::casttarget_friendlive == pSkill->ustCastTarget )
	{
		stTargetID = pOwner->GetID();
	}

    if( MsgUseSkillHintMessage::eNormal == pOwner->IsSkillCanUse( m_iSkillId, m_iLevel ) )
	{   
		pOwner->_SkillTaskManager.SetTasks( SSkillTask::STT_SingleSkill, true, stTargetID, D3DXVECTOR3(0,0,0), m_iSkillId, m_iLevel );
	}
}
