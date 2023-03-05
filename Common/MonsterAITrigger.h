/********************************************************************
    Filename:     MonsterAITrigger.h
    MaintenanceMan Mail: Luo_157@hotmail.com
*********************************************************************/

#include "MeRTLibs.h"

#pragma once

enum EnumTriggerEvent
{
    eTE_WhenAIBeStarted,     // 每当怪物AI被击活的时候 
    eTE_WhenThinking,        // 每当怪物思考的时候
    eTE_WhenGotoTargetPoint, // 每当怪物移动到目标点的时候
    eTE_WhenAttacked,        // 每当怪物受到攻击的时候
    eTE_WhenAttack,          // 每当怪物攻击的时候
    eTE_WhenIdle,            // 每当怪物空闲的时候
    eTE_WhenReturnToBron,    // 每当怪物回出生点的时候
};

enum EnumTriggerCondition
{
    eTC_HPChanged, // 怪物HP改变
    eTC_MPChanged, // 怪物MP改变
};

enum EnumTriggerAction
{
    eTA_UseSkill,  // 释放技能
    eTA_ReStoreHP, // 回复HP
    eTA_ReStoreMP, // 回复MP
};

struct SEvent
{ // 事件
    short stEventID;         // 事件ID
    char szEventIntro[1024]; // 事件介绍
    SEvent()
    {
        stEventID = -1;
        memset(szEventIntro, NULL, sizeof(szEventIntro));
    }
};

struct SCondition
{ // 条件
    short stConditionID;         // 条件ID
    char szConditionIntro[1024]; // 条件介绍
    BYTE byOperation[1];
    int nValue[1];
    SCondition()
    {
        memset(byOperation, 0, sizeof(byOperation));
        memset(nValue, 0, sizeof(nValue));
        stConditionID = -1;
        memset(szConditionIntro, NULL, sizeof(szConditionIntro));
    }
};

struct SAction
{ // 动作
    short stActionID;                //动作ID
    char szActionIntro[1024];        //动作介绍
    int nValue[1];
    SAction()
    {
        memset(nValue, 0, sizeof(nValue));
        stActionID = -1;
        memset(szActionIntro, NULL, sizeof(szActionIntro));
    }
};

struct SMonsterTrigger 
{ // 区域
    char szTriggerIntro[256];
    //char szTriggerRemark[2048];
    SEvent event;
    SCondition condition;
    SAction action;
    SMonsterTrigger()
    {
        memset(szTriggerIntro, NULL, sizeof(szTriggerIntro));
    }
};

//怪物AI触发器
class CMonsterAITrigger
{
public:
    CMonsterAITrigger();
    virtual ~CMonsterAITrigger();

    void AddMonsterAITrigger();

    void AddMonsterAITrigger( SMonsterTrigger mt );

    int GetMaxMonsterAITrigger();

    SMonsterTrigger* GetMonsterAITriggerByID( int id );

    void Clear();

    std::vector< SMonsterTrigger > m_vectorMonsterAITriggerStore;
    //std::map< std::string, int > m_mapAreaStore;
//private:
//    CStageDataLoader* m_pStageDataLoader;

};