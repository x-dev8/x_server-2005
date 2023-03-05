#include "MonsterSpecial.h"
#include "ShareData.h"
#include "GamePlayer.h"
#include "TeamManager.h"
#include "DropItemManager.h"

MonsterSpecial::MonsterSpecial() : MonsterBaseEx()
{
    SetSpecialType( MonsterDefine::SpecialNone );
    SetSpecialValue( 0 );

    SetObjType( Object_MonsterSpecial );
}

void MonsterSpecial::Initialize( ItemDefine::SMonster* pConfig, MonsterCreateData& xCreateData, GamePlayer* pPlayer /* = NULL */ )
{
    MonsterBaseEx::Initialize( pConfig, xCreateData, pPlayer );

    SetSpecialType( xCreateData.GetSpecialType() );
    SetSpecialValue( xCreateData.GetSpecialValue() );
}

void MonsterSpecial::ProcessDeathCallScript()
{
    if ( !CheckDeathCallScript() )
    { return; }

    switch ( GetSpecialType() )
    {
    case MonsterDefine::SpecialPlayerAttack:
    case MonsterDefine::SpecialPlayerVar:
        {
            GamePlayer* pPlayer = theRunTimeData.GetGamePlayerByDBID( GetSpecialValue() );
            if ( pPlayer == NULL || pPlayer->GetMapID() != GetMapID() )
            { return; }

            GetScriptMgr()->StartupVM( ST_MONSTER, GetMonsterID(), pPlayer, false, AiDefine::MonsterDeathScriptEnter, GetID() );
        }
        break;
    case MonsterDefine::SpecialTeamAttack:
    case MonsterDefine::SpecialTeamVar:
        {
            GameTeam* pTeam = theGameTeamManager.GetTeam( GetSpecialValue() );
            if ( pTeam == NULL )
            { return; }

            for ( int i = 0; i < pTeam->TeamMemberCount(); ++i )
            {
                GameTeamMember* pMember = pTeam->GetTeamMemberByIndex( i );
                if ( pMember == NULL )
                { continue; }

                GamePlayer* pPlayer = theRunTimeData.GetGamePlayerByDBID( pMember->GetID() );
                if ( pPlayer == NULL || pPlayer->GetMapID() != GetMapID() )
                { continue; }

                GetScriptMgr()->StartupVM( ST_MONSTER, GetMonsterID(), pPlayer, false, AiDefine::MonsterDeathScriptEnter, GetID() );
            }
        }
        break;
    default:
        break;
    }
}

void MonsterSpecial::ProcessDeathDromItem()
{
    switch ( GetSpecialType() )
    {
    case MonsterDefine::SpecialPlayerAttack:
    case MonsterDefine::SpecialPlayerVar:
        {
            GamePlayer* pPlayer = theRunTimeData.GetGamePlayerByDBID( GetSpecialValue() );
            if ( pPlayer == NULL || pPlayer->GetMapID() != GetMapID() )
            { return; }

            GetDropItemManager().MonsterDeath( this, pPlayer );
        }
        break;
    case MonsterDefine::SpecialTeamAttack:
    case MonsterDefine::SpecialTeamVar:
        {
            GameTeam* pTeam = theGameTeamManager.GetTeam( GetSpecialValue() );
            if ( pTeam == NULL )
            { return; }

            // 找到一个玩家掉落后直接返回
            for ( int i = 0; i < pTeam->TeamMemberCount(); ++i )
            {
                GameTeamMember* pMember = pTeam->GetTeamMemberByIndex( i );
                if ( pMember == NULL )
                { continue; }

                GamePlayer* pPlayer = theRunTimeData.GetGamePlayerByDBID( pMember->GetID() );
                if ( pPlayer == NULL || pPlayer->GetMapID() != GetMapID() )
                { continue; }

                GetDropItemManager().MonsterDeath( this, pPlayer );
                break;
            }
        }
        break;
    default:
        break;
    }
}

uint8 MonsterSpecial::CheckCanAttackResult( BaseCharacter* pTarget )
{
    // 有人攻击我, 我就反击
    EnmityData* pEnmityData = GetEnmity( pTarget->GetID() );
    if ( pEnmityData != NULL && pEnmityData->HaveEnmity() )
    { return CheckAttack::EnmityTarget; }

    // 只攻击专属者
    GamePlayer* pPlayer = NULL;
    if ( pTarget->IsPlayer() )
    { pPlayer = static_cast< GamePlayer* >( pTarget ); }
    else
    { pPlayer = pTarget->GetMasterPlayer(); }

    if ( pPlayer == NULL )
    { return CheckAttack::CanNotAttack; }

    switch ( GetSpecialType() )
    {
    case MonsterDefine::SpecialPlayerAttack:
    case MonsterDefine::SpecialPlayerVar:
        {
            if ( GetSpecialValue() == pPlayer->GetDBCharacterID() )
            { return CheckAttack::EnmityTarget; }
        }
        break;
    case MonsterDefine::SpecialTeamAttack:
    case MonsterDefine::SpecialTeamVar:
        {
            if ( GetSpecialValue() == pPlayer->GetTeamID() )
            { return CheckAttack::EnmityTarget; }
        }
        break;
    }

    return CheckAttack::AttackUnknow;
}

void MonsterSpecial::ProcessRefreshEnmity( uint32 nCurrentTime )
{
    // 专属的玩家, 或者队伍不存在了, 专属怪消失
    switch ( GetSpecialType() )
    {
    case MonsterDefine::SpecialPlayerAttack:
    case MonsterDefine::SpecialPlayerVar:
        {
            GamePlayer* pPlayer = theRunTimeData.GetGamePlayerByDBID( GetSpecialValue() );
            if ( pPlayer == NULL )
            { SetMonsterExit(); }
        }
        break;
    case MonsterDefine::SpecialTeamAttack:
    case MonsterDefine::SpecialTeamVar:
        {
            GameTeam* pTeam = theGameTeamManager.GetTeam( GetSpecialValue() );
            if ( pTeam == NULL )
            { SetMonsterExit(); }
        }
        break;
    default:
        {
            SetMonsterExit();
        }
        break;
    }

    MonsterBaseEx::ProcessRefreshEnmity( nCurrentTime );
}

bool MonsterSpecial::CheckSpecialTarget( int nSpecialType, GamePlayer* pTarget )
{
    if ( pTarget == NULL )
    { return false; }

    switch ( nSpecialType )
    {
    case MonsterDefine::SpecialPlayerAttack:
    case MonsterDefine::SpecialPlayerVar:
        {
            return pTarget->GetDBCharacterID() == GetSpecialValue();
        }
        break;
    case MonsterDefine::SpecialTeamAttack:
    case MonsterDefine::SpecialTeamVar:
        {
            return pTarget->GetTeamID() == GetSpecialValue();
        }
    default:
        break;
    }

    return false;
}