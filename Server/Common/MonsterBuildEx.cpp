#include "MonsterBuildEx.h"


MonsterBuildEx::MonsterBuildEx() : MonsterBaseEx()
{
    // �����ֲ�ִ��AI˼��
    m_xTimer[ AiDefine::AiTimer_Thinking ].StopTimer();

    SetObjType( Object_MonsterBuilding );
}

void MonsterBuildEx::ProcessRefreshEnmity( uint32 nCurrentTime )
{
    // �����ֲ�ˢ���
}
