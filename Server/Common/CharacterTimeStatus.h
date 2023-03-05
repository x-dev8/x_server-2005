/********************************************************************
	Filename: 	CharacterTimeStatus.h
	MaintenanceMan Mail: Luo_157@hotmail.com
*********************************************************************/

#ifndef __CHARACTERTIMESTATUS_H__
#define __CHARACTERTIMESTATUS_H__

#pragma once

#include "MeRTLibsServer.h"
#include "GameTime.h"
#include "GameTimer.h"
#include "FuncPerformanceLog.h"

class CharacterTimeStatus 
{  // �д�ʱ�䳬ʱ�Ľ�ɫ״̬
public:
    enum EFilterStatus
    { // ״̬����
        efs_Normal,             // ����״̬�� �������ƶ���
        efs_CanNotNormalAttack, // ��������ͨ����
        efs_ActionTime,         // ������ĪЩ��������ʱ��(��ʱ�䣬�����ƶ�������һ���ƶ���ȡ���ö���)
        efs_ReliveTime,         // ������ȴ�����״̬
        efs_StatusMax,
    };    
    
    uint32        m_nHoldTime   ; // ս����ʱ
	EFilterStatus m_fsExtend    ; // ��չ״̬����չ��ʱ��
	GameTimer     m_fsExtendTimers[efs_StatusMax];

public:
    CharacterTimeStatus(); // ��ʼ������    
    void Process();        // ������
    
    BOOL IsNormal()             { return m_fsExtend == efs_Normal;}             // �Ƿ�������״̬

    BOOL  IsCannotNormalAttack() { return m_fsExtend == efs_CanNotNormalAttack;} // �Ƿ��ǲ�����ͨ����״̬
	BOOL  IsCannotNormalAttackDone()      { return m_fsExtendTimers[efs_CanNotNormalAttack].IsTimerDone();}
    DWORD GetCannotNormalAttackLeftTime() { return m_fsExtendTimers[efs_CanNotNormalAttack].TimeLeft(); }

    BOOL IsReliveTime()         { return m_fsExtend == efs_ReliveTime;}         // �Ƿ�Ϊ����״̬
	BOOL IsReliveDone()		    { return m_fsExtendTimers[efs_ReliveTime].IsTimerDone();}

    BOOL IsActionTime()         { return m_fsExtend == efs_ActionTime;}         // �ж��Ƿ�����Ī��������״̬
	BOOL IsActionDone()		    { return m_fsExtendTimers[efs_ActionTime].IsTimerDone();}

    void EnterNormalStatus(){ m_fsExtend = efs_Normal; } // ��������״̬    
    void EnterCanNotNormalAttack( DWORD dwDelay );       // ���벻����ͨ����״̬
    void EnterActionStatus( DWORD dwDelay );             // ������Ī��������״̬
    void EnterReliveTime( DWORD dwDelay );               // ����ȴ�����״̬
	void ExtendActionStatusTime( int nExtendPercent );

    uint32 GetNormalAttackHoldTime() { return m_nHoldTime; }
};

inline void CharacterTimeStatus::EnterCanNotNormalAttack( DWORD dwDelay ) // ���벻����ͨ����״̬
{
    m_nHoldTime = dwDelay;
    m_fsExtend  = efs_CanNotNormalAttack;
    m_fsExtendTimers[m_fsExtend].Start(dwDelay);
}

inline void CharacterTimeStatus::EnterActionStatus( DWORD dwDelay ) // ������Ī��������״̬
{
    m_fsExtend = efs_ActionTime;
    m_fsExtendTimers[m_fsExtend].Start(dwDelay);
}

inline void CharacterTimeStatus::EnterReliveTime( DWORD dwDelay ) // ����ȴ�����״̬
{
    m_fsExtend = efs_ReliveTime;
    m_fsExtendTimers[m_fsExtend].Start(dwDelay);
}

inline void CharacterTimeStatus::ExtendActionStatusTime( int nExtendPercent )
{
	m_fsExtendTimers[efs_ActionTime].BackupTime( nExtendPercent );
}
#endif // __CHARACTERTIMESTATUS_H__
