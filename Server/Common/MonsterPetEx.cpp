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
    { // 主人的移动速度
        GetCharFightAttr()->moveSpeed.base = pPlayer->GetMoveSpeed();
        SettAttackMoveSpeed ( pPlayer->GetMoveSpeed() );
        SetIdleMoveSpeed    ( pPlayer->GetMoveSpeed() );
        SetLastMovingSpeed  ( pPlayer->GetMoveSpeed() );
    }

    UpdateCharAllAttibute();

    // 设置国家, 阵营信息
    SetCountry  ( pPlayer->GetCountry() );
    SetFightCamp( pPlayer->GetFightCamp() );
    SetForce    (  pPlayer->GetForce() );
    SetMasterID ( pPlayer->GetID() );
}

void MonsterPetEx::CharacterMurder()
{
    ProcessPetDeath( EPetDeathType_Murder );

    // 基类方法
    MonsterBaseEx::CharacterMurder();
}

void MonsterPetEx::OnDeath()
{
    // 处理死亡
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
    // 主人不见了, 自动消失
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
    // 宠物类型, 进入视野就加入仇恨列表
    AddEnmity( pTarget->GetID(), 0, 0, GetEnmityRate() );
}

uint8 MonsterPetEx::CheckCanAttackResult( BaseCharacter* pTarget )
{
    // 如果是仇恨势力, 还需要判断, 因为陷阱在空闲状态下是不攻击被动怪的
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

    // 对方的主人和我的主人是同一个人， 表示不能攻击
    if ( pMaster->GetID() == pTarget->GetMasterID() )
    { return CheckAttack::CanNotAttack; }

    // 主人攻击了他, 则可以攻击
    if ( pMaster->IsAttackTarget( pTarget->GetID() ) )
    { return CheckAttack::EnmityTarget; }

    // 主人可以攻击他, 则可以攻击
    if ( pMaster->CheckCanAttackTarget( pTarget ) )
    { return CheckAttack::EnmityTarget; }

    // 主人对它有仇恨, 也可以攻击
    EnmityData* pEnmityData = pMaster->GetEnmity( pTarget->GetID() );
    if ( pEnmityData != NULL && pEnmityData->HaveEnmity() )
    { return CheckAttack::EnmityTarget; }

    // 宠物可以攻击怪物
    if ( pTarget->IsMonster() && !pTarget->HaveMaster() )
    { return CheckAttack::EnmityForce; }

    return CheckAttack::AttackUnknow;
}

void MonsterPetEx::ProcessFindAttackTarget()
{
    // 待机跟随状态下不攻击
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
    // 跟随状态下不攻击
    switch ( GetAiStatus() )
    {
    case AiDefine::ThinkingFollowMaster:
        return;
        break;
    }

    // 每次都锁定主人的攻击目标
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

     // 不在同一个地图, 就不跟随
     if ( pMaster->GetMapID() != GetMapID() )
     { return ; }

     D3DXVECTOR3 vMasterPos = pMaster->GetPos();
     D3DXVECTOR3 vCurPos    = GetPos();

     // 只判断平面位置
     D3DXVECTOR3 vecDistance( vMasterPos.x - vCurPos.x, vMasterPos.y - vCurPos.y, 0 );
     float fDistance = D3DXVec3Length( &vecDistance );

     if (  fDistance <= AiDefine::ProtectCharStopDistance )
     { return ; }

     pMaster->ProcessSummonObjectChangeMap( GetID() );
 }

 // 攻击对方, 在对方身上加上主人的仇恨
 void MonsterPetEx::CalcEnmity( BaseCharacter* pTarget, const ItemDefine::SItemSkill* pSkillConfig, int nDamage )
 {
     AiCharacter::CalcEnmity( pTarget, pSkillConfig, nDamage );

     // 技能不带仇恨值
     if ( pSkillConfig->stEnmity == 0 )
     {  return; }

     GamePlayer* pMaster = GetMasterPlayer();
     if ( pMaster == NULL  )
     {  return; }

     // 添加我攻击了对方
     pMaster->AddAttackTarget( pTarget->GetID() );

     // 仇恨值
     int nEnmity = (nDamage + pSkillConfig->stEnmity) / 2;
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