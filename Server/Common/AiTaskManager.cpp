#include "AiTaskManager.h"
#include "BaseCharacter.h"

bool AiTaskManager::AddTask( AiBaseTask* pTask )
{
    if ( !pTask)
        return false;

    switch (pTask->PL())
    {
    case AiBaseTask::EPL_LOW:
        _lowTasks.push_back(pTask);
        break;
    case AiBaseTask::EPL_NORMAL:
        _normalTasks.push_back(pTask);
        break;
    case AiBaseTask::EPL_HIGH:
        _highTasks.push_back(pTask);
        break;
    }
    return true;
}

void AiTaskManager::ClearTask()
{
    ItrAiTaskContainer it = _lowTasks.begin();
    for ( ; it!=_lowTasks.end(); ++it)
    {
        AiBaseTask* pTask = *it;
        if ( !pTask )
            continue;
        
		pTask->Release();
    }
    _lowTasks.clear();

    it = _normalTasks.begin();
    for ( ; it!=_normalTasks.end(); ++it)
    {
        AiBaseTask* pTask = *it;
        if ( !pTask )
            continue;
        
		pTask->Release();
    }
    _normalTasks.clear();

    it = _highTasks.begin();
    for ( ; it!=_highTasks.end(); ++it)
    {
        AiBaseTask* pTask = *it;
        if ( !pTask )
            continue;
        
		pTask->Release();
    }
    _highTasks.clear();
}