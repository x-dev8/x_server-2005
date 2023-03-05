#include "MonsterPetEx.h"
#include "ShareData.h"
#include "GamePlayer.h"
#include "D3DFunction.h"

MonsterPetEx::MonsterPetEx() : MonsterBaseEx()
{
    SetForce( ForceDefine::PetMonsterForce );

    SetMasterID( -1 );

    m_fAttackMoveSpeed = 0.f;
    m_fIdleMoveSpeed   = 0.f;

    SetAiStatus( AiDefine::ThinkingMoveToMaster );
}

void MonsterPetEx::Initialize( ItemDefine::SMonster* pConfig, MonsterCreateData& xCreateData, GamePlayer* pPlayer /* = NULL */ )
{
    MonsterBaseEx::Initialize( pConfig, xCreateData, pPlayer );

    if ( !IsFloatZero( pConfig->fMoveSpeed )  )
    { // ���˵��ƶ��ٶ�
        GetCharFightAttr()->moveSpeed.base = pPlayer->GetMoveSpeed();
        SettAttackMoveSpeed ( pPlayer->GetMoveSpeed() );
        SetIdleMoveSpeed    ( pPlayer->GetMoveSpeed() );
        SetLastMovingSpeed  ( pPlayer->GetMoveSpeed() );
    }

    UpdateCharAllAttibute();

    // ���ù���, ��Ӫ��Ϣ
    SetCountry  ( pPlayer->GetCountry() );
    SetFightCamp( pPlayer->GetFightCamp() );
    SetForce    (  pPlayer->GetForce() );
    SetMasterID ( pPlayer->GetID() );
}

void MonsterPetEx::CharacterMurder()
{
    ProcessPetDeath( EPetDeathType_Murder );

    // ���෽��
    MonsterBaseEx::CharacterMurder();
}

void MonsterPetEx::OnDeath()
{
    // ��������
    ProcessPetDeath( EPetDeathType_BeKilled );

    MonsterBaseEx::OnDeath();
}

void MonsterPetEx::ProcessPetDeath( int deathType )
{

}

Msg* MonsterPetEx::FirstSightOnMe( char* szMsgBuffer, unsigned int nBuffSize )
{
    MonsterBaseEx::FirstSightOnMe( szMsgBuffer, nBuffSize );

    MsgNPCEnterMySight* pEnter = reinterpret_cast< MsgNPCEnterMySight* >( szMsgBuffer );

    pEnter->stMasterId = GetMasterID();

	pEnter->BelongID			= GetKiller()?GetKiller()->GetID():0;
    GamePlayer* pMaster = GetMasterPlayer();
    if ( pMaster != NULL )
    { HelperFunc::SafeNCpy( pEnter->szDisplayName, pMaster->GetCharName(), sizeof( pEnter->szDisplayName ) ); }

    return pEnter;
}

int MonsterPetEx::GetThinkingSpaceTime()
{
    return AiDefine::BaseThinkTime;
}

void MonsterPetEx::ProcessEndAttackStatus()
{
    MonsterBaseEx::ProcessEndAttackStatus();

    SetAiStatus( AiDefine::ThinkingMoveToMaster );
}


uint8 MonsterPetEx::AiThinking( uint32 nCurrentTime )
{
    // ���˲�����, �Զ���ʧ
    GamePlayer* pMaster = GetMasterPlayer();
    if ( pMaster == NULL || pMaster->IsDead() )
    { 
        CharacterMurder(); 
        return AiDefine::ThinkingDoNothing;
    }
    
    return MonsterBaseEx::AiThinking( nCurrentTime );
}

void MonsterPetEx::ProcessEnterSightEnmity( BaseCharacter* pTarget )
{
    // ��������, ������Ұ�ͼ������б�
    AddEnmity( pTarget->GetID(), 0, 0, GetEnmityRate() );
}

