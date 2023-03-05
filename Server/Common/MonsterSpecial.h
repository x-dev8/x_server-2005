#ifndef __MONSTERSPECIAL_H__
#define __MONSTERSPECIAL_H__

/********************************************************************
            专属怪, 可移动, 可攻击
            Filename:     MonsterSpecial.h
            MaintenanceMan Mail: lori227@live.cn
*********************************************************************/
#include "MonsterBaseEx.h"

class MonsterSpecial : public MonsterBaseEx, INHERIT_POOL_PARAM( MonsterSpecial, 100 )
{
public:
    DECLARE_POOL_FUNC( MonsterSpecial )

    MonsterSpecial();
    virtual ~MonsterSpecial(){};

    // 初始化
    virtual void Initialize( ItemDefine::SMonster* pConfig, MonsterCreateData& xCreateData, GamePlayer* pPlayer = NULL );

    // 判断是否能攻击
    virtual uint8 CheckCanAttackResult( BaseCharacter* pTarget );

    void SetSpecialType( int nValue ) { m_nSpceialType = nValue; }
    int GetSpecialType() const { return m_nSpceialType; }

    void SetSpecialValue ( uint32 nValue ) { m_nSpecialValue = nValue; }
    uint32 GetSpecialValue() const { return m_nSpecialValue; }

    bool CheckSpecialTarget( int nSpecialType, GamePlayer* pTarget );

protected:

    // 刷新仇恨
    void ProcessRefreshEnmity( uint32 nCurrentTime );

    // 调用死亡脚本
    void ProcessDeathCallScript();

    // 处理怪物掉落
    virtual void ProcessDeathDromItem();

protected:
    // 专属类型
    int m_nSpceialType;

    // 专属值
    uint32 m_nSpecialValue;
};

#endif