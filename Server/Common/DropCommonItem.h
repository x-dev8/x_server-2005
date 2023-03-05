/********************************************************************
    Filename:    DropCommonItem.h
    MaintenanceMan Mail: Luo_157@hotmail.com
*********************************************************************/

#ifndef __GAMESERVER_DROPCOMMONITEM_H__
#define __GAMESERVER_DROPCOMMONITEM_H__

#pragma once

#include "DropItem.h"
#include "DropCommonItemConfig.h"

class DropCommonItem : public DropBaseItem
{
public:
    DropCommonItem();
    virtual ~DropCommonItem();

    bool Drop       ( unsigned int nPackIndex, int nMapId, float fX, float fY, int nTask, BaseCharacter* pOwner ); // µÙ¬‰ŒÔ∆∑
    bool DropPackage( unsigned int nPackIndex, DropItemVector& mapDropItem );

};

#endif // __GAMESERVER_DROPCOMMONITEM_H__
