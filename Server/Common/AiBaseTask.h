/********************************************************************
    Filename:     AiBaseTask.h
    MaintenanceMan Mail: Luo_157@hotmail.com
*********************************************************************/

#ifndef __GAMESERVER_AIBASETASK_H__
#define __GAMESERVER_AIBASETASK_H__

#include "MeRTLibsServer.h"

class BaseCharacter;

class AiBaseTask
{ // �������
public:
    enum ConstData
    {
        constTaskNameLen = 64,
    };

    enum EPriorityLevel
    {
        EPL_LOW,
        EPL_NORMAL,
        EPL_HIGH,
    };

    AiBaseTask();
    virtual ~AiBaseTask(){};

    virtual void Release() = 0;
    virtual void ExecuteTask( BaseCharacter* pChar ) = 0; // ִ������,��AIBaseCharacter�������

    bool operator < ( const AiBaseTask &right ) const  { return m_dwPriorityLevel < right.m_dwPriorityLevel ? true : false; }
    char* GetName()     { return m_szName; }          // ���������
    bool IsComplete()   { return m_bComplete; }       // �Ƿ����������    
    bool IsSuccessful() { return m_bSuccessful; }     // �Ƿ���ɹ�    
    DWORD PL()          { return m_dwPriorityLevel; } // ���ȼ�
    DWORD PL( DWORD pl ){ m_dwPriorityLevel = pl; return m_dwPriorityLevel;}

protected:
    bool  m_bSuccessful;              // ��ɽ��
    bool  m_bComplete;                // ��ɱ�־
    char  m_szName[constTaskNameLen]; // ������
    DWORD m_dwPriorityLevel;          // ���ȼ�
};

typedef std::vector< AiBaseTask * > AITaskContainer;
typedef AITaskContainer::iterator   AITaskContainerItr;

#endif // __GAMESERVER_AIBASETASK_H__
