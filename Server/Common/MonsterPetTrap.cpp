#include "MonsterPetTrap.h"
#include "GamePlayer.h"

MonsterPetTrap::MonsterPetTrap() : MonsterPetEx()
{
    SetObjType( Object_MonsterTrap );

    SetAiStatus( AiDefine::ThinkingDoNothing );
}

void MonsterPetTrap::Initialize( ItemDefine::SMonster* pConfig, MonsterCreateData& xCreateData, GamePlayer* pPlayer /* = NULL */ )
{
    MonsterPetEx::Initialize( pConfig, xCreateData, pPlayer );

    // 陷阱怪不能移动
    SetMoveSpeed( 0.0f );
    SettAttackMoveSpeed( 0.0f );
    SetIdleMoveSpeed( 0.0f );
    SetLastMovingSpeed( 0.0f );
}

void MonsterPetTrap::ProcessAiTask( AiTask* pAiTask )
{
    MonsterBaseEx::ProcessAiTask( pAiTask );

    // 陷阱怪使用技能后, 马上消失
    SetMonsterExit();
}

uint8 MonsterPetTrap::CheckCanAttackResult( BaseCharacter* pTarget )
{
    // 如果是仇恨势力, 还需要判断, 因为陷阱在空闲状态下是不攻击被动怪的
    uint8 nCheckResult = MonsterPetEx::CheckCanAttackResult( pTarget );
    switch ( nCheckResult )
    {
    case CheckAttack::CanNotAttack:
    case CheckAttack::EnmityFightCamp:
    case CheckAttack::EnmityCountry:
    case CheckAttack::EnmityTarget:
        return nCheckResult;
        break;
    default:
        break;
    }

    if ( pTarget->IsMonster() )
    {
        // 如果在攻击状态, 所有怪物都能攻击
        switch ( GetAiStatus() )
        {
        case AiDefine::ThinkingAttackTarget:
            return CheckAttack::EnmityTarget;
            break;
        default:
            {
                // 普通状态, 主动怪能攻击
                MonsterBaseEx* pMonster = static_cast< MonsterBaseEx* >( pTarget );
                if ( pMonster->GetActiveMonster() )
                { return CheckAttack::EnmityTarget; }
            }
            break;
        }
    }

    return CheckAttack::AttackUnknow;
}

void MonsterPetTrap::CalcEnmity( BaseCharacter* pTarget, const ItemDefine::SItemSkill* pSkillConfig, int nDamage )
{
    BaseCharacter::CalcEnmity( pTarget, pSkillConfig, nDamage );

    // 技能不带仇恨值
    if ( pSkillConfig->stEnmity == 0 )
    {  return; }

    // 技能陷阱怪 加主人的仇恨
    GamePlayer* pMaster = GetMasterPlayer();
    if ( pMaster == NULL )
    { return; }

    // 添加主人攻击了他们
    pMaster->AddAttackTarget( pTarget->GetID() );

    // 仇恨值
    int nEnmity = nDamage + pSkillConfig->stEnmity;
    if ( nEnmity >= 0 )
    { 
        pTarget->AddEnmity( pMaster->GetID(), nEnmity, nDamage, GetEnmityRate() );
    }
    else
    { 
        // 减少仇恨不能减少到0
        pTarget->DecEnmity( pMaster->GetID(), abs( nEnmity ) );
        pTarget->AddEnmity( pMaster->GetID(), 1, nDamage, GetEnmityRate() );
    }
}

void MonsterPetTrap::ProcessEndAttackStatus()
{
    MonsterBaseEx::ProcessEndAttackStatus();

    // 在原地不动
    SetAiStatus( AiDefine::ThinkingDoNothing );
}

void MonsterPetTrap::ProcessFindAttackTarget()
{
    MonsterBaseEx::ProcessFindAttackTarget();
}

void MonsterPetTrap::ProcessRefreshEnmity( uint32 nCurrentTime )
{
    MonsterBaseEx::ProcessRefreshEnmity( nCurrentTime );
}
