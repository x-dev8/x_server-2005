/********************************************************************
    Filename:    GameDefineQuest.h
    MaintenanceMan Mail: Luo_157@hotmail.com
*********************************************************************/

#ifndef __COMMON_GAMEDEFINEQUEST_H__
#define __COMMON_GAMEDEFINEQUEST_H__

#pragma once

#pragma pack(push,1)

#include "MeRTLibs.h"
#include "XmlStringLanguage.h"
#include "NpcInfo.h"
#include "GameDefineSystem.h"

struct SQuestReward
{ // 任务回报
    SQuestReward()
    {
        Value        = -1;
        shSex        = 0;
        shProfession = -1;
        byType       = 0;
        Number       = 0;
        Icon         = 0;
    }

    uint8 byType;       // 类型
    int32 Number;       // 数值
    int32 Value;        // 名字值Id
    int16 shSex;        // 奖励的道具物品的性别
    int16 shProfession; // 奖励的道具物品的
    int32 Icon;         // 奖励的道具的图标  

    void ClearReward()
    {
        Value        = -1;
        shSex        = 0;
        shProfession = -1;
        byType       = 0;
        Number       = 0;
        Icon         = 0;
    }
};

struct SQuestRequirement
{ // 任务需求
    SQuestRequirement()
    {
        byType = 0;
        wVar = ErrorUnsignedShortID;
        MaxNum = 0;
        Value = ErrorUnsignedShortID;
    }
    uint8  byType; // 类型
    uint16 wVar;   // 变量的ID
    uint16 MaxNum; // 任务需求最大数值
    int32  Value;  // 可以是道具Id,可以是值

    void ClearRequirement()
    {
        byType = 0;
        wVar = 0;
        MaxNum = 0;
        Value = ErrorUnsignedLongID;
        //memset(szItem,0,dr_MaxQuestStateDesc);
    }
};

struct SQuest
{
    enum ERequirementTypes
    {
        eRequirement_Money = 0, // 金钱
        eRequirement_Item     , // 道具
        eRequirement_Var      , // 任务相应的记数变量
        eRequirement_Profession,
        eRequirement_Level,
        eRequirement_Reputation,
        eRequirement_Sex,
        eRequirement_Energy,
        eRequirement_Monster,
        eRequirement_Quest,
        eRequirement_Time,
        eRequirement_SocialRelation,//社会关系
        eRequirement_Exp      , // 经验值
        eRequirement_SkillExp , // 技能经验
        eRequirement_Action,    // 行为任务，比如护送
        eRequirement_VarLimit,  // 记数限制( 小于记数值 可以领取任务 )
        eRequirement_Max,
    };


    enum ERewardType
    {
        eReward_Money = 0, // 金钱
        eReward_Exp, // 经验值
        eReward_SkillExp , // 技能经验
        eReward_Item, // 道具
        eReward_Reputation,
        eReward_Exploit,        //功勋
        eReward_Title,
        eReward_Buff,
        eReward_ChangeRoleVar,
        eReward_GuildContribute,        // 奖励帮贡
        eReward_SpecialItem,            // 特别物品
        eReward_JiaoZi,                 // 交子 
        eReward_Max,
    };

    enum QuestRank
    {
        eQuestRank_Nor,  //普通
        eQuestRank_Nic,  //良好的
        eQuestRank_Exc,  //优秀
        eQuestRank_Gold, //卓越
        eQuestRank_Legend,//传说
        //eQuestRank_Epic,//史诗
        eQuestRank_Max,
    };

    enum QuestType
    {
        Type_Main = 0,      // 主线任务
        Type_Lateral,       // 支线任务
        Type_Campaign,      // 活动任务
        Type_Ectype,        // 副本任务
        Type_Official,      // 官府任务
        Type_Circle,        // 循环任务
        Type_Cruise,        // 巡城任务
        Type_Battalion,     // 军需任务
        Type_Precious,      // 藏宝任务
        Type_Title,         // 称号任务 
        Type_Gut,           // 剧情任务
        Type_Gout,          // 趣味任务
        Type_Guild,         // 帮派任务
        Type_Pub,           // 酒馆任务
        Type_Royal,         // 皇榜任务
        Type_ConQuest,      // 征伐任务

        Type_End,
    };

    typedef std::vector<SQuestReward>      RewardType;
    typedef std::vector<SQuestRequirement> RequirementType;

