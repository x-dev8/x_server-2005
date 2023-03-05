#ifndef __NPCFIGHTEX_H__
#define __NPCFIGHTEX_H__
/************************************************************************
                战斗NPC
                Filename:    NpcFightEx.h
                MaintenanceMan Mail: lori227@live.cn
************************************************************************/
#include "NpcBaseEx.h"

class NpcFightEx : public NpcBaseEx, INHERIT_POOL_PARAM( NpcFightEx, 10 )
{
public:
    DECLARE_POOL_FUNC( NpcFightEx )

	enum FightType
	{
		FT_Player, // 只打人
		FT_Monster,// 主动打怪，不主动打人
		FT_Both,   // 都打
	};

    NpcFightEx();
	virtual ~NpcFightEx(){};

    virtual bool IsFightNpc() { return true; }

	//virtual void OnDeath();


    // 判断能否被攻击
    virtual bool CheckCanBeAttack();  

    virtual void Initialize( NpcInfo::Npc* pConfig, GameStage* pStage, bool bAsyn = false );

	int GetFightType() { return m_pNpcInfo->fightData[0].fightType; }

    ////////////////////////////////////////////////////////////////////////
protected:
    // 刷仇恨
    virtual void ProcessRefreshEnmity( uint32 nCurrentTime );

    // 攻击目标
    virtual void ProcessFindAttackTarget();

    // 判断能否攻击目标结果
    virtual uint8 CheckCanAttackResult( BaseCharacter* pTarget );

    // 处理进入视野仇恨
    virtual void ProcessEnterSightEnmity( BaseCharacter* pTarget );

    ///////////////////////////////////////////////////////////////////////////////////
    virtual int GetMaxAttackRange() { return m_pNpcInfo->fightData[0].maxRange; }

    virtual int GetBaseEnmityRange() { return m_pNpcInfo->fightData[0].baseEnmityRange; }

    // 怪物空闲视野范围
    virtual int GetIdleViewSight() { return m_pNpcInfo->fightData[0].view; }

    // 怪物战斗视野范围
    virtual int GetFightViewSight() { return m_pNpcInfo->fightData[0].fightView; }

    // 待机移动速度
    virtual float GetIdleMoveSpeed() { return m_pNpcInfo->fightData[0].idleMoveSpeed; }

    // 追击或跑回移动速度
    virtual float GetAttackMoveSpeed() { return m_pNpcInfo->fightData[0].moveSpeed; }

    // 仇恨衰减比率
    virtual unsigned int GetEnmityRate() { return m_pNpcInfo->fightData[0].enmityDecRate; }

    // 获得视野仇恨
    virtual int GetViewEnmity() { return m_pNpcInfo->fightData[0].enmityView; }

    // 初始朝向
    virtual float GetBornDir() { return m_pNpcInfo->direction; }

	// 获得追击时间
	virtual uint32 GetKeepAttakTime() { return m_pNpcInfo->fightData[0].catchTime; }

	//virtual void OnDeath();
	bool CheckMonsterTpye(int type);

	// 处理视野仇恨
	virtual bool CheckAddViewEnmity( EnmityData& xEnmityData, BaseCharacter* pChar );

};


#endif