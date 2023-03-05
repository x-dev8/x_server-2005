/********************************************************************
    Filename:    NpcFight.h
    MaintenanceMan Mail: Luo_157@hotmail.com
*********************************************************************/

#ifndef __COMMON_NPCFIGHT_H__
#define __COMMON_NPCFIGHT_H__

#pragma once

#include "NpcBase.h"
#include "AiBaseTask.h"

class NpcFight : public NpcBase, public DNpcFightChar,
                 INHERIT_POOL_PARAM( NpcFight, gNpcPoolBatchSize )
{
public:
    enum EConstDefine
    {
        ECD_SkillInfoMaxSize = 3,
    };

    struct SSkillInfo
    {
        uint16 m_iSkillId                ; // 技能Id
        int8   m_stSkillLevel            ; // 技能等级
        uint8  m_stSkillRate             ; // 每个技能的概率
        uint32 m_dwSkillStartColdDownTime; // 技能组的开始ColdDown时间
        uint32 m_dwSkillColdDownTime     ; // 技能组的ColdDown时间
    };

public:
    DECLARE_POOL_FUNC( NpcFight )

    NpcFight();
    virtual ~NpcFight(){}

    virtual uint32 Init();

    //////////////////////////////////////////////////////////////////////////
    // IBaseCharProperty
    virtual SCharFightAttr* GetCharFightAttr(){ return &_baseProperty.fightAttr; }
    virtual void            SetHPMax( uint32 hpMax );
    virtual uint32          GetHPMax();
    virtual void            SetMPMax( uint32 mpMax );
    virtual uint32          GetMPMax();
    virtual float           GetMoveSpeed()              { return GetCharFightAttr()->moveSpeed.final; }
    virtual void            SetMoveSpeed( float fMove ) { GetCharFightAttr()->moveSpeed.base = fMove; GetCharFightAttr()->moveSpeed.UpdateFinal(); }

    //////////////////////////////////////////////////////////////////////////
    // NpcBase    
    virtual void         EnterMySight( BaseCharacter* pWho );   // 玩家进入FightNpc视野
    virtual void         ExitMySight ( BaseCharacter* pWho );   // 玩家离开FightNpc视野
    virtual void         ProcessLogicBeforeProcessMsg( DWORD dwCostTime, bool& bContinue ); // 在处理消息前调用
    virtual void         Run( DWORD dwCostTime );
    virtual bool         IsCanAttack( BaseCharacter* pTarget );
    virtual void         OnDeath();
    virtual void         CallDeadScript(); // 执行死亡脚本
    virtual void         ClearTryToAttackCharId();
    virtual void         ClearTryToAttackCharEnmity();
    virtual unsigned int AddAttackCharacter( GameObjectId charId );
    virtual unsigned int DecAttackCharacter( GameObjectId charId );
    virtual unsigned int GetEnmityRate(){ return m_nEnmityRate;}
    virtual unsigned int GetViewEnmity()  { return _nViewEnmity; }
    virtual bool         IsPassiveAttack(){ return m_bPassive; } // 是否是被动攻击
    virtual int          GetViewSight() { return m_iViewSight; } // 获得当前视野
    virtual bool         IsInBaseEnmityRange();
    virtual GameObjectId       GetTryToAttackCharId()        { return _tryToAttackCharId;        }
    virtual void				SetTryToAttackCharId( GameObjectId nID )   { _tryToAttackCharId = nID;         }    
    virtual uint32       GetTryAttackCharEnmity()             { return _tryToAttackCharEnmity;    }
    virtual void         SetAttackCharEnmity( uint32 nEnmity) { _tryToAttackCharEnmity = nEnmity; }

    //////////////////////////////////////////////////////////////////////////
    // AI
    void           ChangeMoveSpeed( float speed );
    bool           IsAIStartUp(){ return _bAIRun; }
    void           StartUpAI()  { _bAIRun = true; } // 开启怪物AI
    void           RestoreHPInstant( int nRestoreHP ); // 瞬间回血
    void           RestoreMPInstant( int nRestoreMP ); // 瞬间回魔    
    void           Relive();

    void           SetIdleMoveViewSight( short sight ){ m_stIdleMoveViewSight = sight; } // 设置空闲移动时的视野
    short          GetIdleMoveViewSight()             { return m_stIdleMoveViewSight;  } // 获得空闲移动时的视野
    void           SetFightViewSight( short sight )   { m_stFightViewSight = sight;    }
    short          GetFightViewSight()                { return m_stFightViewSight;     }
    void           SetViewSight( int sight )          { m_iViewSight = sight;          } // 设置当前视野

    bool           HaveTryToAttackCharId()              { return _tryToAttackCharId != InvalidGameObjectId;}

    void           LockTarget( GameObjectId nMaxEnmityCharId );  // 锁定目标
    void           LostAttackTarget();  // 丢失攻击目标

    void           SetCanAttackCharId( GameObjectId charId ) { canAttackCharId = charId;                       } // 设置攻击目标
    void           ClearCanAttackCharId()              { canAttackCharId = InvalidGameObjectId;         }
    uint16         GetCanAttackCharId()                { return canAttackCharId;                         } // 获取攻击目标
    bool           HaveCanAttackCharId()               { return canAttackCharId != InvalidGameObjectId; } // 是否有攻击目标
    BaseCharacter* GetCanAttackChar(); // 获得攻击目标  

    bool           IsInRange(); // 最否在追击范围

    bool           IsAICanAttack( BaseCharacter* pChar ); // 目标是否可攻击

    void           SetPassiveAttack( bool bPassive ) { m_bPassive = bPassive; } // 设置为被动攻击

    void           SendVerifyPos( float x, float y );
    void           SendClosingToTarget( GameObjectId nTargetID, D3DXVECTOR3 vNextPos );

    int            GetCurSkill()             { return m_iCurSkillId;     } // 获得当前技能
    short          GetCurSkillLevel()        { return m_stCurSkillLevel; } // 获得当前技能的等级
    int            GetCurSkillIndex();              // 获取当前使用技能的索引    

    void           SetCurSkillIndex( int i );       // 设置当前使用技能栏
    void           SetCurSkillLevel( uint8 index ); // 设置当前使用的技能等级

    bool           IsHaveMoveAbility(); // 是否有移动的能力
    bool           IsBeginPosMove(); // 是否有目标点

    void           SetDeadScript( const char* szScriptName ){ m_strDeadScriptName = szScriptName; } // 设置死亡脚本名
    const char*    GetDeadScript(){ return m_strDeadScriptName.c_str(); }              // 获得死亡脚本名

    void           SetMoveRange     ( int maxRange )                   { nMaxRange = maxRange;                  }
    void           SetChangePassive ( uint8 nChangePassive )           { changePassiveConfig = nChangePassive;  }
    void           SetEndPassiveTime( uint32 nEndPassiveTime )         { endPassiveTimeConfig = nEndPassiveTime;}
    void           SetBornPoint( SFPos2 ptBorn )                       { m_ptBornPoint = ptBorn;                }
    void           SetBaseEnmityRange( int nBaseEnmityRange )          { m_nBaseEnmityRange = nBaseEnmityRange; }
    void           SetAttackRange( uint16 attackMin, uint16 attackMax ){ normalAttackMin = attackMin; normalAttackMax = attackMax; }
    void           SetNormalMoveSpeed( float fNormalMoveSpeed )        { m_fNormalMoveSpeed = fNormalMoveSpeed; }
    void           SetIdleMoveSpeed  ( float fIdleMoveSpeed   )        { m_fIdleMoveSpeed = fIdleMoveSpeed; }    
    void           SetSkillRateTotal();              // 设置随机会要用的总技能概率
    void           SetEnmityRate( unsigned int nEnmity) { m_nEnmityRate = nEnmity;}
    void           SetViewEnmity( unsigned int nEnmity) { _nViewEnmity = nEnmity; }
    void           SetSkillColdDown();

    // 路径逻辑
    void           ClearOutOfRouteRecord();
    SMovePos*      GetBeginPos();
    SMovePos*      GetMovePos( uint8 step = 1);

protected:
    void           ProcessAIThink()                 ; // 思考
    void           ProcessAISelectTask()            ; // 选择AITask
    void           ProcessAIMove( DWORD dwCostTime ); // 处理AI移动    
    void           ProcessAIDoTask()                ; // 处理AItask
         
    void           ThinkAttack()   ; // 可以产生攻击行为
    void           ThinkIdle()     ; // 可以产生Idle常态行为
    void           ThinkRouteMove(); // 路径移动

    void           MoveAttackMoving( uint32 lapseTime ); // 有攻击目标的移动
    void           MovePosMoving   ( uint32 lapseTime ); // 一般的点目标的移动

    bool           HaveTask(){ return !m_vecNormalTask.empty(); } // 当前是否有任务
    void           AddTask( AiBaseTask* pTask );                  // 增加任务
    void           ClearTask();                                   // 清除任务

    // 攻击目标
    void           AITryAttack();   // 尝试普通攻击
    void           AITryUseSkill(); // 用技能攻击
    void           AIAttack( int iTarget, int iSkill, int iLevel ); // 发出攻击指令

private:
    AITaskContainer m_vecNormalTask;

    bool          _bAIRun                 ; // AI是否开启
    bool          _disableControlThinkTime; // 不要控制思考时间
    uint32        m_dwLastThinkingTime    ; // 上一次Npc思考时间
    int           m_nAiValueWave          ; // 怪物的思考波动
    uint32        m_dwFightViewEndTime    ; // FightView结束时间
    int           m_iViewSight            ; // 视野(可攻击范围)
    short         m_stIdleMoveViewSight   ; // 空闲移动中的视野
    short         m_stFightViewSight      ; // 战斗时的视野
    GameObjectId _tryToAttackCharId      ; // 尝试去攻击目标的Id
    uint32        _tryToAttackCharEnmity  ; // 尝试去攻击目标的Id对应的仇恨
    uint32        m_AttackCharacterCnt    ; // 当前怪物具有仇恨的角色数量
    int           nMaxRange               ; // 活动范围
    float         lastIdleX               ; // 上一次未被攻击时位置X
    float         lastIdleY               ; // 上一次未被攻击时位置Y
    bool          m_bIsFighting           ; // 在战斗状态
    uint8         changePassiveConfig     ; // 战斗时是否成为被动怪被动怪
    bool          bPassiveConfig           ; // 是否被动怪数据
    bool          m_bPassive              ; // 当前的是否被动的状态
    GameObjectId canAttackCharId         ; // 攻击目标
    bool          m_bClosingToTarget      ; // 靠近目标
    bool          _isNeedMove             ; // 是否需要移动
    bool          m_bMoving               ; // 是否在移动
    short         m_stSkillRateTotal      ; // 总概率
    SSkillInfo    skillInfo[ECD_SkillInfoMaxSize]; // 拥有的技能信息
    D3DXVECTOR3   m_vLastSendTargetPos    ; // 最后一次发送的移动目标点
    uint16        m_iCurSkillId           ; // 当前技能
    short         m_stCurSkillLevel       ; // 当前技能等级
    uint8         m_nCurSkillIndex        ; // 当前技能的索引
    CItemDetail::SItemSkill* m_pCurSkill  ; // 当前选择使用的技能
    short         m_stCurAttackRange       ; // 记录当前的攻击距离
    uint8         m_stCurAiTactic          ; // 当前的AI策略
    float         m_fNormalMoveSpeed       ; // 平时的移动速度
    float         m_fIdleMoveSpeed         ; // 空闲移动速度
    int           endPassiveTimeConfig     ; // 战斗结束被动持续时间
    uint32        _endPassiveTimeRecord    ; // 战斗结束被动持续时间纪录    
    D3DXVECTOR3   _moveTargetPos           ; // 制定的目标位置
    uint32        m_dwSendMoveMessageTime  ; // 最近一次发移动中消息的时间
    uint32        m_noMoveSendVerifyPosTime; // 最近一次在不移动的情况下发纠正位置的时间
    std::string   m_strDeadScriptName      ; // 死亡脚本名字
    int           m_nVMId                  ; // 死亡脚本脚本器
    int           m_nBaseEnmityRange       ; // 基础仇恨持续范围
    SFPos2        m_ptBornPoint            ; // 出生点
    SFDir3        _bornDir                 ; // 出生的朝向
    uint16        normalAttackMin          ; // 普通攻击最小系数
    uint16        normalAttackMax          ; // 普通攻击最大系数
    uint32        m_nEnmityRate            ;            
    uint32        _nViewEnmity             ; // 视野触发的仇恨初值
    GameTimerEx   m_xReliveTimer           ; // 死亡复活定时器
    // route
    uint16       _routeId                 ; // routeId
    uint16       _routeStep               ; // 当前到哪一步
    SRoute       _route                   ; // 路点信息
    bool         _bArriveTargetPos        ; // 是否达到目标点
    bool         _bFinalArrive            ; // 最终到达目的地

    bool         _bOutOfRoute             ; // 是否离开了指定的前进路线做其他事去了
};

//////////////////////////////////////////////////////////////////////////
// inline
inline void NpcFight::ClearOutOfRouteRecord()
{
    lastIdleX = 0;
    lastIdleY = 0;
}

inline void NpcFight::SetSkillRateTotal()
{
    m_stSkillRateTotal = skillInfo[0].m_stSkillRate + skillInfo[1].m_stSkillRate + skillInfo[2].m_stSkillRate;
    skillInfo[1].m_stSkillRate = skillInfo[1].m_stSkillRate + skillInfo[0].m_stSkillRate;
    skillInfo[2].m_stSkillRate = skillInfo[2].m_stSkillRate  + skillInfo[1].m_stSkillRate;
}

#endif // __COMMON_NPCFIGHT_H__
