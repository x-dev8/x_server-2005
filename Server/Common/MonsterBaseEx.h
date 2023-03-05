#ifndef __MONSTERBASE_H__
#define __MONSTERBASE_H__

/********************************************************************
    Filename:     MonsterBaseEx.h
    MaintenanceMan Mail: lori227@live.cn
*********************************************************************/

#include "AiCharacter.h"
#include "ItemDetail.h"

class MonsterBaseEx : public AiCharacter
{
public:
    // 构造函数
    MonsterBaseEx();

    // 析构函数
    virtual ~MonsterBaseEx();

    // 初始化
    virtual void Initialize( ItemDefine::SMonster* pConfig, MonsterCreateData& xCreateData, GamePlayer* pPlayer = NULL );

    // 执行怪物逻辑
    virtual void Run( uint32 nCostTime );

    // 第一眼印象
    virtual Msg* FirstSightOnMe( char* szMsgBuffer, unsigned int nBuffSize ); 

    // 死亡
    virtual void OnDeath();        

    // 是否是怪物
    virtual bool IsMonster() { return true; }    

    // 判断是否是召唤型宠物
    virtual bool IsSummonPet() { return false; }

    // 保护怪身上绑定的记数变量
    virtual void SetVarID( int nValue ) {}
    virtual int GetVarID() { return -1; }

    // 判断能否被攻击
    virtual bool CheckCanBeAttack();

    // 怪物类型
    virtual uint8 GetMonsterType() const { return m_nMonsterType; }
    void SetMonsterType( uint8 nValue ) { m_nMonsterType = nValue; }

    // 怪物状态类型
    uint8 GetMonsterStatus() const { return m_nMonsterStatus; }
    void SetMonsterStatus( uint8 nValue ) { m_nMonsterStatus = nValue; }
    
    // 怪物产生序列号
    void SetProduceIndex( int nValue ) { m_nProduceIndex = nValue; } 
    int GetProduceIndex() { return m_nProduceIndex; }

    // 处理怪物类型状态改变( 默认参数是按照配置文件变到某个状态, 否则按策划需求改变 )
    void ProcessMonsterStatusChange( int nMonsterStatus );
    
    // 是否能攻击的怪物状态
    bool CanAttackMonsterStatus();

    // 是否是执行脚本的怪物状态
    virtual bool CanQueryScriptTypeStatus();

    virtual void OnEnterFightState();
	virtual void  OnOutFightState();                               // 出战斗状态

    // 获得当前状态脚本入口
    int GetMonsterStatusScriptEnter();

    // 设置怪物消失
    void SetMonsterExit() { m_xTimer[ AiDefine::AiTimer_Disappear ].NextTimer( 1 ); }

    // 道行
    uint32 GetDaoxing() { return m_pMonsterConfig->nDaoxing; }

    //////////////////////////////////////////////////////////////////////////
    // 怪物ID
    int GetMonsterID() { return m_pMonsterConfig->stMonsterId; }
    // 模型ID
    int GetModelID() { return m_pMonsterConfig->iModelID; }
    // 仇恨衰减比率
    unsigned int GetEnmityRate() { return m_pMonsterConfig->nEnmityRate; }
    // 奖励经验
    int GetRewardExp() { return m_pMonsterConfig->nRewardExp; }
    // 奖励技能经验
    int GetRewardSkillExp() { return m_pMonsterConfig->nSuperfluitySkillExp; }
    // 奖励金钱
    int GetRewardMoney() { return m_pMonsterConfig->nCashMoney; }
    // 奖励声望
    int GetRewardReputation() { return m_pMonsterConfig->nRewardReputation; }
    // 奖励功勋
    int GetRewardExpolit() { return m_pMonsterConfig->nRewardExploit; }
    // 奖励好友度
    int GetRewardFriendly() { return m_pMonsterConfig->nRewardFriendly; }
    // 奖励状态
    int GetRewardStatusID() { return m_pMonsterConfig->nRewardStatusID; }
    // 奖励道行
    int GetRewardDaoxing()  { return m_pMonsterConfig->nRewardDaoxing;  }
    // 奖励其他类型
    int GetRewardMulType() { return m_pMonsterConfig->nRewardMulType; }
    // 奖励数值
    int GetRewardMulValue() { return m_pMonsterConfig->nRewardMulValue; }
    // 怪物空闲视野范围
    int GetIdleViewSight() { return m_pMonsterConfig->stView; }
    // 怪物战斗视野范围
    int GetFightViewSight() { return m_pMonsterConfig->stFightView; }

    // 怪物回血间隔
    uint32 GetRestoreSpaceTime() { return m_pMonsterConfig->dwRestoreSpaceTime; }

    // 怪物回血数值
    int GetRestoreHP() { return m_pMonsterConfig->stHPRestore; }

    // 怪物回魔数值
    int GetRestoreMP() { return m_pMonsterConfig->stMPRestore; }

    // 待机移动速度
    float GetIdleMoveSpeed() { return m_pMonsterConfig->fIdleMoveSpeed; }

    // 追击或跑回移动速度
    float GetAttackMoveSpeed() { return m_pMonsterConfig->fMoveSpeed; }

