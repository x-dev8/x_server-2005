#ifndef __MONSTERBUILD_H__
#define __MONSTERBUILD_H__

/********************************************************************
            建筑怪, 不能攻击目标, 不能移动
            Filename:     MonsterBuildEx.h
            MaintenanceMan Mail: lori227@live.cn
*********************************************************************/
#include "MonsterBaseEx.h"

class MonsterBuildEx : public MonsterBaseEx, INHERIT_POOL_PARAM( MonsterBuildEx, 20 )
{
public:
    DECLARE_POOL_FUNC( MonsterBuildEx )

    MonsterBuildEx();
    virtual ~MonsterBuildEx(){};

protected:

    // 建筑怪不会移动
    virtual void ProcessAiMoving( uint32 nCostTime ){};

    // 判断是否能攻击
    uint8 CheckCanAttackResult( BaseCharacter* pTarget ) { return CheckAttack::CanNotAttack; }

    // 处理怪物思考
    void ProcessFindAttackTarget(){};

    virtual void ProcessRefreshEnmity( uint32 nCurrentTime );
};

#endif