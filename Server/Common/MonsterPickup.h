#ifndef __GAMESERVER_MONSTERPICKUP_H__
#define __GAMESERVER_MONSTERPICKUP_H__

/********************************************************************
            ʰ��С��, ���ƶ�, �ɹ���
            Filename:     MonsterPickup.h
            MaintenanceMan Mail: lori227@live.cn
*********************************************************************/
#include "MonsterBaseEx.h"
#include "DropCommonItem.h"

class MonsterPickup : public MonsterBaseEx, INHERIT_POOL_PARAM( MonsterPickup, 100 )
{
public:
    DECLARE_POOL_FUNC( MonsterPickup )

    MonsterPickup();
    virtual ~MonsterPickup(){};

    // ��ʼ��
    virtual void Initialize( ItemDefine::SMonster* pConfig, MonsterCreateData& xCreateData, GamePlayer* pPlayer = NULL  );

    // Ӧ��BUFF
    virtual long ApplyBufferStatus( int iStatusID, int iStatusLevel, GameObjectId iMaster, int eventType, int eventValue );

    // ������������Ŀ��
    virtual void ProcessLockTarget( int nTargetID );

protected:

    // ���������������
    virtual void ProcessDeathDromItem();

    // ����������
    virtual void ProcessDropItemPackage( int nDropPackIndex );

    // �����Ai����
    virtual void ClearAiVariable() { return; }

protected:
    DropCommonItem  m_CommonDropItem;
};

#endif