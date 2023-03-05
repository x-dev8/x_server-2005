#ifndef __NPCNORMALEX_H__
#define __NPCNORMALEX_H__

/********************************************************************
                ∆’Õ®NPC
                Filename:    NpcNormalEx.h
                MaintenanceMan Mail: lori227@live.cn
*********************************************************************/

#include "NpcBaseEx.h"

class NpcNormalEx : public NpcBaseEx, INHERIT_POOL_PARAM( NpcNormalEx, 20 )
{
public:
    DECLARE_POOL_FUNC( NpcNormalEx )

    NpcNormalEx();
    virtual ~NpcNormalEx(){}
};

#endif