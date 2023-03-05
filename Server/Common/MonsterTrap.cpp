#include "MonsterTrap.h"
#include "ShareData.h"
#include "GameWorld.h"
#include "GamePlayer.h"

MonsterPetTrap::MonsterPetTrap()
{
    _skillUseCount = 0;
}

MonsterPetTrap::~MonsterPetTrap()
{

}

void MonsterPetTrap::OnBeAttacked( BaseCharacter* pAttacker,const CItemDetail::SItemSkill* pSkillConfig )
{
    if( !pAttacker)
    { return; }

    BaseCharacter::OnBeAttacked( pAttacker, pSkillConfig);

    StartUpAI();
    if ( !HaveCanAttackCharId() )
    { _disableControlThinkTime = true; }

    //记录下上一次未被攻击前的空闲位置
    if (GetAiData()->lastIdleX == 0)
    {
        GetAiData()->lastIdleX = GetFloatX();
        GetAiData()->lastIdleY = GetFloatY();
    }
}

bool MonsterPetTrap::OnThink()
{   
    if ( _skillUseCount >= 1)
    {
        Exit();
        return false;
    }

    BaseCharacter* pSummoner = theRunTimeData.GetCharacterByID( GetSummonMasterID() );
    if ( NULL == pSummoner || !pSummoner->IsPlayer() || pSummoner->IsDead() )
    { 
        Murder(); 
        return false;
    }

    GamePlayer* pPlayer = static_cast<GamePlayer*>( pSummoner );

    if( HaveAskToAttackTargetId() )
    {   
        BaseCharacter* Target = theRunTimeData.GetCharacterByID(m_AskToAttackTargetID);
        if (!MasterOutOfTarget(pSummoner,Target,60))
        { LockTarget( m_AskToAttackTargetID ); }
        else
        { ClearCanAttackCharId(); }
    }
    else
    {
        m_AskToAttackTargetID = pSummoner->GetMaxEnmityChar();
        if( HaveAskToAttackTargetId() )
        { LockTarget( m_AskToAttackTargetID ); }
    }

    if( HaveCanAttackCharId() )
    {
        m_bIsFighting = true;
        TryChangeFightState( m_bIsFighting, eFighting );
        BaseCharacter* pTarget = GetCanAttackChar();

        if( pTarget == NULL || GetMapID() != pTarget->GetMapID() || pTarget->IsDead() || pTarget->GetBuffManager()->IsHide() )
        { // 目标不存在 目标不在一个地图 目标已经死了 目标是隐身状态
            LostAttackTarget();
            return false;
        }

        if( pTarget->IsPlayer() && IsAttackTargetIsProtectChar() )
        { // 别打主人
            LostAttackTarget();
            return false;
        }

        _isNeedMove = false;

        if (!_SkillTaskManager.IsTaskEmpty())
        { return false; }

        uint16 skillId    = GetAiData()->GetCurrentSelectSkillId();
        uint8  skillLevel = GetAiData()->GetCurrentSelectSkillLevel();

        if ( skillId == 0)
        {
            SetStatus( CS_IDLE );
            return false;
        }

        // 得到当前选择的技能
        if ( IsNormalAttack( skillId ) )
        {
            if ( !_buffManager.IsCanUsePhysicsSkill() )
            {
                SetStatus( CS_IDLE );
                return false;
            }
        }
        else
        {
            if ( !_buffManager.IsCanUseMagicSkill() )
            {
                SetStatus( CS_IDLE );
                return false;
            }
        }

        m_pCurSkill = GettheItemDetail().GetSkillByID( skillId, skillLevel );
        if ( NULL == m_pCurSkill )
        {
            SetStatus( CS_IDLE );
            return false;
        }

        SetCurSkillIndex( GetAiData()->GetCurrentSelectSkillIndex() );
        SetCurSkillLevel( GetAiData()->GetCurrentSelectSkillIndex() );
        m_stCurAttackRange = m_pCurSkill->fRangeCanCast;

        float fRangeCorrect = monsterCastCorrect;

        if ( IsInAttackRange( pTarget, m_pCurSkill, fRangeCorrect ) )
        { // 在攻击范围内
            if( GetAiData()->GetCurrentSelectSkillIndex() > 0 )
            {
                m_stCurAiTactic = EAISelectTaskType_TryUseSkill;
            }
            else
            {
                m_stCurAiTactic = EAISelectTaskType_TryAttackTarget;
            }
            m_bClosingToTarget = false;
        }
    }
    else
    {
        if( HaveAskToAttackTargetId() )
        { ClearAskToAttackTargetId(); }

        m_bIsFighting = false;
        TryChangeFightState( m_bIsFighting, eFighting );
    }
    return true;
}

bool MonsterPetTrap::OnMove( uint32 lapseTime )
{
    // 开始不同情况的移动
    if( HaveCanAttackCharId() )
    { MoveAttackMoving( lapseTime ); }
    else
    { MovePosMoving( lapseTime ); }
    return true;
}

void MonsterPetTrap::MoveAttackMoving( uint32 lapseTime )
{
    BaseCharacter* pTarget = GetCanAttackChar();
    if( NULL == pTarget || GetMapID() != pTarget->GetMapID() || pTarget->IsDead())
    {
        LostAttackTarget();
        return;
    }

    if( GameTime::IsPassCurrentTime( m_dwSendMoveMessageTime, 1000 ) )
    {
        theGameWorld.OnRefreshNewArea( GetID() );

        SendVerifyPos( GetFloatX(), GetFloatY() );

        m_dwSendMoveMessageTime = theGameWorld.g_dwLastWorldProcessTime;
    }
}

void MonsterPetTrap::MovePosMoving( uint32 lapseTime )
{
    if( GameTime::IsPassCurrentTime( m_dwSendMoveMessageTime, 2000 ) )
    { // 移动消息频率 更新用 比如GateServer热起

        theGameWorld.OnRefreshNewArea( GetID() );
        if ( AreaHavePlayer() )
        {
            if ( GameTime::IsPassCurrentTime( m_noMoveSendVerifyPosTime, 4000 ) )
            { 
                SendVerifyPos( GetFloatX(), GetFloatY() ); 
                m_noMoveSendVerifyPosTime = HQ_TimeGetTime();
            }
        }
        m_dwSendMoveMessageTime = HQ_TimeGetTime();
    }
}