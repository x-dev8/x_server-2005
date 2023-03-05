#ifndef __MONSTERRESOURCE_H__
#define __MONSTERRESOURCE_H__

/********************************************************************
            资源怪, 可能会移动, 不可攻击( 一攻击就死 )
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

    // 判断是否是资源怪
    virtual bool IsResourceMonster() { return true; }

protected:
    virtual void ProcessAiLogic( uint32 nCostTime );
};

#endif