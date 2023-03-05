/********************************************************************
    Filename:     DropMonsterItem.h
    MaintenanceMan Mail: Luo_157@hotmail.com
*********************************************************************/

#ifndef __GAMESERVER_DROPMONSTERITEM_H__
#define __GAMESERVER_DROPMONSTERITEM_H__

#pragma once

#include "DropItem.h"
#include "DropCommonItem.h"
#include "DropCommonItemConfig.h"
#include "DropMonsterItemConfig.h"

class DropMonsterItem : public DropBaseItem
{
public:
    DropMonsterItem();
    virtual ~DropMonsterItem();

    bool   MonsterDeath     ( MonsterBaseEx* pMonster, BaseCharacter* pKiller );
    float  GetDistanceLevelX( MonsterBaseEx* pMonster, BaseCharacter* pKiller, OUT int& nDistanceLevel );

private:
    DropCommonItem            m_CommonDropItem;
};

#endif // __GAMESERVER_DROPMONSTERITEM_H__
