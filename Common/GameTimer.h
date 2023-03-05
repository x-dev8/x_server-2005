#ifndef __GAMESERVER_GATETIMER_H__
#define __GAMESERVER_GATETIMER_H__

/************************************************************************
        һ����ʱ��ģ����, ����������Ϸʱ�����ʵʱ��
        Filename:     GameTimer.h
        MaintenanceMan Mail: lori227@live.cn
************************************************************************/
#include "TimeEx.h"
#include "GameTime.h"

// ��ʵʱ������
class RealType
{
public:
    typedef __int64 ValueType ;
    typedef TimeEx ClassType ;
};

// ��Ϸʱ������
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

    // ��ʱ���Ƿ��Ѿ�����
    bool IsStart() const { return m_nStartTime != 0; }

    // ����Ƿ�����, ��������һ��
    bool CheckStart( ValueType nCurrentTime )
    {
        if ( !IsStart() )
        { return false; }

        NextTimer( nCurrentTime );
        return true;
    }

    // ����Ƿ�����, ��ֹͣ��ʱ��
    bool CheckStart()
    {
        if ( !IsStart() )
        { return false; }

        StopTimer();
        return true;
    }

    // ��ʱ������
    void StartTimer( ValueType nStartTime, ValueType nSpaceTime )
    {
        if ( m_nStartTime == 0 || m_nSpaceTime == 0 )
        {
            SetStartTime( nStartTime );
            SetSpaceTime( nSpaceTime );
        }
    }

    // ��һ�μ�ʱ
    void NextTimer( ValueType nValue ) { SetStartTime( nValue ); }

    // ��ʱ��ֹͣ
    void StopTimer() { m_nStartTime = 0; }

    // ���ü�ʱ�����ʱ��
    void SetSpaceTime( ValueType nValue ) { m_nSpaceTime = nValue; }

    // �Ƿ��ʱ���( ֻ��ʱһ�� )
    bool DoneTimer()
    { 
        bool bDone = DoneTimer_();
        if ( bDone )
        { StopTimer(); }

        return bDone;
    }

    // �Ƿ��ʱ���
    bool DoneTimer( ValueType nCurrentTime )
    {
        bool bDone = DoneTimer_();
        if ( bDone )
        { NextTimer( nCurrentTime ); }

        return bDone;
    }

private:
    // ���ÿ�ʼʱ��
    void SetStartTime( ValueType nValue )
    {
        if ( nValue == 0 )
        { nValue = 1; } // ��֤��ʼʱ�䲻Ϊ0

        m_nStartTime = nValue;
    }

    // �Ƿ��ʱ���
    bool DoneTimer_()
    { 
        if ( m_nStartTime == 0 )
        { return false; }

        return ClassType::IsPassCurrentTime( m_nStartTime, m_nSpaceTime ); 
    }

private:
    ValueType m_nStartTime;     // ��ʼʱ��( 0 ��ʾ��δ��ʼ )
    ValueType m_nSpaceTime;     // ���ʱ�� 
};

typedef TimerEx< GameType > GameTimerEx;    // ��Ϸʱ�䶨ʱ��
typedef TimerEx< RealType > RealTimerEx;    // ��ʵʱ�䶨ʱ��    

//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
class GameTimer
{
public:
    // ��ʼ��ʱ
    void Start( DWORD dwDelay )
    {
        m_dwStartTime = HQ_TimeGetTime();
        m_dwDelayTime = dwDelay;
        m_bStarted    = TRUE;
        m_bAlreadyUse = TRUE;
    }
    // ����
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

    // �Ƿ񵹼�ʱ���
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

	// ���˵�ʱ��
	void BackupTime( int nBackupPercent )
	{
		if( m_bStarted )
		{
			m_dwStartTime += m_dwDelayTime*nBackupPercent/100;

			if( m_dwStartTime > HQ_TimeGetTime() )
				m_dwStartTime = HQ_TimeGetTime();
		}
	}

    //���ü�ʱ����
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
