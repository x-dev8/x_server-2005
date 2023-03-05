/********************************************************************
    Filename:     DropItem.h
    MaintenanceMan Mail: Luo_157@hotmail.com
*********************************************************************/

#ifndef __GAMESERVER_DROPITEM_H__
#define __GAMESERVER_DROPITEM_H__

#pragma once



class ItemCharacter;
class AiBaseCharacter;
class BaseCharacter;
#include <vector>
#define DROP_PROBABILITY        10000
#define GoodItem_For_AssignTeam 2

class DropBaseItem
{
public:
    struct SDropItem
    {
        int nItemId;
        int nProbability;
        SDropItem():nItemId(-1),nProbability(0)
        {

        }
    };

    typedef std::vector<SDropItem> DropItemInfos;
public:

protected:

};

#endif // __GAMESERVER_DROPITEM_H__