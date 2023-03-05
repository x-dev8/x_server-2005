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
        STT_SingleSkill,    // ���м���
        STT_Express,        // ���鶯��
        STT_MultiLinkSkill, // ���м���
        STT_Max,
    };

    SSkillTask()
    { memset( this, 0, sizeof(SSkillTask) ); }

    int   type;        // ����(���ܣ����Ƕ���))
    short id;          // ���ܵ�ID
    short level;       // ���ܵĵȼ�    
    bool  isDone;      // �Ƿ����
    DWORD state;       // ״̬
    DWORD startTime;   // ��ʼʱ��
    DWORD balanceTime; // ����ʱ��
    DWORD holdTime;    // ����ʱ��
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
    int  DoneCurTask();          // ����done��status id

    bool WaitFirstTaskStart(); // �Ƿ����ڵȴ���һ����������ʼ
    bool GetNextTask();        // �Ƿ�����һ����������
    bool IsTaskEmpty();        // �жϵ�ǰ�������б��Ƿ�Ϊ��

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
    GameObjectId   m_nTargetId;             // ������Ŀ��    
    D3DXVECTOR3    m_vTargetPos;            // Ŀ��λ��
    int            m_nSkillTaskIndex;       // �������������±�
    int            m_nSkillTaskCount;       // �����������
    BaseCharacter* _pOwner;
};

#endif // __GAMESERVER_SKILLTASKMANAGER_H__
