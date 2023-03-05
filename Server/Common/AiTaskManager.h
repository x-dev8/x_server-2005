#ifndef __GAMESERVER_AITASKMANAGER_H__
#define __GAMESERVER_AITASKMANAGER_H__

#pragma once

#include "AiBaseTask.h"

class BaseCharacter;

class AiTaskManager
{
public:
    AiTaskManager(){}
    ~AiTaskManager(){}
    
    bool AddTask( AiBaseTask * pTask ); // 增加任务
    void ClearTask();                   // 清除任务

private:
    typedef std::vector< AiBaseTask * > AiTaskContainer;
    typedef AiTaskContainer::iterator   ItrAiTaskContainer;
    AiTaskContainer _lowTasks;    
    AiTaskContainer _normalTasks;
    AiTaskContainer _highTasks;

    BaseCharacter* _pMaster;
};

#endif // __GAMESERVER_AITASKMANAGER_H__
