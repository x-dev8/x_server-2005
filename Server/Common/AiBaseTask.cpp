#include "AiBaseTask.h"
#include "MonsterBaseEx.h"

AiBaseTask::AiBaseTask()
{
    m_bSuccessful = false;
    m_bComplete = false;
    m_szName[0] = 0;
}

// 任务优先级比较
static bool TaskUDgreater ( AiBaseTask *elem1, AiBaseTask *elem2 )
{
    return (*elem1) < (*elem2);
}

