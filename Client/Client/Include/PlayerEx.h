#ifndef _PLAYER_EX_H_
#define _PLAYER_EX_H_

#include <windows.h>
#include "FuncPerformanceLog.h"
// 状态表示类，只是把状态分出来一下表示。
class CPlayerStatus
{
public:
    //.......................
    //定义增加
    //      这里的状态主要应该是指npc当前在作什么样的动作
    //      和战斗状态的定义是不相同的
    //.......................
    // 状态定义
    enum STATUS_KEY
    {
        esk_Null,           // 空
        esk_Idle,           // 待机状态，无任何操作，等待指令。
//      esk_Walk,			// 行走移动状态
        esk_PickItem,       // 捡取道具
        esk_DropItem,       // 丢弃道具
        esk_Talk,           // 对话
        esk_Trade,          // 交易
        esk_ChangeDir,      // 转身
        esk_PreAttack,      // 预备攻击状态
        esk_Attack,         // 攻击状态
        esk_Intonate,       // 呤唱状态
		
        
		esk_BeAttack,       // 受击状态
        esk_BeatBack,       // 击退处理
        esk_Miss,           // 闪避状态
        esk_Sleep,          // 昏倒状态
        esk_Die,            // 死亡状态
		esk_ActionTime,		//在一段时间内作莫个动作


		//   added 2004.08.26
		esk_PreIntonate,	// 预备吟唱
		esk_HoldSkill,		// 技能持续

		esk_Scabbard,		//拔刀，收刀

		esk_ReadyToUseSpecialSkill,		//准备使用特殊技能
		esk_UseSpecialSkill,			//使用特殊技能

		esk_Revive,          //复活状态

        esk_undefined,      // 未定义的
    };

public:
    CPlayerStatus() :
      m_skRecord(esk_Idle)
    {}
    bool    IsStateCanBreak(void);         //判断该状态能否被其他的状态直接打断
    void SetStatus( STATUS_KEY skRecord )   { m_skRecord = skRecord;    }
    STATUS_KEY GetStatus()                  { return m_skRecord;        }

private:
    // 当前状态记录
    STATUS_KEY	m_skRecord;
	//
	struct Target
	{
		int	stDst;	//目标npc的编号
		int	x, y;	//目标坐标的位置
	} target;					// 目标
	struct Skill
	{
		int iSkillID;			//技能的编号
		int	iSkillLevel;		//技能的的等级
	}skill;
};
//---
//	RecordTimer
//---
class CRecordTimer
{
public:
	// 开始计时
	void Start(DWORD dwDelay)
	{
		m_dwStartTime = HQ_TimeGetTime();
		m_dwDelayTime = dwDelay;
		m_bStarted = TRUE;
		m_bAlreadyUse = TRUE;
	}
	// 处理
	void Run()
	{
		if(m_bStarted&&m_bAlreadyUse)
		{
			if(HQ_TimeGetTime()-m_dwStartTime>=m_dwDelayTime)
			{
				m_bStarted = FALSE;
			}
		}
	}
	// 是否倒计时完成
	BOOL IsTimerDone()
	{
		if( m_bAlreadyUse )
		{
			if( m_bStarted == FALSE )
			{
				m_bAlreadyUse = FALSE;
				return TRUE;
			}
			else
			{
				return FALSE;
			}
		}
		else
		{
			return TRUE;
		}
		//
		return FALSE;
	}

	DWORD TimeLeft()
	{
		if(m_bStarted)
			return m_dwDelayTime-(HQ_TimeGetTime()-m_dwStartTime);
		return -1;
	}

	//重置计时器。
	void Reset()
	{
		m_bAlreadyUse = FALSE;
	}

	CRecordTimer()
	{
		m_bStarted = FALSE;
		m_bAlreadyUse = FALSE;
		m_dwDelayTime = 0;
		m_dwStartTime = 0;
	}
private:
	DWORD m_dwStartTime;
	DWORD m_dwDelayTime;
	BOOL m_bStarted;
	BOOL m_bAlreadyUse;
};

// 状态定时器
class CStatusTimer
{
public:
    enum {
        NoLimitDelay = (DWORD)-1,
    };
    void Start(DWORD Delay, CPlayerStatus::STATUS_KEY CurKey, CPlayerStatus::STATUS_KEY NextKey);
    bool TestTimerDone();
    CPlayerStatus::STATUS_KEY GetDoneStatus();
    CStatusTimer();
    // 剩余时长
    DWORD TimeLeft()
    {
        if( !m_bDone )
            return m_dwDelayTime-(HQ_TimeGetTime()-m_dwStartTime);
        return CStatusTimer::NoLimitDelay;
    }
    // 总计时时长
    DWORD TimeTotal()
    {
        if( !m_bDone )
            return m_dwDelayTime;
        return CStatusTimer::NoLimitDelay;
    }
private:
    DWORD m_dwStartTime;
    DWORD m_dwDelayTime;
    CPlayerStatus::STATUS_KEY m_CurStatus;
    CPlayerStatus::STATUS_KEY m_NextStatus;
    bool m_bDone;
// 用法:

};

class CPlayer;
// 状态控制扩展部分
class CPlayerEx
{
public:
    // 处理状态
    void ProcessStatus();

    CPlayerEx();
    // 连接到唯一的对象，哈哈哈。
    void LinkPlayer(CPlayer *player);
    // 改变状态
    void SwitchStatus(CPlayerStatus::STATUS_KEY CurKey, DWORD Delay, CPlayerStatus::STATUS_KEY NextKey = CPlayerStatus::esk_Idle );
    // 获得当前状态
    CPlayerStatus::STATUS_KEY CurStatus() { return m_CurStatus.GetStatus(); }
    BOOL    IsStateCanBreak() {return m_CurStatus.IsStateCanBreak();};
    // 检测是否为可移动的状态
    BOOL IsDead();
	//
	BOOL IsTimerDone(void);
    // 重置死亡状态
    void ResetDead();
    // 获取计时器指针
    CStatusTimer *GetStatusTimer() { return &m_StatusTimer; }
	//
	DWORD	GetStatusStartTime(void){return m_StatusStartTime;};
	void SetStateExFlag( DWORD dwFlag );
	DWORD GetStateEx(){ return m_dwStateEx; }
	//记录战斗硬直时间
	void	StartFightHoldTime(DWORD dwTime);
	BOOL	IsFightHoldTimeOver(void); //判断战斗硬直时间是否结束
	//
private:
    // 唯一关联的对象
    friend class CPlayer;
    CPlayer *ThePlayer;
    // 状态计时器
    CStatusTimer    m_StatusTimer;
    // 当前状态
    CPlayerStatus   m_CurStatus;
	//该状态开始的时间
	DWORD			m_StatusStartTime;
	//
	//攻击硬值时间计数器
	CRecordTimer    m_FightHoldTimer;
	//
    bool m_bDead;
	// 附加状态
	DWORD		m_dwStateEx;
};

#endif // _PLAYER_EX_H_
//-------------------------------------------------------------------------
//	End.
//-------------------------------------------------------------------------


