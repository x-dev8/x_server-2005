#ifndef __MONSTERPET_H__
#define __MONSTERPET_H__

/********************************************************************
            宠物基类
            Filename:     MonsterPetEx.h
            MaintenanceMan Mail: lori227@live.cn
*********************************************************************/
#include "MonsterBaseEx.h"

class MonsterPetEx : public MonsterBaseEx
{
public:
    enum EPetDeathType
    {
        EPetDeathType_BeKilled, // 被杀
        EPetDeathType_Murder,   // 自杀
    };

public:
    MonsterPetEx();
    virtual ~MonsterPetEx(){};
    
    // 初始化
    virtual void Initialize( ItemDefine::SMonster* pConfig, MonsterCreateData& xCreateData, GamePlayer* pPlayer = NULL );

    virtual bool IsPet() { return true; }

    uint8 GetPetType() const { return m_nPetType; }

    GameObjectId GetMasterID() { return m_nMasterID; }
    void SetMasterID( GameObjectId nValue ) { m_nMasterID = nValue; }

    // 待机移动速度
    virtual float GetIdleMoveSpeed() { return m_fIdleMoveSpeed; }
    void SetIdleMoveSpeed(float fValue) { m_fIdleMoveSpeed = fValue; }

    // 追击或跑回移动速度
    void SettAttackMoveSpeed( float fValue ){ m_fAttackMoveSpeed = fValue; }
    virtual float GetAttackMoveSpeed() { return m_fAttackMoveSpeed; }

    // 宠物怪自杀
    virtual void CharacterMurder();

    // 第一眼印象
    virtual Msg* FirstSightOnMe( char* szMsgBuffer, unsigned int nBuffSize ); 

    // 死亡
    virtual void OnDeath();      

    virtual void CalcEnmity( BaseCharacter* pTarget, const ItemDefine::SItemSkill* pSkillConfig, int nDamage );

protected:

    // 刷新怪物仇恨
    virtual void ProcessRefreshEnmity( uint32 nCurrentTime );

    // 查找攻击目标
    virtual void ProcessFindAttackTarget();

    // 判断是否能攻击
    virtual uint8 CheckCanAttackResult( BaseCharacter* pTarget );

    // 进入视野加入仇恨列表
    virtual void ProcessEnterSightEnmity( BaseCharacter* pTarget );

    // 获得怪物思考时间
    virtual int GetThinkingSpaceTime();

    // 怪物思考逻辑
    virtual uint8 AiThinking( uint32 nCurrentTime );

    // 处理宠物死亡, 消失后清除主人的信息
    virtual void ProcessPetDeath( int deathType ) ;

    // 结束战斗状态
    virtual void ProcessEndAttackStatus();

    // 待机
    virtual void ProcessIdle();

protected:
    uint8 m_nPetType;

    // 主人的ID
    GameObjectId m_nMasterID;

    // 攻击,平时的移动速度
    float m_fAttackMoveSpeed; 

    // 空闲移动速度
    float m_fIdleMoveSpeed; 
};

#endif