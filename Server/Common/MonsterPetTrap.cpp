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

    // ����ֲ����ƶ�
    SetMoveSpeed( 0.0f );
    SettAttackMoveSpeed( 0.0f );
    SetIdleMoveSpeed( 0.0f );
    SetLastMovingSpeed( 0.0f );
}

void MonsterPetTrap::ProcessAiTask( AiTask* pAiTask )
{
    MonsterBaseEx::ProcessAiTask( pAiTask );

    // �����ʹ�ü��ܺ�, ������ʧ
    SetMonsterExit();
}

uint8 MonsterPetTrap::CheckCanAttackResult( BaseCharacter* pTarget )
{
    // ����ǳ������, ����Ҫ�ж�, ��Ϊ�����ڿ���״̬���ǲ����������ֵ�
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
        // ����ڹ���״̬, ���й��ﶼ�ܹ���
        switch ( GetAiStatus() )
        {
        case AiDefine::ThinkingAttackTarget:
            return CheckAttack::EnmityTarget;
            break;
        default:
            {
                // ��ͨ״̬, �������ܹ���
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

    // ���ܲ������ֵ
    if ( pSkillConfig->stEnmity == 0 )
    {  return; }

    // ��������� �����˵ĳ��
    GamePlayer* pMaster = GetMasterPlayer();
    if ( pMaster == NULL )
    { return; }

    // ������˹���������
    pMaster->AddAttackTarget( pTarget->GetID() );

    // ���ֵ
    int nEnmity = nDamage + pSkillConfig->stEnmity;
    if ( nEnmity >= 0 )
    { 
        pTarget->AddEnmity( pMaster->GetID(), nEnmity, nDamage, GetEnmityRate() );
    }
    else
    { 
        // ���ٳ�޲��ܼ��ٵ�0
        pTarget->DecEnmity( pMaster->GetID(), abs( nEnmity ) );
        pTarget->AddEnmity( pMaster->GetID(), 1, nDamage, GetEnmityRate() );
    }
}

void MonsterPetTrap::ProcessEndAttackStatus()
{
    MonsterBaseEx::ProcessEndAttackStatus();

    // ��ԭ�ز���
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
