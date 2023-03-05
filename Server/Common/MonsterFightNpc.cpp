#include "MonsterFightNpc.h"

MonsterFightNpc::MonsterFightNpc() : MonsterActive()
{
    SetObjType( Object_NpcFight );
    SetForce( ForceDefine::FightNpcForce );
}

void MonsterFightNpc::Initialize( CItemDetail::SMonster* pConfig, MonsterCreateData& xCreateData, GamePlayer* pPlayer /* = NULL */ )
{
    MonsterBaseEx::Initialize( pConfig, xCreateData, pPlayer );

    // ���ø���ʱ��
    m_xReliveTime.SetSpaceTime( xCreateData.GetReliveTime() * 1000 );
}

void MonsterFightNpc::ProcessMonsterDeathExitWorld()
{
    ClearLockID();
    ClearMoveTargetPoint();
    SetAiStatus( AiDefine::ThinkingWaitRelive );

    // ���ø���ʱ��
    m_xReliveTime.NextTimer( HQ_TimeGetTime() );
}

void MonsterFightNpc::ProcessMosnterRelive()
{
    if ( !m_xReliveTime.DoneTimer() )
    { return; }

    // ����
    SetDead( false );
    SetStatus( CS_IDLE );

    SetHP( GetHPMax() );
    SetHP( GetMPMax() );

    ClearLastIdlePoint();
    SetAiStatus( AiDefine::ThinkingMoveToRoute );

    // ����������ϵ�״̬
    bool bResult = _buffManager.UpdateOnDead();
    if ( bResult )
    {
        _buffManager.ApplyBuffsToChar( GetProfession(), GetCharBaseAttr(), GetCharFightAttr() );  
        SendBuffChanged( NULL );
    }

    MsgCharAttrChanged Change;
    Change.iChangeCount = 0;
    Change.header.stID = GetID();
    Change.AddAttrShortChange( CharAttr_Relive, false );
    Change.AddAttrIntChange( CharAttr_HP, GetHP() );
    Change.AddAttrIntChange( CharAttr_MP, GetMP() );
    Change.CaluLength();
    GettheServer().SendMsgToView( &Change, GetID(), false );

    // ����������
    SetFloatXF( m_xBornPoint.x );
    SetFloatYF( m_xBornPoint.y );
    SendVerifyPointMessage();
}