    int16           Id;                   // 任务Id
    uint32          QuestName;            // 任务名称
    uint32          IntroStringId;        // 任务说明
    RewardType      stReward;             // 报酬
    RequirementType stCommitRequirement;  // 任务完成的需求
    RequirementType stReceiveRequirement; // 接受任务的需求
    bool            IsRepeat;             // 是否重复试练
    bool            IsCancel;             // 任务是否可被删除,重要的任务不能被删除,接任务的时候也不增加激活任务数
    uint8           HintLevelMin;         // 提示任务下限
    uint8           HintLevelMax;         // 提示任务上限
    uint32          AcceptTargetId;       // 接任务目标
    uint32          ReplyTargetId;        // 交任务的NPC名称
    int16           MapId;                // 任务的地图Id
    uint32          TargetStringId;       // 任务目标
    bool            CanAssist;            // 可否协助
    bool            CanShare;             // 可否共享
    int16           RankId;               // 任务品质
    uint8           chQuestType;          // 任务类型
    bool            CanDisplay;           // 客户端是否可显示

    SQuest()
    {
        QuestName = 0;
        IntroStringId = 0;
        Id = 0;
        IsRepeat = false;
        IsCancel = true;
        HintLevelMin = 0;
        HintLevelMax = 100;
        MapId = -1;
        CanAssist = true;
        CanShare = true;
        TargetStringId = 0;
        AcceptTargetId = ErrorUnsignedLongID;
        ReplyTargetId = ErrorUnsignedLongID;
        RankId = -1;
        chQuestType = Type_Main;
        CanDisplay = true;
    }

    const char* GetQuestName();
    const char* GetQuestStateInfo();
    const char* GetRewardNpcName();
    const char* GetAcceptNpcName();
    const char* GetQuestInfo();

    SQuest& operator =(const SQuest& squest)
    {
        if (this == &squest)
        {
            return *this;
        }
        Id = squest.Id;
        IsRepeat = squest.IsRepeat;
        IsCancel = squest.IsCancel;
        HintLevelMin = squest.HintLevelMin;
        HintLevelMax = squest.HintLevelMax;
        MapId = squest.MapId;
        CanAssist = squest.CanAssist;
        CanShare = squest.CanShare;
        TargetStringId = squest.TargetStringId;
        QuestName = squest.QuestName;
        IntroStringId = squest.IntroStringId;
        AcceptTargetId = squest.AcceptTargetId;
        ReplyTargetId = squest.ReplyTargetId;
        RankId = squest.RankId;
        chQuestType = squest.chQuestType;

        stReward = squest.stReward;
        stCommitRequirement = squest.stCommitRequirement;
        stReceiveRequirement = squest.stReceiveRequirement;
        CanDisplay = squest.CanDisplay;
        return *this;
    }

    int GetPlayerReceiveQuestLevel()
    {
        for (std::vector<SQuestRequirement>::iterator itrPlayerLevel=stReceiveRequirement.begin();itrPlayerLevel!=stReceiveRequirement.end();++itrPlayerLevel)
        {
            if (itrPlayerLevel->byType == eRequirement_Level)//eRequirement_Level
            {
                return itrPlayerLevel->Value;
            }
        }
        return 1;
    }
    int GetPlayerReceiveQuestSex()
    {
        for (std::vector<SQuestRequirement>::iterator itrPlayerLevel=stReceiveRequirement.begin();itrPlayerLevel!=stReceiveRequirement.end();++itrPlayerLevel)
        {
            if (itrPlayerLevel->byType == eRequirement_Sex)//eRequirement_Level
            {
                return itrPlayerLevel->Value;
            }
        }
        return 2;
    }
    int GetPlayerReceiveQuestProfession()
    {
        for (std::vector<SQuestRequirement>::iterator itrPlayerLevel=stReceiveRequirement.begin();itrPlayerLevel!=stReceiveRequirement.end();++itrPlayerLevel)
        {
            if (itrPlayerLevel->byType == eRequirement_Profession)//eRequirement_Profession
            {
                return itrPlayerLevel->Value;
            }
        }
        return 0xff;
    }
    int GetPlayerReceiveQuestReputation()
    {
        for (std::vector<SQuestRequirement>::iterator itrPlayerLevel=stReceiveRequirement.begin();itrPlayerLevel!=stReceiveRequirement.end();++itrPlayerLevel)
        {
            if (itrPlayerLevel->byType == eRequirement_Reputation)//eRequirement_Reputation
            {
                return itrPlayerLevel->Value;
            }
        }
        return 1;
    }
    int16 AddReceiveRequirement( const SQuestRequirement* pRequirement )
    {
        stReceiveRequirement.push_back(*pRequirement);

        return (int16)stReceiveRequirement.size();
    }

    int RemoveReceiveRequirement( const SQuestRequirement* pRequirement )
    {
        if( stReceiveRequirement.empty() )
            return -1;
        int i = 0;
        for( std::vector<SQuestRequirement>::iterator it = stReceiveRequirement.begin();it != stReceiveRequirement.end();++it)
        {
            if(it->byType == pRequirement->byType)
            {
                stReceiveRequirement.erase(it);
                return i;
            }
            ++i;
        }

        return -1;
    }

