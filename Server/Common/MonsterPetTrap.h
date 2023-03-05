#ifndef __MONSTERPETTRAP_H__
#define __MONSTERPETTRAP_H__

/********************************************************************
            陷阱怪, 不可移动, 可攻击
            Filename:     MonsterPetTrap.h
            MaintenanceMan Mail: lori227@live.cn
*********************************************************************/
#include "MonsterPetEx.h"

class MonsterPetTrap : public MonsterPetEx, INHERIT_POOL_PARAM( MonsterPetTrap, 100 )
{
public:
    DECLARE_POOL_FUNC( MonsterPetTrap )

    MonsterPetTrap();
    virtual ~MonsterPetTrap(){};

    // 初始化
    virtual void Initialize( ItemDefine::SMonster* pConfig, MonsterCreateData& xCreateData, GamePlayer* pPlayer = NULL );

    // 判断是否能攻击
    virtual uint8 CheckCanAttackResult( BaseCharacter* pTarget );

protected:
    // 刷新仇恨
    virtual void ProcessRefreshEnmity( uint32 nCurrentTime );

    // 查找攻击目标
    virtual void ProcessFindAttackTarget();

    // 执行怪物AiTask
    virtual void ProcessAiTask( AiTask* pAiTask );

    // 处理结束战斗状态
    virtual void ProcessEndAttackStatus();

    // 计算仇恨
    virtual void CalcEnmity( BaseCharacter* pCharTarget, const ItemDefine::SItemSkill* pSkillConfig, int nDamage );

    // 处理怪物掉落
    virtual void ProcessDeathDromItem(){};

};

#endif