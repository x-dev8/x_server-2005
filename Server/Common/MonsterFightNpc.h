#ifndef __MONSTERFIGHTNPC_H__
#define __MONSTERFIGHTNPC_H__

/************************************************************************
        ս��npc��, Ҳ��һ�����
        Filename:     MonsterFightNpc.h
        MaintenanceMan Mail: lori227@live.cn
************************************************************************/
#include "MonsterActive.h"

class MonsterFightNpc : public MonsterActive, INHERIT_POOL_PARAM( MonsterFightNpc, 50 )
{
public:

    DECLARE_POOL_FUNC( MonsterFightNpc )

    MonsterFightNpc();
    virtual ~MonsterFightNpc(){};

    virtual void Initialize( CItemDetail::SMonster* pConfig, MonsterCreateData& xCreateData, GamePlayer* pPlayer = NULL );

    // ����ִ�нű�
    virtual bool CanQueryScriptTypeStatus() { return true; }

protected:

    // �������������, �˳���Ϸ����
    virtual void ProcessMonsterDeathExitWorld();

    // ������︴��
    virtual void ProcessMosnterRelive();

protected:
    GameTimerEx m_xReliveTime;  // ��ɱ��֮���ø���
};


#endif