    SQuestRequirement* GetReceiveRequirement(int Typeid,int* pBeginPos = NULL)
    {
        int nBeginPos = 0;
        if (pBeginPos)
        {
            nBeginPos = *pBeginPos;
        }

        if( stReceiveRequirement.empty() || nBeginPos >= (int)stReceiveRequirement.size())
        { return NULL; }
        int retPos = nBeginPos + 1;
        for(std::vector<SQuestRequirement>::iterator workitr = stReceiveRequirement.begin() + nBeginPos; workitr != stReceiveRequirement.end() ; ++workitr,++retPos)
        {
            if (workitr->byType == Typeid)
            {
                if (pBeginPos)
                {
                    *pBeginPos = retPos;
                }
                return &(*workitr);
            }            
        }
        return NULL;
    }
    void ClearCommitRequirement()
    {
        stCommitRequirement.clear();
    }
    void ClearReceiveRequirement()
    {
        stReceiveRequirement.clear();
    }
    void ClearReward()
    {
        stReward.clear();
    }
    int16 AddCommitRequirement( const SQuestRequirement* pRequirement )
    {
        stCommitRequirement.push_back(*pRequirement);

        return (int16)stCommitRequirement.size();
    }

    int RemoveCommitRequirement( const SQuestRequirement* pRequirement )
    {
        if( stCommitRequirement.empty() )
            return -1;
        int i = 0;
        for( std::vector<SQuestRequirement>::iterator it = stCommitRequirement.begin();it != stCommitRequirement.end();++it)
        {
            if(it->byType == pRequirement->byType)
            {
                stCommitRequirement.erase(it);
                return i;
            }
            ++i;
        }

        return -1;
    }
    SQuestRequirement* GetCommitRequirementt(int Typeid)
    {
        if( stCommitRequirement.empty() )
            return NULL;
        for(std::vector<SQuestRequirement>::iterator workitr = stCommitRequirement.begin() ; workitr != stCommitRequirement.end() ; ++workitr)
        {
            if (workitr->byType == Typeid)
            {
                return &(*workitr);
            }
        }
        return NULL;
    }

    int AddReward( const SQuestReward* pReward )
    {
        // 		for (std::vector<SQuestReward>::iterator iter = stReward.begin(); iter != stReward.end(); ++iter)
        // 		{
        // 			if ((*iter).byType > pReward->byType)
        // 			{
        // 				stReward.insert(iter,*pReward);
        // 				return stReward.size();
        // 			}
        // 		} 排序，根据小胖建议去掉
        stReward.push_back(*pReward);
        return (int)stReward.size();
    }

    int RemoveReward( const SQuestReward* pReward )
    {
        int i = 0;
        for (std::vector<SQuestReward>::iterator it = stReward.begin(); it != stReward.end();++it)
        {
            if (it->byType == pReward->byType)
            {
                stReward.erase(it);
                return i;
            }
            ++i;
        }

        return -1;
    }
    SQuestReward* GetReward(int Typeid)
    {
        if( stReward.empty() )
            return NULL;
        for(std::vector<SQuestReward>::iterator workitr = stReward.begin() ; workitr != stReward.end() ; ++workitr)
        {
            if (workitr->byType == Typeid)
            {
                return &(*workitr);
            }
        }
        return NULL;
    }

    bool IsPubQuest() { return ( chQuestType == Type_Pub || chQuestType == Type_Royal ); }
    bool IsConQuest() { return chQuestType == Type_ConQuest; }
};

//////////////////////////////////////////////////////////////////////////
// inline
inline const char* SQuest::GetQuestName()
{ return theXmlString.GetString(QuestName); }

inline const char* SQuest::GetRewardNpcName()
{
    NpcInfo::Npc* NpcName = theNpcInfo.GetNpcByStaticId(ReplyTargetId);
    if (NpcName == NULL)
    { return NULL; }
    return NpcName->name.c_str();
}

inline const char* SQuest::GetAcceptNpcName()
{
    NpcInfo::Npc* NpcName = theNpcInfo.GetNpcByStaticId(AcceptTargetId);
    if (NpcName == NULL)
    { return NULL; }
    return NpcName->name.c_str();
}

inline const char*  SQuest::GetQuestStateInfo()
{ return theXmlString.GetString(TargetStringId); }

inline const char* SQuest::GetQuestInfo()
{ return theXmlString.GetString(IntroStringId);}

#pragma pack(pop) 

#endif // __COMMON_GAMEDEFINEQUEST_H__