    // 获得怪物的追击范围
    int GetMaxAttackRange() { return m_pMonsterConfig->nMaxRange; }

    // 获得追击时间
    virtual uint32 GetKeepAttakTime() { return m_pMonsterConfig->dwCatchTime; }

    // 获得怪物Idle状态下随即移动概率
    int GetIdleMoveRate() { return m_pMonsterConfig->nIdleMoveRate; }

    // 获得怪物基础仇恨视野范围
    int GetBaseEnmityRange() { return m_pMonsterConfig->nBaseEnmityRange; }

    // 获得视野仇恨
    int GetViewEnmity() { return m_pMonsterConfig->nEnmity; }

    // 获得怪物是否是主动怪
    bool GetActiveMonster() { return m_pMonsterConfig->nIsInitiative != 0; }

    //  怪物的抗性
    int16 GetResistBeMove() { return m_pMonsterConfig->nResistMove; }
    int16 GetResistBeAtt() { return m_pMonsterConfig->nResistAtt; }
    int16 GetResistBeMagic() { return m_pMonsterConfig->nResistMagic; }
    int16 GetResistBeTools() { return m_pMonsterConfig->nResistTools; }

    // 攻击防御系数
    float GetAttackPhysicsMod() { return m_pMonsterConfig->fAttackPhysicsMod; }
    float GetDefendPhysicsMod() { return m_pMonsterConfig->fDefendPhysicsMod; }
    float GetAttackMagicMod()   { return m_pMonsterConfig->fAttackMagicMod;   }
    float GetDefendMagicMod()   { return m_pMonsterConfig->fDefendMagicMod;   }

    virtual const char* GetAILuaScript() const { return m_pMonsterConfig->GetAILuaScript(); }

    void  SetMonsterConfig( ItemDefine::SMonster* pConfig) { m_pMonsterConfig = pConfig; }

    // 浮动攻击之
    short GetAttackFloat() { return 0; }

    // 是否是被动怪
    bool  IsPassivity() { return m_bPassivity; }
    void  SetPassivity( bool bVal ){ m_bPassivity = bVal; }

    // 处理怪物的视野仇恨
    virtual bool CheckAddViewEnmity( EnmityData& xEnmityData, BaseCharacter* pChar );

    // 进入视野加仇恨列表
    virtual void ProcessEnterSightEnmity( BaseCharacter* pTarget );

	// 获取怪物的种族
	virtual unsigned char GetPhyle() const { return m_pMonsterConfig->phyle; }

    // 获取怪物配置
    ItemDefine::SMonster* GetMonsterConfig() const { return m_pMonsterConfig; }

	virtual void WasKilled( BaseCharacter* pKiller );
	virtual void UpdateMonsterBeLong(BaseCharacter* pKiller = NULL);//更新怪物的归属
protected:

    // 判断是否能攻击
    virtual uint8 CheckCanAttackResult( BaseCharacter* pTarget );

    // 查找攻击目标
    virtual void ProcessFindAttackTarget();

    // 处理怪物死亡掉落
    virtual void ProcessDeathDromItem();

    // 处理死亡调用死亡脚本
    void ProcessDeathCallScript();

    // 是否除以可以AI思考的状态
    bool CheckAiThinkingMonsterStatus();

    // 阵营怪物死亡
    virtual void ProcessCampMonsterDeath();

	virtual void ProcessGameBattleMonsterDeath();

    // 处理怪物死亡后怪物状态的改变
    virtual void ProcessDeathChangeStatus();

    // 处理怪物状态改变
    void ProcessMonsterStatusChange();
 
protected:
    // 怪物的配置属性
    ItemDefine::SMonster* m_pMonsterConfig;

    // 怪物产生序列号
    int m_nProduceIndex;

    // 怪物类型
    uint8 m_nMonsterType;

    // 怪物的类型状态( 怪物可以转化成npc之类 )
    uint8 m_nMonsterStatus;

    // 下一个怪物状态
    uint8 m_nNextMosntrStatus;

    // 是否被动怪
    bool m_bPassivity;

	//上次更新归属的时间
	DWORD    m_dwLastBeLongTime;
};

/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
inline bool MonsterBaseEx::CanAttackMonsterStatus()
{
    switch ( GetMonsterStatus() )
    {
    case MonsterDefine::StatusNormal:
    case MonsterDefine::StatusMonster:
        return true;
        break;
    default:
        break;
    }

    return false;
}

inline bool MonsterBaseEx::CanQueryScriptTypeStatus()
{
    switch ( m_nMonsterStatus )
    {
    case MonsterDefine::StatusMoveNpc:
    case MonsterDefine::StatusUnMoveNpc:
    case MonsterDefine::StatusMonsterDeath:
        return true;
        break;
    default:
        break;
    }

    return false;
}

inline bool MonsterBaseEx::CheckAiThinkingMonsterStatus()
{
    switch ( GetMonsterStatus() )
    {
    case MonsterDefine::StatusUnMoveNpc:
    case MonsterDefine::StatusMonsterBorn:
        return false;
        break;
    default:
        break;
    }

    return true;
}

#endif