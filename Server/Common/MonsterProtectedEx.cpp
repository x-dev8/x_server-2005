#include "MonsterProtectedEx.h"
#include "ShareData.h"
#include "GamePlayer.h"

MonsterProtectedEx::MonsterProtectedEx() : MonsterBaseEx()
{
    SetForce( ForceDefine::PetMonsterForce );

    // ��ֱ�ֲ�ִ��AI˼��
    SetMasterID( -1 );
    SetVarID( -1 );

    SetObjType( Object_MonsterProtected );

    // һֱ�Ǹ�������״̬
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

    // ���ù���, ��Ӫ��Ϣ
    SetCountry  ( pPlayer->GetCountry() );
    SetFightCamp( pPlayer->GetFightCamp() );
    SetForce    (  pPlayer->GetForce() );
    SetMasterID ( pPlayer->GetID() );
	SetIsCanRide( xCreateData.IsCanRide() );
}

int MonsterProtectedEx::GetThinkingSpaceTime()
{
    // ����200����ִ��һ��
    return AiDefine::BaseThinkTime;
}

uint8 MonsterProtectedEx::AiThinking( uint32 nCurrentTime )
{
    // ���˲�����, �Զ���ʧ
    GamePlayer* pMaster = GetMasterPlayer();
    if ( pMaster == NULL || pMaster->IsDead() )
    { 
        CharacterMurder();
        return AiDefine::ThinkingDoNothing;
    }

    // ֱ�ӷ��ص�ǰ״̬
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

    // ���෽��
    MonsterBaseEx::CharacterMurder();
}

void MonsterProtectedEx::ProcessProtectedDeath()
{
    GamePlayer* pMaster = GetMasterPlayer();
    if ( pMaster != NULL )
    {
        pMaster->ResetLostProtectCharData();

        // ����󶨵ļ�������
        if ( GetVarID() != -1 )
        { pMaster->SetVar( GetVarID(), 0 ); }
    }
}

void MonsterProtectedEx::OnDeath()
{
    // ��������
    ProcessProtectedDeath();

    MonsterBaseEx::OnDeath();
}

bool MonsterProtectedEx::CheckAddViewEnmity( EnmityData& xEnmityData, BaseCharacter* pChar )
{
    // �����ͻ��͹ֲ�Ҫ���ֳ��
    return false;
}

void MonsterProtectedEx::ProcessEndAttackStatus()
{
    MonsterBaseEx::ProcessEndAttackStatus();

    // ����״̬ �ƶ����������
    SetAiStatus( AiDefine::ThinkingMoveToMaster );
}
