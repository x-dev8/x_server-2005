/********************************************************************
    Filename:    MonsterNormal.h
    MaintenanceMan Mail: Luo_157@hotmail.com
*********************************************************************/

#ifndef __GAMESERVER_MONSTERNORMAL_H__
#define __GAMESERVER_MONSTERNORMAL_H__

#pragma once

#include "MonsterBaseEx.h"

const int gMonsterNormalPoolBatchSize = 100;

class MonsterNormalEx : public MonsterBaseEx, 
                      INHERIT_POOL_PARAM( MonsterNormalEx, gMonsterNormalPoolBatchSize )
{
public:
    DECLARE_POOL_FUNC( MonsterNormalEx )

	MonsterNormalEx();
    virtual ~MonsterNormalEx() {}
};

#endif // __GAMESERVER_MONSTERNORMAL_H__
