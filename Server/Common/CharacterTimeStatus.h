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
{  // 有带时间超时的角色状态
public:
    enum EFilterStatus
    { // 状态定义
        efs_Normal,             // 正常状态， 待机，移动等
        efs_CanNotNormalAttack, // 不可以普通攻击
        efs_ActionTime,         // 进入作莫些个动作的时间(该时间，可以移动，不过一旦移动，取消该动作)
        efs_ReliveTime,         // 死亡后等待重生状态
        efs_StatusMax,
    };    
    
    uint32        m_nHoldTime   ; // 战斗延时
	EFilterStatus m_fsExtend    ; // 扩展状态和扩展定时器
	GameTimer     m_fsExtendTimers[efs_StatusMax];

public:
    CharacterTimeStatus(); // 初始化函数    
    void Process();        // 处理函数
    
    BOOL IsNormal()             { return m_fsExtend == efs_Normal;}             // 是否是正常状态

    BOOL  IsCannotNormalAttack() { return m_fsExtend == efs_CanNotNormalAttack;} // 是否是不能普通攻击状态
	BOOL  IsCannotNormalAttackDone()      { return m_fsExtendTimers[efs_CanNotNormalAttack].IsTimerDone();}
    DWORD GetCannotNormalAttackLeftTime() { return m_fsExtendTimers[efs_CanNotNormalAttack].TimeLeft(); }

    BOOL IsReliveTime()         { return m_fsExtend == efs_ReliveTime;}         // 是否为重生状态
	BOOL IsReliveDone()		    { return m_fsExtendTimers[efs_ReliveTime].IsTimerDone();}

    BOOL IsActionTime()         { return m_fsExtend == efs_ActionTime;}         // 判断是否处在作莫个动作的状态
	BOOL IsActionDone()		    { return m_fsExtendTimers[efs_ActionTime].IsTimerDone();}

    void EnterNormalStatus(){ m_fsExtend = efs_Normal; } // 进入正常状态    
    void EnterCanNotNormalAttack( DWORD dwDelay );       // 进入不能普通攻击状态
    void EnterActionStatus( DWORD dwDelay );             // 进入作莫个动作的状态
    void EnterReliveTime( DWORD dwDelay );               // 进入等待重生状态
	void ExtendActionStatusTime( int nExtendPercent );

    uint32 GetNormalAttackHoldTime() { return m_nHoldTime; }
};

inline void CharacterTimeStatus::EnterCanNotNormalAttack( DWORD dwDelay ) // 进入不能普通攻击状态
{
    m_nHoldTime = dwDelay;
    m_fsExtend  = efs_CanNotNormalAttack;
    m_fsExtendTimers[m_fsExtend].Start(dwDelay);
}

inline void CharacterTimeStatus::EnterActionStatus( DWORD dwDelay ) // 进入作莫个动作的状态
{
    m_fsExtend = efs_ActionTime;
    m_fsExtendTimers[m_fsExtend].Start(dwDelay);
}

inline void CharacterTimeStatus::EnterReliveTime( DWORD dwDelay ) // 进入等待重生状态
{
    m_fsExtend = efs_ReliveTime;
    m_fsExtendTimers[m_fsExtend].Start(dwDelay);
}

inline void CharacterTimeStatus::ExtendActionStatusTime( int nExtendPercent )
{
	m_fsExtendTimers[efs_ActionTime].BackupTime( nExtendPercent );
}
#endif // __CHARACTERTIMESTATUS_H__
