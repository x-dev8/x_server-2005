/********************************************************************
    Filename:    QuestDefine.h
    MaintenanceMan Mail: Luo_157@hotmail.com
*********************************************************************/

#ifndef __COMMON_QUESTDEFINE_H__
#define __COMMON_QUESTDEFINE_H__

#pragma once

#include "MeRTLibsServer.h"
#include "GameDefineGlobal.h"

#pragma pack ( push ,1 )

struct SQuestReward
{ // 任务回报
    SQuestReward()
    {
        Value = -1;
        shSex = 2;
        shProfession = -1;
        byType = 0;
        Number = 0;
        Icon   = 0;
        bIsBound = true;
        bIsStarRandom = false;
        nStarLevel = 0;
        RewardID = 0;
    }

    BYTE    byType       ; // 类型
    int     Number       ; // 数值
    int     Value        ; // 名字值Id
    short   shSex        ; // 奖励的道具物品的性别
    short   shProfession ; // 奖励的道具物品的
    int     Icon         ; // 奖励的道具的图标
    bool    bIsBound     ; // 是否绑定
    bool    bIsStarRandom; // 是否随机星级
    short   nStarLevel   ; // 最大星级
    BYTE    RewardID     ; // 奖励ID

    void ClearReward()
    {
        Value = -1;
        shSex = 2;
        shProfession = -1;
        byType = 0;
        Number = 0;
        Icon = 0;
        RewardID = 0;
    }
};

struct SQuestRequirement
{
    SQuestRequirement()
    {
        ClearRequirement();
    }

    BYTE byType   ; // 类型
    WORD wVar     ; // 变量的ID
    WORD MaxNum   ; // 任务需求最大数值
    int  Value    ; // 可以是道具Id,可以是值
    int  nStringID; // 计数变量对应的字串ID，仅在选择需要类型为计数变量时存储
    BYTE nRewardID; // 对应奖励ID

    void ClearRequirement()
    {
        byType = 0;
        wVar = 0;
        MaxNum = 0;
        Value = InvalidLogicNumber;
        nStringID = InvalidLogicNumber;
        nRewardID = 0;
        //memset(szItem,0,dr_MaxQuestStateDesc);
    }
};

/*
*@desc Npc特别对话
*/
struct SQuestTalk;
typedef std::vector<SQuestTalk> QuestTalks;
struct SQuestOption
{
    SQuestOption()
    {
        nStringId = InvalidLogicNumber;
    }
    int nStringId;
    QuestTalks vTalks;
};
typedef std::vector<SQuestOption> QuestOptions;
struct SQuestTalk
{
    SQuestTalk()
    {
        nNpcId = InvalidLogicNumber;
        nStringId = InvalidLogicNumber;
		nNpcAnim = InvalidLogicNumber;
    }
    int nNpcId;
    int nStringId;
	int nNpcAnim;
    QuestOptions vOptions;
};

struct SQuest
{
    enum ERequirementTypes
    {
        eRequirement_Money = 0      , // 金钱
        eRequirement_Item           , // 道具
        eRequirement_Var            , // 任务相应的记数变量
        eRequirement_Profession     ,
        eRequirement_Level          ,
        eRequirement_Reputation     ,
        eRequirement_Sex            ,
        eRequirement_Energy         ,
        eRequirement_Monster        ,
        eRequirement_Quest          ,
        eRequirement_Time           , // 时间限制(s)
        eRequirement_SocialRelation , // 社会关系
        eRequirement_Exp            , // 经验值
        eRequirement_SkillExp       , // 技能经验
        eRequirement_Action         , // 行为任务，比如护送
        eRequirement_VarLimit       , // 记数限制( 小于记数值 可以领取任务 )
        eRequirement_WeakCountry    , // 弱国才能接
        eRequirement_Status         , // 需要状态
        eRequirement_NoStatus       , // 没有状态
        eRequirement_XinFaLevel     , // 心法等级
        eRequirement_PetNumber      , // 宠物数量
        eRequirement_PetLevel       , // 宠物等级
        eRequirement_PetID          , // 宠物ID
        eRequirement_PetType        , // 宠物类型
        eRequirement_PetActive      , // 宠物出战
        eRequirement_Max            ,
    };

    enum ERewardType
    {
        eReward_Money = 0      , // 金钱
        eReward_Exp            , // 经验值
        eReward_SkillExp       , // 技能经验
        eReward_Item           , // 道具
        eReward_Reputation     ,
        eReward_Exploit        , // 功勋
        eReward_Title          ,
        eReward_Buff           ,
        eReward_ChangeRoleVar  ,
        eReward_GuildContribute, // 奖励帮贡
        eReward_SpecialItem    , // 特别物品
        eReward_JiaoZi         , // 交子
        eReward_Honor          , // 奖励荣誉
		eReward_CountryMoney   , // 国家资金
		eReward_ScriptExp	  ,  // 奖励经验 脚本给予
        eReward_Max,
    };

