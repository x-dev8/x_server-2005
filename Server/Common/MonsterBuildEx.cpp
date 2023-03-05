#include "MonsterBuildEx.h"


MonsterBuildEx::MonsterBuildEx() : MonsterBaseEx()
{
    // 建筑怪不执行AI思考
    m_xTimer[ AiDefine::AiTimer_Thinking ].StopTimer();

    SetObjType( Object_MonsterBuilding );
}

void MonsterBuildEx::ProcessRefreshEnmity( uint32 nCurrentTime )
{
    // 建筑怪不刷仇恨
}
