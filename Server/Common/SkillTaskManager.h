#ifndef __GAMESERVER_SKILLTASKMANAGER_H__
#define __GAMESERVER_SKILLTASKMANAGER_H__

#pragma once

#include "MeRTLibsServer.h"
#include "GlobalDef.h"
#include "Dxsdk/d3dx9math.h"
#include "GameTimer.h"

struct SSkillTask
{
    enum ESkillTaskType
    {
        STT_SingleSkill,    // 单招技能
        STT_Express,        // 表情动作
        STT_MultiLinkSkill, // 连招技能
        STT_Max,
    };

    SSkillTask()
    { memset( this, 0, sizeof(SSkillTask) ); }

    int   type;        // 类型(技能，还是动作))
    short id;          // 技能的ID
    short level;       // 技能的等级    
    bool  isDone;      // 是否完成
    DWORD state;       // 状态
    DWORD startTime;   // 开始时间
    DWORD balanceTime; // 结算时间
    DWORD holdTime;    // 持续时间
};

class BaseCharacter;

class SkillTaskManager
{
public:
    SkillTaskManager() : _pOwner(NULL) { Clear(); }

    void SetOwner( BaseCharacter* pOwner ) { _pOwner = pOwner; }
    SSkillTask* GetTask( int i );
    SSkillTask* GetCurTask();

    bool HasNewTask( DWORD dwTime );
    bool IsCurTaskDone();
    int  DoneCurTask();          // 返回done的status id

    bool WaitFirstTaskStart(); // 是否正在等待第一个技能任务开始
    bool GetNextTask();        // 是否有下一个技能任务
    bool IsTaskEmpty();        // 判断当前的任务列表是否为空

    bool SetTasks( short type, bool bCharTarget, GameObjectId stTargetId, short xTarget, short yTarget, short stSkills[], short stSkillLevel[], int nSkillCount );    
    bool SetTasks( short type, bool bCharTarget, GameObjectId nTargetId, D3DXVECTOR3 vTargetPos, int nSkillID, int nSkillLevel );

    void Clear();

    void IdleUpdate();
    void AttackUpdate();

protected:
    void _BeginIntonateTask( SSkillTask* pSkillTask );
    void _BeginNotIntonateTask( SSkillTask* pSkillTask );

protected:
	void SendSkillMsgToSingle(short shHintId, int nSkillID = -1, int stSkillLevel = -1);

public:
    SSkillTask     m_skillTasks[More_iSkillCountPerLinkedSkills];
    bool           m_bCharTarget;
    GameObjectId   m_nTargetId;             // 攻击的目标    
    D3DXVECTOR3    m_vTargetPos;            // 目标位置
    int            m_nSkillTaskIndex;       // 技能任务数组下标
    int            m_nSkillTaskCount;       // 技能任务个数
    BaseCharacter* _pOwner;
};

#endif // __GAMESERVER_SKILLTASKMANAGER_H__
