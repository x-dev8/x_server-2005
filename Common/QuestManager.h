/********************************************************************
    Filename:    QuestManager.h
    MaintenanceMan Mail: Luo_157@hotmail.com
*********************************************************************/

#ifndef __COMMON_QUESTMANAGER_H__
#define __COMMON_QUESTMANAGER_H__

#pragma once

#include "GlobalDef.h"
#include "QuestDefine.h"

class QuestManager
{
public:

    // QuestValue 16位 分为 1 1 6 8
    // 0 0 000000 00000000
    // | | |    | |      |
    // | | |____| |______|
    // A B    X      C
    // A.第一表示这个任务看没看过接前对话
    // B.第二表示这个任务看没看过交前对话
    // C.表示任务状态
    // X.预留

    enum EConstDefine
    {
        ECD_A = 0x8000, // A区取值
        ECD_B = 0x4000, // B区取值
        ECD_C = 0x00ff, // C区取值
        ECD_X = 0x3f00, // X区取值
    };

    enum EHaveSawTalkType
    {
        HSTT_ToGain, // 去接任务
        HSTT_ToDone, // 去交任务
		HSTT_Count
    };

    enum EQuestState
    {
        eQuestCantGain = 0x03, // 无法接取 3         
        eQuestNotGain  = 0x00, // 未接 0
        eQuestGaining  = 0x01, // 接了任务 1
        eQuestDone     = 0x02, // 完成 2
		eQuestFrozen   = 0x04, // 任务暂时冻结
		eQuestEntrustDone = 0x08,
    };

    enum ESpecialQuestGainState
    {
        ESQGS_CannotGain = 0, // 不可接取
        ESQGS_CanGain    = 1, // 可接取
    };

    typedef std::map< int, int >      PubQuestRankMap   ; // <任务品质,随机率>
    typedef PubQuestRankMap::iterator ItrPubQuestRankMap;
    typedef std::vector< int >        PubQuestId        ; // <任务Id列表>
    typedef PubQuestId::iterator      ItrPubQuestId     ;

public:
    ~QuestManager();

    static QuestManager& Instance();
    
    // 是否是有效的QuestId
    bool IsQuestIdValid( int nQuestId );
    
    // 设置任务状态 返回 存在Var中的原始值
    short SetQuestState( short questValue, uint8 questState );

    // 取得任务状态值 传入的参数 questValue为从Var队列中取的原始值
    uint8 GetQuestState( short questValue );
    
    // 当前状态是否是完成状态
    bool IsQuestDone  ( uint8 questState );

    // 当前状态是否是未接状态
    bool IsQuestNotGain( uint8 questState );

    // 当前状态是否 在已接取 做任务中(激活中)
    bool IsQuestActive( uint8 questState );

    // 是否看过对话 传入的参数是事件类型 EHaveSawTalkType. questValue为从Var队列中取的原始值
    bool IsHaveSaw( uint8 type, short questValue );

    // 设置任务是否已经看过对话
    short SetHaveSaw( uint8 type, short questValue );

    SQuest*     GetQuest( int nQuestId );                               // 获取指定任务Id的任务
    void        AddPubQuest  ( int nQuestID ) { _PubQuestID.push_back( nQuestID ); _AllPubQuestID.push_back( nQuestID ); }
    void        AddRoyalQuest( int nQuestID ) { _RoyalQuestID.push_back( nQuestID ); _AllPubQuestID.push_back( nQuestID ); }
    void        AddConQuest  ( int nQuestID ) { _ConQuestID.push_back( nQuestID );}
    PubQuestId& GetAllPubQuest() { return _AllPubQuestID; } // 获取酒馆和皇榜任务
    PubQuestId& GetPubQuest()    { return _PubQuestID   ; } // 获取酒馆任务
    PubQuestId& GetRoyalQuest()  { return _RoyalQuestID ; } // 获取皇榜任务
    PubQuestId& GetConQuest()    { return _ConQuestID   ; } // 获取征伐任务
    SQuest*     GetQuestByTheQuests( std::list<int>& QuestIds ); // 通过任务列表,返回随机的任务
    bool        LoadQuestRandConfigFile(const char* Path);       // 读取品质随机文件
    void        ParseAllSpecializationQuestByQuest();            // 解析任务列表分析出皇榜任务和酒馆任务
    bool        SaveQuestRandConfigFile(const char* Path);

protected:
    QuestManager();
    bool    CheckQuestRand( PubQuestRankMap &_PubQuestRankMap );

protected:
    PubQuestRankMap _QuestRankMap  ; // 任务品质概率数据
    int             _QuestTotalRand; // 计算出的总的品质概率总数

    PubQuestId      _PubQuestID   ;
    PubQuestId      _RoyalQuestID ;
    PubQuestId      _AllPubQuestID;
    PubQuestId      _ConQuestID   ;
};

#define theQuestManager QuestManager::Instance()

#endif // __COMMON_QUESTMANAGER_H__