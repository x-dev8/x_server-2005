/********************************************************************
    Filename:    DropItemMgr.h
    MaintenanceMan Mail: Luo_157@hotmail.com
*********************************************************************/

#ifndef __GAMESERVER_DROPITEMMANAGER_H__
#define __GAMESERVER_DROPITEMMANAGER_H__

#include "DropQuestItem.h"
#include "DropMonsterItem.h"


class MonsterBaseEx;
class BaseCharacter;

class DropItemManager
{
public:
    DropItemManager();
    ~DropItemManager();

	bool Init();

    bool MonsterDeath( MonsterBaseEx* pMonster, BaseCharacter* pKiller );

    DropMonsterItem&  GetMonsterDropItem(){ return _DropMonsterItem;}
    DropQuestItem&    GetTaskDropItem(){ return _DropQuestItem;}

    void DropItemBroadcast( int StringID, uint32 dwPlayerID, short nMonsterID, int nItemID, ItemCharacter* pItemChar );

    void AddItemDropControl( uint16 nItemID, uint32 dwControlCount, uint32 dwDorpCount );
    ItemDropControl* GetItemDropControl( uint16 nItemID );
    bool CheckItemCanDrop( uint16 nItemID, uint16 nCount );

private:
    DropMonsterItem _DropMonsterItem;
    DropQuestItem   _DropQuestItem;

    MapItemDropControl m_mapItemDropControl;     // ŒÔ∆∑µÙ¬‰øÿ÷∆
};

DropItemManager& GetDropItemManager();

#define theDropItemManager GetDropItemManager()

#endif // __GAMESERVER_DROPITEMMANAGER_H__
