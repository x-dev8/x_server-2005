#ifndef __MONSTERRESOURCE_H__
#define __MONSTERRESOURCE_H__

/********************************************************************
            ��Դ��, ���ܻ��ƶ�, ���ɹ���( һ�������� )
            Filename:     MonsterResource.h
            MaintenanceMan Mail: lori227@live.cn
*********************************************************************/
#include "MonsterBaseEx.h"

class MonsterResource : public MonsterBaseEx, INHERIT_POOL_PARAM( MonsterResource, 100 )
{
public:
    DECLARE_POOL_FUNC( MonsterResource )

    MonsterResource();
    virtual ~MonsterResource(){};

    // �ж��Ƿ�����Դ��
    virtual bool IsResourceMonster() { return true; }

protected:
    virtual void ProcessAiLogic( uint32 nCostTime );
};

#endif