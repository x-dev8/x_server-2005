#ifndef __MONSTERPROTECTED_H__
#define __MONSTERPROTECTED_H__

/********************************************************************
            保护怪, 不可攻击, 可移动
            Filename:     MonsterProtected.h
            MaintenanceMan Mail: lori227@live.cn
*********************************************************************/
#include "MonsterBaseEx.h"

class MonsterProtectedEx : public MonsterBaseEx, INHERIT_POOL_PARAM( MonsterProtectedEx, 10 )
{
public:
    DECLARE_POOL_FUNC( MonsterProtectedEx )

    MonsterProtectedEx();
    virtual ~MonsterProtectedEx();

    // 初始化
    virtual void Initialize( ItemDefine::SMonster* pConfig, MonsterCreateData& xCreateData, GamePlayer* pPlayer = NULL );

    GameObjectId GetMasterID() { return m_nMasterID; }
    void SetMasterID( GameObjectId nValue ) { m_nMasterID = nValue; }

	bool IsCanRide() const { return mIsCanRide; }
	void SetIsCanRide(bool b) { mIsCanRide = b; }

    int GetVarID() { return m_nVarID; }
    void SetVarID( int nValue ) { m_nVarID = nValue; }

    // 保护怪自杀
    void CharacterMurder();

    // 第一眼印象
    virtual Msg* FirstSightOnMe( char* szMsgBuffer, unsigned int nBuffSize ); 

    // 死亡
    virtual void OnDeath();       

protected:
    // 怪物思考逻辑
    virtual uint8 AiThinking( uint32 nCurrentTime );

    // 获得怪物思考时间
    virtual int GetThinkingSpaceTime();

    // 处理保护怪死亡, 消失后清除主人的信息
    void ProcessProtectedDeath();

    // 判断是否能攻击
    uint8 CheckCanAttackResult( BaseCharacter* pTarget ) { return CheckAttack::CanNotAttack; }

    // 是否能加视野仇恨
    virtual bool CheckAddViewEnmity( EnmityData& xEnmityData, BaseCharacter* pChar );

    // 处理锁定目标
    void ProcessFindAttackTarget(){};

    // 结束战斗状态
    void ProcessEndAttackStatus();

private:
    // 主人的ID
    GameObjectId m_nMasterID;

	// 能否骑
	bool mIsCanRide;

    // 绑定的记数变量ID
    int m_nVarID;
};

#endif