/********************************************************************
    Filename:     AiBaseTask.h
    MaintenanceMan Mail: Luo_157@hotmail.com
*********************************************************************/

#ifndef __GAMESERVER_AIBASETASK_H__
#define __GAMESERVER_AIBASETASK_H__

#include "MeRTLibsServer.h"

class BaseCharacter;

class AiBaseTask
{ // 任务基类
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
    virtual void ExecuteTask( BaseCharacter* pChar ) = 0; // 执行任务,被AIBaseCharacter对象调用

    bool operator < ( const AiBaseTask &right ) const  { return m_dwPriorityLevel < right.m_dwPriorityLevel ? true : false; }
    char* GetName()     { return m_szName; }          // 获得任务名
    bool IsComplete()   { return m_bComplete; }       // 是否完成任务处理    
    bool IsSuccessful() { return m_bSuccessful; }     // 是否处理成功    
    DWORD PL()          { return m_dwPriorityLevel; } // 优先级
    DWORD PL( DWORD pl ){ m_dwPriorityLevel = pl; return m_dwPriorityLevel;}

protected:
    bool  m_bSuccessful;              // 完成结果
    bool  m_bComplete;                // 完成标志
    char  m_szName[constTaskNameLen]; // 任务名
    DWORD m_dwPriorityLevel;          // 优先级
};

typedef std::vector< AiBaseTask * > AITaskContainer;
typedef AITaskContainer::iterator   AITaskContainerItr;

#endif // __GAMESERVER_AIBASETASK_H__
