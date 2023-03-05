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
//�жϸ�״̬�ܷ�������״ֱ̬�Ӵ��
//---
bool    CPlayerStatus::IsStateCanBreak(void)
{

	guardfunc;
    switch (m_skRecord)
    {
    case esk_Null:           // ��
    case esk_Idle:           // ����״̬�����κβ������ȴ�ָ�
//    case esk_Walk:           // �����ƶ�״̬	
    
	case esk_PickItem:       // ��ȡ����
	case esk_DropItem:		 // ��������
	case esk_Talk:           // �Ի�
	case esk_Trade:          //����
        return true;
        break;

	case esk_Intonate:		 // �ʳ�
	case esk_HoldSkill:		 // ��������	


	case esk_PreIntonate:


    case esk_PreAttack:      // Ԥ������״̬
    case esk_Attack:         // ����״̬
    //case esk_BeAttack:       // �ܻ�״̬
    //case esk_BeatBack:       // ���˴���
    case esk_Miss:           // ����״̬
    case esk_Sleep:          // �赹״̬
    case esk_Die:            // ����״̬
	case esk_ActionTime:	 //��һ��ʱ������Ī������
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
    // ����ӳ�Ϊ��������Ϊ����ʱ��
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
    // ����Ϊ����״̬
    m_CurStatus.SetStatus( CPlayerStatus::esk_Idle );
    // ������ʼ��״̬��ʱ��
    m_StatusTimer.Start( CStatusTimer::NoLimitDelay, CPlayerStatus::esk_Idle, CPlayerStatus::esk_Idle );
	unguard;
}

void CPlayerEx::SwitchStatus( CPlayerStatus::STATUS_KEY CurKey, DWORD Delay, CPlayerStatus::STATUS_KEY NextKey )
{
	guardfunc;
    // << >> ���¼�������ʱ���Կ�������Ϣ
	m_StatusStartTime = HQ_TimeGetTime();//ȡ�ø�״̬�Ŀ�ʼʱ��
    if( CurKey == CPlayerStatus::esk_Die )
    {
        m_bDead = true;
    }
    // ����״̬
    m_CurStatus.SetStatus( CurKey );
    // ������ʱ
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
	// ���м�ʱ�ԵĶ��������������������״̬(Idle)��
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
    // ��״̬������

    // ����ʱ��
    if(m_StatusTimer.TestTimerDone())
    {
		// ������һЩУ��
		switch( m_CurStatus.GetStatus() )
		{
		//case CPlayerStatus::esk_Intonate:
		//	break;
		case CPlayerStatus::esk_PreAttack:
			break;
		// ����״̬��ɣ���Ҫ���Ŀ���б�
		case CPlayerStatus::esk_Attack:
			{

			}
			break;
		// ����������������Ժ�
		case CPlayerStatus::esk_Die:
			{
				if (!ThePlayer->IsPlayer() 
					) // ����ǲ���dead over��...
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
			// ���м�ʱ�ԵĶ��������������������״̬(Idle)��
			m_StatusTimer.Start( CStatusTimer::NoLimitDelay, CPlayerStatus::esk_Idle, CPlayerStatus::esk_Idle );
		}
    }
	unguard;
}

//��¼ս��Ӳֱʱ��
void	CPlayerEx::StartFightHoldTime(DWORD dwTime)
{
	guardfunc;
	m_FightHoldTimer.Start(dwTime);
	unguard;
}
//�ж�ս��Ӳֱʱ���Ƿ����
BOOL	CPlayerEx::IsFightHoldTimeOver(void)
{
	guardfunc;
	return m_FightHoldTimer.IsTimerDone();
	unguard;
}

//---------------------------------------------------------------------------
//	End.
//---------------------------------------------------------------------------