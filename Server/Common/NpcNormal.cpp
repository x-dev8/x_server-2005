#include "NpcNormal.h"

NpcNormal::NpcNormal()
{
    SetObjType( Object_NpcNormal );
}

void NpcNormal::Prepare()
{
    SetMoveState( EAction_WillMoveNext );
    return;
}