    enum QuestRank
    {
        eQuestRank_Nor   , // 普通
        eQuestRank_Nic   , // 良好的
        eQuestRank_Exc   , // 优秀
        eQuestRank_Gold  , // 卓越
        eQuestRank_Legend, // 传说
        //eQuestRank_Epic  , // 史诗
        eQuestRank_Max   ,
    };

    enum QuestType
    {
        Type_Main = 0      , // 主线任务
        Type_Lateral       , // 支线任务
        Type_Campaign      , // 活动任务
        Type_Ectype        , // 副本任务
        Type_Official      , // 官府任务
        Type_Circle        , // 循环任务
        Type_Cruise        , // 巡城任务
        Type_Battalion     , // 军需任务
        Type_Precious      , // 藏宝任务
        Type_Title         , // 称号任务 
        Type_Gut           , // 剧情任务
        Type_Gout          , // 趣味任务
        Type_Guild         , // 帮派任务
        Type_Pub           , // 酒馆任务
        Type_Royal         , // 皇榜任务
        Type_ConQuest      , // 征伐任务
        Type_CountryKing   , // 国运任务
        Type_CountryGeneral, // 出国任务
        Type_CountryLeft   , // 天行任务
        Type_CountryRight  , // 探宝任务
        Type_Adventure     , // 奇遇任务
        Type_Achieve       , // 成就任务
        Type_End           ,
    };

    typedef std::vector<SQuestReward>       RewardType;
    typedef RewardType::iterator            RewardTypeItr;
    typedef RewardType::iterator			RewardTypeItr;
    typedef std::vector<SQuestRequirement>	RequirementType;
    typedef RequirementType::iterator		RequirementTypeItr;
    typedef map<int, QuestTalks>			QuestTalksAll;
    typedef map<int, QuestTalks>::iterator  QuestTalkAllIter;
    typedef RequirementType::iterator       RequirementTypeItr;

    short           Id                  ; // 任务Id
    DWORD           QuestName           ; // 任务名称
    DWORD           IntroStringId       ; // 任务说明
    RewardType      stReward            ; // 报酬
    RequirementType stCommitRequirement ; // 任务完成的需求
    RequirementType stReceiveRequirement; // 接受任务的需求
    bool            IsRepeat            ; // 是否重复试练
    bool            IsCancel            ; // 任务是否可被删除,重要的任务不能被删除,接任务的时候也不增加激活任务数
    BYTE            HintLevelMin        ; // 提示任务下限
    BYTE            HintLevelMax        ; // 提示任务上限
    DWORD           AcceptTargetId      ; // 接任务目标
    DWORD           ReplyTargetId       ; // 交任务的NPC名称
    short           MapId               ; // 任务的地图Id
    DWORD           TargetStringId      ; // 任务目标
    bool            CanAssist           ; // 可否协助
    bool            CanShare            ; // 可否共享
    short           RankId              ; // 任务品质
    unsigned char   chQuestType         ; // 任务类型
    bool            CanDisplay          ; // 客户端是否可显示
	bool			bDisplayInCanAccept	; // 是否在可接任务中显示
    bool            IsSingleRequirement ; // 完成一个条件即可完成任务

	//增加一个任务所属国家字段，0表示所有人都能接
	BYTE			Country				; //国家ID

