#ifndef __MONSTERCONTROLPROTECTED_H__
#define __MONSTERCONTROLPROTECTED_H__

/********************************************************************
            控制型保护怪, 不可攻击, 控制才可移动
            Filename:     MonsterControlProtected.h
            MaintenanceMan Mail: lori227@live.cn
*********************************************************************/
#include "MonsterProtectedEx.h"

class MonsterControlProtected : public MonsterProtectedEx, INHERIT_POOL_PARAM( MonsterControlProtected, 20 )
{
public:
    DECLARE_POOL_FUNC( MonsterControlProtected )

    MonsterControlProtected();
    virtual ~MonsterControlProtected(){};

protected:

private:
    
};

#endif