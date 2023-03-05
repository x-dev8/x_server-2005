/********************************************************************
    Filename:     DropTaskItem.h
    MaintenanceMan Mail: Luo_157@hotmail.com
*********************************************************************/

#ifndef __GAMESERVER_TASKDROPITEM_H__
#define __GAMESERVER_TASKDROPITEM_H__

#pragma once

#include "DropItem.h"
#include <map>
#include <list>
class DropTaskItem : public DropBaseItem
{
public:
    static const short DeleQuest = -1;
    static const short NotFandQuest = -1;
    struct STask
    {
        int         nTaskId;
        int         nTaskState;
        SDropItem   stItem;
        int         nMaxItemCount;
        int         nVarId;
        int         nMaxVar;

        STask():nTaskState(1),nTaskId(-1),nMaxItemCount(0),nVarId(-1),nMaxVar(0)
        {


        }
        void Drop()
        {
            nTaskId = -1;
            nVarId = -1;
            stItem.nItemId = -1;
        }
        //std::string strVarName;
    };

    

    struct SDropCount
    {
        int nItemId;
        int nMaxItemCount;
    };

public:    
    DropTaskItem();
    virtual ~DropTaskItem();

    virtual bool Init();
    //virtual bool LoadData();
    bool        LoadXmlData(const char* FileName);

#ifdef __QUEST_EDIT__

    bool        SaveXmlData(const char* FileName);
    bool        AddQuest(int MonsterId ,STask &stask, bool bDropCount = true);
    bool        SubQuest(int Monster,int QuestId,int itemid);
    bool        CoalitionTable(DropTaskItem* item);
    int         FindDropItemByVarId(int Varid,STask &sTask);
    int         FindDropItemByMonsterId(int MonsterId,int Questid,STask &Task);
	int			FindDropItemByItemId(int ItemId, int QuestId, STask &task);
    int         CheckVarId(int VarId,STask &STask);

#endif // __QUEST_EDIT__
private:
    bool AddDropCount( const SDropCount& stItem );
private:
    // 需要优化存储方式
    //monster id
    typedef std::vector<STask> STaskVector;
    typedef std::map<int,STaskVector> DropItemType;
    DropItemType  m_vtDropItem;
    //item id
    typedef std::map<int,SDropCount> DropCountType;
    DropCountType  m_vtDropCount;
};


#endif // __GAMESERVER_TASKDROPITEM_H__