    QuestTalksAll   vQuestTalks;          // 任务特殊对话
	

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
        AcceptTargetId = InvalidLogicNumber;
        ReplyTargetId = InvalidLogicNumber;
        RankId = -1;
        chQuestType = Type_Main;
        CanDisplay = true;
        IsSingleRequirement = false;
		Country = 0;
		bDisplayInCanAccept = true;
    }

    const char* GetQuestName();
    const char* GetQuestStateInfo();
    const char* GetRewardNpcName();
    const char* GetAcceptNpcName();
    const char* GetQuestInfo();

    SQuest& operator =(const SQuest& squest)
    {
        if (this == &squest)
        { return *this; }

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
		bDisplayInCanAccept = squest.bDisplayInCanAccept;
        IsSingleRequirement = squest.IsSingleRequirement;
		Country = squest.Country;
        vQuestTalks = squest.vQuestTalks;
        return *this;
    }

    bool HaveQuestTalk( short stPosition )
    {
        return ( vQuestTalks.find( stPosition ) != vQuestTalks.end() );
    }

    int GetPlayerReceiveQuestLevel()
    {
        for ( RequirementTypeItr itrPlayerLevel=stReceiveRequirement.begin();itrPlayerLevel!=stReceiveRequirement.end();++itrPlayerLevel)
        {
            if (itrPlayerLevel->byType == eRequirement_Level)//eRequirement_Level
            { return itrPlayerLevel->Value; }
        }
        return 1;
    }

    int GetPlayerReceiveQuestSex()
    {
        for ( RequirementTypeItr itrPlayerLevel=stReceiveRequirement.begin();itrPlayerLevel!=stReceiveRequirement.end();++itrPlayerLevel)
        {
            if (itrPlayerLevel->byType == eRequirement_Sex)//eRequirement_Level
            { return itrPlayerLevel->Value; }
        }
        return 2;
    }

    int GetPlayerReceiveQuestProfession()
    {
        for ( RequirementTypeItr itrPlayerLevel=stReceiveRequirement.begin();itrPlayerLevel!=stReceiveRequirement.end();++itrPlayerLevel)
        {
            if (itrPlayerLevel->byType == eRequirement_Profession)//eRequirement_Profession
            { return itrPlayerLevel->Value; }
        }
        return 0xff;
    }

    int GetPlayerReceiveQuestReputation()
    {
        for ( RequirementTypeItr itrPlayerLevel=stReceiveRequirement.begin();itrPlayerLevel!=stReceiveRequirement.end();++itrPlayerLevel)
        {
            if (itrPlayerLevel->byType == eRequirement_Reputation)//eRequirement_Reputation
            { return itrPlayerLevel->Value; }
        }
        return 1;
    }

    short AddReceiveRequirement( const SQuestRequirement* pRequirement )
    {
        stReceiveRequirement.push_back(*pRequirement);
        return (short)stReceiveRequirement.size();
    }

    int RemoveReceiveRequirement( const SQuestRequirement* pRequirement )
    {
        if( stReceiveRequirement.empty() )
        { return -1; }

        int i = 0;
        for( RequirementTypeItr it = stReceiveRequirement.begin();it != stReceiveRequirement.end();++it)
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

    SQuestRequirement* GetReceiveRequirement( int Typeid,int* pBeginPos = NULL)
    {
        int nBeginPos = 0;
        if ( pBeginPos )
        { nBeginPos = *pBeginPos; }

        if( stReceiveRequirement.empty() || nBeginPos >= (int)stReceiveRequirement.size())
        { return NULL; }

        int retPos = nBeginPos + 1;

        for( RequirementTypeItr workitr = stReceiveRequirement.begin() + nBeginPos; workitr != stReceiveRequirement.end() ; ++workitr,++retPos)
        {
            if (workitr->byType == Typeid)
            {
                if (pBeginPos)
                { *pBeginPos = retPos; }
                return &(*workitr);
            }            
        }
        return NULL;
    }

    void ClearCommitRequirement()
    { stCommitRequirement.clear(); }

    void ClearReceiveRequirement()
    { stReceiveRequirement.clear(); }

    void ClearReward()
    { stReward.clear(); }

    short AddCommitRequirement( const SQuestRequirement* pRequirement )
    {
        stCommitRequirement.push_back(*pRequirement);        
        return (short)stCommitRequirement.size();
    }

    int RemoveCommitRequirement( const SQuestRequirement* pRequirement )
    {
        if( stCommitRequirement.empty() )
        { return -1; }

        int i = 0;
        for( RequirementTypeItr it = stCommitRequirement.begin();it != stCommitRequirement.end();++it)
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
        { return NULL; }

        for( RequirementTypeItr workitr = stCommitRequirement.begin() ; workitr != stCommitRequirement.end() ; ++workitr)
        {
            if (workitr->byType == Typeid)
            { return &(*workitr); }
        }
        return NULL;
    }

    int AddReward( const SQuestReward* pReward )
    {
        stReward.push_back(*pReward);
        return (int)stReward.size();
    }

    int RemoveReward( const SQuestReward* pReward )
    {
        int i = 0;
        for ( RewardTypeItr it = stReward.begin(); it != stReward.end();++it)
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
        { return NULL; }

        for( RewardTypeItr workitr = stReward.begin() ; workitr != stReward.end() ; ++workitr)
        {
            if (workitr->byType == Typeid)
            { return &(*workitr); }
        }
        return NULL;
    }

    bool IsPubQuest()       { return ( chQuestType == Type_Pub || chQuestType == Type_Royal ); }
    bool IsConQuest()       { return chQuestType == Type_ConQuest;                             }    
};

#pragma pack ( pop )

#endif // __COMMON_QUESTDEFINE_H__
