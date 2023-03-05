/********************************************************************
    Filename:     DropQuestItem.h
    MaintenanceMan Mail: Luo_157@hotmail.com
*********************************************************************/

#ifndef __GAMESERVER_TASKDROPITEM_H__
#define __GAMESERVER_TASKDROPITEM_H__

#pragma once

#include "DropItem.h"

class GamePlayer;

class DropQuestItem : public DropBaseItem
{
public:
    struct STask
    {
        int         nTaskId;
        int         nTaskState;
        SDropItem   stItem;
        int         nMaxItemCount;
        int         nVarId;
        int         nMaxVar;
        //std::string strVarName;
        STask():nTaskState(1),nTaskId(-1),nMaxItemCount(0),nVarId(-1),nMaxVar(0)
        {

        }
        void Drop()
        {
            nTaskId = -1;
            nVarId = -1;
            stItem.nItemId = -1;
        }
    };

    struct STaskDrop
    {
        int nMonster;
        std::vector<STask> vtTask;
    };

    struct SDropCount
    {
        int nItemId;
        int nMaxItemCount;
    };

public:    
    DropQuestItem();
    virtual ~DropQuestItem();

    virtual bool Init();
    virtual bool LoadData(const char* FileName = TASKDROPITEM_FILEPATH);

    //bool        LoadXmlData(const char* FileName);

#ifdef __QUEST_EDIT__

    bool        SaveXmlData(const char* FileName);
    bool        AddQuest(int MonsterId ,STask &stask, bool bDropCount = true);
    bool        SubQuest(int Monster,int QuestId);
    bool        CoalitionTable(DropQuestItem* item);
    int         FindDropItemByVarId(int Varid,STask &sTask);
    int         FindDropItemByMonsterId(int MonsterId,int Questid,STask &Task);
	int			FindDropItemByItemId(int ItemId, int QuestId, STask &task);
    int         CheckVarId(int VarId,STask &STask);

#endif // __QUEST_EDIT__

    bool MonsterDeath( MonsterBaseEx* pMonster, BaseCharacter* pKiller );
    bool IsTaskItemFull( GamePlayer* pPlayer, int nItemId );

private:
    bool AddDropCount( const SDropCount& stItem );
    bool UpdateTeamTaskVar( const STask* pTask,  MonsterBaseEx* pMonster, GamePlayer *pPlayer );
    void QuestInfoToClient( SQuest* pQuest, const STask* pTask, MonsterBaseEx* pMonster, GamePlayer *pPlayer, int nVar );// 抽出UpdateTeamTaskVar中公共部分

private:
    // 需要优化存储方式
    typedef std::vector<STask> STaskVector;
    typedef std::map<int,STaskVector> DropItemType;
    DropItemType  m_vtDropItem;
    //item id
    typedef std::map<int,SDropCount> DropCountType;
    DropCountType  m_vtDropCount;
//     std::vector<STaskDrop>  m_vtDropItem;
//     std::vector<SDropCount> m_vtDropCount;
};


#endif // __GAMESERVER_TASKDROPITEM_H__
