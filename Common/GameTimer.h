#ifndef __GAMESERVER_GATETIMER_H__
#define __GAMESERVER_GATETIMER_H__

/************************************************************************
        一个定时器模板类, 包括处理游戏时间和现实时间
        Filename:     GameTimer.h
        MaintenanceMan Mail: lori227@live.cn
************************************************************************/
#include "TimeEx.h"
#include "GameTime.h"

// 现实时间类型
class RealType
{
public:
    typedef __int64 ValueType ;
    typedef TimeEx ClassType ;
};

// 游戏时间类型
class GameType
{
public:
    typedef unsigned int ValueType ;
    typedef GameTime ClassType ;
};

template< class T >
class TimerEx
{
protected:

    typedef typename T::ValueType ValueType;
    typedef typename T::ClassType ClassType;

public:
    TimerEx() : m_nStartTime( 0 ), m_nSpaceTime( 0 )
    {

    }

    // 计时器是否已经启动
    bool IsStart() const { return m_nStartTime != 0; }

    // 检测是否启动, 并开启下一次
    bool CheckStart( ValueType nCurrentTime )
    {
        if ( !IsStart() )
        { return false; }

        NextTimer( nCurrentTime );
        return true;
    }

    // 检测是否启动, 并停止定时器
    bool CheckStart()
    {
        if ( !IsStart() )
        { return false; }

        StopTimer();
        return true;
    }

    // 计时器启动
    void StartTimer( ValueType nStartTime, ValueType nSpaceTime )
    {
        if ( m_nStartTime == 0 || m_nSpaceTime == 0 )
        {
            SetStartTime( nStartTime );
            SetSpaceTime( nSpaceTime );
        }
    }

    // 下一次计时
    void NextTimer( ValueType nValue ) { SetStartTime( nValue ); }

    // 计时器停止
    void StopTimer() { m_nStartTime = 0; }

    // 设置计时器间隔时间
    void SetSpaceTime( ValueType nValue ) { m_nSpaceTime = nValue; }

    // 是否计时完成( 只计时一次 )
    bool DoneTimer()
    { 
        bool bDone = DoneTimer_();
        if ( bDone )
        { StopTimer(); }

        return bDone;
    }

    // 是否计时完成
    bool DoneTimer( ValueType nCurrentTime )
    {
        bool bDone = DoneTimer_();
        if ( bDone )
        { NextTimer( nCurrentTime ); }

        return bDone;
    }

private:
    // 设置开始时间
    void SetStartTime( ValueType nValue )
    {
        if ( nValue == 0 )
        { nValue = 1; } // 保证开始时间不为0

        m_nStartTime = nValue;
    }

    // 是否计时完成
    bool DoneTimer_()
    { 
        if ( m_nStartTime == 0 )
        { return false; }

        return ClassType::IsPassCurrentTime( m_nStartTime, m_nSpaceTime ); 
    }

private:
    ValueType m_nStartTime;     // 开始时间( 0 表示还未开始 )
    ValueType m_nSpaceTime;     // 间隔时间 
};

typedef TimerEx< GameType > GameTimerEx;    // 游戏时间定时器
typedef TimerEx< RealType > RealTimerEx;    // 现实时间定时器    

//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
class GameTimer
{
public:
    // 开始计时
    void Start( DWORD dwDelay )
    {
        m_dwStartTime = HQ_TimeGetTime();
        m_dwDelayTime = dwDelay;
        m_bStarted    = TRUE;
        m_bAlreadyUse = TRUE;
    }
    // 处理
    void Run()
    {
        if(m_bStarted&&m_bAlreadyUse)
        {
            if( GameTime::IsPassCurrentTime( m_dwStartTime, m_dwDelayTime ) )
            {
                m_bStarted = FALSE;
            }
        }
    }

    // 是否倒计时完成
    BOOL IsTimerDone()
    {
        if( m_bAlreadyUse == TRUE )
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
        return FALSE;
    }

    DWORD TimeLeft()
    {
        if(m_bStarted)
            return m_dwDelayTime-(HQ_TimeGetTime()-m_dwStartTime);
        return 0;
    }

	// 倒退的时间
	void BackupTime( int nBackupPercent )
	{
		if( m_bStarted )
		{
			m_dwStartTime += m_dwDelayTime*nBackupPercent/100;

			if( m_dwStartTime > HQ_TimeGetTime() )
				m_dwStartTime = HQ_TimeGetTime();
		}
	}

    //重置计时器。
    void Reset()
    {
        m_bAlreadyUse = FALSE;
    }

    GameTimer()
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

#endif // __GAMESERVER_GATETIMER_H__