uint8 MonsterPetEx::CheckCanAttackResult( BaseCharacter* pTarget )
{
    // ����ǳ������, ����Ҫ�ж�, ��Ϊ�����ڿ���״̬���ǲ����������ֵ�
    uint8 nCheckResult = MonsterBaseEx::CheckCanAttackResult( pTarget );
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
    
    GamePlayer* pMaster = GetMasterPlayer();
    if ( pMaster == NULL )
    { return CheckAttack::CanNotAttack; }

    // �Է������˺��ҵ�������ͬһ���ˣ� ��ʾ���ܹ���
    if ( pMaster->GetID() == pTarget->GetMasterID() )
    { return CheckAttack::CanNotAttack; }

    // ���˹�������, ����Թ���
    if ( pMaster->IsAttackTarget( pTarget->GetID() ) )
    { return CheckAttack::EnmityTarget; }

    // ���˿��Թ�����, ����Թ���
    if ( pMaster->CheckCanAttackTarget( pTarget ) )
    { return CheckAttack::EnmityTarget; }

    // ���˶����г��, Ҳ���Թ���
    EnmityData* pEnmityData = pMaster->GetEnmity( pTarget->GetID() );
    if ( pEnmityData != NULL && pEnmityData->HaveEnmity() )
    { return CheckAttack::EnmityTarget; }

    // ������Թ�������
    if ( pTarget->IsMonster() && !pTarget->HaveMaster() )
    { return CheckAttack::EnmityForce; }

    return CheckAttack::AttackUnknow;
}

void MonsterPetEx::ProcessFindAttackTarget()
{
    // ��������״̬�²�����
    switch ( GetAiStatus() )
    {
    case AiDefine::ThinkingFollowMaster:
    case AiDefine::ThinkingIdle:
        return;
        break;
    }

    BaseCharacter* pTarget = theRunTimeData.GetCharacterByID( GetLockID() );
    if ( pTarget == NULL )
    {
        return ProcessEndAttackStatus();
    }

    return ProcessLockTarget( GetLockID() );
}

void MonsterPetEx::ProcessRefreshEnmity( uint32 nCurrentTime )
{
    // ����״̬�²�����
    switch ( GetAiStatus() )
    {
    case AiDefine::ThinkingFollowMaster:
        return;
        break;
    }

    // ÿ�ζ��������˵Ĺ���Ŀ��
    GamePlayer* pPlayer = GetMasterPlayer();
    if ( pPlayer == NULL || pPlayer->GetLockID() == GetID() )
    { return; }

    if ( !pPlayer->IsAttackTarget( pPlayer->GetLockID() ) )
    { return; }

    BaseCharacter* pLockChar = pPlayer->GetLockChar();
    if ( pLockChar == NULL )
    { return; }

    if ( !pPlayer->CheckCanAttackTarget( pLockChar ) )
    { return; }

    SetLockID( pPlayer->GetLockID() );
}

 void MonsterPetEx::ProcessIdle()
 {
     GamePlayer* pMaster = GetMasterPlayer();
     if ( pMaster == NULL || pMaster->IsDead() )
     { return CharacterMurder(); }

     ClearMoveTargetPoint();
     ProcessAttackMoveSpeed();

     // ����ͬһ����ͼ, �Ͳ�����
     if ( pMaster->GetMapID() != GetMapID() )
     { return ; }

     D3DXVECTOR3 vMasterPos = pMaster->GetPos();
     D3DXVECTOR3 vCurPos    = GetPos();

     // ֻ�ж�ƽ��λ��
     D3DXVECTOR3 vecDistance( vMasterPos.x - vCurPos.x, vMasterPos.y - vCurPos.y, 0 );
     float fDistance = D3DXVec3Length( &vecDistance );

     if (  fDistance <= AiDefine::ProtectCharStopDistance )
     { return ; }

     pMaster->ProcessSummonObjectChangeMap( GetID() );
 }

 // �����Է�, �ڶԷ����ϼ������˵ĳ��
 void MonsterPetEx::CalcEnmity( BaseCharacter* pTarget, const ItemDefine::SItemSkill* pSkillConfig, int nDamage )
 {
     AiCharacter::CalcEnmity( pTarget, pSkillConfig, nDamage );

     // ���ܲ������ֵ
     if ( pSkillConfig->stEnmity == 0 )
     {  return; }

     GamePlayer* pMaster = GetMasterPlayer();
     if ( pMaster == NULL  )
     {  return; }

     // ����ҹ����˶Է�
     pMaster->AddAttackTarget( pTarget->GetID() );

     // ���ֵ
     int nEnmity = (nDamage + pSkillConfig->stEnmity) / 2;
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