#include "MonsterControlProtected.h"
#include "GamePlayer.h"

MonsterControlProtected::MonsterControlProtected() : MonsterProtectedEx()
{
    SetObjType( Object_MonsterControlProtected );

    // 默认是不移动的
    SetAiStatus( AiDefine::ThinkingDoNothing );

    // 控制型的怪物没有AI
    m_xThinkTimer.StopTimer();
}
