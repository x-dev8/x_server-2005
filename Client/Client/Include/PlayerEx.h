#ifndef _PLAYER_EX_H_
#define _PLAYER_EX_H_

#include <windows.h>
#include "FuncPerformanceLog.h"
// ״̬��ʾ�ֻ࣬�ǰ�״̬�ֳ���һ�±�ʾ��
class CPlayerStatus
{
public:
    //.......................
    //��������
    //      �����״̬��ҪӦ����ָnpc��ǰ����ʲô���Ķ���
    //      ��ս��״̬�Ķ����ǲ���ͬ��
    //.......................
    // ״̬����
    enum STATUS_KEY
    {
        esk_Null,           // ��
        esk_Idle,           // ����״̬�����κβ������ȴ�ָ�
//      esk_Walk,			// �����ƶ�״̬
        esk_PickItem,       // ��ȡ����
        esk_DropItem,       // ��������
        esk_Talk,           // �Ի�
        esk_Trade,          // ����
        esk_ChangeDir,      // ת��
        esk_PreAttack,      // Ԥ������״̬
        esk_Attack,         // ����״̬
        esk_Intonate,       // �ʳ�״̬
		
        
		esk_BeAttack,       // �ܻ�״̬
        esk_BeatBack,       // ���˴���
        esk_Miss,           // ����״̬
        esk_Sleep,          // �赹״̬
        esk_Die,            // ����״̬
		esk_ActionTime,		//��һ��ʱ������Ī������


		//   added 2004.08.26
		esk_PreIntonate,	// Ԥ������
		esk_HoldSkill,		// ���ܳ���

		esk_Scabbard,		//�ε����յ�

		esk_ReadyToUseSpecialSkill,		//׼��ʹ�����⼼��
		esk_UseSpecialSkill,			//ʹ�����⼼��

		esk_Revive,          //����״̬

        esk_undefined,      // δ�����
    };

public:
    CPlayerStatus() :
      m_skRecord(esk_Idle)
    {}
    bool    IsStateCanBreak(void);         //�жϸ�״̬�ܷ�������״ֱ̬�Ӵ��
    void SetStatus( STATUS_KEY skRecord )   { m_skRecord = skRecord;    }
    STATUS_KEY GetStatus()                  { return m_skRecord;        }

private:
    // ��ǰ״̬��¼
    STATUS_KEY	m_skRecord;
	//
	struct Target
	{
		int	stDst;	//Ŀ��npc�ı��
		int	x, y;	//Ŀ�������λ��
	} target;					// Ŀ��
	struct Skill
	{
		int iSkillID;			//���ܵı��
		int	iSkillLevel;		//���ܵĵĵȼ�
	}skill;
};
//---
//	RecordTimer
//---
class CRecordTimer
{
public:
	// ��ʼ��ʱ
	void Start(DWORD dwDelay)
	{
		m_dwStartTime = HQ_TimeGetTime();
		m_dwDelayTime = dwDelay;
		m_bStarted = TRUE;
		m_bAlreadyUse = TRUE;
	}
	// ����
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
	// �Ƿ񵹼�ʱ���
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

	//���ü�ʱ����
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

// ״̬��ʱ��
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
    // ʣ��ʱ��
    DWORD TimeLeft()
    {
        if( !m_bDone )
            return m_dwDelayTime-(HQ_TimeGetTime()-m_dwStartTime);
        return CStatusTimer::NoLimitDelay;
    }
    // �ܼ�ʱʱ��
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
// �÷�:

};

class CPlayer;
// ״̬������չ����
class CPlayerEx
{
public:
    // ����״̬
    void ProcessStatus();

    CPlayerEx();
    // ���ӵ�Ψһ�Ķ��󣬹�������
    void LinkPlayer(CPlayer *player);
    // �ı�״̬
    void SwitchStatus(CPlayerStatus::STATUS_KEY CurKey, DWORD Delay, CPlayerStatus::STATUS_KEY NextKey = CPlayerStatus::esk_Idle );
    // ��õ�ǰ״̬
    CPlayerStatus::STATUS_KEY CurStatus() { return m_CurStatus.GetStatus(); }
    BOOL    IsStateCanBreak() {return m_CurStatus.IsStateCanBreak();};
    // ����Ƿ�Ϊ���ƶ���״̬
    BOOL IsDead();
	//
	BOOL IsTimerDone(void);
    // ��������״̬
    void ResetDead();
    // ��ȡ��ʱ��ָ��
    CStatusTimer *GetStatusTimer() { return &m_StatusTimer; }
	//
	DWORD	GetStatusStartTime(void){return m_StatusStartTime;};
	void SetStateExFlag( DWORD dwFlag );
	DWORD GetStateEx(){ return m_dwStateEx; }
	//��¼ս��Ӳֱʱ��
	void	StartFightHoldTime(DWORD dwTime);
	BOOL	IsFightHoldTimeOver(void); //�ж�ս��Ӳֱʱ���Ƿ����
	//
private:
    // Ψһ�����Ķ���
    friend class CPlayer;
    CPlayer *ThePlayer;
    // ״̬��ʱ��
    CStatusTimer    m_StatusTimer;
    // ��ǰ״̬
    CPlayerStatus   m_CurStatus;
	//��״̬��ʼ��ʱ��
	DWORD			m_StatusStartTime;
	//
	//����Ӳֵʱ�������
	CRecordTimer    m_FightHoldTimer;
	//
    bool m_bDead;
	// ����״̬
	DWORD		m_dwStateEx;
};

#endif // _PLAYER_EX_H_
//-------------------------------------------------------------------------
//	End.
//-------------------------------------------------------------------------


