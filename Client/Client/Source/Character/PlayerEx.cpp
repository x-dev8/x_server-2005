#include <assert.h>
#include "Player.h"
#include "PlayerEX.h"
#ifndef WARNING_FOR_CLIENT
#define WARNING_FOR_CLIENT
#endif
#include "g_assert.h"

#include "FuncPerformanceLog.h"


//--------------------------------------------------------------------------------------
//
//--------------------------------------------------------------------------------------
//---
//判断该状态能否被其他的状态直接打断
//---
bool    CPlayerStatus::IsStateCanBreak(void)
{

	guardfunc;
    switch (m_skRecord)
    {
    case esk_Null:           // 空
    case esk_Idle:           // 待机状态，无任何操作，等待指令。
//    case esk_Walk:           // 行走移动状态	
    
	case esk_PickItem:       // 捡取道具
	case esk_DropItem:		 // 丢弃道具
	case esk_Talk:           // 对话
	case esk_Trade:          //交易
        return true;
        break;

	case esk_Intonate:		 // 呤唱
	case esk_HoldSkill:		 // 持续技能	


	case esk_PreIntonate:


    case esk_PreAttack:      // 预备攻击状态
    case esk_Attack:         // 攻击状态
    //case esk_BeAttack:       // 受击状态
    //case esk_BeatBack:       // 击退处理
    case esk_Miss:           // 闪避状态
    case esk_Sleep:          // 昏倒状态
    case esk_Die:            // 死亡状态
	case esk_ActionTime:	 //在一段时间内作莫个动作
        return false;
        break;
    }
    //
    return  false;
	unguard;
}
//--------------------------------------------------------------------------------------
//
//--------------------------------------------------------------------------------------
CStatusTimer::CStatusTimer()
{
	guardfunc;
    m_bDone         = true;
    m_dwStartTime   = 0;
    m_dwDelayTime   = 0;
    m_CurStatus     = CPlayerStatus::esk_Null;
    m_NextStatus    = CPlayerStatus::esk_Null;
	unguard;
}

void CStatusTimer::Start(DWORD Delay, CPlayerStatus::STATUS_KEY CurKey, CPlayerStatus::STATUS_KEY NextKey)
{
	guardfunc;
    m_dwStartTime = HQ_TimeGetTime();
	m_NextStatus = NextKey;
    m_dwDelayTime = Delay;
    m_bDone = false;
	unguard;
}

bool CStatusTimer::TestTimerDone()
{
	guardfunc;
    // 如果延迟为负数，则为无限时间
    if( m_dwDelayTime == NoLimitDelay )
        return false;
	if( m_bDone )
		return true;
	if( HQ_TimeGetTime() - m_dwStartTime >= m_dwDelayTime )
	{
		m_bDone = true;
	}
	return m_bDone;
	unguard;
}

CPlayerStatus::STATUS_KEY CStatusTimer::GetDoneStatus()
{
	guardfunc;
    if(m_bDone)
        return m_NextStatus;
    else
        return m_CurStatus;
	unguard;
}


void CPlayerEx::LinkPlayer( CPlayer* player )
{
	guardfunc;
    assert(player);
    ThePlayer = player; 
	unguard;
}

CPlayerEx::CPlayerEx()
{
	guardfunc;
    m_bDead         = false;
    // 设置为待机状态
    m_CurStatus.SetStatus( CPlayerStatus::esk_Idle );
    // 启动初始主状态计时器
    m_StatusTimer.Start( CStatusTimer::NoLimitDelay, CPlayerStatus::esk_Idle, CPlayerStatus::esk_Idle );
	unguard;
}

void CPlayerEx::SwitchStatus( CPlayerStatus::STATUS_KEY CurKey, DWORD Delay, CPlayerStatus::STATUS_KEY NextKey )
{
	guardfunc;
    // << >> 重新加入人物时可以看到由消息
	m_StatusStartTime = HQ_TimeGetTime();//取得该状态的开始时间
    if( CurKey == CPlayerStatus::esk_Die )
    {
        m_bDead = true;
    }
    // 设置状态
    m_CurStatus.SetStatus( CurKey );
    // 启动计时
    m_StatusTimer.Start( Delay, CurKey, NextKey );
	unguard;
}
BOOL CPlayerEx::IsTimerDone(void)
{
	guardfunc;
	if (m_StatusTimer.TestTimerDone())
		return TRUE;
	//
	return FALSE;
	unguard;
}

BOOL CPlayerEx::IsDead()
{

	guardfunc;
    return m_bDead;
	unguard;
}

void CPlayerEx::ResetDead()
{
	guardfunc;
    m_bDead = false; 
	//m_CurStatus.SetStatus(m_StatusTimer.GetDoneStatus());
	// 所有计时性的动作结束后，立即进入待机状态(Idle)。
	m_StatusTimer.Start( CStatusTimer::NoLimitDelay, CPlayerStatus::esk_Revive, CPlayerStatus::esk_Revive );
	unguard;
}

void CPlayerEx::ProcessStatus()
{
	guardfunc;
	if (m_CurStatus.GetStatus() <= CPlayerStatus::esk_Null ||  
		m_CurStatus.GetStatus() >=  CPlayerStatus::esk_undefined)
	{
		assert( false && "status is invalid" );
	}


	bool Change2IdleFlag = true;

    //////////////////////////////////////////////////////////////////////////
    // 主状态处理部分

    // 检测计时器
    if(m_StatusTimer.TestTimerDone())
    {
		// 这里是一些校验
		switch( m_CurStatus.GetStatus() )
		{
		//case CPlayerStatus::esk_Intonate:
		//	break;
		case CPlayerStatus::esk_PreAttack:
			break;
		// 攻击状态完成，需要清空目标列表
		case CPlayerStatus::esk_Attack:
			{

			}
			break;
		// 死亡动画播放完成以后
		case CPlayerStatus::esk_Die:
			{
				if (!ThePlayer->IsPlayer() 
					) // 玩家是不会dead over的...
				{
					ThePlayer->SetDeadOver( true );
					ThePlayer->SetDeadOverTime( HQ_TimeGetTime() );
					//	
					ThePlayer->Release();
				}
				else
				{
					Change2IdleFlag = false;
				}
			}
			break;
		}
		if (Change2IdleFlag)
		{
			m_CurStatus.SetStatus(m_StatusTimer.GetDoneStatus());
			// 所有计时性的动作结束后，立即进入待机状态(Idle)。
			m_StatusTimer.Start( CStatusTimer::NoLimitDelay, CPlayerStatus::esk_Idle, CPlayerStatus::esk_Idle );
		}
    }
	unguard;
}

//记录战斗硬直时间
void	CPlayerEx::StartFightHoldTime(DWORD dwTime)
{
	guardfunc;
	m_FightHoldTimer.Start(dwTime);
	unguard;
}
//判断战斗硬直时间是否结束
BOOL	CPlayerEx::IsFightHoldTimeOver(void)
{
	guardfunc;
	return m_FightHoldTimer.IsTimerDone();
	unguard;
}

//---------------------------------------------------------------------------
//	End.
//---------------------------------------------------------------------------