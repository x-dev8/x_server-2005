#include "MonsterResource.h"

MonsterResource::MonsterResource() : MonsterBaseEx()
{
    SetObjType( Object_MonsterResource );

    SetAiStatus( AiDefine::ThinkingMoveAround );
}

void MonsterResource::ProcessAiLogic( uint32 nCostTime )
{
}