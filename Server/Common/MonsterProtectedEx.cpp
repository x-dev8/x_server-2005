#include "MonsterProtectedEx.h"
#include "ShareData.h"
#include "GamePlayer.h"

MonsterProtectedEx::MonsterProtectedEx() : MonsterBaseEx()
{
    SetForce( ForceDefine::PetMonsterForce );

    // 简直怪不执行AI思考
    SetMasterID( -1 );
    SetVarID( -1 );

    SetObjType( Object_MonsterProtected );

    // 一直是跟随主人状态
    SetAiStatus( AiDefine::ThinkingMoveToMaster );
}

MonsterProtectedEx::~MonsterProtectedEx()
{
    SetMasterID( -1 );
    SetVarID( -1 );
}

void MonsterProtectedEx::Initialize( ItemDefine::SMonster* pConfig, MonsterCreateData& xCreateData, GamePlayer* pPlayer /* = NULL */ )
{
    MonsterBaseEx::Initialize( pConfig, xCreateData, pPlayer );

    // 设置国家, 阵营信息
    SetCountry  ( pPlayer->GetCountry() );
    SetFightCamp( pPlayer->GetFightCamp() );
    SetForce    (  pPlayer->GetForce() );
    SetMasterID ( pPlayer->GetID() );
	SetIsCanRide( xCreateData.IsCanRide() );
}

int MonsterProtectedEx::GetThinkingSpaceTime()
{
    // 跟随200毫秒执行一次
    return AiDefine::BaseThinkTime;
}

uint8 MonsterProtectedEx::AiThinking( uint32 nCurrentTime )
{
    // 主人不见了, 自动消失
    GamePlayer* pMaster = GetMasterPlayer();
    if ( pMaster == NULL || pMaster->IsDead() )
    { 
        CharacterMurder();
        return AiDefine::ThinkingDoNothing;
    }

    // 直接返回当前状态
    return GetAiStatus();
}

Msg* MonsterProtectedEx::FirstSightOnMe( char* szMsgBuffer, unsigned int nBuffSize )
{
    MonsterBaseEx::FirstSightOnMe( szMsgBuffer, nBuffSize );

    MsgNPCEnterMySight* pEnter = reinterpret_cast< MsgNPCEnterMySight* >( szMsgBuffer );

    pEnter->stMasterId = GetMasterID();
	pEnter->bIsCanRide = IsCanRide();
    GamePlayer* pMaster = GetMasterPlayer();
    if ( pMaster != NULL )
    { HelperFunc::SafeNCpy( pEnter->szDisplayName, pMaster->GetCharName(), sizeof( pEnter->szDisplayName ) ); }
	pEnter->BelongID			= GetKiller()?GetKiller()->GetID():0;
	pEnter->bIsCanRide		= IsCanRide();
    return pEnter;
}

void MonsterProtectedEx::CharacterMurder()
{
    ProcessProtectedDeath();

    // 基类方法
    MonsterBaseEx::CharacterMurder();
}

void MonsterProtectedEx::ProcessProtectedDeath()
{
    GamePlayer* pMaster = GetMasterPlayer();
    if ( pMaster != NULL )
    {
        pMaster->ResetLostProtectCharData();

        // 清除绑定的记数变量
        if ( GetVarID() != -1 )
        { pMaster->SetVar( GetVarID(), 0 ); }
    }
}

void MonsterProtectedEx::OnDeath()
{
    // 处理死亡
    ProcessProtectedDeath();

    MonsterBaseEx::OnDeath();
}

bool MonsterProtectedEx::CheckAddViewEnmity( EnmityData& xEnmityData, BaseCharacter* pChar )
{
    // 跟随型护送怪不要保持仇恨
    return false;
}

void MonsterProtectedEx::ProcessEndAttackStatus()
{
    MonsterBaseEx::ProcessEndAttackStatus();

    // 设置状态 移动到主人身边
    SetAiStatus( AiDefine::ThinkingMoveToMaster );
}
