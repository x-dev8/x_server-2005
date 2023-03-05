#include "MonsterControlProtected.h"
#include "GamePlayer.h"

MonsterControlProtected::MonsterControlProtected() : MonsterProtectedEx()
{
    SetObjType( Object_MonsterControlProtected );

    // Ĭ���ǲ��ƶ���
    SetAiStatus( AiDefine::ThinkingDoNothing );

    // �����͵Ĺ���û��AI
    m_xThinkTimer.StopTimer();
}
